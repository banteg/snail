/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_backdrop @ 0x410d50 */
/* selector: change_backdrop */

// Binds one parsed background script entry into the shared backdrop renderer, including its texture handles, Distort scalar, and split-vs-single draw mode. Cross-port Android and iOS symbols match this helper to `cRBackdrop::Change(cRLandscape*, bool)`.
void __thiscall change_backdrop(Backdrop *backdrop, LandscapeScriptRecord *record, uint8_t flip)
{
  int32_t v3; // edx
  int32_t backdrop_texture_id; // esi

  v3 = 0;
  backdrop_texture_id = record->backdrop_texture_id;
  if ( record->split_backdrop_texture_pair )
  {
    if ( backdrop_texture_id )
    {
      v3 = 1;
      backdrop->pending_split_backdrop_pair = 1;
      backdrop->backdrop_change_queued = 1;
      backdrop->pending_primary_texture_id = record->backdrop_texture_id;
      backdrop->pending_secondary_texture_id = record->backdrop_texture_id + 1;
LABEL_6:
      backdrop->pending_distort = record->distort;
      backdrop->pending_flip = flip;
    }
  }
  else if ( backdrop_texture_id )
  {
    backdrop->pending_split_backdrop_pair = 0;
    v3 = 1;
    backdrop->backdrop_change_queued = 1;
    backdrop->pending_primary_texture_id = record->backdrop_texture_id;
    goto LABEL_6;
  }
  backdrop->backdrop_render_enabled = v3;
}
