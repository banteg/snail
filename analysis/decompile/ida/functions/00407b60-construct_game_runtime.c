/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: construct_game_runtime @ 0x407b60 */
/* selector: construct_game_runtime */

// Allocates the `cRGame` root object, seeds its embedded managers and callback tables, initializes the runtime pools, and publishes the live global game pointer at `data_4df904`.
int construct_game_runtime()
{
  char *v0; // eax
  char *v1; // esi
  _DWORD *v2; // edi
  int v3; // ebx
  _DWORD *v4; // edi
  int v5; // ebx
  int v6; // edi
  int v7; // ebx
  _DWORD *v8; // edi
  int v9; // ebx

  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  sub_449C00();
  v0 = (char *)operator new(0x12E6FF4u);
  v1 = v0;
  if ( v0 )
  {
    Iostream_init::Iostream_init((#93 *)(v0 + 20));
    v2 = v1 + 68;
    v3 = 2;
    do
    {
      initialize_bod_base(v2);
      *v2 = off_4972F0;
      v2 += 28;
      --v3;
    }
    while ( v3 );
    v4 = v1 + 292;
    v5 = 2;
    do
    {
      sub_408000(v4);
      v4 += 126;
      --v5;
    }
    while ( v5 );
    initialize_bod_base((_DWORD *)v1 + 348);
    v6 = (int)(v1 + 1460);
    v7 = 5;
    do
    {
      sub_44E920(v6);
      v6 += 40;
      --v7;
    }
    while ( v7 );
    initialize_renderable_bod((_DWORD *)v1 + 415);
    sub_408040((_DWORD *)v1 + 447);
    *((_DWORD *)v1 + 415) = off_4972EC;
    initialize_renderable_bod((_DWORD *)v1 + 498);
    sub_408040((_DWORD *)v1 + 530);
    *((_DWORD *)v1 + 498) = off_4972EC;
    initialize_renderable_bod((_DWORD *)v1 + 581);
    sub_408040((_DWORD *)v1 + 613);
    *((_DWORD *)v1 + 581) = off_4972EC;
    initialize_renderable_bod((_DWORD *)v1 + 664);
    Iostream_init::Iostream_init((#93 *)(v1 + 2784));
    *((_DWORD *)v1 + 664) = &off_4972B0;
    initialize_bod_base((_DWORD *)v1 + 723);
    initialize_array_with_constructor((int)(v1 + 4560), 1828, 150, (int (__thiscall *)(int))sub_408410);
    *((_DWORD *)v1 + 723) = off_4972E8;
    v8 = v1 + 278784;
    v9 = 352;
    do
    {
      initialize_bod_base(v8);
      v8 += 14;
      --v9;
    }
    while ( v9 );
    initialize_array_with_constructor((int)(v1 + 298504), 188, 128, (int (__thiscall *)(int))sub_408470);
    initialize_bod_base((_DWORD *)v1 + 80644);
    Iostream_init::Iostream_init((#93 *)(v1 + 324236));
    Iostream_init::Iostream_init((#93 *)(v1 + 324268));
    *((_DWORD *)v1 + 80644) = off_4972E4;
    initialize_bod_base((_DWORD *)v1 + 81103);
    *((_DWORD *)v1 + 81103) = off_4972E0;
    initialize_bod_base((_DWORD *)v1 + 81138);
    initialize_array_with_constructor((int)(v1 + 324632), 144, 1024, (int (__thiscall *)(int))sub_408490);
    initialize_array_with_constructor((int)(v1 + 472088), 144, 32, (int (__thiscall *)(int))sub_408490);
    initialize_runtime_pools_and_path_template_bank((_DWORD *)v1 + 119174);
    initialize_bod_base((_DWORD *)v1 + 4955094);
    *((_DWORD *)v1 + 4955094) = off_4972DC;
    *(_DWORD *)v1 = &off_4972D8;
  }
  else
  {
    v1 = nullptr;
  }
  MEMORY[0x4DF904] = v1;
  sub_449C00();
  sub_449C00();
  return sub_449C00();
}

