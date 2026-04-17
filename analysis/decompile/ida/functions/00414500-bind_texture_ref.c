/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: bind_texture_ref @ 0x414500 */
/* selector: bind_texture_ref */

// Binds one texture ref, skips redundant binds through the cached current-texture lane, and applies the texture-stage wrap-vs-clamp state from the ref flags. Cross-port Android symbols match this helper to `G0BindTexture(int)`.
int __cdecl sub_414500(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // ecx

  result = MEMORY[0x503174];
  if ( a1 != MEMORY[0x503174] )
  {
    MEMORY[0x503174] = a1;
    v2 = (*(int (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 244))(
           MEMORY[0x502FEC],
           0,
           *(_DWORD *)(MEMORY[0x5031C8] + 4 * *(_DWORD *)(a1 + 140)));
    ++MEMORY[0x5031C0];
    if ( v2 )
    {
      return report_errorf("SetTexture Failed %s", (const char *)(a1 + 12));
    }
    else
    {
      v3 = *(_DWORD *)MEMORY[0x502FEC];
      if ( (*(_DWORD *)a1 & 0x1000) != 0 )
      {
        (*(void (__stdcall **)(int, _DWORD, int, int))(v3 + 252))(MEMORY[0x502FEC], 0, 13, 1);
        return (*(int (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 252))(
                 MEMORY[0x502FEC],
                 0,
                 14,
                 1);
      }
      else
      {
        (*(void (__stdcall **)(int, _DWORD, int, int))(v3 + 252))(MEMORY[0x502FEC], 0, 13, 3);
        return (*(int (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 252))(
                 MEMORY[0x502FEC],
                 0,
                 14,
                 3);
      }
    }
  }
  return result;
}

