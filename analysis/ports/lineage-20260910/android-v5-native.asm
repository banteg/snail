; ELF link-time virtual addresses. $d ranges are literal data.

_Z4Sqrtf 00019c10 size 20
00019c10 10402de9 push {r4, lr}
00019c14 8eb601eb bl #0x87654 __aeabi_f2d,__extendsfdf2
00019c18 d3e8ffeb bl #0x13f6c
00019c1c 1ab701eb bl #0x8788c __aeabi_d2f,__truncdfsf2
00019c20 1080bde8 pop {r4, pc}

_ZN11tQuaternianC1ERK7tMatrix 00019c24 size 920
00019c24 f0472de9 push {r4, r5, r6, r7, r8, sb, sl, lr}
00019c28 008091e5 ldr r8, [r1]
00019c2c 146091e5 ldr r6, [r1, #0x14]
00019c30 28a091e5 ldr sl, [r1, #0x28]
00019c34 0140a0e1 mov r4, r1
00019c38 0050a0e1 mov r5, r0
00019c3c 0610a0e1 mov r1, r6
00019c40 0800a0e1 mov r0, r8
00019c44 3bb701eb bl #0x87938 __addsf3,__aeabi_fadd
00019c48 0a10a0e1 mov r1, sl
00019c4c 39b701eb bl #0x87938 __addsf3,__aeabi_fadd
00019c50 fe15a0e3 mov r1, #0x3f800000
00019c54 37b701eb bl #0x87938 __addsf3,__aeabi_fadd
00019c58 4c139fe5 ldr r1, [pc, #0x34c]
00019c5c 0090a0e1 mov sb, r0
00019c60 bcb801eb bl #0x87f58 __aeabi_fcmpgt
00019c64 44739fe5 ldr r7, [pc, #0x344]
00019c68 000050e3 cmp r0, #0
00019c6c 07708fe0 add r7, pc, r7
00019c70 9b00001a bne #0x19ee4
00019c74 0800a0e1 mov r0, r8
00019c78 0610a0e1 mov r1, r6
00019c7c b0b801eb bl #0x87f44 __aeabi_fcmpge
00019c80 000050e3 cmp r0, #0
00019c84 3b00000a beq #0x19d78
00019c88 0800a0e1 mov r0, r8
00019c8c 0a10a0e1 mov r1, sl
00019c90 b0b801eb bl #0x87f58 __aeabi_fcmpgt
00019c94 000050e3 cmp r0, #0
00019c98 6900001a bne #0x19e44
00019c9c 0600a0e1 mov r0, r6
00019ca0 0a10a0e1 mov r1, sl
00019ca4 abb801eb bl #0x87f58 __aeabi_fcmpgt
00019ca8 000050e3 cmp r0, #0
00019cac 3b00000a beq #0x19da0
00019cb0 0600a0e1 mov r0, r6
00019cb4 fe15a0e3 mov r1, #0x3f800000
00019cb8 1eb701eb bl #0x87938 __addsf3,__aeabi_fadd
00019cbc 0810a0e1 mov r1, r8
00019cc0 1bb701eb bl #0x87934 __aeabi_fsub,__subsf3
00019cc4 0a10a0e1 mov r1, sl
00019cc8 19b701eb bl #0x87934 __aeabi_fsub,__subsf3
00019ccc 0010a0e3 mov r1, #0
00019cd0 0060a0e1 mov r6, r0
00019cd4 90b801eb bl #0x87f1c __aeabi_fcmplt
00019cd8 000050e3 cmp r0, #0
00019cdc 0800000a beq #0x19d04
00019ce0 cc329fe5 ldr r3, [pc, #0x2cc]
00019ce4 0600a0e1 mov r0, r6
00019ce8 0060a0e3 mov r6, #0
00019cec 037087e0 add r7, r7, r3
00019cf0 57b601eb bl #0x87654 __aeabi_f2d,__extendsfdf2
00019cf4 0020a0e1 mov r2, r0
00019cf8 0130a0e1 mov r3, r1
00019cfc 0700a0e1 mov r0, r7
00019d00 870600eb bl #0x1b724 _Z7wprintfPcz
00019d04 0600a0e1 mov r0, r6
00019d08 c0ffffeb bl #0x19c10 _Z4Sqrtf
00019d0c 0010a0e1 mov r1, r0
00019d10 08b701eb bl #0x87938 __addsf3,__aeabi_fadd
00019d14 041094e5 ldr r1, [r4, #4]
00019d18 0060a0e1 mov r6, r0
00019d1c 100094e5 ldr r0, [r4, #0x10]
00019d20 04b701eb bl #0x87938 __addsf3,__aeabi_fadd
00019d24 0610a0e1 mov r1, r6
00019d28 f9b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019d2c fa15a0e3 mov r1, #0x3e800000
00019d30 000085e5 str r0, [r5]
00019d34 0600a0e1 mov r0, r6
00019d38 8fb701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019d3c 040085e5 str r0, [r5, #4]
00019d40 181094e5 ldr r1, [r4, #0x18]
00019d44 240094e5 ldr r0, [r4, #0x24]
00019d48 fab601eb bl #0x87938 __addsf3,__aeabi_fadd
00019d4c 0610a0e1 mov r1, r6
00019d50 efb701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019d54 080085e5 str r0, [r5, #8]
00019d58 081094e5 ldr r1, [r4, #8]
00019d5c 200094e5 ldr r0, [r4, #0x20]
00019d60 f4b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019d64 0610a0e1 mov r1, r6
00019d68 e9b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019d6c 0c0085e5 str r0, [r5, #0xc]
00019d70 0500a0e1 mov r0, r5
00019d74 f087bde8 pop {r4, r5, r6, r7, r8, sb, sl, pc}
00019d78 0600a0e1 mov r0, r6
00019d7c 0a10a0e1 mov r1, sl
00019d80 6fb801eb bl #0x87f44 __aeabi_fcmpge
00019d84 000050e3 cmp r0, #0
00019d88 c8ffff1a bne #0x19cb0
00019d8c 0800a0e1 mov r0, r8
00019d90 0a10a0e1 mov r1, sl
00019d94 6fb801eb bl #0x87f58 __aeabi_fcmpgt
00019d98 000050e3 cmp r0, #0
00019d9c 2800001a bne #0x19e44
00019da0 fe15a0e3 mov r1, #0x3f800000
00019da4 0a00a0e1 mov r0, sl
00019da8 e2b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019dac 0810a0e1 mov r1, r8
00019db0 dfb601eb bl #0x87934 __aeabi_fsub,__subsf3
00019db4 0610a0e1 mov r1, r6
00019db8 ddb601eb bl #0x87934 __aeabi_fsub,__subsf3
00019dbc 0010a0e3 mov r1, #0
00019dc0 0060a0e1 mov r6, r0
00019dc4 54b801eb bl #0x87f1c __aeabi_fcmplt
00019dc8 000050e3 cmp r0, #0
00019dcc 6c00001a bne #0x19f84
00019dd0 0600a0e1 mov r0, r6
00019dd4 8dffffeb bl #0x19c10 _Z4Sqrtf
00019dd8 0010a0e1 mov r1, r0
00019ddc d5b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019de0 081094e5 ldr r1, [r4, #8]
00019de4 0060a0e1 mov r6, r0
00019de8 200094e5 ldr r0, [r4, #0x20]
00019dec d1b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019df0 0610a0e1 mov r1, r6
00019df4 c6b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019df8 000085e5 str r0, [r5]
00019dfc 181094e5 ldr r1, [r4, #0x18]
00019e00 240094e5 ldr r0, [r4, #0x24]
00019e04 cbb601eb bl #0x87938 __addsf3,__aeabi_fadd
00019e08 0610a0e1 mov r1, r6
00019e0c c0b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019e10 fa15a0e3 mov r1, #0x3e800000
00019e14 040085e5 str r0, [r5, #4]
00019e18 0600a0e1 mov r0, r6
00019e1c 56b701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019e20 080085e5 str r0, [r5, #8]
00019e24 041094e5 ldr r1, [r4, #4]
00019e28 100094e5 ldr r0, [r4, #0x10]
00019e2c c1b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019e30 0610a0e1 mov r1, r6
00019e34 b6b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019e38 0c0085e5 str r0, [r5, #0xc]
00019e3c 0500a0e1 mov r0, r5
00019e40 f087bde8 pop {r4, r5, r6, r7, r8, sb, sl, pc}
00019e44 fe15a0e3 mov r1, #0x3f800000
00019e48 0800a0e1 mov r0, r8
00019e4c b9b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019e50 0610a0e1 mov r1, r6
00019e54 b6b601eb bl #0x87934 __aeabi_fsub,__subsf3
00019e58 0a10a0e1 mov r1, sl
00019e5c b4b601eb bl #0x87934 __aeabi_fsub,__subsf3
00019e60 0010a0e3 mov r1, #0
00019e64 0060a0e1 mov r6, r0
00019e68 2bb801eb bl #0x87f1c __aeabi_fcmplt
00019e6c 000050e3 cmp r0, #0
00019e70 3900001a bne #0x19f5c
00019e74 0600a0e1 mov r0, r6
00019e78 64ffffeb bl #0x19c10 _Z4Sqrtf
00019e7c 0010a0e1 mov r1, r0
00019e80 acb601eb bl #0x87938 __addsf3,__aeabi_fadd
00019e84 fa15a0e3 mov r1, #0x3e800000
00019e88 0060a0e1 mov r6, r0
00019e8c 3ab701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019e90 000085e5 str r0, [r5]
00019e94 041094e5 ldr r1, [r4, #4]
00019e98 100094e5 ldr r0, [r4, #0x10]
00019e9c a5b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019ea0 0610a0e1 mov r1, r6
00019ea4 9ab701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019ea8 040085e5 str r0, [r5, #4]
00019eac 081094e5 ldr r1, [r4, #8]
00019eb0 200094e5 ldr r0, [r4, #0x20]
00019eb4 9fb601eb bl #0x87938 __addsf3,__aeabi_fadd
00019eb8 0610a0e1 mov r1, r6
00019ebc 94b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019ec0 080085e5 str r0, [r5, #8]
00019ec4 181094e5 ldr r1, [r4, #0x18]
00019ec8 240094e5 ldr r0, [r4, #0x24]
00019ecc 99b601eb bl #0x87938 __addsf3,__aeabi_fadd
00019ed0 0610a0e1 mov r1, r6
00019ed4 8eb701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019ed8 0c0085e5 str r0, [r5, #0xc]
00019edc 0500a0e1 mov r0, r5
00019ee0 f087bde8 pop {r4, r5, r6, r7, r8, sb, sl, pc}
00019ee4 0900a0e1 mov r0, sb
00019ee8 48ffffeb bl #0x19c10 _Z4Sqrtf
00019eec 0010a0e1 mov r1, r0
00019ef0 3f04a0e3 mov r0, #0x3f000000
00019ef4 86b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019ef8 0060a0e1 mov r6, r0
00019efc 0010a0e1 mov r1, r0
00019f00 fa05a0e3 mov r0, #0x3e800000
00019f04 82b701eb bl #0x87d14 __aeabi_fdiv,__divsf3
00019f08 0c0085e5 str r0, [r5, #0xc]
00019f0c 241094e5 ldr r1, [r4, #0x24]
00019f10 180094e5 ldr r0, [r4, #0x18]
00019f14 86b601eb bl #0x87934 __aeabi_fsub,__subsf3
00019f18 0610a0e1 mov r1, r6
00019f1c 16b701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019f20 000085e5 str r0, [r5]
00019f24 081094e5 ldr r1, [r4, #8]
00019f28 200094e5 ldr r0, [r4, #0x20]
00019f2c 80b601eb bl #0x87934 __aeabi_fsub,__subsf3
00019f30 0610a0e1 mov r1, r6
00019f34 10b701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019f38 040085e5 str r0, [r5, #4]
00019f3c 101094e5 ldr r1, [r4, #0x10]
00019f40 040094e5 ldr r0, [r4, #4]
00019f44 7ab601eb bl #0x87934 __aeabi_fsub,__subsf3
00019f48 0610a0e1 mov r1, r6
00019f4c 0ab701eb bl #0x87b7c __aeabi_fmul,__mulsf3
00019f50 080085e5 str r0, [r5, #8]
00019f54 0500a0e1 mov r0, r5
00019f58 f087bde8 pop {r4, r5, r6, r7, r8, sb, sl, pc}
00019f5c 54309fe5 ldr r3, [pc, #0x54]
00019f60 0600a0e1 mov r0, r6
00019f64 0060a0e3 mov r6, #0
00019f68 037087e0 add r7, r7, r3
00019f6c b8b501eb bl #0x87654 __aeabi_f2d,__extendsfdf2
00019f70 0020a0e1 mov r2, r0
00019f74 0130a0e1 mov r3, r1
00019f78 0700a0e1 mov r0, r7
00019f7c e80500eb bl #0x1b724 _Z7wprintfPcz
00019f80 bbffffea b #0x19e74
00019f84 28309fe5 ldr r3, [pc, #0x28]
00019f88 0600a0e1 mov r0, r6
00019f8c 0060a0e3 mov r6, #0
00019f90 037087e0 add r7, r7, r3
00019f94 aeb501eb bl #0x87654 __aeabi_f2d,__extendsfdf2
00019f98 0020a0e1 mov r2, r0
00019f9c 0130a0e1 mov r3, r1
00019fa0 0700a0e1 mov r0, r7
00019fa4 de0500eb bl #0x1b724 _Z7wprintfPcz
00019fa8 88ffffea b #0x19dd0
00019fac bd378635 .word 0x358637bd
00019fb0 94a50700 .word 0x0007a594
00019fb4 5061ffff .word 0xffff6150
00019fb8 4061ffff .word 0xffff6140

_ZN11cRGameInput2AIEv 0003d11c size 152
0003d11c 88309fe5 ldr r3, [pc, #0x88]
0003d120 88209fe5 ldr r2, [pc, #0x88]
0003d124 f0452de9 push {r4, r5, r6, r7, r8, sl, lr}
0003d128 03308fe0 add r3, pc, r3
0003d12c 022093e7 ldr r2, [r3, r2]
0003d130 24d04de2 sub sp, sp, #0x24
0003d134 0040a0e1 mov r4, r0
0003d138 003092e5 ldr r3, [r2]
0003d13c dc32d3e5 ldrb r3, [r3, #0x2dc]
0003d140 000053e3 cmp r3, #0
0003d144 0100001a bne #0x3d150
0003d148 24d08de2 add sp, sp, #0x24
0003d14c f085bde8 pop {r4, r5, r6, r7, r8, sl, pc}
0003d150 2c0090e5 ldr r0, [r0, #0x2c]
0003d154 4ce084e2 add lr, r4, #0x4c
0003d158 64c084e2 add ip, r4, #0x64
0003d15c 547084e2 add r7, r4, #0x54
0003d160 586084e2 add r6, r4, #0x58
0003d164 5c5084e2 add r5, r4, #0x5c
0003d168 508084e2 add r8, r4, #0x50
0003d16c 60a084e2 add sl, r4, #0x60
0003d170 681084e2 add r1, r4, #0x68
0003d174 402084e2 add r2, r4, #0x40
0003d178 443084e2 add r3, r4, #0x44
0003d17c 00708de5 str r7, [sp]
0003d180 04608de5 str r6, [sp, #4]
0003d184 08508de5 str r5, [sp, #8]
0003d188 0ce08de5 str lr, [sp, #0xc]
0003d18c 10808de5 str r8, [sp, #0x10]
0003d190 14a08de5 str sl, [sp, #0x14]
0003d194 18c08de5 str ip, [sp, #0x18]
0003d198 6b7bffeb bl #0x1bf4c _Z19RShellInputRetrieveiPiPfS0_S0_S0_S0_S0_S0_S0_S0_
0003d19c 2c0084e2 add r0, r4, #0x2c
0003d1a0 24d08de2 add sp, sp, #0x24
0003d1a4 f045bde8 pop {r4, r5, r6, r7, r8, sl, lr}
0003d1a8 b7d1ffea b #0x3188c _ZN7cRInput6UpdateEv
0003d1ac d8700500 .word 0x000570d8
0003d1b0 e0020000 .word 0x000002e0
