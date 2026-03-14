/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_death @ 0x446e30 */
/* selector: initialize_subgoldy_death */

// Chooses Goldy's death outcome from the current gameplay mode and visible life stock, then enters the resurrect state machine in either respawn or final-loss mode. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::DeathInit()`.
int __thiscall sub_446E30(_DWORD *this)
{
  int result; // eax

  result = *(_DWORD *)(*(this + 258) + 64);
  switch ( result )
  {
    case 0:
      if ( (int)*(this + 4304) > 0 )
        goto LABEL_4;
      goto LABEL_3;
    case 1:
    case 4:
LABEL_3:
      result = initialize_subgoldy_resurrect((int)this, 1);
      break;
    case 7:
LABEL_4:
      result = initialize_subgoldy_resurrect((int)this, 0);
      break;
    default:
      return result;
  }
  return result;
}

