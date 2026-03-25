/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy @ 0x43a9c0 */
/* selector: initialize_subgoldy */

// Initializes the live Goldy actor for a new run: resets movement and follow state, seeds the animation managers and cutscene block, initializes the jetpack gauge, cameraman, and click-start prompt, and wires the actor back to the active Game. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::Init(int)`.
int __thiscall sub_43A9C0(int this, int a2)
{
  int v3; // eax
  unsigned int v4; // ecx
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // ecx
  int v8; // ecx
  char *v9; // eax
  _DWORD *v10; // edi
  int v11; // ebp
  int result; // eax
  int v13; // [esp-4h] [ebp-14h]

  *(_DWORD *)(this + 896) = a2;
  *(_DWORD *)(this + 1032) = (char *)MEMORY[0x4DF904] + 476696;
  *(_DWORD *)(this + 880) = 0;
  *(_DWORD *)(this + 488) = 0;
  *(_BYTE *)(this + 728) = 0;
  *(_DWORD *)(this + 340) = this;
  *(_DWORD *)(this + 336) = 0;
  *(_BYTE *)(this + 332) = 0;
  *(_DWORD *)(this + 140) = 0;
  *(_DWORD *)(this + 1092) = 0;
  *(_DWORD *)(this + 824) = 0;
  *(_DWORD *)(this + 828) = -1;
  *(_BYTE *)(this + 484) = 0;
  *(_BYTE *)(this + 17080) = 0;
  *(_DWORD *)(*(_DWORD *)(this + 1032) + 19343340) = 0;
  *(_DWORD *)(this + 15464) = 0;
  *(_DWORD *)(this + 12500) = 0;
  *(_DWORD *)(this + 13488) = 0;
  *(_DWORD *)(this + 14476) = 0;
  *(_DWORD *)(this + 732) = 0;
  *(_DWORD *)(this + 736) = 0;
  sub_41AA30((_DWORD *)(*(_DWORD *)(this + 10664) + 128));
  *(_DWORD *)(this + 10624) = -1047003136;
  *(_DWORD *)(this + 460) = 0;
  *(_DWORD *)(this + 17072) = 0;
  *(_DWORD *)(this + 17076) = 1015580809;
  *(_DWORD *)(this + 17244) = 0;
  *(_DWORD *)(this + 17248) = 1015580809;
  initialize_score_stats((_DWORD *)(this + 17220));
  initialize_invincible_shell((_DWORD *)(this + 16920));
  *(_DWORD *)(this + 820) = 1029934648;
  *(_DWORD *)(this + 816) = 1029934648;
  *(_DWORD *)(this + 1076) = 0;
  *(_DWORD *)(this + 1080) = 1015580809;
  if ( (*(_DWORD *)(*(_DWORD *)(this + 10664) + 16) & 0x200000) != 0 )
  {
    v3 = *(_DWORD *)(this + 10632);
    BYTE1(v3) |= 8u;
    *(_DWORD *)(this + 10632) = v3;
    *(_DWORD *)(this + 10748) = this + 10888;
    initialize_anim_manager((_DWORD *)(this + 10888));
    *(_DWORD *)(this + 10888) = 1;
    *(_DWORD *)(this + 10952) = this + 10628;
    *(_DWORD *)(this + 10956) = this + 10960;
    *(_DWORD *)(this + 10948) = 0;
  }
  else
  {
    initialize_anim_manager((_DWORD *)(this + 10888));
    *(_DWORD *)(this + 10888) = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)(this + 15240) + 16) & 0x200000) != 0 )
  {
    v4 = *(_DWORD *)(this + 15208) & 0xFFFFFFDF;
    BYTE1(v4) |= 8u;
    *(_DWORD *)(this + 15208) = v4;
    *(_DWORD *)(this + 15464) = 0;
    *(_DWORD *)(this + 15324) = this + 15468;
    initialize_anim_manager((_DWORD *)(this + 15468));
    *(_DWORD *)(this + 15468) = 1;
    *(_DWORD *)(this + 15532) = this + 15204;
    *(_DWORD *)(this + 15536) = this + 15540;
    *(_DWORD *)(this + 15528) = 0;
  }
  else
  {
    initialize_anim_manager((_DWORD *)(this + 15468));
    *(_DWORD *)(this + 15468) = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)(this + 12276) + 16) & 0x200000) != 0 )
  {
    v5 = *(_DWORD *)(this + 12244) & 0xFFFFFFDF;
    BYTE1(v5) |= 8u;
    *(_DWORD *)(this + 12244) = v5;
    *(_DWORD *)(this + 12500) = 0;
    *(_DWORD *)(this + 12360) = this + 12504;
    initialize_anim_manager((_DWORD *)(this + 12504));
    *(_DWORD *)(this + 12504) = 1;
    *(_DWORD *)(this + 12568) = this + 12240;
    *(_DWORD *)(this + 12572) = this + 12576;
    *(_DWORD *)(this + 12564) = 0;
  }
  else
  {
    initialize_anim_manager((_DWORD *)(this + 12504));
    *(_DWORD *)(this + 12504) = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)(this + 13264) + 16) & 0x200000) != 0 )
  {
    v6 = *(_DWORD *)(this + 13232);
    LOBYTE(v6) = v6 & 0xDF;
    BYTE1(v6) |= 8u;
    *(_DWORD *)(this + 13232) = v6;
    *(_DWORD *)(this + 13488) = 0;
    *(_DWORD *)(this + 13348) = this + 13492;
    initialize_anim_manager((_DWORD *)(this + 13492));
    *(_DWORD *)(this + 13492) = 1;
    *(_DWORD *)(this + 13556) = this + 13228;
    *(_DWORD *)(this + 13560) = this + 13564;
    *(_DWORD *)(this + 13552) = 0;
  }
  else
  {
    initialize_anim_manager((_DWORD *)(this + 13492));
    *(_DWORD *)(this + 13492) = 0;
  }
  if ( (*(_DWORD *)(*(_DWORD *)(this + 14252) + 16) & 0x200000) != 0 )
  {
    v7 = *(_DWORD *)(this + 14220) & 0xFFFFFFDF;
    BYTE1(v7) |= 8u;
    *(_DWORD *)(this + 14220) = v7;
    *(_DWORD *)(this + 14476) = 0;
    *(_DWORD *)(this + 14336) = this + 14480;
    initialize_anim_manager((_DWORD *)(this + 14480));
    *(_DWORD *)(this + 14480) = 1;
    *(_DWORD *)(this + 14544) = this + 14216;
    *(_DWORD *)(this + 14548) = this + 14552;
    *(_DWORD *)(this + 14540) = 0;
  }
  else
  {
    initialize_anim_manager((_DWORD *)(this + 14480));
    *(_DWORD *)(this + 14480) = 0;
  }
  initialize_snail_skin((_DWORD *)(this + 17084));
  initialize_cutscene_ai((_DWORD *)(this + 17116));
  if ( !*(_BYTE *)(*(_DWORD *)(this + 1032) + 16721360) )
    *(_DWORD *)(this + 17128) = 1;
  *(_DWORD *)(this + 10884) = this;
  set_matrix_identity((_DWORD *)(this + 10684));
  set_matrix_identity((_DWORD *)(this + 10820));
  set_matrix_identity((_DWORD *)(this + 10756));
  *(_DWORD *)(this + 17208) = 0;
  initialize_click_start(this + 160, this);
  initialize_cameraman(this + 512);
  initialize_subgoldy_ghost((_DWORD *)this, *(_DWORD *)(this + 896));
  *(_DWORD *)(this + 472) = 1028578914;
  *(_DWORD *)(this + 480) = 1028578914;
  *(_DWORD *)(this + 104) = 0;
  *(_DWORD *)(this + 108) = 0;
  *(_DWORD *)(this + 10596) = 0;
  *(_DWORD *)(this + 112) = 1082130432;
  v8 = *(_DWORD *)(this + 112);
  *(_DWORD *)(this + 892) = 0;
  *(_DWORD *)(this + 10600) = 0;
  *(_DWORD *)(this + 808) = 0;
  *(_DWORD *)(this + 812) = 1015580809;
  *(_DWORD *)(this + 468) = 0;
  *(_DWORD *)(this + 476) = 0;
  *(_DWORD *)(this + 16192) = 0;
  *(_DWORD *)(this + 16196) = 1002197604;
  *(_DWORD *)(this + 16200) = 0;
  *(_DWORD *)(this + 16204) = 1004405091;
  *(_BYTE *)(this + 132) = 0;
  *(_DWORD *)(this + 10604) = v8;
  *(_DWORD *)(this + 1048) = 0;
  *(_DWORD *)(this + 1044) = 0;
  *(_DWORD *)(this + 1040) = 0;
  if ( *(_DWORD *)(this + 896) != 1 )
  {
    if ( MEMORY[0x4DF904] != (void *)-180 )
    {
      v9 = (char *)MEMORY[0x4DF904] + 236;
      goto LABEL_24;
    }
LABEL_23:
    v9 = nullptr;
    goto LABEL_24;
  }
  if ( MEMORY[0x4DF904] == (void *)-68 )
    goto LABEL_23;
  v9 = (char *)MEMORY[0x4DF904] + 124;
LABEL_24:
  *(_DWORD *)(this + 1084) = v9;
  *(_DWORD *)(this + 10032) = 0;
  *(_BYTE *)(this + 1088) = 0;
  *(_DWORD *)(this + 10040) = 0;
  initialize_damage_gauge((_DWORD *)(this + 964));
  noop_runtime_ai(this + 1008);
  *(_BYTE *)(this + 900) = 0;
  v10 = (_DWORD *)(this + 1556);
  v11 = 12;
  do
  {
    v10[32] = 0;
    set_matrix_identity(v10);
    v10[43] = *(_DWORD *)(this + 1032);
    v10 += 186;
    --v11;
  }
  while ( v11 );
  v13 = *(_DWORD *)(this + 896);
  *(_DWORD *)(this + 4) |= 0x20u;
  *(_DWORD *)(this + 10052) = 0;
  *(_DWORD *)(this + 10056) = 1045779798;
  *(_DWORD *)(this + 10060) = 0;
  result = initialize_jetpack_gauge((_DWORD *)(this + 10064), v13);
  *(_DWORD *)(this + 848) = 0;
  *(_DWORD *)(this + 852) = 0;
  *(_DWORD *)(this + 856) = 0;
  *(_DWORD *)(this + 860) = 0;
  *(_DWORD *)(this + 864) = 0;
  *(_DWORD *)(this + 868) = 0;
  *(_DWORD *)(this + 872) = 0;
  *(_DWORD *)(this + 876) = 0;
  *(_DWORD *)(this + 884) = 0;
  *(_DWORD *)(this + 888) = 0;
  *(_BYTE *)(this + 1053) = 0;
  *(_BYTE *)(this + 1052) = 0;
  *(_DWORD *)(this + 1028) = 0;
  *(_BYTE *)(*(_DWORD *)(this + 1032) + 1) = 1;
  return result;
}

