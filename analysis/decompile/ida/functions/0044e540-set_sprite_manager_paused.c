/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_sprite_manager_paused @ 0x44e540 */
/* selector: set_sprite_manager_paused */

// Writes the shared sprite-manager pause byte consumed by `update_sprite`, freezing or unfreezing sprite updates globally. iOS RSprite.o names this `cRSpriteManager::Pause(bool)`.
uint8_t __thiscall set_sprite_manager_paused(SpriteManager *manager, uint8_t paused)
{
  manager->paused = paused;
  return paused;
}
