/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_loading_screen @ 0x418e50 */
/* selector: destroy_loading_screen */

// Exact void cRLoadingBar::UnInit(): tears down the loading-screen textures and preserves the last measured loading budget. Startup discards the final COM Release value left in EAX.
void __thiscall destroy_loading_screen(cRLoadingBar *loading_bar)
{
  g_runtime_config.last_loading_budget = loading_bar->last_loading_budget;
  g_loading_background_texture->vtbl->Release(g_loading_background_texture);
  g_loading_bar_on_texture->vtbl->Release(g_loading_bar_on_texture);
  loading_bar->active = 0;
}
