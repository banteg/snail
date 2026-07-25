/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_ring_or_special_effect_particle @ 0x43e780 */

0043e790        if (particle->parent->kind != SUB_RING_KIND_SLOW_DEFAULT)
0043e798        particle->phase = fconvert.s(fconvert.t(particle->phase_step) + fconvert.t(particle->phase))
0043e79b        long double x87_r7_3 = fconvert.t(particle->phase)
0043e79e        long double temp0 = fconvert.t(6.28318548f)
0043e79e        x87_r7_3 - temp0
0043e7a9        if ((((x87_r7_3 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0) ? 1 : 0) << 0xa | (x87_r7_3 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0043e7b4        particle->phase = fconvert.s(fconvert.t(particle->phase) - fconvert.t(6.28318548f))
0043e7c0        long double x87_r7_7 = cosine(particle->phase) * fconvert.t(particle->radius)
0043e7cb        long double st0_1 = sine(particle->phase)
0043e7d0        struct SubRing* parent = particle->parent
0043e80b        particle->sprite->position.x.12 = struct Vec3 {
    .x = fconvert.s(st0_1 * fconvert.t(particle->radius) + fconvert.t(parent->body.transform.position.x))
    .y = fconvert.s(fconvert.t(fconvert.s(x87_r7_7)) + fconvert.t(parent->body.transform.position.y))
    .z = parent->body.transform.position.z
}
0043e80e        struct SubRing* result_parent = particle->parent
0043e819        if (result_parent->star_shower_counter == 0)
0043e824        emit_ring_star_shower(particle, result_parent->owner_player)
0043e82d        return
