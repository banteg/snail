/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_zoom @ 0x410c30 */
/* selector: set_backdrop_zoom */

// Exact `cRBackdrop::SetZoom(float)`: stores the active backdrop zoom at +0x6c8. Windows `update_subgoldy` drives it from the normalized current track-row payload ratio, while Android and iOS independently preserve the authored owner and signature.
void __thiscall set_backdrop_zoom(cRBackdrop *backdrop, float zoom)
{
  backdrop->zoom = zoom;
}
