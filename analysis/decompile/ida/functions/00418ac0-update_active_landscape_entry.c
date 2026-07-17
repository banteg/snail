/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_active_landscape_entry @ 0x418ac0 */
/* selector: update_active_landscape_entry */

// Updates one active repeated landscape slice: state 1 wraps its inherited transform z offset by the recovered repeat span, then toggles the shared visibility bit against the reference BOD camera band.
void __thiscall update_active_landscape_entry(ActiveLandscapeEntry *active_entry)
{
  Object *object; // edx
  RenderableBod *reference_bod; // esi
  uint32_t list_flags; // eax

  if ( !g_game_base->subgame.subgame_pause_gate && active_entry->state == 1 )
  {
    object = active_entry->bod.bod.object;
    reference_bod = active_entry->reference_bod;
    if ( reference_bod->transform.position.z - 10.0 > object->bounds_max.z + active_entry->bod.transform.position.z )
      active_entry->bod.transform.position.z = active_entry->repeat_z_span * 3.0
                                             + active_entry->bod.transform.position.z;
    list_flags = active_entry->bod.bod.bod.list_flags;
    if ( g_game_base->fog_end + reference_bod->transform.position.z >= object->bounds_min.z
                                                                     + active_entry->bod.transform.position.z )
      LOBYTE(list_flags) = list_flags | 0x20;
    else
      LOBYTE(list_flags) = list_flags & 0xDF;
    active_entry->bod.bod.bod.list_flags = list_flags;
  }
}
