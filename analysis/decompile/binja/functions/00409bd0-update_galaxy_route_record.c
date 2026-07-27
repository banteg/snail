/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_galaxy_route_record @ 0x409bd0 */

00409bdf        star->record.route_tint_alpha = fconvert.s((fconvert.t(star->record.highlight_target) - fconvert.t(star->record.route_tint_alpha)) * fconvert.t(0.100000001f) + fconvert.t(star->record.route_tint_alpha))
00409be2        return
