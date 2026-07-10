/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_assets_and_world @ 0x40acf0 */
/* selector: initialize_game_assets_and_world */

// Bootstraps the shared app world, front-end managers, score tables, and star field, and clears the app-side persistent replay-launch bits before the first front-end or gameplay owner runs.
char __thiscall sub_40ACF0(int this)
{
  int v2; // eax
  int *v3; // edx
  char *v4; // ecx
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char *v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // ecx
  char *v14; // eax
  int v15; // edx
  int v16; // ecx
  int v17; // ecx
  int v18; // edi
  _DWORD *v19; // eax
  _DWORD *v20; // eax
  _DWORD *v21; // eax
  double v22; // st7
  _DWORD *v23; // eax
  _DWORD *v24; // eax
  _DWORD *v25; // eax
  _DWORD *v26; // eax
  _DWORD *v27; // eax
  _DWORD *v28; // eax
  _DWORD *v29; // eax
  _DWORD *v30; // eax
  _DWORD *v31; // eax
  _DWORD *v32; // eax
  _DWORD *v33; // eax
  _DWORD *v34; // eax
  _DWORD *v35; // eax
  _DWORD *v36; // eax
  _DWORD *v37; // eax
  _DWORD *v38; // eax
  _DWORD *v39; // eax
  _DWORD *v40; // eax
  _DWORD *v41; // eax
  _DWORD *v42; // eax
  _DWORD *v43; // eax
  _DWORD *v44; // eax
  _DWORD *v45; // eax
  _DWORD *v46; // eax
  _DWORD *v47; // eax
  _DWORD *v48; // eax
  int *v49; // eax
  int v50; // ecx
  _DWORD *v51; // eax
  _DWORD *v52; // edi
  int *v53; // eax
  int v54; // ecx
  int v55; // ecx
  bool v56; // zf
  _DWORD *v57; // eax
  _DWORD *v58; // edi
  int i; // edi
  _DWORD *v60; // eax
  int v61; // edi
  int v62; // ecx
  int v63; // eax
  int v64; // ecx
  int v65; // eax
  int v66; // eax
  int *v67; // ecx
  int v68; // edx
  int v69; // eax
  int v70; // eax
  int *v71; // edx
  int v72; // ecx
  int v73; // eax
  int v74; // eax
  int *v75; // edx
  int v76; // ecx
  int v77; // eax
  int v78; // eax
  int *v79; // edx
  int v80; // ecx
  int v81; // eax
  int v82; // eax
  int *v83; // edx
  int v84; // ecx
  int v85; // eax
  int v86; // eax
  int *v87; // edx
  int v88; // ecx
  int v89; // eax
  int v90; // eax
  int *v91; // edx
  int v92; // ecx
  int v93; // eax
  int v94; // eax
  int *v95; // edx
  int v96; // ecx
  int v97; // eax
  _DWORD *v98; // eax
  _DWORD *v99; // eax
  _DWORD *v100; // eax
  _DWORD *v101; // eax
  _DWORD *v102; // eax
  _DWORD *v103; // eax
  _DWORD *v104; // eax
  _DWORD *v105; // eax
  _DWORD *v106; // eax
  _DWORD *v107; // eax
  _DWORD *v108; // eax
  _DWORD *v109; // eax
  _DWORD *v110; // eax
  _DWORD *v111; // eax
  _DWORD *v112; // eax
  _DWORD *v113; // eax
  _DWORD *v114; // eax
  _DWORD *v115; // eax
  _DWORD *v116; // eax
  _DWORD *v117; // eax
  _DWORD *v118; // eax
  _DWORD *v119; // eax
  _DWORD *v120; // eax
  _DWORD *v121; // eax
  _DWORD *v122; // eax
  _DWORD *v123; // eax
  _DWORD *v124; // eax
  _DWORD *v125; // eax
  _DWORD *v126; // eax
  _DWORD *v127; // eax
  _DWORD *v128; // eax
  _DWORD *v129; // eax
  _DWORD *v130; // eax
  _DWORD *v131; // eax
  _DWORD *v132; // eax
  _DWORD *v133; // eax
  _DWORD *v134; // eax
  _DWORD *v135; // eax
  _DWORD *v136; // eax
  _DWORD *v137; // eax
  _DWORD *v138; // eax
  _DWORD *v139; // eax
  _DWORD *v140; // eax
  _DWORD *v141; // eax
  _DWORD *v142; // eax
  _DWORD *v143; // eax
  _DWORD *v144; // eax
  _DWORD *v145; // eax
  _DWORD *v146; // eax
  _DWORD *v147; // eax
  _DWORD *v148; // eax
  _DWORD *v149; // eax
  _DWORD *v150; // eax
  _DWORD *v151; // eax
  _DWORD *v152; // eax
  _DWORD *v153; // eax
  _DWORD *v154; // eax
  _DWORD *v155; // eax
  _DWORD *v156; // eax
  _DWORD *v157; // eax
  _DWORD *v158; // eax
  _DWORD *v159; // eax
  _DWORD *v160; // eax
  _DWORD *v161; // eax
  _DWORD *v162; // eax
  _DWORD *v163; // eax
  _DWORD *v164; // eax
  _DWORD *v165; // eax
  _DWORD *v166; // eax
  _DWORD *v167; // eax
  _DWORD *v168; // eax
  _DWORD *v169; // eax
  _DWORD *v170; // eax
  _DWORD *v171; // eax
  _DWORD *v172; // eax
  _DWORD *v173; // eax
  _DWORD *v174; // eax
  _DWORD *v175; // eax
  _DWORD *v176; // eax
  _DWORD *v177; // eax
  _DWORD *v178; // eax
  _DWORD *v179; // eax
  _DWORD *v180; // eax
  _DWORD *v181; // eax
  _DWORD *v182; // eax
  _DWORD *v183; // eax
  _DWORD *v184; // eax
  _DWORD *v185; // eax
  _DWORD *v186; // eax
  _DWORD *v187; // eax
  _DWORD *v188; // eax
  _DWORD *v189; // eax
  _DWORD *v190; // eax
  _DWORD *v191; // eax
  _DWORD *v192; // eax
  _DWORD *v193; // eax
  _DWORD *v194; // eax
  _DWORD *v195; // eax
  _DWORD *v196; // eax
  _DWORD *v197; // eax
  _DWORD *v198; // eax
  _DWORD *v199; // eax
  _DWORD *v200; // eax
  _DWORD *v201; // eax
  int v202; // ecx
  int v203; // edx
  int v204; // eax
  _DWORD *v205; // eax
  _DWORD *v206; // eax
  int v207; // edx
  int v208; // eax
  _DWORD *v209; // eax
  _DWORD *v210; // eax
  int v211; // eax
  int v212; // ecx
  _DWORD *v213; // eax
  _DWORD *v214; // eax
  _DWORD *v215; // eax
  _DWORD *v216; // eax
  _DWORD *v217; // eax
  _DWORD *v218; // eax
  _DWORD *v219; // eax
  _DWORD *v220; // eax
  _DWORD *v221; // eax
  _DWORD *v222; // eax
  _DWORD *v223; // eax
  _DWORD *v224; // eax
  _DWORD *v225; // eax
  _DWORD *v226; // eax
  _DWORD *v227; // eax
  _DWORD *v228; // eax
  _DWORD *v229; // eax
  _DWORD *v230; // eax
  _DWORD *v231; // eax
  char *v232; // eax
  char *v233; // eax
  char v234; // cl
  char *v235; // edx
  char *v236; // eax
  int v237; // edx
  _BYTE *v238; // eax
  _DWORD *v239; // eax
  _DWORD *v240; // eax
  _DWORD *v241; // eax
  _DWORD *v242; // eax
  _DWORD *v243; // eax
  _DWORD *v244; // eax
  _DWORD *v245; // eax
  _DWORD *v246; // eax
  _DWORD *v247; // eax
  _DWORD *v248; // eax
  _DWORD *v249; // eax
  int v250; // ecx
  _DWORD *v251; // eax
  _DWORD *v252; // eax
  _DWORD *v253; // eax
  int v254; // edx
  _DWORD *v255; // eax
  _DWORD *v256; // eax
  _DWORD *v257; // eax
  _DWORD *v258; // eax
  _DWORD *v259; // eax
  _DWORD *v260; // eax
  int v261; // ecx
  _DWORD *v262; // eax
  _DWORD *v263; // eax
  _DWORD *v264; // eax
  _DWORD *v265; // eax
  _DWORD *v266; // eax
  _DWORD *v267; // eax
  int v268; // edx
  _DWORD *v269; // eax
  _DWORD *v270; // eax
  _DWORD *v271; // eax
  _DWORD *v272; // eax
  _DWORD *v273; // eax
  _DWORD *v274; // eax
  int v275; // ecx
  _DWORD *v276; // eax
  _DWORD *v277; // eax
  char *v278; // esi
  _DWORD *v279; // eax
  int *v280; // eax
  int v281; // ecx
  _DWORD *v282; // eax
  _DWORD *v283; // eax
  int *v284; // eax
  int v285; // ecx
  _DWORD *v286; // eax
  _DWORD *v287; // eax
  _DWORD *v288; // eax
  _DWORD *v289; // eax
  _DWORD *v290; // eax
  _DWORD *v291; // eax
  _DWORD *v292; // eax
  _DWORD *v293; // eax
  _DWORD *v294; // eax
  int **v295; // eax
  int **v296; // esi
  int k; // edi
  _DWORD *v298; // eax
  int *v299; // eax
  int *v300; // eax
  int v301; // ecx
  int *v302; // esi
  int v303; // edi
  _DWORD *v304; // eax
  int v305; // ecx
  float v307; // [esp+10h] [ebp-12Ch]
  _DWORD **v308; // [esp+10h] [ebp-12Ch]
  _DWORD **v309; // [esp+10h] [ebp-12Ch]
  _DWORD **v310; // [esp+10h] [ebp-12Ch]
  _DWORD **v311; // [esp+10h] [ebp-12Ch]
  _DWORD **v312; // [esp+10h] [ebp-12Ch]
  int v313; // [esp+10h] [ebp-12Ch]
  int m; // [esp+10h] [ebp-12Ch]
  int *v315; // [esp+14h] [ebp-128h]
  int *v316; // [esp+14h] [ebp-128h]
  int v317; // [esp+14h] [ebp-128h]
  int v318; // [esp+14h] [ebp-128h]
  _DWORD *v319; // [esp+14h] [ebp-128h]
  int v320; // [esp+14h] [ebp-128h]
  int v321; // [esp+14h] [ebp-128h]
  int v322; // [esp+14h] [ebp-128h]
  int v323; // [esp+14h] [ebp-128h]
  int v324; // [esp+14h] [ebp-128h]
  int v325; // [esp+14h] [ebp-128h]
  int v326; // [esp+14h] [ebp-128h]
  int v327; // [esp+14h] [ebp-128h]
  _DWORD v328[4]; // [esp+18h] [ebp-124h] BYREF
  int j; // [esp+28h] [ebp-114h]
  float v330[12]; // [esp+2Ch] [ebp-110h] BYREF
  int v331; // [esp+5Ch] [ebp-E0h]
  char v332[16]; // [esp+6Ch] [ebp-D0h] BYREF
  char ArgList[128]; // [esp+7Ch] [ebp-C0h] BYREF
  int v334[16]; // [esp+FCh] [ebp-40h] BYREF

  Iostream_init::Iostream_init((#93 *)v332);
  store_color4f((_DWORD *)(this + 20), 1065353216, 1065353216, 1065353216, 1065353216);
  *(_DWORD *)(this + 16) = 1065353216;
  *(_DWORD *)(this + 8) = 1106247680;
  *(_DWORD *)(this + 12) = 1112014848;
  *(_BYTE *)(this + 4) = 1;
  *(_DWORD *)(this + 64) = 2;
  Concurrency::details::StructuredWorkStealingQueue<Concurrency::details::_UnrealizedChore,Concurrency::details::_CriticalNonReentrantLock>::Reinitialize(this + 36);
  *(_BYTE *)(this + 1384) = 0;
  *(_BYTE *)(this + 476705) = 0;
  initialize_cheat(&byte_4B2F40);
  *(_BYTE *)(this + 324320) = 0;
  initialize_blink_random((float *)(this + 476696));
  set_subgame_rate((_DWORD *)(this + 476696), 1066192077);
  *(_DWORD *)(this + 1388) = 2;
  *(_DWORD *)(this + 60) = 1;
  initialize_texture_list(&texture_list, 500);
  initialize_object_list(unk_4B7648, 3000);
  *(_DWORD *)(this + 1300) = 0;
  *(_DWORD *)(this + 1304) = 0;
  *(_DWORD *)(this + 1308) = 0;
  *(_DWORD *)(this + 1404) = 0;
  *(_DWORD *)(this + 1456) = this + 1392;
  *(_DWORD *)(this + 1452) = 0;
  *(_DWORD *)(this + 2888) = 0;
  memset(&MEMORY[0x4F7050], 0, 0x400u);
  *(_DWORD *)(this + 1464) = 0;
  *(_DWORD *)(this + 1468) = 16777219;
  *(_DWORD *)(this + 1492) = this + 1788;
  *(_DWORD *)(this + 1472) = 0;
  *(_DWORD *)(this + 1476) = 0;
  *(_DWORD *)(this + 1480) = 1065353216;
  *(_DWORD *)(this + 1484) = 1065353216;
  *(_BYTE *)(this + 1576) = 0;
  v2 = this + 1660;
  v3 = (int *)(this + 1664);
  if ( (*(_DWORD *)(this + 1664) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v4 = (char *)MEMORY[0x4DF904] + 1452;
    v5 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v5 )
    {
      *(_DWORD *)(v5 + 8) = v2;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v4 + 8) + 12) = *(_DWORD *)v4;
      v6 = *(_DWORD *)(*(_DWORD *)v4 + 8);
      *(_DWORD *)v4 = v6;
      *(_DWORD *)(v6 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v4 = v2;
      *(_DWORD *)(this + 1668) = 0;
      *(_DWORD *)(*(_DWORD *)v4 + 12) = 0;
    }
    v7 = *v3;
    BYTE1(v7) = BYTE1(*v3) | 2;
    *v3 = v7;
  }
  initialize_overlay(this + 1660);
  memset(&unk_74EB18, 0, 0x15Cu);
  initialize_directx_loader((_DWORD *)(this + 298496));
  reset_landscape_manager((_DWORD *)(this + 17220120));
  load_segment_definitions((int *)(this + 17259236));
  load_landscape_script_by_name((char *)(this + 17220120), aStarmapTxt);
  load_landscape_script_by_name((char *)(this + 17220120), aSplashTxt);
  load_landscape_script_by_name((char *)(this + 17220120), aHelpTxt);
  *(_DWORD *)(this + 476764) = unk_4DF9BC;
  open_thanks_screen((_DWORD *)(this + 19744248));
  open_thanks_screen((_DWORD *)(this + 19744292));
  load_galaxy_layout((_DWORD *)(this + 19744312));
  initialize_cameraman((int)&loc_42FF7C + this);
  open_logo((int **)(this + 324608));
  initialize_sound_bank(&off_4A2140);
  initialize_voice_manager(unk_751498);
  apply_audio_config_volumes();
  load_level_definitions();
  load_landscape_script_by_name((char *)MEMORY[0x4DF904] + 17220120, aMenubgTxt);
  load_builtin_segment_definitions((int *)(this + 2246660), (int)&off_4A63D0);
  *(_DWORD *)(this + 1504) = 1;
  *(_DWORD *)(this + 1508) = 33554433;
  sub_44E900((_DWORD *)(this + 1500), this + 452);
  *(_DWORD *)(this + 648) = 0x2000000;
  *(_DWORD *)(this + 1624) = 1;
  *(_DWORD *)(this + 1628) = 268435459;
  sub_44E900((_DWORD *)(this + 1620), this + 956);
  *(_DWORD *)(this + 1152) = 0x10000000;
  *(_DWORD *)(this + 1584) = 3;
  *(_DWORD *)(this + 1588) = 134217731;
  *(_DWORD *)(this + 1612) = this + 2452;
  *(_DWORD *)(this + 1592) = 0;
  *(_DWORD *)(this + 1596) = 0;
  *(_DWORD *)(this + 1600) = 1065353216;
  *(_DWORD *)(this + 1604) = 1065353216;
  v8 = this + 2324;
  v315 = (int *)(this + 2328);
  if ( (*(_DWORD *)(this + 2328) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v9 = (char *)MEMORY[0x4DF904] + 1452;
    v10 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v10 )
    {
      *(_DWORD *)(v10 + 8) = v8;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v9 + 8) + 12) = *(_DWORD *)v9;
      v11 = *(_DWORD *)(*(_DWORD *)v9 + 8);
      *(_DWORD *)v9 = v11;
      *(_DWORD *)(v11 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v9 = v8;
      *(_DWORD *)(this + 2332) = 0;
      *(_DWORD *)(*(_DWORD *)v9 + 12) = 0;
    }
    v12 = *v315;
    BYTE1(v12) = BYTE1(*v315) | 2;
    *v315 = v12;
  }
  initialize_overlay(this + 2324);
  *(_DWORD *)(this + 1544) = 2;
  *(_DWORD *)(this + 1548) = 67108867;
  *(_DWORD *)(this + 1572) = this + 2120;
  *(_DWORD *)(this + 1552) = 0;
  *(_DWORD *)(this + 1556) = 0;
  v13 = this + 1992;
  *(_DWORD *)(this + 1560) = 1065353216;
  *(_DWORD *)(this + 1564) = 1065353216;
  v316 = (int *)(this + 1996);
  if ( (*(_DWORD *)(this + 1996) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v14 = (char *)MEMORY[0x4DF904] + 1452;
    v15 = *((_DWORD *)MEMORY[0x4DF904] + 363);
    if ( v15 )
    {
      *(_DWORD *)(v15 + 8) = v13;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v14 + 8) + 12) = *(_DWORD *)v14;
      v16 = *(_DWORD *)(*(_DWORD *)v14 + 8);
      *(_DWORD *)v14 = v16;
      *(_DWORD *)(v16 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v14 = v13;
      *(_DWORD *)(this + 2000) = 0;
      *(_DWORD *)(*(_DWORD *)v14 + 12) = 0;
    }
    v17 = *v316;
    BYTE1(v17) = BYTE1(*v316) | 2;
    *v316 = v17;
  }
  initialize_overlay(this + 1992);
  sub_432D20(aObjectsFontFon, 2, 1061158912, 1.0);
  initialize_font3d_objects(0.0);
  initialize_font_wave_state();
  initialize_sprite_manager(g_sprite_manager);
  register_sprite_texture(aSpritesDebugTg, 1, 0);
  register_sprite_texture(aSpritesOverlay, 2, 0);
  register_sprite_texture(aSpritesBorderT, 5, 1024);
  register_sprite_texture(aSpritesMouseTg, 22, 1024);
  register_sprite_texture(aSpritesWarning, 94, 1024);
  register_sprite_texture(aSpritesPlayTga, 27, 1024);
  register_sprite_texture(aSpritesStartai, 32, 1024);
  register_sprite_texture(aSpritesJetTga, 33, 1024);
  register_sprite_texture(aSpritesHealthT, 57, 1024);
  register_sprite_texture(aSpritesDamageg, 89, 1024);
  register_sprite_texture(aSpritesDamageg_0, 90, 1024);
  register_sprite_texture(aSpritesDamageg_1, 91, 1024);
  register_sprite_texture(aSpritesSparkTg, 92, 1024);
  register_sprite_texture(aSpritesBlackTg, 93, 1024);
  register_sprite_texture(aSpritesBorderg, 99, 1024);
  register_sprite_texture(aSpritesSlug000, 118, 1024);
  register_sprite_texture(aSpritesSlug001, 119, 1024);
  register_sprite_texture(aSpritesSlugmas, 120, 1024);
  register_sprite_texture(aSpritesParcel0, 121, 1024);
  register_sprite_texture(aSpritesParceli, 122, 1024);
  register_sprite_texture(aSpritesGarbage, 114, 1024);
  register_sprite_texture(aSpritesGarbage_0, 115, 1024);
  register_sprite_texture(aSpritesGarbage_1, 116, 1024);
  register_sprite_texture(aSpritesGarbage_2, 117, 1024);
  register_sprite_texture(aSpritesLifeTga, 123, 1024);
  register_sprite_texture(aSpritesJetpack, 124, 1024);
  register_sprite_texture(aSpritesSmokeTg, 128, 1024);
  register_sprite_texture(aSpritesSluggoo, 129, 1024);
  register_sprite_texture(aSpritesSliderb, 36, 1024);
  register_sprite_texture(aSpritesSliderb_0, 37, 1024);
  register_sprite_texture(aSpritesLessTga, 38, 1024);
  register_sprite_texture(aSpritesLesshov, 40, 1024);
  register_sprite_texture(aSpritesLessmas, 41, 1056);
  register_sprite_texture(aSpritesMoreTga, 42, 1024);
  register_sprite_texture(aSpritesMorehov, 44, 1024);
  register_sprite_texture(aSpritesMoremas, 45, 1056);
  register_sprite_texture(aSpritesParticl, 130, 1024);
  register_sprite_texture(aSpritesParticl_0, 131, 1024);
  register_sprite_texture(aSpritesParticl_1, 132, 1024);
  register_sprite_texture(aSpritesParticl_2, 133, 1024);
  register_sprite_texture(aSpritesParticl_3, 134, 1024);
  register_sprite_texture(aSpritesParticl_4, 135, 1024);
  register_sprite_texture(aSpritesParticl_5, 136, 1024);
  register_sprite_texture(aSpritesCollisi, 137, 1024);
  register_sprite_texture(aGalaxySpacemap, 138, 1024);
  register_sprite_texture(aGalaxyGalaxy00, 139, 1024);
  register_sprite_texture(aGalaxyGalaxy00_0, 140, 1024);
  register_sprite_texture(aGalaxyGalaxy00_1, 141, 1024);
  register_sprite_texture(aGalaxyGalaxy00_2, 142, 1024);
  register_sprite_texture(aGalaxyGalaxy00_3, 143, 1024);
  register_sprite_texture(aGalaxyGalaxy00_4, 144, 1024);
  register_sprite_texture(aGalaxyGalaxy00_5, 145, 1024);
  register_sprite_texture(aGalaxyGalaxy00_6, 146, 1024);
  register_sprite_texture(aGalaxyGalaxy00_7, 147, 1024);
  register_sprite_texture(aGalaxyGalaxy00_8, 148, 1024);
  register_sprite_texture(aGalaxyGalaxyse, 149, 1024);
  register_sprite_texture(aGalaxyLevelsel, 150, 1024);
  register_sprite_texture(aGalaxyLevelsta, 151, 1024);
  register_sprite_texture(aGalaxyBordersp, 152, 1024);
  register_sprite_texture(aGalaxyLineTga, 153, 1024);
  register_sprite_texture(aGalaxyLinestar, 154, 1024);
  register_sprite_texture(aSpritesProgres, 155, 1024);
  register_sprite_texture(aSpritesProgres_0, 156, 1024);
  register_sprite_texture(aSpritesProgres_1, 157, 1024);
  register_sprite_texture(aSpritesJetpack_0, 158, 1024);
  register_sprite_texture(aSpritesGhostTg, 159, 1024);
  v307 = 0.0;
  do
  {
    v18 = this + 56 * (__int64)v307;
    v19 = add_object_to_list(unk_4B7648);
    set_bod_object((_DWORD *)(v18 + 280464), (int)v19);
    initialize_backdrop_slice_quad(*(int **)(v18 + 280500), aObjectsWorld00, v307);
    v20 = add_object_to_list(unk_4B7648);
    set_bod_object((_DWORD *)(v18 + 280912), (int)v20);
    initialize_backdrop_slice_quad(*(int **)(v18 + 280948), aObjectsWorld00_0, v307);
    v21 = add_object_to_list(unk_4B7648);
    set_bod_object((_DWORD *)(v18 + 281360), (int)v21);
    initialize_backdrop_slice_quad(*(int **)(v18 + 281396), texture_a, v307);
    v22 = v307 + 1.0;
    v307 = v22;
  }
  while ( v22 < 8.0 );
  set_matrix_identity(v330);
  v23 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280016), (int)v23);
  load_x_mesh(aPillar1X, *(int **)(this + 280052), 1);
  v331 = 0;
  apply_bod_position((_DWORD *)(this + 280016), v330);
  v24 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280072), (int)v24);
  load_x_mesh(aPillar2X, *(int **)(this + 280108), 1);
  v331 = 1056964608;
  apply_bod_position((_DWORD *)(this + 280072), v330);
  v25 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280128), (int)v25);
  load_x_mesh(aPillar3X, *(int **)(this + 280164), 1);
  v331 = 1065353216;
  apply_bod_position((_DWORD *)(this + 280128), v330);
  v26 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280184), (int)v26);
  load_x_mesh(aPillar4X, *(int **)(this + 280220), 1);
  v331 = 1069547520;
  apply_bod_position((_DWORD *)(this + 280184), v330);
  v27 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280240), (int)v27);
  load_x_mesh(aPillar5X, *(int **)(this + 280276), 1);
  v331 = 0x40000000;
  apply_bod_position((_DWORD *)(this + 280240), v330);
  v28 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280296), (int)v28);
  load_x_mesh(aPillar6X, *(int **)(this + 280332), 1);
  v331 = 1075838976;
  apply_bod_position((_DWORD *)(this + 280296), v330);
  v29 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280352), (int)v29);
  load_x_mesh(aPillar7X, *(int **)(this + 280388), 1);
  v331 = 1077936128;
  apply_bod_position((_DWORD *)(this + 280352), v330);
  v30 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 280408), (int)v30);
  load_x_mesh(aPillar8X, *(int **)(this + 280444), 1);
  v331 = 1080033280;
  apply_bod_position((_DWORD *)(this + 280408), v330);
  v31 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 281808), (int)v31);
  initialize_textured_backdrop_quad(*(int **)(this + 281844), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(-1, *(_DWORD *)(this + 281844));
  v32 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 281864), (int)v32);
  initialize_textured_backdrop_quad(*(int **)(this + 281900), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(0, *(_DWORD *)(this + 281900));
  v33 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 281920), (int)v33);
  initialize_textured_backdrop_quad(*(int **)(this + 281956), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(1, *(_DWORD *)(this + 281956));
  v34 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279064), (int)v34);
  initialize_backdrop_corner_quad(0, *(int **)(this + 279100), aObjectsWorld00);
  v35 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279120), (int)v35);
  initialize_backdrop_corner_quad(1, *(int **)(this + 279156), aObjectsWorld00);
  v36 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279232), (int)v36);
  initialize_backdrop_corner_quad(2, *(int **)(this + 279268), aObjectsWorld00);
  v37 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279176), (int)v37);
  initialize_backdrop_corner_quad(3, *(int **)(this + 279212), aObjectsWorld00);
  v38 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279288), (int)v38);
  initialize_backdrop_corner_quad(0, *(int **)(this + 279324), aObjectsWorld00_0);
  v39 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279344), (int)v39);
  initialize_backdrop_corner_quad(1, *(int **)(this + 279380), aObjectsWorld00_0);
  v40 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279456), (int)v40);
  initialize_backdrop_corner_quad(2, *(int **)(this + 279492), aObjectsWorld00_0);
  v41 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279400), (int)v41);
  initialize_backdrop_corner_quad(3, *(int **)(this + 279436), aObjectsWorld00_0);
  v42 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279512), (int)v42);
  initialize_backdrop_corner_quad(0, *(int **)(this + 279548), texture_a);
  v43 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279568), (int)v43);
  initialize_backdrop_corner_quad(1, *(int **)(this + 279604), texture_a);
  v44 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279680), (int)v44);
  initialize_backdrop_corner_quad(2, *(int **)(this + 279716), texture_a);
  v45 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279624), (int)v45);
  initialize_backdrop_corner_quad(3, *(int **)(this + 279660), texture_a);
  v46 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 279736), (int)v46);
  load_x_mesh(aTrampX, *(int **)(this + 279772), 1);
  *(_DWORD *)(*(_DWORD *)(this + 279772) + 20) = 6;
  v47 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(this + 279772) + 92) + 12);
  *v47 |= 0x400u;
  v48 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 278784), (int)v48);
  initialize_textured_backdrop_quad(*(int **)(this + 278820), aObjectsUnivers_0, 0.0);
  *(_DWORD *)(*(_DWORD *)(this + 278820) + 20) = 5;
  v49 = *(int **)(*(_DWORD *)(*(_DWORD *)(this + 278820) + 92) + 12);
  v50 = *v49;
  BYTE1(v50) = BYTE1(*v49) | 4;
  *v49 = v50;
  v51 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 281976), (int)v51);
  load_object_definition(aObjectsLazer, *(int **)(this + 282012));
  v52 = (_DWORD *)(this + 3977532);
  v317 = 20;
  do
  {
    set_bod_object(v52 - 9, *(_DWORD *)(this + 282012));
    v53 = *(int **)(*(_DWORD *)(*v52 + 92) + 12);
    v54 = *v53;
    BYTE1(v54) = BYTE1(*v53) | 4;
    *v53 = v54;
    v52[25] = this + 476696;
    store_color4f(v52 + 1, 1065353216, 1065353216, 1065353216, 1060320051);
    v55 = *v52;
    v52 += 44;
    v56 = v317 == 1;
    *(_DWORD *)(v55 + 20) = 9;
    --v317;
  }
  while ( !v56 );
  v57 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 298440), (int)v57);
  load_x_mesh(aSaltX, *(int **)(this + 298476), 1);
  v58 = (_DWORD *)(this + 3981152);
  v318 = 40;
  do
  {
    set_bod_object(v58 - 34, *(_DWORD *)(this + 298476));
    *v58 = this + 476696;
    store_color4f(v58 - 24, 1065353216, 1065353216, 1065353216, 1063675494);
    *(_DWORD *)(*(v58 - 25) + 20) = 12;
    set_matrix_identity(v58 - 20);
    v58 += 38;
    --v318;
  }
  while ( v318 );
  for ( i = 0; i < 2; ++i )
  {
    v319 = (_DWORD *)(this + 96 * i);
    v60 = add_object_to_list(unk_4B7648);
    set_bod_object(v319 + 996774, (int)v60);
    if ( i )
    {
      if ( i == 1 )
        load_x_mesh(aPostofficestop, *(int **)(this + 3987228), 1);
    }
    else
    {
      load_x_mesh(aPostofficestop, *(int **)(this + 3987132), 1);
    }
    v319[996780] = 0;
    v319[996779] = 0;
    v319[996778] = 0;
    *(_DWORD *)(32 * (3 * i + 124599) + this) = this + 476696;
    v319[996788] = i;
    v319[996796] = 0;
    v319[996797] = 1004768824;
  }
  v61 = this + 3973556;
  if ( (*(_DWORD *)(this + 3973560) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v62 = *(_DWORD *)(this + 1452);
    v63 = this + 1452;
    if ( v62 )
    {
      *(_DWORD *)(v62 + 8) = v61;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v63 + 8) + 12) = *(_DWORD *)v63;
      v64 = *(_DWORD *)(*(_DWORD *)v63 + 8);
      *(_DWORD *)v63 = v64;
      *(_DWORD *)(v64 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v63 = v61;
      *(_DWORD *)(this + 3973564) = 0;
      *(_DWORD *)(*(_DWORD *)v63 + 12) = 0;
    }
    v65 = *(_DWORD *)(this + 3973560);
    BYTE1(v65) |= 2u;
    *(_DWORD *)(this + 3973560) = v65;
  }
  v66 = this + 3973612;
  v67 = (int *)(this + 3973616);
  if ( (*(_DWORD *)(this + 3973616) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973620) = v61;
    *(_DWORD *)(this + 3973624) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v66;
    v68 = *(_DWORD *)(this + 3973624);
    if ( v68 )
      *(_DWORD *)(v68 + 8) = v66;
    v69 = *v67;
    BYTE1(v69) = BYTE1(*v67) | 2;
    *v67 = v69;
  }
  v70 = this + 3973668;
  v71 = (int *)(this + 3973672);
  if ( (*(_DWORD *)(this + 3973672) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973676) = v61;
    *(_DWORD *)(this + 3973680) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v70;
    v72 = *(_DWORD *)(this + 3973680);
    if ( v72 )
      *(_DWORD *)(v72 + 8) = v70;
    v73 = *v71;
    BYTE1(v73) = BYTE1(*v71) | 2;
    *v71 = v73;
  }
  v74 = this + 3973948;
  v75 = (int *)(this + 3973952);
  if ( (*(_DWORD *)(this + 3973952) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973956) = v61;
    *(_DWORD *)(this + 3973960) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v74;
    v76 = *(_DWORD *)(this + 3973960);
    if ( v76 )
      *(_DWORD *)(v76 + 8) = v74;
    v77 = *v75;
    BYTE1(v77) = BYTE1(*v75) | 2;
    *v75 = v77;
  }
  v78 = this + 3973500;
  v79 = (int *)(this + 3973504);
  if ( (*(_DWORD *)(this + 3973504) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973508) = v61;
    *(_DWORD *)(this + 3973512) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v78;
    v80 = *(_DWORD *)(this + 3973512);
    if ( v80 )
      *(_DWORD *)(v80 + 8) = v78;
    v81 = *v79;
    BYTE1(v81) = BYTE1(*v79) | 2;
    *v79 = v81;
  }
  v82 = this + 3973836;
  v83 = (int *)(this + 3973840);
  if ( (*(_DWORD *)(this + 3973840) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973844) = v61;
    *(_DWORD *)(this + 3973848) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v82;
    v84 = *(_DWORD *)(this + 3973848);
    if ( v84 )
      *(_DWORD *)(v84 + 8) = v82;
    v85 = *v83;
    BYTE1(v85) = BYTE1(*v83) | 2;
    *v83 = v85;
  }
  v86 = this + 3973892;
  v87 = (int *)(this + 3973896);
  if ( (*(_DWORD *)(this + 3973896) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973900) = v61;
    *(_DWORD *)(this + 3973904) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v86;
    v88 = *(_DWORD *)(this + 3973904);
    if ( v88 )
      *(_DWORD *)(v88 + 8) = v86;
    v89 = *v87;
    BYTE1(v89) = BYTE1(*v87) | 2;
    *v87 = v89;
  }
  v90 = this + 3973724;
  v91 = (int *)(this + 3973728);
  if ( (*(_DWORD *)(this + 3973728) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973732) = v61;
    *(_DWORD *)(this + 3973736) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v90;
    v92 = *(_DWORD *)(this + 3973736);
    if ( v92 )
      *(_DWORD *)(v92 + 8) = v90;
    v93 = *v91;
    BYTE1(v93) = BYTE1(*v91) | 2;
    *v91 = v93;
  }
  v94 = this + 3973780;
  v95 = (int *)(this + 3973784);
  if ( (*(_DWORD *)(this + 3973784) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973788) = v61;
    *(_DWORD *)(this + 3973792) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v94;
    v96 = *(_DWORD *)(this + 3973792);
    if ( v96 )
      *(_DWORD *)(v96 + 8) = v94;
    v97 = *v95;
    BYTE1(v97) = BYTE1(*v95) | 2;
    *v95 = v97;
  }
  sub_449C00();
  v98 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17198892), (int)v98);
  initialize_looptheloop_path_template_pair(this + 17198892, 6.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17198916) = 0;
  *(_DWORD *)(this + 17198912) = 0;
  *(_DWORD *)(this + 17198908) = 0;
  v99 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199060), (int)v99);
  mirror_path_template_pair_x(this + 17199060, this + 17198892);
  *(_DWORD *)(this + 17199084) = 0;
  *(_DWORD *)(this + 17199080) = 0;
  *(_DWORD *)(this + 17199076) = 0;
  build_track_fringe_mesh(this + 17198892, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199012) = 0;
  *(_DWORD *)(this + 17199008) = 0;
  *(_DWORD *)(this + 17199004) = 0;
  build_track_fringe_mesh(this + 17199060, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199180) = 0;
  *(_DWORD *)(this + 17199176) = 0;
  *(_DWORD *)(this + 17199172) = 0;
  v100 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199228), (int)v100);
  initialize_looptheloop_path_template_pair(this + 17199228, 6.0, 2, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17199252) = 0;
  *(_DWORD *)(this + 17199248) = 0;
  *(_DWORD *)(this + 17199244) = 0;
  v101 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199396), (int)v101);
  mirror_path_template_pair_x(this + 17199396, this + 17199228);
  *(_DWORD *)(this + 17199420) = 0;
  *(_DWORD *)(this + 17199416) = 0;
  *(_DWORD *)(this + 17199412) = 0;
  build_track_fringe_mesh(this + 17199228, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199348) = 0;
  *(_DWORD *)(this + 17199344) = 0;
  *(_DWORD *)(this + 17199340) = 0;
  build_track_fringe_mesh(this + 17199396, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199516) = 0;
  *(_DWORD *)(this + 17199512) = 0;
  *(_DWORD *)(this + 17199508) = 0;
  v102 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199564), (int)v102);
  initialize_looptheloop_path_template_pair(this + 17199564, 8.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17199588) = 0;
  *(_DWORD *)(this + 17199584) = 0;
  *(_DWORD *)(this + 17199580) = 0;
  v103 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199732), (int)v103);
  mirror_path_template_pair_x(this + 17199732, this + 17199564);
  *(_DWORD *)(this + 17199756) = 0;
  *(_DWORD *)(this + 17199752) = 0;
  *(_DWORD *)(this + 17199748) = 0;
  build_track_fringe_mesh(this + 17199564, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199684) = 0;
  *(_DWORD *)(this + 17199680) = 0;
  *(_DWORD *)(this + 17199676) = 0;
  build_track_fringe_mesh(this + 17199732, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199852) = 0;
  *(_DWORD *)(this + 17199848) = 0;
  *(_DWORD *)(this + 17199844) = 0;
  v104 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200908), (int)v104);
  initialize_looptheloopw_path_template_pair(this + 17200908, 8.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17200932) = 0;
  *(_DWORD *)(this + 17200928) = 0;
  *(_DWORD *)(this + 17200924) = 0;
  v105 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201076), (int)v105);
  mirror_path_template_pair_x(this + 17201076, this + 17200908);
  *(_DWORD *)(this + 17201100) = 0;
  *(_DWORD *)(this + 17201096) = 0;
  *(_DWORD *)(this + 17201092) = 0;
  build_track_fringe_mesh(this + 17200908, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201028) = 0;
  *(_DWORD *)(this + 17201024) = 0;
  *(_DWORD *)(this + 17201020) = 0;
  build_track_fringe_mesh(this + 17201076, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201196) = 0;
  *(_DWORD *)(this + 17201192) = 0;
  *(_DWORD *)(this + 17201188) = 0;
  v106 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17199900), (int)v106);
  initialize_looptheloop_path_template_pair(this + 17199900, 3.0, 2, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17199924) = 0;
  *(_DWORD *)(this + 17199920) = 0;
  *(_DWORD *)(this + 17199916) = 0;
  v107 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200068), (int)v107);
  mirror_path_template_pair_x(this + 17200068, this + 17199900);
  *(_DWORD *)(this + 17200092) = 0;
  *(_DWORD *)(this + 17200088) = 0;
  *(_DWORD *)(this + 17200084) = 0;
  build_track_fringe_mesh(this + 17199900, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200020) = 0;
  *(_DWORD *)(this + 17200016) = 0;
  *(_DWORD *)(this + 17200012) = 0;
  build_track_fringe_mesh(this + 17200068, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200188) = 0;
  *(_DWORD *)(this + 17200184) = 0;
  *(_DWORD *)(this + 17200180) = 0;
  v108 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200236), (int)v108);
  initialize_looptheloop_path_template_pair(this + 17200236, 3.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17200260) = 0;
  *(_DWORD *)(this + 17200256) = 0;
  *(_DWORD *)(this + 17200252) = 0;
  v109 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200404), (int)v109);
  mirror_path_template_pair_x(this + 17200404, this + 17200236);
  *(_DWORD *)(this + 17200428) = 0;
  *(_DWORD *)(this + 17200424) = 0;
  *(_DWORD *)(this + 17200420) = 0;
  build_track_fringe_mesh(this + 17200236, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200356) = 0;
  *(_DWORD *)(this + 17200352) = 0;
  *(_DWORD *)(this + 17200348) = 0;
  build_track_fringe_mesh(this + 17200404, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200524) = 0;
  *(_DWORD *)(this + 17200520) = 0;
  *(_DWORD *)(this + 17200516) = 0;
  v110 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200572), (int)v110);
  initialize_looptheloop_path_template_pair(this + 17200572, 3.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17200596) = 0;
  *(_DWORD *)(this + 17200592) = 0;
  *(_DWORD *)(this + 17200588) = 0;
  v111 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17200740), (int)v111);
  mirror_path_template_pair_x(this + 17200740, this + 17200572);
  *(_DWORD *)(this + 17200764) = 0;
  *(_DWORD *)(this + 17200760) = 0;
  *(_DWORD *)(this + 17200756) = 0;
  build_track_fringe_mesh(this + 17200572, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200692) = 0;
  *(_DWORD *)(this + 17200688) = 0;
  *(_DWORD *)(this + 17200684) = 0;
  build_track_fringe_mesh(this + 17200740, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17200860) = 0;
  *(_DWORD *)(this + 17200856) = 0;
  *(_DWORD *)(this + 17200852) = 0;
  v112 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201244), (int)v112);
  initialize_loopbow_path_template_pair(this + 17201244, 6.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17201268) = 0;
  *(_DWORD *)(this + 17201264) = 0;
  *(_DWORD *)(this + 17201260) = 0;
  v113 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201412), (int)v113);
  mirror_path_template_pair_x(this + 17201412, this + 17201244);
  *(_DWORD *)(this + 17201436) = 0;
  *(_DWORD *)(this + 17201432) = 0;
  *(_DWORD *)(this + 17201428) = 0;
  build_track_fringe_mesh(this + 17201244, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201364) = 0;
  *(_DWORD *)(this + 17201360) = 0;
  *(_DWORD *)(this + 17201356) = 0;
  build_track_fringe_mesh(this + 17201412, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201532) = 0;
  *(_DWORD *)(this + 17201528) = 0;
  *(_DWORD *)(this + 17201524) = 0;
  v114 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211324), (int)v114);
  initialize_turnover_path_template_pair(this + 17211324, 6.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17211348) = 0;
  *(_DWORD *)(this + 17211344) = 0;
  *(_DWORD *)(this + 17211340) = 0;
  v115 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211492), (int)v115);
  mirror_path_template_pair_x(this + 17211492, this + 17211324);
  *(_DWORD *)(this + 17211516) = 0;
  *(_DWORD *)(this + 17211512) = 0;
  *(_DWORD *)(this + 17211508) = 0;
  build_track_fringe_mesh(this + 17211324, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211444) = 0;
  *(_DWORD *)(this + 17211440) = 0;
  *(_DWORD *)(this + 17211436) = 0;
  build_track_fringe_mesh(this + 17211492, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211612) = 0;
  *(_DWORD *)(this + 17211608) = 0;
  *(_DWORD *)(this + 17211604) = 0;
  v116 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211660), (int)v116);
  initialize_turnoverdouble_path_template_pair(this + 17211660, 6.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17211684) = 0;
  *(_DWORD *)(this + 17211680) = 0;
  *(_DWORD *)(this + 17211676) = 0;
  v117 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211828), (int)v117);
  mirror_path_template_pair_x(this + 17211828, this + 17211660);
  *(_DWORD *)(this + 17211852) = 0;
  *(_DWORD *)(this + 17211848) = 0;
  *(_DWORD *)(this + 17211844) = 0;
  build_track_fringe_mesh(this + 17211660, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211780) = 0;
  *(_DWORD *)(this + 17211776) = 0;
  *(_DWORD *)(this + 17211772) = 0;
  build_track_fringe_mesh(this + 17211828, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211948) = 0;
  *(_DWORD *)(this + 17211944) = 0;
  *(_DWORD *)(this + 17211940) = 0;
  v118 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213340), (int)v118);
  initialize_twister_path_template_pair(
    this + 17213340,
    2.5,
    COERCE_FLOAT(3),
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17213364) = 0;
  *(_DWORD *)(this + 17213360) = 0;
  *(_DWORD *)(this + 17213356) = 0;
  v119 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213508), (int)v119);
  mirror_path_template_pair_x(this + 17213508, this + 17213340);
  *(_DWORD *)(this + 17213532) = 0;
  *(_DWORD *)(this + 17213528) = 0;
  *(_DWORD *)(this + 17213524) = 0;
  build_track_fringe_mesh(this + 17213340, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213460) = 0;
  *(_DWORD *)(this + 17213456) = 0;
  *(_DWORD *)(this + 17213452) = 0;
  build_track_fringe_mesh(this + 17213508, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213628) = 0;
  *(_DWORD *)(this + 17213624) = 0;
  *(_DWORD *)(this + 17213620) = 0;
  v120 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213676), (int)v120);
  initialize_twister_path_template_pair(
    this + 17213676,
    2.5,
    COERCE_FLOAT(3),
    0,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17213700) = 0;
  *(_DWORD *)(this + 17213696) = 0;
  *(_DWORD *)(this + 17213692) = 0;
  v121 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213844), (int)v121);
  mirror_path_template_pair_x(this + 17213844, this + 17213676);
  *(_DWORD *)(this + 17213868) = 0;
  *(_DWORD *)(this + 17213864) = 0;
  *(_DWORD *)(this + 17213860) = 0;
  build_track_fringe_mesh(this + 17213676, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213796) = 0;
  *(_DWORD *)(this + 17213792) = 0;
  *(_DWORD *)(this + 17213788) = 0;
  build_track_fringe_mesh(this + 17213844, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213964) = 0;
  *(_DWORD *)(this + 17213960) = 0;
  *(_DWORD *)(this + 17213956) = 0;
  v122 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214012), (int)v122);
  initialize_twister2_path_template_pair(
    this + 17214012,
    2.5,
    COERCE_FLOAT(3),
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17214036) = 0;
  *(_DWORD *)(this + 17214032) = 0;
  *(_DWORD *)(this + 17214028) = 0;
  v123 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214180), (int)v123);
  mirror_path_template_pair_x(this + 17214180, this + 17214012);
  *(_DWORD *)(this + 17214204) = 0;
  *(_DWORD *)(this + 17214200) = 0;
  *(_DWORD *)(this + 17214196) = 0;
  build_track_fringe_mesh(this + 17214012, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214132) = 0;
  *(_DWORD *)(this + 17214128) = 0;
  *(_DWORD *)(this + 17214124) = 0;
  build_track_fringe_mesh(this + 17214180, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214300) = 0;
  *(_DWORD *)(this + 17214296) = 0;
  *(_DWORD *)(this + 17214292) = 0;
  v124 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214348), (int)v124);
  initialize_twister2_path_template_pair(
    this + 17214348,
    2.5,
    COERCE_FLOAT(3),
    0,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17214372) = 0;
  *(_DWORD *)(this + 17214368) = 0;
  *(_DWORD *)(this + 17214364) = 0;
  v125 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214516), (int)v125);
  mirror_path_template_pair_x(this + 17214516, this + 17214348);
  *(_DWORD *)(this + 17214540) = 0;
  *(_DWORD *)(this + 17214536) = 0;
  *(_DWORD *)(this + 17214532) = 0;
  build_track_fringe_mesh(this + 17214348, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214468) = 0;
  *(_DWORD *)(this + 17214464) = 0;
  *(_DWORD *)(this + 17214460) = 0;
  build_track_fringe_mesh(this + 17214516, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214636) = 0;
  *(_DWORD *)(this + 17214632) = 0;
  *(_DWORD *)(this + 17214628) = 0;
  v126 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211996), (int)v126);
  initialize_turnunder_path_template_pair(this + 17211996, 6.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17212020) = 0;
  *(_DWORD *)(this + 17212016) = 0;
  *(_DWORD *)(this + 17212012) = 0;
  v127 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17212164), (int)v127);
  mirror_path_template_pair_x(this + 17212164, this + 17211996);
  *(_DWORD *)(this + 17212188) = 0;
  *(_DWORD *)(this + 17212184) = 0;
  *(_DWORD *)(this + 17212180) = 0;
  build_track_fringe_mesh(this + 17211996, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212116) = 0;
  *(_DWORD *)(this + 17212112) = 0;
  *(_DWORD *)(this + 17212108) = 0;
  build_track_fringe_mesh(this + 17212164, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212284) = 0;
  *(_DWORD *)(this + 17212280) = 0;
  *(_DWORD *)(this + 17212276) = 0;
  v128 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17212668), (int)v128);
  initialize_invert_path_template_pair(
    this + 17212668,
    1086324736,
    COERCE_FLOAT(8),
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17212692) = 0;
  *(_DWORD *)(this + 17212688) = 0;
  *(_DWORD *)(this + 17212684) = 0;
  v129 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17212836), (int)v129);
  mirror_path_template_pair_x(this + 17212836, this + 17212668);
  *(_DWORD *)(this + 17212860) = 0;
  *(_DWORD *)(this + 17212856) = 0;
  *(_DWORD *)(this + 17212852) = 0;
  build_track_fringe_mesh(this + 17212668, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212788) = 0;
  *(_DWORD *)(this + 17212784) = 0;
  *(_DWORD *)(this + 17212780) = 0;
  build_track_fringe_mesh(this + 17212836, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212956) = 0;
  *(_DWORD *)(this + 17212952) = 0;
  *(_DWORD *)(this + 17212948) = 0;
  v130 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213004), (int)v130);
  initialize_halfpipe_path_template_pair(this + 17213004, 1086324736, 8, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17213028) = 0;
  *(_DWORD *)(this + 17213024) = 0;
  *(_DWORD *)(this + 17213020) = 0;
  v131 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17213172), (int)v131);
  mirror_path_template_pair_x(this + 17213172, this + 17213004);
  *(_DWORD *)(this + 17213196) = 0;
  *(_DWORD *)(this + 17213192) = 0;
  *(_DWORD *)(this + 17213188) = 0;
  build_track_fringe_mesh(this + 17213004, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213124) = 0;
  *(_DWORD *)(this + 17213120) = 0;
  *(_DWORD *)(this + 17213116) = 0;
  build_track_fringe_mesh(this + 17213172, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17213292) = 0;
  *(_DWORD *)(this + 17213288) = 0;
  *(_DWORD *)(this + 17213284) = 0;
  v132 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17212332), (int)v132);
  initialize_wibble_path_template_pair(this + 17212332, 1086324736, 8, 1, texture_a, texture_a, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17212356) = 0;
  *(_DWORD *)(this + 17212352) = 0;
  *(_DWORD *)(this + 17212348) = 0;
  v133 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17212500), (int)v133);
  mirror_path_template_pair_x(this + 17212500, this + 17212332);
  *(_DWORD *)(this + 17212524) = 0;
  *(_DWORD *)(this + 17212520) = 0;
  *(_DWORD *)(this + 17212516) = 0;
  build_track_fringe_mesh(this + 17212332, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212452) = 0;
  *(_DWORD *)(this + 17212448) = 0;
  *(_DWORD *)(this + 17212444) = 0;
  build_track_fringe_mesh(this + 17212500, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17212620) = 0;
  *(_DWORD *)(this + 17212616) = 0;
  *(_DWORD *)(this + 17212612) = 0;
  v134 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17209308), (int)v134);
  initialize_supertramp_path_template_pair(
    this + 17209308,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer,
    aObjectsWorld00_0);
  *(_DWORD *)(this + 17209332) = 0;
  *(_DWORD *)(this + 17209328) = 0;
  *(_DWORD *)(this + 17209324) = 0;
  build_track_fringe_supertramp_mesh((_DWORD *)(this + 17209308), aObjectsUnivers_1);
  *(_DWORD *)(this + 17209428) = 0;
  *(_DWORD *)(this + 17209424) = 0;
  *(_DWORD *)(this + 17209420) = 0;
  v135 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17209476), (int)v135);
  initialize_supertramp_path_template_pair(
    this + 17209476,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer,
    aObjectsWorld00_0);
  *(_DWORD *)(this + 17209500) = 0;
  *(_DWORD *)(this + 17209496) = 0;
  *(_DWORD *)(this + 17209492) = 0;
  build_track_fringe_supertramp_mesh((_DWORD *)(this + 17209476), aObjectsUnivers_1);
  *(_DWORD *)(this + 17209596) = 0;
  *(_DWORD *)(this + 17209592) = 0;
  *(_DWORD *)(this + 17209588) = 0;
  v136 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210988), (int)v136);
  initialize_start_path_template_pair(this + 17210988, 4.0, 8, 1, texture_a, (int)texture_a, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17211012) = 0;
  *(_DWORD *)(this + 17211008) = 0;
  *(_DWORD *)(this + 17211004) = 0;
  build_track_fringe_mesh(this + 17210988, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211108) = 0;
  *(_DWORD *)(this + 17211104) = 0;
  *(_DWORD *)(this + 17211100) = 0;
  v137 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17211156), (int)v137);
  initialize_start_path_template_pair(
    this + 17211156,
    4.0,
    8,
    1,
    texture_a,
    (int)aObjectsWorld00_3,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17211180) = 0;
  *(_DWORD *)(this + 17211176) = 0;
  *(_DWORD *)(this + 17211172) = 0;
  build_track_fringe_mesh(this + 17211156, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17211276) = 0;
  *(_DWORD *)(this + 17211272) = 0;
  *(_DWORD *)(this + 17211268) = 0;
  v138 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207292), (int)v138);
  initialize_loopout_path_template_pair(this + 17207292, 3.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17207316) = 0;
  *(_DWORD *)(this + 17207312) = 0;
  *(_DWORD *)(this + 17207308) = 0;
  v139 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207460), (int)v139);
  mirror_path_template_pair_x(this + 17207460, this + 17207292);
  *(_DWORD *)(this + 17207484) = 0;
  *(_DWORD *)(this + 17207480) = 0;
  *(_DWORD *)(this + 17207476) = 0;
  build_track_fringe_mesh(this + 17207292, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17207412) = 0;
  *(_DWORD *)(this + 17207408) = 0;
  *(_DWORD *)(this + 17207404) = 0;
  build_track_fringe_mesh(this + 17207460, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17207580) = 0;
  *(_DWORD *)(this + 17207576) = 0;
  *(_DWORD *)(this + 17207572) = 0;
  v140 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207964), (int)v140);
  initialize_loopout_path_template_pair(this + 17207964, 5.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17207988) = 0;
  *(_DWORD *)(this + 17207984) = 0;
  *(_DWORD *)(this + 17207980) = 0;
  v141 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17208132), (int)v141);
  mirror_path_template_pair_x(this + 17208132, this + 17207964);
  *(_DWORD *)(this + 17208156) = 0;
  *(_DWORD *)(this + 17208152) = 0;
  *(_DWORD *)(this + 17208148) = 0;
  build_track_fringe_mesh(this + 17207964, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208084) = 0;
  *(_DWORD *)(this + 17208080) = 0;
  *(_DWORD *)(this + 17208076) = 0;
  build_track_fringe_mesh(this + 17208132, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208252) = 0;
  *(_DWORD *)(this + 17208248) = 0;
  *(_DWORD *)(this + 17208244) = 0;
  v142 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207628), (int)v142);
  initialize_loopout_path_template_pair(this + 17207628, 3.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17207652) = 0;
  *(_DWORD *)(this + 17207648) = 0;
  *(_DWORD *)(this + 17207644) = 0;
  v143 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207796), (int)v143);
  mirror_path_template_pair_x(this + 17207796, this + 17207628);
  *(_DWORD *)(this + 17207820) = 0;
  *(_DWORD *)(this + 17207816) = 0;
  *(_DWORD *)(this + 17207812) = 0;
  build_track_fringe_mesh(this + 17207628, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17207748) = 0;
  *(_DWORD *)(this + 17207744) = 0;
  *(_DWORD *)(this + 17207740) = 0;
  build_track_fringe_mesh(this + 17207796, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17207916) = 0;
  *(_DWORD *)(this + 17207912) = 0;
  *(_DWORD *)(this + 17207908) = 0;
  v144 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204268), (int)v144);
  initialize_hump_path_template_pair(this + 17204268, 4.0, 1.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17204292) = 0;
  *(_DWORD *)(this + 17204288) = 0;
  *(_DWORD *)(this + 17204284) = 0;
  v145 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204436), (int)v145);
  mirror_path_template_pair_x(this + 17204436, this + 17204268);
  *(_DWORD *)(this + 17204460) = 0;
  *(_DWORD *)(this + 17204456) = 0;
  *(_DWORD *)(this + 17204452) = 0;
  build_track_fringe_mesh(this + 17204268, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204388) = 0;
  *(_DWORD *)(this + 17204384) = 0;
  *(_DWORD *)(this + 17204380) = 0;
  build_track_fringe_mesh(this + 17204436, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204556) = 0;
  *(_DWORD *)(this + 17204552) = 0;
  *(_DWORD *)(this + 17204548) = 0;
  v146 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204604), (int)v146);
  initialize_dump_path_template_pair(this + 17204604, 4.0, 1.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17204628) = 0;
  *(_DWORD *)(this + 17204624) = 0;
  *(_DWORD *)(this + 17204620) = 0;
  v147 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204772), (int)v147);
  mirror_path_template_pair_x(this + 17204772, this + 17204604);
  *(_DWORD *)(this + 17204796) = 0;
  *(_DWORD *)(this + 17204792) = 0;
  *(_DWORD *)(this + 17204788) = 0;
  build_track_fringe_mesh(this + 17204604, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204724) = 0;
  *(_DWORD *)(this + 17204720) = 0;
  *(_DWORD *)(this + 17204716) = 0;
  build_track_fringe_mesh(this + 17204772, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204892) = 0;
  *(_DWORD *)(this + 17204888) = 0;
  *(_DWORD *)(this + 17204884) = 0;
  v148 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204940), (int)v148);
  initialize_hump_path_template_pair(this + 17204940, 4.0, 0.30000001, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17204964) = 0;
  *(_DWORD *)(this + 17204960) = 0;
  *(_DWORD *)(this + 17204956) = 0;
  v149 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205108), (int)v149);
  mirror_path_template_pair_x(this + 17205108, this + 17204940);
  *(_DWORD *)(this + 17205132) = 0;
  *(_DWORD *)(this + 17205128) = 0;
  *(_DWORD *)(this + 17205124) = 0;
  build_track_fringe_mesh(this + 17204940, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205060) = 0;
  *(_DWORD *)(this + 17205056) = 0;
  *(_DWORD *)(this + 17205052) = 0;
  build_track_fringe_mesh(this + 17205108, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205228) = 0;
  *(_DWORD *)(this + 17205224) = 0;
  *(_DWORD *)(this + 17205220) = 0;
  v150 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205276), (int)v150);
  initialize_dump_path_template_pair(this + 17205276, 4.0, 0.30000001, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17205300) = 0;
  *(_DWORD *)(this + 17205296) = 0;
  *(_DWORD *)(this + 17205292) = 0;
  v151 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205444), (int)v151);
  mirror_path_template_pair_x(this + 17205444, this + 17205276);
  *(_DWORD *)(this + 17205468) = 0;
  *(_DWORD *)(this + 17205464) = 0;
  *(_DWORD *)(this + 17205460) = 0;
  build_track_fringe_mesh(this + 17205276, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205396) = 0;
  *(_DWORD *)(this + 17205392) = 0;
  *(_DWORD *)(this + 17205388) = 0;
  build_track_fringe_mesh(this + 17205444, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205564) = 0;
  *(_DWORD *)(this + 17205560) = 0;
  *(_DWORD *)(this + 17205556) = 0;
  v152 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201580), (int)v152);
  initialize_hill_valley_path_template_pair(
    this + 17201580,
    8,
    4.0,
    20.0,
    COERCE_FLOAT(1),
    texture_a,
    texture_a,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17201604) = 0;
  *(_DWORD *)(this + 17201600) = 0;
  *(_DWORD *)(this + 17201596) = 0;
  v153 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201748), (int)v153);
  mirror_path_template_pair_x(this + 17201748, this + 17201580);
  *(_DWORD *)(this + 17201772) = 0;
  *(_DWORD *)(this + 17201768) = 0;
  *(_DWORD *)(this + 17201764) = 0;
  build_track_fringe_mesh(this + 17201580, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201700) = 0;
  *(_DWORD *)(this + 17201696) = 0;
  *(_DWORD *)(this + 17201692) = 0;
  build_track_fringe_mesh(this + 17201748, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17201868) = 0;
  *(_DWORD *)(this + 17201864) = 0;
  *(_DWORD *)(this + 17201860) = 0;
  v154 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202252), (int)v154);
  initialize_hill_valley_path_template_pair(
    this + 17202252,
    4,
    4.0,
    20.0,
    0.0,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17202276) = 0;
  *(_DWORD *)(this + 17202272) = 0;
  *(_DWORD *)(this + 17202268) = 0;
  v155 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202420), (int)v155);
  mirror_path_template_pair_x(this + 17202420, this + 17202252);
  *(_DWORD *)(this + 17202444) = 0;
  *(_DWORD *)(this + 17202440) = 0;
  *(_DWORD *)(this + 17202436) = 0;
  build_track_fringe_mesh(this + 17202252, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202372) = 0;
  *(_DWORD *)(this + 17202368) = 0;
  *(_DWORD *)(this + 17202364) = 0;
  build_track_fringe_mesh(this + 17202420, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202540) = 0;
  *(_DWORD *)(this + 17202536) = 0;
  *(_DWORD *)(this + 17202532) = 0;
  v156 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17201916), (int)v156);
  initialize_hill_valley_path_template_pair(
    this + 17201916,
    4,
    4.0,
    20.0,
    COERCE_FLOAT(1),
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17201940) = 0;
  *(_DWORD *)(this + 17201936) = 0;
  *(_DWORD *)(this + 17201932) = 0;
  v157 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202084), (int)v157);
  mirror_path_template_pair_x(this + 17202084, this + 17201916);
  *(_DWORD *)(this + 17202108) = 0;
  *(_DWORD *)(this + 17202104) = 0;
  *(_DWORD *)(this + 17202100) = 0;
  build_track_fringe_mesh(this + 17201916, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202036) = 0;
  *(_DWORD *)(this + 17202032) = 0;
  *(_DWORD *)(this + 17202028) = 0;
  build_track_fringe_mesh(this + 17202084, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202204) = 0;
  *(_DWORD *)(this + 17202200) = 0;
  *(_DWORD *)(this + 17202196) = 0;
  v158 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203596), (int)v158);
  initialize_sbend_path_template_pair(
    this + 17203596,
    8,
    8.0,
    14.0,
    1,
    aObjectsWorld00,
    aObjectsWorld00,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17203620) = 0;
  *(_DWORD *)(this + 17203616) = 0;
  *(_DWORD *)(this + 17203612) = 0;
  v159 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203764), (int)v159);
  mirror_path_template_pair_x(this + 17203764, this + 17203596);
  *(_DWORD *)(this + 17203788) = 0;
  *(_DWORD *)(this + 17203784) = 0;
  *(_DWORD *)(this + 17203780) = 0;
  build_track_fringe_mesh(this + 17203596, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203716) = 0;
  *(_DWORD *)(this + 17203712) = 0;
  *(_DWORD *)(this + 17203708) = 0;
  build_track_fringe_mesh(this + 17203764, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203884) = 0;
  *(_DWORD *)(this + 17203880) = 0;
  *(_DWORD *)(this + 17203876) = 0;
  v160 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202588), (int)v160);
  initialize_hill_valley_path_template_pair(
    this + 17202588,
    8,
    -4.0,
    20.0,
    COERCE_FLOAT(1),
    texture_a,
    texture_a,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17202612) = 0;
  *(_DWORD *)(this + 17202608) = 0;
  *(_DWORD *)(this + 17202604) = 0;
  v161 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202756), (int)v161);
  mirror_path_template_pair_x(this + 17202756, this + 17202588);
  *(_DWORD *)(this + 17202780) = 0;
  *(_DWORD *)(this + 17202776) = 0;
  *(_DWORD *)(this + 17202772) = 0;
  build_track_fringe_mesh(this + 17202588, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202708) = 0;
  *(_DWORD *)(this + 17202704) = 0;
  *(_DWORD *)(this + 17202700) = 0;
  build_track_fringe_mesh(this + 17202756, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17202876) = 0;
  *(_DWORD *)(this + 17202872) = 0;
  *(_DWORD *)(this + 17202868) = 0;
  v162 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203260), (int)v162);
  initialize_hill_valley_path_template_pair(
    this + 17203260,
    4,
    -4.0,
    20.0,
    0.0,
    texture_a,
    texture_a,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17203284) = 0;
  *(_DWORD *)(this + 17203280) = 0;
  *(_DWORD *)(this + 17203276) = 0;
  v163 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203428), (int)v163);
  mirror_path_template_pair_x(this + 17203428, this + 17203260);
  *(_DWORD *)(this + 17203452) = 0;
  *(_DWORD *)(this + 17203448) = 0;
  *(_DWORD *)(this + 17203444) = 0;
  build_track_fringe_mesh(this + 17203260, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203380) = 0;
  *(_DWORD *)(this + 17203376) = 0;
  *(_DWORD *)(this + 17203372) = 0;
  build_track_fringe_mesh(this + 17203428, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203548) = 0;
  *(_DWORD *)(this + 17203544) = 0;
  *(_DWORD *)(this + 17203540) = 0;
  v164 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17202924), (int)v164);
  initialize_hill_valley_path_template_pair(
    this + 17202924,
    4,
    -4.0,
    20.0,
    COERCE_FLOAT(1),
    texture_a,
    texture_a,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17202948) = 0;
  *(_DWORD *)(this + 17202944) = 0;
  *(_DWORD *)(this + 17202940) = 0;
  v165 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203092), (int)v165);
  mirror_path_template_pair_x(this + 17203092, this + 17202924);
  *(_DWORD *)(this + 17203116) = 0;
  *(_DWORD *)(this + 17203112) = 0;
  *(_DWORD *)(this + 17203108) = 0;
  build_track_fringe_mesh(this + 17202924, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203044) = 0;
  *(_DWORD *)(this + 17203040) = 0;
  *(_DWORD *)(this + 17203036) = 0;
  build_track_fringe_mesh(this + 17203092, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17203212) = 0;
  *(_DWORD *)(this + 17203208) = 0;
  *(_DWORD *)(this + 17203204) = 0;
  v166 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205612), (int)v166);
  initialize_dip_path_template_pair(this + 17205612, 4.0, 2, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17205636) = 0;
  *(_DWORD *)(this + 17205632) = 0;
  *(_DWORD *)(this + 17205628) = 0;
  v167 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205780), (int)v167);
  mirror_path_template_pair_x(this + 17205780, this + 17205612);
  *(_DWORD *)(this + 17205804) = 0;
  *(_DWORD *)(this + 17205800) = 0;
  *(_DWORD *)(this + 17205796) = 0;
  build_track_fringe_mesh(this + 17205612, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205732) = 0;
  *(_DWORD *)(this + 17205728) = 0;
  *(_DWORD *)(this + 17205724) = 0;
  build_track_fringe_mesh(this + 17205780, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17205900) = 0;
  *(_DWORD *)(this + 17205896) = 0;
  *(_DWORD *)(this + 17205892) = 0;
  v168 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17205948), (int)v168);
  initialize_screw_path_template_pair(this + 17205948, 24, 3, 1, texture_a, texture_a, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17205972) = 0;
  *(_DWORD *)(this + 17205968) = 0;
  *(_DWORD *)(this + 17205964) = 0;
  v169 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206116), (int)v169);
  mirror_path_template_pair_x(this + 17206116, this + 17205948);
  *(_DWORD *)(this + 17206140) = 0;
  *(_DWORD *)(this + 17206136) = 0;
  *(_DWORD *)(this + 17206132) = 0;
  build_track_fringe_mesh(this + 17205948, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206068) = 0;
  *(_DWORD *)(this + 17206064) = 0;
  *(_DWORD *)(this + 17206060) = 0;
  build_track_fringe_mesh(this + 17206116, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206236) = 0;
  *(_DWORD *)(this + 17206232) = 0;
  *(_DWORD *)(this + 17206228) = 0;
  v170 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206284), (int)v170);
  initialize_slalom_path_template_pair(this + 17206284, 32, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17206308) = 0;
  *(_DWORD *)(this + 17206304) = 0;
  *(_DWORD *)(this + 17206300) = 0;
  v171 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206452), (int)v171);
  mirror_path_template_pair_x(this + 17206452, this + 17206284);
  *(_DWORD *)(this + 17206476) = 0;
  *(_DWORD *)(this + 17206472) = 0;
  *(_DWORD *)(this + 17206468) = 0;
  build_track_fringe_mesh(this + 17206284, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206404) = 0;
  *(_DWORD *)(this + 17206400) = 0;
  *(_DWORD *)(this + 17206396) = 0;
  build_track_fringe_mesh(this + 17206452, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206572) = 0;
  *(_DWORD *)(this + 17206568) = 0;
  *(_DWORD *)(this + 17206564) = 0;
  v172 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206620), (int)v172);
  initialize_slalombig_path_template_pair(this + 17206620, 32, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17206644) = 0;
  *(_DWORD *)(this + 17206640) = 0;
  *(_DWORD *)(this + 17206636) = 0;
  v173 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206788), (int)v173);
  mirror_path_template_pair_x(this + 17206788, this + 17206620);
  *(_DWORD *)(this + 17206812) = 0;
  *(_DWORD *)(this + 17206808) = 0;
  *(_DWORD *)(this + 17206804) = 0;
  build_track_fringe_mesh(this + 17206620, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206740) = 0;
  *(_DWORD *)(this + 17206736) = 0;
  *(_DWORD *)(this + 17206732) = 0;
  build_track_fringe_mesh(this + 17206788, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17206908) = 0;
  *(_DWORD *)(this + 17206904) = 0;
  *(_DWORD *)(this + 17206900) = 0;
  v174 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17209644), (int)v174);
  initialize_slalomdouble_path_template_pair(this + 17209644, 32, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17209668) = 0;
  *(_DWORD *)(this + 17209664) = 0;
  *(_DWORD *)(this + 17209660) = 0;
  v175 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17209812), (int)v175);
  mirror_path_template_pair_x(this + 17209812, this + 17209644);
  *(_DWORD *)(this + 17209836) = 0;
  *(_DWORD *)(this + 17209832) = 0;
  *(_DWORD *)(this + 17209828) = 0;
  build_track_fringe_mesh(this + 17209644, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17209764) = 0;
  *(_DWORD *)(this + 17209760) = 0;
  *(_DWORD *)(this + 17209756) = 0;
  build_track_fringe_mesh(this + 17209812, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17209932) = 0;
  *(_DWORD *)(this + 17209928) = 0;
  *(_DWORD *)(this + 17209924) = 0;
  v176 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17206956), (int)v176);
  initialize_worm_path_template_pair(this + 17206956, aObjectsWorld00_4);
  *(_DWORD *)(this + 17206980) = 0;
  *(_DWORD *)(this + 17206976) = 0;
  *(_DWORD *)(this + 17206972) = 0;
  v177 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207124), (int)v177);
  mirror_path_template_pair_x(this + 17207124, this + 17206956);
  *(_DWORD *)(this + 17207148) = 0;
  *(_DWORD *)(this + 17207144) = 0;
  *(_DWORD *)(this + 17207140) = 0;
  v178 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207052), (int)v178);
  sub_41A0A0(*(_DWORD *)(this + 17207088));
  v179 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17207220), (int)v179);
  sub_41A0A0(*(_DWORD *)(this + 17207256));
  *(_DWORD *)(*(_DWORD *)(this + 17206992) + 20) = 8;
  *(_DWORD *)(*(_DWORD *)(this + 17207160) + 20) = 8;
  v180 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17208300), (int)v180);
  initialize_sweep_path_template_pair(this + 17208300, 1082130432, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17208324) = 0;
  *(_DWORD *)(this + 17208320) = 0;
  *(_DWORD *)(this + 17208316) = 0;
  v181 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17208468), (int)v181);
  mirror_path_template_pair_x(this + 17208468, this + 17208300);
  *(_DWORD *)(this + 17208492) = 0;
  *(_DWORD *)(this + 17208488) = 0;
  *(_DWORD *)(this + 17208484) = 0;
  build_track_fringe_mesh(this + 17208300, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208420) = 0;
  *(_DWORD *)(this + 17208416) = 0;
  *(_DWORD *)(this + 17208412) = 0;
  build_track_fringe_mesh(this + 17208468, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208588) = 0;
  *(_DWORD *)(this + 17208584) = 0;
  *(_DWORD *)(this + 17208580) = 0;
  v182 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17203932), (int)v182);
  initialize_cage2_path_template_pair(this + 17203932, 3, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17203956) = 0;
  *(_DWORD *)(this + 17203952) = 0;
  *(_DWORD *)(this + 17203948) = 0;
  v183 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17204100), (int)v183);
  mirror_path_template_pair_x(this + 17204100, this + 17203932);
  *(_DWORD *)(this + 17204124) = 0;
  *(_DWORD *)(this + 17204120) = 0;
  *(_DWORD *)(this + 17204116) = 0;
  build_track_fringe_mesh(this + 17203932, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204052) = 0;
  *(_DWORD *)(this + 17204048) = 0;
  *(_DWORD *)(this + 17204044) = 0;
  build_track_fringe_mesh(this + 17204100, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17204220) = 0;
  *(_DWORD *)(this + 17204216) = 0;
  *(_DWORD *)(this + 17204212) = 0;
  v184 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17209980), (int)v184);
  initialize_p_path_template_pair(
    this + 17209980,
    0,
    1082130432,
    3,
    0.5,
    -2.5,
    14,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17210004) = 0;
  *(_DWORD *)(this + 17210000) = 0;
  *(_DWORD *)(this + 17209996) = 0;
  v185 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210148), (int)v185);
  mirror_path_template_pair_x(this + 17210148, this + 17209980);
  *(_DWORD *)(this + 17210172) = 0;
  *(_DWORD *)(this + 17210168) = 0;
  *(_DWORD *)(this + 17210164) = 0;
  build_track_fringe_mesh(this + 17209980, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210100) = 0;
  *(_DWORD *)(this + 17210096) = 0;
  *(_DWORD *)(this + 17210092) = 0;
  build_track_fringe_mesh(this + 17210148, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210268) = 0;
  *(_DWORD *)(this + 17210264) = 0;
  *(_DWORD *)(this + 17210260) = 0;
  v186 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210316), (int)v186);
  initialize_p_path_template_pair(
    this + 17210316,
    1,
    1082130432,
    3,
    -2.5,
    2.5,
    14,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17210340) = 0;
  *(_DWORD *)(this + 17210336) = 0;
  *(_DWORD *)(this + 17210332) = 0;
  v187 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210484), (int)v187);
  mirror_path_template_pair_x(this + 17210484, this + 17210316);
  *(_DWORD *)(this + 17210508) = 0;
  *(_DWORD *)(this + 17210504) = 0;
  *(_DWORD *)(this + 17210500) = 0;
  build_track_fringe_mesh(this + 17210316, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210436) = 0;
  *(_DWORD *)(this + 17210432) = 0;
  *(_DWORD *)(this + 17210428) = 0;
  build_track_fringe_mesh(this + 17210484, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210604) = 0;
  *(_DWORD *)(this + 17210600) = 0;
  *(_DWORD *)(this + 17210596) = 0;
  v188 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210652), (int)v188);
  initialize_p_path_template_pair(
    this + 17210652,
    2,
    1082130432,
    3,
    2.5,
    0.5,
    14,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17210676) = 0;
  *(_DWORD *)(this + 17210672) = 0;
  *(_DWORD *)(this + 17210668) = 0;
  v189 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17210820), (int)v189);
  mirror_path_template_pair_x(this + 17210820, this + 17210652);
  *(_DWORD *)(this + 17210844) = 0;
  *(_DWORD *)(this + 17210840) = 0;
  *(_DWORD *)(this + 17210836) = 0;
  build_track_fringe_mesh(this + 17210652, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210772) = 0;
  *(_DWORD *)(this + 17210768) = 0;
  *(_DWORD *)(this + 17210764) = 0;
  build_track_fringe_mesh(this + 17210820, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17210940) = 0;
  *(_DWORD *)(this + 17210936) = 0;
  *(_DWORD *)(this + 17210932) = 0;
  v190 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17208636), (int)v190);
  initialize_snake_path_template_pair(
    this + 17208636,
    0x40000000,
    4,
    1,
    texture_a,
    aObjectsWorld00,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17208660) = 0;
  *(_DWORD *)(this + 17208656) = 0;
  *(_DWORD *)(this + 17208652) = 0;
  v191 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17208804), (int)v191);
  mirror_path_template_pair_x(this + 17208804, this + 17208636);
  *(_DWORD *)(this + 17208828) = 0;
  *(_DWORD *)(this + 17208824) = 0;
  *(_DWORD *)(this + 17208820) = 0;
  build_track_fringe_mesh(this + 17208636, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208756) = 0;
  *(_DWORD *)(this + 17208752) = 0;
  *(_DWORD *)(this + 17208748) = 0;
  build_track_fringe_mesh(this + 17208804, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17208924) = 0;
  *(_DWORD *)(this + 17208920) = 0;
  *(_DWORD *)(this + 17208916) = 0;
  v192 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214684), (int)v192);
  initialize_toad_path_template_pair(this + 17214684, 1, texture_a, aObjectsWorld00, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17214708) = 0;
  *(_DWORD *)(this + 17214704) = 0;
  *(_DWORD *)(this + 17214700) = 0;
  v193 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17214852), (int)v193);
  mirror_path_template_pair_x(this + 17214852, this + 17214684);
  *(_DWORD *)(this + 17214876) = 0;
  *(_DWORD *)(this + 17214872) = 0;
  *(_DWORD *)(this + 17214868) = 0;
  build_track_fringe_mesh(this + 17214684, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214804) = 0;
  *(_DWORD *)(this + 17214800) = 0;
  *(_DWORD *)(this + 17214796) = 0;
  build_track_fringe_mesh(this + 17214852, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17214972) = 0;
  *(_DWORD *)(this + 17214968) = 0;
  *(_DWORD *)(this + 17214964) = 0;
  v194 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215020), (int)v194);
  initialize_toad_path_template_pair(this + 17215020, 0, texture_a, aObjectsWorld00, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17215044) = 0;
  *(_DWORD *)(this + 17215040) = 0;
  *(_DWORD *)(this + 17215036) = 0;
  v195 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215188), (int)v195);
  mirror_path_template_pair_x(this + 17215188, this + 17215020);
  *(_DWORD *)(this + 17215212) = 0;
  *(_DWORD *)(this + 17215208) = 0;
  *(_DWORD *)(this + 17215204) = 0;
  build_track_fringe_mesh(this + 17215020, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17215140) = 0;
  *(_DWORD *)(this + 17215136) = 0;
  *(_DWORD *)(this + 17215132) = 0;
  build_track_fringe_mesh(this + 17215188, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17215308) = 0;
  *(_DWORD *)(this + 17215304) = 0;
  *(_DWORD *)(this + 17215300) = 0;
  v196 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215356), (int)v196);
  initialize_toad_path_template_pair(this + 17215356, 1, texture_a, aObjectsWorld00, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17215380) = 0;
  *(_DWORD *)(this + 17215376) = 0;
  *(_DWORD *)(this + 17215372) = 0;
  v197 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215524), (int)v197);
  mirror_path_template_pair_x(this + 17215524, this + 17215356);
  *(_DWORD *)(this + 17215548) = 0;
  *(_DWORD *)(this + 17215544) = 0;
  *(_DWORD *)(this + 17215540) = 0;
  build_track_fringe_mesh(this + 17215356, aObjectsUnivers_1, -1.0);
  *(_DWORD *)(this + 17215476) = 0;
  *(_DWORD *)(this + 17215472) = 0;
  *(_DWORD *)(this + 17215468) = 0;
  build_track_fringe_mesh(this + 17215524, aObjectsUnivers_1, 1.0);
  *(_DWORD *)(this + 17215644) = 0;
  *(_DWORD *)(this + 17215640) = 0;
  *(_DWORD *)(this + 17215636) = 0;
  v198 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215692), (int)v198);
  initialize_toad_path_template_pair(this + 17215692, 0, texture_a, aObjectsWorld00, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17215716) = 0;
  *(_DWORD *)(this + 17215712) = 0;
  *(_DWORD *)(this + 17215708) = 0;
  v199 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17215860), (int)v199);
  mirror_path_template_pair_x(this + 17215860, this + 17215692);
  *(_DWORD *)(this + 17215884) = 0;
  *(_DWORD *)(this + 17215880) = 0;
  *(_DWORD *)(this + 17215876) = 0;
  build_track_fringe_mesh(this + 17215692, aObjectsUnivers_1, 1.0);
  *(_DWORD *)(this + 17215812) = 0;
  *(_DWORD *)(this + 17215808) = 0;
  *(_DWORD *)(this + 17215804) = 0;
  build_track_fringe_mesh(this + 17215860, aObjectsUnivers_1, -1.0);
  *(_DWORD *)(this + 17215980) = 0;
  *(_DWORD *)(this + 17215976) = 0;
  *(_DWORD *)(this + 17215972) = 0;
  Iostream_init::Iostream_init((#93 *)v328);
  store_color4f(v328, 1065353216, 1065353216, 1065353216, 1058642330);
  v200 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216028), (int)v200);
  initialize_looptheloop_path_template_pair(this + 17216028, 6.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17216052) = 0;
  *(_DWORD *)(this + 17216048) = 0;
  *(_DWORD *)(this + 17216044) = 0;
  v201 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216196), (int)v201);
  mirror_path_template_pair_x(this + 17216196, this + 17216028);
  *(_DWORD *)(this + 17216220) = 0;
  *(_DWORD *)(this + 17216216) = 0;
  *(_DWORD *)(this + 17216212) = 0;
  build_track_fringe_mesh(this + 17216028, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216148) = 0;
  *(_DWORD *)(this + 17216144) = 0;
  *(_DWORD *)(this + 17216140) = 0;
  build_track_fringe_mesh(this + 17216196, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216316) = 0;
  *(_DWORD *)(this + 17216312) = 0;
  *(_DWORD *)(this + 17216308) = 0;
  v202 = *(_DWORD *)(this + 17198928);
  v203 = *(_DWORD *)(this + 17216232);
  *(_DWORD *)(this + 17199052) = *(_DWORD *)(this + 17216064);
  v204 = *(_DWORD *)(this + 17199096);
  *(_DWORD *)(this + 17199056) = v202;
  *(_DWORD *)(this + 17199220) = v203;
  *(_DWORD *)(this + 17199224) = v204;
  v205 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216364), (int)v205);
  initialize_looptheloop_path_template_pair(this + 17216364, 6.0, 2, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17216388) = 0;
  *(_DWORD *)(this + 17216384) = 0;
  *(_DWORD *)(this + 17216380) = 0;
  v206 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216532), (int)v206);
  mirror_path_template_pair_x(this + 17216532, this + 17216364);
  *(_DWORD *)(this + 17216556) = 0;
  *(_DWORD *)(this + 17216552) = 0;
  *(_DWORD *)(this + 17216548) = 0;
  build_track_fringe_mesh(this + 17216364, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216484) = 0;
  *(_DWORD *)(this + 17216480) = 0;
  *(_DWORD *)(this + 17216476) = 0;
  build_track_fringe_mesh(this + 17216532, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216652) = 0;
  *(_DWORD *)(this + 17216648) = 0;
  *(_DWORD *)(this + 17216644) = 0;
  v207 = *(_DWORD *)(this + 17199264);
  v208 = *(_DWORD *)(this + 17216568);
  *(_DWORD *)(this + 17199388) = *(_DWORD *)(this + 17216400);
  *(_DWORD *)(this + 17199560) = *(_DWORD *)(this + 17199432);
  *(_DWORD *)(this + 17199392) = v207;
  *(_DWORD *)(this + 17199556) = v208;
  v209 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216700), (int)v209);
  initialize_looptheloop_path_template_pair(this + 17216700, 8.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17216724) = 0;
  *(_DWORD *)(this + 17216720) = 0;
  *(_DWORD *)(this + 17216716) = 0;
  v210 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17216868), (int)v210);
  mirror_path_template_pair_x(this + 17216868, this + 17216700);
  *(_DWORD *)(this + 17216892) = 0;
  *(_DWORD *)(this + 17216888) = 0;
  *(_DWORD *)(this + 17216884) = 0;
  build_track_fringe_mesh(this + 17216700, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216820) = 0;
  *(_DWORD *)(this + 17216816) = 0;
  *(_DWORD *)(this + 17216812) = 0;
  build_track_fringe_mesh(this + 17216868, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17216988) = 0;
  *(_DWORD *)(this + 17216984) = 0;
  *(_DWORD *)(this + 17216980) = 0;
  v211 = *(_DWORD *)(this + 17199600);
  v212 = *(_DWORD *)(this + 17216904);
  *(_DWORD *)(this + 17199724) = *(_DWORD *)(this + 17216736);
  *(_DWORD *)(this + 17199728) = v211;
  *(_DWORD *)(this + 17199892) = v212;
  *(_DWORD *)(this + 17199896) = *(_DWORD *)(this + 17199768);
  v213 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218044), (int)v213);
  initialize_looptheloopw_path_template_pair(this + 17218044, 8.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17218068) = 0;
  *(_DWORD *)(this + 17218064) = 0;
  *(_DWORD *)(this + 17218060) = 0;
  v214 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218212), (int)v214);
  mirror_path_template_pair_x(this + 17218212, this + 17218044);
  *(_DWORD *)(this + 17218236) = 0;
  *(_DWORD *)(this + 17218232) = 0;
  *(_DWORD *)(this + 17218228) = 0;
  build_track_fringe_mesh(this + 17218044, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17218164) = 0;
  *(_DWORD *)(this + 17218160) = 0;
  *(_DWORD *)(this + 17218156) = 0;
  build_track_fringe_mesh(this + 17218212, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17218332) = 0;
  *(_DWORD *)(this + 17218328) = 0;
  *(_DWORD *)(this + 17218324) = 0;
  *(_DWORD *)(this + 17201068) = *(_DWORD *)(this + 17218080);
  *(_DWORD *)(this + 17201072) = *(_DWORD *)(this + 17200944);
  *(_DWORD *)(this + 17201236) = *(_DWORD *)(this + 17218248);
  *(_DWORD *)(this + 17201240) = *(_DWORD *)(this + 17201112);
  v215 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217036), (int)v215);
  initialize_looptheloop_path_template_pair(this + 17217036, 3.0, 2, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17217060) = 0;
  *(_DWORD *)(this + 17217056) = 0;
  *(_DWORD *)(this + 17217052) = 0;
  v216 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217204), (int)v216);
  mirror_path_template_pair_x(this + 17217204, this + 17217036);
  *(_DWORD *)(this + 17217228) = 0;
  *(_DWORD *)(this + 17217224) = 0;
  *(_DWORD *)(this + 17217220) = 0;
  build_track_fringe_mesh(this + 17217036, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217156) = 0;
  *(_DWORD *)(this + 17217152) = 0;
  *(_DWORD *)(this + 17217148) = 0;
  build_track_fringe_mesh(this + 17217204, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217324) = 0;
  *(_DWORD *)(this + 17217320) = 0;
  *(_DWORD *)(this + 17217316) = 0;
  *(_DWORD *)(this + 17200060) = *(_DWORD *)(this + 17217072);
  *(_DWORD *)(this + 17200064) = *(_DWORD *)(this + 17199936);
  *(_DWORD *)(this + 17200228) = *(_DWORD *)(this + 17217240);
  *(_DWORD *)(this + 17200232) = *(_DWORD *)(this + 17200104);
  v217 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217372), (int)v217);
  initialize_looptheloop_path_template_pair(this + 17217372, 3.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17217396) = 0;
  *(_DWORD *)(this + 17217392) = 0;
  *(_DWORD *)(this + 17217388) = 0;
  v218 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217540), (int)v218);
  mirror_path_template_pair_x(this + 17217540, this + 17217372);
  *(_DWORD *)(this + 17217564) = 0;
  *(_DWORD *)(this + 17217560) = 0;
  *(_DWORD *)(this + 17217556) = 0;
  build_track_fringe_mesh(this + 17217372, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217492) = 0;
  *(_DWORD *)(this + 17217488) = 0;
  *(_DWORD *)(this + 17217484) = 0;
  build_track_fringe_mesh(this + 17217540, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217660) = 0;
  *(_DWORD *)(this + 17217656) = 0;
  *(_DWORD *)(this + 17217652) = 0;
  *(_DWORD *)(this + 17200396) = *(_DWORD *)(this + 17217408);
  *(_DWORD *)(this + 17200400) = *(_DWORD *)(this + 17200272);
  *(_DWORD *)(this + 17200564) = *(_DWORD *)(this + 17217576);
  *(_DWORD *)(this + 17200568) = *(_DWORD *)(this + 17200440);
  v219 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217708), (int)v219);
  initialize_looptheloop_path_template_pair(this + 17217708, 3.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17217732) = 0;
  *(_DWORD *)(this + 17217728) = 0;
  *(_DWORD *)(this + 17217724) = 0;
  v220 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17217876), (int)v220);
  mirror_path_template_pair_x(this + 17217876, this + 17217708);
  *(_DWORD *)(this + 17217900) = 0;
  *(_DWORD *)(this + 17217896) = 0;
  *(_DWORD *)(this + 17217892) = 0;
  build_track_fringe_mesh(this + 17217708, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217828) = 0;
  *(_DWORD *)(this + 17217824) = 0;
  *(_DWORD *)(this + 17217820) = 0;
  build_track_fringe_mesh(this + 17217876, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17217996) = 0;
  *(_DWORD *)(this + 17217992) = 0;
  *(_DWORD *)(this + 17217988) = 0;
  *(_DWORD *)(this + 17200732) = *(_DWORD *)(this + 17217744);
  *(_DWORD *)(this + 17200736) = *(_DWORD *)(this + 17200608);
  *(_DWORD *)(this + 17200900) = *(_DWORD *)(this + 17217912);
  *(_DWORD *)(this + 17200904) = *(_DWORD *)(this + 17200776);
  v221 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218380), (int)v221);
  initialize_loopbow_path_template_pair(this + 17218380, 6.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17218404) = 0;
  *(_DWORD *)(this + 17218400) = 0;
  *(_DWORD *)(this + 17218396) = 0;
  v222 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218548), (int)v222);
  mirror_path_template_pair_x(this + 17218548, this + 17218380);
  *(_DWORD *)(this + 17218572) = 0;
  *(_DWORD *)(this + 17218568) = 0;
  *(_DWORD *)(this + 17218564) = 0;
  build_track_fringe_mesh(this + 17218380, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17218500) = 0;
  *(_DWORD *)(this + 17218496) = 0;
  *(_DWORD *)(this + 17218492) = 0;
  build_track_fringe_mesh(this + 17218548, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17218668) = 0;
  *(_DWORD *)(this + 17218664) = 0;
  *(_DWORD *)(this + 17218660) = 0;
  *(_DWORD *)(this + 17201404) = *(_DWORD *)(this + 17218416);
  *(_DWORD *)(this + 17201408) = *(_DWORD *)(this + 17201280);
  *(_DWORD *)(this + 17201572) = *(_DWORD *)(this + 17218584);
  *(_DWORD *)(this + 17201576) = *(_DWORD *)(this + 17201448);
  v223 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219724), (int)v223);
  initialize_invert_path_template_pair(
    this + 17219724,
    1086324736,
    COERCE_FLOAT(8),
    1,
    texture_a,
    texture_b,
    (int)aObjectsPathVer);
  *(_DWORD *)(this + 17219748) = 0;
  *(_DWORD *)(this + 17219744) = 0;
  *(_DWORD *)(this + 17219740) = 0;
  v224 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219892), (int)v224);
  mirror_path_template_pair_x(this + 17219892, this + 17219724);
  *(_DWORD *)(this + 17219916) = 0;
  *(_DWORD *)(this + 17219912) = 0;
  *(_DWORD *)(this + 17219908) = 0;
  build_track_fringe_mesh(this + 17219724, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17219844) = 0;
  *(_DWORD *)(this + 17219840) = 0;
  *(_DWORD *)(this + 17219836) = 0;
  build_track_fringe_mesh(this + 17219892, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17220012) = 0;
  *(_DWORD *)(this + 17220008) = 0;
  *(_DWORD *)(this + 17220004) = 0;
  *(_DWORD *)(this + 17212828) = *(_DWORD *)(this + 17219760);
  *(_DWORD *)(this + 17212832) = *(_DWORD *)(this + 17212704);
  *(_DWORD *)(this + 17212996) = *(_DWORD *)(this + 17219928);
  *(_DWORD *)(this + 17213000) = *(_DWORD *)(this + 17212872);
  v225 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218716), (int)v225);
  initialize_loopout_path_template_pair(this + 17218716, 3.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17218740) = 0;
  *(_DWORD *)(this + 17218736) = 0;
  *(_DWORD *)(this + 17218732) = 0;
  v226 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17218884), (int)v226);
  mirror_path_template_pair_x(this + 17218884, this + 17218716);
  *(_DWORD *)(this + 17218908) = 0;
  *(_DWORD *)(this + 17218904) = 0;
  *(_DWORD *)(this + 17218900) = 0;
  build_track_fringe_mesh(this + 17218716, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17218836) = 0;
  *(_DWORD *)(this + 17218832) = 0;
  *(_DWORD *)(this + 17218828) = 0;
  build_track_fringe_mesh(this + 17218884, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17219004) = 0;
  *(_DWORD *)(this + 17219000) = 0;
  *(_DWORD *)(this + 17218996) = 0;
  *(_DWORD *)(this + 17207452) = *(_DWORD *)(this + 17218752);
  *(_DWORD *)(this + 17207456) = *(_DWORD *)(this + 17207328);
  *(_DWORD *)(this + 17207620) = *(_DWORD *)(this + 17218920);
  *(_DWORD *)(this + 17207624) = *(_DWORD *)(this + 17207496);
  v227 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219388), (int)v227);
  initialize_loopout_path_template_pair(this + 17219388, 5.0, 4, 1, texture_a, texture_b, (int)aObjectsPathVer);
  *(_DWORD *)(this + 17219412) = 0;
  *(_DWORD *)(this + 17219408) = 0;
  *(_DWORD *)(this + 17219404) = 0;
  v228 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219556), (int)v228);
  mirror_path_template_pair_x(this + 17219556, this + 17219388);
  *(_DWORD *)(this + 17219580) = 0;
  *(_DWORD *)(this + 17219576) = 0;
  *(_DWORD *)(this + 17219572) = 0;
  build_track_fringe_mesh(this + 17219388, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17219508) = 0;
  *(_DWORD *)(this + 17219504) = 0;
  *(_DWORD *)(this + 17219500) = 0;
  build_track_fringe_mesh(this + 17219556, aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17219676) = 0;
  *(_DWORD *)(this + 17219672) = 0;
  *(_DWORD *)(this + 17219668) = 0;
  *(_DWORD *)(this + 17208124) = *(_DWORD *)(this + 17219424);
  *(_DWORD *)(this + 17208128) = *(_DWORD *)(this + 17208000);
  *(_DWORD *)(this + 17208292) = *(_DWORD *)(this + 17219592);
  *(_DWORD *)(this + 17208296) = *(_DWORD *)(this + 17208168);
  v229 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219052), (int)v229);
  initialize_loopout_path_template_pair(this + 17219052, 3.0, 3, 1, texture_a, texture_b, (int)aObjectsPathVer);
  initialize_distort((_DWORD *)(this + 17219068));
  v230 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17219220), (int)v230);
  mirror_path_template_pair_x(this + 17219220, this + 17219052);
  initialize_distort((_DWORD *)(this + 17219236));
  build_track_fringe_mesh(this + 17219052, aObjectsUnivers_1, 0.0);
  initialize_distort((_DWORD *)(this + 17219164));
  build_track_fringe_mesh(this + 17219220, aObjectsUnivers_1, 0.0);
  initialize_distort((_DWORD *)(this + 17219332));
  *(_DWORD *)(this + 17207788) = *(_DWORD *)(this + 17219088);
  *(_DWORD *)(this + 17207792) = *(_DWORD *)(this + 17207664);
  *(_DWORD *)(this + 17207956) = *(_DWORD *)(this + 17219256);
  *(_DWORD *)(this + 17207960) = *(_DWORD *)(this + 17207832);
  sub_449C00();
  v231 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_43284A + this + 2, (int)v231);
  v232 = find_case_insensitive_substring(aTest, *(char **)(this + 298496));
  if ( v232 )
  {
    v233 = find_case_insensitive_substring(asc_4A1644, v232);
    v234 = v233[1];
    v235 = v233 + 1;
    v236 = ArgList;
    if ( v234 != 46 )
    {
      v237 = v235 - ArgList;
      do
      {
        *v236 = v234;
        v234 = (v236++)[v237 + 1];
      }
      while ( v234 != 46 );
    }
    *v236 = 46;
    v238 = v236 + 1;
    *v238 = 120;
    v238[1] = 0;
  }
  else
  {
    rstrcpy_checked_ascii(ArgList, aTurboBase000X);
  }
  load_x_animation_clip(this + 298496, ArgList, *(int **)((char *)&loc_432870 + this));
  v239 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4326FF + this + 1, (int)v239);
  load_x_animation_clip(this + 298496, ArgList, *(int **)((char *)&loc_432720 + this + 4));
  v240 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4328C8 + this + 4, (int)v240);
  load_x_animation_clip(this + 298496, aTurboMove000X, *(int **)((char *)&loc_4328F0 + this));
  v241 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_43294C + this, (int)v241);
  load_x_animation_clip(this + 298496, aTurboBobalong0, *(int **)((char *)&loc_432970 + this));
  v242 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4329CC + this, (int)v242);
  load_x_animation_clip(this + 298496, aTurboLookbackl, *(int **)((char *)&loc_4329EE + this + 2));
  v243 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432A4A + this + 2, (int)v243);
  load_x_animation_clip(this + 298496, aTurboLookbackr, *(int **)((char *)&loc_432A6D + this + 3));
  v244 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432ACB + this + 1, (int)v244);
  load_x_animation_clip(this + 298496, aTurboFall000X, *(int **)((char *)&loc_432AEF + this + 1));
  v245 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432B49 + this + 3, (int)v245);
  load_x_animation_clip(this + 298496, aTurboDamaged00, *(int **)((char *)&loc_432B6E + this + 2));
  v246 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432BCA + this + 2, (int)v246);
  load_x_animation_clip(this + 298496, aTurboIntoshell, *(int **)((char *)&loc_432BEF + this + 1));
  v247 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432C48 + this + 4, (int)v247);
  load_x_animation_clip(this + 298496, aTurboSkidstop0, *(int **)((char *)&loc_432C6D + this + 3));
  v248 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432CCA + this + 2, (int)v248);
  load_x_animation_clip(this + 298496, aTurboTalk000X, *(int **)((char *)&loc_432CE9 + this + 7));
  v249 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433D46 + this + 6, (int)v249);
  load_x_mesh(aTurbohotspotsX, *(int **)((char *)&loc_433D6F + this + 1), 2);
  build_snail_hotspots((int)&loc_4326FF + this + 1);
  v320 = 10;
  v308 = (_DWORD **)((char *)&loc_432870 + this);
  do
  {
    (*v308)[4] |= 4u;
    apply_object_toon(*v308, 0);
    v250 = (int)*v308;
    v308 += 32;
    *(_DWORD *)(v250 + 128) = 0;
    (*(v308 - 32))[33] = 0;
    v56 = v320 == 1;
    (*(v308 - 32))[34] = 0;
    --v320;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 16) |= 4u;
  apply_object_toon(*(_DWORD **)((char *)&loc_432720 + this + 4), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 136) = 0;
  v251 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4338DE + this + 2, (int)v251);
  load_x_animation_clip(this + 298496, aJetpackBase000, *(int **)((char *)&loc_433902 + this + 2));
  v252 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433A2C + this + 4, (int)v252);
  load_x_animation_clip(this + 298496, aJetpackBase000, *(int **)((char *)&loc_433A54 + this));
  v253 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433AB0 + this, (int)v253);
  load_x_animation_clip(this + 298496, aJetpackDraw000, *(int **)((char *)&loc_433AD4 + this));
  v321 = 2;
  v309 = (_DWORD **)((char *)&loc_433A54 + this);
  do
  {
    (*v309)[4] |= 4u;
    apply_object_toon(*v309, 0);
    v254 = (int)*v309;
    v309 += 32;
    *(_DWORD *)(v254 + 128) = 0;
    (*(v309 - 32))[33] = 0;
    v56 = v321 == 1;
    (*(v309 - 32))[34] = 0;
    --v321;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 16) |= 4u;
  apply_object_toon(*(_DWORD **)((char *)&loc_433902 + this + 2), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 136) = 0;
  v255 = add_object_to_list(unk_4B7648);
  set_bod_object(&byte_432D4C[this], (int)v255);
  load_x_animation_clip(this + 298496, aBlasterleftBas, *(int **)((char *)&loc_432D6D + this + 3));
  v256 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432E9A + this + 2, (int)v256);
  load_x_animation_clip(this + 298496, aBlasterleftBas, *(int **)((char *)&loc_432EBF + this + 1));
  v257 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432F1A + this + 2, (int)v257);
  load_x_animation_clip(this + 298496, aBlasterleftDra, *(int **)((char *)&loc_432F40 + this));
  v258 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_432F9B + this + 1, (int)v258);
  load_x_animation_clip(this + 298496, aBlasterleftFir, *(int **)((char *)sub_432FC0 + this));
  v259 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_43301C + this, (int)v259);
  load_x_animation_clip(this + 298496, aLaserleftBase0, *(int **)((char *)sub_433040 + this));
  v260 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_43309C + this, (int)v260);
  load_x_animation_clip(this + 298496, aLaserleftDraw0, *(int **)((char *)&loc_4330BF + this + 1));
  v322 = 5;
  v310 = (_DWORD **)((char *)&loc_432EBF + this + 1);
  do
  {
    (*v310)[4] |= 4u;
    apply_object_toon(*v310, 0);
    v261 = (int)*v310;
    v310 += 32;
    *(_DWORD *)(v261 + 128) = 0;
    (*(v310 - 32))[33] = 0;
    v56 = v322 == 1;
    (*(v310 - 32))[34] = 0;
    --v322;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 16) |= 4u;
  apply_object_toon(*(_DWORD **)((char *)&loc_432D6D + this + 3), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 136) = 0;
  v262 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433127 + this + 1, (int)v262);
  load_x_animation_clip(this + 298496, aBlasterrightBa, *(int **)((char *)&loc_43314C + this));
  v263 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433275 + this + 3, (int)v263);
  load_x_animation_clip(this + 298496, aBlasterrightBa, *(int **)((char *)&loc_43329B + this + 1));
  v264 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4332F7 + this + 1, (int)v264);
  load_x_animation_clip(this + 298496, aBlasterrightDr, *(int **)((char *)&loc_43331C + this));
  v265 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433378 + this, (int)v265);
  load_x_animation_clip(this + 298496, aBlasterrightFi, *(int **)((char *)&loc_43339A + this + 2));
  v266 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4333F8 + this, (int)v266);
  load_x_animation_clip(this + 298496, aLaserrightBase, *(int **)((char *)&loc_433417 + this + 5));
  v267 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433475 + this + 3, (int)v267);
  load_x_animation_clip(this + 298496, aLaserrightDraw, *(int **)((char *)&loc_433499 + this + 3));
  v323 = 5;
  v311 = (_DWORD **)((char *)&loc_43329B + this + 1);
  do
  {
    (*v311)[4] |= 4u;
    apply_object_toon(*v311, 0);
    v268 = (int)*v311;
    v311 += 32;
    *(_DWORD *)(v268 + 128) = 0;
    (*(v311 - 32))[33] = 0;
    v56 = v323 == 1;
    (*(v311 - 32))[34] = 0;
    --v323;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 16) |= 4u;
  apply_object_toon(*(_DWORD **)((char *)&loc_43314C + this), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 136) = 0;
  v269 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433504 + this, (int)v269);
  load_x_animation_clip(this + 298496, aBlastertopBase, *(int **)((char *)&loc_433523 + this + 5));
  v270 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433654 + this, (int)v270);
  load_x_animation_clip(this + 298496, aBlastertopBase, *(int **)((char *)&loc_433677 + this + 1));
  v271 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4336D0 + this + 4, (int)v271);
  load_x_animation_clip(this + 298496, aBlastertopDraw, *(int **)((char *)&loc_4336F6 + this + 2));
  v272 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433751 + this + 3, (int)v272);
  load_x_animation_clip(this + 298496, aBlastertopFire, *(int **)((char *)&loc_433777 + this + 1));
  v273 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4337D3 + this + 1, (int)v273);
  load_x_animation_clip(this + 298496, aRocketlauncher, *(int **)((char *)&loc_4337F6 + this + 2));
  v274 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433853 + this + 1, (int)v274);
  load_x_animation_clip(this + 298496, aRocketlauncher_0, *(int **)((char *)&loc_433877 + this + 1));
  v324 = 5;
  v312 = (_DWORD **)((char *)&loc_433677 + this + 1);
  do
  {
    (*v312)[4] |= 4u;
    apply_object_toon(*v312, 0);
    v275 = (int)*v312;
    v312 += 32;
    *(_DWORD *)(v275 + 128) = 0;
    (*(v312 - 32))[33] = 0;
    v56 = v324 == 1;
    (*(v312 - 32))[34] = 0;
    --v324;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 16) |= 4u;
  apply_object_toon(*(_DWORD **)((char *)&loc_433523 + this + 5), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 136) = 0;
  *(_DWORD *)((char *)&loc_434037 + this + 5) = get_or_create_texture_ref(&texture_list, aXSnailTurboTga_0, 0, 0);
  *(_DWORD *)((char *)&loc_43403D + this + 3) = get_or_create_texture_ref(&texture_list, aXSnailTurboDam, 0, 0);
  *(_DWORD *)((char *)&loc_434042 + this + 2) = get_or_create_texture_ref(&texture_list, aXSnailTurboInv, 0, 0);
  v276 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_433F94 + this, (int)v276);
  load_x_mesh(aInvincibleBase, *(int **)((char *)&loc_433FB8 + this), 1);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433FB8 + this) + 16) &= ~0x100000u;
  v277 = add_object_to_list(unk_4B7648);
  set_bod_object((char *)&loc_4302E3 + this + 1, (int)v277);
  load_x_mesh(aRocketBase000X, *(int **)((char *)&loc_430306 + this + 2), 1);
  v278 = (char *)&loc_43026E + this + 2;
  v325 = 12;
  do
  {
    v279 = add_object_to_list(unk_4B7648);
    set_bod_object((_DWORD *)v278 - 9, (int)v279);
    *(_DWORD *)(*(_DWORD *)v278 + 16) |= 0x100004u;
    *(_DWORD *)(*(_DWORD *)v278 + 20) = 9;
    load_object_definition(aObjectsVapourl, *(int **)v278);
    initialize_vapour((_DWORD *)v278 - 9, *(_DWORD *)v278, 1042536202);
    set_bod_object((_DWORD *)v278 + 29, *(_DWORD *)((char *)&loc_430306 + this + 2));
    v278 += 744;
    --v325;
  }
  while ( v325 );
  v280 = (int *)get_or_create_texture_ref(&texture_list, aObjectsVapourl_0, 0, 0);
  v281 = *v280;
  BYTE1(v281) = BYTE1(*v280) | 4;
  *v280 = v281;
  v282 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_4, 0, 0);
  *v282 |= 0x1403u;
  v283 = (_DWORD *)get_or_create_texture_ref(&texture_list, texture_b, 0, 0);
  *v283 |= 0x1402u;
  *(_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_0, 0, 0) = 4096;
  v284 = (int *)get_or_create_texture_ref(&texture_list, aObjectsUnivers, 0, 0);
  v285 = *v284;
  BYTE1(v285) = BYTE1(*v284) | 0x10;
  *v284 = v285;
  v286 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00, 0, 0);
  *v286 |= 0x1002u;
  v287 = (_DWORD *)get_or_create_texture_ref(&texture_list, texture_a, 0, 0);
  *v287 |= 0x1002u;
  v288 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_5, 0, 0);
  *v288 |= 0x1002u;
  v289 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_6, 0, 0);
  *v289 |= 0x1002u;
  v290 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_7, 0, 0);
  *v290 |= 0x1002u;
  v291 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_8, 0, 0);
  *v291 |= 0x1002u;
  v292 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_9, 0, 0);
  *v292 |= 0x1002u;
  v293 = (_DWORD *)get_or_create_texture_ref(&texture_list, aObjectsWorld00_10, 0, 0);
  *v293 |= 0x1002u;
  *(_DWORD *)(this + 2852) = get_or_create_texture_ref(&texture_list, aObjectsWorld00, 0, 0);
  *(_DWORD *)(this + 2868) = get_or_create_texture_ref(&texture_list, texture_a, 0, 0);
  *(_DWORD *)(this + 2856) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_5, 0, 0);
  *(_DWORD *)(this + 2872) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_6, 0, 0);
  *(_DWORD *)(this + 2860) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_7, 0, 0);
  *(_DWORD *)(this + 2876) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_8, 0, 0);
  *(_DWORD *)(this + 2864) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_9, 0, 0);
  *(_DWORD *)(this + 2880) = get_or_create_texture_ref(&texture_list, aObjectsWorld00_10, 0, 0);
  *(_DWORD *)(this + 2884) = 0;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, texture_b, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_0, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsUnivers, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, texture_a, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_5, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_6, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_7, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_8, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_9, 0, 0) + 160) = 2;
  *(_DWORD *)(get_or_create_texture_ref(&texture_list, aObjectsWorld00_10, 0, 0) + 160) = 2;
  v294 = add_object_to_list(unk_4B7648);
  set_bod_object((_DWORD *)(this + 17220060), (int)v294);
  load_object_definition(aObjectsBarrier, *(int **)(this + 17220096));
  initialize_distort((_DWORD *)(this + 17220076));
  store_color4f((_DWORD *)(this + 17220100), 1065353216, 1065353216, 1065353216, 1061997773);
  *(_DWORD *)(*(_DWORD *)(this + 17220096) + 20) = 7;
  initialize_track_render_cache_manager((_DWORD *)(this + 476788));
  v326 = 0;
  v295 = (int **)(this + 282068);
  do
  {
    for ( j = 0; j < 4; ++j )
    {
      v313 = 0;
      v296 = v295;
      do
      {
        for ( k = 0; k < 3; ++k )
        {
          v298 = add_object_to_list(unk_4B7648);
          set_bod_object(v296 - 9, (int)v298);
          initialize_backdrop_tile_quad(*v296, v326, j, v313 - 1, k - 1, aObjectsUnivers_1);
          v299 = *v296;
          v296 += 14;
          v299[5] = 5;
        }
        ++v313;
      }
      while ( v313 < 3 );
      v295 = v296;
    }
    ++v326;
  }
  while ( v326 < 8 );
  v300 = (int *)get_or_create_texture_ref(&texture_list, aObjectsUnivers_1, 0, 0);
  v301 = *v300;
  v302 = (int *)(this + 124);
  BYTE1(v301) = BYTE1(*v300) | 4;
  v303 = 0;
  *v300 = v301;
  do
  {
    sub_4113B0((_DWORD *)(this + 1448), (int)(v302 - 14));
    *v302 = v303;
    initialize_input(v302);
    ++v303;
    v302 += 28;
  }
  while ( v303 < 2 );
  for ( m = 0; m < *(_DWORD *)(this + 64); ++m )
  {
    v327 = this + 504 * m;
    set_matrix_identity((_DWORD *)(v327 + 348));
    set_matrix_identity((_DWORD *)(v327 + 508));
    *(_DWORD *)(v327 + 644) = 1121714176;
    *(_DWORD *)(v327 + 652) = 112 * m + this + 68;
    qmemcpy(
      (void *)(v327 + 348),
      initialize_matrix_from_values(
        v334,
        1033254107,
        0,
        -1082175546,
        0,
        1042008055,
        1065156872,
        1010257376,
        0,
        1065112278,
        -1105448078,
        1033138814,
        0,
        -1056307500,
        1078412299,
        1083131627,
        1065353216),
      0x40u);
    initialize_frontend_overlay_color_lerp((_DWORD *)(v327 + 680), 0x1000000);
    release_mouse_cursor((_DWORD *)(v327 + 656));
    *(_BYTE *)(v327 + 676) = 0;
    if ( !m )
      *(_DWORD *)(this + 440) = 12;
    *(_BYTE *)(v327 + 781) = 0;
    *(_DWORD *)(v327 + 784) = 0;
    rstrcpy_checked_ascii((char *)(v327 + 420), &unk_4DF978);
  }
  initialize_high_score_tables((char *)&byte_6FFAE0 + this);
  load_high_scores_from_file((char *)&byte_6FFAE0 + this, aScoreaDat);
  load_high_scores_from_file((char *)&byte_6FFAE0 + this, aScorebDat);
  load_high_scores_from_file((char *)&byte_6FFAE0 + this, aScorecDat);
  *(_BYTE *)(this + 17198057) = 0;
  *(_BYTE *)(this + 17198056) = 0;
  initialize_tip_manager((_DWORD *)(this + 19820376));
  sub_4113B0((_DWORD *)(this + 1448), this + 19820376);
  sub_4113B0((_DWORD *)MEMORY[0x4DF904] + 362, this + 324412);
  open_star_field((_DWORD *)(this + 324412), 36);
  *(_DWORD *)(this + 3998116) = 0;
  *(_DWORD *)(this + 3998112) = 0;
  sub_4113B0((_DWORD *)(this + 1448), this + 322576);
  *(_DWORD *)(this + 324200) = 0;
  sub_411420((_DWORD *)(this + 1448), (_DWORD *)(this + 2892));
  Concurrency::details::StructuredWorkStealingQueue<Concurrency::details::_UnrealizedChore,Concurrency::details::_CriticalNonReentrantLock>::Reinitialize(this + 2948);
  *(_DWORD *)(this + 4556) = this + 2892;
  *(_BYTE *)(this + 278764) = 0;
  set_border_justify_centre((_DWORD *)(this + 2892), 1103626240);
  v304 = (_DWORD *)(this + 4976);
  v305 = 150;
  do
  {
    *v304 = 0;
    v304 += 457;
    --v305;
  }
  while ( v305 );
  build_all_objects(unk_4B7648, this + 1448, v22);
  set_object_color(*(_DWORD **)(this + 17216064));
  set_object_color(*(_DWORD **)(this + 17216232));
  set_object_color(*(_DWORD **)(this + 17216400));
  set_object_color(*(_DWORD **)(this + 17216568));
  set_object_color(*(_DWORD **)(this + 17216736));
  set_object_color(*(_DWORD **)(this + 17216904));
  set_object_color(*(_DWORD **)(this + 17218080));
  set_object_color(*(_DWORD **)(this + 17218248));
  set_object_color(*(_DWORD **)(this + 17217072));
  set_object_color(*(_DWORD **)(this + 17217240));
  set_object_color(*(_DWORD **)(this + 17217408));
  set_object_color(*(_DWORD **)(this + 17217576));
  set_object_color(*(_DWORD **)(this + 17217744));
  set_object_color(*(_DWORD **)(this + 17217912));
  set_object_color(*(_DWORD **)(this + 17218416));
  set_object_color(*(_DWORD **)(this + 17218584));
  set_object_color(*(_DWORD **)(this + 17219760));
  set_object_color(*(_DWORD **)(this + 17219928));
  set_object_color(*(_DWORD **)(this + 17218752));
  set_object_color(*(_DWORD **)(this + 17218920));
  set_object_color(*(_DWORD **)(this + 17219424));
  set_object_color(*(_DWORD **)(this + 17219592));
  set_object_color(*(_DWORD **)(this + 17219088));
  set_object_color(*(_DWORD **)(this + 17219256), v328[0], v328[1], v328[2], v328[3]);
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  *(_DWORD *)(this + 19813856) = 2;
  return 1;
}
