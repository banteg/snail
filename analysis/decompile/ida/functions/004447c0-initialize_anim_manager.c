/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_anim_manager @ 0x4447c0 */
/* selector: initialize_anim_manager */

// Exact void `cRAnimManager::Init()`: clears the state, progress, progress step, and completion latch of the authored 0x48-byte queued animation owner. Android preserves the same offsets and void contract.
void __thiscall initialize_anim_manager(AnimManager *manager)
{
  manager->progress = 0.0;
  manager->progress_step = 0.0;
  manager->state = 0;
  manager->completed = 0;
}
