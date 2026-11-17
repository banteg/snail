/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* export: isolated copy with manifest symbols applied */
/* function: initialize_galaxy_route_name_record @ 0x408880 */
/* selector: initialize_galaxy_route_name_record */

// Constructs one 0xa0-byte GalaxyRouteNameRecord by running the no-op tColour constructor on its color field at +0x84.
GalaxyRouteNameRecord *__thiscall initialize_galaxy_route_name_record(GalaxyRouteNameRecord *record)
{
  noop_this_constructor(&record->color);
  return record;
}
