/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: game_window_proc @ 0x4074b0 */
/* selector: game_window_proc */

// Primary Win32 window procedure for the game's main window. It handles activation and minimize transitions, ESC-to-quit, left and right mouse button latches, and mouse-wheel delta capture before delegating the rest to DefWindowProcA.
int __stdcall game_window_proc(int hWnd, unsigned int Msg, int wParam, int lParam)
{
  int result; // eax

  if ( Msg > 0x200 )
  {
    switch ( Msg )
    {
      case 0x201u:
        unk_4B7764[0] = 1;
        unk_4B7234[0] = 1;
        result = 0;
        break;
      case 0x202u:
        unk_4B7764[0] = 0;
        unk_4B7234[0] = 0;
        result = 0;
        break;
      case 0x204u:
        unk_4B7230[0] = 1;
        LOBYTE(flt_4B763C[1]) = 1;
        result = 0;
        break;
      case 0x205u:
        unk_4B7230[0] = 0;
        LOBYTE(flt_4B763C[1]) = 0;
        result = 0;
        break;
      case 0x20Au:
        goto LABEL_19;
      default:
LABEL_28:
        result = ((int (__stdcall *)(int, unsigned int, int, int))DefWindowProcA)(hWnd, Msg, wParam, lParam);
        break;
    }
  }
  else if ( Msg == 512 )
  {
LABEL_19:
    if ( SHIWORD(wParam) <= 0 )
    {
      if ( wParam < 0 )
        unk_4DFAD0[0] = -1;
      return 0;
    }
    else
    {
      unk_4DFAD0[0] = 1;
      return 0;
    }
  }
  else
  {
    switch ( Msg )
    {
      case 2u:
        goto LABEL_5;
      case 5u:
        if ( wParam == 1 )
        {
          sub_449C00();
          pause_audio_backend_if_running(unk_753C58);
          unk_4B7654 = 1;
          restore_desktop_display_mode();
          return 0;
        }
        else
        {
          if ( !wParam )
          {
            resume_audio_backend_if_paused(unk_753C58);
            unk_4B7654 = 0;
            flt_4DFAFC[1] = (double)(unsigned int)((int (*)(void))timeGetTime)() * 0.001;
            sub_407920(unk_4DF9E0);
          }
          return 0;
        }
      case 6u:
        if ( (_WORD)wParam )
        {
          if ( (unsigned __int16)wParam == 1 )
          {
            resume_audio_backend_if_paused(unk_753C58);
            sub_449C00();
            handle_game_window_activate();
          }
          return 0;
        }
        else
        {
          pause_audio_backend_if_running(unk_753C58);
          sub_449C00();
          handle_game_window_deactivate();
          return 0;
        }
      case 0x10u:
        goto LABEL_4;
      case 0x100u:
        if ( wParam == 27 )
        {
LABEL_4:
          PostQuitMessage(0);
LABEL_5:
          result = 0;
        }
        else
        {
          result = 0;
        }
        break;
      default:
        goto LABEL_28;
    }
  }
  return result;
}

