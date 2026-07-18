/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_uniform_scale_matrix @ 0x44cde0 */

0044cdea        transform->basis_right.x = scale
0044cdee        transform->basis_right.y = 0f
0044cdf1        transform->basis_right.z = 0f
0044cdf4        transform->basis_right_w = 0f
0044cdf7        transform->basis_up.x = 0
0044cdfa        transform->basis_up.y = scale
0044cdfd        transform->basis_up.z = 0f
0044ce00        transform->basis_up_w = 0f
0044ce03        transform->basis_forward.x = 0
0044ce06        transform->basis_forward.y = 0f
0044ce09        transform->basis_forward.z = scale
0044ce0c        transform->basis_forward_w = 0f
0044ce0f        transform->position.x = 0
0044ce12        transform->position.y = 0f
0044ce15        transform->position.z = 0f
0044ce18        transform->position_w = 1f
0044ce1f        return transform
