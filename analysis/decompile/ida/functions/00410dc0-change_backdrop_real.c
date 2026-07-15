/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_backdrop_real @ 0x410dc0 */
/* selector: change_backdrop_real */

// Commits the pending backdrop selection, refreshes the distortion grid when the world index changes, and copies the current split-vs-single draw flags into the active renderer state. Cross-port Android and iOS symbols match this helper to `cRBackdrop::ChangeReal()`.
void __thiscall change_backdrop_real(Backdrop *backdrop)
{
  int32_t pending_primary_texture_id; // eax
  uint8_t pending_flip; // dl
  uint8_t pending_split_backdrop_pair; // al
  uint8_t v5; // dl
  int v6; // eax

  pending_primary_texture_id = backdrop->pending_primary_texture_id;
  if ( pending_primary_texture_id )
  {
    if ( pending_primary_texture_id != backdrop->active_primary_texture_id )
    {
      backdrop->active_primary_texture_id = pending_primary_texture_id;
      backdrop->active_secondary_texture_id = backdrop->pending_secondary_texture_id;
    }
    backdrop->zoom = 0.0;
    set_backdrop_distort(backdrop, backdrop->pending_distort);
    pending_flip = backdrop->pending_flip;
    pending_split_backdrop_pair = backdrop->pending_split_backdrop_pair;
    backdrop->backdrop_render_enabled = 1;
    backdrop->active_flip = pending_flip;
    backdrop->active_split_backdrop_pair = pending_split_backdrop_pair;
  }
  else
  {
    v5 = backdrop->pending_flip;
    v6 = backdrop->pending_split_backdrop_pair;
    backdrop->backdrop_render_enabled = 0;
    backdrop->active_flip = v5;
    backdrop->active_split_backdrop_pair = v6;
  }
}
