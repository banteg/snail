/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_snail_skin @ 0x445f60 */
/* selector: initialize_snail_skin */

// Exact Windows `SnailSkin::initialize_snail_skin`, authored as `cRSnailSkin::Init`: clears the 0x20-byte child state and stores its borrowed `Snail*` parent backlink. iOS v1.9 exposes that parent explicitly as `cRSnailSkin::Init(cRSnail*)`; Android retains the no-argument member.
void __thiscall initialize_snail_skin(SnailSkin *snail_skin)
{
  GameRoot *v1; // eax

  v1 = g_game_base;
  snail_skin->selected_slot = 0;
  snail_skin->active = 0;
  snail_skin->owner_snail = &v1->subgame.player.presentation;
}
