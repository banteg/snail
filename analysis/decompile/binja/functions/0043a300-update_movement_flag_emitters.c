/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_movement_flag_emitters @ 0x43a300 */

0043a307        uint8_t movement_flags = (movement_source->movement_flags).b
0043a312        int32_t spawn_selector
0043a312        if ((movement_flags & 0x69) != 0)
0043a32a        spawn_selector = 1
0043a32f        label_43a32f:
0043a32f        int32_t emitter_index = 0
0043a331        struct GolbShot (* shot)[0xc] = &owner->golb_shots
0043a33f        if ((shot - 0x450)->golb_shots[0].state == 0)
0043a346        create_golb(shot, owner, spawn_selector, emitter_index)
0043a34b        int32_t spawn_selector_1 = spawn_selector
0043a34b        spawn_selector -= 1
0043a34c        if (spawn_selector_1 == 1)
0043a34c        break
0043a34e        emitter_index += 1
0043a34f        shot = &(*shot)[1]
0043a358        do while (emitter_index s< 0xc)
0043a316        if ((movement_flags & 0x12) != 0)
0043a323        spawn_selector = 2
0043a328        goto label_43a32f
0043a31a        if ((movement_flags & 4) != 0)
0043a31c        spawn_selector = 3
0043a321        goto label_43a32f
0043a35e        return
