/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_border_record @ 0x408410 */
/* selector: initialize_border_record */

// Constructs one 0x724-byte front-end border/widget pool record by seeding the shared BOD header, no-op-constructing the constructor-proven color/style blocks, and installing the front-end widget callback table. `construct_game_runtime` uses it for the 150-entry `BorderManager::borders` pool at `game + 0x11d0`.
BorderRecord *__thiscall initialize_border_record(BorderRecord *record)
{
  initialize_bod_base((BodBase *)record);
  noop_this_constructor(&record->color_06c);
  noop_this_constructor(&record->color_1ac);
  noop_this_constructor(&record->color_1bc);
  noop_this_constructor(&record->color_1cc);
  noop_this_constructor(&record->color_1dc);
  noop_this_constructor(&record->color_1ec);
  noop_this_constructor(&record->color_1fc);
  record->vtable = &g_frontend_widget_vtable;
  return record;
}
