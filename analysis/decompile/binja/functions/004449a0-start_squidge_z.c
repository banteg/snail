/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: start_squidge_z @ 0x4449a0 */

004449ae        squidge->z_phase = value
004449b1        squidge->z_velocity = fconvert.s(fconvert.t(value) * fconvert.t(-0.00300000003f))
004449b4        return
