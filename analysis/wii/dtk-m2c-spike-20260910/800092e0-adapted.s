.include "macros.inc"
.file "auto_fn_800092E0_text"

# 0x80006720..0x80006728 | size: 0x8
.section extab, "a"
.balign 4

# extab:0x0 | 0x80006720 | size: 0x8
.obj "@etb_80006720", local
.hidden "@etb_80006720"
/*
 * Flag values:
 * Has Elf Vector: Yes
 * Large Frame: Yes
 * Has Frame Pointer: No
 * Saved CR: No
 */
	.4byte 0x000A0000
	.4byte 0x00000000
.endobj "@etb_80006720"

# 0x800078E0..0x800078EC | size: 0xC
.section extabindex, "a"
.balign 4

# extabindex:0x0 | 0x800078E0 | size: 0xC
.obj "@eti_800078E0", local
.hidden "@eti_800078E0"
	.4byte fn_800092E0
	.4byte 0x00000024
	.4byte "@etb_80006720"
.endobj "@eti_800078E0"

# 0x800092E0..0x80009304 | size: 0x24
.text
.balign 4

# .text:0x0 | 0x800092E0 | size: 0x24
.fn fn_800092E0, global
/* 800092E0 00002820  C0 02 80 00 */	lfs f0, lbl_808F4860@sda21(r0)
/* 800092E4 00002824  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800092E8 00002828  EC 00 10 24 */	fdivs f0, f0, f2
/* 800092EC 0000282C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800092F0 00002830  FC 00 00 1E */	fctiwz f0, f0
/* 800092F4 00002834  D8 01 00 08 */	stfd f0, 0x8(r1)
/* 800092F8 00002838  80 61 00 0C */	lwz r3, 0xc(r1)
/* 800092FC 0000283C  38 21 00 10 */	addi r1, r1, 0x10
/* 80009300 00002840  4E 80 00 20 */	blr
.endfn fn_800092E0
