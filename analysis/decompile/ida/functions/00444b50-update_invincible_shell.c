/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_invincible_shell @ 0x444b50 */
/* selector: update_invincible_shell */

// Advances the runner-owned invincible-shell controller: fades the shell in while the invincible movement-flag bit stays active, keeps the shell spinning on the shared snail matrix, and fades back to the base skin once invincibility clears.
void __thiscall update_invincible_shell(InvincibleShellController *shell)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  double spin_phase; // st7
  float angle; // [esp+0h] [ebp-10h]

  switch ( shell->state )
  {
    case 0:
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        *((_DWORD *)MEMORY[0x4DF904] + 1101798) &= ~0x20u;
      else
        start_invincible_shell(shell);
      return;
    case 1:
      v2 = shell->fade_step + shell->fade_progress;
      shell->fade_progress = v2;
      if ( v2 > 1.0 )
      {
        shell->fade_progress = 1.0;
        shell->state = 2;
      }
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        shell->state = 3;
      goto LABEL_15;
    case 2:
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        shell->state = 3;
      goto LABEL_15;
    case 3:
      v3 = shell->fade_progress - shell->fade_step;
      shell->fade_progress = v3;
      if ( v3 >= 0.0 )
      {
        if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) < 0 )
          shell->state = 1;
LABEL_15:
        v4 = shell->spin_phase_step + shell->spin_phase;
        shell->spin_phase = v4;
        if ( !(v6 | v7) )
          shell->spin_phase = v4 - 1.0;
        change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 2, 0.0);
        set_color_white(&shell->_pad_00[40]);
        *(float *)&shell->_pad_00[52] = shell->fade_progress * 0.80000001;
        spin_phase = shell->spin_phase;
        qmemcpy(&shell->_pad_00[56], (char *)&loc_432738 + (_DWORD)MEMORY[0x4DF904], 0x40u);
        angle = spin_phase * 6.2831855;
        rotate_matrix_world_y((TransformMatrix *)&shell->_pad_00[56], angle);
      }
      else
      {
        shell->fade_progress = 0.0;
        shell->state = 0;
        change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 0, 0.0);
      }
      return;
    default:
      goto LABEL_15;
  }
}

