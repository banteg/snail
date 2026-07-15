/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_loading_screen @ 0x418e50 */
/* selector: destroy_loading_screen */

// Exact void cRLoadingBar::UnInit(): tears down the loading-screen textures and preserves the last measured loading budget. Startup discards the final COM Release value left in EAX.
void __thiscall destroy_loading_screen(LoadingBar *loading_bar)
{
  g_runtime_config.last_loading_budget = loading_bar->last_loading_budget;
  (*(void (__stdcall **)(int))(*(_DWORD *)g_loading_background_texture + 8))(g_loading_background_texture);
  (*(void (__stdcall **)(int))(*(_DWORD *)g_loading_bar_on_texture + 8))(g_loading_bar_on_texture);
  loading_bar->active = 0;
}
