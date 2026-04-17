/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_blend_mode @ 0x412d00 */
/* selector: set_blend_mode */

// Maps one render blend preset through the shared lookup table and programs the matching alpha-blend state. Cross-port Android symbols match this helper to `G0SetBlend(int)`.
int __cdecl sub_412D00(int a1)
{
  int result; // eax

  result = a1;
  switch ( a1 )
  {
    case 0:
    case 6:
    case 9:
    case 12:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 6);
      break;
    case 1:
    case 8:
    case 20:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      goto LABEL_7;
    case 5:
    case 13:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 2);
      break;
    case 7:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 2);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 2);
      break;
    case 19:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 2);
LABEL_7:
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 6);
      break;
    default:
      return result;
  }
  return result;
}

