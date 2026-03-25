/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: configure_sprite_render_state @ 0x413670 */
/* selector: configure_sprite_render_state */

// Chooses the sprite render-state preset from the sprite draw-mode lane at `+0x28` before one sprite quad is submitted.
int __cdecl sub_413670(int a1)
{
  int result; // eax

  result = *(_DWORD *)(a1 + 40);
  switch ( result )
  {
    case 0:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 6);
      break;
    case 1:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 1);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 6);
      break;
    case 2:
      result = (*(int (__stdcall **)(int, int, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 0);
      break;
    case 9:
    case 10:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 2);
      break;
    case 13:
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 27, 1);
      (*(void (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 19, 5);
      result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 200))(MEMORY[0x502FEC], 20, 3);
      break;
    default:
      return result;
  }
  return result;
}

