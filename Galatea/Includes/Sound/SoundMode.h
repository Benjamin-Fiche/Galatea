#pragma once

typedef unsigned int G_SOUND_MODE;
#define G_SOUND_DEFAULT                                0x00000000
#define G_SOUND_LOOP_OFF                               0x00000001
#define G_SOUND_LOOP_NORMAL                            0x00000002
#define G_SOUND_LOOP_BIDI                              0x00000004
#define G_SOUND_2D                                     0x00000008
#define G_SOUND_3D                                     0x00000010
#define G_SOUND_CREATESTREAM                           0x00000080
#define G_SOUND_CREATESAMPLE                           0x00000100
#define G_SOUND_CREATECOMPRESSEDSAMPLE                 0x00000200
#define G_SOUND_OPENUSER                               0x00000400
#define G_SOUND_OPENMEMORY                             0x00000800
#define G_SOUND_OPENMEMORY_POINT                       0x10000000
#define G_SOUND_OPENRAW                                0x00001000
#define G_SOUND_OPENONLY                               0x00002000
#define G_SOUND_ACCURATETIME                           0x00004000
#define G_SOUND_MPEGSEARCH                             0x00008000
#define G_SOUND_NONBLOCKING                            0x00010000
#define G_SOUND_UNIQUE                                 0x00020000
#define G_SOUND_3D_HEADRELATIVE                        0x00040000
#define G_SOUND_3D_WORLDRELATIVE                       0x00080000
#define G_SOUND_3D_INVERSEROLLOFF                      0x00100000
#define G_SOUND_3D_LINEARROLLOFF                       0x00200000
#define G_SOUND_3D_LINEARSQUAREROLLOFF                 0x00400000
#define G_SOUND_3D_INVERSETAPEREDROLLOFF               0x00800000
#define G_SOUND_3D_CUSTOMROLLOFF                       0x04000000
#define G_SOUND_3D_IGNOREGEOMETRY                      0x40000000
#define G_SOUND_IGNORETAGS                             0x02000000
#define G_SOUND_LOWMEM                                 0x08000000
#define G_SOUND_VIRTUAL_PLAYFROMSTART                  0x80000000