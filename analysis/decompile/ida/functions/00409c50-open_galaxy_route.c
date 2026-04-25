/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_galaxy_route @ 0x409c50 */
/* selector: open_galaxy_route */

// Opens one selected Star Map route card, loads its preview label and widget stack, and toggles the replay-only controls for locked or cleared routes. Cross-port Android and iOS symbols match this helper to `cRGalaxy::Open(int)`.
int __thiscall sub_409C50(int this, float a2)
{
  float v2; // eax
  _DWORD *v4; // ecx
  double v5; // st7
  int result; // eax
  int v7; // [esp-4h] [ebp-14h]
  float v8; // [esp+4h] [ebp-Ch] BYREF
  float v9; // [esp+8h] [ebp-8h] BYREF
  float v10; // [esp+Ch] [ebp-4h] BYREF

  v2 = a2;
  v4 = *(_DWORD **)(this + 69520);
  *(_DWORD *)(this + 8) = 1;
  *(float *)(this + 69504) = v2;
  unhide_border_init(v4);
  rstrcpy_checked_ascii(
    (char *)(*(_DWORD *)(this + 69520) + 716),
    (char *)(160 * *(_DWORD *)(672 * *(_DWORD *)(this + 69504) + this + 20) + this + 67888));
  *(float *)(*(_DWORD *)(this + 69520) + 1780) = *(float *)(672 * *(_DWORD *)(this + 69504) + this + 28) + 60.0;
  *(float *)(*(_DWORD *)(this + 69520) + 1784) = *(float *)(672 * *(_DWORD *)(this + 69504) + this + 32) - 130.0;
  do
  {
    layout_frontend_widget(*(_DWORD *)(this + 69520));
    unhide_border_init(*(_DWORD **)(this + 69524));
    rstrcpy_checked_ascii(
      (char *)(*(_DWORD *)(this + 69524) + 716),
      (char *)(672 * *(_DWORD *)(this + 69504) + this + 48));
    stack_widget_below(*(_DWORD *)(this + 69524), *(_DWORD *)(this + 69520));
    unhide_border_init(*(_DWORD **)(this + 69528));
    rstrcpy_checked_ascii(
      (char *)(*(_DWORD *)(this + 69528) + 716),
      (char *)(672 * *(_DWORD *)(this + 69504) + this + 176));
    stack_widget_below(*(_DWORD *)(this + 69528), *(_DWORD *)(this + 69524));
    unhide_border_init(*(_DWORD **)(this + 69532));
    *(float *)(*(_DWORD *)(this + 69532) + 608) = *(float *)(*(_DWORD *)(this + 69520) + 584) * 0.5
                                                + *(float *)(*(_DWORD *)(this + 69520) + 568)
                                                - 320.0;
    stack_widget_below(*(_DWORD *)(this + 69532), *(_DWORD *)(this + 69528));
    if ( *(_DWORD *)(129728 * *(_DWORD *)(this + 69504) + *(_DWORD *)(this + 69488) + 9716048) == 1
      && *(_DWORD *)(this + 4) == 2 )
    {
      unhide_border_init(*(_DWORD **)(this + 69536));
      *(float *)(*(_DWORD *)(this + 69536) + 608) = *(float *)(*(_DWORD *)(this + 69520) + 584) * 0.5
                                                  + *(float *)(*(_DWORD *)(this + 69520) + 568)
                                                  - 320.0;
      stack_widget_below(*(_DWORD *)(this + 69536), *(_DWORD *)(this + 69528));
      stack_widget_below(*(_DWORD *)(this + 69532), *(_DWORD *)(this + 69536));
    }
    else
    {
      hide_border_init(*(_DWORD **)(this + 69536));
    }
    unhide_border_init(*(_DWORD **)(this + 69516));
    v7 = *(_DWORD *)(this + 69520);
    v9 = 1000.0;
    a2 = -1000.0;
    v10 = 1000.0;
    v8 = -1000.0;
    galaxy_border_bound(&v9, &a2, &v10, &v8, v7);
    galaxy_border_bound(&v9, &a2, &v10, &v8, *(_DWORD *)(this + 69524));
    galaxy_border_bound(&v9, &a2, &v10, &v8, *(_DWORD *)(this + 69528));
    galaxy_border_bound(&v9, &a2, &v10, &v8, *(_DWORD *)(this + 69532));
    v8 = v8 + 8.0;
    v9 = v9 - 8.0;
    v5 = a2 + 8.0;
    a2 = v5;
    if ( v5 > 630.0 )
      *(float *)(*(_DWORD *)(this + 69520) + 1780) = *(float *)(672 * *(_DWORD *)(this + 69504) + this + 28)
                                                   - (a2
                                                    - v9)
                                                   - 40.0;
    if ( v10 < 50.0 )
      *(_DWORD *)(*(_DWORD *)(this + 69520) + 1784) = 1112014848;
    if ( v8 > 450.0 )
      *(float *)(*(_DWORD *)(this + 69520) + 1784) = 450.0 - (v8 - v10);
  }
  while ( a2 > 631.0 || v10 < 49.0 || v8 > 451.0 );
  *(float *)(*(_DWORD *)(this + 69516) + 84) = a2 - v9;
  *(float *)(*(_DWORD *)(this + 69516) + 88) = v8 - v10;
  *(float *)(*(_DWORD *)(this + 69516) + 76) = v9;
  *(float *)(*(_DWORD *)(this + 69516) + 80) = v10;
  *(float *)(*(_DWORD *)(this + 69532) + 608) = *(float *)(*(_DWORD *)(this + 69516) + 84) * 0.5
                                              + *(float *)(*(_DWORD *)(this + 69516) + 76)
                                              - 320.0;
  result = *(_DWORD *)(this + 69516);
  *(float *)(*(_DWORD *)(this + 69536) + 608) = *(float *)(result + 84) * 0.5 + *(float *)(result + 76) - 320.0;
  return result;
}

