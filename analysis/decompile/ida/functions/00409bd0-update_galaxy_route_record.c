/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_galaxy_route_record @ 0x409bd0 */
/* selector: update_galaxy_route_record */

// Exact Windows `cRGalaxyStar::AI`: interpolates one 0x2a0-byte GalaxyStar child's tint alpha at +0x18 toward its highlight target at +0x1c by 0.1. Android retains the named member and identical child-relative expression; iOS inlines it inside `cRGalaxy::AI()` over the same stride.
void __thiscall update_galaxy_route_record(GalaxyStar *star)
{
  star->record.route_tint_alpha = (star->record.highlight_target - star->record.route_tint_alpha) * 0.1
                                + star->record.route_tint_alpha;
}
