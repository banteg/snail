/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_subgame_contact_target @ 0x415ef0 */

00415efa        if (((object->list_flags).w:1.b & 0x10) != 0)
00415efa        return
00415f0b        registry->entries[registry->count].kind = kind
00415f0f        int32_t count = registry->count
00415f1e        registry->entries[count].position.x = position->x
00415f23        registry->entries[count].position.y = position->y
00415f2a        registry->entries[count].position.z = position->z
00415f33        registry->entries[registry->count].radius = fconvert.s(fconvert.t(radius))
00415f3d        *(registry + (registry->count + 1) * 0x18) = object
00415f43        registry->count += 1
00415f45        return
