/* 
 * File:   constants.h
 * Author: Sam Rappl and Jacob Inkrote
 *
 */
 
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

/** FuseMuse Pitches */
// Octave 0
const int c0 = 0;
const int cs0 = 1;
const int df0 = 1;
const int d0 = 2;
const int ds0 = 3;
const int ef0 = 3;
const int e0 = 4;
const int ff0 = 4;
const int es0 = 5;
const int f0 = 5;
const int fs0 = 6;
const int gf0 = 6;
const int g0 = 7;
const int gs0 = 8;
const int af0 = 8;
const int a0 = 9;
const int as0 = 10;
const int bf0 = 10;
const int b0 = 11;
const int cf1 = 11;
// Octave 1
const int bs0 = 12;
const int c1 = 12;
const int cs1 = 13;
const int df1 = 13;
const int d1 = 14;
const int ds1 = 15;
const int ef1 = 15;
const int e1 = 16;
const int ff1 = 16;
const int es1 = 17;
const int f1 = 17;
const int fs1 = 18;
const int gf1 = 18;
const int g1 = 19;
const int gs1 = 20;
const int af1 = 20;
const int a1 = 21;
const int as1 = 22;
const int bf1 = 22;
const int b1 = 23;
const int cf2 = 23;
// Octave 2
const int bs1 = 24;
const int c2 = 24;
const int cs2 = 25;
const int df2 = 25;
const int d2 = 26;
const int ds2 = 27;
const int ef2 = 27;
const int e2 = 28;
const int ff2 = 28;
const int es2 = 29;
const int f2 = 29;
const int fs2 = 30;
const int gf2 = 30;
const int g2 = 31;
const int gs2 = 32;
const int af2 = 32;
const int a2 = 33;
const int as2 = 34;
const int bf2 = 34;
const int b2 = 35;
const int cf3 = 35;
// Octave 3
const int bs2 = 36;
const int c3 = 36;
const int cs3 = 37;
const int df3 = 37;
const int d3 = 38;
const int ds3 = 39;
const int ef3 = 39;
const int e3 = 40;
const int ff3 = 40;
const int es3 = 41;
const int f3 = 41;
const int fs3 = 42;
const int gf3 = 42;
const int g3 = 43;
const int gs3 = 44;
const int af3 = 44;
const int a3 = 45;
const int as3 = 46;
const int bf3 = 46;
const int b3 = 47;
const int cf4 = 47;
// Octave 4
const int bs3 = 48;
const int c4 = 48;
const int cs4 = 49;
const int df4 = 49;
const int d4 = 50;
const int ds4 = 51;
const int ef4 = 51;
const int e4 = 52;
const int ff4 = 52;
const int es4 = 53;
const int f4 = 53;
const int fs4 = 54;
const int gf4 = 54;
const int g4 = 55;
const int gs4 = 56;
const int af4 = 56;
const int a4 = 57;
const int as4 = 58;
const int bf4 = 58;
const int b4 = 59;
const int cf5 = 59;
// Octave 5
const int bs4 = 60;
const int c5 = 60;
const int cs5 = 61;
const int df5 = 61;
const int d5 = 62;
const int ds5 = 63;
const int ef5 = 63;
const int e5 = 64;
const int ff5 = 64;
const int es5 = 65;
const int f5 = 65;
const int fs5 = 66;
const int gf5 = 66;
const int g5 = 67;
const int gs5 = 68;
const int af5 = 68;
const int a5 = 69;
const int as5 = 70;
const int bf5 = 70;
const int b5 = 71;
const int cf6 = 71;
// Octave 6
const int bs5 = 72;
const int c6 = 72;
const int cs6 = 73;
const int df6 = 73;
const int d6 = 74;
const int ds6 = 75;
const int ef6 = 75;
const int e6 = 76;
const int ff6 = 76;
const int es6 = 77;
const int f6 = 77;
const int fs6 = 78;
const int gf6 = 78;
const int g6 = 79;
const int gs6 = 80;
const int af6 = 80;
const int a6 = 81;
const int as6 = 82;
const int bf6 = 82;
const int b6 = 83;
const int cf7 = 83;
// Octave 7
const int bs6 = 84;
const int c7 = 84;
const int cs7 = 85;
const int df7 = 85;
const int d7 = 86;
const int ds7 = 87;
const int ef7 = 87;
const int e7 = 88;
const int ff7 = 88;
const int es7 = 89;
const int f7 = 89;
const int fs7 = 90;
const int gf7 = 90;
const int g7 = 91;
const int gs7 = 92;
const int af7 = 92;
const int a7 = 93;
const int as7 = 94;
const int bf7 = 94;
const int b7 = 95;
const int cf8 = 95;
// Octave 8
const int bs7 = 96;
const int c8 = 96;
const int cs8 = 97;
const int df8 = 97;
const int d8 = 98;
const int ds8 = 99;
const int ef8 = 99;
const int e8 = 100;
const int ff8 = 100;
const int es8 = 101;
const int f8 = 101;
const int fs8 = 102;
const int gf8 = 102;
const int g8 = 103;
const int gs8 = 104;
const int af8 = 104;
const int a8 = 105;
const int as8 = 106;
const int bf8 = 106;
const int b8 = 107;
const int cf9 = 107;
// Octave 9
const int bs8 = 108;
const int c9 = 108;
const int cs9 = 109;
const int df9 = 109;
const int d9 = 110;
const int ds9 = 111;
const int ef9 = 111;
const int e9 = 112;
const int ff9 = 112;
const int es9 = 113;
const int f9 = 113;
const int fs9 = 114;
const int gf9 = 114;
const int g9 = 115;
const int gs9 = 116;
const int af9 = 116;
const int a9 = 117;
const int as9 = 118;
const int bf9 = 118;
const int b9 = 119;
const int cf10 = 119;
// Octave 10
const int bs9 = 120;
const int c10 = 121;
const int cs10 = 122;
const int df10 = 122;
const int d10 = 123;
const int ds10 = 124;
const int ef10 = 124;
const int e10 = 125;
const int ff10 = 125;
const int es10 = 126;
const int f10 = 126;
// Rest
const int rest = 127;

/** FuseMuse Durations */
// One-Hundred Twenty-Eighth Note Variants
const int triplet_one_twenty_eighth_note = 2;
const int one_twenty_eighth_note = 3;
const int triplet_dotted_one_twenty_eighth_note = 3;
// Sixty-Fourth Note Variants
const int triplet_sixty_fourth_note = 4;
const int sixty_fourth_note = 6;
const int triplet_dotted_sixty_fourth_note = 6;
const int triplet_double_dotted_sixty_fourth_note = 7;
const int dotted_sixty_fourth_note = 9;
// Thirty-Second Note Variants
const int triplet_thirty_second_note = 8;
const int thirty_second_note = 12;
const int triplet_dotted_thirty_second_note = 12;
const int triplet_double_dotted_thirty_second_note = 14;
const int dotted_thirty_second_note = 18;
const int double_dotted_thirty_second_note = 21;
// Sixteenth Note Variants
const int triplet_sixteenth_note = 16;
const int sixteenth_note = 24;
const int triplet_dotted_sixteenth_note = 24;
const int triplet_double_dotted_sixteenth_note = 28;
const int dotted_sixteenth_note = 36;
const int double_dotted_sixteenth_note = 42;
// Eighth Note Variants
const int triplet_eighth_note = 32;
const int eighth_note = 48;
const int triplet_dotted_eighth_note = 48;
const int triplet_double_dotted_eighth_note = 56;
const int dotted_eighth_note = 72;
const int double_dotted_eighth_note = 84;
// Quarter Note Variants
const int triplet_quarter_note = 64;
const int quarter_note = 96;
const int triplet_dotted_quarter_note = 96;
const int triplet_double_dotted_quarter_note = 112;
const int dotted_quarter_note = 144;
const int double_dotted_quarter_note = 168;
// Half Note Variants
const int triplet_half_note = 128;
const int half_note = 192;
const int triplet_dotted_half_note = 192;
const int triplet_double_dotted_half_note = 224;
const int dotted_half_note = 288;
const int double_dotted_half_note = 336;
// Whole Note Variants
const int triplet_whole_note = 256;
const int whole_note = 384;
const int triplet_dotted_whole_note = 384;
const int triplet_double_dotted_whole_note = 448;
const int dotted_whole_note = 576;
const int double_dotted_whole_note = 672;

/** Common Scales */
// Common Scale Intervals
const std::vector<char> ionian_intervals = {2, 2, 1, 2, 2, 2, 1};
const std::vector<char> dorian_intervals = {2, 1, 2, 2, 2, 1, 2};
const std::vector<char> phrygian_intervals = {1, 2, 2, 2, 1, 2, 2};
const std::vector<char> lydian_intervals = {2, 2, 2, 1, 2, 2, 1};
const std::vector<char> mixolydian_intervals = {2, 2, 1, 2, 2, 1, 2};
const std::vector<char> aeolian_intervals = {2, 1, 2, 2, 1, 2, 2};
const std::vector<char> locrian_intervals = {1, 2, 2, 1, 2, 2, 2};
const std::vector<char> major_intervals = ionian_intervals;
const std::vector<char> minor_intervals = aeolian_intervals;

/** Dynamics */
// Dynamics
const int ppp = 0;
const int pp = 1;
const int p = 2;
const int mp = 3;
const int mf = 4;
const int f = 5;
const int ff = 6;
const int fff = 7;

/** Common Chords */
// Chords
const std::vector<int> c_major_chord = {c3, e3, g3};
const std::vector<int> c_minor_chord = {c3, ef3, g3};
const std::vector<int> c_sus2_chord = {c3, d3, g3};
const std::vector<int> c_sus4_chord = {c3, f3, g3};
const std::vector<int> c_major_7_chord = {c3, e3, g3, b3};
const std::vector<int> c_minor_7_chord = {c3, ef3, g3, bf3};
const std::vector<int> cs_major_chord = {cs3, f3, gs3};
const std::vector<int> cs_minor_chord = {cs3, e3, gs3};
const std::vector<int> cs_sus2_chord = {cs3, ds3, gs3};
const std::vector<int> cs_sus4_chord = {cs3, fs3, gs3};
const std::vector<int> cs_major_7_chord = {cs3, f3, gs3, c3};
const std::vector<int> cs_minor_7_chord = {cs3, e3, gs3, b3};
const std::vector<int> df_major_chord = {df3, f3, af3};
const std::vector<int> df_minor_chord = {df3, e3, af3};
const std::vector<int> df_sus2_chord = {df3, ef3, af3};
const std::vector<int> df_sus4_chord = {df3, gf3, af3};
const std::vector<int> df_major_7_chord = {df3, f3, af3, c4};
const std::vector<int> df_minor_7_chord = {df3, e3, af3, b3};
const std::vector<int> d_major_chord = {d3, fs3, a3};
const std::vector<int> d_minor_chord = {d3, f3, a3};
const std::vector<int> d_sus2_chord = {d3, e3, a3};
const std::vector<int> d_sus4_chord = {d3, g3, a3};
const std::vector<int> d_major_7_chord = {d3, fs3, a3, cs4};
const std::vector<int> d_minor_7_chord = {d3, f3, a3, c4};
const std::vector<int> ds_major_chord = {ds3, g3, as3};
const std::vector<int> ds_minor_chord = {ds3, fs3, as3};
const std::vector<int> ds_sus2_chord = {ds3, f3, as3};
const std::vector<int> ds_sus4_chord = {ds3, gs3, as3};
const std::vector<int> ds_major_7_chord = {ds3, g3, as3, d4};
const std::vector<int> ds_minor_7_chord = {ds3, fs3, as3, cs4};
const std::vector<int> ef_major_chord = {ef3, g3, bf3};
const std::vector<int> ef_minor_chord = {ef3, gf3, bf3};
const std::vector<int> ef_sus2_chord = {ef3, f3, bf3};
const std::vector<int> ef_sus4_chord = {ef3, af3, bf3};
const std::vector<int> ef_major_7_chord = {ef3, g3, bf3, d4};
const std::vector<int> ef_minor_7_chord = {ef3, gf3, bf3, df4};
const std::vector<int> e_major_chord = {e3, gs3, b3};
const std::vector<int> e_minor_chord = {e3, g3, b3};
const std::vector<int> e_sus2_chord = {e3, fs3, b3};
const std::vector<int> e_sus4_chord = {e3, a3, b3};
const std::vector<int> e_major_7_chord = {e3, gs3, b3, ds4};
const std::vector<int> e_minor_7_chord = {e3, g3, b3, d4};
const std::vector<int> f_major_chord = {f3, a3, c4};
const std::vector<int> f_minor_chord = {f3, af3, c4};
const std::vector<int> f_sus2_chord = {f3, g3, c4};
const std::vector<int> f_sus4_chord = {f3, bf3, c4};
const std::vector<int> f_major_7_chord = {f3, a3, c4, e4};
const std::vector<int> f_minor_7_chord = {f3, af3, c4, ef4};
const std::vector<int> fs_major_chord = {fs3, as3, cs4};
const std::vector<int> fs_minor_chord = {fs3, a3, cs4};
const std::vector<int> fs_sus2_chord = {fs3, gs3, cs4};
const std::vector<int> fs_sus4_chord = {fs3, b3, cs4};
const std::vector<int> fs_major_7_chord = {fs3, as3, cs4, f4};
const std::vector<int> fs_minor_7_chord = {fs3, a3, cs4, f4};
const std::vector<int> gf_major_chord = {gf3, bf3, df4};
const std::vector<int> gf_minor_chord = {gf3, a3, df4};
const std::vector<int> gf_sus2_chord = {gf3, af3, df4};
const std::vector<int> gf_sus4_chord = {gf3, b3, df4};
const std::vector<int> gf_major_7_chord = {gf3, bf3, df4, f4};
const std::vector<int> gf_minor_7_chord = {gf3, a3, df4, e4};
const std::vector<int> g_major_chord = {g3, b3, d4};
const std::vector<int> g_minor_chord = {g3, bf3, d4};
const std::vector<int> g_sus2_chord = {g3, a3, d4};
const std::vector<int> g_sus4_chord = {g3, c4, d4};
const std::vector<int> g_major_7_chord = {g3, b3, d4, fs4};
const std::vector<int> g_minor_7_chord = {g3, bf3, d4, f4};
const std::vector<int> gs_major_chord = {gs3, c4, ds4};
const std::vector<int> gs_minor_chord = {gs3, b3, ds4};
const std::vector<int> gs_sus2_chord = {gs3, as3, ds4};
const std::vector<int> gs_sus4_chord = {gs3, cs4, ds4};
const std::vector<int> gs_major_7_chord = {gs3, c4, ds4, g4};
const std::vector<int> gs_minor_7_chord = {gs3, b3, ds4, fs4};
const std::vector<int> af_major_chord = {af3, c4, ef4};
const std::vector<int> af_minor_chord = {af3, b3, ef4};
const std::vector<int> af_sus2_chord = {af3, bf3, ef4};
const std::vector<int> af_sus4_chord = {af3, df4, ef4};
const std::vector<int> af_major_7_chord = {af3, c4, ef4, g4};
const std::vector<int> af_minor_7_chord = {af3, b3, ef4, gf4};
const std::vector<int> a_major_chord = {a3, cs4, e4};
const std::vector<int> a_minor_chord = {a3, c4, e4};
const std::vector<int> a_sus2_chord = {a3, b3, e4};
const std::vector<int> a_sus4_chord = {a3, d4, e4};
const std::vector<int> a_major_7_chord = {a3, cs4, e4, gs4};
const std::vector<int> a_minor_7_chord = {a3, c4, e4, g4};
const std::vector<int> as_major_chord = {as3, d4, f4};
const std::vector<int> as_minor_chord = {as3, cs4, f4};
const std::vector<int> as_sus2_chord = {as3, c4, f4};
const std::vector<int> as_sus4_chord = {as3, ds4, f4};
const std::vector<int> as_major_7_chord = {as3, d4, f4, a4};
const std::vector<int> as_minor_7_chord = {as3, cs4, f4, gs4};
const std::vector<int> bf_major_chord = {bf3, d4, f4};
const std::vector<int> bf_minor_chord = {bf3, df4, f4};
const std::vector<int> bf_sus2_chord = {bf3, c4, f4};
const std::vector<int> bf_sus4_chord = {bf3, ef4, f4};
const std::vector<int> bf_major_7_chord = {bf3, d4, f4, a4};
const std::vector<int> bf_minor_7_chord = {bf3, df4, f4, af4};
const std::vector<int> b_major_chord = {b3, ds4, fs4};
const std::vector<int> b_minor_chord = {b3, d4, fs4};
const std::vector<int> b_sus2_chord = {b3, cs4, fs4};
const std::vector<int> b_sus4_chord = {b3, e4, fs4};
const std::vector<int> b_major_7_chord = {b3, ds4, fs4, as4};
const std::vector<int> b_minor_7_chord = {b3, d4, fs4, a4};

#endif /* CONSTANTS_H */

