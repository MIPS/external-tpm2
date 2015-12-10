// This file was extracted from the TCG Published
// Trusted Platform Module Library
// Part 4: Supporting Routines
// Family "2.0"
// Level 00 Revision 01.16
// October 30, 2014

#include    "TPMB.h"
TPM2B_BYTE_VALUE(1);
TPM2B_BYTE_VALUE(16);
TPM2B_BYTE_VALUE(2);
TPM2B_BYTE_VALUE(24);
TPM2B_BYTE_VALUE(28);
TPM2B_BYTE_VALUE(32);
TPM2B_BYTE_VALUE(4);
TPM2B_BYTE_VALUE(48);
TPM2B_BYTE_VALUE(64);
TPM2B_BYTE_VALUE(66);
TPM2B_BYTE_VALUE(8);
TPM2B_BYTE_VALUE(80);
#if defined ECC_NIST_P192 && ECC_NIST_P192 == YES
const TPM2B_24_BYTE_VALUE NIST_P192_p = {24,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const TPM2B_24_BYTE_VALUE NIST_P192_a = {24,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}};
const TPM2B_24_BYTE_VALUE NIST_P192_b = {24,
       {0x64, 0x21, 0x05, 0x19, 0xE5, 0x9C, 0x80, 0xE7,
        0x0F, 0xA7, 0xE9, 0xAB, 0x72, 0x24, 0x30, 0x49,
        0xFE, 0xB8, 0xDE, 0xEC, 0xC1, 0x46, 0xB9, 0xB1}};
const TPM2B_24_BYTE_VALUE NIST_P192_gX = {24,
       {0x18, 0x8D, 0xA8, 0x0E, 0xB0, 0x30, 0x90, 0xF6,
        0x7C, 0xBF, 0x20, 0xEB, 0x43, 0xA1, 0x88, 0x00,
        0xF4, 0xFF, 0x0A, 0xFD, 0x82, 0xFF, 0x10, 0x12}};
const TPM2B_24_BYTE_VALUE NIST_P192_gY = {24,
       {0x07, 0x19, 0x2B, 0x95, 0xFFC, 0x8D, 0xA7, 0x86,
        0x31, 0x01, 0x1ED, 0x6B, 0x24, 0xCD, 0xD5, 0x73,
        0xF9, 0x77, 0xA1, 0x1E, 0x79, 0x48, 0x11}};
const TPM2B_24_BYTE_VALUE NIST_P192_n = {24,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xDE, 0xF8, 0x36,
        0x14, 0x6B, 0xC9, 0xB1, 0xB4, 0xD2, 0x28, 0x31}};
const TPM2B_1_BYTE_VALUE NIST_P192_h = {1,{1}};
const ECC_CURVE_DATA NIST_P192 = {&NIST_P192_p.b, &NIST_P192_a.b, &NIST_P192_b.b,
                                  &NIST_P192_gX.b, &NIST_P192_gY.b, &NIST_P192_n.b,
                                  &NIST_P192_h.b};
#endif // ECC_NIST_P192
#if defined ECC_NIST_P224 && ECC_NIST_P224 == YES
const TPM2B_28_BYTE_VALUE NIST_P224_p = {28,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01}};
const TPM2B_28_BYTE_VALUE NIST_P224_a = {28,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFE}};
const TPM2B_28_BYTE_VALUE NIST_P224_b = {28,
       {0xB4, 0x05, 0x0A, 0x85, 0x0C, 0x04, 0xB3, 0xAB,
        0xF5, 0x41, 0x32, 0x56, 0x50, 0x44, 0xB0, 0xB7,
        0xD7, 0xBF, 0xD8, 0xBA, 0x27, 0x0B, 0x39, 0x43,
        0x23, 0x55, 0xFF, 0xB4}};
const TPM2B_28_BYTE_VALUE NIST_P224_gX = {28,
       {0xB7, 0x0E, 0x0C, 0xBD, 0x6B, 0xB4, 0xBF, 0x7F,
        0x32, 0x13, 0x90, 0xB9, 0x4A, 0x03, 0xC1, 0xD3,
        0x56, 0xC2, 0x11, 0x22, 0x34, 0x32, 0x80, 0xD6,
        0x11, 0x5C, 0x1D, 0x21}};
const TPM2B_28_BYTE_VALUE NIST_P224_gY = {28,
       {0xBD, 0x37, 0x63, 0x88, 0xB5, 0xF7, 0x23, 0xFB,
        0x4C, 0x22, 0xDF, 0xE6, 0xCD, 0x43, 0x75, 0xA0,
        0x5A, 0x07, 0x47, 0x64, 0x44, 0xD5, 0x81, 0x99,
        0x85, 0x00, 0x7E, 0x34}};
const TPM2B_28_BYTE_VALUE NIST_P224_n = {28,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x16, 0xA2,
        0xE0, 0xB8, 0xF0, 0x3E, 0x13, 0xDD, 0x29, 0x45,
        0x5C, 0x5C, 0x2A, 0x3D}};
const TPM2B_1_BYTE_VALUE NIST_P224_h = {1,{1}};
const ECC_CURVE_DATA NIST_P224 = {&NIST_P224_p.b, &NIST_P224_a.b, &NIST_P224_b.b,
                                  &NIST_P224_gX.b, &NIST_P224_gY.b, &NIST_P224_n.b,
                                  &NIST_P224_h.b};
#endif // ECC_NIST_P224
#if defined ECC_NIST_P256 && ECC_NIST_P256 == YES
const TPM2B_32_BYTE_VALUE NIST_P256_p = {32,
       {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const TPM2B_32_BYTE_VALUE NIST_P256_a = {32,
       {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}};
const TPM2B_32_BYTE_VALUE NIST_P256_b = {32,
       {0x5A, 0xC6, 0x35, 0xD8, 0xAA, 0x3A, 0x93, 0xE7,
        0xB3, 0xEB, 0xBD, 0x55, 0x76, 0x98, 0x86, 0xBC,
        0x65, 0x1D, 0x06, 0xB0, 0xCC, 0x53, 0xB0, 0xF6,
        0x3B, 0xCE, 0x3C, 0x3E, 0x27, 0xD2, 0x60, 0x4B}};
const TPM2B_32_BYTE_VALUE NIST_P256_gX = {32,
       {0x6B, 0x17, 0xD1, 0xF2, 0xE1, 0x2C, 0x42, 0x47,
        0xF8, 0xBC, 0xE6, 0xE5, 0x63, 0xA4, 0x40, 0xF2,
        0x77, 0x03, 0x7D, 0x81, 0x2D, 0xEB, 0x33, 0xA0,
        0xF4, 0xA1, 0x39, 0x45, 0xD8, 0x98, 0xC2, 0x96}};
const TPM2B_32_BYTE_VALUE NIST_P256_gY = {32,
       {0x4F, 0xE3, 0x42, 0xE2, 0xFE, 0x1A, 0x7F, 0x9B,
        0x8E, 0xE7, 0xEB, 0x4A, 0x7C, 0x0F, 0x9E, 0x16,
        0x2B, 0xCE, 0x33, 0x57, 0x6B, 0x31, 0x5E, 0xCE,
        0xCB, 0xB6, 0x40, 0x68, 0x37, 0xBF, 0x51, 0xF5}};
const TPM2B_32_BYTE_VALUE NIST_P256_n = {32,
       {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xBC, 0xE6, 0xFA, 0xAD, 0xA7, 0x17, 0x9E, 0x84,
        0xF3, 0xB9, 0xCA, 0xC2, 0xFC, 0x63, 0x25, 0x51}};
const TPM2B_1_BYTE_VALUE NIST_P256_h = {1,{1}};
const ECC_CURVE_DATA NIST_P256 = {&NIST_P256_p.b, &NIST_P256_a.b, &NIST_P256_b.b,
                                  &NIST_P256_gX.b, &NIST_P256_gY.b, &NIST_P256_n.b,
                                  &NIST_P256_h.b};
#endif // ECC_NIST_P256
#if defined ECC_NIST_P384 && ECC_NIST_P384 == YES
const TPM2B_48_BYTE_VALUE NIST_P384_p = {48,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF}};
const TPM2B_48_BYTE_VALUE NIST_P384_a = {48,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFC}};
const TPM2B_48_BYTE_VALUE NIST_P384_b = {48,
       {0xB3, 0x31, 0x2F, 0xA7, 0xE2, 0x3E, 0xE7, 0xE4,
        0x98, 0x8E, 0x05, 0x6B, 0xE3, 0xF8, 0x2D, 0x19,
        0x18, 0x1D, 0x9C, 0x6E, 0xFE, 0x81, 0x41, 0x12,
        0x03, 0x14, 0x08, 0x8F, 0x50, 0x13, 0x87, 0x5A,
        0xC6, 0x56, 0x39, 0x8D, 0x8A, 0x2E, 0xD1, 0x9D,
        0x2A, 0x85, 0xC8, 0xED, 0xD3, 0xEC, 0x2A, 0xEF}};
const TPM2B_48_BYTE_VALUE NIST_P384_gX = {48,
       {0xAA, 0x87, 0xCA, 0x22, 0xBE, 0x8B, 0x05, 0x37,
        0x8E, 0xB1, 0xC7, 0x1E, 0xF3, 0x20, 0xAD, 0x74,
        0x6E, 0x1D, 0x3B, 0x62, 0x8B, 0xA7, 0x9B, 0x98,
        0x59, 0xF7, 0x41, 0xE0, 0x82, 0x54, 0x2A, 0x38,
        0x55, 0x02, 0xF2, 0x5D, 0xBF, 0x55, 0x29, 0x6C,
        0x3A, 0x54, 0x5E, 0x38, 0x72, 0x76, 0x0A, 0xB7}};
const TPM2B_48_BYTE_VALUE NIST_P384_gY = {48,
       {0x36, 0x17, 0xDE, 0x4A, 0x96, 0x26, 0x2C, 0x6F,
        0x5D, 0x9E, 0x98, 0xBF, 0x92, 0x92, 0xDC, 0x29,
        0xF8, 0xF4, 0x1D, 0xBD, 0x28, 0x9A, 0x14, 0x7C,
        0xE9, 0xDA, 0x31, 0x13, 0xB5, 0xF0, 0xB8, 0xC0,
        0x0A, 0x60, 0xB1, 0xCE, 0x1D, 0x7E, 0x81, 0x9D,
        0x7A, 0x43, 0x1D, 0x7C, 0x90, 0xEA, 0x0E, 0x5F}};
const TPM2B_48_BYTE_VALUE NIST_P384_n = {48,
       {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xC7, 0x63, 0x4D, 0x81, 0xF4, 0x37, 0x2D, 0xDF,
        0x58, 0x1A, 0x0D, 0xB2, 0x48, 0xB0, 0xA7, 0x7A,
        0xEC, 0xEC, 0x19, 0x6A, 0xCC, 0xC5, 0x29, 0x73}};
const TPM2B_1_BYTE_VALUE NIST_P384_h = {1,{1}};
const ECC_CURVE_DATA NIST_P384 = {&NIST_P384_p.b, &NIST_P384_a.b, &NIST_P384_b.b,
                                 &NIST_P384_gX.b, &NIST_P384_gY.b, &NIST_P384_n.b,
                                 &NIST_P384_h.b};
#endif // ECC_NIST_P384
#if defined ECC_NIST_P521 && ECC_NIST_P521 == YES
const TPM2B_66_BYTE_VALUE NIST_P521_p = {66,
       {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF}};
const TPM2B_66_BYTE_VALUE NIST_P521_a = {66,
       {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFC}};
const TPM2B_66_BYTE_VALUE NIST_P521_b = {66,
       {0x00, 0x51, 0x95, 0x3E, 0xB9, 0x61, 0x8E, 0x1C,
        0x9A, 0x1F, 0x92, 0x9A, 0x21, 0xA0, 0xB6, 0x85,
        0x40, 0xEE, 0xA2, 0xDA, 0x72, 0x5B, 0x99, 0xB3,
        0x15, 0xF3, 0xB8, 0xB4, 0x89, 0x91, 0x8E, 0xF1,
        0x09, 0xE1, 0x56, 0x19, 0x39, 0x51, 0xEC, 0x7E,
        0x93, 0x7B, 0x16, 0x52, 0xC0, 0xBD, 0x3B, 0xB1,
        0xBF, 0x07, 0x35, 0x73, 0xDF, 0x88, 0x3D, 0x2C,
        0x34, 0xF1, 0xEF, 0x45, 0x1F, 0xD4, 0x6B, 0x50,
        0x3F, 0x00}};
const TPM2B_66_BYTE_VALUE NIST_P521_gX = {66,
       {0x00, 0xC6, 0x85, 0x8E, 0x06, 0xB7, 0x04, 0x04,
        0xE9, 0xCD, 0x9E, 0x3E, 0xCB, 0x66, 0x23, 0x95,
        0xB4, 0x42, 0x9C, 0x64, 0x81, 0x39, 0x05, 0x3F,
        0xB5, 0x21, 0xF8, 0x28, 0xAF, 0x60, 0x6B, 0x4D,
        0x3D, 0xBA, 0xA1, 0x4B, 0x5E, 0x77, 0xEF, 0xE7,
        0x59, 0x28, 0xFE, 0x1D, 0xC1, 0x27, 0xA2, 0xFF,
        0xA8, 0xDE, 0x33, 0x48, 0xB3, 0xC1, 0x85, 0x6A,
        0x42, 0x9B, 0xF9, 0x7E, 0x7E, 0x31, 0xC2, 0xE5,
        0xBD, 0x66}};
const TPM2B_66_BYTE_VALUE NIST_P521_gY = {66,
       {0x01, 0x18, 0x39, 0x29, 0x6A, 0x78, 0x9A, 0x3B,
        0xC0, 0x04, 0x5C, 0x8A, 0x5F, 0xB4, 0x2C, 0x7D,
        0x1B, 0xD9, 0x98, 0xF5, 0x44, 0x49, 0x57, 0x9B,
        0x44, 0x68, 0x17, 0xAF, 0xBD, 0x17, 0x27, 0x3E,
        0x66, 0x2C, 0x97, 0xEE, 0x72, 0x99, 0x5E, 0xF4,
        0x26, 0x40, 0xC5, 0x50, 0xB9, 0x01, 0x3F, 0xAD,
        0x07, 0x61, 0x35, 0x3C, 0x70, 0x86, 0xA2, 0x72,
        0xC2, 0x40, 0x88, 0xBE, 0x94, 0x76, 0x9F, 0xD1,
        0x66, 0x50}};
const TPM2B_66_BYTE_VALUE NIST_P521_n = {66,
       {0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFA, 0x51, 0x86, 0x87, 0x83, 0xBF, 0x2F,
        0x96, 0x6B, 0x7F, 0xCC, 0x01, 0x48, 0xF7, 0x09,
        0xA5, 0xD0, 0x3B, 0xB5, 0xC9, 0xB8, 0x89, 0x9C,
        0x47, 0xAE, 0xBB, 0x6F, 0xB7, 0x1E, 0x91, 0x38,
        0x64, 0x09}};
const TPM2B_1_BYTE_VALUE NIST_P521_h = {1,{1}};
const ECC_CURVE_DATA NIST_P521 = {&NIST_P521_p.b, &NIST_P521_a.b, &NIST_P521_b.b,
                                 &NIST_P521_gX.b, &NIST_P521_gY.b, &NIST_P521_n.b,
                                 &NIST_P521_h.b};
#endif // ECC_NIST_P521
#if defined ECC_BN_P256 && ECC_BN_P256 == YES
const TPM2B_32_BYTE_VALUE BN_P256_p = {32,
       {0xFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFC, 0XF0, 0XCD,
        0X46, 0XE5, 0XF2, 0X5E, 0XEE, 0X71, 0XA4, 0X9F,
        0X0C, 0XDC, 0X65, 0XFB, 0X12, 0X98, 0X0A, 0X82,
        0XD3, 0X29, 0X2D, 0XDB, 0XAE, 0XD3, 0X30, 0X13}};
const TPM2B_1_BYTE_VALUE BN_P256_a = {1,{0}};
const TPM2B_1_BYTE_VALUE BN_P256_b = {1,{3}};
const TPM2B_1_BYTE_VALUE BN_P256_gX = {1,{1}};
const TPM2B_1_BYTE_VALUE BN_P256_gY = {1,{2}};;
const TPM2B_32_BYTE_VALUE BN_P256_n = {32,
       {0xFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFC, 0XF0, 0XCD,
        0X46, 0XE5, 0XF2, 0X5E, 0XEE, 0X71, 0XA4, 0X9E,
        0X0C, 0XDC, 0X65, 0XFB, 0X12, 0X99, 0X92, 0X1A,
        0XF6, 0X2D, 0X53, 0X6C, 0XD1, 0X0B, 0X50, 0X0D}};
const TPM2B_1_BYTE_VALUE BN_P256_h = {1,{1}};
const ECC_CURVE_DATA BN_P256 = {&BN_P256_p.b, &BN_P256_a.b, &BN_P256_b.b,
                                 &BN_P256_gX.b, &BN_P256_gY.b, &BN_P256_n.b,
                                 &BN_P256_h.b};
#endif // ECC_BN_P256
#if defined ECC_BN_P638 && ECC_BN_P638 == YES
const TPM2B_80_BYTE_VALUE BN_P638_p = {80,
       {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D,
        0x7F, 0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3,
        0xFF, 0xFF, 0xF9, 0x42, 0xD0, 0x00, 0x16, 0x5E,
        0x3F, 0xFF, 0x94, 0x87, 0x00, 0x00, 0xD5, 0x2F,
        0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE, 0x55,
        0xC0, 0x00, 0x86, 0x52, 0x00, 0x21, 0xE5, 0x5B,
        0xFF, 0xFF, 0xF5, 0x1F, 0xFF, 0xF4, 0xEB, 0x80,
        0x00, 0x00, 0x00, 0x4C, 0x80, 0x01, 0x5A, 0xCD,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xE0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67}};
const TPM2B_1_BYTE_VALUE BN_P638_a = {1,{0}};
const TPM2B_2_BYTE_VALUE BN_P638_b = {2,{0x01,0x01}};
const TPM2B_80_BYTE_VALUE BN_P638_gX = {80,
       {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D,
        0x7F, 0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3,
        0xFF, 0xFF, 0xF9, 0x42, 0xD0, 0x00, 0x16, 0x5E,
        0x3F, 0xFF, 0x94, 0x87, 0x00, 0x00, 0xD5, 0x2F,
        0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE, 0x55,
        0xC0, 0x00, 0x86, 0x52, 0x00, 0x21, 0xE5, 0x5B,
        0xFF, 0xFF, 0xF5, 0x1F, 0xFF, 0xF4, 0xEB, 0x80,
        0x00, 0x00, 0x00, 0x4C, 0x80, 0x01, 0x5A, 0xCD,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xE0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66}};
const TPM2B_1_BYTE_VALUE BN_P638_gY = {1,{0x10}};
const TPM2B_80_BYTE_VALUE BN_P638_n = {80,
       {0x23, 0xFF, 0xFF, 0xFD, 0xC0, 0x00, 0x00, 0x0D,
        0x7F, 0xFF, 0xFF, 0xB8, 0x00, 0x00, 0x01, 0xD3,
        0xFF, 0xFF, 0xF9, 0x42, 0xD0, 0x00, 0x16, 0x5E,
        0x3F, 0xFF, 0x94, 0x87, 0x00, 0x00, 0xD5, 0x2F,
        0xFF, 0xFD, 0xD0, 0xE0, 0x00, 0x08, 0xDE, 0x55,
        0x60, 0x00, 0x86, 0x55, 0x00, 0x21, 0xE5, 0x55,
        0xFF, 0xFF, 0xF5, 0x4F, 0xFF, 0xF4, 0xEA, 0xC0,
        0x00, 0x00, 0x00, 0x49, 0x80, 0x01, 0x54, 0xD9,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xED, 0xA0,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61}};
const TPM2B_1_BYTE_VALUE BN_P638_h = {1,{1}};
const ECC_CURVE_DATA BN_P638 = {&BN_P638_p.b, &BN_P638_a.b, &BN_P638_b.b,
                                 &BN_P638_gX.b, &BN_P638_gY.b, &BN_P638_n.b,
                                 &BN_P638_h.b};
#endif // ECC_BN_P638
#if defined ECC_SM2_P256 && ECC_SM2_P256 == YES
const TPM2B_32_BYTE_VALUE SM2_P256_p = {32,
       {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
const TPM2B_32_BYTE_VALUE SM2_P256_a = {32,
       {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC}};
const TPM2B_32_BYTE_VALUE SM2_P256_b = {32,
       {0x28, 0xE9, 0xFA, 0x9E, 0x9D, 0x9F, 0x5E, 0x34,
        0x4D, 0x5A, 0x9E, 0x4B, 0xCF, 0x65, 0x09, 0xA7,
        0xF3, 0x97, 0x89, 0xF5, 0x15, 0xAB, 0x8F, 0x92,
        0xDD, 0xBC, 0xBD, 0x41, 0x4D, 0x94, 0x0E, 0x93}};
const TPM2B_32_BYTE_VALUE SM2_P256_gX = {32,
       {0x32, 0xC4, 0xAE, 0x2C, 0x1F, 0x19, 0x81, 0x19,
        0x5F, 0x99, 0x04, 0x46, 0x6A, 0x39, 0xC9, 0x94,
        0x8F, 0xE3, 0x0B, 0xBF, 0xF2, 0x66, 0x0B, 0xE1,
        0x71, 0x5A, 0x45, 0x89, 0x33, 0x4C, 0x74, 0xC7}};
const TPM2B_32_BYTE_VALUE SM2_P256_gY = {32,
       {0xBC, 0x37, 0x36, 0xA2, 0xF4, 0xF6, 0x77, 0x9C,
        0x59, 0xBD, 0xCE, 0xE3, 0x6B, 0x69, 0x21, 0x53,
        0xD0, 0xA9, 0x87, 0x7C, 0xC6, 0x2A, 0x47, 0x40,
        0x02, 0xDF, 0x32, 0xE5, 0x21, 0x39, 0xF0, 0xA0}};
const TPM2B_32_BYTE_VALUE SM2_P256_n = {32,
       {0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0x72, 0x03, 0xDF, 0x6B, 0x21, 0xC6, 0x05, 0x2B,
        0x53, 0xBB, 0xF4, 0x09, 0x39, 0xD5, 0x41, 0x23}};
const TPM2B_1_BYTE_VALUE SM2_P256_h = {1,{1}};
const ECC_CURVE_DATA SM2_P256 = {&SM2_P256_p.b, &SM2_P256_a.b, &SM2_P256_b.b,
                                 &SM2_P256_gX.b, &SM2_P256_gY.b, &SM2_P256_n.b,
                                  &SM2_P256_h.b};
#endif // ECC_SM2_P256
#define comma
const ECC_CURVE    eccCurves[] = {
#if defined ECC_NIST_P192 && ECC_NIST_P192 == YES
   comma
   {TPM_ECC_NIST_P192,
   192,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SHA256},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &NIST_P192}
#   undef comma
#   define comma ,
#endif // ECC_NIST_P192
#if defined ECC_NIST_P224 && ECC_NIST_P224 == YES
   comma
   {TPM_ECC_NIST_P224,
   224,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SHA256},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &NIST_P224}
#   undef comma
#   define comma ,
#endif // ECC_NIST_P224
#if defined ECC_NIST_P256 && ECC_NIST_P256 == YES
   comma
   {TPM_ECC_NIST_P256,
   256,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SHA256},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &NIST_P256}
#   undef comma
#   define comma ,
#endif // ECC_NIST_P256
#if defined ECC_NIST_P384 && ECC_NIST_P384 == YES
   comma
   {TPM_ECC_NIST_P384,
   384,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SHA384},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &NIST_P384}
#   undef comma
#   define comma ,
#endif // ECC_NIST_P384
#if defined ECC_NIST_P521 && ECC_NIST_P521 == YES
   comma
   {TPM_ECC_NIST_P521,
   521,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SHA512},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &NIST_P521}
#   undef comma
#   define comma ,
#endif // ECC_NIST_P521
#if defined ECC_BN_P256 && ECC_BN_P256 == YES
   comma
   {TPM_ECC_BN_P256,
   256,
   {TPM_ALG_NULL,TPM_ALG_NULL},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &BN_P256}
#   undef comma
#   define comma ,
#endif // ECC_BN_P256
#if defined ECC_BN_P638 && ECC_BN_P638 == YES
   comma
   {TPM_ECC_BN_P638,
   638,
   {TPM_ALG_NULL,TPM_ALG_NULL},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &BN_P638}
#   undef comma
#   define comma ,
#endif // ECC_BN_P638
#if defined ECC_SM2_P256 && ECC_SM2_P256 == YES
   comma
   {TPM_ECC_SM2_P256,
   256,
   {TPM_ALG_KDF1_SP800_56A,TPM_ALG_SM3_256},
   {TPM_ALG_NULL,TPM_ALG_NULL},
   &SM2_P256}
#   undef comma
#   define comma ,
#endif // ECC_SM2_P256
};
const UINT16    ECC_CURVE_COUNT = sizeof(eccCurves) / sizeof(ECC_CURVE);
