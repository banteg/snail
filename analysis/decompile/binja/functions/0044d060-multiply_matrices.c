/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_matrices @ 0x44d060 */

0044d07c        out->basis_right.x = fconvert.s(fconvert.t(lhs->basis_right.x) * fconvert.t(rhs->basis_right.x) + fconvert.t(lhs->basis_right.y) * fconvert.t(rhs->basis_up.x) + fconvert.t(lhs->basis_right.z) * fconvert.t(rhs->basis_forward.x))
0044d093        out->basis_right.y = fconvert.s(fconvert.t(lhs->basis_right.y) * fconvert.t(rhs->basis_up.y) + fconvert.t(rhs->basis_right.y) * fconvert.t(lhs->basis_right.x) + fconvert.t(rhs->basis_forward.y) * fconvert.t(lhs->basis_right.z))
0044d0ab        out->basis_right.z = fconvert.s(fconvert.t(lhs->basis_right.y) * fconvert.t(rhs->basis_up.z) + fconvert.t(rhs->basis_right.z) * fconvert.t(lhs->basis_right.x) + fconvert.t(rhs->basis_forward.z) * fconvert.t(lhs->basis_right.z))
0044d0c3        out->basis_up.x = fconvert.s(fconvert.t(lhs->basis_up.z) * fconvert.t(rhs->basis_forward.x) + fconvert.t(lhs->basis_up.y) * fconvert.t(rhs->basis_up.x) + fconvert.t(lhs->basis_up.x) * fconvert.t(rhs->basis_right.x))
0044d0dc        out->basis_up.y = fconvert.s(fconvert.t(lhs->basis_up.z) * fconvert.t(rhs->basis_forward.y) + fconvert.t(lhs->basis_up.y) * fconvert.t(rhs->basis_up.y) + fconvert.t(lhs->basis_up.x) * fconvert.t(rhs->basis_right.y))
0044d0f5        out->basis_up.z = fconvert.s(fconvert.t(lhs->basis_up.z) * fconvert.t(rhs->basis_forward.z) + fconvert.t(lhs->basis_up.y) * fconvert.t(rhs->basis_up.z) + fconvert.t(lhs->basis_up.x) * fconvert.t(rhs->basis_right.z))
0044d10d        out->basis_forward.x = fconvert.s(fconvert.t(lhs->basis_forward.x) * fconvert.t(rhs->basis_right.x) + fconvert.t(lhs->basis_forward.z) * fconvert.t(rhs->basis_forward.x) + fconvert.t(lhs->basis_forward.y) * fconvert.t(rhs->basis_up.x))
0044d126        out->basis_forward.y = fconvert.s(fconvert.t(rhs->basis_forward.y) * fconvert.t(lhs->basis_forward.z) + fconvert.t(rhs->basis_up.y) * fconvert.t(lhs->basis_forward.y) + fconvert.t(rhs->basis_right.y) * fconvert.t(lhs->basis_forward.x))
0044d13f        out->basis_forward.z = fconvert.s(fconvert.t(rhs->basis_forward.z) * fconvert.t(lhs->basis_forward.z) + fconvert.t(rhs->basis_up.z) * fconvert.t(lhs->basis_forward.y) + fconvert.t(rhs->basis_right.z) * fconvert.t(lhs->basis_forward.x))
0044d157        long double x87_r7_40 = fconvert.t(lhs->position.z) * fconvert.t(rhs->basis_forward.x) + fconvert.t(lhs->position.y) * fconvert.t(rhs->basis_up.x) + fconvert.t(lhs->position.x) * fconvert.t(rhs->basis_right.x) + fconvert.t(rhs->position.x)
0044d15a        out->position.x = fconvert.s(x87_r7_40)
0044d173        long double x87_r7_45 = fconvert.t(lhs->position.z) * fconvert.t(rhs->basis_forward.y) + fconvert.t(lhs->position.y) * fconvert.t(rhs->basis_up.y) + fconvert.t(lhs->position.x) * fconvert.t(rhs->basis_right.y) + fconvert.t(rhs->position.y)
0044d176        out->position.y = fconvert.s(x87_r7_45)
0044d18f        long double x87_r7_50 = fconvert.t(lhs->position.z) * fconvert.t(rhs->basis_forward.z) + fconvert.t(lhs->position.y) * fconvert.t(rhs->basis_up.z) + fconvert.t(lhs->position.x) * fconvert.t(rhs->basis_right.z) + fconvert.t(rhs->position.z)
0044d192        out->position.z = fconvert.s(x87_r7_50)
0044d195        return
