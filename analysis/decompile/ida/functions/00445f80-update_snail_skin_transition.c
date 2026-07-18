/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin_transition @ 0x445f80 */
/* selector: update_snail_skin_transition */

// Exact Windows `SnailSkin::update_snail_skin_transition`, authored as `cRSnailSkin::AI`: follows the borrowed Snail backlink, marks its linked Object dirty, installs the selected TextureRef override, and advances the timed reset state.
void __thiscall update_snail_skin_transition(SnailSkin *snail_skin)
{
  double v1; // st7

  snail_skin->owner_snail->body.bod.object->flags |= 8u;
  snail_skin->owner_snail->body.bod.object->override_texture_ref = snail_skin->material_overrides[snail_skin->selected_slot];
  if ( snail_skin->active == 1 )
  {
    v1 = snail_skin->progress_step + snail_skin->progress;
    snail_skin->progress = v1;
    if ( v1 > 1.0 )
    {
      snail_skin->progress = 0.0;
      snail_skin->active = 0;
      snail_skin->selected_slot = 0;
    }
  }
}
