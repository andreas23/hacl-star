#include "Hacl_Symmetric_HSalsa20.h"

uint32_t Hacl_Symmetric_HSalsa20_rotate(uint32_t a, uint32_t s)
{
  return a << s | a >> (uint32_t )32 - s;
}

uint32_t Hacl_Symmetric_HSalsa20_load32_le(uint8_t *k)
{
  uint8_t k0 = k[0];
  uint8_t k1 = k[1];
  uint8_t k2 = k[2];
  uint8_t k3 = k[3];
  return
    (uint32_t )k0
    | (uint32_t )k1 << (uint32_t )8
    | (uint32_t )k2 << (uint32_t )16
    | (uint32_t )k3 << (uint32_t )24;
}

void Hacl_Symmetric_HSalsa20_store32_le(uint8_t *k, uint32_t x)
{
  k[0] = (uint8_t )x;
  k[1] = (uint8_t )(x >> (uint32_t )8);
  k[2] = (uint8_t )(x >> (uint32_t )16);
  k[3] = (uint8_t )(x >> (uint32_t )24);
}

void
Hacl_Symmetric_HSalsa20_crypto_core_hsalsa20(uint8_t *output, uint8_t *input, uint8_t *key)
{
  uint32_t x00 = (uint32_t )0x61707865;
  uint32_t x50 = (uint32_t )0x3320646e;
  uint32_t x100 = (uint32_t )0x79622d32;
  uint32_t x150 = (uint32_t )0x6b206574;
  uint32_t x16 = Hacl_Symmetric_HSalsa20_load32_le(key);
  uint32_t x20 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )4);
  uint32_t x30 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )8);
  uint32_t x40 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )12);
  uint32_t x110 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )16);
  uint32_t x120 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )20);
  uint32_t x130 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )24);
  uint32_t x140 = Hacl_Symmetric_HSalsa20_load32_le(key + (uint32_t )28);
  uint32_t x60 = Hacl_Symmetric_HSalsa20_load32_le(input);
  uint32_t x70 = Hacl_Symmetric_HSalsa20_load32_le(input + (uint32_t )4);
  uint32_t x80 = Hacl_Symmetric_HSalsa20_load32_le(input + (uint32_t )8);
  uint32_t x90 = Hacl_Symmetric_HSalsa20_load32_le(input + (uint32_t )12);
  uint32_t x41 = x40 ^ Hacl_Symmetric_HSalsa20_rotate(x00 + x120, (uint32_t )7);
  uint32_t x81 = x80 ^ Hacl_Symmetric_HSalsa20_rotate(x41 + x00, (uint32_t )9);
  uint32_t x121 = x120 ^ Hacl_Symmetric_HSalsa20_rotate(x81 + x41, (uint32_t )13);
  uint32_t x01 = x00 ^ Hacl_Symmetric_HSalsa20_rotate(x121 + x81, (uint32_t )18);
  uint32_t x91 = x90 ^ Hacl_Symmetric_HSalsa20_rotate(x50 + x16, (uint32_t )7);
  uint32_t x131 = x130 ^ Hacl_Symmetric_HSalsa20_rotate(x91 + x50, (uint32_t )9);
  uint32_t x17 = x16 ^ Hacl_Symmetric_HSalsa20_rotate(x131 + x91, (uint32_t )13);
  uint32_t x51 = x50 ^ Hacl_Symmetric_HSalsa20_rotate(x17 + x131, (uint32_t )18);
  uint32_t x141 = x140 ^ Hacl_Symmetric_HSalsa20_rotate(x100 + x60, (uint32_t )7);
  uint32_t x21 = x20 ^ Hacl_Symmetric_HSalsa20_rotate(x141 + x100, (uint32_t )9);
  uint32_t x61 = x60 ^ Hacl_Symmetric_HSalsa20_rotate(x21 + x141, (uint32_t )13);
  uint32_t x101 = x100 ^ Hacl_Symmetric_HSalsa20_rotate(x61 + x21, (uint32_t )18);
  uint32_t x31 = x30 ^ Hacl_Symmetric_HSalsa20_rotate(x150 + x110, (uint32_t )7);
  uint32_t x71 = x70 ^ Hacl_Symmetric_HSalsa20_rotate(x31 + x150, (uint32_t )9);
  uint32_t x111 = x110 ^ Hacl_Symmetric_HSalsa20_rotate(x71 + x31, (uint32_t )13);
  uint32_t x151 = x150 ^ Hacl_Symmetric_HSalsa20_rotate(x111 + x71, (uint32_t )18);
  uint32_t x18 = x17 ^ Hacl_Symmetric_HSalsa20_rotate(x01 + x31, (uint32_t )7);
  uint32_t x22 = x21 ^ Hacl_Symmetric_HSalsa20_rotate(x18 + x01, (uint32_t )9);
  uint32_t x32 = x31 ^ Hacl_Symmetric_HSalsa20_rotate(x22 + x18, (uint32_t )13);
  uint32_t x02 = x01 ^ Hacl_Symmetric_HSalsa20_rotate(x32 + x22, (uint32_t )18);
  uint32_t x62 = x61 ^ Hacl_Symmetric_HSalsa20_rotate(x51 + x41, (uint32_t )7);
  uint32_t x72 = x71 ^ Hacl_Symmetric_HSalsa20_rotate(x62 + x51, (uint32_t )9);
  uint32_t x42 = x41 ^ Hacl_Symmetric_HSalsa20_rotate(x72 + x62, (uint32_t )13);
  uint32_t x52 = x51 ^ Hacl_Symmetric_HSalsa20_rotate(x42 + x72, (uint32_t )18);
  uint32_t x112 = x111 ^ Hacl_Symmetric_HSalsa20_rotate(x101 + x91, (uint32_t )7);
  uint32_t x82 = x81 ^ Hacl_Symmetric_HSalsa20_rotate(x112 + x101, (uint32_t )9);
  uint32_t x92 = x91 ^ Hacl_Symmetric_HSalsa20_rotate(x82 + x112, (uint32_t )13);
  uint32_t x102 = x101 ^ Hacl_Symmetric_HSalsa20_rotate(x92 + x82, (uint32_t )18);
  uint32_t x122 = x121 ^ Hacl_Symmetric_HSalsa20_rotate(x151 + x141, (uint32_t )7);
  uint32_t x132 = x131 ^ Hacl_Symmetric_HSalsa20_rotate(x122 + x151, (uint32_t )9);
  uint32_t x142 = x141 ^ Hacl_Symmetric_HSalsa20_rotate(x132 + x122, (uint32_t )13);
  uint32_t x152 = x151 ^ Hacl_Symmetric_HSalsa20_rotate(x142 + x132, (uint32_t )18);
  uint32_t x43 = x42 ^ Hacl_Symmetric_HSalsa20_rotate(x02 + x122, (uint32_t )7);
  uint32_t x83 = x82 ^ Hacl_Symmetric_HSalsa20_rotate(x43 + x02, (uint32_t )9);
  uint32_t x123 = x122 ^ Hacl_Symmetric_HSalsa20_rotate(x83 + x43, (uint32_t )13);
  uint32_t x03 = x02 ^ Hacl_Symmetric_HSalsa20_rotate(x123 + x83, (uint32_t )18);
  uint32_t x93 = x92 ^ Hacl_Symmetric_HSalsa20_rotate(x52 + x18, (uint32_t )7);
  uint32_t x133 = x132 ^ Hacl_Symmetric_HSalsa20_rotate(x93 + x52, (uint32_t )9);
  uint32_t x19 = x18 ^ Hacl_Symmetric_HSalsa20_rotate(x133 + x93, (uint32_t )13);
  uint32_t x53 = x52 ^ Hacl_Symmetric_HSalsa20_rotate(x19 + x133, (uint32_t )18);
  uint32_t x143 = x142 ^ Hacl_Symmetric_HSalsa20_rotate(x102 + x62, (uint32_t )7);
  uint32_t x23 = x22 ^ Hacl_Symmetric_HSalsa20_rotate(x143 + x102, (uint32_t )9);
  uint32_t x63 = x62 ^ Hacl_Symmetric_HSalsa20_rotate(x23 + x143, (uint32_t )13);
  uint32_t x103 = x102 ^ Hacl_Symmetric_HSalsa20_rotate(x63 + x23, (uint32_t )18);
  uint32_t x33 = x32 ^ Hacl_Symmetric_HSalsa20_rotate(x152 + x112, (uint32_t )7);
  uint32_t x73 = x72 ^ Hacl_Symmetric_HSalsa20_rotate(x33 + x152, (uint32_t )9);
  uint32_t x113 = x112 ^ Hacl_Symmetric_HSalsa20_rotate(x73 + x33, (uint32_t )13);
  uint32_t x153 = x152 ^ Hacl_Symmetric_HSalsa20_rotate(x113 + x73, (uint32_t )18);
  uint32_t x114 = x19 ^ Hacl_Symmetric_HSalsa20_rotate(x03 + x33, (uint32_t )7);
  uint32_t x24 = x23 ^ Hacl_Symmetric_HSalsa20_rotate(x114 + x03, (uint32_t )9);
  uint32_t x34 = x33 ^ Hacl_Symmetric_HSalsa20_rotate(x24 + x114, (uint32_t )13);
  uint32_t x04 = x03 ^ Hacl_Symmetric_HSalsa20_rotate(x34 + x24, (uint32_t )18);
  uint32_t x64 = x63 ^ Hacl_Symmetric_HSalsa20_rotate(x53 + x43, (uint32_t )7);
  uint32_t x74 = x73 ^ Hacl_Symmetric_HSalsa20_rotate(x64 + x53, (uint32_t )9);
  uint32_t x44 = x43 ^ Hacl_Symmetric_HSalsa20_rotate(x74 + x64, (uint32_t )13);
  uint32_t x54 = x53 ^ Hacl_Symmetric_HSalsa20_rotate(x44 + x74, (uint32_t )18);
  uint32_t x115 = x113 ^ Hacl_Symmetric_HSalsa20_rotate(x103 + x93, (uint32_t )7);
  uint32_t x84 = x83 ^ Hacl_Symmetric_HSalsa20_rotate(x115 + x103, (uint32_t )9);
  uint32_t x94 = x93 ^ Hacl_Symmetric_HSalsa20_rotate(x84 + x115, (uint32_t )13);
  uint32_t x104 = x103 ^ Hacl_Symmetric_HSalsa20_rotate(x94 + x84, (uint32_t )18);
  uint32_t x124 = x123 ^ Hacl_Symmetric_HSalsa20_rotate(x153 + x143, (uint32_t )7);
  uint32_t x134 = x133 ^ Hacl_Symmetric_HSalsa20_rotate(x124 + x153, (uint32_t )9);
  uint32_t x144 = x143 ^ Hacl_Symmetric_HSalsa20_rotate(x134 + x124, (uint32_t )13);
  uint32_t x154 = x153 ^ Hacl_Symmetric_HSalsa20_rotate(x144 + x134, (uint32_t )18);
  uint32_t x45 = x44 ^ Hacl_Symmetric_HSalsa20_rotate(x04 + x124, (uint32_t )7);
  uint32_t x85 = x84 ^ Hacl_Symmetric_HSalsa20_rotate(x45 + x04, (uint32_t )9);
  uint32_t x125 = x124 ^ Hacl_Symmetric_HSalsa20_rotate(x85 + x45, (uint32_t )13);
  uint32_t x05 = x04 ^ Hacl_Symmetric_HSalsa20_rotate(x125 + x85, (uint32_t )18);
  uint32_t x95 = x94 ^ Hacl_Symmetric_HSalsa20_rotate(x54 + x114, (uint32_t )7);
  uint32_t x135 = x134 ^ Hacl_Symmetric_HSalsa20_rotate(x95 + x54, (uint32_t )9);
  uint32_t x116 = x114 ^ Hacl_Symmetric_HSalsa20_rotate(x135 + x95, (uint32_t )13);
  uint32_t x55 = x54 ^ Hacl_Symmetric_HSalsa20_rotate(x116 + x135, (uint32_t )18);
  uint32_t x145 = x144 ^ Hacl_Symmetric_HSalsa20_rotate(x104 + x64, (uint32_t )7);
  uint32_t x25 = x24 ^ Hacl_Symmetric_HSalsa20_rotate(x145 + x104, (uint32_t )9);
  uint32_t x65 = x64 ^ Hacl_Symmetric_HSalsa20_rotate(x25 + x145, (uint32_t )13);
  uint32_t x105 = x104 ^ Hacl_Symmetric_HSalsa20_rotate(x65 + x25, (uint32_t )18);
  uint32_t x35 = x34 ^ Hacl_Symmetric_HSalsa20_rotate(x154 + x115, (uint32_t )7);
  uint32_t x75 = x74 ^ Hacl_Symmetric_HSalsa20_rotate(x35 + x154, (uint32_t )9);
  uint32_t x117 = x115 ^ Hacl_Symmetric_HSalsa20_rotate(x75 + x35, (uint32_t )13);
  uint32_t x155 = x154 ^ Hacl_Symmetric_HSalsa20_rotate(x117 + x75, (uint32_t )18);
  uint32_t x118 = x116 ^ Hacl_Symmetric_HSalsa20_rotate(x05 + x35, (uint32_t )7);
  uint32_t x26 = x25 ^ Hacl_Symmetric_HSalsa20_rotate(x118 + x05, (uint32_t )9);
  uint32_t x36 = x35 ^ Hacl_Symmetric_HSalsa20_rotate(x26 + x118, (uint32_t )13);
  uint32_t x06 = x05 ^ Hacl_Symmetric_HSalsa20_rotate(x36 + x26, (uint32_t )18);
  uint32_t x66 = x65 ^ Hacl_Symmetric_HSalsa20_rotate(x55 + x45, (uint32_t )7);
  uint32_t x76 = x75 ^ Hacl_Symmetric_HSalsa20_rotate(x66 + x55, (uint32_t )9);
  uint32_t x46 = x45 ^ Hacl_Symmetric_HSalsa20_rotate(x76 + x66, (uint32_t )13);
  uint32_t x56 = x55 ^ Hacl_Symmetric_HSalsa20_rotate(x46 + x76, (uint32_t )18);
  uint32_t x119 = x117 ^ Hacl_Symmetric_HSalsa20_rotate(x105 + x95, (uint32_t )7);
  uint32_t x86 = x85 ^ Hacl_Symmetric_HSalsa20_rotate(x119 + x105, (uint32_t )9);
  uint32_t x96 = x95 ^ Hacl_Symmetric_HSalsa20_rotate(x86 + x119, (uint32_t )13);
  uint32_t x106 = x105 ^ Hacl_Symmetric_HSalsa20_rotate(x96 + x86, (uint32_t )18);
  uint32_t x126 = x125 ^ Hacl_Symmetric_HSalsa20_rotate(x155 + x145, (uint32_t )7);
  uint32_t x136 = x135 ^ Hacl_Symmetric_HSalsa20_rotate(x126 + x155, (uint32_t )9);
  uint32_t x146 = x145 ^ Hacl_Symmetric_HSalsa20_rotate(x136 + x126, (uint32_t )13);
  uint32_t x156 = x155 ^ Hacl_Symmetric_HSalsa20_rotate(x146 + x136, (uint32_t )18);
  uint32_t x47 = x46 ^ Hacl_Symmetric_HSalsa20_rotate(x06 + x126, (uint32_t )7);
  uint32_t x87 = x86 ^ Hacl_Symmetric_HSalsa20_rotate(x47 + x06, (uint32_t )9);
  uint32_t x127 = x126 ^ Hacl_Symmetric_HSalsa20_rotate(x87 + x47, (uint32_t )13);
  uint32_t x07 = x06 ^ Hacl_Symmetric_HSalsa20_rotate(x127 + x87, (uint32_t )18);
  uint32_t x97 = x96 ^ Hacl_Symmetric_HSalsa20_rotate(x56 + x118, (uint32_t )7);
  uint32_t x137 = x136 ^ Hacl_Symmetric_HSalsa20_rotate(x97 + x56, (uint32_t )9);
  uint32_t x128 = x118 ^ Hacl_Symmetric_HSalsa20_rotate(x137 + x97, (uint32_t )13);
  uint32_t x57 = x56 ^ Hacl_Symmetric_HSalsa20_rotate(x128 + x137, (uint32_t )18);
  uint32_t x147 = x146 ^ Hacl_Symmetric_HSalsa20_rotate(x106 + x66, (uint32_t )7);
  uint32_t x27 = x26 ^ Hacl_Symmetric_HSalsa20_rotate(x147 + x106, (uint32_t )9);
  uint32_t x67 = x66 ^ Hacl_Symmetric_HSalsa20_rotate(x27 + x147, (uint32_t )13);
  uint32_t x107 = x106 ^ Hacl_Symmetric_HSalsa20_rotate(x67 + x27, (uint32_t )18);
  uint32_t x37 = x36 ^ Hacl_Symmetric_HSalsa20_rotate(x156 + x119, (uint32_t )7);
  uint32_t x77 = x76 ^ Hacl_Symmetric_HSalsa20_rotate(x37 + x156, (uint32_t )9);
  uint32_t x1110 = x119 ^ Hacl_Symmetric_HSalsa20_rotate(x77 + x37, (uint32_t )13);
  uint32_t x157 = x156 ^ Hacl_Symmetric_HSalsa20_rotate(x1110 + x77, (uint32_t )18);
  uint32_t x129 = x128 ^ Hacl_Symmetric_HSalsa20_rotate(x07 + x37, (uint32_t )7);
  uint32_t x28 = x27 ^ Hacl_Symmetric_HSalsa20_rotate(x129 + x07, (uint32_t )9);
  uint32_t x38 = x37 ^ Hacl_Symmetric_HSalsa20_rotate(x28 + x129, (uint32_t )13);
  uint32_t x08 = x07 ^ Hacl_Symmetric_HSalsa20_rotate(x38 + x28, (uint32_t )18);
  uint32_t x68 = x67 ^ Hacl_Symmetric_HSalsa20_rotate(x57 + x47, (uint32_t )7);
  uint32_t x78 = x77 ^ Hacl_Symmetric_HSalsa20_rotate(x68 + x57, (uint32_t )9);
  uint32_t x48 = x47 ^ Hacl_Symmetric_HSalsa20_rotate(x78 + x68, (uint32_t )13);
  uint32_t x58 = x57 ^ Hacl_Symmetric_HSalsa20_rotate(x48 + x78, (uint32_t )18);
  uint32_t x1111 = x1110 ^ Hacl_Symmetric_HSalsa20_rotate(x107 + x97, (uint32_t )7);
  uint32_t x88 = x87 ^ Hacl_Symmetric_HSalsa20_rotate(x1111 + x107, (uint32_t )9);
  uint32_t x98 = x97 ^ Hacl_Symmetric_HSalsa20_rotate(x88 + x1111, (uint32_t )13);
  uint32_t x108 = x107 ^ Hacl_Symmetric_HSalsa20_rotate(x98 + x88, (uint32_t )18);
  uint32_t x1210 = x127 ^ Hacl_Symmetric_HSalsa20_rotate(x157 + x147, (uint32_t )7);
  uint32_t x138 = x137 ^ Hacl_Symmetric_HSalsa20_rotate(x1210 + x157, (uint32_t )9);
  uint32_t x148 = x147 ^ Hacl_Symmetric_HSalsa20_rotate(x138 + x1210, (uint32_t )13);
  uint32_t x158 = x157 ^ Hacl_Symmetric_HSalsa20_rotate(x148 + x138, (uint32_t )18);
  uint32_t x49 = x48 ^ Hacl_Symmetric_HSalsa20_rotate(x08 + x1210, (uint32_t )7);
  uint32_t x89 = x88 ^ Hacl_Symmetric_HSalsa20_rotate(x49 + x08, (uint32_t )9);
  uint32_t x1211 = x1210 ^ Hacl_Symmetric_HSalsa20_rotate(x89 + x49, (uint32_t )13);
  uint32_t x09 = x08 ^ Hacl_Symmetric_HSalsa20_rotate(x1211 + x89, (uint32_t )18);
  uint32_t x99 = x98 ^ Hacl_Symmetric_HSalsa20_rotate(x58 + x129, (uint32_t )7);
  uint32_t x139 = x138 ^ Hacl_Symmetric_HSalsa20_rotate(x99 + x58, (uint32_t )9);
  uint32_t x149 = x129 ^ Hacl_Symmetric_HSalsa20_rotate(x139 + x99, (uint32_t )13);
  uint32_t x59 = x58 ^ Hacl_Symmetric_HSalsa20_rotate(x149 + x139, (uint32_t )18);
  uint32_t x1410 = x148 ^ Hacl_Symmetric_HSalsa20_rotate(x108 + x68, (uint32_t )7);
  uint32_t x29 = x28 ^ Hacl_Symmetric_HSalsa20_rotate(x1410 + x108, (uint32_t )9);
  uint32_t x69 = x68 ^ Hacl_Symmetric_HSalsa20_rotate(x29 + x1410, (uint32_t )13);
  uint32_t x109 = x108 ^ Hacl_Symmetric_HSalsa20_rotate(x69 + x29, (uint32_t )18);
  uint32_t x39 = x38 ^ Hacl_Symmetric_HSalsa20_rotate(x158 + x1111, (uint32_t )7);
  uint32_t x79 = x78 ^ Hacl_Symmetric_HSalsa20_rotate(x39 + x158, (uint32_t )9);
  uint32_t x1112 = x1111 ^ Hacl_Symmetric_HSalsa20_rotate(x79 + x39, (uint32_t )13);
  uint32_t x159 = x158 ^ Hacl_Symmetric_HSalsa20_rotate(x1112 + x79, (uint32_t )18);
  uint32_t x160 = x149 ^ Hacl_Symmetric_HSalsa20_rotate(x09 + x39, (uint32_t )7);
  uint32_t x210 = x29 ^ Hacl_Symmetric_HSalsa20_rotate(x160 + x09, (uint32_t )9);
  uint32_t x310 = x39 ^ Hacl_Symmetric_HSalsa20_rotate(x210 + x160, (uint32_t )13);
  uint32_t x010 = x09 ^ Hacl_Symmetric_HSalsa20_rotate(x310 + x210, (uint32_t )18);
  uint32_t x610 = x69 ^ Hacl_Symmetric_HSalsa20_rotate(x59 + x49, (uint32_t )7);
  uint32_t x710 = x79 ^ Hacl_Symmetric_HSalsa20_rotate(x610 + x59, (uint32_t )9);
  uint32_t x410 = x49 ^ Hacl_Symmetric_HSalsa20_rotate(x710 + x610, (uint32_t )13);
  uint32_t x510 = x59 ^ Hacl_Symmetric_HSalsa20_rotate(x410 + x710, (uint32_t )18);
  uint32_t x1113 = x1112 ^ Hacl_Symmetric_HSalsa20_rotate(x109 + x99, (uint32_t )7);
  uint32_t x810 = x89 ^ Hacl_Symmetric_HSalsa20_rotate(x1113 + x109, (uint32_t )9);
  uint32_t x910 = x99 ^ Hacl_Symmetric_HSalsa20_rotate(x810 + x1113, (uint32_t )13);
  uint32_t x1010 = x109 ^ Hacl_Symmetric_HSalsa20_rotate(x910 + x810, (uint32_t )18);
  uint32_t x1212 = x1211 ^ Hacl_Symmetric_HSalsa20_rotate(x159 + x1410, (uint32_t )7);
  uint32_t x1310 = x139 ^ Hacl_Symmetric_HSalsa20_rotate(x1212 + x159, (uint32_t )9);
  uint32_t x1411 = x1410 ^ Hacl_Symmetric_HSalsa20_rotate(x1310 + x1212, (uint32_t )13);
  uint32_t x1510 = x159 ^ Hacl_Symmetric_HSalsa20_rotate(x1411 + x1310, (uint32_t )18);
  uint32_t x411 = x410 ^ Hacl_Symmetric_HSalsa20_rotate(x010 + x1212, (uint32_t )7);
  uint32_t x811 = x810 ^ Hacl_Symmetric_HSalsa20_rotate(x411 + x010, (uint32_t )9);
  uint32_t x1213 = x1212 ^ Hacl_Symmetric_HSalsa20_rotate(x811 + x411, (uint32_t )13);
  uint32_t x011 = x010 ^ Hacl_Symmetric_HSalsa20_rotate(x1213 + x811, (uint32_t )18);
  uint32_t x911 = x910 ^ Hacl_Symmetric_HSalsa20_rotate(x510 + x160, (uint32_t )7);
  uint32_t x1311 = x1310 ^ Hacl_Symmetric_HSalsa20_rotate(x911 + x510, (uint32_t )9);
  uint32_t x161 = x160 ^ Hacl_Symmetric_HSalsa20_rotate(x1311 + x911, (uint32_t )13);
  uint32_t x511 = x510 ^ Hacl_Symmetric_HSalsa20_rotate(x161 + x1311, (uint32_t )18);
  uint32_t x1412 = x1411 ^ Hacl_Symmetric_HSalsa20_rotate(x1010 + x610, (uint32_t )7);
  uint32_t x211 = x210 ^ Hacl_Symmetric_HSalsa20_rotate(x1412 + x1010, (uint32_t )9);
  uint32_t x611 = x610 ^ Hacl_Symmetric_HSalsa20_rotate(x211 + x1412, (uint32_t )13);
  uint32_t x1011 = x1010 ^ Hacl_Symmetric_HSalsa20_rotate(x611 + x211, (uint32_t )18);
  uint32_t x311 = x310 ^ Hacl_Symmetric_HSalsa20_rotate(x1510 + x1113, (uint32_t )7);
  uint32_t x711 = x710 ^ Hacl_Symmetric_HSalsa20_rotate(x311 + x1510, (uint32_t )9);
  uint32_t x1114 = x1113 ^ Hacl_Symmetric_HSalsa20_rotate(x711 + x311, (uint32_t )13);
  uint32_t x1511 = x1510 ^ Hacl_Symmetric_HSalsa20_rotate(x1114 + x711, (uint32_t )18);
  uint32_t x162 = x161 ^ Hacl_Symmetric_HSalsa20_rotate(x011 + x311, (uint32_t )7);
  uint32_t x212 = x211 ^ Hacl_Symmetric_HSalsa20_rotate(x162 + x011, (uint32_t )9);
  uint32_t x312 = x311 ^ Hacl_Symmetric_HSalsa20_rotate(x212 + x162, (uint32_t )13);
  uint32_t x012 = x011 ^ Hacl_Symmetric_HSalsa20_rotate(x312 + x212, (uint32_t )18);
  uint32_t x612 = x611 ^ Hacl_Symmetric_HSalsa20_rotate(x511 + x411, (uint32_t )7);
  uint32_t x712 = x711 ^ Hacl_Symmetric_HSalsa20_rotate(x612 + x511, (uint32_t )9);
  uint32_t x412 = x411 ^ Hacl_Symmetric_HSalsa20_rotate(x712 + x612, (uint32_t )13);
  uint32_t x512 = x511 ^ Hacl_Symmetric_HSalsa20_rotate(x412 + x712, (uint32_t )18);
  uint32_t x1115 = x1114 ^ Hacl_Symmetric_HSalsa20_rotate(x1011 + x911, (uint32_t )7);
  uint32_t x812 = x811 ^ Hacl_Symmetric_HSalsa20_rotate(x1115 + x1011, (uint32_t )9);
  uint32_t x912 = x911 ^ Hacl_Symmetric_HSalsa20_rotate(x812 + x1115, (uint32_t )13);
  uint32_t x1012 = x1011 ^ Hacl_Symmetric_HSalsa20_rotate(x912 + x812, (uint32_t )18);
  uint32_t x1214 = x1213 ^ Hacl_Symmetric_HSalsa20_rotate(x1511 + x1412, (uint32_t )7);
  uint32_t x1312 = x1311 ^ Hacl_Symmetric_HSalsa20_rotate(x1214 + x1511, (uint32_t )9);
  uint32_t x1413 = x1412 ^ Hacl_Symmetric_HSalsa20_rotate(x1312 + x1214, (uint32_t )13);
  uint32_t x1512 = x1511 ^ Hacl_Symmetric_HSalsa20_rotate(x1413 + x1312, (uint32_t )18);
  uint32_t x413 = x412 ^ Hacl_Symmetric_HSalsa20_rotate(x012 + x1214, (uint32_t )7);
  uint32_t x813 = x812 ^ Hacl_Symmetric_HSalsa20_rotate(x413 + x012, (uint32_t )9);
  uint32_t x1215 = x1214 ^ Hacl_Symmetric_HSalsa20_rotate(x813 + x413, (uint32_t )13);
  uint32_t x013 = x012 ^ Hacl_Symmetric_HSalsa20_rotate(x1215 + x813, (uint32_t )18);
  uint32_t x913 = x912 ^ Hacl_Symmetric_HSalsa20_rotate(x512 + x162, (uint32_t )7);
  uint32_t x1313 = x1312 ^ Hacl_Symmetric_HSalsa20_rotate(x913 + x512, (uint32_t )9);
  uint32_t x163 = x162 ^ Hacl_Symmetric_HSalsa20_rotate(x1313 + x913, (uint32_t )13);
  uint32_t x513 = x512 ^ Hacl_Symmetric_HSalsa20_rotate(x163 + x1313, (uint32_t )18);
  uint32_t x1414 = x1413 ^ Hacl_Symmetric_HSalsa20_rotate(x1012 + x612, (uint32_t )7);
  uint32_t x213 = x212 ^ Hacl_Symmetric_HSalsa20_rotate(x1414 + x1012, (uint32_t )9);
  uint32_t x613 = x612 ^ Hacl_Symmetric_HSalsa20_rotate(x213 + x1414, (uint32_t )13);
  uint32_t x1013 = x1012 ^ Hacl_Symmetric_HSalsa20_rotate(x613 + x213, (uint32_t )18);
  uint32_t x313 = x312 ^ Hacl_Symmetric_HSalsa20_rotate(x1512 + x1115, (uint32_t )7);
  uint32_t x713 = x712 ^ Hacl_Symmetric_HSalsa20_rotate(x313 + x1512, (uint32_t )9);
  uint32_t x1116 = x1115 ^ Hacl_Symmetric_HSalsa20_rotate(x713 + x313, (uint32_t )13);
  uint32_t x1513 = x1512 ^ Hacl_Symmetric_HSalsa20_rotate(x1116 + x713, (uint32_t )18);
  uint32_t x164 = x163 ^ Hacl_Symmetric_HSalsa20_rotate(x013 + x313, (uint32_t )7);
  uint32_t x214 = x213 ^ Hacl_Symmetric_HSalsa20_rotate(x164 + x013, (uint32_t )9);
  uint32_t x314 = x313 ^ Hacl_Symmetric_HSalsa20_rotate(x214 + x164, (uint32_t )13);
  uint32_t x014 = x013 ^ Hacl_Symmetric_HSalsa20_rotate(x314 + x214, (uint32_t )18);
  uint32_t x614 = x613 ^ Hacl_Symmetric_HSalsa20_rotate(x513 + x413, (uint32_t )7);
  uint32_t x714 = x713 ^ Hacl_Symmetric_HSalsa20_rotate(x614 + x513, (uint32_t )9);
  uint32_t x414 = x413 ^ Hacl_Symmetric_HSalsa20_rotate(x714 + x614, (uint32_t )13);
  uint32_t x514 = x513 ^ Hacl_Symmetric_HSalsa20_rotate(x414 + x714, (uint32_t )18);
  uint32_t x1117 = x1116 ^ Hacl_Symmetric_HSalsa20_rotate(x1013 + x913, (uint32_t )7);
  uint32_t x814 = x813 ^ Hacl_Symmetric_HSalsa20_rotate(x1117 + x1013, (uint32_t )9);
  uint32_t x914 = x913 ^ Hacl_Symmetric_HSalsa20_rotate(x814 + x1117, (uint32_t )13);
  uint32_t x1014 = x1013 ^ Hacl_Symmetric_HSalsa20_rotate(x914 + x814, (uint32_t )18);
  uint32_t x1216 = x1215 ^ Hacl_Symmetric_HSalsa20_rotate(x1513 + x1414, (uint32_t )7);
  uint32_t x1314 = x1313 ^ Hacl_Symmetric_HSalsa20_rotate(x1216 + x1513, (uint32_t )9);
  uint32_t x1415 = x1414 ^ Hacl_Symmetric_HSalsa20_rotate(x1314 + x1216, (uint32_t )13);
  uint32_t x1514 = x1513 ^ Hacl_Symmetric_HSalsa20_rotate(x1415 + x1314, (uint32_t )18);
  uint32_t x415 = x414 ^ Hacl_Symmetric_HSalsa20_rotate(x014 + x1216, (uint32_t )7);
  uint32_t x815 = x814 ^ Hacl_Symmetric_HSalsa20_rotate(x415 + x014, (uint32_t )9);
  uint32_t x1217 = x1216 ^ Hacl_Symmetric_HSalsa20_rotate(x815 + x415, (uint32_t )13);
  uint32_t x015 = x014 ^ Hacl_Symmetric_HSalsa20_rotate(x1217 + x815, (uint32_t )18);
  uint32_t x915 = x914 ^ Hacl_Symmetric_HSalsa20_rotate(x514 + x164, (uint32_t )7);
  uint32_t x1315 = x1314 ^ Hacl_Symmetric_HSalsa20_rotate(x915 + x514, (uint32_t )9);
  uint32_t x165 = x164 ^ Hacl_Symmetric_HSalsa20_rotate(x1315 + x915, (uint32_t )13);
  uint32_t x515 = x514 ^ Hacl_Symmetric_HSalsa20_rotate(x165 + x1315, (uint32_t )18);
  uint32_t x1416 = x1415 ^ Hacl_Symmetric_HSalsa20_rotate(x1014 + x614, (uint32_t )7);
  uint32_t x215 = x214 ^ Hacl_Symmetric_HSalsa20_rotate(x1416 + x1014, (uint32_t )9);
  uint32_t x615 = x614 ^ Hacl_Symmetric_HSalsa20_rotate(x215 + x1416, (uint32_t )13);
  uint32_t x1015 = x1014 ^ Hacl_Symmetric_HSalsa20_rotate(x615 + x215, (uint32_t )18);
  uint32_t x315 = x314 ^ Hacl_Symmetric_HSalsa20_rotate(x1514 + x1117, (uint32_t )7);
  uint32_t x715 = x714 ^ Hacl_Symmetric_HSalsa20_rotate(x315 + x1514, (uint32_t )9);
  uint32_t x1118 = x1117 ^ Hacl_Symmetric_HSalsa20_rotate(x715 + x315, (uint32_t )13);
  uint32_t x1515 = x1514 ^ Hacl_Symmetric_HSalsa20_rotate(x1118 + x715, (uint32_t )18);
  uint32_t x166 = x165 ^ Hacl_Symmetric_HSalsa20_rotate(x015 + x315, (uint32_t )7);
  uint32_t x216 = x215 ^ Hacl_Symmetric_HSalsa20_rotate(x166 + x015, (uint32_t )9);
  uint32_t x316 = x315 ^ Hacl_Symmetric_HSalsa20_rotate(x216 + x166, (uint32_t )13);
  uint32_t x016 = x015 ^ Hacl_Symmetric_HSalsa20_rotate(x316 + x216, (uint32_t )18);
  uint32_t x616 = x615 ^ Hacl_Symmetric_HSalsa20_rotate(x515 + x415, (uint32_t )7);
  uint32_t x716 = x715 ^ Hacl_Symmetric_HSalsa20_rotate(x616 + x515, (uint32_t )9);
  uint32_t x416 = x415 ^ Hacl_Symmetric_HSalsa20_rotate(x716 + x616, (uint32_t )13);
  uint32_t x516 = x515 ^ Hacl_Symmetric_HSalsa20_rotate(x416 + x716, (uint32_t )18);
  uint32_t x1119 = x1118 ^ Hacl_Symmetric_HSalsa20_rotate(x1015 + x915, (uint32_t )7);
  uint32_t x816 = x815 ^ Hacl_Symmetric_HSalsa20_rotate(x1119 + x1015, (uint32_t )9);
  uint32_t x916 = x915 ^ Hacl_Symmetric_HSalsa20_rotate(x816 + x1119, (uint32_t )13);
  uint32_t x1016 = x1015 ^ Hacl_Symmetric_HSalsa20_rotate(x916 + x816, (uint32_t )18);
  uint32_t x1218 = x1217 ^ Hacl_Symmetric_HSalsa20_rotate(x1515 + x1416, (uint32_t )7);
  uint32_t x1316 = x1315 ^ Hacl_Symmetric_HSalsa20_rotate(x1218 + x1515, (uint32_t )9);
  uint32_t x1417 = x1416 ^ Hacl_Symmetric_HSalsa20_rotate(x1316 + x1218, (uint32_t )13);
  uint32_t x1516 = x1515 ^ Hacl_Symmetric_HSalsa20_rotate(x1417 + x1316, (uint32_t )18);
  uint32_t x417 = x416 ^ Hacl_Symmetric_HSalsa20_rotate(x016 + x1218, (uint32_t )7);
  uint32_t x817 = x816 ^ Hacl_Symmetric_HSalsa20_rotate(x417 + x016, (uint32_t )9);
  uint32_t x1219 = x1218 ^ Hacl_Symmetric_HSalsa20_rotate(x817 + x417, (uint32_t )13);
  uint32_t x017 = x016 ^ Hacl_Symmetric_HSalsa20_rotate(x1219 + x817, (uint32_t )18);
  uint32_t x917 = x916 ^ Hacl_Symmetric_HSalsa20_rotate(x516 + x166, (uint32_t )7);
  uint32_t x1317 = x1316 ^ Hacl_Symmetric_HSalsa20_rotate(x917 + x516, (uint32_t )9);
  uint32_t x167 = x166 ^ Hacl_Symmetric_HSalsa20_rotate(x1317 + x917, (uint32_t )13);
  uint32_t x517 = x516 ^ Hacl_Symmetric_HSalsa20_rotate(x167 + x1317, (uint32_t )18);
  uint32_t x1418 = x1417 ^ Hacl_Symmetric_HSalsa20_rotate(x1016 + x616, (uint32_t )7);
  uint32_t x217 = x216 ^ Hacl_Symmetric_HSalsa20_rotate(x1418 + x1016, (uint32_t )9);
  uint32_t x617 = x616 ^ Hacl_Symmetric_HSalsa20_rotate(x217 + x1418, (uint32_t )13);
  uint32_t x1017 = x1016 ^ Hacl_Symmetric_HSalsa20_rotate(x617 + x217, (uint32_t )18);
  uint32_t x317 = x316 ^ Hacl_Symmetric_HSalsa20_rotate(x1516 + x1119, (uint32_t )7);
  uint32_t x717 = x716 ^ Hacl_Symmetric_HSalsa20_rotate(x317 + x1516, (uint32_t )9);
  uint32_t x1120 = x1119 ^ Hacl_Symmetric_HSalsa20_rotate(x717 + x317, (uint32_t )13);
  uint32_t x1517 = x1516 ^ Hacl_Symmetric_HSalsa20_rotate(x1120 + x717, (uint32_t )18);
  uint32_t x168 = x167 ^ Hacl_Symmetric_HSalsa20_rotate(x017 + x317, (uint32_t )7);
  uint32_t x218 = x217 ^ Hacl_Symmetric_HSalsa20_rotate(x168 + x017, (uint32_t )9);
  uint32_t x318 = x317 ^ Hacl_Symmetric_HSalsa20_rotate(x218 + x168, (uint32_t )13);
  uint32_t x018 = x017 ^ Hacl_Symmetric_HSalsa20_rotate(x318 + x218, (uint32_t )18);
  uint32_t x618 = x617 ^ Hacl_Symmetric_HSalsa20_rotate(x517 + x417, (uint32_t )7);
  uint32_t x718 = x717 ^ Hacl_Symmetric_HSalsa20_rotate(x618 + x517, (uint32_t )9);
  uint32_t x418 = x417 ^ Hacl_Symmetric_HSalsa20_rotate(x718 + x618, (uint32_t )13);
  uint32_t x518 = x517 ^ Hacl_Symmetric_HSalsa20_rotate(x418 + x718, (uint32_t )18);
  uint32_t x1121 = x1120 ^ Hacl_Symmetric_HSalsa20_rotate(x1017 + x917, (uint32_t )7);
  uint32_t x818 = x817 ^ Hacl_Symmetric_HSalsa20_rotate(x1121 + x1017, (uint32_t )9);
  uint32_t x918 = x917 ^ Hacl_Symmetric_HSalsa20_rotate(x818 + x1121, (uint32_t )13);
  uint32_t x1018 = x1017 ^ Hacl_Symmetric_HSalsa20_rotate(x918 + x818, (uint32_t )18);
  uint32_t x1220 = x1219 ^ Hacl_Symmetric_HSalsa20_rotate(x1517 + x1418, (uint32_t )7);
  uint32_t x1318 = x1317 ^ Hacl_Symmetric_HSalsa20_rotate(x1220 + x1517, (uint32_t )9);
  uint32_t x1419 = x1418 ^ Hacl_Symmetric_HSalsa20_rotate(x1318 + x1220, (uint32_t )13);
  uint32_t x1518 = x1517 ^ Hacl_Symmetric_HSalsa20_rotate(x1419 + x1318, (uint32_t )18);
  uint32_t x419 = x418 ^ Hacl_Symmetric_HSalsa20_rotate(x018 + x1220, (uint32_t )7);
  uint32_t x819 = x818 ^ Hacl_Symmetric_HSalsa20_rotate(x419 + x018, (uint32_t )9);
  uint32_t x1221 = x1220 ^ Hacl_Symmetric_HSalsa20_rotate(x819 + x419, (uint32_t )13);
  uint32_t x0 = x018 ^ Hacl_Symmetric_HSalsa20_rotate(x1221 + x819, (uint32_t )18);
  uint32_t x919 = x918 ^ Hacl_Symmetric_HSalsa20_rotate(x518 + x168, (uint32_t )7);
  uint32_t x1319 = x1318 ^ Hacl_Symmetric_HSalsa20_rotate(x919 + x518, (uint32_t )9);
  uint32_t x169 = x168 ^ Hacl_Symmetric_HSalsa20_rotate(x1319 + x919, (uint32_t )13);
  uint32_t x5 = x518 ^ Hacl_Symmetric_HSalsa20_rotate(x169 + x1319, (uint32_t )18);
  uint32_t x1420 = x1419 ^ Hacl_Symmetric_HSalsa20_rotate(x1018 + x618, (uint32_t )7);
  uint32_t x219 = x218 ^ Hacl_Symmetric_HSalsa20_rotate(x1420 + x1018, (uint32_t )9);
  uint32_t x619 = x618 ^ Hacl_Symmetric_HSalsa20_rotate(x219 + x1420, (uint32_t )13);
  uint32_t x1019 = x1018 ^ Hacl_Symmetric_HSalsa20_rotate(x619 + x219, (uint32_t )18);
  uint32_t x319 = x318 ^ Hacl_Symmetric_HSalsa20_rotate(x1518 + x1121, (uint32_t )7);
  uint32_t x719 = x718 ^ Hacl_Symmetric_HSalsa20_rotate(x319 + x1518, (uint32_t )9);
  uint32_t x1122 = x1121 ^ Hacl_Symmetric_HSalsa20_rotate(x719 + x319, (uint32_t )13);
  uint32_t x15 = x1518 ^ Hacl_Symmetric_HSalsa20_rotate(x1122 + x719, (uint32_t )18);
  uint32_t x1 = x169 ^ Hacl_Symmetric_HSalsa20_rotate(x0 + x319, (uint32_t )7);
  uint32_t x2 = x219 ^ Hacl_Symmetric_HSalsa20_rotate(x1 + x0, (uint32_t )9);
  uint32_t x3 = x319 ^ Hacl_Symmetric_HSalsa20_rotate(x2 + x1, (uint32_t )13);
  uint32_t x019 = x0 ^ Hacl_Symmetric_HSalsa20_rotate(x3 + x2, (uint32_t )18);
  uint32_t x6 = x619 ^ Hacl_Symmetric_HSalsa20_rotate(x5 + x419, (uint32_t )7);
  uint32_t x7 = x719 ^ Hacl_Symmetric_HSalsa20_rotate(x6 + x5, (uint32_t )9);
  uint32_t x4 = x419 ^ Hacl_Symmetric_HSalsa20_rotate(x7 + x6, (uint32_t )13);
  uint32_t x519 = x5 ^ Hacl_Symmetric_HSalsa20_rotate(x4 + x7, (uint32_t )18);
  uint32_t x11 = x1122 ^ Hacl_Symmetric_HSalsa20_rotate(x1019 + x919, (uint32_t )7);
  uint32_t x8 = x819 ^ Hacl_Symmetric_HSalsa20_rotate(x11 + x1019, (uint32_t )9);
  uint32_t x9 = x919 ^ Hacl_Symmetric_HSalsa20_rotate(x8 + x11, (uint32_t )13);
  uint32_t x10 = x1019 ^ Hacl_Symmetric_HSalsa20_rotate(x9 + x8, (uint32_t )18);
  uint32_t x12 = x1221 ^ Hacl_Symmetric_HSalsa20_rotate(x15 + x1420, (uint32_t )7);
  uint32_t x13 = x1319 ^ Hacl_Symmetric_HSalsa20_rotate(x12 + x15, (uint32_t )9);
  uint32_t x14 = x1420 ^ Hacl_Symmetric_HSalsa20_rotate(x13 + x12, (uint32_t )13);
  uint32_t x1519 = x15 ^ Hacl_Symmetric_HSalsa20_rotate(x14 + x13, (uint32_t )18);
  Hacl_Symmetric_HSalsa20_store32_le(output, x019);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )4, x519);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )8, x10);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )12, x1519);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )16, x6);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )20, x7);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )24, x8);
  Hacl_Symmetric_HSalsa20_store32_le(output + (uint32_t )28, x9);
  return;
}
