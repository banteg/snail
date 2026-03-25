/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_smtracks @ 0x441f60 */
/* selector: update_smtracks */

// Advances the `cRSMTracks` manager's active frame sequence, copies the live replacement scalar into the selected SMTrack texture slot, and resamples the active source texture into the runtime height grid.
void __thiscall update_smtracks(int *this)
{
  advance_frame_sequence((int)(this + 14));
  *(_DWORD *)(*(_DWORD *)(*(this + 9) + 92) + 12) = *(this + 73);
  sample_smtrack_heightmap(*(this + 9), 0.0, 5.0, *(this + 73), 0);
}

