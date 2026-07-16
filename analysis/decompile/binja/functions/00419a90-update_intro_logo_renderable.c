/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_intro_logo_renderable @ 0x419a90 */

00419a99        letter->renderable.transform.position.x = fconvert.s(fconvert.t(letter->velocity.x) + fconvert.t(letter->renderable.transform.position.x))
00419aa5        letter->renderable.transform.position.y = fconvert.s(fconvert.t(letter->velocity.y) + fconvert.t(letter->renderable.transform.position.y))
00419ab1        letter->renderable.transform.position.z = fconvert.s(fconvert.t(letter->velocity.z) + fconvert.t(letter->renderable.transform.position.z))
00419ab4        long double x87_r7_5 = fconvert.t(letter->renderable.transform.position.z)
00419ab7        long double temp0 = fconvert.t(8f)
00419ab7        x87_r7_5 - temp0
00419ac2        if ((((x87_r7_5 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp0) ? 1 : 0) << 0xa | (x87_r7_5 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00419ae4        letter->renderable.bod.color.a = 0.999000013f
00419adf        letter->renderable.bod.color.a = fconvert.s((fconvert.t(1f) - (fconvert.t(letter->renderable.transform.position.z) - fconvert.t(8f)) * fconvert.t(0.125f)) * fconvert.t(0.999000013f))
00419aeb        struct Object* object = letter->renderable.bod.object
00419aee        object->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW
00419af2        long double x87_r7_11 = fconvert.t(letter->renderable.transform.position.z)
00419af5        long double temp1 = fconvert.t(16f)
00419af5        x87_r7_11 - temp1
00419b00        if ((((x87_r7_11 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp1) ? 1 : 0) << 0xa | (x87_r7_11 == temp1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00419b02        long double x87_r7_12 = fconvert.t(letter->renderable.transform.position.z)
00419b05        long double temp2_1 = fconvert.t(-4f)
00419b05        x87_r7_12 - temp2_1
00419b10        if ((((x87_r7_12 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp2_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00419b12        uint32_t list_flags = letter->renderable.bod.bod.list_flags
00419b15        list_flags.b |= 0x20
00419b17        letter->renderable.bod.bod.list_flags = list_flags
00419b1a        return
00419b1b        uint32_t list_flags_1 = letter->renderable.bod.bod.list_flags
00419b1e        list_flags_1.b &= 0xdf
00419b20        letter->renderable.bod.bod.list_flags = list_flags_1
00419b23        return
