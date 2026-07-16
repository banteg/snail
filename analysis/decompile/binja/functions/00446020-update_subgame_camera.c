/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgame_camera @ 0x446020 */

00446036        int32_t subgame_state = runtime->subgame_state
00446042        struct TransformMatrix from
00446042        __builtin_memcpy(&from, &g_game_base->players[0].transform, 0x40)
00446047        runtime->camera_snap_requested = 0
0044604b        struct TransformMatrix var_80
0044604b        if (subgame_state != 1)
00446078        update_cameraman(&runtime->player.cameraman)
00446085        if (runtime->player.presentation.cutscene.state == CUT_SCENE_STATE_INACTIVE)
004460bb        float fov_degrees = runtime->player.cameraman.fov_degrees
004460c1        __builtin_memcpy(&var_80, &runtime->player.cameraman, 0x40)
004460c9        runtime->camera_snap_requested = runtime->player.cameraman.force_camera_update
004460d1        g_game_base->players[0].camera.fov_degrees = fov_degrees
00446093        runtime->camera_snap_requested = runtime->player.presentation.cutscene.force_camera_update
00446096        struct GameRoot* game_base_1 = g_game_base
004460a4        __builtin_memcpy(&var_80, &runtime->player.presentation.cutscene.live_matrix, 0x40)
004460a6        game_base_1->players[0].camera.fov_degrees = 110f
00446051        set_matrix_identity(&var_80)
0044605c        var_80.position.y = 0x40400000
00446064        g_game_base->players[0].camera.fov_degrees = 110f
004460dc        if (runtime->camera_snap_requested == 0)
00446103        struct GameRoot* game_base_2 = g_game_base
0044610d        float alpha
0044610d        __builtin_strncpy(&alpha, "fff?", 4)
0044611e        linear_interpolate_matrix(&game_base_2->players[0].transform, &from, &var_80, alpha)
0044612c        return
004460f3        __builtin_memcpy(&g_game_base->players[0].transform, &var_80, 0x40)
004460f6        runtime->camera_snap_requested = 0
00446102        return
