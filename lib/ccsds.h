/* -*- c++ -*- */
/*
 * Copyright 2016 André Løfaldli.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef __CCSDS_H__
#define __CCSDS_H__

#include <stdint.h>
#include <stdio.h>

// reed solomon(233,255) constants
#define RS_BITS_PER_SYM 8
#define RS_DATA_LEN 223
#define RS_PARITY_LEN 32
#define RS_BLOCK_LEN (RS_DATA_LEN + RS_PARITY_LEN)
#define RS_MAX_NBLOCKS 8
#define RS_GFPOLY 0x187 // (x^8 + x^7 + x^2 + x^1 + 1)
#define RS_APRIM 11
#define RS_FCS 112

// frame constants
#define SYNC_WORD_LEN 4
//#define SYNC_WORD 0x1acffc1d
#define SCRAMBLER_POLY_LEN 255
#define DATA_MAX_LEN (RS_DATA_LEN * RS_MAX_NBLOCKS)
#define CODEWORD_MAX_LEN (RS_BLOCK_LEN * RS_MAX_NBLOCKS)
//#define TOTAL_FRAME_LEN (SYNC_WORD_LEN + CODEWORD_LEN)

struct ccsds_tx_pkt {
    uint8_t sync_word[SYNC_WORD_LEN];
    uint8_t codeword[CODEWORD_MAX_LEN];
}__attribute__((packed));

const uint8_t SYNC_WORD[SYNC_WORD_LEN] = {0x1a, 0xcf, 0xfc, 0x1d};
// generator polynome: 0x1a9 (x^8 + x^7 + x^5 + x^3 + 1)
const uint8_t SCRAMBLER_POLY[SCRAMBLER_POLY_LEN] = {0xFF, 0x48, 0x0E, 0xC0, 0x9A, 0x0D, 0x70, 0xBC,
            0x8E, 0x2C, 0x93, 0xAD, 0xA7, 0xB7, 0x46, 0xCE, 0x5A, 0x97, 0x7D, 0xCC, 0x32,
            0xA2, 0xBF, 0x3E, 0x0A, 0x10, 0xF1, 0x88, 0x94, 0xCD, 0xEA, 0xB1, 0xFE, 0x90,
            0x1D, 0x81, 0x34, 0x1A, 0xE1, 0x79, 0x1C, 0x59, 0x27, 0x5B, 0x4F, 0x6E, 0x8D,
            0x9C, 0xB5, 0x2E, 0xFB, 0x98, 0x65, 0x45, 0x7E, 0x7C, 0x14, 0x21, 0xE3, 0x11,
            0x29, 0x9B, 0xD5, 0x63, 0xFD, 0x20, 0x3B, 0x02, 0x68, 0x35, 0xC2, 0xF2, 0x38,
            0xB2, 0x4E, 0xB6, 0x9E, 0xDD, 0x1B, 0x39, 0x6A, 0x5D, 0xF7, 0x30, 0xCA, 0x8A,
            0xFC, 0xF8, 0x28, 0x43, 0xC6, 0x22, 0x53, 0x37, 0xAA, 0xC7, 0xFA, 0x40, 0x76,
            0x04, 0xD0, 0x6B, 0x85, 0xE4, 0x71, 0x64, 0x9D, 0x6D, 0x3D, 0xBA, 0x36, 0x72,
            0xD4, 0xBB, 0xEE, 0x61, 0x95, 0x15, 0xF9, 0xF0, 0x50, 0x87, 0x8C, 0x44, 0xA6,
            0x6F, 0x55, 0x8F, 0xF4, 0x80, 0xEC, 0x09, 0xA0, 0xD7, 0x0B, 0xC8, 0xE2, 0xC9,
            0x3A, 0xDA, 0x7B, 0x74, 0x6C, 0xE5, 0xA9, 0x77, 0xDC, 0xC3, 0x2A, 0x2B, 0xF3,
            0xE0, 0xA1, 0x0F, 0x18, 0x89, 0x4C, 0xDE, 0xAB, 0x1F, 0xE9, 0x01, 0xD8, 0x13,
            0x41, 0xAE, 0x17, 0x91, 0xC5, 0x92, 0x75, 0xB4, 0xF6, 0xE8, 0xD9, 0xCB, 0x52,
            0xEF, 0xB9, 0x86, 0x54, 0x57, 0xE7, 0xC1, 0x42, 0x1E, 0x31, 0x12, 0x99, 0xBD,
            0x56, 0x3F, 0xD2, 0x03, 0xB0, 0x26, 0x83, 0x5C, 0x2F, 0x23, 0x8B, 0x24, 0xEB,
            0x69, 0xED, 0xD1, 0xB3, 0x96, 0xA5, 0xDF, 0x73, 0x0C, 0xA8, 0xAF, 0xCF, 0x82,
            0x84, 0x3C, 0x62, 0x25, 0x33, 0x7A, 0xAC, 0x7F, 0xA4, 0x07, 0x60, 0x4D, 0x06,
            0xB8, 0x5E, 0x47, 0x16, 0x49, 0xD6, 0xD3, 0xDB, 0xA3, 0x67, 0x2D, 0x4B, 0xBE,
            0xE6, 0x19, 0x51, 0x5F, 0x9F, 0x05, 0x08, 0x78, 0xC4, 0x4A, 0x66, 0xF5, 0x58
        };

inline void print_bytes(uint8_t *data, uint32_t length) {
    for (uint32_t i=0; i<length; i+=10) {
        // print hex representation....
        printf("    %4i: ", i);
        for (uint8_t j=0; j<10; j++) {
            if (i+j < length)
                printf("%x%x ", (data[i+j] >> 4 & 0x0f), (data[i+j] & 0x0f));
            else
                printf("   ");
        }
        // ...and ascii
        printf("  ");
        for (uint8_t j=0; j<10 && i+j<length; j++) {
            if (data[i+j] > 31 && data[i+j] < 127)
                printf("%c", data[i+j]);
            else
                printf(".");
        }
        printf("\n");
    }
}

inline void scramble(uint8_t *data, uint32_t length) {
    for (uint32_t i=0; i<length; i++) {
        data[i] ^= SCRAMBLER_POLY[i%SCRAMBLER_POLY_LEN];
    }
}
inline void descramble(uint8_t *data, uint32_t length) {
    // self inverse function
    scramble(data, length);
}

#endif // __CCSDS_H__
