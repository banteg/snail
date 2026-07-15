/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_progress_fraction @ 0x410c30 */
/* selector: set_backdrop_progress_fraction */

// Stores the active backdrop zoom at +0x6c8. Windows `update_subgoldy` drives it from the normalized current track-row payload ratio, while symbol-preserving iOS builds name the corresponding authored member `cRBackdrop::SetZoom(float)`.
void __thiscall set_backdrop_progress_fraction(Backdrop *backdrop, float zoom)
{
  backdrop->zoom = zoom;
}
