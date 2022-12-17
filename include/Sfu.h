#pragma once

#include <stdint.h>
#include <assert.h>
#include <math.h>

#define GPUASSERT(a, info) assert(a)

#define SFU_INS_NUMB       7

#define SFU_RCP_IDX_NUMB   128
#define SFU_LOG_IDX_NUMB   64
#define SFU_EXP_IDX_NUMB   32
#define SFU_SIN_IDX_NUMB   32
#define SFU_RANK_NUMB      3

const uint64_t sqrt_table_list[SFU_RCP_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x000ff808,	0x03fc06, 0x0001fa},
    {0x002fb8d5,	0x03f435, 0x0001ef},
    {0x004f3bd0,	0x03ec91, 0x0001e3},
    {0x006e825e,	0x03e519, 0x0001d9},
    {0x008d8dd4,	0x03ddcb, 0x0001ce},
    {0x00ac5f7c,	0x03d6a6, 0x0001c4},
    {0x00caf896,	0x03cfa7, 0x0001bb},
    {0x00e95a54,	0x03c8ce, 0x0001b2},
    {0x010785dd,	0x03c21a, 0x0001a9},
    {0x01257c52,	0x03bb89, 0x0001a0},
    {0x01433ec4,	0x03b51a, 0x000198},
    {0x0160ce41,	0x03aecb, 0x000190},
    {0x017e2bca,	0x03a89c, 0x000188},
    {0x019b585a,	0x03a28c, 0x000180},
    {0x01b854e1,	0x039c9a, 0x000179},
    {0x01d5224b,	0x0396c5, 0x000172},
    {0x01f1c17a,	0x03910b, 0x00016b},
    {0x020e334a,	0x038b6d, 0x000164},
    {0x022a7890,	0x0385e9, 0x00015e},
    {0x0246921b,	0x03807e, 0x000158},
    {0x026280b3,	0x037b2c, 0x000151},
    {0x027e451c,	0x0375f2, 0x00014c},
    {0x0299e011,	0x0370cf, 0x000146},
    {0x02b5524b,	0x036bc3, 0x000140},
    {0x02d09c7b,	0x0366cd, 0x00013b},
    {0x02ebbf50,	0x0361ec, 0x000136},
    {0x0306bb70,	0x035d20, 0x000130},
    {0x03219181,	0x035868, 0x00012c},
    {0x033c4221,	0x0353c3, 0x000127},
    {0x0356cdec,	0x034f32, 0x000122},
    {0x03713578,	0x034ab4, 0x00011d},
    {0x038b7958,	0x034647, 0x000119},
    {0x03a59a1b,	0x0341ec, 0x000115},
    {0x03bf984d,	0x033da3, 0x000110},
    {0x03d97475,	0x03396a, 0x00010c},
    {0x03f32f18,	0x033541, 0x000108},
    {0x040cc8b7,	0x033129, 0x000104},
    {0x042641cf,	0x032d20, 0x000100},
    {0x043f9adc,	0x032926, 0x0000fd},
    {0x0458d455,	0x03253b, 0x0000f9},
    {0x0471eeaf,	0x03215e, 0x0000f5},
    {0x048aea5d,	0x031d90, 0x0000f2},
    {0x04a3c7cd,	0x0319cf, 0x0000ef},
    {0x04bc876c,	0x03161b, 0x0000eb},
    {0x04d529a4,	0x031275, 0x0000e8},
    {0x04edaede,	0x030edc, 0x0000e5},
    {0x0506177f,	0x030b4f, 0x0000e2},
    {0x051e63ea,	0x0307ce, 0x0000df},
    {0x05369480,	0x030459, 0x0000dc},
    {0x054ea9a0,	0x0300f0, 0x0000d9},
    {0x0566a3a6,	0x02fd93, 0x0000d6},
    {0x057e82ed,	0x02fa41, 0x0000d3},
    {0x059647ce,	0x02f6f9, 0x0000d0},
    {0x05adf2a0,	0x02f3bd, 0x0000ce},
    {0x05c583b7,	0x02f08b, 0x0000cb},
    {0x05dcfb67,	0x02ed63, 0x0000c9},
    {0x05f45a02,	0x02ea45, 0x0000c6},
    {0x060b9fd7,	0x02e731, 0x0000c4},
    {0x0622cd33,	0x02e427, 0x0000c1},
    {0x0639e265,	0x02e127, 0x0000bf},
    {0x0650dfb7,	0x02de2f, 0x0000bd},
    {0x0667c572,	0x02db41, 0x0000ba},
    {0x067e93de,	0x02d85c, 0x0000b8},
    {0x06954b42,	0x02d57f, 0x0000b6},
    {0x06b733c0,	0x02d144, 0x0000b3},
    {0x06e41b9c,	0x02cbbd, 0x0000af},
    {0x0710ac0b,	0x02c656, 0x0000ab},
    {0x073ce705,	0x02c10e, 0x0000a7},
    {0x0768ce6d,	0x02bbe4, 0x0000a3},
    {0x07946417,	0x02b6d6, 0x0000a0},
    {0x07bfa9c4,	0x02b1e4, 0x00009d},
    {0x07eaa127,	0x02ad0d, 0x000099},
    {0x08154be2,	0x02a84f, 0x000096},
    {0x083fab8b,	0x02a3aa, 0x000093},
    {0x0869c1a8,	0x029f1d, 0x000090},
    {0x08938fb3,	0x029aa8, 0x00008d},
    {0x08bd171a,	0x029649, 0x00008b},
    {0x08e6593d,	0x0291ff, 0x000088},
    {0x090f5774,	0x028dcb, 0x000085},
    {0x09381309,	0x0289ab, 0x000083},
    {0x09608d3c,	0x02859f, 0x000080},
    {0x0988c746,	0x0281a6, 0x00007e},
    {0x09b0c253,	0x027dbf, 0x00007c},
    {0x09d87f88,	0x0279ea, 0x000079},
    {0x0a000000,	0x027627, 0x000077},
    {0x0a2744cf,	0x027275, 0x000075},
    {0x0a4e4eff,	0x026ed4, 0x000073},
    {0x0a751f94,	0x026b42, 0x000071},
    {0x0a9bb78b,	0x0267c0, 0x00006f},
    {0x0ac217d8,	0x02644c, 0x00006d},
    {0x0ae84169,	0x0260e8, 0x00006c},
    {0x0b0e3527,	0x025d92, 0x00006a},
    {0x0b33f3f1,	0x025a4a, 0x000068},
    {0x0b597ea4,	0x02570f, 0x000067},
    {0x0b7ed616,	0x0253e1, 0x000065},
    {0x0ba3fb14,	0x0250c1, 0x000063},
    {0x0bc8ee6b,	0x024dac, 0x000062},
    {0x0bedb0df,	0x024aa4, 0x000060},
    {0x0c124330,	0x0247a8, 0x00005f},
    {0x0c36a619,	0x0244b7, 0x00005d},
    {0x0c5ada51,	0x0241d2, 0x00005c},
    {0x0c7ee08a,	0x023ef7, 0x00005b},
    {0x0ca2b971,	0x023c27, 0x000059},
    {0x0cc665b0,	0x023962, 0x000058},
    {0x0ce9e5ec,	0x0236a7, 0x000057},
    {0x0d0d3ac7,	0x0233f6, 0x000056},
    {0x0d3064dd,	0x02314e, 0x000054},
    {0x0d5364c9,	0x022eb1, 0x000053},
    {0x0d763b21,	0x022c1c, 0x000052},
    {0x0d98e878,	0x022990, 0x000051},
    {0x0dbb6d5d,	0x02270e, 0x000050},
    {0x0dddca5d,	0x022494, 0x00004f},
    {0x0e000000,	0x022222, 0x00004e},
    {0x0e220ecd,	0x021fb9, 0x00004d},
    {0x0e43f747,	0x021d58, 0x00004c},
    {0x0e65b9ee,	0x021afe, 0x00004b},
    {0x0e87573f,	0x0218ad, 0x00004a},
    {0x0ea8cfb6,	0x021663, 0x000049},
    {0x0eca23cb,	0x021421, 0x000048},
    {0x0eeb53f2,	0x0211e5, 0x000047},
    {0x0f0c60a0,	0x020fb1, 0x000046},
    {0x0f2d4a45,	0x020d84, 0x000045},
    {0x0f4e1150,	0x020b5e, 0x000044},
    {0x0f6eb62d,	0x02093f, 0x000044},
    {0x0f8f3946,	0x020726, 0x000043},
    {0x0faf9b03,	0x020513, 0x000042},
    {0x0fcfdbca,	0x020307, 0x000041},
    {0x0feffbfe,	0x020101, 0x000040},
};

const uint64_t exp_table_list[SFU_EXP_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x08164d1f, 0x0166c3, 0x0003e3},
    {0x0843a28c, 0x016e9e, 0x0003f8},
    {0x0871f619, 0x0176a5, 0x00040f},
    {0x08a14d57, 0x017ed9, 0x000425},
    {0x08d1adf6, 0x01873b, 0x00043d},
    {0x09031dc4, 0x018fcc, 0x000454},
    {0x0935a2b3, 0x01988e, 0x00046d},
    {0x096942d3, 0x01a180, 0x000486},
    {0x099e0459, 0x01aaa4, 0x00049f},
    {0x09d3ed9a, 0x01b3fc, 0x0004b9},
    {0x0a0b0511, 0x01bd88, 0x0004d3},
    {0x0a43515b, 0x01c749, 0x0004ee},
    {0x0a7cd93b, 0x01d141, 0x00050a},
    {0x0ab7a39b, 0x01db72, 0x000526},
    {0x0af3b78b, 0x01e5db, 0x000543},
    {0x0b311c41, 0x01f07e, 0x000561},
    {0x0b6fd91e, 0x01fb5d, 0x00057f},
    {0x0baff5ab, 0x02067a, 0x00059e},
    {0x0bf1799b, 0x0211d4, 0x0005bd},
    {0x0c346cce, 0x021d6e, 0x0005dd},
    {0x0c78d74d, 0x022949, 0x0005fe},
    {0x0cbec150, 0x023567, 0x000620},
    {0x0d06333e, 0x0241c8, 0x000642},
    {0x0d4f35ab, 0x024e6f, 0x000665},
    {0x0d99d15c, 0x025b5d, 0x000689},
    {0x0de60f48, 0x026893, 0x0006ae},
    {0x0e33f897, 0x027613, 0x0006d3},
    {0x0e8396a5, 0x0283df, 0x0006f9},
    {0x0ed4f302, 0x0291f9, 0x000720},
    {0x0f281774, 0x02a061, 0x000748},
    {0x0f7d0df7, 0x02af1a, 0x000771},
    {0x0fd3e0c1, 0x02be26, 0x00079b},
};

const uint64_t rsq_table_list[SFU_RCP_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x0ff017d8, 0x03f425, 0x0005e2},
    {0x0fd0d3de, 0x03dd0e, 0x0005aa},
    {0x0fb2451d, 0x03c6d4, 0x000574},
    {0x0f9464da, 0x03b16c, 0x000541},
    {0x0f772caf, 0x039ccb, 0x000510},
    {0x0f5a968c, 0x0388e8, 0x0004e2},
    {0x0f3e9cac, 0x0375b8, 0x0004b6},
    {0x0f233994, 0x036334, 0x00048c},
    {0x0f08680c, 0x035153, 0x000465},
    {0x0eee231b, 0x03400c, 0x00043f},
    {0x0ed46607, 0x032f5a, 0x00041b},
    {0x0ebb2c4c, 0x031f35, 0x0003f8},
    {0x0ea2719a, 0x030f96, 0x0003d7},
    {0x0e8a31d6, 0x030078, 0x0003b8},
    {0x0e726913, 0x02f1d5, 0x00039a},
    {0x0e5b138e, 0x02e3a7, 0x00037d},
    {0x0e442db2, 0x02d5e9, 0x000362},
    {0x0e2db40e, 0x02c898, 0x000347},
    {0x0e17a358, 0x02bbad, 0x00032e},
    {0x0e01f86a, 0x02af25, 0x000316},
    {0x0decb03f, 0x02a2fb, 0x0002ff},
    {0x0dd7c7f1, 0x02972d, 0x0002e9},
    {0x0dc33cb8, 0x028bb5, 0x0002d3},
    {0x0daf0beb, 0x028091, 0x0002bf},
    {0x0d9b32f8, 0x0275be, 0x0002ab},
    {0x0d87af6b, 0x026b37, 0x000298},
    {0x0d747ee5, 0x0260fb, 0x000286},
    {0x0d619f21, 0x025706, 0x000274},
    {0x0d4f0ded, 0x024d56, 0x000264},
    {0x0d3cc930, 0x0243e8, 0x000253},
    {0x0d2acee1, 0x023aba, 0x000244},
    {0x0d191d0c, 0x0231c9, 0x000235},
    {0x0d07b1cf, 0x022913, 0x000226},
    {0x0cf68b5b, 0x022097, 0x000218},
    {0x0ce5a7ee, 0x021851, 0x00020b},
    {0x0cd505d9, 0x021040, 0x0001fe},
    {0x0cc4a37b, 0x020863, 0x0001f1},
    {0x0cb47f40, 0x0200b7, 0x0001e5},
    {0x0ca497a4, 0x01f93b, 0x0001d9},
    {0x0c94eb2f, 0x01f1ed, 0x0001ce},
    {0x0c857875, 0x01eacc, 0x0001c3},
    {0x0c763e19, 0x01e3d5, 0x0001b8},
    {0x0c673ac5, 0x01dd09, 0x0001ae},
    {0x0c586d33, 0x01d665, 0x0001a4},
    {0x0c49d424, 0x01cfe8, 0x00019a},
    {0x0c3b6e64, 0x01c991, 0x000191},
    {0x0c2d3ac9, 0x01c35e, 0x000188},
    {0x0c1f3834, 0x01bd4f, 0x00017f},
    {0x0c11658c, 0x01b763, 0x000177},
    {0x0c03c1c3, 0x01b197, 0x00016f},
    {0x0bf64bd2, 0x01abec, 0x000167},
    {0x0be902bb, 0x01a661, 0x00015f},
    {0x0bdbe586, 0x01a0f3, 0x000158},
    {0x0bcef344, 0x019ba4, 0x000150},
    {0x0bc22b0d, 0x019671, 0x000149},
    {0x0bb58c00, 0x019159, 0x000142},
    {0x0ba91540, 0x018c5d, 0x00013c},
    {0x0b9cc5f9, 0x01877b, 0x000135},
    {0x0b909d5d, 0x0182b2, 0x00012f},
    {0x0b849aa2, 0x017e02, 0x000129},
    {0x0b78bd07, 0x01796a, 0x000123},
    {0x0b6d03cc, 0x0174ea, 0x00011d},
    {0x0b616e3a, 0x017080, 0x000118},
    {0x0b55fb9d, 0x016c2c, 0x000112},
    {0x0b450fc0, 0x0165d9, 0x00010a},
    {0x0b2ef415, 0x015daf, 0x000100},
    {0x0b195890, 0x0155d3, 0x0000f7},
    {0x0b04386d, 0x014e42, 0x0000ee},
    {0x0aef8f26, 0x0146f7, 0x0000e5},
    {0x0adb5872, 0x013fef, 0x0000dd},
    {0x0ac7903c, 0x013926, 0x0000d5},
    {0x0ab432a4, 0x01329a, 0x0000ce},
    {0x0aa13bfa, 0x012c48, 0x0000c7},
    {0x0a8ea8ba, 0x01262c, 0x0000c0},
    {0x0a7c758b, 0x012045, 0x0000ba},
    {0x0a6a9f3d, 0x011a90, 0x0000b4},
    {0x0a5922c3, 0x01150a, 0x0000ae},
    {0x0a47fd35, 0x010fb2, 0x0000a8},
    {0x0a372bcd, 0x010a85, 0x0000a3},
    {0x0a26abe3, 0x010582, 0x00009e},
    {0x0a167aed, 0x0100a6, 0x000099},
    {0x0a06967d, 0x00fbf0, 0x000094},
    {0x09f6fc3f, 0x00f75f, 0x000090},
    {0x09e7a9fa, 0x00f2f1, 0x00008c},
    {0x09d89d8a, 0x00eea4, 0x000088},
    {0x09c9d4e3, 0x00ea78, 0x000084},
    {0x09bb4e0e, 0x00e66a, 0x000080},
    {0x09ad0729, 0x00e279, 0x00007c},
    {0x099efe63, 0x00dea6, 0x000079},
    {0x09913200, 0x00daed, 0x000075},
    {0x0983a052, 0x00d74f, 0x000072},
    {0x097647bf, 0x00d3c9, 0x00006f},
    {0x096926ba, 0x00d05d, 0x00006c},
    {0x095c3bc5, 0x00cd07, 0x000069},
    {0x094f8572, 0x00c9c8, 0x000066},
    {0x0943025f, 0x00c69f, 0x000064},
    {0x0936b137, 0x00c38b, 0x000061},
    {0x092a90b2, 0x00c08b, 0x00005f},
    {0x091e9f93, 0x00bd9e, 0x00005c},
    {0x0912dca8, 0x00bac4, 0x00005a},
    {0x090746ca, 0x00b7fc, 0x000058},
    {0x08fbdcdc, 0x00b546, 0x000056},
    {0x08f09dcc, 0x00b2a0, 0x000054},
    {0x08e58890, 0x00b00b, 0x000052},
    {0x08da9c26, 0x00ad86, 0x000050},
    {0x08cfd797, 0x00ab10, 0x00004e},
    {0x08c539f3, 0x00a8a8, 0x00004c},
    {0x08bac251, 0x00a64f, 0x00004a},
    {0x08b06fd1, 0x00a404, 0x000049},
    {0x08a64199, 0x00a1c6, 0x000047},
    {0x089c36d7, 0x009f95, 0x000045},
    {0x08924ebe, 0x009d71, 0x000044},
    {0x08888889, 0x009b59, 0x000042},
    {0x087ee378, 0x00994c, 0x000041},
    {0x08755ed2, 0x00974b, 0x00003f},
    {0x086bf9e3, 0x009555, 0x00003e},
    {0x0862b3fb, 0x00936a, 0x00003d},
    {0x08598c73, 0x009189, 0x00003b},
    {0x085082a5, 0x008fb3, 0x00003a},
    {0x084795f2, 0x008de6, 0x000039},
    {0x083ec5be, 0x008c23, 0x000038},
    {0x08361174, 0x008a69, 0x000037},
    {0x082d7882, 0x0088b8, 0x000036},
    {0x0824fa58, 0x00870f, 0x000034},
    {0x081c966f, 0x008570, 0x000033},
    {0x08144c3e, 0x0083d8, 0x000032},
    {0x080c1b44, 0x008249, 0x000031},
    {0x08040303, 0x0080c1, 0x000030},
};

const uint64_t log_table_list[SFU_LOG_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x05bf9431, 0x02dcf2, 0x0005af},
    {0x088e68ec, 0x02d1c1, 0x000582},
    {0x07137eaf, 0x02c6e7, 0x000558},
    {0x09d517ef, 0x02bc5e, 0x000530},
    {0x0646285c, 0x02b225, 0x00050a},
    {0x079cbb05, 0x02a837, 0x0004e5},
    {0x08ee68cc, 0x029e91, 0x0004c2},
    {0x0a3b54fd, 0x029530, 0x0004a0},
    {0x05c1d0b5, 0x028c11, 0x00047f},
    {0x0663b742, 0x028332, 0x000460},
    {0x07036db4, 0x027a90, 0x000442},
    {0x07a102fa, 0x027228, 0x000426},
    {0x083c856e, 0x0269f8, 0x00040a},
    {0x08d602d9, 0x0261ff, 0x0003ef},
    {0x096d887e, 0x025a3a, 0x0003d6},
    {0x0a03231e, 0x0252a6, 0x0003bd},
    {0x054b6f7f, 0x024b43, 0x0003a6},
    {0x059463f9, 0x02440f, 0x00038f},
    {0x05dc74af, 0x023d07, 0x000379},
    {0x0623a71d, 0x02362a, 0x000364},
    {0x066a008e, 0x022f77, 0x00034f},
    {0x06af861e, 0x0228eb, 0x00033c},
    {0x06f43cbb, 0x022287, 0x000329},
    {0x07382925, 0x021c48, 0x000316},
    {0x077b4ff5, 0x02162d, 0x000305},
    {0x07bdb59d, 0x021035, 0x0002f3},
    {0x07ff5e67, 0x020a5f, 0x0002e3},
    {0x08404e79, 0x0204aa, 0x0002d3},
    {0x088089d9, 0x01ff14, 0x0002c3},
    {0x08c01468, 0x01f99c, 0x0002b4},
    {0x08fef1ea, 0x01f443, 0x0002a6},
    {0x093d2603, 0x01ef06, 0x000297},
    {0x06854bc5, 0x01e9e4, 0x00028a},
    {0x06486002, 0x01e4de, 0x00027d},
    {0x060c1364, 0x01dff2, 0x000270},
    {0x05d062b4, 0x01db1f, 0x000263},
    {0x05954ad2, 0x01d665, 0x000257},
    {0x055ac8ba, 0x01d1c2, 0x00024b},
    {0x0520d97a, 0x01cd37, 0x000240},
    {0x04e77a38, 0x01c8c2, 0x000235},
    {0x04aea831, 0x01c463, 0x00022a},
    {0x047660b2, 0x01c019, 0x000220},
    {0x043ea120, 0x01bbe4, 0x000216},
    {0x040766ef, 0x01b7c3, 0x00020c},
    {0x03d0afa8, 0x01b3b6, 0x000202},
    {0x039a78e2, 0x01afbb, 0x0001f9},
    {0x0364c049, 0x01abd3, 0x0001f0},
    {0x032f8396, 0x01a7fc, 0x0001e7},
    {0x05f58126, 0x01a438, 0x0001de},
    {0x058cea30, 0x01a084, 0x0001d6},
    {0x05253e19, 0x019ce1, 0x0001ce},
    {0x04be78cb, 0x01994d, 0x0001c6},
    {0x0458964c, 0x0195ca, 0x0001be},
    {0x03f392bb, 0x019256, 0x0001b6},
    {0x038f6a51, 0x018ef1, 0x0001af},
    {0x032c195f, 0x018b9a, 0x0001a8},
    {0x0593389b, 0x018852, 0x0001a1},
    {0x04cfdf37, 0x018517, 0x00019a},
    {0x040e1fbf, 0x0181ea, 0x000193},
    {0x034df387, 0x017eca, 0x00018d},
    {0x051ea81d, 0x017bb7, 0x000186},
    {0x03a475f9, 0x0178b0, 0x000180},
    {0x045a8878, 0x0175b6, 0x00017a},
    {0x02e41b38, 0x0172c8, 0x000174},
};

const uint64_t rcp_table_list[SFU_RCP_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x0ff00ff0, 0x03f80f, 0x0007e8},
    {0x0fd08e55, 0x03e86d, 0x0007ba},
    {0x0fb18856, 0x03d927, 0x00078d},
    {0x0f92fb22, 0x03ca3a, 0x000761},
    {0x0f74e3fc, 0x03bba3, 0x000736},
    {0x0f57403d, 0x03ad60, 0x00070d},
    {0x0f3a0d53, 0x039f6d, 0x0006e5},
    {0x0f1d48bd, 0x0391ca, 0x0006be},
    {0x0f00f00f, 0x038473, 0x000699},
    {0x0ee500ee, 0x037766, 0x000674},
    {0x0ec97912, 0x036aa1, 0x000651},
    {0x0eae5640, 0x035e23, 0x00062e},
    {0x0e939652, 0x0351e8, 0x00060d},
    {0x0e79372e, 0x0345f0, 0x0005ec},
    {0x0e5f36cb, 0x033a38, 0x0005cc},
    {0x0e45932d, 0x032ebe, 0x0005ad},
    {0x0e2c4a69, 0x032381, 0x000590},
    {0x0e135a9d, 0x03187f, 0x000572},
    {0x0dfac1f7, 0x030db7, 0x000556},
    {0x0de27eb3, 0x030327, 0x00053a},
    {0x0dca8f16, 0x02f8cd, 0x000520},
    {0x0db2f172, 0x02eea8, 0x000505},
    {0x0d9ba425, 0x02e4b7, 0x0004ec},
    {0x0d84a599, 0x02daf8, 0x0004d3},
    {0x0d6df440, 0x02d16a, 0x0004bb},
    {0x0d578e98, 0x02c80b, 0x0004a4},
    {0x0d417329, 0x02bedb, 0x00048d},
    {0x0d2ba084, 0x02b5d8, 0x000476},
    {0x0d161544, 0x02ad02, 0x000461},
    {0x0d00d00d, 0x02a456, 0x00044b},
    {0x0cebcf8c, 0x029bd4, 0x000437},
    {0x0cd71275, 0x02937b, 0x000422},
    {0x0cc29787, 0x028b4a, 0x00040f},
    {0x0cae5d86, 0x02833f, 0x0003fc},
    {0x0c9a6340, 0x027b5b, 0x0003e9},
    {0x0c86a789, 0x02739b, 0x0003d7},
    {0x0c73293d, 0x026c00, 0x0003c5},
    {0x0c5fe740, 0x026488, 0x0003b3},
    {0x0c4ce07b, 0x025d32, 0x0003a3},
    {0x0c3a13de, 0x0255fd, 0x000392},
    {0x0c278061, 0x024eea, 0x000382},
    {0x0c152501, 0x0247f6, 0x000372},
    {0x0c0300c0, 0x024121, 0x000363},
    {0x0bf112a9, 0x023a6b, 0x000353},
    {0x0bdf59c9, 0x0233d3, 0x000345},
    {0x0bcdd536, 0x022d58, 0x000336},
    {0x0bbc8409, 0x0226fa, 0x000328},
    {0x0bab6561, 0x0220b7, 0x00031b},
    {0x0b9a7863, 0x021a8f, 0x00030d},
    {0x0b89bc37, 0x021482, 0x000300},
    {0x0b79300b, 0x020e8f, 0x0002f3},
    {0x0b68d313, 0x0208b5, 0x0002e7},
    {0x0b58a485, 0x0202f4, 0x0002da},
    {0x0b48a39d, 0x01fd4b, 0x0002ce},
    {0x0b38cf9b, 0x01f7bb, 0x0002c3},
    {0x0b2927c3, 0x01f241, 0x0002b7},
    {0x0b19ab5c, 0x01ecde, 0x0002ac},
    {0x0b0a59b4, 0x01e791, 0x0002a1},
    {0x0afb321a, 0x01e25a, 0x000296},
    {0x0aec33e2, 0x01dd39, 0x00028c},
    {0x0add5e63, 0x01d82c, 0x000281},
    {0x0aceb0f9, 0x01d333, 0x000277},
    {0x0ac02b01, 0x01ce4f, 0x00026d},
    {0x0ab1cbdd, 0x01c97e, 0x000264},
    {0x0aa392f3, 0x01c4c1, 0x00025a},
    {0x0a957fab, 0x01c016, 0x000251},
    {0x0a879171, 0x01bb7d, 0x000248},
    {0x0a79c7b1, 0x01b6f7, 0x00023f},
    {0x0a6c21df, 0x01b282, 0x000236},
    {0x0a5e9f6f, 0x01ae1e, 0x00022e},
    {0x0a513fd7, 0x01a9cc, 0x000225},
    {0x0a440291, 0x01a58a, 0x00021d},
    {0x0a36e71a, 0x01a158, 0x000215},
    {0x0a29ecf1, 0x019d36, 0x00020d},
    {0x0a1d1398, 0x019924, 0x000205},
    {0x0a105a93, 0x019521, 0x0001fe},
    {0x0a03c169, 0x01912d, 0x0001f6},
    {0x09f747a1, 0x018d48, 0x0001ef},
    {0x09eaecc9, 0x018971, 0x0001e8},
    {0x09deb06d, 0x0185a9, 0x0001e1},
    {0x09d2921c, 0x0181ee, 0x0001da},
    {0x09c6916a, 0x017e41, 0x0001d3},
    {0x09baade9, 0x017aa2, 0x0001cc},
    {0x09aee730, 0x01770f, 0x0001c6},
    {0x09a33cd6, 0x01738a, 0x0001c0},
    {0x0997ae77, 0x017011, 0x0001b9},
    {0x098c3bac, 0x016ca4, 0x0001b3},
    {0x0980e415, 0x016944, 0x0001ad},
    {0x0975a751, 0x0165f0, 0x0001a7},
    {0x096a8501, 0x0162a7, 0x0001a1},
    {0x095f7cc7, 0x015f6a, 0x00019c},
    {0x09548e49, 0x015c38, 0x000196},
    {0x0949b92e, 0x015911, 0x000191},
    {0x093efd1c, 0x0155f6, 0x00018b},
    {0x093459be, 0x0152e4, 0x000186},
    {0x0929cebf, 0x014fde, 0x000181},
    {0x091f5bcc, 0x014ce1, 0x00017c},
    {0x09150091, 0x0149ef, 0x000177},
    {0x090abcc0, 0x014707, 0x000172},
    {0x09009009, 0x014429, 0x00016d},
    {0x08f67a1e, 0x014154, 0x000168},
    {0x08ec7ab4, 0x013e89, 0x000163},
    {0x08e2917e, 0x013bc7, 0x00015f},
    {0x08d8be34, 0x01390e, 0x00015a},
    {0x08cf008d, 0x01365e, 0x000156},
    {0x08c55842, 0x0133b7, 0x000151},
    {0x08bbc50d, 0x013118, 0x00014d},
    {0x08b246a8, 0x012e83, 0x000149},
    {0x08a8dcd2, 0x012bf5, 0x000145},
    {0x089f8747, 0x012970, 0x000141},
    {0x089645c5, 0x0126f3, 0x00013d},
    {0x088d180d, 0x01247d, 0x000139},
    {0x0883fddf, 0x012210, 0x000135},
    {0x087af6fd, 0x011faa, 0x000131},
    {0x0872032b, 0x011d4c, 0x00012d},
    {0x0869222b, 0x011af5, 0x000129},
    {0x086053c3, 0x0118a6, 0x000126},
    {0x085797b9, 0x01165e, 0x000122},
    {0x084eedd3, 0x01141d, 0x00011f},
    {0x084655da, 0x0111e3, 0x00011b},
    {0x083dcf95, 0x010fb0, 0x000118},
    {0x08355ace, 0x010d83, 0x000115},
    {0x082cf750, 0x010b5e, 0x000111},
    {0x0824a4e6, 0x01093e, 0x00010e},
    {0x081c635c, 0x010726, 0x00010b},
    {0x0814327e, 0x010513, 0x000108},
    {0x080c121b, 0x010307, 0x000105},
    {0x08040201, 0x010101, 0x000102},
};

const uint64_t sincos_table_list[SFU_SIN_IDX_NUMB][SFU_RANK_NUMB] =
{
    {0x00648558, 0x0323f2, 0x00001f},
    {0x012d5209, 0x032202, 0x00005d},
    {0x01f564e5, 0x031e24, 0x00009b},
    {0x02bc4288, 0x031859, 0x0000d8},
    {0x0381704d, 0x0310a6, 0x000115},
    {0x04447498, 0x03070e, 0x000151},
    {0x0504d725, 0x02fb99, 0x00018c},
    {0x05c2214c, 0x02ee4d, 0x0001c7},
    {0x067bde51, 0x02df32, 0x000200},
    {0x07319ba6, 0x02ce52, 0x000238},
    {0x07e2e936, 0x02bbb6, 0x00026f},
    {0x088f59aa, 0x02a76c, 0x0002a4},
    {0x093682a6, 0x02917e, 0x0002d7},
    {0x09d7fd14, 0x0279fa, 0x000309},
    {0x0a73655d, 0x0260f0, 0x000339},
    {0x0b085baa, 0x02466e, 0x000367},
    {0x0b96841b, 0x022a85, 0x000393},
    {0x0c1d8705, 0x020d46, 0x0003bd},
    {0x0c9d1124, 0x01eec3, 0x0003e4},
    {0x0d14d3cf, 0x01cf0f, 0x000409},
    {0x0d84852b, 0x01ae3d, 0x00042b},
    {0x0debe055, 0x018c62, 0x00044b},
    {0x0e4aa590, 0x016992, 0x000468},
    {0x0ea09a68, 0x0145e4, 0x000483},
    {0x0eed89da, 0x01216c, 0x00049b},
    {0x0f314475, 0x00fc42, 0x0004af},
    {0x0f6ba073, 0x00d67d, 0x0004c1},
    {0x0f9c79d5, 0x00b033, 0x0004d1},
    {0x0fc3b27c, 0x00897c, 0x0004dd},
    {0x0fe13237, 0x006271, 0x0004e6},
    {0x0ff4e6d5, 0x003b29, 0x0004ec},
    {0x0ffec42f, 0x0013bc, 0x0004ef},
};

class sfu_const_c {
public:
    static const uint32_t SFU_EXU_WIDTH = 16;
    static const uint32_t SFU_EXP_MAX = 255;
    static const uint32_t SFU_EXP_MIN = 0;
    static const uint32_t SFU_MAN_MAX = 0x7fffff;
    static const uint32_t SFU_MAN_MIN = 0;
    static const uint32_t SFU_DELTA_MASK = 0x1ffff;
    static const uint32_t SFU_EXP_EXP_MAX = 0xff;
    static const uint32_t SFU_EXP_127 = 0x7f;
    static const uint32_t SFU_OUT_MASK28 = 0xfffffff;
    static const uint32_t SFU_OUT_MASK29 = 0x1fffffff;
    static const uint32_t SFU_OUT_MASK30 = 0x3fffffff;
    static const uint32_t SPECIAL_FP_ONE = 0x3f800000;
    static const uint32_t SPECIAL_ZERO = 0;
    static const uint32_t RCP_EXP_MAX = 253;
    static const uint32_t EXP_EXP_MAX = 127 + 7;
    static const uint32_t EXP_EXP_MIN = 127 - 24;
    static const uint32_t SFU_SIGN_BIT = 0x80000000;
    static const uint32_t FLAG_Z_BIT = 30;
    static const uint32_t FLAG_INF_BIT = 29;
    static const uint32_t FLAG_NAN_BIT = 28;

    static const uint32_t DPU_SRC_NUMB1 = 1;
    static const uint32_t DPU_SRC_NUMB2 = 2;
    static const uint32_t DPU_SRC_NUMB3 = 3;
    static const uint32_t SIMD_LANE_NUMB = 32;
};

class special_ins_info
{
public:
    special_ins_info()
    {
        init();
    }

    special_ins_info(uint32_t sgn, uint32_t lg_exp_exp, uint32_t lg_exp_man, uint32_t res_exp, uint32_t sbit, uint32_t lz, uint32_t lz_idx)
    {
        m_sgn = sgn;
        m_lg_exp_exp = lg_exp_exp;
        m_lg_exp_man = lg_exp_man;
        m_res_exp = res_exp;
        m_sbit = sbit;
        m_lz = lz;
        m_lz_idx = lz_idx;

        m_lg_compute_res = 0ull;
        m_blg_int_res = false;
    }

    special_ins_info(uint32_t sgn, uint32_t lz)
    {
        m_sgn = sgn;
        m_lz = lz;
    }

    void init()
    {
        m_sgn = 0;
        m_lg_exp_exp = 0;
        m_lg_exp_man = 0;
        m_res_exp = 0;
        m_sbit = 0;
        m_lz = 0;
        m_lz_idx = 0;

        m_lg_compute_res = 0ull;
        m_blg_int_res = false;
    }

public:
    uint32_t m_sgn;
    uint32_t m_lg_exp_exp;
    uint32_t m_lg_exp_man;
    uint32_t m_res_exp;
    uint32_t m_sbit;
    uint32_t m_lz;
    uint32_t m_lz_idx;

    bool     m_blg_int_res;
    uint64_t m_lg_compute_res;
};


typedef enum
{
    SFU_RCP,
    SFU_RSQ,
    SFU_SQRT,
    SFU_LOG,
    SFU_EXP,
    SFU_SIN,
    SFU_COS,
} SFU_OP;

class Sfu
{
public:
    Sfu()
    {
        m_useSystemMath = false;
    }

    Sfu(bool useSystemMath)
    {
        m_useSystemMath = useSystemMath;
    }
    float rcp(float f);
    float rsq(float f);
    float sqrt(float f);
    float log(float f);
    float exp(float a, float b);
    float sin(float a);
    float cos(float a);

private:
    special_ins_info  m_special_dat;
    bool m_useSystemMath;

    uint32_t fp2fxcc(float input);


    uint32_t bf(const uint32_t a, const uint32_t msb, const uint32_t lsb)
    {
        return (a << (31 - msb)) >> (31 - msb + lsb);
    }

    uint64_t bf64(const uint64_t a, const uint32_t msb, const uint32_t lsb)
    {
        return (a << (63 - msb)) >> (63 - msb + lsb);
    }

    void extract_float_without_manhide(const uint32_t float_in, uint32_t& sgn, uint32_t& exp, uint32_t& man)
    {
        sgn = bf(float_in, 31, 31);
        exp = bf(float_in, 30, 23);
        man = bf(float_in, 22, 0);
    }

    bool is_float_dnm(const uint32_t float_in)
    {
        uint32_t sgn;
        uint32_t exp;
        uint32_t man;
        extract_float_without_manhide(float_in, sgn, exp, man);
        return ((exp == 0U) && (man != 0U));
    }

    // return true if the input float value is 0.
    bool is_float_zero(const uint32_t float_in)
    {
        uint32_t sgn;
        uint32_t exp;
        uint32_t man;
        extract_float_without_manhide(float_in, sgn, exp, man);
        return ((exp == 0U) && (man == 0U));
    }

    void extract_float(const uint32_t float_in, uint32_t& sgn, uint32_t& exp, uint32_t& man)
    {
        sgn = bf(float_in, 31, 31);
        exp = bf(float_in, 30, 23);
        man = (is_float_dnm(float_in) || is_float_zero(float_in)) ? bf(float_in, 22, 0) : ((1U << 23) | bf(float_in, 22, 0));
    }

    uint32_t compose_float(const uint32_t sgn, const uint32_t exp, const uint32_t man)
    {
        const uint32_t EXP_WTH = 8;
        const uint32_t MAN_WTH = 23;
        const uint32_t SGN_POS = EXP_WTH + MAN_WTH;
        GPUASSERT(sgn < 2, "sgn can be only 0 or 1");
        GPUASSERT(exp < (1 << EXP_WTH), "exp is 8bits can only be equal or less than 255");
        GPUASSERT(man < (1 << MAN_WTH), "man is 23bits");
        return (sgn << SGN_POS) | (exp << MAN_WTH) | man;
    }

    uint32_t get_specify_bit(uint32_t input, uint32_t width)
    {
        uint32_t input_sign = (input >> width) & 0x1;
        return input_sign;
    }

    void detail_process(const uint32_t& man, uint32_t& utable_idx, uint32_t& usbit, uint64_t& udelta, uint64_t& usquare, uint32_t manshiftbit, uint32_t delshiftbit)
    {
        utable_idx = man >> manshiftbit;
        usbit = get_specify_bit(man, manshiftbit - 1);
        udelta = (man << delshiftbit) & sfu_const_c::SFU_DELTA_MASK;
        udelta = usbit ? udelta : ((~udelta) & sfu_const_c::SFU_DELTA_MASK) + 1;
        usquare = ((udelta >> 3) * (udelta >> 3)) >> 15;
    }

    void finds_shift_lz(const uint32_t man, const int bit, const bool bassign, uint32_t special_bit, uint32_t compare)
    {
        uint32_t ushift = bassign ? (bit - 1) : bit;
        uint32_t ustart = bassign ? special_bit : 0;
        for (m_special_dat.m_lz = ustart; m_special_dat.m_lz < (uint32_t)bit; m_special_dat.m_lz++)
            if (((man >> (ushift - m_special_dat.m_lz)) & 0x1) == compare)
                break;

        if (!bassign)
            m_special_dat.m_lz_idx = m_special_dat.m_lz;
        else
            m_special_dat.m_lz_idx = special_bit;
    }

    void delta_idx_pre_process(const uint32_t& instr_op, const uint32_t& sgn, const uint32_t& exp, const uint32_t& man, uint32_t& utable_idx, uint32_t& usbit, uint64_t& udelta, uint64_t& usquare)
    {
        switch (instr_op)
        {
        case SFU_RCP:
            detail_process(man, utable_idx, usbit, udelta, usquare, 16, 2);
            break;
        case SFU_RSQ:
        case SFU_SQRT:
            detail_process(man, utable_idx, usbit, udelta, usquare, 17, 1);
            break;

        case SFU_LOG:
        {
            if (exp >= sfu_const_c::SFU_EXP_127)
            {
                m_special_dat.m_sgn = 0;
                m_special_dat.m_lg_exp_man = exp - sfu_const_c::SFU_EXP_127;
            }
            else
            {
                m_special_dat.m_sgn = 1;
                m_special_dat.m_lg_exp_man = sfu_const_c::SFU_EXP_127 - exp - 1;
            }

            while (m_special_dat.m_lg_exp_man >= pow(2, m_special_dat.m_lg_exp_exp) && m_special_dat.m_lg_exp_exp < 7)
            {
                m_special_dat.m_lg_exp_exp++;
            }

            if (man)
            {
                detail_process(man, utable_idx, usbit, udelta, usquare, 17, 1);
                m_special_dat.m_sbit = get_specify_bit(man, 22);

                if (m_special_dat.m_sbit)
                {
                    if (utable_idx == 0x3f)
                        finds_shift_lz(man, 23, true, 6, 0);
                    else
                        finds_shift_lz(utable_idx, 5, false, 0, 0);
                }
                else
                {
                    if (utable_idx == 0)
                        finds_shift_lz(man, 23, true, 6, 1);
                    else
                        finds_shift_lz(utable_idx, 5, false, 0, 1);
                }
            }
            else
            {
                m_special_dat.m_blg_int_res = true;
                m_special_dat.m_res_exp = sfu_const_c::SFU_EXP_127 - 1 + m_special_dat.m_lg_exp_exp;
                m_special_dat.m_lg_compute_res = uint64_t(m_special_dat.m_lg_exp_man) << (28 - m_special_dat.m_lg_exp_exp);
                if (m_special_dat.m_sgn)
                    m_special_dat.m_lg_compute_res |= (sfu_const_c::SFU_OUT_MASK28) >> m_special_dat.m_lg_exp_exp;
            }

        }
        break;
        case SFU_EXP:
        {
            uint32_t uman = man | (sfu_const_c::SFU_MAN_MAX + 1);
            if (exp >= sfu_const_c::SFU_EXP_127)
                uman <<= (exp - sfu_const_c::SFU_EXP_127);
            else
                uman >>= (sfu_const_c::SFU_EXP_127 - exp);

            m_special_dat.m_res_exp = sgn ? (((~uman + 1) >> 23) & 0x1ff) : (uman >> 23);
            uman = sgn ? (~uman + 1) & sfu_const_c::SFU_MAN_MAX : uman & sfu_const_c::SFU_MAN_MAX;

            detail_process(uman, utable_idx, usbit, udelta, usquare, 18, 0);
        }
        break;
        case SFU_SIN:
        case SFU_COS:
        {
            uint32_t srcsbit = 0;
            uint32_t src_bit = compose_float(sgn, exp, man) & sfu_const_c::SFU_OUT_MASK28;

            m_special_dat.m_sgn = src_bit >> 27;
            srcsbit = (src_bit >> 26) & 0x1;
            if (instr_op == SFU_COS)
            {
                m_special_dat.m_sgn = m_special_dat.m_sgn ^ srcsbit;
                srcsbit = 1 - srcsbit;
            }

            uint32_t src_26_man = srcsbit ? ((~src_bit) & 0x3ffffff) : (src_bit & 0x3ffffff);

            utable_idx = (src_26_man >> 21) & 0x1f;
            usbit = get_specify_bit(src_26_man, 20);
            udelta = (src_26_man >> 2) & 0x3ffff;
            udelta = usbit ? udelta : ((~udelta) & 0x3ffff);
            usquare = ((udelta >> 4) * (udelta >> 4)) >> 14;

            m_special_dat.m_lz = 26;
            while (src_26_man)
            {
                src_26_man >>= 1;
                m_special_dat.m_lz--;
            }
        }
        break;
        default:
            GPUASSERT(0, "error sfu instr op type");
        }
    }

    // look up tables
    void lookup_tables(const uint32_t& instr_op, const uint32_t& utable_idx, uint64_t table_value[3])
    {
        for (uint32_t uidx = 0; uidx < SFU_RANK_NUMB; uidx++)
        {
            switch (instr_op)
            {
            case SFU_RCP:
                table_value[uidx] = rcp_table_list[utable_idx][uidx];
                break;
            case SFU_RSQ:
                table_value[uidx] = rsq_table_list[utable_idx][uidx];
                break;
            case SFU_SQRT:
                table_value[uidx] = sqrt_table_list[utable_idx][uidx];
                break;
            case SFU_LOG:
                table_value[uidx] = log_table_list[utable_idx][uidx];
                break;
            case SFU_EXP:
                table_value[uidx] = exp_table_list[utable_idx][uidx];
                break;
            case SFU_SIN:
            case SFU_COS:
                table_value[uidx] = sincos_table_list[utable_idx][uidx];
                break;
            default:
                GPUASSERT(0, "error sfu instr op type");
            }
        }
    }

    uint64_t ext_specify_bit(uint64_t input_width, uint64_t bits)
    {
        return (1ull << (input_width + bits)) - 1ull;
    }

    uint64_t shift_specify_bit(uint64_t input, uint64_t bits, bool bnegative = false)
    {
        if (bnegative)
            return (~(input << bits) - 1ull);
        else
            return input << bits;
    }

    uint64_t get_sign_bit(uint64_t input, uint64_t input_width)
    {
        uint64_t input_sign = (input >> (input_width - 1)) & 0x1;
        return input_sign;
    }

    uint64_t get_negitive(const uint64_t udat)
    {
        return ((~udat) + 1ull);
    }

    void ext_padding(uint64_t input, uint64_t input_width, uint32_t ushift, uint64_t& input_sign, uint64_t& input_pad)
    {
        input_sign = get_sign_bit(input, input_width);

        if (input_sign)
            input_pad = ((0x3ull << input_width) | input) << ushift;
        else
            input_pad = input << ushift;
    }

    uint64_t compute_bit_mul(uint64_t input_0_width, uint64_t input_1, uint64_t input_1_width, uint64_t bitgrp)
    {
        uint64_t ext_1bit = ext_specify_bit(input_0_width, 1);
        uint64_t ext_2bit = ext_specify_bit(input_0_width, 2);

        uint64_t input_1_padded = 0ull;
        uint64_t input_1_sign = 0ull;
        ext_padding(input_1, input_1_width, 0, input_1_sign, input_1_padded);

        uint64_t bit_result = 0ull;
        if (input_1_sign)
        {
            switch (bitgrp)
            {
            case 1:
            case 2:
                bit_result = (shift_specify_bit(input_1_padded, 1) & ext_specify_bit(input_1_width, 3))
                    | shift_specify_bit(ext_2bit, input_1_width + 3);
                break;

            case 3:
                bit_result = (shift_specify_bit(input_1_padded, 2) & ext_specify_bit(input_1_width, 4))
                    | shift_specify_bit(ext_1bit, input_1_width + 4);
                break;

            case 4: bit_result = shift_specify_bit(input_1_padded, 2, true) & ext_specify_bit(input_1_width, 4); break;

            case 5:
            case 6: bit_result = shift_specify_bit(input_1_padded, 1, true) & ext_specify_bit(input_1_width, 3); break;

            case 0:
            case 7:
            default: bit_result = 0ull;  break;
            }
        }
        else
        {
            switch (bitgrp)
            {
            case 1:
            case 2: bit_result = shift_specify_bit(input_1_padded, 1); break;

            case 3: bit_result = shift_specify_bit(input_1_padded, 2); break;

            case 4:   // -4
                bit_result = (shift_specify_bit(input_1_padded, 2, true) & ext_specify_bit(input_1_width, 4))
                    | shift_specify_bit(ext_1bit, input_1_width + 4);
                break;

            case 5:
            case 6:  // -2
                bit_result = (shift_specify_bit(input_1_padded, 1, true) & ext_specify_bit(input_1_width, 3))
                    | shift_specify_bit(ext_2bit, input_1_width + 3);
                break;

            case 0:
            case 7:
            default: bit_result = 0ull; break;
            }
        }
        return bit_result;
    }

    void multiplier(uint64_t& out_carry, uint64_t& out_sum, uint64_t out_bits,
        uint64_t input_0, uint64_t input_0_width,
        uint64_t input_1, uint64_t input_1_width)
    {
        uint64_t input_0_padded = 0ull, input_1_padded = 0ull;
        uint64_t input_0_sign = 0ull, input_1_sign = 0ull, out_sign = 0ull;
        ext_padding(input_0, input_0_width, 1, input_0_sign, input_0_padded);

        uint64_t bit_pair_numb = ((input_0_width / 2) + 2);
        uint64_t max_width = (input_0_width + input_1_width + 1);

        uint64_t bitmul_step_result[64] = { 0ull };
        for (uint64_t bit_pair = 0; bit_pair < bit_pair_numb - 1; bit_pair++)
        {
            uint64_t input_0_padded_remain = (input_0_padded >> (bit_pair * 2));
            uint64_t temp_result = compute_bit_mul(input_0_width, input_1, input_1_width, input_0_padded_remain & 0x7);

            temp_result = (temp_result << (2 * bit_pair)) & (((uint64_t)1 << (max_width + 4)) - 1);
            bitmul_step_result[bit_pair + 1] = (temp_result >> 0x1) & (((uint64_t)1 << max_width) - 1);

            uint64_t ubitgrpvalue = (input_0_padded >> (2 * bit_pair)) & 0x7;
            if ((ubitgrpvalue >= 0x4) && (ubitgrpvalue <= 0x6))
            {
                bitmul_step_result[0] = bitmul_step_result[0] | ((uint64_t)1 << (bit_pair * 2));
            }
        }

        uint64_t next_step_result[64] = { 0ull };
        uint64_t pair_idx = bit_pair_numb;
        while (pair_idx > 2)
        {
            for (uint32_t idx = 0; idx < (pair_idx / 3); idx++)
            {
                next_step_result[idx * 2] = bitmul_step_result[idx * 3] ^ bitmul_step_result[idx * 3 + 1] ^ bitmul_step_result[idx * 3 + 2];

                uint64_t tmp_pp_carry = (bitmul_step_result[idx * 3] & bitmul_step_result[idx * 3 + 1]) |
                    (bitmul_step_result[idx * 3 + 1] & bitmul_step_result[idx * 3 + 2]) |
                    (bitmul_step_result[idx * 3] & bitmul_step_result[idx * 3 + 2]);

                next_step_result[idx * 2 + 1] = (tmp_pp_carry << 1) & (((uint64_t)1 << (max_width)) - 1);
            }

            if ((pair_idx % 3) > 0)
            {
                for (uint32_t idx = 0; idx < (pair_idx % 3); idx++)
                    next_step_result[2 * (pair_idx / 3) + idx] = bitmul_step_result[3 * (pair_idx / 3) + idx];
            }

            for (uint32_t idx = 0; idx < bit_pair_numb; idx++)
                bitmul_step_result[idx] = next_step_result[idx];

            pair_idx = pair_idx - (pair_idx / 3);
        }

        uint64_t out_temp0 = bitmul_step_result[0];
        uint64_t out_temp1 = (pair_idx > 1) ? bitmul_step_result[1] : 0;

        out_sign = ((out_temp0 >> (max_width - 1)) & 0x1)
            | ((out_temp1 >> (max_width - 1)) & 0x1);

        out_carry = out_sign ? (out_temp1 | ((((uint64_t)1 << (out_bits - max_width)) - 1) << max_width)) : out_temp1;
        out_sum = out_temp0;
    }

    bool chk_special_data(const uint32_t& instr_op, const uint32_t& exp, const uint32_t& sgn, const uint32_t& oridat)
    {
        switch (instr_op)
        {
        case SFU_RCP:
            if (exp != sfu_const_c::SFU_EXP_MIN && exp < sfu_const_c::RCP_EXP_MAX) return false;
            return true;

        case SFU_RSQ:
        case SFU_SQRT:
        case SFU_LOG:
            if (sgn || (exp == sfu_const_c::SFU_EXP_MIN || exp == sfu_const_c::SFU_EXP_MAX) || oridat == sfu_const_c::SPECIAL_FP_ONE)  return true;
            break;
        case SFU_EXP:
            if (exp <= sfu_const_c::EXP_EXP_MIN || exp >= sfu_const_c::EXP_EXP_MAX) return true;
            break;
        case SFU_SIN:
        case SFU_COS:
        {
            for (uint32_t ubitidx = 30; ubitidx >= 28; ubitidx--)  // z, inf, nan
                if ((oridat >> ubitidx) & 0x1) return true;
        }
        break;
        default:
            GPUASSERT(0, "error sfu instr op type");
        }
        return false;
    }
   
    uint32_t  get_special_data(const uint32_t& instr_op, const uint32_t& sgn, const uint32_t& exp, const uint32_t& man)
    {
        uint32_t res_sgn = sgn, res_exp = 0, res_man = 0, result = 0;
        switch (instr_op)
        {
        case SFU_RCP:
        {
            if (exp == sfu_const_c::SFU_EXP_MIN)
                result = compose_float(res_sgn, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
            else if (exp == sfu_const_c::SFU_EXP_MAX)
            {
                result = man ? compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MAX) /* inf->zero */ :
                    compose_float(res_sgn, sfu_const_c::SFU_EXP_MIN, sfu_const_c::SFU_MAN_MIN) /* Nan->Nan */;
            }
            else if (exp == 0xfe || exp == 0xfd)
            {
                if (exp == 0xfd && !man)  res_exp = 1;
                result = compose_float(res_sgn, res_exp, sfu_const_c::SFU_MAN_MIN);
            }
            else
                GPUASSERT(0, "normal case can't enter this part!");
        }
        break;
        case SFU_RSQ:
        {
            if (exp == sfu_const_c::SFU_EXP_MIN)
                result = compose_float(res_sgn, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
            else if (compose_float(sgn, exp, man) == sfu_const_c::SPECIAL_FP_ONE)
                result = sfu_const_c::SPECIAL_FP_ONE;
            else if (res_sgn || ((exp == sfu_const_c::SFU_EXP_MAX) && man))
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MAX);
            else
                result = compose_float(res_sgn, sfu_const_c::SFU_EXP_MIN, sfu_const_c::SFU_MAN_MIN);
        }
        break;
        case SFU_SQRT:
        {
            if (exp == sfu_const_c::SFU_EXP_MIN)  // +0/+den->+0, -0/-den->-0
                result = compose_float(res_sgn, sfu_const_c::SFU_EXP_MIN, sfu_const_c::SFU_MAN_MIN);
            else if (res_sgn || ((exp == sfu_const_c::SFU_EXP_MAX) && man))
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MAX);
            else if (exp == sfu_const_c::SFU_EXP_MAX)  //
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
            else if (compose_float(sgn, exp, man) == sfu_const_c::SPECIAL_FP_ONE)
                result = sfu_const_c::SPECIAL_FP_ONE;
        }
        break;
        case SFU_LOG:
        {
            if (exp == sfu_const_c::SFU_EXP_MIN)  // 0->-inf
                result = compose_float(1, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
            else if (compose_float(sgn, exp, man) == sfu_const_c::SPECIAL_FP_ONE)
                result = sfu_const_c::SPECIAL_ZERO;
            else if (res_sgn || ((exp == sfu_const_c::SFU_EXP_MAX) && man)) // -/nna->nan
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MAX);
            else
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
        }
        break;
        case SFU_EXP:
        {
            if ((exp == sfu_const_c::SFU_EXP_MAX) && man)
                result = compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MAX);
            else if (exp >= sfu_const_c::EXP_EXP_MAX)
                result = res_sgn ? sfu_const_c::SPECIAL_ZERO : compose_float(0, sfu_const_c::SFU_EXP_MAX, sfu_const_c::SFU_MAN_MIN);
            else if (exp <= sfu_const_c::EXP_EXP_MIN)
                result = compose_float(0, sfu_const_c::SFU_EXP_127, sfu_const_c::SFU_MAN_MIN);
        }
        break;
        case SFU_SIN:
        case SFU_COS:
        {
            uint32_t uori = compose_float(sgn, exp, man);
            if (get_specify_bit(uori, sfu_const_c::FLAG_INF_BIT) || get_specify_bit(uori, sfu_const_c::FLAG_NAN_BIT))
                result = ~sfu_const_c::SFU_SIGN_BIT;
            else if (get_specify_bit(uori, sfu_const_c::FLAG_Z_BIT))
                result = (instr_op == SFU_SIN) ? uori & sfu_const_c::SFU_SIGN_BIT : sfu_const_c::SPECIAL_FP_ONE;
        }
        break;
        default:
            GPUASSERT(0, "error sfu instr op type");
        }
        return result;
    }

    uint64_t adder_summary(const uint64_t& b_table_val, const uint32_t& usbit,
        const uint64_t& u64_1st_carryout_delta, const uint64_t& u64_1st_sign_out,
        const uint64_t& u64_2nd_carryout_square, const uint64_t& u64_2nd_sign_square,
        const uint32_t addshiftbit1, const uint32_t addshiftbit2, const uint32_t valmsk, uint64_t specialoff, bool bnegsbit = false, bool brever_neg = false)
    {
        bool uget_sbit_neg = bnegsbit ? !usbit : usbit;
        uint64_t uadder[3] = { 0ull };
        uadder[0] = b_table_val + specialoff;
        uadder[1] = (u64_1st_carryout_delta + u64_1st_sign_out) >> addshiftbit1;
        uadder[1] = uget_sbit_neg ? (~uadder[1] + 1) & valmsk : uadder[1];
        uadder[2] = (u64_2nd_carryout_square + u64_2nd_sign_square) >> addshiftbit2;
        if (brever_neg)
            uadder[2] = (~uadder[2] + 1) & valmsk;
        return (uadder[0] + uadder[1] + uadder[2]) & valmsk;
    }

    void adjust_adder(uint64_t& adder, uint64_t sumary, int bit)
    {
        int shift = bit - m_special_dat.m_lz;
        if (shift < 0)
            adder = sumary << (-shift);
        else
            adder = sumary >> shift;
    }

    uint64_t compute_man_out(const uint32_t& instr_op, const uint32_t& exp, const uint32_t& usbit, const uint64_t& b_table_val,
        const uint64_t& u64_1st_carryout_delta, const uint64_t& u64_1st_sign_out,
        const uint64_t& u64_2nd_carryout_square, const uint64_t& u64_2nd_sign_square)
    {
        uint32_t utrickbit = (exp & 0x1) ? 0 : 1;
        switch (instr_op)
        {
        case SFU_RCP:
            return adder_summary(b_table_val, usbit, u64_1st_carryout_delta, u64_1st_sign_out, u64_2nd_carryout_square, u64_2nd_sign_square, 15, 12, sfu_const_c::SFU_OUT_MASK29, 0ull, false);

        case SFU_RSQ:
            return adder_summary(b_table_val, usbit, u64_1st_carryout_delta, u64_1st_sign_out, u64_2nd_carryout_square, u64_2nd_sign_square, 15 - utrickbit, 11 - (utrickbit << 1), sfu_const_c::SFU_OUT_MASK29, 0ull, false);

        case SFU_SQRT:
            return adder_summary(b_table_val, !usbit, u64_1st_carryout_delta, u64_1st_sign_out, u64_2nd_carryout_square, u64_2nd_sign_square, 15 - utrickbit, 11 - (utrickbit << 1), sfu_const_c::SFU_OUT_MASK30, 0x10000000ull, false, true);

        case SFU_LOG:
        {
            if (m_special_dat.m_blg_int_res)
                return m_special_dat.m_lg_compute_res;

            uint64_t uadder[3] = { 0ull };
            if (((!m_special_dat.m_sbit) && exp == sfu_const_c::SFU_EXP_127)
                || ((m_special_dat.m_sbit) && exp == sfu_const_c::SFU_EXP_127 - 1))
            {
                uadder[0] = b_table_val << (m_special_dat.m_lz - m_special_dat.m_lz_idx);
                adjust_adder(uadder[1], u64_1st_carryout_delta + u64_1st_sign_out, 14);
                adjust_adder(uadder[2], u64_2nd_carryout_square + u64_2nd_sign_square, 11);
                m_special_dat.m_res_exp = sfu_const_c::SFU_EXP_127 - m_special_dat.m_lz;
            }
            else
            {
                uadder[0] = b_table_val >> m_special_dat.m_lz_idx;
                uadder[1] = (u64_1st_carryout_delta + u64_1st_sign_out) >> 14;
                uadder[2] = (u64_2nd_carryout_square + u64_2nd_sign_square) >> 11;
                m_special_dat.m_res_exp = sfu_const_c::SFU_EXP_127 + m_special_dat.m_lg_exp_exp;
            }

            uint64_t valmsk = sfu_const_c::SFU_OUT_MASK28;
            if (((m_special_dat.m_sbit) && exp >= sfu_const_c::SFU_EXP_127)
                || ((!m_special_dat.m_sbit) && exp <= sfu_const_c::SFU_EXP_127 - 1))
            {
                uadder[0] = get_negitive(uadder[0]);
                valmsk = sfu_const_c::SFU_OUT_MASK28 >> 1;
            }
            if (((!usbit) && exp >= sfu_const_c::SFU_EXP_127)
                || (usbit && exp <= sfu_const_c::SFU_EXP_127 - 1))
                uadder[1] = get_negitive(uadder[1]);
            if (exp >= sfu_const_c::SFU_EXP_127)
                uadder[2] = get_negitive(uadder[2]);

            uint64_t result = (uadder[0] + uadder[1] + uadder[2]) & valmsk;
            return (result >> m_special_dat.m_lg_exp_exp) | (uint64_t(m_special_dat.m_lg_exp_man) << (27 - m_special_dat.m_lg_exp_exp));
        }

        case SFU_EXP:
            return adder_summary(b_table_val, usbit, u64_1st_carryout_delta, u64_1st_sign_out, u64_2nd_carryout_square, u64_2nd_sign_square, 13, 10, sfu_const_c::SFU_OUT_MASK28, 0ull, true);

        case SFU_SIN:
        case SFU_COS:
        {
            uint64_t uadder[3] = { 0ull };
            uadder[0] = b_table_val << m_special_dat.m_lz;
            adjust_adder(uadder[1], u64_1st_carryout_delta + u64_1st_sign_out, 13);
            if (!usbit) uadder[1] = ~uadder[1];
            adjust_adder(uadder[2], u64_2nd_carryout_square + u64_2nd_sign_square, 8);
            return (uadder[0] + uadder[1] + ~uadder[2]) & sfu_const_c::SFU_OUT_MASK29;
        }

        default:
            GPUASSERT(0, "error sfu instr op type");
        }
        return 0ull;
    }

    uint32_t norm_man(const uint64_t& totman, uint32_t& exp_carry, uint32_t& movbit, const uint32_t specifybit0, const uint32_t specifybit1, const bool search)
    {
        uint32_t ures_out = 0, res_exp = 0;
        if (!search)
            while (movbit < 3)
            {
                if ((totman >> (specifybit0 - movbit)) & 0x1) break;
                movbit++;
            }
        else
            movbit = 0;
        ures_out = static_cast<uint32_t>(((totman >> (specifybit1 - movbit)) + 1) >> 1);
        exp_carry = static_cast<uint32_t>(ures_out >> 24);
        return ures_out & sfu_const_c::SFU_MAN_MAX;
    }

    uint32_t normalize(const uint32_t& instr_op, const uint32_t& sgn, const uint32_t& exp, const uint64_t& out)
    {
        uint32_t utrickbit = (exp & 0x1) ? 0 : 1;
        uint32_t movbit = 0, uexp_carry = 0;
        uint32_t ures_out = 0, res_exp = 0;
        switch (instr_op)
        {
        case SFU_RCP:
        {
            ures_out = norm_man(out, uexp_carry, movbit, 28, 4, false);
            res_exp = 254 + uexp_carry - movbit - exp;
            return compose_float(sgn, res_exp, ures_out);
        }

        case SFU_RSQ:
        {
            ures_out = norm_man(out, uexp_carry, movbit, 28, 4, false);
            res_exp = 190 + uexp_carry - movbit - (exp >> 1) + utrickbit;
            return compose_float(0, res_exp, ures_out);
        }

        case SFU_SQRT:
        {
            ures_out = norm_man(out, uexp_carry, movbit, 28, 4, true);
            res_exp = 64 + uexp_carry + (exp >> 1) - utrickbit;
            return compose_float(0, res_exp, ures_out);
        }

        case SFU_LOG:
        {
            if (out)
            {
                ures_out = norm_man(out, uexp_carry, movbit, 27, 3, false);
                res_exp = m_special_dat.m_res_exp + uexp_carry - movbit;
                return compose_float(m_special_dat.m_sgn, res_exp, ures_out & sfu_const_c::SFU_MAN_MAX);
            }
            else
                return compose_float(m_special_dat.m_sgn, sfu_const_c::SFU_EXP_MIN, sfu_const_c::SFU_MAN_MIN);
        }

        case SFU_EXP:
        {
            ures_out = norm_man(out, uexp_carry, movbit, 27, 3, false);
            if ((m_special_dat.m_res_exp <= 0x181) && (m_special_dat.m_res_exp >> 8))
                return compose_float(0, sfu_const_c::SFU_EXP_MIN, sfu_const_c::SFU_MAN_MIN);
            else
            {
                res_exp = (m_special_dat.m_res_exp + 127 - movbit + uexp_carry) & sfu_const_c::SFU_EXP_EXP_MAX;
                return compose_float(0, res_exp, res_exp ? ures_out : sfu_const_c::SFU_MAN_MIN);
            }
        }

        case SFU_SIN:
        case SFU_COS:
        {
            ures_out = norm_man(out, uexp_carry, movbit, 28, 4, false);
            res_exp = sfu_const_c::SFU_EXP_127 + uexp_carry - movbit - m_special_dat.m_lz;
            return compose_float(m_special_dat.m_sgn, res_exp, ures_out);
        }

        default:
            GPUASSERT(0, "error sfu instr op type");
        }
        return 0;
    }

    void do_fp_saturate(uint32_t& insat)
    {
        uint32_t sgn = 0, exp = 0, man = 0, result = 0;
        extract_float(insat, sgn, exp, man);
        man &= sfu_const_c::SFU_MAN_MAX;

        if ((exp == sfu_const_c::SFU_EXP_MAX) && man)
            result = 0;
        else
        {
            float fpdat = *(float *)(&insat);
            if (fpdat > 1.0f)
                result = sfu_const_c::SPECIAL_FP_ONE;
            else if (fpdat <= 0.0f)
                result = 0;
            else
                result = insat;
        }

        insat = result;
    }

    uint32_t get_fp_mode(uint32_t shadertype)
    {
        /*
        if (shadertype == (uint32_t)ck::SHADER_TYPE_T::PS)
            return m_ps_fp_mode;

        return m_fs_fp_mode;
        */
        return 0;
    }

    void saturation(const bool bsat, uint32_t& insat, uint32_t shadertype)
    {
        if (bsat)
            do_fp_saturate(insat);

        if (get_fp_mode(shadertype))
        {
            uint32_t sgn = 0, exp = 0, man = 0, result = 0;
            extract_float(insat, sgn, exp, man);

            if ((exp == sfu_const_c::SFU_EXP_MAX) && man)
                result = 0x7f800000;
        }
    }

    void do_sfu_function(SFU_OP op, uint32_t data, uint32_t& result_ret)
    {
        uint32_t sgn = 0, exp = 0, man = 0, result = 0, ucpuref_res = 0;
        m_special_dat.init();

        uint32_t usrcdat = data;

#if 0
        if (t.sfu.src_mod)
        {
            if (t.sfu.src_abs)
                usrcdat |= sfu_const_c::SFU_SIGN_BIT;
            else
                usrcdat = ((sfu_const_c::SFU_SIGN_BIT & t.sfu.data[uidx]) ^ sfu_const_c::SFU_SIGN_BIT) | ((~sfu_const_c::SFU_SIGN_BIT) & t.sfu.data[uidx]);
        }
        else if (t.sfu.src_abs)
            usrcdat &= ~sfu_const_c::SFU_SIGN_BIT;

        if (t.sfu.minor_op == ck::Peo_Sfu_Ins_Wr_Tag::Sfu::MINOR_OP::SIN || t.sfu.minor_op == ck::Peo_Sfu_Ins_Wr_Tag::Sfu::MINOR_OP::COS)
        {
            GPUASSERT((t.sfu.src_mod == 0) && (t.sfu.src_abs == 0), "sin/cos no abs and modify");
        }
#endif

        extract_float(usrcdat, sgn, exp, man);
        man &= sfu_const_c::SFU_MAN_MAX;

        // chk and special data handle
        if (chk_special_data(op, exp, sgn, usrcdat))
            result = get_special_data(op, sgn, exp, man);
        else
        {
            // cpu reference result
            // if (instr_op == ck::Peo_Sfu_Ins_Wr_Tag::Sfu::MINOR_OP::RCP)
            //    ucpuref_res = reinterpret_to_uint(1 / reinterpret_to_float(usrcdat));

            // idx, delta, del_square 
            uint32_t utable_idx = 0, usbit = 0;
            uint64_t udelta = 0ull, usquare = 0ull;
            delta_idx_pre_process(op, sgn, exp, man, utable_idx, usbit, udelta, usquare);

            if (((op == SFU_RSQ) || (op ==SFU_SQRT))
                && !(exp & 0x1))
                utable_idx += SFU_RCP_IDX_NUMB >> 1;

            // look up tables
            uint64_t table_value[3] = { 0ull, 0ull, 0ull };
            lookup_tables(op, utable_idx, table_value);


            uint32_t umul_inbit_f_tb = 19, umul_inbit_delta = 19;
            uint32_t umul_inbit_ex_tb = 12, umul_inbit_square = 15;
            uint64_t u641st_carryout_delta = 0ull, u641st_sign_out = 0ull;
            uint64_t u64_2nd_carryout_square = 0ull, u64_2nd_sign_square = 0ull;

            uint32_t outbits = 60;
            // multiplier pipe, f'*delta
            multiplier(u641st_carryout_delta, u641st_sign_out, outbits,
                table_value[1], umul_inbit_f_tb,
                udelta, umul_inbit_delta);

            // multiplier pipe, f''*delta^2/2
            multiplier(u64_2nd_carryout_square, u64_2nd_sign_square, outbits,
                table_value[2], umul_inbit_ex_tb,
                usquare, umul_inbit_square);

            // sum 3 parts, f + f'*delta + f"*delta^2/2
            uint64_t u64_out = compute_man_out(op, exp, usbit, table_value[0], u641st_carryout_delta, u641st_sign_out, u64_2nd_carryout_square, u64_2nd_sign_square);
            result = normalize(op, sgn, exp, u64_out);
        }
        // saturate and write into result
        //saturation(t.sfu.sat, result, t.shtyp);

        result_ret = result;
    }

};