/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: font_slot_index_for_char @ 0x449d20 */

00449d20        int32_t eax
00449d20        eax.b = arg1
00449d2a        if (eax.b s>= 0x41 && eax.b s<= 0x5a)
00449d32        return sx.d(eax.b) - 0x26
00449d39        if (eax.b s>= 0x61 && eax.b s<= 0x7a)
00449d41        return sx.d(eax.b) - 0x60
00449d48        if (eax.b s>= 0x30 && eax.b s<= 0x39)
00449d50        return sx.d(eax.b) + 6
00449d53        if (eax.b == 0x20)
00449d5a        return 0x35
00449d64        if (sx.d(eax.b) == 0x2222)
00449d6b        return 0x40
00449d6e        switch (eax.b)
00449d8a        case 0x21
00449d93        return 0x45
00449d9e        case 0x23
00449da7        return 0x47
00449da8        case 0x24
00449db1        return 0x48
00449db2        case 0x25
00449dbb        return 0x49
00449dc6        case 0x26
00449dcf        return 0x4b
00449e16        case 0x27
00449e1f        return 0x54
00449d76        case 0x28
00449d7f        return 0x43
00449d80        case 0x29
00449d89        return 0x44
00449dd0        case 0x2a
00449dd9        return 0x4c
00449dda        case 0x2b
00449de3        return 0x4d
00449e02        case 0x2c
00449e0b        return 0x52
00449de4        case 0x2d
00449ded        return 0x4f
00449e0c        case 0x2e
00449e15        return 0x53
00449dee        case 0x2f
00449df7        return 0x50
00449d6c        case 0x3a
00449d75        return 0x42
00449e5c        case 0x3b
00449e65        return 0x5b
00449dbc        case 0x3f
00449dc5        return 0x4a
00449d94        case 0x40
00449d9d        return 0x46
00449e3e        case 0x5b
00449e47        return 0x58
00449df8        case 0x5c
00449e01        return 0x51
00449e48        case 0x5d
00449e51        return 0x59
00449e70        case 0x5e
00449e79        return 0x5d
00449e66        case 0x5f
00449e6f        return 0x5c
00449e2a        case 0x7b
00449e33        return 0x56
00449e20        case 0x7c
00449e29        return 0x55
00449e34        case 0x7d
00449e3d        return 0x57
00449e52        case 0x7e
00449e5b        return 0x5a
00449e7a        eax.b -= 0x3d
00449e7c        char temp0 = eax.b
00449e7c        eax.b = neg.b(eax.b)
00449e80        int32_t eax_36
00449e80        eax_36.b = sbb.d(eax, eax, temp0 != 0).b & 0xd7
00449e85        return eax_36 + 0x5e
