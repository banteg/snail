/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_star_field @ 0x4342c0 */
/* selector: open_star_field */

// Allocates the persistent star-field controller storage and, when the global star-pass flag is enabled, immediately initializes the live streak sprite pool for the requested slot count.
void __thiscall open_star_field(StarManager *manager, int32_t star_count)
{
  manager->entries = (StarManagerEntry *)allocate_tracked_memory(44 * star_count, (int)aStarfield);
  manager->count = star_count;
  if ( (g_render_flags & 4) != 0 )
  {
    manager->state = 1;
    initialize_star_field(manager);
  }
  else
  {
    manager->state = 0;
  }
}

