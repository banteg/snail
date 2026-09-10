; ELF link-time virtual addresses. $d ranges are literal data.

_Z4Sqrtf 0001830c size 52
0001830c 900a07ee vmov s15, r0
00018310 e76ab7ee vcvt.f64.f32 d6, s15
00018314 10402de9 push {r4, lr}
00018318 c67bb1ee vsqrt.f64 d7, d6
0001831c 477bb4ee vcmp.f64 d7, d7
00018320 10faf1ee vmrs apsr_nzcv, fpscr
00018324 0200000a beq #0x18334
00018328 160b51ec vmov r0, r1, d6
0001832c dcecffeb bl #0x136a4
00018330 170b41ec vmov d7, r0, r1
00018334 c76bf7ee vcvt.f32.f64 s13, d7
00018338 900a16ee vmov r0, s13
0001833c 1080bde8 pop {r4, pc}

_ZN11tQuaternianC1ERK7tMatrix 00018340 size 708
00018340 007a91ed vldr s14, [r1]
00018344 057ad1ed vldr s15, [r1, #0x14]
00018348 276a37ee vadd.f32 s12, s14, s15
0001834c 0a6ad1ed vldr s13, [r1, #0x28]
00018350 a35adfed vldr s11, [pc, #0x28c]
00018354 70402de9 push {r4, r5, r6, lr}
00018358 0140a0e1 mov r4, r1
0001835c 94129fe5 ldr r1, [pc, #0x294]
00018360 0050a0e1 mov r5, r0
00018364 01108fe0 add r1, pc, r1
00018368 266a36ee vadd.f32 s12, s12, s13
0001836c 256a36ee vadd.f32 s12, s12, s11
00018370 9c5adfed vldr s11, [pc, #0x270]
00018374 e56ab4ee vcmpe.f32 s12, s11
00018378 10faf1ee vmrs apsr_nzcv, fpscr
0001837c 710000ca bgt #0x18548
00018380 e77ab4ee vcmpe.f32 s14, s15
00018384 10faf1ee vmrs apsr_nzcv, fpscr
00018388 2a0000ba blt #0x18438
0001838c e67ab4ee vcmpe.f32 s14, s13
00018390 10faf1ee vmrs apsr_nzcv, fpscr
00018394 4c0000ca bgt #0x184cc
00018398 e67af4ee vcmpe.f32 s15, s13
0001839c 10faf1ee vmrs apsr_nzcv, fpscr
000183a0 2a0000da ble #0x18450
000183a4 8e6a9fed vldr s12, [pc, #0x238]
000183a8 867a77ee vadd.f32 s15, s15, s12
000183ac c77a37ee vsub.f32 s14, s15, s14
000183b0 666a77ee vsub.f32 s13, s14, s13
000183b4 c06af5ee vcmpe.f32 s13, #0
000183b8 10faf1ee vmrs apsr_nzcv, fpscr
000183bc 0500005a bpl #0x183d8
000183c0 e67ab7ee vcvt.f64.f32 d7, s13
000183c4 30029fe5 ldr r0, [pc, #0x230]
000183c8 000081e0 add r0, r1, r0
000183cc 172b53ec vmov r2, r3, d7
000183d0 5c0500eb bl #0x19948 _Z7wprintfPcz
000183d4 846adfed vldr s13, [pc, #0x210]
000183d8 900a16ee vmov r0, s13
000183dc caffffeb bl #0x1830c _Z4Sqrtf
000183e0 017ad4ed vldr s15, [r4, #4]
000183e4 047a94ed vldr s14, [r4, #0x10]
000183e8 277a37ee vadd.f32 s14, s14, s15
000183ec 100a06ee vmov s12, r0
000183f0 067a76ee vadd.f32 s15, s12, s12
000183f4 0500a0e1 mov r0, r5
000183f8 276ac7ee vdiv.f32 s13, s14, s15
000183fc 7b7a9fed vldr s14, [pc, #0x1ec]
00018400 877a27ee vmul.f32 s14, s15, s14
00018404 006ac5ed vstr s13, [r5]
00018408 017a85ed vstr s14, [r5, #4]
0001840c 096ad4ed vldr s13, [r4, #0x24]
00018410 067a94ed vldr s14, [r4, #0x18]
00018414 877a36ee vadd.f32 s14, s13, s14
00018418 277a87ee vdiv.f32 s14, s14, s15
0001841c 027a85ed vstr s14, [r5, #8]
00018420 027a94ed vldr s14, [r4, #8]
00018424 086ad4ed vldr s13, [r4, #0x20]
00018428 877a36ee vadd.f32 s14, s13, s14
0001842c 277ac7ee vdiv.f32 s15, s14, s15
00018430 037ac5ed vstr s15, [r5, #0xc]
00018434 7080bde8 pop {r4, r5, r6, pc}
00018438 e67af4ee vcmpe.f32 s15, s13
0001843c 10faf1ee vmrs apsr_nzcv, fpscr
00018440 d7ffffaa bge #0x183a4
00018444 e67ab4ee vcmpe.f32 s14, s13
00018448 10faf1ee vmrs apsr_nzcv, fpscr
0001844c 1e0000ca bgt #0x184cc
00018450 636a9fed vldr s12, [pc, #0x18c]
00018454 866a76ee vadd.f32 s13, s13, s12
00018458 c77a36ee vsub.f32 s14, s13, s14
0001845c 677a77ee vsub.f32 s15, s14, s15
00018460 c07af5ee vcmpe.f32 s15, #0
00018464 10faf1ee vmrs apsr_nzcv, fpscr
00018468 5600004a bmi #0x185c8
0001846c 900a17ee vmov r0, s15
00018470 a5ffffeb bl #0x1830c _Z4Sqrtf
00018474 027ad4ed vldr s15, [r4, #8]
00018478 087a94ed vldr s14, [r4, #0x20]
0001847c 277a37ee vadd.f32 s14, s14, s15
00018480 900a06ee vmov s13, r0
00018484 a67a76ee vadd.f32 s15, s13, s13
00018488 0500a0e1 mov r0, r5
0001848c 277a87ee vdiv.f32 s14, s14, s15
00018490 007a85ed vstr s14, [r5]
00018494 096ad4ed vldr s13, [r4, #0x24]
00018498 067a94ed vldr s14, [r4, #0x18]
0001849c 877a36ee vadd.f32 s14, s13, s14
000184a0 276ac7ee vdiv.f32 s13, s14, s15
000184a4 517a9fed vldr s14, [pc, #0x144]
000184a8 877a27ee vmul.f32 s14, s15, s14
000184ac 016ac5ed vstr s13, [r5, #4]
000184b0 027a85ed vstr s14, [r5, #8]
000184b4 017a94ed vldr s14, [r4, #4]
000184b8 046ad4ed vldr s13, [r4, #0x10]
000184bc 877a36ee vadd.f32 s14, s13, s14
000184c0 277ac7ee vdiv.f32 s15, s14, s15
000184c4 037ac5ed vstr s15, [r5, #0xc]
000184c8 7080bde8 pop {r4, r5, r6, pc}
000184cc 446a9fed vldr s12, [pc, #0x110]
000184d0 067a37ee vadd.f32 s14, s14, s12
000184d4 677a77ee vsub.f32 s15, s14, s15
000184d8 e66a77ee vsub.f32 s13, s15, s13
000184dc c06af5ee vcmpe.f32 s13, #0
000184e0 10faf1ee vmrs apsr_nzcv, fpscr
000184e4 3000004a bmi #0x185ac
000184e8 900a16ee vmov r0, s13
000184ec 86ffffeb bl #0x1830c _Z4Sqrtf
000184f0 3e7a9fed vldr s14, [pc, #0xf8]
000184f4 100a06ee vmov s12, r0
000184f8 067a76ee vadd.f32 s15, s12, s12
000184fc 0500a0e1 mov r0, r5
00018500 877a27ee vmul.f32 s14, s15, s14
00018504 007a85ed vstr s14, [r5]
00018508 046ad4ed vldr s13, [r4, #0x10]
0001850c 017a94ed vldr s14, [r4, #4]
00018510 877a36ee vadd.f32 s14, s13, s14
00018514 277a87ee vdiv.f32 s14, s14, s15
00018518 017a85ed vstr s14, [r5, #4]
0001851c 086ad4ed vldr s13, [r4, #0x20]
00018520 027a94ed vldr s14, [r4, #8]
00018524 877a36ee vadd.f32 s14, s13, s14
00018528 277a87ee vdiv.f32 s14, s14, s15
0001852c 027a85ed vstr s14, [r5, #8]
00018530 067a94ed vldr s14, [r4, #0x18]
00018534 096ad4ed vldr s13, [r4, #0x24]
00018538 877a36ee vadd.f32 s14, s13, s14
0001853c 277ac7ee vdiv.f32 s15, s14, s15
00018540 037ac5ed vstr s15, [r5, #0xc]
00018544 7080bde8 pop {r4, r5, r6, pc}
00018548 100a16ee vmov r0, s12
0001854c 6effffeb bl #0x1830c _Z4Sqrtf
00018550 277adfed vldr s15, [pc, #0x9c]
00018554 257a9fed vldr s14, [pc, #0x94]
00018558 100a06ee vmov s12, r0
0001855c 867ac7ee vdiv.f32 s15, s15, s12
00018560 0500a0e1 mov r0, r5
00018564 277a87ee vdiv.f32 s14, s14, s15
00018568 037a85ed vstr s14, [r5, #0xc]
0001856c 066ad4ed vldr s13, [r4, #0x18]
00018570 097a94ed vldr s14, [r4, #0x24]
00018574 c77a36ee vsub.f32 s14, s13, s14
00018578 277a27ee vmul.f32 s14, s14, s15
0001857c 007a85ed vstr s14, [r5]
00018580 086ad4ed vldr s13, [r4, #0x20]
00018584 027a94ed vldr s14, [r4, #8]
00018588 c77a36ee vsub.f32 s14, s13, s14
0001858c 277a27ee vmul.f32 s14, s14, s15
00018590 017a85ed vstr s14, [r5, #4]
00018594 047a94ed vldr s14, [r4, #0x10]
00018598 016ad4ed vldr s13, [r4, #4]
0001859c c77a36ee vsub.f32 s14, s13, s14
000185a0 277a67ee vmul.f32 s15, s14, s15
000185a4 027ac5ed vstr s15, [r5, #8]
000185a8 7080bde8 pop {r4, r5, r6, pc}
000185ac e67ab7ee vcvt.f64.f32 d7, s13
000185b0 48009fe5 ldr r0, [pc, #0x48]
000185b4 000081e0 add r0, r1, r0
000185b8 172b53ec vmov r2, r3, d7
000185bc e10400eb bl #0x19948 _Z7wprintfPcz
000185c0 096adfed vldr s13, [pc, #0x24]
000185c4 c7ffffea b #0x184e8
000185c8 e76ab7ee vcvt.f64.f32 d6, s15
000185cc 28009fe5 ldr r0, [pc, #0x28]
000185d0 000081e0 add r0, r1, r0
000185d4 162b53ec vmov r2, r3, d6
000185d8 da0400eb bl #0x19948 _Z7wprintfPcz
000185dc 027adfed vldr s15, [pc, #8]
000185e0 a1ffffea b #0x1846c
000185e4 0000803f .word 0x3f800000
000185e8 bd378635 .word 0x358637bd
000185ec 00000000 .word 0x00000000
000185f0 0000803e .word 0x3e800000
000185f4 0000003f .word 0x3f000000
000185f8 a42b0700 .word 0x00072ba4
000185fc ac62ffff .word 0xffff62ac
00018600 9c62ffff .word 0xffff629c

_ZN11cRGameInput2AIEv 0003a68c size 152
0003a68c 88309fe5 ldr r3, [pc, #0x88]
0003a690 88209fe5 ldr r2, [pc, #0x88]
0003a694 03308fe0 add r3, pc, r3
0003a698 10402de9 push {r4, lr}
0003a69c 023093e7 ldr r3, [r3, r2]
0003a6a0 20d04de2 sub sp, sp, #0x20
0003a6a4 0040a0e1 mov r4, r0
0003a6a8 003093e5 ldr r3, [r3]
0003a6ac dc32d3e5 ldrb r3, [r3, #0x2dc]
0003a6b0 000053e3 cmp r3, #0
0003a6b4 0100001a bne #0x3a6c0
0003a6b8 20d08de2 add sp, sp, #0x20
0003a6bc 1080bde8 pop {r4, pc}
0003a6c0 2c0090e5 ldr r0, [r0, #0x2c]
0003a6c4 681084e2 add r1, r4, #0x68
0003a6c8 402084e2 add r2, r4, #0x40
0003a6cc 443084e2 add r3, r4, #0x44
0003a6d0 54c084e2 add ip, r4, #0x54
0003a6d4 00c08de5 str ip, [sp]
0003a6d8 58c084e2 add ip, r4, #0x58
0003a6dc 04c08de5 str ip, [sp, #4]
0003a6e0 5cc084e2 add ip, r4, #0x5c
0003a6e4 08c08de5 str ip, [sp, #8]
0003a6e8 4cc084e2 add ip, r4, #0x4c
0003a6ec 0cc08de5 str ip, [sp, #0xc]
0003a6f0 50c084e2 add ip, r4, #0x50
0003a6f4 10c08de5 str ip, [sp, #0x10]
0003a6f8 60c084e2 add ip, r4, #0x60
0003a6fc 14c08de5 str ip, [sp, #0x14]
0003a700 64c084e2 add ip, r4, #0x64
0003a704 18c08de5 str ip, [sp, #0x18]
0003a708 8b7effeb bl #0x1a13c _Z19RShellInputRetrieveiPiPfS0_S0_S0_S0_S0_S0_S0_S0_
0003a70c 2c0084e2 add r0, r4, #0x2c
0003a710 20d08de2 add sp, sp, #0x20
0003a714 1040bde8 pop {r4, lr}
0003a718 50ceffea b #0x2e060 _ZN7cRInput6UpdateEv
0003a71c 74080500 .word 0x00050874
0003a720 e0020000 .word 0x000002e0
