/* 
 * File:   shell.cpp
 * Author: Sam Rappl and Jacob Inkrote
 *
 */
 
#include "libfm/composition.h"
#include "libfm/utilities.h"
#include "nlohmann/json.h"

typedef std::string (*callback)(std::string zipPath, std::string mode, std::string input);

std::string executeShell(callback execute, PacketPart *rootNode,
		std::string dmPath, std::string cmPath) {
	// Call the Driver Module and store the JSON it passes back as a composition
	nlohmann::json composition = execute(dmPath, "driver", "");
	// Populate the composition with the Packet Hierarchy
	Composition comp;
	from_json(&composition, &comp);
	comp.setPacketTreeRoot(rootNode);
	to_json(&composition, &comp);
	// Execute Packets in a Leftmost Depth-First-Search order, passing them the
	// most recent composition JSON
	run(execute, rootNode, &composition, cmPath);
	return execute(cmPath, "finalcontrol", packetin);
}

void run(callback execute, PacketPart *node, nlohmann::json *compositionJSON,
		std::string cmPath) {
	if (node->executed == false) {
		*compositionJSON = execute(node->packetPath, node->mode, *compositionJSON);
		*compositionJSON = execute(cmPath, "control", *compositionJSON);
		node->executed = true;
	}
	if (!node->isLeaf()) {
		std::vector<PacketPart*> children = node->getChildren();
		for (int i = 0; i < children.size(); i++) {
			run(execute, children[i], compositionJSON, cmPath);
		}
	}
}
