#include "decode.h"

#define GROUP(n) (0x8000 | (n))


static const uint16_t ud_itab__1[] = {
             7,           0,
};

static const uint16_t ud_itab__2[] = {
             8,           0,
};

static const uint16_t ud_itab__3[] = {
            15,           0,
};

static const uint16_t ud_itab__6[] = {
            16,           0,           0,           0,
};

static const uint16_t ud_itab__7[] = {
            17,           0,           0,           0,
};

static const uint16_t ud_itab__8[] = {
            18,           0,           0,           0,
};

static const uint16_t ud_itab__9[] = {
            19,           0,           0,           0,
};

static const uint16_t ud_itab__10[] = {
            20,           0,           0,           0,
};

static const uint16_t ud_itab__11[] = {
            21,           0,           0,           0,
};

static const uint16_t ud_itab__5[] = {
      GROUP(6),    GROUP(7),    GROUP(8),    GROUP(9),
     GROUP(10),   GROUP(11),           0,           0,
};

static const uint16_t ud_itab__15[] = {
            22,           0,
};

static const uint16_t ud_itab__14[] = {
     GROUP(15),           0,           0,           0,
};

static const uint16_t ud_itab__17[] = {
            23,           0,
};

static const uint16_t ud_itab__16[] = {
     GROUP(17),           0,           0,           0,
};

static const uint16_t ud_itab__19[] = {
            24,           0,
};

static const uint16_t ud_itab__18[] = {
     GROUP(19),           0,           0,           0,
};

static const uint16_t ud_itab__21[] = {
            25,           0,
};

static const uint16_t ud_itab__20[] = {
     GROUP(21),           0,           0,           0,
};

static const uint16_t ud_itab__23[] = {
            26,           0,
};

static const uint16_t ud_itab__22[] = {
     GROUP(23),           0,           0,           0,
};

static const uint16_t ud_itab__25[] = {
            27,           0,
};

static const uint16_t ud_itab__24[] = {
     GROUP(25),           0,           0,           0,
};

static const uint16_t ud_itab__27[] = {
            28,           0,
};

static const uint16_t ud_itab__26[] = {
     GROUP(27),           0,           0,           0,
};

static const uint16_t ud_itab__13[] = {
     GROUP(14),   GROUP(16),   GROUP(18),   GROUP(20),
     GROUP(22),           0,   GROUP(24),   GROUP(26),
};

static const uint16_t ud_itab__32[] = {
             0,          29,           0,
};

static const uint16_t ud_itab__31[] = {
             0,   GROUP(32),
};

static const uint16_t ud_itab__30[] = {
     GROUP(31),           0,           0,           0,
};

static const uint16_t ud_itab__35[] = {
             0,          30,           0,
};

static const uint16_t ud_itab__34[] = {
             0,   GROUP(35),
};

static const uint16_t ud_itab__33[] = {
     GROUP(34),           0,           0,           0,
};

static const uint16_t ud_itab__38[] = {
             0,          31,           0,
};

static const uint16_t ud_itab__37[] = {
             0,   GROUP(38),
};

static const uint16_t ud_itab__36[] = {
     GROUP(37),           0,           0,           0,
};

static const uint16_t ud_itab__41[] = {
             0,          32,           0,
};

static const uint16_t ud_itab__40[] = {
             0,   GROUP(41),
};

static const uint16_t ud_itab__39[] = {
     GROUP(40),           0,           0,           0,
};

static const uint16_t ud_itab__29[] = {
             0,   GROUP(30),   GROUP(33),   GROUP(36),
     GROUP(39),           0,           0,           0,
};

static const uint16_t ud_itab__44[] = {
             0,          33,
};

static const uint16_t ud_itab__43[] = {
     GROUP(44),           0,           0,           0,
};

static const uint16_t ud_itab__46[] = {
             0,          34,
};

static const uint16_t ud_itab__45[] = {
     GROUP(46),           0,           0,           0,
};

static const uint16_t ud_itab__42[] = {
     GROUP(43),   GROUP(45),           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__49[] = {
             0,          35,
};

static const uint16_t ud_itab__48[] = {
     GROUP(49),           0,           0,           0,
};

static const uint16_t ud_itab__51[] = {
             0,          36,
};

static const uint16_t ud_itab__50[] = {
     GROUP(51),           0,           0,           0,
};

static const uint16_t ud_itab__47[] = {
     GROUP(48),   GROUP(50),           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__55[] = {
            37,           0,           0,
};

static const uint16_t ud_itab__54[] = {
             0,   GROUP(55),
};

static const uint16_t ud_itab__53[] = {
     GROUP(54),           0,           0,           0,
};

static const uint16_t ud_itab__58[] = {
            38,           0,           0,
};

static const uint16_t ud_itab__57[] = {
             0,   GROUP(58),
};

static const uint16_t ud_itab__56[] = {
     GROUP(57),           0,           0,           0,
};

static const uint16_t ud_itab__61[] = {
            39,           0,           0,
};

static const uint16_t ud_itab__60[] = {
             0,   GROUP(61),
};

static const uint16_t ud_itab__59[] = {
     GROUP(60),           0,           0,           0,
};

static const uint16_t ud_itab__64[] = {
            40,           0,           0,
};

static const uint16_t ud_itab__63[] = {
             0,   GROUP(64),
};

static const uint16_t ud_itab__62[] = {
     GROUP(63),           0,           0,           0,
};

static const uint16_t ud_itab__67[] = {
            41,           0,           0,
};

static const uint16_t ud_itab__66[] = {
             0,   GROUP(67),
};

static const uint16_t ud_itab__65[] = {
     GROUP(66),           0,           0,           0,
};

static const uint16_t ud_itab__70[] = {
            42,           0,           0,
};

static const uint16_t ud_itab__69[] = {
             0,   GROUP(70),
};

static const uint16_t ud_itab__68[] = {
     GROUP(69),           0,           0,           0,
};

static const uint16_t ud_itab__73[] = {
            43,           0,           0,
};

static const uint16_t ud_itab__72[] = {
             0,   GROUP(73),
};

static const uint16_t ud_itab__71[] = {
     GROUP(72),           0,           0,           0,
};

static const uint16_t ud_itab__76[] = {
            44,           0,           0,
};

static const uint16_t ud_itab__75[] = {
             0,   GROUP(76),
};

static const uint16_t ud_itab__74[] = {
     GROUP(75),           0,           0,           0,
};

static const uint16_t ud_itab__52[] = {
     GROUP(53),   GROUP(56),   GROUP(59),   GROUP(62),
     GROUP(65),   GROUP(68),   GROUP(71),   GROUP(74),
};

static const uint16_t ud_itab__78[] = {
             0,          45,
};

static const uint16_t ud_itab__77[] = {
     GROUP(78),           0,           0,           0,
};

static const uint16_t ud_itab__80[] = {
             0,          46,
};

static const uint16_t ud_itab__79[] = {
     GROUP(80),           0,           0,           0,
};

static const uint16_t ud_itab__83[] = {
             0,          47,
};

static const uint16_t ud_itab__82[] = {
     GROUP(83),           0,           0,           0,
};

static const uint16_t ud_itab__86[] = {
            48,           0,           0,
};

static const uint16_t ud_itab__85[] = {
             0,   GROUP(86),
};

static const uint16_t ud_itab__84[] = {
     GROUP(85),           0,           0,           0,
};

static const uint16_t ud_itab__81[] = {
     GROUP(82),   GROUP(84),           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__28[] = {
     GROUP(29),   GROUP(42),   GROUP(47),   GROUP(52),
     GROUP(77),           0,   GROUP(79),   GROUP(81),
};

static const uint16_t ud_itab__12[] = {
     GROUP(13),   GROUP(28),
};

static const uint16_t ud_itab__87[] = {
            49,           0,           0,           0,
};

static const uint16_t ud_itab__88[] = {
            50,           0,           0,           0,
};

static const uint16_t ud_itab__89[] = {
            51,           0,           0,           0,
};

static const uint16_t ud_itab__90[] = {
            52,           0,           0,           0,
};

static const uint16_t ud_itab__91[] = {
            53,           0,           0,           0,
};

static const uint16_t ud_itab__92[] = {
            54,           0,           0,           0,
};

static const uint16_t ud_itab__93[] = {
            55,           0,           0,           0,
};

static const uint16_t ud_itab__94[] = {
            56,           0,           0,           0,
};

static const uint16_t ud_itab__96[] = {
            57,           0,           0,           0,
};

static const uint16_t ud_itab__97[] = {
            58,           0,           0,           0,
};

static const uint16_t ud_itab__98[] = {
            59,           0,           0,           0,
};

static const uint16_t ud_itab__99[] = {
            60,           0,           0,           0,
};

static const uint16_t ud_itab__100[] = {
            61,           0,           0,           0,
};

static const uint16_t ud_itab__101[] = {
            62,           0,           0,           0,
};

static const uint16_t ud_itab__102[] = {
            63,           0,           0,           0,
};

static const uint16_t ud_itab__103[] = {
            64,           0,           0,           0,
};

static const uint16_t ud_itab__95[] = {
     GROUP(96),   GROUP(97),   GROUP(98),   GROUP(99),
    GROUP(100),  GROUP(101),  GROUP(102),  GROUP(103),
};

static const uint16_t ud_itab__104[] = {
            65,           0,           0,           0,
};

static const uint16_t ud_itab__105[] = {
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
            66,          67,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
            68,          69,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,          70,           0,
             0,           0,          71,           0,
            72,           0,           0,           0,
            73,           0,          74,          75,
             0,           0,          76,           0,
             0,           0,          77,           0,
            78,           0,           0,           0,
            79,           0,          80,          81,
             0,           0,          82,           0,
             0,           0,          83,           0,
            84,           0,           0,           0,
            85,           0,          86,          87,
             0,           0,           0,          88,
             0,           0,           0,          89,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__106[] = {
            90,          91,          92,          93,
};

static const uint16_t ud_itab__107[] = {
            94,          95,          96,          97,
};

static const uint16_t ud_itab__110[] = {
            98,           0,
};

static const uint16_t ud_itab__111[] = {
            99,           0,
};

static const uint16_t ud_itab__112[] = {
           100,           0,
};

static const uint16_t ud_itab__113[] = {
           101,           0,
};

static const uint16_t ud_itab__109[] = {
    GROUP(110),  GROUP(111),  GROUP(112),  GROUP(113),
};

static const uint16_t ud_itab__115[] = {
             0,         102,
};

static const uint16_t ud_itab__116[] = {
             0,         103,
};

static const uint16_t ud_itab__117[] = {
             0,         104,
};

static const uint16_t ud_itab__114[] = {
    GROUP(115),  GROUP(116),  GROUP(117),           0,
};

static const uint16_t ud_itab__108[] = {
    GROUP(109),  GROUP(114),
};

static const uint16_t ud_itab__118[] = {
           105,           0,           0,         106,
};

static const uint16_t ud_itab__119[] = {
           107,           0,           0,         108,
};

static const uint16_t ud_itab__120[] = {
           109,           0,           0,         110,
};

static const uint16_t ud_itab__123[] = {
           111,           0,
};

static const uint16_t ud_itab__124[] = {
           112,           0,
};

static const uint16_t ud_itab__125[] = {
           113,           0,
};

static const uint16_t ud_itab__122[] = {
    GROUP(123),           0,  GROUP(124),  GROUP(125),
};

static const uint16_t ud_itab__127[] = {
             0,         114,
};

static const uint16_t ud_itab__128[] = {
             0,         115,
};

static const uint16_t ud_itab__126[] = {
    GROUP(127),           0,  GROUP(128),           0,
};

static const uint16_t ud_itab__121[] = {
    GROUP(122),  GROUP(126),
};

static const uint16_t ud_itab__129[] = {
           116,           0,           0,         117,
};

static const uint16_t ud_itab__131[] = {
           118,           0,           0,           0,
};

static const uint16_t ud_itab__132[] = {
           119,           0,           0,           0,
};

static const uint16_t ud_itab__133[] = {
           120,           0,           0,           0,
};

static const uint16_t ud_itab__134[] = {
           121,           0,           0,           0,
};

static const uint16_t ud_itab__130[] = {
    GROUP(131),  GROUP(132),  GROUP(133),  GROUP(134),
             0,           0,           0,           0,
};

static const uint16_t ud_itab__135[] = {
           122,           0,           0,           0,
};

static const uint16_t ud_itab__136[] = {
           123,           0,           0,           0,
};

static const uint16_t ud_itab__137[] = {
           124,           0,           0,           0,
};

static const uint16_t ud_itab__138[] = {
           125,           0,           0,           0,
};

static const uint16_t ud_itab__139[] = {
           126,           0,           0,           0,
};

static const uint16_t ud_itab__140[] = {
           127,           0,           0,           0,
};

static const uint16_t ud_itab__141[] = {
           128,           0,           0,           0,
};

static const uint16_t ud_itab__142[] = {
           129,           0,           0,           0,
};

static const uint16_t ud_itab__143[] = {
           130,           0,           0,           0,
};

static const uint16_t ud_itab__144[] = {
           131,           0,           0,           0,
};

static const uint16_t ud_itab__145[] = {
           132,           0,           0,           0,
};

static const uint16_t ud_itab__146[] = {
           133,           0,           0,         134,
};

static const uint16_t ud_itab__147[] = {
           135,           0,           0,         136,
};

static const uint16_t ud_itab__148[] = {
           137,         138,         139,         140,
};

static const uint16_t ud_itab__149[] = {
           141,           0,           0,         142,
};

static const uint16_t ud_itab__150[] = {
           143,         144,         145,         146,
};

static const uint16_t ud_itab__151[] = {
           147,         148,         149,         150,
};

static const uint16_t ud_itab__152[] = {
           151,           0,           0,         152,
};

static const uint16_t ud_itab__153[] = {
           153,           0,           0,         154,
};

static const uint16_t ud_itab__154[] = {
           155,           0,           0,           0,
};

static const uint16_t ud_itab__155[] = {
           156,           0,           0,           0,
};

static const uint16_t ud_itab__156[] = {
           157,           0,           0,           0,
};

static const uint16_t ud_itab__157[] = {
           158,           0,           0,           0,
};

static const uint16_t ud_itab__160[] = {
             0,         160,           0,
};

static const uint16_t ud_itab__159[] = {
           159,  GROUP(160),
};

static const uint16_t ud_itab__158[] = {
    GROUP(159),           0,           0,           0,
};

static const uint16_t ud_itab__163[] = {
             0,         162,           0,
};

static const uint16_t ud_itab__162[] = {
           161,  GROUP(163),
};

static const uint16_t ud_itab__161[] = {
    GROUP(162),           0,           0,           0,
};

static const uint16_t ud_itab__164[] = {
           163,           0,           0,           0,
};

static const uint16_t ud_itab__166[] = {
           164,           0,           0,         165,
};

static const uint16_t ud_itab__167[] = {
           166,           0,           0,         167,
};

static const uint16_t ud_itab__168[] = {
           168,           0,           0,         169,
};

static const uint16_t ud_itab__169[] = {
           170,           0,           0,         171,
};

static const uint16_t ud_itab__170[] = {
           172,           0,           0,         173,
};

static const uint16_t ud_itab__171[] = {
           174,           0,           0,         175,
};

static const uint16_t ud_itab__172[] = {
           176,           0,           0,         177,
};

static const uint16_t ud_itab__173[] = {
           178,           0,           0,         179,
};

static const uint16_t ud_itab__174[] = {
           180,           0,           0,         181,
};

static const uint16_t ud_itab__175[] = {
           182,           0,           0,         183,
};

static const uint16_t ud_itab__176[] = {
           184,           0,           0,         185,
};

static const uint16_t ud_itab__177[] = {
           186,           0,           0,         187,
};

static const uint16_t ud_itab__178[] = {
             0,           0,           0,         188,
};

static const uint16_t ud_itab__179[] = {
             0,           0,           0,         189,
};

static const uint16_t ud_itab__180[] = {
             0,           0,           0,         190,
};

static const uint16_t ud_itab__181[] = {
             0,           0,           0,         191,
};

static const uint16_t ud_itab__182[] = {
           192,           0,           0,         193,
};

static const uint16_t ud_itab__183[] = {
           194,           0,           0,         195,
};

static const uint16_t ud_itab__184[] = {
           196,           0,           0,         197,
};

static const uint16_t ud_itab__185[] = {
             0,           0,           0,         198,
};

static const uint16_t ud_itab__186[] = {
             0,           0,           0,         199,
};

static const uint16_t ud_itab__187[] = {
             0,           0,           0,         200,
};

static const uint16_t ud_itab__188[] = {
             0,           0,           0,         201,
};

static const uint16_t ud_itab__189[] = {
             0,           0,           0,         202,
};

static const uint16_t ud_itab__190[] = {
             0,           0,           0,         203,
};

static const uint16_t ud_itab__191[] = {
             0,           0,           0,         204,
};

static const uint16_t ud_itab__192[] = {
             0,           0,           0,         205,
};

static const uint16_t ud_itab__193[] = {
             0,           0,           0,         206,
};

static const uint16_t ud_itab__194[] = {
             0,           0,           0,         207,
};

static const uint16_t ud_itab__195[] = {
             0,           0,           0,         208,
};

static const uint16_t ud_itab__196[] = {
             0,           0,           0,         209,
};

static const uint16_t ud_itab__197[] = {
             0,           0,           0,         210,
};

static const uint16_t ud_itab__198[] = {
             0,           0,           0,         211,
};

static const uint16_t ud_itab__199[] = {
             0,           0,           0,         212,
};

static const uint16_t ud_itab__200[] = {
             0,           0,           0,         213,
};

static const uint16_t ud_itab__201[] = {
             0,           0,           0,         214,
};

static const uint16_t ud_itab__202[] = {
             0,           0,           0,         215,
};

static const uint16_t ud_itab__203[] = {
             0,           0,           0,         216,
};

static const uint16_t ud_itab__204[] = {
             0,           0,           0,         217,
};

static const uint16_t ud_itab__205[] = {
             0,           0,           0,         218,
};

static const uint16_t ud_itab__206[] = {
             0,           0,           0,         219,
};

static const uint16_t ud_itab__207[] = {
             0,           0,           0,         220,
};

static const uint16_t ud_itab__208[] = {
             0,           0,           0,         221,
};

static const uint16_t ud_itab__209[] = {
             0,           0,           0,         222,
};

static const uint16_t ud_itab__210[] = {
             0,           0,           0,         223,
};

static const uint16_t ud_itab__211[] = {
             0,           0,           0,         224,
};

static const uint16_t ud_itab__214[] = {
             0,         225,           0,
};

static const uint16_t ud_itab__213[] = {
             0,  GROUP(214),
};

static const uint16_t ud_itab__212[] = {
             0,           0,           0,  GROUP(213),
};

static const uint16_t ud_itab__217[] = {
             0,         226,           0,
};

static const uint16_t ud_itab__216[] = {
             0,  GROUP(217),
};

static const uint16_t ud_itab__215[] = {
             0,           0,           0,  GROUP(216),
};

static const uint16_t ud_itab__218[] = {
             0,           0,           0,         227,
};

static const uint16_t ud_itab__219[] = {
             0,           0,           0,         228,
};

static const uint16_t ud_itab__220[] = {
             0,           0,           0,         229,
};

static const uint16_t ud_itab__221[] = {
             0,           0,           0,         230,
};

static const uint16_t ud_itab__222[] = {
             0,           0,           0,         231,
};

static const uint16_t ud_itab__223[] = {
           232,         233,           0,           0,
};

static const uint16_t ud_itab__224[] = {
           234,         235,           0,           0,
};

static const uint16_t ud_itab__165[] = {
    GROUP(166),  GROUP(167),  GROUP(168),  GROUP(169),
    GROUP(170),  GROUP(171),  GROUP(172),  GROUP(173),
    GROUP(174),  GROUP(175),  GROUP(176),  GROUP(177),
             0,           0,           0,           0,
    GROUP(178),           0,           0,           0,
    GROUP(179),  GROUP(180),           0,  GROUP(181),
             0,           0,           0,           0,
    GROUP(182),  GROUP(183),  GROUP(184),           0,
    GROUP(185),  GROUP(186),  GROUP(187),  GROUP(188),
    GROUP(189),  GROUP(190),           0,           0,
    GROUP(191),  GROUP(192),  GROUP(193),  GROUP(194),
             0,           0,           0,           0,
    GROUP(195),  GROUP(196),  GROUP(197),  GROUP(198),
    GROUP(199),  GROUP(200),           0,  GROUP(201),
    GROUP(202),  GROUP(203),  GROUP(204),  GROUP(205),
    GROUP(206),  GROUP(207),  GROUP(208),  GROUP(209),
    GROUP(210),  GROUP(211),           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(212),  GROUP(215),           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,  GROUP(218),
    GROUP(219),  GROUP(220),  GROUP(221),  GROUP(222),
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(223),  GROUP(224),           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__226[] = {
             0,           0,           0,         236,
};

static const uint16_t ud_itab__227[] = {
             0,           0,           0,         237,
};

static const uint16_t ud_itab__228[] = {
             0,           0,           0,         238,
};

static const uint16_t ud_itab__229[] = {
             0,           0,           0,         239,
};

static const uint16_t ud_itab__230[] = {
             0,           0,           0,         240,
};

static const uint16_t ud_itab__231[] = {
             0,           0,           0,         241,
};

static const uint16_t ud_itab__232[] = {
             0,           0,           0,         242,
};

static const uint16_t ud_itab__233[] = {
           243,           0,           0,         244,
};

static const uint16_t ud_itab__234[] = {
             0,           0,           0,         245,
};

static const uint16_t ud_itab__235[] = {
             0,           0,           0,         246,
};

static const uint16_t ud_itab__237[] = {
           247,         248,         249,
};

static const uint16_t ud_itab__236[] = {
             0,           0,           0,  GROUP(237),
};

static const uint16_t ud_itab__238[] = {
             0,           0,           0,         250,
};

static const uint16_t ud_itab__239[] = {
             0,           0,           0,         251,
};

static const uint16_t ud_itab__240[] = {
             0,           0,           0,         252,
};

static const uint16_t ud_itab__242[] = {
           253,         254,         255,
};

static const uint16_t ud_itab__241[] = {
             0,           0,           0,  GROUP(242),
};

static const uint16_t ud_itab__243[] = {
             0,           0,           0,         256,
};

static const uint16_t ud_itab__244[] = {
             0,           0,           0,         257,
};

static const uint16_t ud_itab__245[] = {
             0,           0,           0,         258,
};

static const uint16_t ud_itab__246[] = {
             0,           0,           0,         259,
};

static const uint16_t ud_itab__247[] = {
             0,           0,           0,         260,
};

static const uint16_t ud_itab__248[] = {
             0,           0,           0,         261,
};

static const uint16_t ud_itab__249[] = {
             0,           0,           0,         262,
};

static const uint16_t ud_itab__250[] = {
             0,           0,           0,         263,
};

static const uint16_t ud_itab__251[] = {
             0,           0,           0,         264,
};

static const uint16_t ud_itab__225[] = {
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(226),  GROUP(227),  GROUP(228),  GROUP(229),
    GROUP(230),  GROUP(231),  GROUP(232),  GROUP(233),
             0,           0,           0,           0,
    GROUP(234),  GROUP(235),  GROUP(236),  GROUP(238),
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(239),  GROUP(240),  GROUP(241),           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(243),  GROUP(244),  GROUP(245),           0,
    GROUP(246),           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
    GROUP(247),  GROUP(248),  GROUP(249),  GROUP(250),
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,  GROUP(251),
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__252[] = {
           265,           0,           0,           0,
};

static const uint16_t ud_itab__253[] = {
           266,           0,           0,           0,
};

static const uint16_t ud_itab__254[] = {
           267,           0,           0,           0,
};

static const uint16_t ud_itab__255[] = {
           268,           0,           0,           0,
};

static const uint16_t ud_itab__256[] = {
           269,           0,           0,           0,
};

static const uint16_t ud_itab__257[] = {
           270,           0,           0,           0,
};

static const uint16_t ud_itab__258[] = {
           271,           0,           0,           0,
};

static const uint16_t ud_itab__259[] = {
           272,           0,           0,           0,
};

static const uint16_t ud_itab__260[] = {
           273,           0,           0,           0,
};

static const uint16_t ud_itab__261[] = {
           274,           0,           0,           0,
};

static const uint16_t ud_itab__262[] = {
           275,           0,           0,           0,
};

static const uint16_t ud_itab__263[] = {
           276,           0,           0,           0,
};

static const uint16_t ud_itab__264[] = {
           277,           0,           0,           0,
};

static const uint16_t ud_itab__265[] = {
           278,           0,           0,           0,
};

static const uint16_t ud_itab__266[] = {
           279,           0,           0,           0,
};

static const uint16_t ud_itab__267[] = {
           280,           0,           0,           0,
};

static const uint16_t ud_itab__268[] = {
           281,           0,           0,         282,
};

static const uint16_t ud_itab__269[] = {
           283,         284,         285,         286,
};

static const uint16_t ud_itab__270[] = {
           287,           0,         288,           0,
};

static const uint16_t ud_itab__271[] = {
           289,           0,         290,           0,
};

static const uint16_t ud_itab__272[] = {
           291,           0,           0,         292,
};

static const uint16_t ud_itab__273[] = {
           293,           0,           0,         294,
};

static const uint16_t ud_itab__274[] = {
           295,           0,           0,         296,
};

static const uint16_t ud_itab__275[] = {
           297,           0,           0,         298,
};

static const uint16_t ud_itab__276[] = {
           299,         300,         301,         302,
};

static const uint16_t ud_itab__277[] = {
           303,         304,         305,         306,
};

static const uint16_t ud_itab__278[] = {
           307,         308,         309,         310,
};

static const uint16_t ud_itab__279[] = {
           311,           0,         312,         313,
};

static const uint16_t ud_itab__280[] = {
           314,         315,         316,         317,
};

static const uint16_t ud_itab__281[] = {
           318,         319,         320,         321,
};

static const uint16_t ud_itab__282[] = {
           322,         323,         324,         325,
};

static const uint16_t ud_itab__283[] = {
           326,         327,         328,         329,
};

static const uint16_t ud_itab__284[] = {
           330,           0,           0,         331,
};

static const uint16_t ud_itab__285[] = {
           332,           0,           0,         333,
};

static const uint16_t ud_itab__286[] = {
           334,           0,           0,         335,
};

static const uint16_t ud_itab__287[] = {
           336,           0,           0,         337,
};

static const uint16_t ud_itab__288[] = {
           338,           0,           0,         339,
};

static const uint16_t ud_itab__289[] = {
           340,           0,           0,         341,
};

static const uint16_t ud_itab__290[] = {
           342,           0,           0,         343,
};

static const uint16_t ud_itab__291[] = {
           344,           0,           0,         345,
};

static const uint16_t ud_itab__292[] = {
           346,           0,           0,         347,
};

static const uint16_t ud_itab__293[] = {
           348,           0,           0,         349,
};

static const uint16_t ud_itab__294[] = {
           350,           0,           0,         351,
};

static const uint16_t ud_itab__295[] = {
           352,           0,           0,         353,
};

static const uint16_t ud_itab__296[] = {
             0,           0,           0,         354,
};

static const uint16_t ud_itab__297[] = {
             0,           0,           0,         355,
};

static const uint16_t ud_itab__298[] = {
           356,           0,           0,         357,
};

static const uint16_t ud_itab__299[] = {
           358,           0,         359,         360,
};

static const uint16_t ud_itab__300[] = {
           361,         362,         363,         364,
};

static const uint16_t ud_itab__302[] = {
           365,           0,           0,         366,
};

static const uint16_t ud_itab__303[] = {
           367,           0,           0,         368,
};

static const uint16_t ud_itab__304[] = {
           369,           0,           0,         370,
};

static const uint16_t ud_itab__301[] = {
             0,           0,  GROUP(302),           0,
    GROUP(303),           0,  GROUP(304),           0,
};

static const uint16_t ud_itab__306[] = {
           371,           0,           0,         372,
};

static const uint16_t ud_itab__307[] = {
           373,           0,           0,         374,
};

static const uint16_t ud_itab__308[] = {
           375,           0,           0,         376,
};

static const uint16_t ud_itab__305[] = {
             0,           0,  GROUP(306),           0,
    GROUP(307),           0,  GROUP(308),           0,
};

static const uint16_t ud_itab__310[] = {
           377,           0,           0,         378,
};

static const uint16_t ud_itab__311[] = {
             0,           0,           0,         379,
};

static const uint16_t ud_itab__312[] = {
           380,           0,           0,         381,
};

static const uint16_t ud_itab__313[] = {
             0,           0,           0,         382,
};

static const uint16_t ud_itab__309[] = {
             0,           0,  GROUP(310),  GROUP(311),
             0,           0,  GROUP(312),  GROUP(313),
};

static const uint16_t ud_itab__314[] = {
           383,           0,           0,         384,
};

static const uint16_t ud_itab__315[] = {
           385,           0,           0,         386,
};

static const uint16_t ud_itab__316[] = {
           387,           0,           0,         388,
};

static const uint16_t ud_itab__317[] = {
           389,           0,           0,           0,
};

static const uint16_t ud_itab__319[] = {
             0,         390,           0,
};

static const uint16_t ud_itab__318[] = {
    GROUP(319),           0,           0,           0,
};

static const uint16_t ud_itab__321[] = {
             0,         391,           0,
};

static const uint16_t ud_itab__320[] = {
    GROUP(321),           0,           0,           0,
};

static const uint16_t ud_itab__322[] = {
             0,         392,           0,         393,
};

static const uint16_t ud_itab__323[] = {
             0,         394,           0,         395,
};

static const uint16_t ud_itab__324[] = {
           396,           0,         397,         398,
};

static const uint16_t ud_itab__325[] = {
           399,           0,         400,         401,
};

static const uint16_t ud_itab__326[] = {
           402,           0,           0,           0,
};

static const uint16_t ud_itab__327[] = {
           403,           0,           0,           0,
};

static const uint16_t ud_itab__328[] = {
           404,           0,           0,           0,
};

static const uint16_t ud_itab__329[] = {
           405,           0,           0,           0,
};

static const uint16_t ud_itab__330[] = {
           406,           0,           0,           0,
};

static const uint16_t ud_itab__331[] = {
           407,           0,           0,           0,
};

static const uint16_t ud_itab__332[] = {
           408,           0,           0,           0,
};

static const uint16_t ud_itab__333[] = {
           409,           0,           0,           0,
};

static const uint16_t ud_itab__334[] = {
           410,           0,           0,           0,
};

static const uint16_t ud_itab__335[] = {
           411,           0,           0,           0,
};

static const uint16_t ud_itab__336[] = {
           412,           0,           0,           0,
};

static const uint16_t ud_itab__337[] = {
           413,           0,           0,           0,
};

static const uint16_t ud_itab__338[] = {
           414,           0,           0,           0,
};

static const uint16_t ud_itab__339[] = {
           415,           0,           0,           0,
};

static const uint16_t ud_itab__340[] = {
           416,           0,           0,           0,
};

static const uint16_t ud_itab__341[] = {
           417,           0,           0,           0,
};

static const uint16_t ud_itab__342[] = {
           418,           0,           0,           0,
};

static const uint16_t ud_itab__343[] = {
           419,           0,           0,           0,
};

static const uint16_t ud_itab__344[] = {
           420,           0,           0,           0,
};

static const uint16_t ud_itab__345[] = {
           421,           0,           0,           0,
};

static const uint16_t ud_itab__346[] = {
           422,           0,           0,           0,
};

static const uint16_t ud_itab__347[] = {
           423,           0,           0,           0,
};

static const uint16_t ud_itab__348[] = {
           424,           0,           0,           0,
};

static const uint16_t ud_itab__349[] = {
           425,           0,           0,           0,
};

static const uint16_t ud_itab__350[] = {
           426,           0,           0,           0,
};

static const uint16_t ud_itab__351[] = {
           427,           0,           0,           0,
};

static const uint16_t ud_itab__352[] = {
           428,           0,           0,           0,
};

static const uint16_t ud_itab__353[] = {
           429,           0,           0,           0,
};

static const uint16_t ud_itab__354[] = {
           430,           0,           0,           0,
};

static const uint16_t ud_itab__355[] = {
           431,           0,           0,           0,
};

static const uint16_t ud_itab__356[] = {
           432,           0,           0,           0,
};

static const uint16_t ud_itab__357[] = {
           433,           0,           0,           0,
};

static const uint16_t ud_itab__358[] = {
           434,           0,           0,           0,
};

static const uint16_t ud_itab__359[] = {
           435,           0,           0,           0,
};

static const uint16_t ud_itab__360[] = {
           436,           0,           0,           0,
};

static const uint16_t ud_itab__361[] = {
           437,           0,           0,           0,
};

static const uint16_t ud_itab__362[] = {
           438,           0,           0,           0,
};

static const uint16_t ud_itab__363[] = {
           439,           0,           0,           0,
};

static const uint16_t ud_itab__368[] = {
             0,         440,
};

static const uint16_t ud_itab__367[] = {
    GROUP(368),           0,           0,           0,
};

static const uint16_t ud_itab__366[] = {
    GROUP(367),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__371[] = {
             0,         441,
};

static const uint16_t ud_itab__370[] = {
    GROUP(371),           0,           0,           0,
};

static const uint16_t ud_itab__369[] = {
    GROUP(370),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__374[] = {
             0,         442,
};

static const uint16_t ud_itab__373[] = {
    GROUP(374),           0,           0,           0,
};

static const uint16_t ud_itab__372[] = {
    GROUP(373),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__365[] = {
    GROUP(366),  GROUP(369),  GROUP(372),           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__364[] = {
             0,  GROUP(365),
};

static const uint16_t ud_itab__379[] = {
             0,         443,
};

static const uint16_t ud_itab__378[] = {
    GROUP(379),           0,           0,           0,
};

static const uint16_t ud_itab__377[] = {
    GROUP(378),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__382[] = {
             0,         444,
};

static const uint16_t ud_itab__381[] = {
    GROUP(382),           0,           0,           0,
};

static const uint16_t ud_itab__380[] = {
    GROUP(381),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__385[] = {
             0,         445,
};

static const uint16_t ud_itab__384[] = {
    GROUP(385),           0,           0,           0,
};

static const uint16_t ud_itab__383[] = {
    GROUP(384),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__388[] = {
             0,         446,
};

static const uint16_t ud_itab__387[] = {
    GROUP(388),           0,           0,           0,
};

static const uint16_t ud_itab__386[] = {
    GROUP(387),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__391[] = {
             0,         447,
};

static const uint16_t ud_itab__390[] = {
    GROUP(391),           0,           0,           0,
};

static const uint16_t ud_itab__389[] = {
    GROUP(390),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__394[] = {
             0,         448,
};

static const uint16_t ud_itab__393[] = {
    GROUP(394),           0,           0,           0,
};

static const uint16_t ud_itab__392[] = {
    GROUP(393),           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__376[] = {
    GROUP(377),  GROUP(380),  GROUP(383),  GROUP(386),
    GROUP(389),  GROUP(392),           0,           0,
};

static const uint16_t ud_itab__375[] = {
             0,  GROUP(376),
};

static const uint16_t ud_itab__395[] = {
           449,           0,           0,           0,
};

static const uint16_t ud_itab__396[] = {
           450,           0,           0,           0,
};

static const uint16_t ud_itab__397[] = {
           451,           0,           0,           0,
};

static const uint16_t ud_itab__398[] = {
           452,           0,           0,           0,
};

static const uint16_t ud_itab__399[] = {
           453,           0,           0,           0,
};

static const uint16_t ud_itab__400[] = {
           454,           0,           0,           0,
};

static const uint16_t ud_itab__404[] = {
           455,           0,
};

static const uint16_t ud_itab__403[] = {
    GROUP(404),           0,           0,           0,
};

static const uint16_t ud_itab__406[] = {
           456,           0,
};

static const uint16_t ud_itab__405[] = {
    GROUP(406),           0,           0,           0,
};

static const uint16_t ud_itab__408[] = {
           457,           0,
};

static const uint16_t ud_itab__407[] = {
    GROUP(408),           0,           0,           0,
};

static const uint16_t ud_itab__410[] = {
           458,           0,
};

static const uint16_t ud_itab__409[] = {
    GROUP(410),           0,           0,           0,
};

static const uint16_t ud_itab__412[] = {
           459,           0,
};

static const uint16_t ud_itab__411[] = {
    GROUP(412),           0,           0,           0,
};

static const uint16_t ud_itab__414[] = {
           460,           0,
};

static const uint16_t ud_itab__413[] = {
    GROUP(414),           0,           0,           0,
};

static const uint16_t ud_itab__416[] = {
           461,           0,
};

static const uint16_t ud_itab__415[] = {
    GROUP(416),           0,           0,           0,
};

static const uint16_t ud_itab__402[] = {
    GROUP(403),  GROUP(405),  GROUP(407),  GROUP(409),
    GROUP(411),  GROUP(413),           0,  GROUP(415),
};

static const uint16_t ud_itab__420[] = {
             0,         462,
};

static const uint16_t ud_itab__419[] = {
    GROUP(420),           0,           0,           0,
};

static const uint16_t ud_itab__422[] = {
             0,         463,
};

static const uint16_t ud_itab__421[] = {
    GROUP(422),           0,           0,           0,
};

static const uint16_t ud_itab__424[] = {
             0,         464,
};

static const uint16_t ud_itab__423[] = {
    GROUP(424),           0,           0,           0,
};

static const uint16_t ud_itab__426[] = {
             0,         465,
};

static const uint16_t ud_itab__425[] = {
    GROUP(426),           0,           0,           0,
};

static const uint16_t ud_itab__428[] = {
             0,         466,
};

static const uint16_t ud_itab__427[] = {
    GROUP(428),           0,           0,           0,
};

static const uint16_t ud_itab__430[] = {
             0,         467,
};

static const uint16_t ud_itab__429[] = {
    GROUP(430),           0,           0,           0,
};

static const uint16_t ud_itab__432[] = {
             0,         468,
};

static const uint16_t ud_itab__431[] = {
    GROUP(432),           0,           0,           0,
};

static const uint16_t ud_itab__434[] = {
             0,         469,
};

static const uint16_t ud_itab__433[] = {
    GROUP(434),           0,           0,           0,
};

static const uint16_t ud_itab__418[] = {
    GROUP(419),  GROUP(421),  GROUP(423),  GROUP(425),
    GROUP(427),  GROUP(429),  GROUP(431),  GROUP(433),
};

static const uint16_t ud_itab__437[] = {
             0,         470,
};

static const uint16_t ud_itab__436[] = {
    GROUP(437),           0,           0,           0,
};

static const uint16_t ud_itab__439[] = {
             0,         471,
};

static const uint16_t ud_itab__438[] = {
    GROUP(439),           0,           0,           0,
};

static const uint16_t ud_itab__441[] = {
             0,         472,
};

static const uint16_t ud_itab__440[] = {
    GROUP(441),           0,           0,           0,
};

static const uint16_t ud_itab__443[] = {
             0,         473,
};

static const uint16_t ud_itab__442[] = {
    GROUP(443),           0,           0,           0,
};

static const uint16_t ud_itab__445[] = {
             0,         474,
};

static const uint16_t ud_itab__444[] = {
    GROUP(445),           0,           0,           0,
};

static const uint16_t ud_itab__447[] = {
             0,         475,
};

static const uint16_t ud_itab__446[] = {
    GROUP(447),           0,           0,           0,
};

static const uint16_t ud_itab__449[] = {
             0,         476,
};

static const uint16_t ud_itab__448[] = {
    GROUP(449),           0,           0,           0,
};

static const uint16_t ud_itab__451[] = {
             0,         477,
};

static const uint16_t ud_itab__450[] = {
    GROUP(451),           0,           0,           0,
};

static const uint16_t ud_itab__435[] = {
    GROUP(436),  GROUP(438),  GROUP(440),  GROUP(442),
    GROUP(444),  GROUP(446),  GROUP(448),  GROUP(450),
};

static const uint16_t ud_itab__454[] = {
             0,         478,
};

static const uint16_t ud_itab__453[] = {
    GROUP(454),           0,           0,           0,
};

static const uint16_t ud_itab__456[] = {
             0,         479,
};

static const uint16_t ud_itab__455[] = {
    GROUP(456),           0,           0,           0,
};

static const uint16_t ud_itab__458[] = {
             0,         480,
};

static const uint16_t ud_itab__457[] = {
    GROUP(458),           0,           0,           0,
};

static const uint16_t ud_itab__460[] = {
             0,         481,
};

static const uint16_t ud_itab__459[] = {
    GROUP(460),           0,           0,           0,
};

static const uint16_t ud_itab__462[] = {
             0,         482,
};

static const uint16_t ud_itab__461[] = {
    GROUP(462),           0,           0,           0,
};

static const uint16_t ud_itab__464[] = {
             0,         483,
};

static const uint16_t ud_itab__463[] = {
    GROUP(464),           0,           0,           0,
};

static const uint16_t ud_itab__466[] = {
             0,         484,
};

static const uint16_t ud_itab__465[] = {
    GROUP(466),           0,           0,           0,
};

static const uint16_t ud_itab__468[] = {
             0,         485,
};

static const uint16_t ud_itab__467[] = {
    GROUP(468),           0,           0,           0,
};

static const uint16_t ud_itab__452[] = {
    GROUP(453),  GROUP(455),  GROUP(457),  GROUP(459),
    GROUP(461),  GROUP(463),  GROUP(465),  GROUP(467),
};

static const uint16_t ud_itab__417[] = {
             0,           0,           0,           0,
             0,  GROUP(418),  GROUP(435),  GROUP(452),
};

static const uint16_t ud_itab__401[] = {
    GROUP(402),  GROUP(417),
};

static const uint16_t ud_itab__469[] = {
           486,           0,           0,           0,
};

static const uint16_t ud_itab__470[] = {
           487,           0,           0,           0,
};

static const uint16_t ud_itab__471[] = {
           488,           0,           0,           0,
};

static const uint16_t ud_itab__472[] = {
           489,           0,           0,           0,
};

static const uint16_t ud_itab__473[] = {
           490,           0,           0,           0,
};

static const uint16_t ud_itab__474[] = {
           491,           0,           0,           0,
};

static const uint16_t ud_itab__475[] = {
           492,           0,           0,           0,
};

static const uint16_t ud_itab__476[] = {
           493,           0,           0,           0,
};

static const uint16_t ud_itab__477[] = {
           494,           0,           0,           0,
};

static const uint16_t ud_itab__478[] = {
             0,           0,         495,           0,
};

static const uint16_t ud_itab__480[] = {
           496,           0,           0,           0,
};

static const uint16_t ud_itab__481[] = {
           497,           0,           0,           0,
};

static const uint16_t ud_itab__482[] = {
           498,           0,           0,           0,
};

static const uint16_t ud_itab__483[] = {
           499,           0,           0,           0,
};

static const uint16_t ud_itab__479[] = {
             0,           0,           0,           0,
    GROUP(480),  GROUP(481),  GROUP(482),  GROUP(483),
};

static const uint16_t ud_itab__484[] = {
           500,           0,           0,           0,
};

static const uint16_t ud_itab__485[] = {
           501,           0,           0,           0,
};

static const uint16_t ud_itab__486[] = {
           502,           0,           0,           0,
};

static const uint16_t ud_itab__487[] = {
           503,           0,           0,           0,
};

static const uint16_t ud_itab__488[] = {
           504,           0,           0,           0,
};

static const uint16_t ud_itab__489[] = {
           505,           0,           0,           0,
};

static const uint16_t ud_itab__490[] = {
           506,           0,           0,           0,
};

static const uint16_t ud_itab__491[] = {
           507,         508,         509,         510,
};

static const uint16_t ud_itab__492[] = {
           511,           0,           0,           0,
};

static const uint16_t ud_itab__493[] = {
           512,           0,           0,         513,
};

static const uint16_t ud_itab__494[] = {
           514,           0,           0,         515,
};

static const uint16_t ud_itab__495[] = {
           516,           0,           0,         517,
};

static const uint16_t ud_itab__498[] = {
           518,         519,         520,
};

static const uint16_t ud_itab__497[] = {
    GROUP(498),           0,           0,           0,
};

static const uint16_t ud_itab__500[] = {
             0,         521,           0,
};

static const uint16_t ud_itab__501[] = {
             0,         522,           0,
};

static const uint16_t ud_itab__502[] = {
             0,         523,           0,
};

static const uint16_t ud_itab__499[] = {
    GROUP(500),           0,  GROUP(501),  GROUP(502),
};

static const uint16_t ud_itab__504[] = {
             0,         524,           0,
};

static const uint16_t ud_itab__503[] = {
    GROUP(504),           0,           0,           0,
};

static const uint16_t ud_itab__496[] = {
             0,  GROUP(497),           0,           0,
             0,           0,  GROUP(499),  GROUP(503),
};

static const uint16_t ud_itab__505[] = {
           525,           0,           0,           0,
};

static const uint16_t ud_itab__506[] = {
           526,           0,           0,           0,
};

static const uint16_t ud_itab__507[] = {
           527,           0,           0,           0,
};

static const uint16_t ud_itab__508[] = {
           528,           0,           0,           0,
};

static const uint16_t ud_itab__509[] = {
           529,           0,           0,           0,
};

static const uint16_t ud_itab__510[] = {
           530,           0,           0,           0,
};

static const uint16_t ud_itab__511[] = {
           531,           0,           0,           0,
};

static const uint16_t ud_itab__512[] = {
           532,           0,           0,           0,
};

static const uint16_t ud_itab__513[] = {
             0,         533,           0,         534,
};

static const uint16_t ud_itab__514[] = {
           535,           0,           0,         536,
};

static const uint16_t ud_itab__515[] = {
           537,           0,           0,         538,
};

static const uint16_t ud_itab__516[] = {
           539,           0,           0,         540,
};

static const uint16_t ud_itab__517[] = {
           541,           0,           0,         542,
};

static const uint16_t ud_itab__518[] = {
           543,           0,           0,         544,
};

static const uint16_t ud_itab__519[] = {
             0,         545,         546,         547,
};

static const uint16_t ud_itab__520[] = {
           548,           0,           0,         549,
};

static const uint16_t ud_itab__521[] = {
           550,           0,           0,         551,
};

static const uint16_t ud_itab__522[] = {
           552,           0,           0,         553,
};

static const uint16_t ud_itab__523[] = {
           554,           0,           0,         555,
};

static const uint16_t ud_itab__524[] = {
           556,           0,           0,         557,
};

static const uint16_t ud_itab__525[] = {
           558,           0,           0,         559,
};

static const uint16_t ud_itab__526[] = {
           560,           0,           0,         561,
};

static const uint16_t ud_itab__527[] = {
           562,           0,           0,         563,
};

static const uint16_t ud_itab__528[] = {
           564,           0,           0,         565,
};

static const uint16_t ud_itab__529[] = {
           566,           0,           0,         567,
};

static const uint16_t ud_itab__530[] = {
           568,           0,           0,         569,
};

static const uint16_t ud_itab__531[] = {
           570,           0,           0,         571,
};

static const uint16_t ud_itab__532[] = {
           572,           0,           0,         573,
};

static const uint16_t ud_itab__533[] = {
           574,           0,           0,         575,
};

static const uint16_t ud_itab__534[] = {
           576,           0,           0,         577,
};

static const uint16_t ud_itab__535[] = {
             0,         578,         579,         580,
};

static const uint16_t ud_itab__536[] = {
           581,           0,           0,         582,
};

static const uint16_t ud_itab__537[] = {
           583,           0,           0,         584,
};

static const uint16_t ud_itab__538[] = {
           585,           0,           0,         586,
};

static const uint16_t ud_itab__539[] = {
           587,           0,           0,         588,
};

static const uint16_t ud_itab__540[] = {
           589,           0,           0,         590,
};

static const uint16_t ud_itab__541[] = {
           591,           0,           0,         592,
};

static const uint16_t ud_itab__542[] = {
           593,           0,           0,         594,
};

static const uint16_t ud_itab__543[] = {
           595,           0,           0,         596,
};

static const uint16_t ud_itab__544[] = {
           597,           0,           0,         598,
};

static const uint16_t ud_itab__545[] = {
             0,         599,           0,           0,
};

static const uint16_t ud_itab__546[] = {
           600,           0,           0,         601,
};

static const uint16_t ud_itab__547[] = {
           602,           0,           0,         603,
};

static const uint16_t ud_itab__548[] = {
           604,           0,           0,         605,
};

static const uint16_t ud_itab__549[] = {
           606,           0,           0,         607,
};

static const uint16_t ud_itab__550[] = {
           608,           0,           0,         609,
};

static const uint16_t ud_itab__551[] = {
           610,           0,           0,         611,
};

static const uint16_t ud_itab__554[] = {
             0,         612,
};

static const uint16_t ud_itab__555[] = {
             0,         613,
};

static const uint16_t ud_itab__553[] = {
    GROUP(554),           0,           0,  GROUP(555),
};

static const uint16_t ud_itab__552[] = {
             0,  GROUP(553),
};

static const uint16_t ud_itab__556[] = {
           614,           0,           0,         615,
};

static const uint16_t ud_itab__557[] = {
           616,           0,           0,         617,
};

static const uint16_t ud_itab__558[] = {
           618,           0,           0,         619,
};

static const uint16_t ud_itab__559[] = {
           620,           0,           0,         621,
};

static const uint16_t ud_itab__560[] = {
           622,           0,           0,         623,
};

static const uint16_t ud_itab__561[] = {
           624,           0,           0,         625,
};

static const uint16_t ud_itab__562[] = {
           626,           0,           0,         627,
};

static const uint16_t ud_itab__4[] = {
      GROUP(5),   GROUP(12),   GROUP(87),   GROUP(88),
             0,   GROUP(89),   GROUP(90),   GROUP(91),
     GROUP(92),   GROUP(93),           0,   GROUP(94),
             0,   GROUP(95),  GROUP(104),  GROUP(105),
    GROUP(106),  GROUP(107),  GROUP(108),  GROUP(118),
    GROUP(119),  GROUP(120),  GROUP(121),  GROUP(129),
    GROUP(130),  GROUP(135),  GROUP(136),  GROUP(137),
    GROUP(138),  GROUP(139),  GROUP(140),  GROUP(141),
    GROUP(142),  GROUP(143),  GROUP(144),  GROUP(145),
             0,           0,           0,           0,
    GROUP(146),  GROUP(147),  GROUP(148),  GROUP(149),
    GROUP(150),  GROUP(151),  GROUP(152),  GROUP(153),
    GROUP(154),  GROUP(155),  GROUP(156),  GROUP(157),
    GROUP(158),  GROUP(161),           0,  GROUP(164),
    GROUP(165),           0,  GROUP(225),           0,
             0,           0,           0,           0,
    GROUP(252),  GROUP(253),  GROUP(254),  GROUP(255),
    GROUP(256),  GROUP(257),  GROUP(258),  GROUP(259),
    GROUP(260),  GROUP(261),  GROUP(262),  GROUP(263),
    GROUP(264),  GROUP(265),  GROUP(266),  GROUP(267),
    GROUP(268),  GROUP(269),  GROUP(270),  GROUP(271),
    GROUP(272),  GROUP(273),  GROUP(274),  GROUP(275),
    GROUP(276),  GROUP(277),  GROUP(278),  GROUP(279),
    GROUP(280),  GROUP(281),  GROUP(282),  GROUP(283),
    GROUP(284),  GROUP(285),  GROUP(286),  GROUP(287),
    GROUP(288),  GROUP(289),  GROUP(290),  GROUP(291),
    GROUP(292),  GROUP(293),  GROUP(294),  GROUP(295),
    GROUP(296),  GROUP(297),  GROUP(298),  GROUP(299),
    GROUP(300),  GROUP(301),  GROUP(305),  GROUP(309),
    GROUP(314),  GROUP(315),  GROUP(316),  GROUP(317),
    GROUP(318),  GROUP(320),           0,           0,
    GROUP(322),  GROUP(323),  GROUP(324),  GROUP(325),
    GROUP(326),  GROUP(327),  GROUP(328),  GROUP(329),
    GROUP(330),  GROUP(331),  GROUP(332),  GROUP(333),
    GROUP(334),  GROUP(335),  GROUP(336),  GROUP(337),
    GROUP(338),  GROUP(339),  GROUP(340),  GROUP(341),
    GROUP(342),  GROUP(343),  GROUP(344),  GROUP(345),
    GROUP(346),  GROUP(347),  GROUP(348),  GROUP(349),
    GROUP(350),  GROUP(351),  GROUP(352),  GROUP(353),
    GROUP(354),  GROUP(355),  GROUP(356),  GROUP(357),
    GROUP(358),  GROUP(359),  GROUP(360),  GROUP(361),
    GROUP(362),  GROUP(363),  GROUP(364),  GROUP(375),
    GROUP(395),  GROUP(396),  GROUP(397),  GROUP(398),
    GROUP(399),  GROUP(400),  GROUP(401),  GROUP(469),
    GROUP(470),  GROUP(471),  GROUP(472),  GROUP(473),
    GROUP(474),  GROUP(475),  GROUP(476),  GROUP(477),
    GROUP(478),           0,  GROUP(479),  GROUP(484),
    GROUP(485),  GROUP(486),  GROUP(487),  GROUP(488),
    GROUP(489),  GROUP(490),  GROUP(491),  GROUP(492),
    GROUP(493),  GROUP(494),  GROUP(495),  GROUP(496),
    GROUP(505),  GROUP(506),  GROUP(507),  GROUP(508),
    GROUP(509),  GROUP(510),  GROUP(511),  GROUP(512),
    GROUP(513),  GROUP(514),  GROUP(515),  GROUP(516),
    GROUP(517),  GROUP(518),  GROUP(519),  GROUP(520),
    GROUP(521),  GROUP(522),  GROUP(523),  GROUP(524),
    GROUP(525),  GROUP(526),  GROUP(527),  GROUP(528),
    GROUP(529),  GROUP(530),  GROUP(531),  GROUP(532),
    GROUP(533),  GROUP(534),  GROUP(535),  GROUP(536),
    GROUP(537),  GROUP(538),  GROUP(539),  GROUP(540),
    GROUP(541),  GROUP(542),  GROUP(543),  GROUP(544),
    GROUP(545),  GROUP(546),  GROUP(547),  GROUP(548),
    GROUP(549),  GROUP(550),  GROUP(551),  GROUP(552),
    GROUP(556),  GROUP(557),  GROUP(558),  GROUP(559),
    GROUP(560),  GROUP(561),  GROUP(562),           0,
};

static const uint16_t ud_itab__563[] = {
           634,           0,
};

static const uint16_t ud_itab__564[] = {
           635,           0,
};

static const uint16_t ud_itab__565[] = {
           642,           0,
};

static const uint16_t ud_itab__566[] = {
           643,           0,
};

static const uint16_t ud_itab__567[] = {
           650,           0,
};

static const uint16_t ud_itab__568[] = {
           657,           0,
};

static const uint16_t ud_itab__569[] = {
           664,           0,
};

static const uint16_t ud_itab__570[] = {
           671,           0,
};

static const uint16_t ud_itab__572[] = {
           704,           0,
};

static const uint16_t ud_itab__573[] = {
           705,           0,
};

static const uint16_t ud_itab__571[] = {
    GROUP(572),  GROUP(573),           0,
};

static const uint16_t ud_itab__575[] = {
           706,           0,
};

static const uint16_t ud_itab__576[] = {
           707,           0,
};

static const uint16_t ud_itab__574[] = {
    GROUP(575),  GROUP(576),           0,
};

static const uint16_t ud_itab__577[] = {
           708,           0,
};

static const uint16_t ud_itab__578[] = {
           709,         710,
};

static const uint16_t ud_itab__579[] = {
           716,         717,           0,
};

static const uint16_t ud_itab__580[] = {
           719,         720,           0,
};

static const uint16_t ud_itab__581[] = {
           737,         738,         739,         740,
           741,         742,         743,         744,
};

static const uint16_t ud_itab__582[] = {
           745,         746,         747,         748,
           749,         750,         751,         752,
};

static const uint16_t ud_itab__584[] = {
           753,           0,
};

static const uint16_t ud_itab__585[] = {
           754,           0,
};

static const uint16_t ud_itab__586[] = {
           755,           0,
};

static const uint16_t ud_itab__587[] = {
           756,           0,
};

static const uint16_t ud_itab__588[] = {
           757,           0,
};

static const uint16_t ud_itab__589[] = {
           758,           0,
};

static const uint16_t ud_itab__590[] = {
           759,           0,
};

static const uint16_t ud_itab__591[] = {
           760,           0,
};

static const uint16_t ud_itab__583[] = {
    GROUP(584),  GROUP(585),  GROUP(586),  GROUP(587),
    GROUP(588),  GROUP(589),  GROUP(590),  GROUP(591),
};

static const uint16_t ud_itab__592[] = {
           761,         762,         763,         764,
           765,         766,         767,         768,
};

static const uint16_t ud_itab__593[] = {
           780,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__594[] = {
           789,         790,         791,
};

static const uint16_t ud_itab__595[] = {
           792,         793,         794,
};

static const uint16_t ud_itab__596[] = {
           795,           0,
};

static const uint16_t ud_itab__598[] = {
           797,         798,
};

static const uint16_t ud_itab__599[] = {
           799,         800,
};

static const uint16_t ud_itab__600[] = {
             0,         801,
};

static const uint16_t ud_itab__597[] = {
    GROUP(598),  GROUP(599),  GROUP(600),
};

static const uint16_t ud_itab__602[] = {
           802,           0,
};

static const uint16_t ud_itab__603[] = {
           803,         804,
};

static const uint16_t ud_itab__604[] = {
             0,         805,
};

static const uint16_t ud_itab__601[] = {
    GROUP(602),  GROUP(603),  GROUP(604),
};

static const uint16_t ud_itab__605[] = {
           813,         814,         815,
};

static const uint16_t ud_itab__606[] = {
           817,         818,         819,
};

static const uint16_t ud_itab__607[] = {
           823,         824,         825,
};

static const uint16_t ud_itab__608[] = {
           827,         828,         829,
};

static const uint16_t ud_itab__609[] = {
           831,         832,         833,
};

static const uint16_t ud_itab__610[] = {
           850,         851,         852,         853,
           854,         855,         856,         857,
};

static const uint16_t ud_itab__611[] = {
           858,         859,         860,         861,
           862,         863,         864,         865,
};

static const uint16_t ud_itab__612[] = {
           868,           0,
};

static const uint16_t ud_itab__613[] = {
           869,           0,
};

static const uint16_t ud_itab__614[] = {
           870,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__615[] = {
           871,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__616[] = {
           878,           0,
};

static const uint16_t ud_itab__617[] = {
           879,         880,         881,
};

static const uint16_t ud_itab__618[] = {
           882,         883,         884,         885,
           886,         887,         888,         889,
};

static const uint16_t ud_itab__619[] = {
           890,         891,         892,         893,
           894,         895,         896,         897,
};

static const uint16_t ud_itab__620[] = {
           898,         899,         900,         901,
           902,         903,         904,         905,
};

static const uint16_t ud_itab__621[] = {
           906,         907,         908,         909,
           910,         911,         912,         913,
};

static const uint16_t ud_itab__622[] = {
           914,           0,
};

static const uint16_t ud_itab__623[] = {
           915,           0,
};

static const uint16_t ud_itab__624[] = {
           916,           0,
};

static const uint16_t ud_itab__627[] = {
           918,           0,
};

static const uint16_t ud_itab__628[] = {
           919,           0,
};

static const uint16_t ud_itab__629[] = {
           920,           0,
};

static const uint16_t ud_itab__630[] = {
           921,           0,
};

static const uint16_t ud_itab__631[] = {
           922,           0,
};

static const uint16_t ud_itab__632[] = {
           923,           0,
};

static const uint16_t ud_itab__633[] = {
           924,           0,
};

static const uint16_t ud_itab__634[] = {
           925,           0,
};

static const uint16_t ud_itab__626[] = {
    GROUP(627),  GROUP(628),  GROUP(629),  GROUP(630),
    GROUP(631),  GROUP(632),  GROUP(633),  GROUP(634),
};

static const uint16_t ud_itab__636[] = {
             0,         926,
};

static const uint16_t ud_itab__637[] = {
             0,         927,
};

static const uint16_t ud_itab__638[] = {
             0,         928,
};

static const uint16_t ud_itab__639[] = {
             0,         929,
};

static const uint16_t ud_itab__640[] = {
             0,         930,
};

static const uint16_t ud_itab__641[] = {
             0,         931,
};

static const uint16_t ud_itab__642[] = {
             0,         932,
};

static const uint16_t ud_itab__643[] = {
             0,         933,
};

static const uint16_t ud_itab__644[] = {
             0,         934,
};

static const uint16_t ud_itab__645[] = {
             0,         935,
};

static const uint16_t ud_itab__646[] = {
             0,         936,
};

static const uint16_t ud_itab__647[] = {
             0,         937,
};

static const uint16_t ud_itab__648[] = {
             0,         938,
};

static const uint16_t ud_itab__649[] = {
             0,         939,
};

static const uint16_t ud_itab__650[] = {
             0,         940,
};

static const uint16_t ud_itab__651[] = {
             0,         941,
};

static const uint16_t ud_itab__652[] = {
             0,         942,
};

static const uint16_t ud_itab__653[] = {
             0,         943,
};

static const uint16_t ud_itab__654[] = {
             0,         944,
};

static const uint16_t ud_itab__655[] = {
             0,         945,
};

static const uint16_t ud_itab__656[] = {
             0,         946,
};

static const uint16_t ud_itab__657[] = {
             0,         947,
};

static const uint16_t ud_itab__658[] = {
             0,         948,
};

static const uint16_t ud_itab__659[] = {
             0,         949,
};

static const uint16_t ud_itab__660[] = {
             0,         950,
};

static const uint16_t ud_itab__661[] = {
             0,         951,
};

static const uint16_t ud_itab__662[] = {
             0,         952,
};

static const uint16_t ud_itab__663[] = {
             0,         953,
};

static const uint16_t ud_itab__664[] = {
             0,         954,
};

static const uint16_t ud_itab__665[] = {
             0,         955,
};

static const uint16_t ud_itab__666[] = {
             0,         956,
};

static const uint16_t ud_itab__667[] = {
             0,         957,
};

static const uint16_t ud_itab__668[] = {
             0,         958,
};

static const uint16_t ud_itab__669[] = {
             0,         959,
};

static const uint16_t ud_itab__670[] = {
             0,         960,
};

static const uint16_t ud_itab__671[] = {
             0,         961,
};

static const uint16_t ud_itab__672[] = {
             0,         962,
};

static const uint16_t ud_itab__673[] = {
             0,         963,
};

static const uint16_t ud_itab__674[] = {
             0,         964,
};

static const uint16_t ud_itab__675[] = {
             0,         965,
};

static const uint16_t ud_itab__676[] = {
             0,         966,
};

static const uint16_t ud_itab__677[] = {
             0,         967,
};

static const uint16_t ud_itab__678[] = {
             0,         968,
};

static const uint16_t ud_itab__679[] = {
             0,         969,
};

static const uint16_t ud_itab__680[] = {
             0,         970,
};

static const uint16_t ud_itab__681[] = {
             0,         971,
};

static const uint16_t ud_itab__682[] = {
             0,         972,
};

static const uint16_t ud_itab__683[] = {
             0,         973,
};

static const uint16_t ud_itab__684[] = {
             0,         974,
};

static const uint16_t ud_itab__685[] = {
             0,         975,
};

static const uint16_t ud_itab__686[] = {
             0,         976,
};

static const uint16_t ud_itab__687[] = {
             0,         977,
};

static const uint16_t ud_itab__688[] = {
             0,         978,
};

static const uint16_t ud_itab__689[] = {
             0,         979,
};

static const uint16_t ud_itab__690[] = {
             0,         980,
};

static const uint16_t ud_itab__691[] = {
             0,         981,
};

static const uint16_t ud_itab__692[] = {
             0,         982,
};

static const uint16_t ud_itab__693[] = {
             0,         983,
};

static const uint16_t ud_itab__694[] = {
             0,         984,
};

static const uint16_t ud_itab__695[] = {
             0,         985,
};

static const uint16_t ud_itab__696[] = {
             0,         986,
};

static const uint16_t ud_itab__697[] = {
             0,         987,
};

static const uint16_t ud_itab__698[] = {
             0,         988,
};

static const uint16_t ud_itab__699[] = {
             0,         989,
};

static const uint16_t ud_itab__635[] = {
    GROUP(636),  GROUP(637),  GROUP(638),  GROUP(639),
    GROUP(640),  GROUP(641),  GROUP(642),  GROUP(643),
    GROUP(644),  GROUP(645),  GROUP(646),  GROUP(647),
    GROUP(648),  GROUP(649),  GROUP(650),  GROUP(651),
    GROUP(652),  GROUP(653),  GROUP(654),  GROUP(655),
    GROUP(656),  GROUP(657),  GROUP(658),  GROUP(659),
    GROUP(660),  GROUP(661),  GROUP(662),  GROUP(663),
    GROUP(664),  GROUP(665),  GROUP(666),  GROUP(667),
    GROUP(668),  GROUP(669),  GROUP(670),  GROUP(671),
    GROUP(672),  GROUP(673),  GROUP(674),  GROUP(675),
    GROUP(676),  GROUP(677),  GROUP(678),  GROUP(679),
    GROUP(680),  GROUP(681),  GROUP(682),  GROUP(683),
    GROUP(684),  GROUP(685),  GROUP(686),  GROUP(687),
    GROUP(688),  GROUP(689),  GROUP(690),  GROUP(691),
    GROUP(692),  GROUP(693),  GROUP(694),  GROUP(695),
    GROUP(696),  GROUP(697),  GROUP(698),  GROUP(699),
};

static const uint16_t ud_itab__625[] = {
    GROUP(626),  GROUP(635),
};

static const uint16_t ud_itab__702[] = {
           990,           0,
};

static const uint16_t ud_itab__703[] = {
           991,           0,
};

static const uint16_t ud_itab__704[] = {
           992,           0,
};

static const uint16_t ud_itab__705[] = {
           993,           0,
};

static const uint16_t ud_itab__706[] = {
           994,           0,
};

static const uint16_t ud_itab__707[] = {
           995,           0,
};

static const uint16_t ud_itab__708[] = {
           996,           0,
};

static const uint16_t ud_itab__701[] = {
    GROUP(702),           0,  GROUP(703),  GROUP(704),
    GROUP(705),  GROUP(706),  GROUP(707),  GROUP(708),
};

static const uint16_t ud_itab__710[] = {
             0,         997,
};

static const uint16_t ud_itab__711[] = {
             0,         998,
};

static const uint16_t ud_itab__712[] = {
             0,         999,
};

static const uint16_t ud_itab__713[] = {
             0,        1000,
};

static const uint16_t ud_itab__714[] = {
             0,        1001,
};

static const uint16_t ud_itab__715[] = {
             0,        1002,
};

static const uint16_t ud_itab__716[] = {
             0,        1003,
};

static const uint16_t ud_itab__717[] = {
             0,        1004,
};

static const uint16_t ud_itab__718[] = {
             0,        1005,
};

static const uint16_t ud_itab__719[] = {
             0,        1006,
};

static const uint16_t ud_itab__720[] = {
             0,        1007,
};

static const uint16_t ud_itab__721[] = {
             0,        1008,
};

static const uint16_t ud_itab__722[] = {
             0,        1009,
};

static const uint16_t ud_itab__723[] = {
             0,        1010,
};

static const uint16_t ud_itab__724[] = {
             0,        1011,
};

static const uint16_t ud_itab__725[] = {
             0,        1012,
};

static const uint16_t ud_itab__726[] = {
             0,        1013,
};

static const uint16_t ud_itab__727[] = {
             0,        1014,
};

static const uint16_t ud_itab__728[] = {
             0,        1015,
};

static const uint16_t ud_itab__729[] = {
             0,        1016,
};

static const uint16_t ud_itab__730[] = {
             0,        1017,
};

static const uint16_t ud_itab__731[] = {
             0,        1018,
};

static const uint16_t ud_itab__732[] = {
             0,        1019,
};

static const uint16_t ud_itab__733[] = {
             0,        1020,
};

static const uint16_t ud_itab__734[] = {
             0,        1021,
};

static const uint16_t ud_itab__735[] = {
             0,        1022,
};

static const uint16_t ud_itab__736[] = {
             0,        1023,
};

static const uint16_t ud_itab__737[] = {
             0,        1024,
};

static const uint16_t ud_itab__738[] = {
             0,        1025,
};

static const uint16_t ud_itab__739[] = {
             0,        1026,
};

static const uint16_t ud_itab__740[] = {
             0,        1027,
};

static const uint16_t ud_itab__741[] = {
             0,        1028,
};

static const uint16_t ud_itab__742[] = {
             0,        1029,
};

static const uint16_t ud_itab__743[] = {
             0,        1030,
};

static const uint16_t ud_itab__744[] = {
             0,        1031,
};

static const uint16_t ud_itab__745[] = {
             0,        1032,
};

static const uint16_t ud_itab__746[] = {
             0,        1033,
};

static const uint16_t ud_itab__747[] = {
             0,        1034,
};

static const uint16_t ud_itab__748[] = {
             0,        1035,
};

static const uint16_t ud_itab__749[] = {
             0,        1036,
};

static const uint16_t ud_itab__750[] = {
             0,        1037,
};

static const uint16_t ud_itab__751[] = {
             0,        1038,
};

static const uint16_t ud_itab__752[] = {
             0,        1039,
};

static const uint16_t ud_itab__753[] = {
             0,        1040,
};

static const uint16_t ud_itab__754[] = {
             0,        1041,
};

static const uint16_t ud_itab__755[] = {
             0,        1042,
};

static const uint16_t ud_itab__756[] = {
             0,        1043,
};

static const uint16_t ud_itab__757[] = {
             0,        1044,
};

static const uint16_t ud_itab__758[] = {
             0,        1045,
};

static const uint16_t ud_itab__759[] = {
             0,        1046,
};

static const uint16_t ud_itab__760[] = {
             0,        1047,
};

static const uint16_t ud_itab__761[] = {
             0,        1048,
};

static const uint16_t ud_itab__709[] = {
    GROUP(710),  GROUP(711),  GROUP(712),  GROUP(713),
    GROUP(714),  GROUP(715),  GROUP(716),  GROUP(717),
    GROUP(718),  GROUP(719),  GROUP(720),  GROUP(721),
    GROUP(722),  GROUP(723),  GROUP(724),  GROUP(725),
    GROUP(726),           0,           0,           0,
             0,           0,           0,           0,
    GROUP(727),  GROUP(728),  GROUP(729),  GROUP(730),
    GROUP(731),  GROUP(732),  GROUP(733),  GROUP(734),
    GROUP(735),  GROUP(736),           0,           0,
    GROUP(737),  GROUP(738),           0,           0,
    GROUP(739),  GROUP(740),  GROUP(741),  GROUP(742),
    GROUP(743),  GROUP(744),  GROUP(745),           0,
    GROUP(746),  GROUP(747),  GROUP(748),  GROUP(749),
    GROUP(750),  GROUP(751),  GROUP(752),  GROUP(753),
    GROUP(754),  GROUP(755),  GROUP(756),  GROUP(757),
    GROUP(758),  GROUP(759),  GROUP(760),  GROUP(761),
};

static const uint16_t ud_itab__700[] = {
    GROUP(701),  GROUP(709),
};

static const uint16_t ud_itab__764[] = {
          1049,           0,
};

static const uint16_t ud_itab__765[] = {
          1050,           0,
};

static const uint16_t ud_itab__766[] = {
          1051,           0,
};

static const uint16_t ud_itab__767[] = {
          1052,           0,
};

static const uint16_t ud_itab__768[] = {
          1053,           0,
};

static const uint16_t ud_itab__769[] = {
          1054,           0,
};

static const uint16_t ud_itab__770[] = {
          1055,           0,
};

static const uint16_t ud_itab__771[] = {
          1056,           0,
};

static const uint16_t ud_itab__763[] = {
    GROUP(764),  GROUP(765),  GROUP(766),  GROUP(767),
    GROUP(768),  GROUP(769),  GROUP(770),  GROUP(771),
};

static const uint16_t ud_itab__773[] = {
             0,        1057,
};

static const uint16_t ud_itab__774[] = {
             0,        1058,
};

static const uint16_t ud_itab__775[] = {
             0,        1059,
};

static const uint16_t ud_itab__776[] = {
             0,        1060,
};

static const uint16_t ud_itab__777[] = {
             0,        1061,
};

static const uint16_t ud_itab__778[] = {
             0,        1062,
};

static const uint16_t ud_itab__779[] = {
             0,        1063,
};

static const uint16_t ud_itab__780[] = {
             0,        1064,
};

static const uint16_t ud_itab__781[] = {
             0,        1065,
};

static const uint16_t ud_itab__782[] = {
             0,        1066,
};

static const uint16_t ud_itab__783[] = {
             0,        1067,
};

static const uint16_t ud_itab__784[] = {
             0,        1068,
};

static const uint16_t ud_itab__785[] = {
             0,        1069,
};

static const uint16_t ud_itab__786[] = {
             0,        1070,
};

static const uint16_t ud_itab__787[] = {
             0,        1071,
};

static const uint16_t ud_itab__788[] = {
             0,        1072,
};

static const uint16_t ud_itab__789[] = {
             0,        1073,
};

static const uint16_t ud_itab__790[] = {
             0,        1074,
};

static const uint16_t ud_itab__791[] = {
             0,        1075,
};

static const uint16_t ud_itab__792[] = {
             0,        1076,
};

static const uint16_t ud_itab__793[] = {
             0,        1077,
};

static const uint16_t ud_itab__794[] = {
             0,        1078,
};

static const uint16_t ud_itab__795[] = {
             0,        1079,
};

static const uint16_t ud_itab__796[] = {
             0,        1080,
};

static const uint16_t ud_itab__797[] = {
             0,        1081,
};

static const uint16_t ud_itab__798[] = {
             0,        1082,
};

static const uint16_t ud_itab__799[] = {
             0,        1083,
};

static const uint16_t ud_itab__800[] = {
             0,        1084,
};

static const uint16_t ud_itab__801[] = {
             0,        1085,
};

static const uint16_t ud_itab__802[] = {
             0,        1086,
};

static const uint16_t ud_itab__803[] = {
             0,        1087,
};

static const uint16_t ud_itab__804[] = {
             0,        1088,
};

static const uint16_t ud_itab__805[] = {
             0,        1089,
};

static const uint16_t ud_itab__772[] = {
    GROUP(773),  GROUP(774),  GROUP(775),  GROUP(776),
    GROUP(777),  GROUP(778),  GROUP(779),  GROUP(780),
    GROUP(781),  GROUP(782),  GROUP(783),  GROUP(784),
    GROUP(785),  GROUP(786),  GROUP(787),  GROUP(788),
    GROUP(789),  GROUP(790),  GROUP(791),  GROUP(792),
    GROUP(793),  GROUP(794),  GROUP(795),  GROUP(796),
    GROUP(797),  GROUP(798),  GROUP(799),  GROUP(800),
    GROUP(801),  GROUP(802),  GROUP(803),  GROUP(804),
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,  GROUP(805),           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__762[] = {
    GROUP(763),  GROUP(772),
};

static const uint16_t ud_itab__808[] = {
          1090,           0,
};

static const uint16_t ud_itab__809[] = {
          1091,           0,
};

static const uint16_t ud_itab__810[] = {
          1092,           0,
};

static const uint16_t ud_itab__811[] = {
          1093,           0,
};

static const uint16_t ud_itab__812[] = {
          1094,           0,
};

static const uint16_t ud_itab__813[] = {
          1095,           0,
};

static const uint16_t ud_itab__807[] = {
    GROUP(808),  GROUP(809),  GROUP(810),  GROUP(811),
             0,  GROUP(812),           0,  GROUP(813),
};

static const uint16_t ud_itab__815[] = {
             0,        1096,
};

static const uint16_t ud_itab__816[] = {
             0,        1097,
};

static const uint16_t ud_itab__817[] = {
             0,        1098,
};

static const uint16_t ud_itab__818[] = {
             0,        1099,
};

static const uint16_t ud_itab__819[] = {
             0,        1100,
};

static const uint16_t ud_itab__820[] = {
             0,        1101,
};

static const uint16_t ud_itab__821[] = {
             0,        1102,
};

static const uint16_t ud_itab__822[] = {
             0,        1103,
};

static const uint16_t ud_itab__823[] = {
             0,        1104,
};

static const uint16_t ud_itab__824[] = {
             0,        1105,
};

static const uint16_t ud_itab__825[] = {
             0,        1106,
};

static const uint16_t ud_itab__826[] = {
             0,        1107,
};

static const uint16_t ud_itab__827[] = {
             0,        1108,
};

static const uint16_t ud_itab__828[] = {
             0,        1109,
};

static const uint16_t ud_itab__829[] = {
             0,        1110,
};

static const uint16_t ud_itab__830[] = {
             0,        1111,
};

static const uint16_t ud_itab__831[] = {
             0,        1112,
};

static const uint16_t ud_itab__832[] = {
             0,        1113,
};

static const uint16_t ud_itab__833[] = {
             0,        1114,
};

static const uint16_t ud_itab__834[] = {
             0,        1115,
};

static const uint16_t ud_itab__835[] = {
             0,        1116,
};

static const uint16_t ud_itab__836[] = {
             0,        1117,
};

static const uint16_t ud_itab__837[] = {
             0,        1118,
};

static const uint16_t ud_itab__838[] = {
             0,        1119,
};

static const uint16_t ud_itab__839[] = {
             0,        1120,
};

static const uint16_t ud_itab__840[] = {
             0,        1121,
};

static const uint16_t ud_itab__841[] = {
             0,        1122,
};

static const uint16_t ud_itab__842[] = {
             0,        1123,
};

static const uint16_t ud_itab__843[] = {
             0,        1124,
};

static const uint16_t ud_itab__844[] = {
             0,        1125,
};

static const uint16_t ud_itab__845[] = {
             0,        1126,
};

static const uint16_t ud_itab__846[] = {
             0,        1127,
};

static const uint16_t ud_itab__847[] = {
             0,        1128,
};

static const uint16_t ud_itab__848[] = {
             0,        1129,
};

static const uint16_t ud_itab__849[] = {
             0,        1130,
};

static const uint16_t ud_itab__850[] = {
             0,        1131,
};

static const uint16_t ud_itab__851[] = {
             0,        1132,
};

static const uint16_t ud_itab__852[] = {
             0,        1133,
};

static const uint16_t ud_itab__853[] = {
             0,        1134,
};

static const uint16_t ud_itab__854[] = {
             0,        1135,
};

static const uint16_t ud_itab__855[] = {
             0,        1136,
};

static const uint16_t ud_itab__856[] = {
             0,        1137,
};

static const uint16_t ud_itab__857[] = {
             0,        1138,
};

static const uint16_t ud_itab__858[] = {
             0,        1139,
};

static const uint16_t ud_itab__859[] = {
             0,        1140,
};

static const uint16_t ud_itab__860[] = {
             0,        1141,
};

static const uint16_t ud_itab__861[] = {
             0,        1142,
};

static const uint16_t ud_itab__862[] = {
             0,        1143,
};

static const uint16_t ud_itab__863[] = {
             0,        1144,
};

static const uint16_t ud_itab__864[] = {
             0,        1145,
};

static const uint16_t ud_itab__814[] = {
    GROUP(815),  GROUP(816),  GROUP(817),  GROUP(818),
    GROUP(819),  GROUP(820),  GROUP(821),  GROUP(822),
    GROUP(823),  GROUP(824),  GROUP(825),  GROUP(826),
    GROUP(827),  GROUP(828),  GROUP(829),  GROUP(830),
    GROUP(831),  GROUP(832),  GROUP(833),  GROUP(834),
    GROUP(835),  GROUP(836),  GROUP(837),  GROUP(838),
    GROUP(839),  GROUP(840),  GROUP(841),  GROUP(842),
    GROUP(843),  GROUP(844),  GROUP(845),  GROUP(846),
             0,           0,  GROUP(847),  GROUP(848),
             0,           0,           0,           0,
    GROUP(849),  GROUP(850),  GROUP(851),  GROUP(852),
    GROUP(853),  GROUP(854),  GROUP(855),  GROUP(856),
    GROUP(857),  GROUP(858),  GROUP(859),  GROUP(860),
    GROUP(861),  GROUP(862),  GROUP(863),  GROUP(864),
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__806[] = {
    GROUP(807),  GROUP(814),
};

static const uint16_t ud_itab__867[] = {
          1146,           0,
};

static const uint16_t ud_itab__868[] = {
          1147,           0,
};

static const uint16_t ud_itab__869[] = {
          1148,           0,
};

static const uint16_t ud_itab__870[] = {
          1149,           0,
};

static const uint16_t ud_itab__871[] = {
          1150,           0,
};

static const uint16_t ud_itab__872[] = {
          1151,           0,
};

static const uint16_t ud_itab__873[] = {
          1152,           0,
};

static const uint16_t ud_itab__874[] = {
          1153,           0,
};

static const uint16_t ud_itab__866[] = {
    GROUP(867),  GROUP(868),  GROUP(869),  GROUP(870),
    GROUP(871),  GROUP(872),  GROUP(873),  GROUP(874),
};

static const uint16_t ud_itab__876[] = {
             0,        1154,
};

static const uint16_t ud_itab__877[] = {
             0,        1155,
};

static const uint16_t ud_itab__878[] = {
             0,        1156,
};

static const uint16_t ud_itab__879[] = {
             0,        1157,
};

static const uint16_t ud_itab__880[] = {
             0,        1158,
};

static const uint16_t ud_itab__881[] = {
             0,        1159,
};

static const uint16_t ud_itab__882[] = {
             0,        1160,
};

static const uint16_t ud_itab__883[] = {
             0,        1161,
};

static const uint16_t ud_itab__884[] = {
             0,        1162,
};

static const uint16_t ud_itab__885[] = {
             0,        1163,
};

static const uint16_t ud_itab__886[] = {
             0,        1164,
};

static const uint16_t ud_itab__887[] = {
             0,        1165,
};

static const uint16_t ud_itab__888[] = {
             0,        1166,
};

static const uint16_t ud_itab__889[] = {
             0,        1167,
};

static const uint16_t ud_itab__890[] = {
             0,        1168,
};

static const uint16_t ud_itab__891[] = {
             0,        1169,
};

static const uint16_t ud_itab__892[] = {
             0,        1170,
};

static const uint16_t ud_itab__893[] = {
             0,        1171,
};

static const uint16_t ud_itab__894[] = {
             0,        1172,
};

static const uint16_t ud_itab__895[] = {
             0,        1173,
};

static const uint16_t ud_itab__896[] = {
             0,        1174,
};

static const uint16_t ud_itab__897[] = {
             0,        1175,
};

static const uint16_t ud_itab__898[] = {
             0,        1176,
};

static const uint16_t ud_itab__899[] = {
             0,        1177,
};

static const uint16_t ud_itab__900[] = {
             0,        1178,
};

static const uint16_t ud_itab__901[] = {
             0,        1179,
};

static const uint16_t ud_itab__902[] = {
             0,        1180,
};

static const uint16_t ud_itab__903[] = {
             0,        1181,
};

static const uint16_t ud_itab__904[] = {
             0,        1182,
};

static const uint16_t ud_itab__905[] = {
             0,        1183,
};

static const uint16_t ud_itab__906[] = {
             0,        1184,
};

static const uint16_t ud_itab__907[] = {
             0,        1185,
};

static const uint16_t ud_itab__908[] = {
             0,        1186,
};

static const uint16_t ud_itab__909[] = {
             0,        1187,
};

static const uint16_t ud_itab__910[] = {
             0,        1188,
};

static const uint16_t ud_itab__911[] = {
             0,        1189,
};

static const uint16_t ud_itab__912[] = {
             0,        1190,
};

static const uint16_t ud_itab__913[] = {
             0,        1191,
};

static const uint16_t ud_itab__914[] = {
             0,        1192,
};

static const uint16_t ud_itab__915[] = {
             0,        1193,
};

static const uint16_t ud_itab__916[] = {
             0,        1194,
};

static const uint16_t ud_itab__917[] = {
             0,        1195,
};

static const uint16_t ud_itab__918[] = {
             0,        1196,
};

static const uint16_t ud_itab__919[] = {
             0,        1197,
};

static const uint16_t ud_itab__920[] = {
             0,        1198,
};

static const uint16_t ud_itab__921[] = {
             0,        1199,
};

static const uint16_t ud_itab__922[] = {
             0,        1200,
};

static const uint16_t ud_itab__923[] = {
             0,        1201,
};

static const uint16_t ud_itab__924[] = {
             0,        1202,
};

static const uint16_t ud_itab__925[] = {
             0,        1203,
};

static const uint16_t ud_itab__926[] = {
             0,        1204,
};

static const uint16_t ud_itab__927[] = {
             0,        1205,
};

static const uint16_t ud_itab__928[] = {
             0,        1206,
};

static const uint16_t ud_itab__929[] = {
             0,        1207,
};

static const uint16_t ud_itab__930[] = {
             0,        1208,
};

static const uint16_t ud_itab__931[] = {
             0,        1209,
};

static const uint16_t ud_itab__932[] = {
             0,        1210,
};

static const uint16_t ud_itab__933[] = {
             0,        1211,
};

static const uint16_t ud_itab__934[] = {
             0,        1212,
};

static const uint16_t ud_itab__935[] = {
             0,        1213,
};

static const uint16_t ud_itab__936[] = {
             0,        1214,
};

static const uint16_t ud_itab__937[] = {
             0,        1215,
};

static const uint16_t ud_itab__938[] = {
             0,        1216,
};

static const uint16_t ud_itab__939[] = {
             0,        1217,
};

static const uint16_t ud_itab__875[] = {
    GROUP(876),  GROUP(877),  GROUP(878),  GROUP(879),
    GROUP(880),  GROUP(881),  GROUP(882),  GROUP(883),
    GROUP(884),  GROUP(885),  GROUP(886),  GROUP(887),
    GROUP(888),  GROUP(889),  GROUP(890),  GROUP(891),
    GROUP(892),  GROUP(893),  GROUP(894),  GROUP(895),
    GROUP(896),  GROUP(897),  GROUP(898),  GROUP(899),
    GROUP(900),  GROUP(901),  GROUP(902),  GROUP(903),
    GROUP(904),  GROUP(905),  GROUP(906),  GROUP(907),
    GROUP(908),  GROUP(909),  GROUP(910),  GROUP(911),
    GROUP(912),  GROUP(913),  GROUP(914),  GROUP(915),
    GROUP(916),  GROUP(917),  GROUP(918),  GROUP(919),
    GROUP(920),  GROUP(921),  GROUP(922),  GROUP(923),
    GROUP(924),  GROUP(925),  GROUP(926),  GROUP(927),
    GROUP(928),  GROUP(929),  GROUP(930),  GROUP(931),
    GROUP(932),  GROUP(933),  GROUP(934),  GROUP(935),
    GROUP(936),  GROUP(937),  GROUP(938),  GROUP(939),
};

static const uint16_t ud_itab__865[] = {
    GROUP(866),  GROUP(875),
};

static const uint16_t ud_itab__942[] = {
          1218,           0,
};

static const uint16_t ud_itab__943[] = {
          1219,           0,
};

static const uint16_t ud_itab__944[] = {
          1220,           0,
};

static const uint16_t ud_itab__945[] = {
          1221,           0,
};

static const uint16_t ud_itab__946[] = {
          1222,           0,
};

static const uint16_t ud_itab__947[] = {
          1223,           0,
};

static const uint16_t ud_itab__948[] = {
          1224,           0,
};

static const uint16_t ud_itab__941[] = {
    GROUP(942),  GROUP(943),  GROUP(944),  GROUP(945),
    GROUP(946),           0,  GROUP(947),  GROUP(948),
};

static const uint16_t ud_itab__950[] = {
             0,        1225,
};

static const uint16_t ud_itab__951[] = {
             0,        1226,
};

static const uint16_t ud_itab__952[] = {
             0,        1227,
};

static const uint16_t ud_itab__953[] = {
             0,        1228,
};

static const uint16_t ud_itab__954[] = {
             0,        1229,
};

static const uint16_t ud_itab__955[] = {
             0,        1230,
};

static const uint16_t ud_itab__956[] = {
             0,        1231,
};

static const uint16_t ud_itab__957[] = {
             0,        1232,
};

static const uint16_t ud_itab__958[] = {
             0,        1233,
};

static const uint16_t ud_itab__959[] = {
             0,        1234,
};

static const uint16_t ud_itab__960[] = {
             0,        1235,
};

static const uint16_t ud_itab__961[] = {
             0,        1236,
};

static const uint16_t ud_itab__962[] = {
             0,        1237,
};

static const uint16_t ud_itab__963[] = {
             0,        1238,
};

static const uint16_t ud_itab__964[] = {
             0,        1239,
};

static const uint16_t ud_itab__965[] = {
             0,        1240,
};

static const uint16_t ud_itab__966[] = {
             0,        1241,
};

static const uint16_t ud_itab__967[] = {
             0,        1242,
};

static const uint16_t ud_itab__968[] = {
             0,        1243,
};

static const uint16_t ud_itab__969[] = {
             0,        1244,
};

static const uint16_t ud_itab__970[] = {
             0,        1245,
};

static const uint16_t ud_itab__971[] = {
             0,        1246,
};

static const uint16_t ud_itab__972[] = {
             0,        1247,
};

static const uint16_t ud_itab__973[] = {
             0,        1248,
};

static const uint16_t ud_itab__974[] = {
             0,        1249,
};

static const uint16_t ud_itab__975[] = {
             0,        1250,
};

static const uint16_t ud_itab__976[] = {
             0,        1251,
};

static const uint16_t ud_itab__977[] = {
             0,        1252,
};

static const uint16_t ud_itab__978[] = {
             0,        1253,
};

static const uint16_t ud_itab__979[] = {
             0,        1254,
};

static const uint16_t ud_itab__980[] = {
             0,        1255,
};

static const uint16_t ud_itab__981[] = {
             0,        1256,
};

static const uint16_t ud_itab__982[] = {
             0,        1257,
};

static const uint16_t ud_itab__983[] = {
             0,        1258,
};

static const uint16_t ud_itab__984[] = {
             0,        1259,
};

static const uint16_t ud_itab__985[] = {
             0,        1260,
};

static const uint16_t ud_itab__986[] = {
             0,        1261,
};

static const uint16_t ud_itab__987[] = {
             0,        1262,
};

static const uint16_t ud_itab__988[] = {
             0,        1263,
};

static const uint16_t ud_itab__989[] = {
             0,        1264,
};

static const uint16_t ud_itab__990[] = {
             0,        1265,
};

static const uint16_t ud_itab__991[] = {
             0,        1266,
};

static const uint16_t ud_itab__992[] = {
             0,        1267,
};

static const uint16_t ud_itab__993[] = {
             0,        1268,
};

static const uint16_t ud_itab__994[] = {
             0,        1269,
};

static const uint16_t ud_itab__995[] = {
             0,        1270,
};

static const uint16_t ud_itab__996[] = {
             0,        1271,
};

static const uint16_t ud_itab__997[] = {
             0,        1272,
};

static const uint16_t ud_itab__949[] = {
    GROUP(950),  GROUP(951),  GROUP(952),  GROUP(953),
    GROUP(954),  GROUP(955),  GROUP(956),  GROUP(957),
    GROUP(958),  GROUP(959),  GROUP(960),  GROUP(961),
    GROUP(962),  GROUP(963),  GROUP(964),  GROUP(965),
    GROUP(966),  GROUP(967),  GROUP(968),  GROUP(969),
    GROUP(970),  GROUP(971),  GROUP(972),  GROUP(973),
    GROUP(974),  GROUP(975),  GROUP(976),  GROUP(977),
    GROUP(978),  GROUP(979),  GROUP(980),  GROUP(981),
    GROUP(982),  GROUP(983),  GROUP(984),  GROUP(985),
    GROUP(986),  GROUP(987),  GROUP(988),  GROUP(989),
    GROUP(990),  GROUP(991),  GROUP(992),  GROUP(993),
    GROUP(994),  GROUP(995),  GROUP(996),  GROUP(997),
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__940[] = {
    GROUP(941),  GROUP(949),
};

static const uint16_t ud_itab__1000[] = {
          1273,           0,
};

static const uint16_t ud_itab__1001[] = {
          1274,           0,
};

static const uint16_t ud_itab__1002[] = {
          1275,           0,
};

static const uint16_t ud_itab__1003[] = {
          1276,           0,
};

static const uint16_t ud_itab__1004[] = {
          1277,           0,
};

static const uint16_t ud_itab__1005[] = {
          1278,           0,
};

static const uint16_t ud_itab__1006[] = {
          1279,           0,
};

static const uint16_t ud_itab__1007[] = {
          1280,           0,
};

static const uint16_t ud_itab__999[] = {
   GROUP(1000), GROUP(1001), GROUP(1002), GROUP(1003),
   GROUP(1004), GROUP(1005), GROUP(1006), GROUP(1007),
};

static const uint16_t ud_itab__1009[] = {
             0,        1281,
};

static const uint16_t ud_itab__1010[] = {
             0,        1282,
};

static const uint16_t ud_itab__1011[] = {
             0,        1283,
};

static const uint16_t ud_itab__1012[] = {
             0,        1284,
};

static const uint16_t ud_itab__1013[] = {
             0,        1285,
};

static const uint16_t ud_itab__1014[] = {
             0,        1286,
};

static const uint16_t ud_itab__1015[] = {
             0,        1287,
};

static const uint16_t ud_itab__1016[] = {
             0,        1288,
};

static const uint16_t ud_itab__1017[] = {
             0,        1289,
};

static const uint16_t ud_itab__1018[] = {
             0,        1290,
};

static const uint16_t ud_itab__1019[] = {
             0,        1291,
};

static const uint16_t ud_itab__1020[] = {
             0,        1292,
};

static const uint16_t ud_itab__1021[] = {
             0,        1293,
};

static const uint16_t ud_itab__1022[] = {
             0,        1294,
};

static const uint16_t ud_itab__1023[] = {
             0,        1295,
};

static const uint16_t ud_itab__1024[] = {
             0,        1296,
};

static const uint16_t ud_itab__1025[] = {
             0,        1297,
};

static const uint16_t ud_itab__1026[] = {
             0,        1298,
};

static const uint16_t ud_itab__1027[] = {
             0,        1299,
};

static const uint16_t ud_itab__1028[] = {
             0,        1300,
};

static const uint16_t ud_itab__1029[] = {
             0,        1301,
};

static const uint16_t ud_itab__1030[] = {
             0,        1302,
};

static const uint16_t ud_itab__1031[] = {
             0,        1303,
};

static const uint16_t ud_itab__1032[] = {
             0,        1304,
};

static const uint16_t ud_itab__1033[] = {
             0,        1305,
};

static const uint16_t ud_itab__1034[] = {
             0,        1306,
};

static const uint16_t ud_itab__1035[] = {
             0,        1307,
};

static const uint16_t ud_itab__1036[] = {
             0,        1308,
};

static const uint16_t ud_itab__1037[] = {
             0,        1309,
};

static const uint16_t ud_itab__1038[] = {
             0,        1310,
};

static const uint16_t ud_itab__1039[] = {
             0,        1311,
};

static const uint16_t ud_itab__1040[] = {
             0,        1312,
};

static const uint16_t ud_itab__1041[] = {
             0,        1313,
};

static const uint16_t ud_itab__1042[] = {
             0,        1314,
};

static const uint16_t ud_itab__1043[] = {
             0,        1315,
};

static const uint16_t ud_itab__1044[] = {
             0,        1316,
};

static const uint16_t ud_itab__1045[] = {
             0,        1317,
};

static const uint16_t ud_itab__1046[] = {
             0,        1318,
};

static const uint16_t ud_itab__1047[] = {
             0,        1319,
};

static const uint16_t ud_itab__1048[] = {
             0,        1320,
};

static const uint16_t ud_itab__1049[] = {
             0,        1321,
};

static const uint16_t ud_itab__1050[] = {
             0,        1322,
};

static const uint16_t ud_itab__1051[] = {
             0,        1323,
};

static const uint16_t ud_itab__1052[] = {
             0,        1324,
};

static const uint16_t ud_itab__1053[] = {
             0,        1325,
};

static const uint16_t ud_itab__1054[] = {
             0,        1326,
};

static const uint16_t ud_itab__1055[] = {
             0,        1327,
};

static const uint16_t ud_itab__1056[] = {
             0,        1328,
};

static const uint16_t ud_itab__1057[] = {
             0,        1329,
};

static const uint16_t ud_itab__1058[] = {
             0,        1330,
};

static const uint16_t ud_itab__1059[] = {
             0,        1331,
};

static const uint16_t ud_itab__1060[] = {
             0,        1332,
};

static const uint16_t ud_itab__1061[] = {
             0,        1333,
};

static const uint16_t ud_itab__1062[] = {
             0,        1334,
};

static const uint16_t ud_itab__1063[] = {
             0,        1335,
};

static const uint16_t ud_itab__1064[] = {
             0,        1336,
};

static const uint16_t ud_itab__1065[] = {
             0,        1337,
};

static const uint16_t ud_itab__1008[] = {
   GROUP(1009), GROUP(1010), GROUP(1011), GROUP(1012),
   GROUP(1013), GROUP(1014), GROUP(1015), GROUP(1016),
   GROUP(1017), GROUP(1018), GROUP(1019), GROUP(1020),
   GROUP(1021), GROUP(1022), GROUP(1023), GROUP(1024),
   GROUP(1025), GROUP(1026), GROUP(1027), GROUP(1028),
   GROUP(1029), GROUP(1030), GROUP(1031), GROUP(1032),
             0, GROUP(1033),           0,           0,
             0,           0,           0,           0,
   GROUP(1034), GROUP(1035), GROUP(1036), GROUP(1037),
   GROUP(1038), GROUP(1039), GROUP(1040), GROUP(1041),
   GROUP(1042), GROUP(1043), GROUP(1044), GROUP(1045),
   GROUP(1046), GROUP(1047), GROUP(1048), GROUP(1049),
   GROUP(1050), GROUP(1051), GROUP(1052), GROUP(1053),
   GROUP(1054), GROUP(1055), GROUP(1056), GROUP(1057),
   GROUP(1058), GROUP(1059), GROUP(1060), GROUP(1061),
   GROUP(1062), GROUP(1063), GROUP(1064), GROUP(1065),
};

static const uint16_t ud_itab__998[] = {
    GROUP(999), GROUP(1008),
};

static const uint16_t ud_itab__1068[] = {
          1338,           0,
};

static const uint16_t ud_itab__1069[] = {
          1339,           0,
};

static const uint16_t ud_itab__1070[] = {
          1340,           0,
};

static const uint16_t ud_itab__1071[] = {
          1341,           0,
};

static const uint16_t ud_itab__1072[] = {
          1342,           0,
};

static const uint16_t ud_itab__1073[] = {
          1343,           0,
};

static const uint16_t ud_itab__1074[] = {
          1344,           0,
};

static const uint16_t ud_itab__1075[] = {
          1345,           0,
};

static const uint16_t ud_itab__1067[] = {
   GROUP(1068), GROUP(1069), GROUP(1070), GROUP(1071),
   GROUP(1072), GROUP(1073), GROUP(1074), GROUP(1075),
};

static const uint16_t ud_itab__1077[] = {
             0,        1346,
};

static const uint16_t ud_itab__1078[] = {
             0,        1347,
};

static const uint16_t ud_itab__1079[] = {
             0,        1348,
};

static const uint16_t ud_itab__1080[] = {
             0,        1349,
};

static const uint16_t ud_itab__1081[] = {
             0,        1350,
};

static const uint16_t ud_itab__1082[] = {
             0,        1351,
};

static const uint16_t ud_itab__1083[] = {
             0,        1352,
};

static const uint16_t ud_itab__1084[] = {
             0,        1353,
};

static const uint16_t ud_itab__1085[] = {
             0,        1354,
};

static const uint16_t ud_itab__1086[] = {
             0,        1355,
};

static const uint16_t ud_itab__1087[] = {
             0,        1356,
};

static const uint16_t ud_itab__1088[] = {
             0,        1357,
};

static const uint16_t ud_itab__1089[] = {
             0,        1358,
};

static const uint16_t ud_itab__1090[] = {
             0,        1359,
};

static const uint16_t ud_itab__1091[] = {
             0,        1360,
};

static const uint16_t ud_itab__1092[] = {
             0,        1361,
};

static const uint16_t ud_itab__1093[] = {
             0,        1362,
};

static const uint16_t ud_itab__1094[] = {
             0,        1363,
};

static const uint16_t ud_itab__1095[] = {
             0,        1364,
};

static const uint16_t ud_itab__1096[] = {
             0,        1365,
};

static const uint16_t ud_itab__1097[] = {
             0,        1366,
};

static const uint16_t ud_itab__1098[] = {
             0,        1367,
};

static const uint16_t ud_itab__1099[] = {
             0,        1368,
};

static const uint16_t ud_itab__1100[] = {
             0,        1369,
};

static const uint16_t ud_itab__1101[] = {
             0,        1370,
};

static const uint16_t ud_itab__1102[] = {
             0,        1371,
};

static const uint16_t ud_itab__1103[] = {
             0,        1372,
};

static const uint16_t ud_itab__1104[] = {
             0,        1373,
};

static const uint16_t ud_itab__1105[] = {
             0,        1374,
};

static const uint16_t ud_itab__1106[] = {
             0,        1375,
};

static const uint16_t ud_itab__1107[] = {
             0,        1376,
};

static const uint16_t ud_itab__1108[] = {
             0,        1377,
};

static const uint16_t ud_itab__1109[] = {
             0,        1378,
};

static const uint16_t ud_itab__1110[] = {
             0,        1379,
};

static const uint16_t ud_itab__1111[] = {
             0,        1380,
};

static const uint16_t ud_itab__1112[] = {
             0,        1381,
};

static const uint16_t ud_itab__1113[] = {
             0,        1382,
};

static const uint16_t ud_itab__1114[] = {
             0,        1383,
};

static const uint16_t ud_itab__1115[] = {
             0,        1384,
};

static const uint16_t ud_itab__1116[] = {
             0,        1385,
};

static const uint16_t ud_itab__1117[] = {
             0,        1386,
};

static const uint16_t ud_itab__1118[] = {
             0,        1387,
};

static const uint16_t ud_itab__1119[] = {
             0,        1388,
};

static const uint16_t ud_itab__1120[] = {
             0,        1389,
};

static const uint16_t ud_itab__1121[] = {
             0,        1390,
};

static const uint16_t ud_itab__1122[] = {
             0,        1391,
};

static const uint16_t ud_itab__1123[] = {
             0,        1392,
};

static const uint16_t ud_itab__1124[] = {
             0,        1393,
};

static const uint16_t ud_itab__1125[] = {
             0,        1394,
};

static const uint16_t ud_itab__1076[] = {
   GROUP(1077), GROUP(1078), GROUP(1079), GROUP(1080),
   GROUP(1081), GROUP(1082), GROUP(1083), GROUP(1084),
   GROUP(1085), GROUP(1086), GROUP(1087), GROUP(1088),
   GROUP(1089), GROUP(1090), GROUP(1091), GROUP(1092),
   GROUP(1093), GROUP(1094), GROUP(1095), GROUP(1096),
   GROUP(1097), GROUP(1098), GROUP(1099), GROUP(1100),
   GROUP(1101), GROUP(1102), GROUP(1103), GROUP(1104),
   GROUP(1105), GROUP(1106), GROUP(1107), GROUP(1108),
   GROUP(1109),           0,           0,           0,
             0,           0,           0,           0,
   GROUP(1110), GROUP(1111), GROUP(1112), GROUP(1113),
   GROUP(1114), GROUP(1115), GROUP(1116), GROUP(1117),
   GROUP(1118), GROUP(1119), GROUP(1120), GROUP(1121),
   GROUP(1122), GROUP(1123), GROUP(1124), GROUP(1125),
             0,           0,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__1066[] = {
   GROUP(1067), GROUP(1076),
};

static const uint16_t ud_itab__1126[] = {
          1398,        1399,        1400,
};

static const uint16_t ud_itab__1127[] = {
          1407,           0,
};

static const uint16_t ud_itab__1128[] = {
          1419,        1420,        1421,        1422,
          1423,        1424,        1425,        1426,
};

static const uint16_t ud_itab__1129[] = {
          1427,        1428,        1429,        1430,
          1431,        1432,        1433,        1434,
};

static const uint16_t ud_itab__1130[] = {
          1441,        1442,           0,           0,
             0,           0,           0,           0,
};

static const uint16_t ud_itab__1132[] = {
          1445,        1446,
};

static const uint16_t ud_itab__1131[] = {
          1443,        1444, GROUP(1132),        1447,
          1448,        1449,        1450,           0,
};

const uint16_t ud_itab__0[] = {
             1,           2,           3,           4,
             5,           6,    GROUP(1),    GROUP(2),
             9,          10,          11,          12,
            13,          14,    GROUP(3),    GROUP(4),
           628,         629,         630,         631,
           632,         633,  GROUP(563),  GROUP(564),
           636,         637,         638,         639,
           640,         641,  GROUP(565),  GROUP(566),
           644,         645,         646,         647,
           648,         649,           0,  GROUP(567),
           651,         652,         653,         654,
           655,         656,           0,  GROUP(568),
           658,         659,         660,         661,
           662,         663,           0,  GROUP(569),
           665,         666,         667,         668,
           669,         670,           0,  GROUP(570),
           672,         673,         674,         675,
           676,         677,         678,         679,
           680,         681,         682,         683,
           684,         685,         686,         687,
           688,         689,         690,         691,
           692,         693,         694,         695,
           696,         697,         698,         699,
           700,         701,         702,         703,
    GROUP(571),  GROUP(574),  GROUP(577),  GROUP(578),
             0,           0,           0,           0,
           711,         712,         713,         714,
           715,  GROUP(579),         718,  GROUP(580),
           721,         722,         723,         724,
           725,         726,         727,         728,
           729,         730,         731,         732,
           733,         734,         735,         736,
    GROUP(581),  GROUP(582),  GROUP(583),  GROUP(592),
           769,         770,         771,         772,
           773,         774,         775,         776,
           777,         778,         779,  GROUP(593),
           781,         782,         783,         784,
           785,         786,         787,         788,
    GROUP(594),  GROUP(595),  GROUP(596),         796,
    GROUP(597),  GROUP(601),         806,         807,
           808,         809,         810,         811,
           812,  GROUP(605),         816,  GROUP(606),
           820,         821,         822,  GROUP(607),
           826,  GROUP(608),         830,  GROUP(609),
           834,         835,         836,         837,
           838,         839,         840,         841,
           842,         843,         844,         845,
           846,         847,         848,         849,
    GROUP(610),  GROUP(611),         866,         867,
    GROUP(612),  GROUP(613),  GROUP(614),  GROUP(615),
           872,         873,         874,         875,
           876,         877,  GROUP(616),  GROUP(617),
    GROUP(618),  GROUP(619),  GROUP(620),  GROUP(621),
    GROUP(622),  GROUP(623),  GROUP(624),         917,
    GROUP(625),  GROUP(700),  GROUP(762),  GROUP(806),
    GROUP(865),  GROUP(940),  GROUP(998), GROUP(1066),
          1395,        1396,        1397, GROUP(1126),
          1401,        1402,        1403,        1404,
          1405,        1406, GROUP(1127),        1408,
          1409,        1410,        1411,        1412,
          1413,        1414,        1415,        1416,
          1417,        1418, GROUP(1128), GROUP(1129),
          1435,        1436,        1437,        1438,
          1439,        1440, GROUP(1130), GROUP(1131),
};


struct ud_lookup_table_list_entry ud_lookup_table_list[] = {
     { ud_itab__0, UD_TAB__OPC_TABLE, "table0" },
     { ud_itab__1, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__2, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__3, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__4, UD_TAB__OPC_TABLE, "0f" },
     { ud_itab__5, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__6, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__7, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__8, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__9, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__10, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__11, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__12, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__13, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__14, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__15, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__16, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__17, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__18, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__19, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__20, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__21, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__22, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__23, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__24, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__25, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__26, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__27, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__28, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__29, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__30, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__31, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__32, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__33, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__34, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__35, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__36, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__37, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__38, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__39, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__40, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__41, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__42, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__43, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__44, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__45, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__46, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__47, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__48, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__49, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__50, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__51, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__52, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__53, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__54, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__55, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__56, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__57, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__58, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__59, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__60, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__61, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__62, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__63, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__64, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__65, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__66, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__67, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__68, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__69, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__70, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__71, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__72, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__73, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__74, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__75, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__76, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__77, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__78, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__79, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__80, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__81, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__82, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__83, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__84, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__85, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__86, UD_TAB__OPC_VENDOR, "amd" },
     { ud_itab__87, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__88, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__89, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__90, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__91, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__92, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__93, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__94, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__95, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__96, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__97, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__98, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__99, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__100, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__101, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__102, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__103, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__104, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__105, UD_TAB__OPC_3DNOW, "/3dnow" },
     { ud_itab__106, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__107, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__108, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__109, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__110, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__111, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__112, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__113, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__114, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__115, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__116, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__117, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__118, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__119, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__120, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__121, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__122, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__123, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__124, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__125, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__126, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__127, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__128, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__129, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__130, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__131, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__132, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__133, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__134, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__135, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__136, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__137, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__138, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__139, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__140, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__141, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__142, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__143, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__144, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__145, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__146, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__147, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__148, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__149, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__150, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__151, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__152, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__153, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__154, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__155, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__156, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__157, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__158, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__159, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__160, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__161, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__162, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__163, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__164, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__165, UD_TAB__OPC_TABLE, "38" },
     { ud_itab__166, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__167, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__168, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__169, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__170, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__171, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__172, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__173, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__174, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__175, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__176, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__177, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__178, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__179, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__180, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__181, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__182, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__183, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__184, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__185, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__186, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__187, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__188, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__189, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__190, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__191, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__192, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__193, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__194, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__195, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__196, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__197, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__198, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__199, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__200, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__201, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__202, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__203, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__204, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__205, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__206, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__207, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__208, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__209, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__210, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__211, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__212, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__213, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__214, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__215, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__216, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__217, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__218, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__219, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__220, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__221, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__222, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__223, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__224, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__225, UD_TAB__OPC_TABLE, "3a" },
     { ud_itab__226, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__227, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__228, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__229, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__230, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__231, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__232, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__233, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__234, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__235, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__236, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__237, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__238, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__239, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__240, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__241, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__242, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__243, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__244, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__245, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__246, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__247, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__248, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__249, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__250, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__251, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__252, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__253, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__254, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__255, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__256, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__257, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__258, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__259, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__260, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__261, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__262, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__263, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__264, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__265, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__266, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__267, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__268, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__269, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__270, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__271, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__272, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__273, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__274, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__275, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__276, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__277, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__278, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__279, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__280, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__281, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__282, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__283, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__284, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__285, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__286, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__287, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__288, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__289, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__290, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__291, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__292, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__293, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__294, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__295, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__296, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__297, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__298, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__299, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__300, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__301, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__302, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__303, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__304, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__305, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__306, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__307, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__308, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__309, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__310, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__311, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__312, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__313, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__314, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__315, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__316, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__317, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__318, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__319, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__320, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__321, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__322, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__323, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__324, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__325, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__326, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__327, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__328, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__329, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__330, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__331, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__332, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__333, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__334, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__335, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__336, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__337, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__338, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__339, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__340, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__341, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__342, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__343, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__344, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__345, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__346, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__347, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__348, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__349, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__350, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__351, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__352, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__353, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__354, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__355, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__356, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__357, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__358, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__359, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__360, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__361, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__362, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__363, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__364, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__365, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__366, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__367, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__368, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__369, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__370, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__371, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__372, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__373, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__374, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__375, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__376, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__377, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__378, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__379, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__380, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__381, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__382, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__383, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__384, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__385, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__386, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__387, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__388, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__389, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__390, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__391, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__392, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__393, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__394, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__395, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__396, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__397, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__398, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__399, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__400, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__401, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__402, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__403, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__404, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__405, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__406, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__407, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__408, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__409, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__410, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__411, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__412, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__413, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__414, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__415, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__416, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__417, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__418, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__419, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__420, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__421, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__422, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__423, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__424, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__425, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__426, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__427, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__428, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__429, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__430, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__431, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__432, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__433, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__434, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__435, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__436, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__437, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__438, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__439, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__440, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__441, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__442, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__443, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__444, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__445, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__446, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__447, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__448, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__449, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__450, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__451, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__452, UD_TAB__OPC_RM, "/rm" },
     { ud_itab__453, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__454, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__455, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__456, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__457, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__458, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__459, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__460, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__461, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__462, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__463, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__464, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__465, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__466, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__467, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__468, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__469, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__470, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__471, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__472, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__473, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__474, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__475, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__476, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__477, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__478, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__479, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__480, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__481, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__482, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__483, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__484, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__485, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__486, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__487, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__488, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__489, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__490, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__491, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__492, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__493, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__494, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__495, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__496, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__497, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__498, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__499, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__500, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__501, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__502, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__503, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__504, UD_TAB__OPC_VENDOR, "intel" },
     { ud_itab__505, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__506, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__507, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__508, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__509, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__510, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__511, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__512, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__513, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__514, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__515, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__516, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__517, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__518, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__519, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__520, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__521, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__522, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__523, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__524, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__525, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__526, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__527, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__528, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__529, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__530, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__531, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__532, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__533, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__534, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__535, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__536, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__537, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__538, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__539, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__540, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__541, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__542, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__543, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__544, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__545, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__546, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__547, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__548, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__549, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__550, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__551, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__552, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__553, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__554, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__555, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__556, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__557, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__558, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__559, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__560, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__561, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__562, UD_TAB__OPC_SSE, "/sse" },
     { ud_itab__563, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__564, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__565, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__566, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__567, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__568, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__569, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__570, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__571, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__572, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__573, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__574, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__575, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__576, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__577, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__578, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__579, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__580, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__581, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__582, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__583, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__584, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__585, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__586, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__587, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__588, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__589, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__590, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__591, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__592, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__593, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__594, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__595, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__596, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__597, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__598, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__599, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__600, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__601, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__602, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__603, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__604, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__605, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__606, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__607, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__608, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__609, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__610, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__611, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__612, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__613, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__614, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__615, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__616, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__617, UD_TAB__OPC_OSIZE, "/o" },
     { ud_itab__618, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__619, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__620, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__621, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__622, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__623, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__624, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__625, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__626, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__627, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__628, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__629, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__630, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__631, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__632, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__633, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__634, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__635, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__636, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__637, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__638, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__639, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__640, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__641, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__642, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__643, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__644, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__645, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__646, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__647, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__648, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__649, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__650, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__651, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__652, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__653, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__654, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__655, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__656, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__657, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__658, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__659, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__660, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__661, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__662, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__663, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__664, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__665, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__666, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__667, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__668, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__669, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__670, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__671, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__672, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__673, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__674, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__675, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__676, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__677, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__678, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__679, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__680, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__681, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__682, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__683, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__684, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__685, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__686, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__687, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__688, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__689, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__690, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__691, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__692, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__693, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__694, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__695, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__696, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__697, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__698, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__699, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__700, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__701, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__702, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__703, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__704, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__705, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__706, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__707, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__708, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__709, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__710, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__711, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__712, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__713, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__714, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__715, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__716, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__717, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__718, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__719, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__720, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__721, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__722, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__723, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__724, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__725, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__726, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__727, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__728, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__729, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__730, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__731, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__732, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__733, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__734, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__735, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__736, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__737, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__738, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__739, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__740, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__741, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__742, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__743, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__744, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__745, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__746, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__747, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__748, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__749, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__750, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__751, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__752, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__753, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__754, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__755, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__756, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__757, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__758, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__759, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__760, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__761, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__762, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__763, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__764, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__765, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__766, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__767, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__768, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__769, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__770, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__771, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__772, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__773, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__774, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__775, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__776, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__777, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__778, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__779, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__780, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__781, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__782, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__783, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__784, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__785, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__786, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__787, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__788, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__789, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__790, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__791, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__792, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__793, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__794, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__795, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__796, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__797, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__798, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__799, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__800, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__801, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__802, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__803, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__804, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__805, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__806, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__807, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__808, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__809, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__810, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__811, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__812, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__813, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__814, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__815, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__816, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__817, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__818, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__819, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__820, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__821, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__822, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__823, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__824, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__825, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__826, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__827, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__828, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__829, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__830, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__831, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__832, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__833, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__834, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__835, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__836, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__837, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__838, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__839, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__840, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__841, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__842, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__843, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__844, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__845, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__846, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__847, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__848, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__849, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__850, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__851, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__852, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__853, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__854, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__855, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__856, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__857, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__858, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__859, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__860, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__861, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__862, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__863, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__864, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__865, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__866, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__867, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__868, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__869, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__870, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__871, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__872, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__873, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__874, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__875, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__876, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__877, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__878, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__879, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__880, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__881, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__882, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__883, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__884, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__885, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__886, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__887, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__888, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__889, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__890, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__891, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__892, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__893, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__894, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__895, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__896, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__897, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__898, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__899, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__900, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__901, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__902, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__903, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__904, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__905, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__906, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__907, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__908, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__909, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__910, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__911, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__912, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__913, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__914, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__915, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__916, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__917, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__918, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__919, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__920, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__921, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__922, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__923, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__924, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__925, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__926, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__927, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__928, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__929, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__930, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__931, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__932, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__933, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__934, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__935, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__936, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__937, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__938, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__939, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__940, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__941, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__942, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__943, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__944, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__945, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__946, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__947, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__948, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__949, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__950, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__951, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__952, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__953, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__954, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__955, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__956, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__957, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__958, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__959, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__960, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__961, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__962, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__963, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__964, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__965, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__966, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__967, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__968, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__969, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__970, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__971, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__972, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__973, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__974, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__975, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__976, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__977, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__978, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__979, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__980, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__981, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__982, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__983, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__984, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__985, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__986, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__987, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__988, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__989, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__990, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__991, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__992, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__993, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__994, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__995, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__996, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__997, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__998, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__999, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1000, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1001, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1002, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1003, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1004, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1005, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1006, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1007, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1008, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__1009, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1010, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1011, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1012, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1013, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1014, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1015, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1016, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1017, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1018, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1019, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1020, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1021, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1022, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1023, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1024, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1025, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1026, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1027, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1028, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1029, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1030, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1031, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1032, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1033, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1034, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1035, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1036, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1037, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1038, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1039, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1040, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1041, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1042, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1043, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1044, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1045, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1046, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1047, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1048, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1049, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1050, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1051, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1052, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1053, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1054, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1055, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1056, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1057, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1058, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1059, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1060, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1061, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1062, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1063, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1064, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1065, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1066, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1067, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1068, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1069, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1070, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1071, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1072, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1073, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1074, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1075, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1076, UD_TAB__OPC_X87, "/x87" },
     { ud_itab__1077, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1078, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1079, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1080, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1081, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1082, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1083, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1084, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1085, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1086, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1087, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1088, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1089, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1090, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1091, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1092, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1093, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1094, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1095, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1096, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1097, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1098, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1099, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1100, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1101, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1102, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1103, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1104, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1105, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1106, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1107, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1108, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1109, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1110, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1111, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1112, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1113, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1114, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1115, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1116, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1117, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1118, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1119, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1120, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1121, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1122, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1123, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1124, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1125, UD_TAB__OPC_MOD, "/mod" },
     { ud_itab__1126, UD_TAB__OPC_ASIZE, "/a" },
     { ud_itab__1127, UD_TAB__OPC_MODE, "/m" },
     { ud_itab__1128, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1129, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1130, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1131, UD_TAB__OPC_REG, "/reg" },
     { ud_itab__1132, UD_TAB__OPC_MODE, "/m" },
};

#define O_AL      { OP_AL,       SZ_B     }
#define O_AX      { OP_AX,       SZ_W     }
#define O_Av      { OP_A,        SZ_V     }
#define O_C       { OP_C,        SZ_NA    }
#define O_CL      { OP_CL,       SZ_B     }
#define O_CS      { OP_CS,       SZ_NA    }
#define O_CX      { OP_CX,       SZ_W     }
#define O_D       { OP_D,        SZ_NA    }
#define O_DL      { OP_DL,       SZ_B     }
#define O_DS      { OP_DS,       SZ_NA    }
#define O_DX      { OP_DX,       SZ_W     }
#define O_E       { OP_E,        SZ_NA    }
#define O_ES      { OP_ES,       SZ_NA    }
#define O_Eb      { OP_E,        SZ_B     }
#define O_Ed      { OP_E,        SZ_D     }
#define O_Eq      { OP_E,        SZ_Q     }
#define O_Ev      { OP_E,        SZ_V     }
#define O_Ew      { OP_E,        SZ_W     }
#define O_Ey      { OP_E,        SZ_Y     }
#define O_Ez      { OP_E,        SZ_Z     }
#define O_FS      { OP_FS,       SZ_NA    }
#define O_Fv      { OP_F,        SZ_V     }
#define O_G       { OP_G,        SZ_NA    }
#define O_GS      { OP_GS,       SZ_NA    }
#define O_Gb      { OP_G,        SZ_B     }
#define O_Gd      { OP_G,        SZ_D     }
#define O_Gq      { OP_G,        SZ_Q     }
#define O_Gv      { OP_G,        SZ_V     }
#define O_Gw      { OP_G,        SZ_W     }
#define O_Gy      { OP_G,        SZ_Y     }
#define O_Gz      { OP_G,        SZ_Z     }
#define O_I1      { OP_I1,       SZ_NA    }
#define O_I3      { OP_I3,       SZ_NA    }
#define O_Ib      { OP_I,        SZ_B     }
#define O_Iv      { OP_I,        SZ_V     }
#define O_Iw      { OP_I,        SZ_W     }
#define O_Iz      { OP_I,        SZ_Z     }
#define O_Jb      { OP_J,        SZ_B     }
#define O_Jv      { OP_J,        SZ_V     }
#define O_Jz      { OP_J,        SZ_Z     }
#define O_M       { OP_M,        SZ_NA    }
#define O_Mb      { OP_M,        SZ_B     }
#define O_MbRd    { OP_MR,       SZ_BD    }
#define O_MbRv    { OP_MR,       SZ_BV    }
#define O_Md      { OP_M,        SZ_D     }
#define O_MdRy    { OP_MR,       SZ_DY    }
#define O_MdU     { OP_MU,       SZ_DO    }
#define O_Mo      { OP_M,        SZ_O     }
#define O_Mq      { OP_M,        SZ_Q     }
#define O_MqU     { OP_MU,       SZ_QO    }
#define O_Ms      { OP_M,        SZ_W     }
#define O_Mt      { OP_M,        SZ_T     }
#define O_Mv      { OP_M,        SZ_V     }
#define O_Mw      { OP_M,        SZ_W     }
#define O_MwRd    { OP_MR,       SZ_WD    }
#define O_MwRv    { OP_MR,       SZ_WV    }
#define O_MwRy    { OP_MR,       SZ_WY    }
#define O_MwU     { OP_MU,       SZ_WO    }
#define O_N       { OP_N,        SZ_Q     }
#define O_NONE    { OP_NONE,     SZ_NA    }
#define O_Ob      { OP_O,        SZ_B     }
#define O_Ov      { OP_O,        SZ_V     }
#define O_Ow      { OP_O,        SZ_W     }
#define O_P       { OP_P,        SZ_Q     }
#define O_Q       { OP_Q,        SZ_Q     }
#define O_R       { OP_R,        SZ_RDQ   }
#define O_R0b     { OP_R0,       SZ_B     }
#define O_R0v     { OP_R0,       SZ_V     }
#define O_R0w     { OP_R0,       SZ_W     }
#define O_R0y     { OP_R0,       SZ_Y     }
#define O_R0z     { OP_R0,       SZ_Z     }
#define O_R1b     { OP_R1,       SZ_B     }
#define O_R1v     { OP_R1,       SZ_V     }
#define O_R1w     { OP_R1,       SZ_W     }
#define O_R1y     { OP_R1,       SZ_Y     }
#define O_R1z     { OP_R1,       SZ_Z     }
#define O_R2b     { OP_R2,       SZ_B     }
#define O_R2v     { OP_R2,       SZ_V     }
#define O_R2w     { OP_R2,       SZ_W     }
#define O_R2y     { OP_R2,       SZ_Y     }
#define O_R2z     { OP_R2,       SZ_Z     }
#define O_R3b     { OP_R3,       SZ_B     }
#define O_R3v     { OP_R3,       SZ_V     }
#define O_R3w     { OP_R3,       SZ_W     }
#define O_R3y     { OP_R3,       SZ_Y     }
#define O_R3z     { OP_R3,       SZ_Z     }
#define O_R4b     { OP_R4,       SZ_B     }
#define O_R4v     { OP_R4,       SZ_V     }
#define O_R4w     { OP_R4,       SZ_W     }
#define O_R4y     { OP_R4,       SZ_Y     }
#define O_R4z     { OP_R4,       SZ_Z     }
#define O_R5b     { OP_R5,       SZ_B     }
#define O_R5v     { OP_R5,       SZ_V     }
#define O_R5w     { OP_R5,       SZ_W     }
#define O_R5y     { OP_R5,       SZ_Y     }
#define O_R5z     { OP_R5,       SZ_Z     }
#define O_R6b     { OP_R6,       SZ_B     }
#define O_R6v     { OP_R6,       SZ_V     }
#define O_R6w     { OP_R6,       SZ_W     }
#define O_R6y     { OP_R6,       SZ_Y     }
#define O_R6z     { OP_R6,       SZ_Z     }
#define O_R7b     { OP_R7,       SZ_B     }
#define O_R7v     { OP_R7,       SZ_V     }
#define O_R7w     { OP_R7,       SZ_W     }
#define O_R7y     { OP_R7,       SZ_Y     }
#define O_R7z     { OP_R7,       SZ_Z     }
#define O_S       { OP_S,        SZ_NA    }
#define O_SS      { OP_SS,       SZ_NA    }
#define O_ST0     { OP_ST0,      SZ_NA    }
#define O_ST1     { OP_ST1,      SZ_NA    }
#define O_ST2     { OP_ST2,      SZ_NA    }
#define O_ST3     { OP_ST3,      SZ_NA    }
#define O_ST4     { OP_ST4,      SZ_NA    }
#define O_ST5     { OP_ST5,      SZ_NA    }
#define O_ST6     { OP_ST6,      SZ_NA    }
#define O_ST7     { OP_ST7,      SZ_NA    }
#define O_U       { OP_U,        SZ_O     }
#define O_V       { OP_V,        SZ_O     }
#define O_W       { OP_W,        SZ_O     }
#define O_eAX     { OP_eAX,      SZ_Z     }
#define O_eCX     { OP_eCX,      SZ_Z     }
#define O_eDX     { OP_eDX,      SZ_Z     }
#define O_rAX     { OP_rAX,      SZ_V     }
#define O_rCX     { OP_rCX,      SZ_V     }
#define O_rDX     { OP_rDX,      SZ_V     }
#define O_sIb     { OP_sI,       SZ_B     }
#define O_sIv     { OP_sI,       SZ_V     }
#define O_sIz     { OP_sI,       SZ_Z     }

struct ud_itab_entry ud_itab[] = {
   { UD_Iinvalid, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iadd, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_AL, O_Ib, O_NONE, P_none },
   { UD_Iadd, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Ipush, O_ES, O_NONE, O_NONE, P_inv64 },
   { UD_Ipop, O_ES, O_NONE, O_NONE, P_inv64 },
   { UD_Ior, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_AL, O_Ib, O_NONE, P_none },
   { UD_Ior, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Ipush, O_CS, O_NONE, O_NONE, P_inv64 },
   { UD_Isldt, O_MwRv, O_NONE, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Istr, O_MwRv, O_NONE, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Illdt, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iltr, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iverr, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iverw, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isgdt, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isidt, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ilgdt, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ilidt, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ismsw, O_MwRv, O_NONE, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ilmsw, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iinvlpg, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ivmcall, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmlaunch, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmresume, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmxoff, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imonitor, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imwait, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixgetbv, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixsetbv, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmrun, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmmcall, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmload, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmsave, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Istgi, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iclgi, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iskinit, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iinvlpga, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ismsw, O_MwRv, O_NONE, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ilmsw, O_Ew, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iswapgs, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irdtscp, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilar, O_Gv, O_Ew, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilsl, O_Gv, O_Ew, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isyscall, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iclts, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isysret, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iinvd, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iwbinvd, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iud2, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetch, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ifemms, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ipi2fw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipi2fd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipf2iw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipf2id, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfnacc, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfpnacc, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfcmpge, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfmin, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfrcp, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfrsqrt, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfsub, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfadd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfcmpgt, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfmax, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfrcpit1, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfrsqit1, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfsubr, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfacc, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfcmpeq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfmul, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipfrcpit2, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhrw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipswapd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipavgusb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovups, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovsd, O_V, O_W, O_NONE, P_str|P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovupd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovups, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovsd, O_W, O_V, O_NONE, P_str|P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovss, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovupd, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovlps, O_V, O_M, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovddup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovsldup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovlpd, O_V, O_M, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovhlps, O_V, O_U, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovddup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovsldup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovlps, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovlpd, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iunpcklps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iunpcklpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iunpckhps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iunpckhpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovhps, O_V, O_M, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovshdup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovhpd, O_V, O_M, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovlhps, O_V, O_U, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovshdup, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovhps, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovhpd, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetchnta, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetcht0, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetcht1, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iprefetcht2, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Inop, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_R, O_C, O_NONE, P_rexr|P_rexw|P_rexb },
   { UD_Imov, O_R, O_D, O_NONE, P_rexr|P_rexw|P_rexb },
   { UD_Imov, O_C, O_R, O_NONE, P_rexr|P_rexw|P_rexb },
   { UD_Imov, O_D, O_R, O_NONE, P_rexr|P_rexw|P_rexb },
   { UD_Imovaps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovapd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovaps, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovapd, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtpi2ps, O_V, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtsi2sd, O_V, O_Ey, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvtsi2ss, O_V, O_Ey, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvtpi2pd, O_V, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovntps, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovntpd, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvttps2pi, O_P, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvttsd2si, O_Gy, O_W, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvttss2si, O_Gy, O_W, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvttpd2pi, O_P, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtps2pi, O_P, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtsd2si, O_Gy, O_W, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvtss2si, O_Gy, O_W, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icvtpd2pi, O_P, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iucomiss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iucomisd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icomiss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icomisd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iwrmsr, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irdtsc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irdmsr, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irdpmc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isysenter, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isysenter, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isysexit, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isysexit, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Igetsec, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ipshufb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipshufb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphaddsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaddubsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaddubsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphsubsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsignd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhrsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhrsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipblendvb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iblendvps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iblendvpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iptest, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipabsb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipabsb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipabsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipabsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipabsd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipabsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmovsxbw, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovsxbd, O_V, O_MdU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovsxbq, O_V, O_MwU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovsxwd, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovsxwq, O_V, O_MdU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovsxdq, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmuldq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Imovntdqa, O_V, O_Mo, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipackusdw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxbw, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxbd, O_V, O_MdU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxbq, O_V, O_MwU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxwd, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxwq, O_V, O_MdU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipmovzxdq, O_V, O_MqU, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipcmpgtq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipminsb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminuw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminud, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxsb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxuw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxud, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulld, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iphminposuw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iinvept, O_Gq, O_Mo, O_NONE, P_none },
   { UD_Iinvvpid, O_Gq, O_Mo, O_NONE, P_none },
   { UD_Iaesimc, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaesenc, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaesenclast, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaesdec, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaesdeclast, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovbe, O_Gv, O_Mv, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Icrc32, O_Gy, O_Eb, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Imovbe, O_Mv, O_Gv, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Icrc32, O_Gy, O_Ev, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Iroundps, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iroundpd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iroundss, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iroundsd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iblendps, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iblendpd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipblendw, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipalignr, O_P, O_Q, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipalignr, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipextrb, O_MbRv, O_V, O_Ib, P_aso|P_rexx|P_rexr|P_rexb|P_def64 },
   { UD_Ipextrw, O_MwRd, O_V, O_Ib, P_aso|P_rexx|P_rexr|P_rexb },
   { UD_Ipextrd, O_Ed, O_V, O_Ib, P_aso|P_rexr|P_rexx|P_rexw|P_rexb },
   { UD_Ipextrd, O_Ed, O_V, O_Ib, P_aso|P_rexr|P_rexx|P_rexw|P_rexb },
   { UD_Ipextrq, O_Eq, O_V, O_Ib, P_aso|P_rexr|P_rexw|P_rexb|P_def64 },
   { UD_Iextractps, O_MdRy, O_V, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipinsrb, O_V, O_MbRd, O_Ib, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iinsertps, O_V, O_Md, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipinsrd, O_V, O_Ed, O_Ib, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipinsrd, O_V, O_Ed, O_Ib, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipinsrq, O_V, O_Eq, O_Ib, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Idpps, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Idppd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Impsadbw, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipclmulqdq, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpestrm, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipcmpestri, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipcmpistrm, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ipcmpistri, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Iaeskeygenassist, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmovo, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovno, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovb, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovae, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovz, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovnz, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovbe, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmova, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovs, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovns, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovp, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovnp, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovl, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovge, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovle, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmovg, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovmskps, O_Gd, O_U, O_NONE, P_oso|P_rexr|P_rexb },
   { UD_Imovmskpd, O_Gd, O_U, O_NONE, P_oso|P_rexr|P_rexb },
   { UD_Isqrtps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isqrtsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isqrtss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isqrtpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Irsqrtps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Irsqrtss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ircpps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ircpss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iandps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iandpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iandnps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iandnpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iorps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iorpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixorps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixorpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaddps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaddsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaddss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaddpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imulps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imulsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imulss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imulpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtps2pd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtsd2ss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtss2sd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtpd2ps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtdq2ps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvttps2dq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtps2dq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isubps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isubsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isubss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isubpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iminps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iminsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iminss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iminpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Idivps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Idivsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Idivss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Idivpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaxps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaxsd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaxss, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaxpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpcklbw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpcklbw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpcklwd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpcklwd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckldq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckldq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipacksswb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipacksswb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpgtd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipackuswb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipackuswb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhbw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhbw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhwd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhwd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhdq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhdq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipackssdw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipackssdw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpcklqdq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipunpckhqdq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovd, O_P, O_Ey, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovd, O_V, O_Ey, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovdqu, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovdqa, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipshufw, O_P, O_Q, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipshuflw, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipshufhw, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipshufd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrlw, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsrlw, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsraw, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsraw, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsllw, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsllw, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsrld, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsrld, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsrad, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsrad, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipslld, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipslld, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsrlq, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsrlq, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsrldq, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipsllq, O_N, O_Ib, O_NONE, P_none },
   { UD_Ipsllq, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipslldq, O_U, O_Ib, O_NONE, P_rexb },
   { UD_Ipcmpeqb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipcmpeqd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iemms, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ivmread, O_Ey, O_Gy, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ivmwrite, O_Gy, O_Ey, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ihaddps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ihaddpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ihsubps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ihsubpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovd, O_Ey, O_P, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovd, O_Ey, O_V, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovq, O_Q, O_P, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovdqu, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovdqa, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ijo, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijno, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijb, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijae, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijz, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijnz, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijbe, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ija, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijs, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijns, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijp, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijnp, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijl, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijge, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijle, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijg, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Iseto, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetno, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetb, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetae, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetz, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetnz, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetbe, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iseta, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isets, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetns, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetp, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetnp, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetl, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetge, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetle, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isetg, O_Eb, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipush, O_FS, O_NONE, O_NONE, P_none },
   { UD_Ipop, O_FS, O_NONE, O_NONE, P_none },
   { UD_Icpuid, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ibt, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishld, O_Ev, O_Gv, O_Ib, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishld, O_Ev, O_Gv, O_CL, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imontmul, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixsha1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixsha256, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixstore, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixcryptecb, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixcryptcbc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixcryptctr, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixcryptcfb, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ixcryptofb, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ipush, O_GS, O_NONE, O_NONE, P_none },
   { UD_Ipop, O_GS, O_NONE, O_NONE, P_none },
   { UD_Irsm, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ibts, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishrd, O_Ev, O_Gv, O_Ib, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishrd, O_Ev, O_Gv, O_CL, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ifxsave, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ifxrstor, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ildmxcsr, O_Md, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Istmxcsr, O_Md, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixsave, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixrstor, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iclflush, O_M, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isfence, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iimul, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmpxchg, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpxchg, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilss, O_Gv, O_M, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibtr, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilfs, O_Gz, O_M, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilgs, O_Gz, O_M, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovzx, O_Gv, O_Eb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovzx, O_Gy, O_Ew, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipopcnt, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexr|P_rexw|P_rexx|P_rexb },
   { UD_Ibt, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibts, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibtr, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibtc, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibtc, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibsf, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ibsr, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovsx, O_Gv, O_Eb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imovsx, O_Gy, O_Ew, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixadd, O_Eb, O_Gb, O_NONE, P_aso|P_oso|P_rexr|P_rexx|P_rexb },
   { UD_Ixadd, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmpps, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpsd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpss, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmppd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovnti, O_M, O_Gy, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipinsrw, O_P, O_MwRy, O_Ib, P_aso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ipinsrw, O_V, O_MwRy, O_Ib, P_aso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ipextrw, O_Gd, O_N, O_Ib, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipextrw, O_Gd, O_U, O_Ib, P_aso|P_rexr|P_rexb },
   { UD_Ishufps, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ishufpd, O_V, O_W, O_Ib, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpxchg8b, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpxchg8b, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmpxchg16b, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ivmptrld, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ivmxon, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ivmclear, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ivmptrst, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ibswap, O_R0y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R1y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R2y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R3y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R4y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R5y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R6y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ibswap, O_R7y, O_NONE, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Iaddsubps, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iaddsubpd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrlw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrlw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrld, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrld, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrlq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrlq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmullw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmullw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovdq2q, O_P, O_U, O_NONE, P_aso|P_rexb },
   { UD_Imovq2dq, O_V, O_N, O_NONE, P_aso|P_rexr },
   { UD_Imovq, O_W, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmovmskb, O_Gd, O_N, O_NONE, P_oso|P_rexr|P_rexb },
   { UD_Ipmovmskb, O_Gd, O_U, O_NONE, P_rexr|P_rexb },
   { UD_Ipsubusb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubusb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubusw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubusw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminub, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminub, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipand, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipand, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddusb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddusb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddusw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddusw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxub, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxub, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipandn, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipandn, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipavgb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipavgb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsraw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsraw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrad, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsrad, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipavgw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipavgw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhuw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhuw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmulhw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtpd2dq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvtdq2pd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icvttpd2dq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovntq, O_M, O_P, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imovntdq, O_M, O_V, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubsb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubsb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipminsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipor, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipor, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddsb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddsb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxsw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaxsw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipxor, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipxor, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ilddqu, O_V, O_M, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsllw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsllw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipslld, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipslld, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsllq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsllq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmuludq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmuludq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaddwd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipmaddwd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsadbw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsadbw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaskmovq, O_P, O_N, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imaskmovdqu, O_V, O_U, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubq, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipsubq, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddb, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddb, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddw, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddw, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddd, O_P, O_Q, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ipaddd, O_V, O_W, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_AL, O_Ib, O_NONE, P_none },
   { UD_Iadc, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Ipush, O_SS, O_NONE, O_NONE, P_inv64 },
   { UD_Ipop, O_SS, O_NONE, O_NONE, P_inv64 },
   { UD_Isbb, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_AL, O_Ib, O_NONE, P_none },
   { UD_Isbb, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Ipush, O_DS, O_NONE, O_NONE, P_inv64 },
   { UD_Ipop, O_DS, O_NONE, O_NONE, P_inv64 },
   { UD_Iand, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_AL, O_Ib, O_NONE, P_none },
   { UD_Iand, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Idaa, O_NONE, O_NONE, O_NONE, P_inv64 },
   { UD_Isub, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_AL, O_Ib, O_NONE, P_none },
   { UD_Isub, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Idas, O_NONE, O_NONE, O_NONE, P_inv64 },
   { UD_Ixor, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_AL, O_Ib, O_NONE, P_none },
   { UD_Ixor, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Iaaa, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Icmp, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_AL, O_Ib, O_NONE, P_none },
   { UD_Icmp, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Iaas, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iinc, O_R0z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R1z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R2z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R3z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R4z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R5z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R6z, O_NONE, O_NONE, P_oso },
   { UD_Iinc, O_R7z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R0z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R1z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R2z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R3z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R4z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R5z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R6z, O_NONE, O_NONE, P_oso },
   { UD_Idec, O_R7z, O_NONE, O_NONE, P_oso },
   { UD_Ipush, O_R0v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R1v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R2v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R3v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R4v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R5v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R6v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipush, O_R7v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R0v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R1v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R2v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R3v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R4v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R5v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R6v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipop, O_R7v, O_NONE, O_NONE, P_oso|P_rexb|P_def64 },
   { UD_Ipusha, O_NONE, O_NONE, O_NONE, P_oso|P_inv64 },
   { UD_Ipushad, O_NONE, O_NONE, O_NONE, P_oso|P_inv64 },
   { UD_Ipopa, O_NONE, O_NONE, O_NONE, P_oso|P_inv64 },
   { UD_Ipopad, O_NONE, O_NONE, O_NONE, P_oso|P_inv64 },
   { UD_Ibound, O_Gv, O_M, O_NONE, P_aso|P_oso },
   { UD_Iarpl, O_Ew, O_Gw, O_NONE, P_aso },
   { UD_Imovsxd, O_Gq, O_Ed, O_NONE, P_aso|P_oso|P_rexw|P_rexx|P_rexr|P_rexb },
   { UD_Ipush, O_sIz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Iimul, O_Gv, O_Ev, O_Iz, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipush, O_sIb, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Iimul, O_Gv, O_Ev, O_sIb, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iinsb, O_NONE, O_NONE, O_NONE, P_str|P_seg },
   { UD_Iinsw, O_NONE, O_NONE, O_NONE, P_str|P_oso|P_seg },
   { UD_Iinsd, O_NONE, O_NONE, O_NONE, P_str|P_oso|P_seg },
   { UD_Ioutsb, O_NONE, O_NONE, O_NONE, P_str|P_seg },
   { UD_Ioutsw, O_NONE, O_NONE, O_NONE, P_str|P_oso|P_seg },
   { UD_Ioutsd, O_NONE, O_NONE, O_NONE, P_str|P_oso|P_seg },
   { UD_Ijo, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijno, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijb, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijae, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijz, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijnz, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijbe, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ija, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijs, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijns, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijp, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijnp, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijl, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijge, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijle, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijg, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Iadd, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadd, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Ior, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Isbb, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Iand, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Isub, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Ixor, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Icmp, O_Eb, O_Ib, O_NONE, P_aso|P_rexr|P_rexx|P_rexb|P_inv64 },
   { UD_Iadd, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ior, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iadc, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isbb, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iand, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isub, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixor, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icmp, O_Ev, O_sIb, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Itest, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Itest, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ixchg, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ixchg, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_Eb, O_Gb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_Ev, O_Gv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_Gb, O_Eb, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_Gv, O_Ev, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_MwRv, O_S, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ilea, O_Gv, O_M, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_S, O_MwRv, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipop, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ixchg, O_R0v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R1v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R2v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R3v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R4v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R5v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R6v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Ixchg, O_R7v, O_rAX, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Icbw, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icwde, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icdqe, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icwd, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icdq, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icqo, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Icall, O_Av, O_NONE, O_NONE, P_oso },
   { UD_Iwait, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ipushfw, O_NONE, O_NONE, O_NONE, P_oso },
   { UD_Ipushfw, O_NONE, O_NONE, O_NONE, P_oso|P_rexw|P_def64 },
   { UD_Ipushfd, O_NONE, O_NONE, O_NONE, P_oso },
   { UD_Ipushfq, O_NONE, O_NONE, O_NONE, P_oso|P_rexw|P_def64 },
   { UD_Ipushfq, O_NONE, O_NONE, O_NONE, P_oso|P_rexw|P_def64 },
   { UD_Ipopfw, O_NONE, O_NONE, O_NONE, P_oso },
   { UD_Ipopfd, O_NONE, O_NONE, O_NONE, P_oso },
   { UD_Ipopfq, O_NONE, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ipopfq, O_NONE, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Isahf, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ilahf, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Imov, O_AL, O_Ob, O_NONE, P_none },
   { UD_Imov, O_rAX, O_Ov, O_NONE, P_aso|P_oso|P_rexw },
   { UD_Imov, O_Ob, O_AL, O_NONE, P_none },
   { UD_Imov, O_Ov, O_rAX, O_NONE, P_aso|P_oso|P_rexw },
   { UD_Imovsb, O_NONE, O_NONE, O_NONE, P_str|P_seg },
   { UD_Imovsw, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Imovsd, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Imovsq, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Icmpsb, O_NONE, O_NONE, O_NONE, P_strz|P_seg },
   { UD_Icmpsw, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw|P_seg },
   { UD_Icmpsd, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw|P_seg },
   { UD_Icmpsq, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw|P_seg },
   { UD_Itest, O_AL, O_Ib, O_NONE, P_none },
   { UD_Itest, O_rAX, O_sIz, O_NONE, P_oso|P_rexw },
   { UD_Istosb, O_NONE, O_NONE, O_NONE, P_str|P_seg },
   { UD_Istosw, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Istosd, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Istosq, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Ilodsb, O_NONE, O_NONE, O_NONE, P_str|P_seg },
   { UD_Ilodsw, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Ilodsd, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Ilodsq, O_NONE, O_NONE, O_NONE, P_str|P_seg|P_oso|P_rexw },
   { UD_Iscasb, O_NONE, O_NONE, O_NONE, P_strz },
   { UD_Iscasw, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw },
   { UD_Iscasd, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw },
   { UD_Iscasq, O_NONE, O_NONE, O_NONE, P_strz|P_oso|P_rexw },
   { UD_Imov, O_R0b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R1b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R2b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R3b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R4b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R5b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R6b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R7b, O_Ib, O_NONE, P_rexb },
   { UD_Imov, O_R0v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R1v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R2v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R3v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R4v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R5v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R6v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Imov, O_R7v, O_Iv, O_NONE, P_oso|P_rexw|P_rexb },
   { UD_Irol, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Irol, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Ev, O_Ib, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iret, O_Iw, O_NONE, O_NONE, P_none },
   { UD_Iret, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iles, O_Gv, O_M, O_NONE, P_aso|P_oso },
   { UD_Ilds, O_Gv, O_M, O_NONE, P_aso|P_oso },
   { UD_Imov, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imov, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ienter, O_Iw, O_Ib, O_NONE, P_def64 },
   { UD_Ileave, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iretf, O_Iw, O_NONE, O_NONE, P_none },
   { UD_Iretf, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iint3, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iint, O_Ib, O_NONE, O_NONE, P_none },
   { UD_Iinto, O_NONE, O_NONE, O_NONE, P_inv64 },
   { UD_Iiretw, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Iiretd, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Iiretq, O_NONE, O_NONE, O_NONE, P_oso|P_rexw },
   { UD_Irol, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Eb, O_I1, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Irol, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Ev, O_I1, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Irol, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_CL, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Eb, O_CL, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Irol, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iror, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircl, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ircr, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishr, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ishl, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Isar, O_Ev, O_CL, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iaam, O_Ib, O_NONE, O_NONE, P_none },
   { UD_Iaad, O_Ib, O_NONE, O_NONE, P_none },
   { UD_Isalc, O_NONE, O_NONE, O_NONE, P_inv64 },
   { UD_Ixlatb, O_NONE, O_NONE, O_NONE, P_rexw|P_seg },
   { UD_Ifadd, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifmul, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcom, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcomp, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifsub, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifsubr, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifdiv, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifdivr, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifadd, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifadd, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcom, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcomp, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifld, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifst, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifstp, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifldenv, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifldcw, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifnstenv, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifnstcw, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifld, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifld, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifxch, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifnop, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifstp1, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifchs, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifabs, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iftst, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifxam, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifld1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldl2t, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldl2e, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldpi, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldlg2, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldln2, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifldz, O_NONE, O_NONE, O_NONE, P_none },
   { UD_If2xm1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifyl2x, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifptan, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifpatan, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifxtract, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifprem1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifdecstp, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifincstp, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifprem, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifyl2xp1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifsqrt, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifsincos, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifrndint, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifscale, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifsin, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifcos, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifiadd, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifimul, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ificom, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ificomp, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisub, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisubr, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifidiv, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifidivr, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcmovb, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovb, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmove, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovbe, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovu, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifucompp, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifild, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisttp, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifist, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifistp, O_Md, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifld, O_Mt, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifstp, O_Mt, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcmovnb, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovnb, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovne, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovnbe, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcmovnu, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifclex, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifninit, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifucomi, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcomi, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifadd, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifmul, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcom, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifcomp, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifsub, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifsubr, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifdiv, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifdivr, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifadd, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifadd, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifmul, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifcom2, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifcom2, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifcomp3, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifsubr, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifsubr, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifsub, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifdivr, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifdiv, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifld, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisttp, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifst, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifstp, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifrstor, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifnsave, O_M, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifnstsw, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iffree, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Iffree, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifxch4, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifst, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifstp, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifucom, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifucomp, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifiadd, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifimul, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ificom, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ificomp, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisub, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisubr, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifidiv, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifidivr, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifaddp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifaddp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifmulp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifcomp5, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifcomp5, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifcompp, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ifsubrp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifsubrp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifsubp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifdivrp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST1, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST2, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST3, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST4, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST5, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST6, O_ST0, O_NONE, P_none },
   { UD_Ifdivp, O_ST7, O_ST0, O_NONE, P_none },
   { UD_Ifild, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifisttp, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifist, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifistp, O_Mw, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifbld, O_Mt, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifild, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifbstp, O_Mt, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Ifistp, O_Mq, O_NONE, O_NONE, P_aso|P_rexr|P_rexx|P_rexb },
   { UD_Iffreep, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Iffreep, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifxch7, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifstp8, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST0, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST1, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST2, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST3, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST4, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST5, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST6, O_NONE, O_NONE, P_none },
   { UD_Ifstp9, O_ST7, O_NONE, O_NONE, P_none },
   { UD_Ifnstsw, O_AX, O_NONE, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifucomip, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST0, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST1, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST2, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST3, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST4, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST5, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST6, O_NONE, P_none },
   { UD_Ifcomip, O_ST0, O_ST7, O_NONE, P_none },
   { UD_Iloopne, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Iloope, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Iloop, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Ijcxz, O_Jb, O_NONE, O_NONE, P_aso },
   { UD_Ijecxz, O_Jb, O_NONE, O_NONE, P_aso },
   { UD_Ijrcxz, O_Jb, O_NONE, O_NONE, P_aso },
   { UD_Iin, O_AL, O_Ib, O_NONE, P_none },
   { UD_Iin, O_eAX, O_Ib, O_NONE, P_oso },
   { UD_Iout, O_Ib, O_AL, O_NONE, P_none },
   { UD_Iout, O_Ib, O_eAX, O_NONE, P_oso },
   { UD_Icall, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijmp, O_Jz, O_NONE, O_NONE, P_oso|P_def64 },
   { UD_Ijmp, O_Av, O_NONE, O_NONE, P_oso },
   { UD_Ijmp, O_Jb, O_NONE, O_NONE, P_none },
   { UD_Iin, O_AL, O_DX, O_NONE, P_none },
   { UD_Iin, O_eAX, O_DX, O_NONE, P_oso },
   { UD_Iout, O_DX, O_AL, O_NONE, P_none },
   { UD_Iout, O_DX, O_eAX, O_NONE, P_oso },
   { UD_Ilock, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iint1, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irepne, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Irep, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Ihlt, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Icmc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Itest, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Itest, O_Eb, O_Ib, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Inot, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ineg, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imul, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iimul, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Idiv, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iidiv, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Itest, O_Ev, O_sIz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Itest, O_Ev, O_Iz, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Inot, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ineg, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Imul, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iimul, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Idiv, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iidiv, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iclc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Istc, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Icli, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Isti, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Icld, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Istd, O_NONE, O_NONE, O_NONE, P_none },
   { UD_Iinc, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Idec, O_Eb, O_NONE, O_NONE, P_aso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Iinc, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Idec, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icall, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Icall, O_Eq, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Icall, O_Fv, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ijmp, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
   { UD_Ijmp, O_Fv, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb },
   { UD_Ipush, O_Ev, O_NONE, O_NONE, P_aso|P_oso|P_rexw|P_rexr|P_rexx|P_rexb|P_def64 },
};


const char * ud_mnemonics_str[] = {
"invalid",
    "3dnow",
    "none",
    "db",
    "pause",
    "aaa",
    "aad",
    "aam",
    "aas",
    "adc",
    "add",
    "addpd",
    "addps",
    "addsd",
    "addss",
    "and",
    "andpd",
    "andps",
    "andnpd",
    "andnps",
    "arpl",
    "movsxd",
    "bound",
    "bsf",
    "bsr",
    "bswap",
    "bt",
    "btc",
    "btr",
    "bts",
    "call",
    "cbw",
    "cwde",
    "cdqe",
    "clc",
    "cld",
    "clflush",
    "clgi",
    "cli",
    "clts",
    "cmc",
    "cmovo",
    "cmovno",
    "cmovb",
    "cmovae",
    "cmovz",
    "cmovnz",
    "cmovbe",
    "cmova",
    "cmovs",
    "cmovns",
    "cmovp",
    "cmovnp",
    "cmovl",
    "cmovge",
    "cmovle",
    "cmovg",
    "cmp",
    "cmppd",
    "cmpps",
    "cmpsb",
    "cmpsw",
    "cmpsd",
    "cmpsq",
    "cmpss",
    "cmpxchg",
    "cmpxchg8b",
    "cmpxchg16b",
    "comisd",
    "comiss",
    "cpuid",
    "cvtdq2pd",
    "cvtdq2ps",
    "cvtpd2dq",
    "cvtpd2pi",
    "cvtpd2ps",
    "cvtpi2ps",
    "cvtpi2pd",
    "cvtps2dq",
    "cvtps2pi",
    "cvtps2pd",
    "cvtsd2si",
    "cvtsd2ss",
    "cvtsi2ss",
    "cvtss2si",
    "cvtss2sd",
    "cvttpd2pi",
    "cvttpd2dq",
    "cvttps2dq",
    "cvttps2pi",
    "cvttsd2si",
    "cvtsi2sd",
    "cvttss2si",
    "cwd",
    "cdq",
    "cqo",
    "daa",
    "das",
    "dec",
    "div",
    "divpd",
    "divps",
    "divsd",
    "divss",
    "emms",
    "enter",
    "f2xm1",
    "fabs",
    "fadd",
    "faddp",
    "fbld",
    "fbstp",
    "fchs",
    "fclex",
    "fcmovb",
    "fcmove",
    "fcmovbe",
    "fcmovu",
    "fcmovnb",
    "fcmovne",
    "fcmovnbe",
    "fcmovnu",
    "fucomi",
    "fcom",
    "fcom2",
    "fcomp3",
    "fcomi",
    "fucomip",
    "fcomip",
    "fcomp",
    "fcomp5",
    "fcompp",
    "fcos",
    "fdecstp",
    "fdiv",
    "fdivp",
    "fdivr",
    "fdivrp",
    "femms",
    "ffree",
    "ffreep",
    "ficom",
    "ficomp",
    "fild",
    "fincstp",
    "fninit",
    "fiadd",
    "fidivr",
    "fidiv",
    "fisub",
    "fisubr",
    "fist",
    "fistp",
    "fisttp",
    "fld",
    "fld1",
    "fldl2t",
    "fldl2e",
    "fldpi",
    "fldlg2",
    "fldln2",
    "fldz",
    "fldcw",
    "fldenv",
    "fmul",
    "fmulp",
    "fimul",
    "fnop",
    "fpatan",
    "fprem",
    "fprem1",
    "fptan",
    "frndint",
    "frstor",
    "fnsave",
    "fscale",
    "fsin",
    "fsincos",
    "fsqrt",
    "fstp",
    "fstp1",
    "fstp8",
    "fstp9",
    "fst",
    "fnstcw",
    "fnstenv",
    "fnstsw",
    "fsub",
    "fsubp",
    "fsubr",
    "fsubrp",
    "ftst",
    "fucom",
    "fucomp",
    "fucompp",
    "fxam",
    "fxch",
    "fxch4",
    "fxch7",
    "fxrstor",
    "fxsave",
    "fxtract",
    "fyl2x",
    "fyl2xp1",
    "hlt",
    "idiv",
    "in",
    "imul",
    "inc",
    "insb",
    "insw",
    "insd",
    "int1",
    "int3",
    "int",
    "into",
    "invd",
    "invept",
    "invlpg",
    "invlpga",
    "invvpid",
    "iretw",
    "iretd",
    "iretq",
    "jo",
    "jno",
    "jb",
    "jae",
    "jz",
    "jnz",
    "jbe",
    "ja",
    "js",
    "jns",
    "jp",
    "jnp",
    "jl",
    "jge",
    "jle",
    "jg",
    "jcxz",
    "jecxz",
    "jrcxz",
    "jmp",
    "lahf",
    "lar",
    "lddqu",
    "ldmxcsr",
    "lds",
    "lea",
    "les",
    "lfs",
    "lgs",
    "lidt",
    "lss",
    "leave",
    "lfence",
    "lgdt",
    "lldt",
    "lmsw",
    "lock",
    "lodsb",
    "lodsw",
    "lodsd",
    "lodsq",
    "loopne",
    "loope",
    "loop",
    "lsl",
    "ltr",
    "maskmovq",
    "maxpd",
    "maxps",
    "maxsd",
    "maxss",
    "mfence",
    "minpd",
    "minps",
    "minsd",
    "minss",
    "monitor",
    "montmul",
    "mov",
    "movapd",
    "movaps",
    "movd",
    "movhpd",
    "movhps",
    "movlhps",
    "movlpd",
    "movlps",
    "movhlps",
    "movmskpd",
    "movmskps",
    "movntdq",
    "movnti",
    "movntpd",
    "movntps",
    "movntq",
    "movq",
    "movsb",
    "movsw",
    "movsd",
    "movsq",
    "movss",
    "movsx",
    "movupd",
    "movups",
    "movzx",
    "mul",
    "mulpd",
    "mulps",
    "mulsd",
    "mulss",
    "mwait",
    "neg",
    "nop",
    "not",
    "or",
    "orpd",
    "orps",
    "out",
    "outsb",
    "outsw",
    "outsd",
    "packsswb",
    "packssdw",
    "packuswb",
    "paddb",
    "paddw",
    "paddd",
    "paddsb",
    "paddsw",
    "paddusb",
    "paddusw",
    "pand",
    "pandn",
    "pavgb",
    "pavgw",
    "pcmpeqb",
    "pcmpeqw",
    "pcmpeqd",
    "pcmpgtb",
    "pcmpgtw",
    "pcmpgtd",
    "pextrb",
    "pextrd",
    "pextrq",
    "pextrw",
    "pinsrb",
    "pinsrw",
    "pinsrd",
    "pinsrq",
    "pmaddwd",
    "pmaxsw",
    "pmaxub",
    "pminsw",
    "pminub",
    "pmovmskb",
    "pmulhuw",
    "pmulhw",
    "pmullw",
    "pop",
    "popa",
    "popad",
    "popfw",
    "popfd",
    "popfq",
    "por",
    "prefetch",
    "prefetchnta",
    "prefetcht0",
    "prefetcht1",
    "prefetcht2",
    "psadbw",
    "pshufw",
    "psllw",
    "pslld",
    "psllq",
    "psraw",
    "psrad",
    "psrlw",
    "psrld",
    "psrlq",
    "psubb",
    "psubw",
    "psubd",
    "psubsb",
    "psubsw",
    "psubusb",
    "psubusw",
    "punpckhbw",
    "punpckhwd",
    "punpckhdq",
    "punpcklbw",
    "punpcklwd",
    "punpckldq",
    "pi2fw",
    "pi2fd",
    "pf2iw",
    "pf2id",
    "pfnacc",
    "pfpnacc",
    "pfcmpge",
    "pfmin",
    "pfrcp",
    "pfrsqrt",
    "pfsub",
    "pfadd",
    "pfcmpgt",
    "pfmax",
    "pfrcpit1",
    "pfrsqit1",
    "pfsubr",
    "pfacc",
    "pfcmpeq",
    "pfmul",
    "pfrcpit2",
    "pmulhrw",
    "pswapd",
    "pavgusb",
    "push",
    "pusha",
    "pushad",
    "pushfw",
    "pushfd",
    "pushfq",
    "pxor",
    "rcl",
    "rcr",
    "rol",
    "ror",
    "rcpps",
    "rcpss",
    "rdmsr",
    "rdpmc",
    "rdtsc",
    "rdtscp",
    "repne",
    "rep",
    "ret",
    "retf",
    "rsm",
    "rsqrtps",
    "rsqrtss",
    "sahf",
    "salc",
    "sar",
    "shl",
    "shr",
    "sbb",
    "scasb",
    "scasw",
    "scasd",
    "scasq",
    "seto",
    "setno",
    "setb",
    "setae",
    "setz",
    "setnz",
    "setbe",
    "seta",
    "sets",
    "setns",
    "setp",
    "setnp",
    "setl",
    "setge",
    "setle",
    "setg",
    "sfence",
    "sgdt",
    "shld",
    "shrd",
    "shufpd",
    "shufps",
    "sidt",
    "sldt",
    "smsw",
    "sqrtps",
    "sqrtpd",
    "sqrtsd",
    "sqrtss",
    "stc",
    "std",
    "stgi",
    "sti",
    "skinit",
    "stmxcsr",
    "stosb",
    "stosw",
    "stosd",
    "stosq",
    "str",
    "sub",
    "subpd",
    "subps",
    "subsd",
    "subss",
    "swapgs",
    "syscall",
    "sysenter",
    "sysexit",
    "sysret",
    "test",
    "ucomisd",
    "ucomiss",
    "ud2",
    "unpckhpd",
    "unpckhps",
    "unpcklps",
    "unpcklpd",
    "verr",
    "verw",
    "vmcall",
    "vmclear",
    "vmxon",
    "vmptrld",
    "vmptrst",
    "vmlaunch",
    "vmresume",
    "vmxoff",
    "vmread",
    "vmwrite",
    "vmrun",
    "vmmcall",
    "vmload",
    "vmsave",
    "wait",
    "wbinvd",
    "wrmsr",
    "xadd",
    "xchg",
    "xgetbv",
    "xlatb",
    "xor",
    "xorpd",
    "xorps",
    "xcryptecb",
    "xcryptcbc",
    "xcryptctr",
    "xcryptcfb",
    "xcryptofb",
    "xrstor",
    "xsave",
    "xsetbv",
    "xsha1",
    "xsha256",
    "xstore",
    "aesdec",
    "aesdeclast",
    "aesenc",
    "aesenclast",
    "aesimc",
    "aeskeygenassist",
    "pclmulqdq",
    "getsec",
    "movdqa",
    "maskmovdqu",
    "movdq2q",
    "movdqu",
    "movq2dq",
    "paddq",
    "psubq",
    "pmuludq",
    "pshufhw",
    "pshuflw",
    "pshufd",
    "pslldq",
    "psrldq",
    "punpckhqdq",
    "punpcklqdq",
    "addsubpd",
    "addsubps",
    "haddpd",
    "haddps",
    "hsubpd",
    "hsubps",
    "movddup",
    "movshdup",
    "movsldup",
    "pabsb",
    "pabsw",
    "pabsd",
    "pshufb",
    "phaddw",
    "phaddd",
    "phaddsw",
    "pmaddubsw",
    "phsubw",
    "phsubd",
    "phsubsw",
    "psignb",
    "psignd",
    "psignw",
    "pmulhrsw",
    "palignr",
    "pblendvb",
    "pmuldq",
    "pminsb",
    "pminsd",
    "pminuw",
    "pminud",
    "pmaxsb",
    "pmaxsd",
    "pmaxud",
    "pmaxuw",
    "pmulld",
    "phminposuw",
    "roundps",
    "roundpd",
    "roundss",
    "roundsd",
    "blendpd",
    "pblendw",
    "blendps",
    "blendvpd",
    "blendvps",
    "dpps",
    "dppd",
    "mpsadbw",
    "extractps",
    "insertps",
    "movntdqa",
    "packusdw",
    "pmovsxbw",
    "pmovsxbd",
    "pmovsxbq",
    "pmovsxwd",
    "pmovsxwq",
    "pmovsxdq",
    "pmovzxbw",
    "pmovzxbd",
    "pmovzxbq",
    "pmovzxwd",
    "pmovzxwq",
    "pmovzxdq",
    "pcmpeqq",
    "popcnt",
    "ptest",
    "pcmpestri",
    "pcmpestrm",
    "pcmpgtq",
    "pcmpistri",
    "pcmpistrm",
    "movbe",
    "crc32"
};