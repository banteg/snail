/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_object_facequad_uv_pairs @ 0x430a30 */

00430a39        quad->uv[0].u = quad->uv[1].u
00430a3f        quad->uv[3].u = fconvert.s(fconvert.t(quad->uv[0].u))
00430a45        quad->uv[1].u = quad->uv[2].u
00430a4b        quad->uv[2].u = quad->uv[3].u
00430a51        quad->uv[0].v = quad->uv[1].v
00430a57        quad->uv[3].v = fconvert.s(fconvert.t(quad->uv[0].v))
00430a5a        quad->uv[1].v = quad->uv[2].v
00430a5d        quad->uv[2].v = quad->uv[3].v
00430a60        return
