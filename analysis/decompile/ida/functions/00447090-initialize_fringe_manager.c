/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_fringe_manager @ 0x447090 */
/* selector: initialize_fringe_manager */

// Resets the shared cRFringeManager pool counter at `data_4df904 + 0x3d01d4` before one track rebuild emits directional fringe objects. Cross-port Android symbols preserve `cRFringeManager::Init()`.
void __thiscall initialize_fringe_manager(cRFringeManager *manager)
{
  manager->count = 0;
}
