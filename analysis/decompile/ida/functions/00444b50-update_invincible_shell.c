/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_invincible_shell @ 0x444b50 */
/* selector: update_invincible_shell */

// Advances the runner-owned invincible-shell controller: fades the shell in while the invincible movement-flag bit stays active, keeps the shell spinning on the shared snail matrix, and fades back to the base skin once invincibility clears.
void __thiscall sub_444B50(int this)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  double v8; // st7
  float v9; // [esp+0h] [ebp-10h]

  switch ( *(_DWORD *)(this + 128) )
  {
    case 0:
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        *((_DWORD *)MEMORY[0x4DF904] + 1101798) &= ~0x20u;
      else
        start_invincible_shell((_DWORD *)this);
      return;
    case 1:
      v2 = *(float *)(this + 144) + *(float *)(this + 140);
      *(float *)(this + 140) = v2;
      if ( v2 > 1.0 )
      {
        *(_DWORD *)(this + 140) = 1065353216;
        *(_DWORD *)(this + 128) = 2;
      }
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        *(_DWORD *)(this + 128) = 3;
      goto LABEL_15;
    case 2:
      if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) >= 0 )
        *(_DWORD *)(this + 128) = 3;
      goto LABEL_15;
    case 3:
      v3 = *(float *)(this + 140) - *(float *)(this + 144);
      *(float *)(this + 140) = v3;
      if ( v3 >= 0.0 )
      {
        if ( *((char *)&loc_4300B4 + (_DWORD)MEMORY[0x4DF904]) < 0 )
          *(_DWORD *)(this + 128) = 1;
LABEL_15:
        v4 = *(float *)(this + 136) + *(float *)(this + 132);
        *(float *)(this + 132) = v4;
        if ( !(v6 | v7) )
          *(float *)(this + 132) = v4 - 1.0;
        change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 2, 0.0);
        set_color_white((_DWORD *)(this + 40));
        *(float *)(this + 52) = *(float *)(this + 140) * 0.80000001;
        v8 = *(float *)(this + 132);
        qmemcpy((void *)(this + 56), (char *)&loc_432738 + (_DWORD)MEMORY[0x4DF904], 0x40u);
        v9 = v8 * 6.2831855;
        rotate_matrix_world_y((float *)(this + 56), v9);
      }
      else
      {
        *(_DWORD *)(this + 140) = 0;
        *(_DWORD *)(this + 128) = 0;
        change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 0, 0.0);
      }
      return;
    default:
      goto LABEL_15;
  }
}

