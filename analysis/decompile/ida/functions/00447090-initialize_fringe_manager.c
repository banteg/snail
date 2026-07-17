/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_fringe_manager @ 0x447090 */
/* selector: initialize_fringe_manager */

// Resets the shared fringe-manager pool counter at `data_4df904 + 0x3d01d4` before one track rebuild emits directional fringe objects. Cross-port Android symbols match this helper to `cRFringeManager::Init()`.
void __thiscall initialize_fringe_manager(FringeManager *manager)
{
  manager->count = 0;
}
