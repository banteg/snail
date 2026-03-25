/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_enemy_manager_runtime @ 0x4086d0 */
/* selector: initialize_enemy_manager_runtime */

// Constructs the embedded enemy-manager runtime object by seeding its visible bods and child renderable entries before the later gameplay reset in `initialize_enemy_manager`. Its `0x1804` footprint matches the native `cREnemyManager` size ledger from `construct_game_runtime`.
_DWORD *__thiscall sub_4086D0(_DWORD *this)
{
  _DWORD *v2; // edi
  int v3; // ebx
  _DWORD *v4; // ebx
  int v5; // ebp

  initialize_renderable_bod(this);
  v2 = this + 83;
  v3 = 10;
  do
  {
    initialize_renderable_bod(v2);
    v2 += 32;
    --v3;
  }
  while ( v3 );
  initialize_renderable_bod(this + 403);
  Iostream_init::Iostream_init((#93 *)(this + 451));
  initialize_array_with_constructor((int)(this + 487), 128, 5, (int (__thiscall *)(int))initialize_renderable_bod);
  *(this + 403) = &off_49735C;
  initialize_renderable_bod(this + 650);
  Iostream_init::Iostream_init((#93 *)(this + 698));
  initialize_array_with_constructor((int)(this + 734), 128, 5, (int (__thiscall *)(int))initialize_renderable_bod);
  *(this + 650) = &off_49735C;
  initialize_renderable_bod(this + 897);
  Iostream_init::Iostream_init((#93 *)(this + 945));
  initialize_array_with_constructor((int)(this + 981), 128, 5, (int (__thiscall *)(int))initialize_renderable_bod);
  *(this + 897) = &off_49735C;
  initialize_renderable_bod(this + 1144);
  Iostream_init::Iostream_init((#93 *)(this + 1176));
  Iostream_init::Iostream_init((#93 *)(this + 1192));
  v4 = this + 1228;
  v5 = 5;
  do
  {
    initialize_renderable_bod(v4);
    v4 += 32;
    --v5;
  }
  while ( v5 );
  *(this + 1144) = &off_49735C;
  initialize_renderable_bod(this + 1395);
  initialize_renderable_bod(this + 1427);
  initialize_renderable_bod(this + 1573);
  *(this + 1573) = off_497358;
  *this = off_497354;
  return this;
}

