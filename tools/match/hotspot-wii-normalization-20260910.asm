; Wii source lead for cRSnail::ExtractHotSpots; later-port layout and compressed vertex handling differ.
; Binary Ninja 6.1.10626-dev ppc_ps. Every annotation checked against the DOL bytes.
; Extent 0x80052a00..0x80052d60 exclusive. See hotspot-wii-normalization-20260910.json.

80052a00  94 21 ff 80      stwu    r1, -128(r1)
80052a04  7c 08 02 a6      mflr    r0
80052a08  90 01 00 84      stw     r0, 132(r1)
80052a0c  39 61 00 40      addi    r11, r1, 0x40
80052a10  db e1 00 70      stfd    f31, 112(r1)
80052a14  f3 e1 00 78      psq_st  f31, 120(r1), 0x0, 0x0
80052a18  db c1 00 60      stfd    f30, 96(r1)
80052a1c  f3 c1 00 68      psq_st  f30, 104(r1), 0x0, 0x0
80052a20  db a1 00 50      stfd    f29, 80(r1)
80052a24  f3 a1 00 58      psq_st  f29, 88(r1), 0x0, 0x0
80052a28  db 81 00 40      stfd    f28, 64(r1)
80052a2c  f3 81 00 48      psq_st  f28, 72(r1), 0x0, 0x0
80052a30  48 06 94 55      bl      0x800bbe84
80052a34  3c 00 43 30      lis     r0, 0x4330
80052a38  7c 7b 1b 78      mr      r27, r3
80052a3c  3f a0 80 16      lis     r29, 0x8016
80052a40  3f 40 80 16      lis     r26, 0x8016
80052a44  c3 c2 8b 18      lfs     f30, -29928(r2)
80052a48  7f 7e db 78      mr      r30, r27
80052a4c  90 01 00 10      stw     r0, 16(r1)
80052a50  3b bd 74 78      addi    r29, r29, 0x7478
80052a54  83 83 07 a4      lwz     r28, 1956(r3)
80052a58  3b 5a 18 94      addi    r26, r26, 0x1894
80052a5c  90 01 00 18      stw     r0, 24(r1)
80052a60  3f e0 80 59      lis     r31, 0x8059
80052a64  cb e2 8b 48      lfd     f31, -29880(r2)
80052a68  c3 a2 8b 1c      lfs     f29, -29924(r2)
80052a6c  d3 de 08 10      stfs    f30, 2064(r30)
80052a70  ff 80 f0 90      fmr     f28, f30
80052a74  38 7f fb 38      addi    r3, r31, -0x4c8
80052a78  38 a0 00 00      li      r5, 0x0
80052a7c  d3 de 08 0c      stfs    f30, 2060(r30)
80052a80  38 c0 00 00      li      r6, 0x0
80052a84  d3 de 08 08      stfs    f30, 2056(r30)
80052a88  d3 de 08 1c      stfs    f30, 2076(r30)
80052a8c  d3 de 08 18      stfs    f30, 2072(r30)
80052a90  d3 de 08 14      stfs    f30, 2068(r30)
80052a94  80 1d 00 00      lwz     r0, 0(r29)
80052a98  90 1e 08 04      stw     r0, 2052(r30)
80052a9c  80 9d 00 04      lwz     r4, 4(r29)
80052aa0  4b fe c5 55      bl      0x8003eff4
80052aa4  80 1c 00 cc      lwz     r0, 204(r28)
80052aa8  38 e0 00 00      li      r7, 0x0
80052aac  38 a0 00 00      li      r5, 0x0
80052ab0  7c 09 03 a6      mtctr   r0
80052ab4  2c 00 00 00      cmpwi   r0, 0x0
80052ab8  40 81 01 b4      ble     0x80052c6c
80052abc  80 dc 00 d4      lwz     r6, 212(r28)
80052ac0  7c 86 2a 14      add     r4, r6, r5
80052ac4  80 04 00 0c      lwz     r0, 12(r4)
80052ac8  7c 00 18 40      cmplw   r0, r3
80052acc  40 82 01 94      bne     0x80052c60
80052ad0  80 1c 00 00      lwz     r0, 0(r28)
80052ad4  54 00 06 b5      rlwinm. r0, r0, 0x0, 0x1a, 0x1a
80052ad8  41 82 00 b8      beq     0x80052b90
80052adc  1c a7 00 30      mulli   r5, r7, 0x30
80052ae0  80 9c 00 ac      lwz     r4, 172(r28)
80052ae4  c0 3c 00 18      lfs     f1, 24(r28)
80052ae8  c0 1e 08 08      lfs     f0, 2056(r30)
80052aec  7c 66 2a 14      add     r3, r6, r5
80052af0  a0 03 00 02      lhz     r0, 2(r3)
80052af4  1c 00 00 06      mulli   r0, r0, 0x6
80052af8  7c 04 02 ae      lhax    r0, r4, r0
80052afc  6c 00 80 00      xoris   r0, r0, 0x8000
80052b00  90 01 00 14      stw     r0, 20(r1)
80052b04  c8 41 00 10      lfd     f2, 16(r1)
80052b08  ec 42 f8 28      fsubs   f2, f2, f31
80052b0c  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052b10  d0 1e 08 08      stfs    f0, 2056(r30)
80052b14  80 1c 00 d4      lwz     r0, 212(r28)
80052b18  80 9c 00 ac      lwz     r4, 172(r28)
80052b1c  7c 60 2a 14      add     r3, r0, r5
80052b20  c0 3c 00 18      lfs     f1, 24(r28)
80052b24  a0 03 00 02      lhz     r0, 2(r3)
80052b28  c0 1e 08 0c      lfs     f0, 2060(r30)
80052b2c  1c 00 00 06      mulli   r0, r0, 0x6
80052b30  7c 64 02 14      add     r3, r4, r0
80052b34  a8 03 00 02      lha     r0, 2(r3)
80052b38  6c 00 80 00      xoris   r0, r0, 0x8000
80052b3c  90 01 00 1c      stw     r0, 28(r1)
80052b40  c8 41 00 18      lfd     f2, 24(r1)
80052b44  ec 42 f8 28      fsubs   f2, f2, f31
80052b48  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052b4c  d0 1e 08 0c      stfs    f0, 2060(r30)
80052b50  80 1c 00 d4      lwz     r0, 212(r28)
80052b54  80 9c 00 ac      lwz     r4, 172(r28)
80052b58  7c 60 2a 14      add     r3, r0, r5
80052b5c  c0 3c 00 18      lfs     f1, 24(r28)
80052b60  a0 03 00 02      lhz     r0, 2(r3)
80052b64  c0 1e 08 10      lfs     f0, 2064(r30)
80052b68  1c 00 00 06      mulli   r0, r0, 0x6
80052b6c  7c 64 02 14      add     r3, r4, r0
80052b70  a8 03 00 04      lha     r0, 4(r3)
80052b74  6c 00 80 00      xoris   r0, r0, 0x8000
80052b78  90 01 00 14      stw     r0, 20(r1)
80052b7c  c8 41 00 10      lfd     f2, 16(r1)
80052b80  ec 42 f8 28      fsubs   f2, f2, f31
80052b84  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052b88  d0 1e 08 10      stfs    f0, 2064(r30)
80052b8c  48 00 00 cc      b       0x80052c58
80052b90  1c a7 00 30      mulli   r5, r7, 0x30
80052b94  80 9c 00 ac      lwz     r4, 172(r28)
80052b98  c0 3c 00 18      lfs     f1, 24(r28)
80052b9c  c0 1e 08 08      lfs     f0, 2056(r30)
80052ba0  7c 66 2a 14      add     r3, r6, r5
80052ba4  a0 63 00 02      lhz     r3, 2(r3)
80052ba8  54 60 10 3a      slwi    r0, r3, 0x2
80052bac  7c 03 00 50      subf    r0, r3, r0
80052bb0  7c 04 00 ae      lbzx    r0, r4, r0
80052bb4  7c 00 07 74      extsb   r0, r0
80052bb8  6c 00 80 00      xoris   r0, r0, 0x8000
80052bbc  90 01 00 1c      stw     r0, 28(r1)
80052bc0  c8 41 00 18      lfd     f2, 24(r1)
80052bc4  ec 42 f8 28      fsubs   f2, f2, f31
80052bc8  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052bcc  d0 1e 08 08      stfs    f0, 2056(r30)
80052bd0  80 1c 00 d4      lwz     r0, 212(r28)
80052bd4  80 9c 00 ac      lwz     r4, 172(r28)
80052bd8  7c 60 2a 14      add     r3, r0, r5
80052bdc  c0 3c 00 18      lfs     f1, 24(r28)
80052be0  a0 63 00 02      lhz     r3, 2(r3)
80052be4  c0 1e 08 0c      lfs     f0, 2060(r30)
80052be8  54 60 10 3a      slwi    r0, r3, 0x2
80052bec  7c 03 00 50      subf    r0, r3, r0
80052bf0  7c 64 02 14      add     r3, r4, r0
80052bf4  88 03 00 01      lbz     r0, 1(r3)
80052bf8  7c 00 07 74      extsb   r0, r0
80052bfc  6c 00 80 00      xoris   r0, r0, 0x8000
80052c00  90 01 00 14      stw     r0, 20(r1)
80052c04  c8 41 00 10      lfd     f2, 16(r1)
80052c08  ec 42 f8 28      fsubs   f2, f2, f31
80052c0c  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052c10  d0 1e 08 0c      stfs    f0, 2060(r30)
80052c14  80 1c 00 d4      lwz     r0, 212(r28)
80052c18  80 9c 00 ac      lwz     r4, 172(r28)
80052c1c  7c 60 2a 14      add     r3, r0, r5
80052c20  c0 3c 00 18      lfs     f1, 24(r28)
80052c24  a0 63 00 02      lhz     r3, 2(r3)
80052c28  c0 1e 08 10      lfs     f0, 2064(r30)
80052c2c  54 60 10 3a      slwi    r0, r3, 0x2
80052c30  7c 03 00 50      subf    r0, r3, r0
80052c34  7c 64 02 14      add     r3, r4, r0
80052c38  88 03 00 02      lbz     r0, 2(r3)
80052c3c  7c 00 07 74      extsb   r0, r0
80052c40  6c 00 80 00      xoris   r0, r0, 0x8000
80052c44  90 01 00 1c      stw     r0, 28(r1)
80052c48  c8 41 00 18      lfd     f2, 24(r1)
80052c4c  ec 42 f8 28      fsubs   f2, f2, f31
80052c50  ec 01 00 ba      fmadds  f0, f1, f2, f0
80052c54  d0 1e 08 10      stfs    f0, 2064(r30)
80052c58  ef 9e e8 2a      fadds   f28, f30, f29
80052c5c  48 00 00 10      b       0x80052c6c
80052c60  38 a5 00 30      addi    r5, r5, 0x30
80052c64  38 e7 00 01      addi    r7, r7, 0x1
80052c68  42 00 fe 54      bdnz    0x80052abc
80052c6c  fc 1e e0 00      fcmpu   cr0, f30, f28
80052c70  40 82 00 28      bne     0x80052c98
80052c74  80 bd 00 00      lwz     r5, 0(r29)
80052c78  38 7a 00 e3      addi    r3, r26, 0xe3
80052c7c  80 1d 00 04      lwz     r0, 4(r29)
80052c80  38 81 00 08      addi    r4, r1, 0x8
80052c84  90 a1 00 08      stw     r5, 8(r1)
80052c88  90 01 00 0c      stw     r0, 12(r1)
80052c8c  4c c6 31 82      crclr   cr1eq
80052c90  4b fb b3 09      bl      0x8000df98
80052c94  48 00 00 2c      b       0x80052cc0
80052c98  ec 3d e0 24      fdivs   f1, f29, f28
80052c9c  c0 1e 08 08      lfs     f0, 2056(r30)
80052ca0  ec 00 00 72      fmuls   f0, f0, f1
80052ca4  d0 1e 08 08      stfs    f0, 2056(r30)
80052ca8  c0 1e 08 0c      lfs     f0, 2060(r30)
80052cac  ec 00 00 72      fmuls   f0, f0, f1
80052cb0  d0 1e 08 0c      stfs    f0, 2060(r30)
80052cb4  c0 1e 08 10      lfs     f0, 2064(r30)
80052cb8  ec 00 00 72      fmuls   f0, f0, f1
80052cbc  d0 1e 08 10      stfs    f0, 2064(r30)
80052cc0  80 1d 00 00      lwz     r0, 0(r29)
80052cc4  3b de 00 1c      addi    r30, r30, 0x1c
80052cc8  3b bd 00 08      addi    r29, r29, 0x8
80052ccc  2c 00 00 00      cmpwi   r0, 0x0
80052cd0  40 82 fd 9c      bne     0x80052a6c
80052cd4  c0 5b 0a 04      lfs     f2, 2564(r27)
80052cd8  38 00 00 01      li      r0, 0x1
80052cdc  c0 02 8b 7c      lfs     f0, -29828(r2)
80052ce0  c0 3b 09 5c      lfs     f1, 2396(r27)
80052ce4  ec c2 00 2a      fadds   f6, f2, f0
80052ce8  c0 02 8b 6c      lfs     f0, -29844(r2)
80052cec  c0 82 8b 18      lfs     f4, -29928(r2)
80052cf0  ec a1 00 2a      fadds   f5, f1, f0
80052cf4  c0 62 8c 6c      lfs     f3, -29588(r2)
80052cf8  c0 42 8c 9c      lfs     f2, -29540(r2)
80052cfc  c0 3b 0a 00      lfs     f1, 2560(r27)
80052d00  c0 1b 0a 08      lfs     f0, 2568(r27)
80052d04  d0 db 0a 04      stfs    f6, 2564(r27)
80052d08  d0 bb 09 5c      stfs    f5, 2396(r27)
80052d0c  90 1b 0a 18      stw     r0, 2584(r27)
80052d10  d0 9b 0a 1c      stfs    f4, 2588(r27)
80052d14  d0 7b 0a 20      stfs    f3, 2592(r27)
80052d18  d0 5b 0a 24      stfs    f2, 2596(r27)
80052d1c  d0 3b 0a 38      stfs    f1, 2616(r27)
80052d20  d0 db 0a 3c      stfs    f6, 2620(r27)
80052d24  d0 1b 0a 40      stfs    f0, 2624(r27)
80052d28  e3 e1 00 78      psq_l   f31, 120(r1), 0x0, 0x0
80052d2c  cb e1 00 70      lfd     f31, 112(r1)
80052d30  e3 c1 00 68      psq_l   f30, 104(r1), 0x0, 0x0
80052d34  cb c1 00 60      lfd     f30, 96(r1)
80052d38  e3 a1 00 58      psq_l   f29, 88(r1), 0x0, 0x0
80052d3c  cb a1 00 50      lfd     f29, 80(r1)
80052d40  e3 81 00 48      psq_l   f28, 72(r1), 0x0, 0x0
80052d44  cb 81 00 40      lfd     f28, 64(r1)
80052d48  39 61 00 40      addi    r11, r1, 0x40
80052d4c  48 06 91 85      bl      0x800bbed0
80052d50  80 01 00 84      lwz     r0, 132(r1)
80052d54  7c 08 03 a6      mtlr    r0
80052d58  38 21 00 80      addi    r1, r1, 0x80
80052d5c  4e 80 00 20      blr
