/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_assets_and_world @ 0x40acf0 */
/* selector: initialize_game_assets_and_world */

// Bootstraps the shared app world, front-end managers, score tables, star field, and the embedded 63-pair path-template bank. Public Path= slots 0..50 are constructed in place at GameRoot+0x1066f2c; slots 51..62 own transition meshes for flagged loop/invert families, HALFPIPE is the direct slot-42 constructor call, and WARP slot 30 remains unbuilt.
char __thiscall initialize_game_assets_and_world(int this)
{
  FrameBodBase *v2; // eax
  int *v3; // edx
  FrameBodBase **p_first; // ecx
  FrameBodBase *first; // edi
  FrameBodBase *list_prev; // eax
  int v7; // eax
  FrameBodBase *v8; // eax
  int v9; // edx
  FrameBodBase **v10; // ecx
  FrameBodBase *v11; // edx
  FrameBodBase *v12; // eax
  int v13; // ecx
  FrameBodBase *v14; // ecx
  int v15; // edx
  FrameBodBase **v16; // eax
  FrameBodBase *v17; // edx
  FrameBodBase *v18; // ecx
  int v19; // ecx
  int v20; // edi
  Object *v21; // eax
  Object *v22; // eax
  Object *v23; // eax
  double v24; // st7
  Object *v25; // eax
  Object *v26; // eax
  Object *v27; // eax
  Object *v28; // eax
  Object *v29; // eax
  Object *v30; // eax
  Object *v31; // eax
  Object *v32; // eax
  Object *v33; // eax
  Object *v34; // eax
  Object *v35; // eax
  Object *v36; // eax
  Object *v37; // eax
  Object *v38; // eax
  Object *v39; // eax
  Object *v40; // eax
  Object *v41; // eax
  Object *v42; // eax
  Object *v43; // eax
  Object *v44; // eax
  Object *v45; // eax
  Object *v46; // eax
  Object *v47; // eax
  Object *v48; // eax
  _DWORD *v49; // eax
  Object *v50; // eax
  int *v51; // eax
  int v52; // ecx
  Object *v53; // eax
  int *v54; // edi
  int v55; // edx
  int v56; // eax
  int *v57; // eax
  int v58; // ecx
  int v59; // ecx
  bool v60; // zf
  int v61; // eax
  Object *v62; // eax
  tColour *v63; // edi
  int i; // edi
  Object *v65; // eax
  int v66; // ecx
  int v67; // edx
  _DWORD *v68; // eax
  int v69; // edi
  int v70; // ecx
  int v71; // eax
  int v72; // ecx
  int v73; // eax
  int v74; // eax
  int *v75; // ecx
  int v76; // edx
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
  int v98; // eax
  int *v99; // edx
  int v100; // ecx
  int v101; // eax
  int v102; // eax
  int *v103; // edx
  int v104; // ecx
  int v105; // eax
  Object *v106; // eax
  Object *v107; // eax
  Object *v108; // eax
  Object *v109; // eax
  Object *v110; // eax
  Object *v111; // eax
  Object *v112; // eax
  Object *v113; // eax
  Object *v114; // eax
  Object *v115; // eax
  Object *v116; // eax
  Object *v117; // eax
  Object *v118; // eax
  Object *v119; // eax
  Object *v120; // eax
  Object *v121; // eax
  Object *v122; // eax
  Object *v123; // eax
  Object *v124; // eax
  Object *v125; // eax
  Object *v126; // eax
  Object *v127; // eax
  Object *v128; // eax
  Object *v129; // eax
  Object *v130; // eax
  Object *v131; // eax
  Object *v132; // eax
  Object *v133; // eax
  Object *v134; // eax
  Object *v135; // eax
  Object *v136; // eax
  Object *v137; // eax
  Object *v138; // eax
  Object *v139; // eax
  Object *v140; // eax
  Object *v141; // eax
  Object *v142; // eax
  Object *v143; // eax
  Object *v144; // eax
  Object *v145; // eax
  Object *v146; // eax
  Object *v147; // eax
  Object *v148; // eax
  Object *v149; // eax
  Object *v150; // eax
  Object *v151; // eax
  Object *v152; // eax
  Object *v153; // eax
  Object *v154; // eax
  Object *v155; // eax
  Object *v156; // eax
  Object *v157; // eax
  Object *v158; // eax
  Object *v159; // eax
  Object *v160; // eax
  Object *v161; // eax
  Object *v162; // eax
  Object *v163; // eax
  Object *v164; // eax
  Object *v165; // eax
  Object *v166; // eax
  Object *v167; // eax
  Object *v168; // eax
  Object *v169; // eax
  Object *v170; // eax
  Object *v171; // eax
  Object *v172; // eax
  Object *v173; // eax
  Object *v174; // eax
  Object *v175; // eax
  Object *v176; // eax
  Object *v177; // eax
  Object *v178; // eax
  Object *v179; // eax
  Object *v180; // eax
  Object *v181; // eax
  Object *v182; // eax
  Object *v183; // eax
  Object *v184; // eax
  Object *v185; // eax
  Object *v186; // eax
  Object *v187; // eax
  Object *v188; // eax
  Object *v189; // eax
  Object *v190; // eax
  Object *v191; // eax
  Object *v192; // eax
  Object *v193; // eax
  Object *v194; // eax
  Object *v195; // eax
  Object *v196; // eax
  Object *v197; // eax
  Object *v198; // eax
  Object *v199; // eax
  Object *v200; // eax
  Object *v201; // eax
  Object *v202; // eax
  Object *v203; // eax
  Object *v204; // eax
  Object *v205; // eax
  Object *v206; // eax
  Object *v207; // eax
  Object *v208; // eax
  Object *v209; // eax
  int v210; // ecx
  int v211; // edx
  int v212; // eax
  Object *v213; // eax
  Object *v214; // eax
  int v215; // edx
  int v216; // eax
  Object *v217; // eax
  Object *v218; // eax
  int v219; // eax
  int v220; // ecx
  Object *v221; // eax
  Object *v222; // eax
  Object *v223; // eax
  Object *v224; // eax
  Object *v225; // eax
  Object *v226; // eax
  Object *v227; // eax
  Object *v228; // eax
  Object *v229; // eax
  Object *v230; // eax
  Object *v231; // eax
  Object *v232; // eax
  Object *v233; // eax
  Object *v234; // eax
  Object *v235; // eax
  Object *v236; // eax
  Object *v237; // eax
  Object *v238; // eax
  int v239; // edx
  Object *v240; // eax
  char *case_insensitive_substring; // eax
  char *v242; // eax
  char v243; // cl
  char *v244; // edx
  char *v245; // eax
  int v246; // edx
  _BYTE *v247; // eax
  Object *v248; // eax
  Object *v249; // eax
  Object *v250; // eax
  Object *v251; // eax
  Object *v252; // eax
  Object *v253; // eax
  Object *v254; // eax
  Object *v255; // eax
  Object *v256; // eax
  Object *v257; // eax
  Object *v258; // eax
  Object **v259; // ecx
  int v260; // ecx
  int v261; // eax
  int v262; // ecx
  int v263; // eax
  int v264; // eax
  Object *v265; // eax
  Object *v266; // eax
  Object *v267; // eax
  Object **v268; // ecx
  int v269; // edx
  int v270; // eax
  int v271; // edx
  int v272; // eax
  int v273; // eax
  Object *v274; // eax
  Object *v275; // eax
  Object *v276; // eax
  Object *v277; // eax
  Object *v278; // eax
  Object *v279; // eax
  Object **v280; // ecx
  int v281; // ecx
  int v282; // eax
  int v283; // ecx
  int v284; // eax
  int v285; // eax
  Object *v286; // eax
  Object *v287; // eax
  Object *v288; // eax
  Object *v289; // eax
  Object *v290; // eax
  Object *v291; // eax
  Object **v292; // ecx
  int v293; // edx
  int v294; // eax
  int v295; // edx
  int v296; // eax
  int v297; // eax
  Object *v298; // eax
  Object *v299; // eax
  Object *v300; // eax
  Object *v301; // eax
  Object *v302; // eax
  Object *v303; // eax
  Object **v304; // ecx
  int v305; // ecx
  int v306; // eax
  int v307; // ecx
  int v308; // eax
  int v309; // eax
  int v310; // edx
  TextureRef *texture_ref; // eax
  TextureRef *v312; // eax
  Object *v313; // eax
  Object *v314; // eax
  char *v315; // esi
  Object *v316; // eax
  TextureRef *v317; // eax
  TextureRefFlags flags; // ecx
  TextureRef *v319; // eax
  TextureRefFlags v320; // ecx
  TextureRef *v321; // eax
  TextureRefFlags v322; // ecx
  TextureRef *v323; // eax
  TextureRef *v324; // eax
  TextureRefFlags v325; // ecx
  TextureRef *v326; // eax
  TextureRefFlags v327; // ecx
  TextureRef *v328; // eax
  TextureRefFlags v329; // ecx
  TextureRef *v330; // eax
  TextureRefFlags v331; // ecx
  TextureRef *v332; // eax
  TextureRefFlags v333; // ecx
  TextureRef *v334; // eax
  TextureRefFlags v335; // ecx
  TextureRef *v336; // eax
  TextureRefFlags v337; // ecx
  TextureRef *v338; // eax
  TextureRefFlags v339; // ecx
  TextureRef *v340; // eax
  TextureRefFlags v341; // ecx
  TextureRef *v342; // eax
  TextureRef *v343; // eax
  TextureRef *v344; // eax
  TextureRef *v345; // eax
  TextureRef *v346; // eax
  TextureRef *v347; // eax
  TextureRef *v348; // eax
  TextureRef *v349; // eax
  TextureRef *v350; // eax
  TextureRef *v351; // eax
  TextureRef *v352; // eax
  TextureRef *v353; // eax
  TextureRef *v354; // eax
  TextureRef *v355; // eax
  TextureRef *v356; // eax
  TextureRef *v357; // eax
  TextureRef *v358; // eax
  TextureRef *v359; // eax
  Object *v360; // eax
  PathTemplateStripMesh **v361; // eax
  PathTemplateStripMesh **v362; // esi
  int j; // edi
  Object *v364; // eax
  PathTemplateStripMesh *v365; // eax
  TextureRef *v366; // eax
  TextureRefFlags v367; // ecx
  InputState *v368; // esi
  int v369; // edi
  int v370; // eax
  int v371; // esi
  int v372; // edx
  int v373; // eax
  int v374; // eax
  int v375; // ecx
  _DWORD *v376; // eax
  int v377; // ecx
  _BYTE v379[92]; // [esp-10h] [ebp-14Ch] BYREF
  int transform_48; // [esp+5Ch] [ebp-E0h]
  char self[16]; // [esp+6Ch] [ebp-D0h] BYREF
  char ArgList[128]; // [esp+7Ch] [ebp-C0h] BYREF
  TransformMatrix v383; // [esp+FCh] [ebp-40h] BYREF

  noop_this_constructor(self);
  store_color4f((tColour *)(this + 20), 1.0, 1.0, 1.0, 1.0);
  *(_DWORD *)(this + 16) = 1065353216;
  *(_DWORD *)(this + 8) = 1106247680;
  *(_DWORD *)(this + 12) = 1112014848;
  *(_BYTE *)(this + 4) = 1;
  *(_DWORD *)(this + 64) = 2;
  initialize_border_stack(this + 36);
  *(_BYTE *)(this + 1384) = 0;
  *(_BYTE *)(this + 476705) = 0;
  initialize_cheat(&g_cheat_state);
  *(_BYTE *)(this + 324320) = 0;
  initialize_blink_random((float *)(this + 476696));
  set_subgame_rate((SubgameRuntime *)(this + 476696), 1.1);
  *(_DWORD *)(this + 1388) = 2;
  *(_DWORD *)&v379[12] = 500;
  *(_DWORD *)(this + 60) = 1;
  initialize_texture_list(&g_texture_refs, *(int *)&v379[12]);
  initialize_object_list(&g_object_list, 3000);
  *(_DWORD *)(this + 1300) = 0;
  *(_DWORD *)(this + 1304) = 0;
  *(_DWORD *)(this + 1308) = 0;
  *(_DWORD *)(this + 1404) = 0;
  *(_DWORD *)(this + 1456) = this + 1392;
  *(_DWORD *)(this + 1452) = 0;
  *(_DWORD *)(this + 2888) = 0;
  memset(g_sprite_depth_buckets, 0, sizeof(g_sprite_depth_buckets));
  *(_DWORD *)(this + 1464) = 0;
  *(_DWORD *)(this + 1468) = 16777219;
  *(_DWORD *)(this + 1492) = this + 1788;
  *(_DWORD *)(this + 1472) = 0;
  *(_DWORD *)(this + 1476) = 0;
  *(_DWORD *)(this + 1480) = 1065353216;
  *(_DWORD *)(this + 1484) = 1065353216;
  *(_BYTE *)(this + 1576) = 0;
  v2 = (FrameBodBase *)(this + 1660);
  v3 = (int *)(this + 1664);
  if ( (*(_DWORD *)(this + 1664) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->bod.list_prev = v2;
      (*p_first)->bod.list_prev->bod.list_next = *p_first;
      list_prev = (*p_first)->bod.list_prev;
      *p_first = list_prev;
      list_prev->bod.list_prev = nullptr;
    }
    else
    {
      *p_first = v2;
      *(_DWORD *)(this + 1668) = 0;
      (*p_first)->bod.list_next = nullptr;
    }
    v7 = *v3;
    BYTE1(v7) = BYTE1(*v3) | 2;
    *v3 = v7;
  }
  initialize_overlay(this + 1660);
  memset(&g_directx_loader_scratch, 0, 0x15Cu);
  initialize_directx_loader((DirectXLoader *)(this + 298496));
  reset_landscape_manager((_DWORD *)(this + 17220120));
  load_segment_definitions((SMTracks *)(this + 17259236));
  load_landscape_script_by_name((char *)(this + 17220120), aStarmapTxt);
  load_landscape_script_by_name((char *)(this + 17220120), aSplashTxt);
  load_landscape_script_by_name((char *)(this + 17220120), g_help_script_path);
  *(_DWORD *)(this + 476764) = g_runtime_config.landscape_backdrop_variant_selector;
  bind_subgame_owner((SubgameOwnerLink *)(this + 19744248));
  bind_subgame_owner((SubgameOwnerLink *)(this + 19744292));
  load_galaxy_layout((char *)(this + 19744312));
  initialize_cameraman((Cameraman *)((char *)&loc_42FF7C + this));
  open_logo((Logo *)(this + 324608));
  initialize_sound_bank(&g_sound_bank_entries);
  initialize_voice_manager(g_voice_manager);
  apply_audio_config_volumes();
  load_level_definitions((SMTracks *)(this + 17259236));
  load_landscape_script_by_name((char *)&g_game_base->subgame.unknown_000044[16743356], g_menu_background_script_path);
  load_builtin_segment_definitions((SubTracks *)(this + 2246660), (SubSegmentRaw **)&g_builtin_segment_definitions);
  *(_DWORD *)(this + 1504) = 1;
  *(_DWORD *)&v379[12] = this + 452;
  *(_DWORD *)(this + 1508) = 33554433;
  attach_render_camera_source((_DWORD *)(this + 1500), *(int *)&v379[12]);
  *(_DWORD *)(this + 648) = 0x2000000;
  *(_DWORD *)&v379[12] = this + 956;
  *(_DWORD *)(this + 1624) = 1;
  *(_DWORD *)(this + 1628) = 268435459;
  attach_render_camera_source((_DWORD *)(this + 1620), *(int *)&v379[12]);
  *(_DWORD *)(this + 1152) = 0x10000000;
  *(_DWORD *)(this + 1584) = 3;
  *(_DWORD *)(this + 1588) = 134217731;
  *(_DWORD *)(this + 1612) = this + 2452;
  *(_DWORD *)(this + 1592) = 0;
  *(_DWORD *)(this + 1596) = 0;
  *(_DWORD *)(this + 1600) = 1065353216;
  *(_DWORD *)(this + 1604) = 1065353216;
  v8 = (FrameBodBase *)(this + 2324);
  v9 = *(_DWORD *)(this + 2328);
  *(_DWORD *)&v379[36] = this + 2328;
  if ( (v9 & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v10 = &g_game_base->active_bod_list.first;
    v11 = g_game_base->active_bod_list.first;
    if ( v11 )
    {
      v11->bod.list_prev = v8;
      (*v10)->bod.list_prev->bod.list_next = *v10;
      v12 = (*v10)->bod.list_prev;
      *v10 = v12;
      v12->bod.list_prev = nullptr;
    }
    else
    {
      *v10 = v8;
      *(_DWORD *)(this + 2332) = 0;
      (*v10)->bod.list_next = nullptr;
    }
    v13 = **(_DWORD **)&v379[36];
    BYTE1(v13) = BYTE1(**(_DWORD **)&v379[36]) | 2;
    **(_DWORD **)&v379[36] = v13;
  }
  initialize_overlay(this + 2324);
  *(_DWORD *)(this + 1544) = 2;
  *(_DWORD *)(this + 1548) = 67108867;
  *(_DWORD *)(this + 1572) = this + 2120;
  *(_DWORD *)(this + 1552) = 0;
  *(_DWORD *)(this + 1556) = 0;
  v14 = (FrameBodBase *)(this + 1992);
  *(_DWORD *)(this + 1560) = 1065353216;
  *(_DWORD *)(this + 1564) = 1065353216;
  v15 = *(_DWORD *)(this + 1996);
  *(_DWORD *)&v379[36] = this + 1996;
  if ( (v15 & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v16 = &g_game_base->active_bod_list.first;
    v17 = g_game_base->active_bod_list.first;
    if ( v17 )
    {
      v17->bod.list_prev = v14;
      (*v16)->bod.list_prev->bod.list_next = *v16;
      v18 = (*v16)->bod.list_prev;
      *v16 = v18;
      v18->bod.list_prev = nullptr;
    }
    else
    {
      *v16 = v14;
      *(_DWORD *)(this + 2000) = 0;
      (*v16)->bod.list_next = nullptr;
    }
    v19 = **(_DWORD **)&v379[36];
    BYTE1(v19) = BYTE1(**(_DWORD **)&v379[36]) | 2;
    **(_DWORD **)&v379[36] = v19;
  }
  initialize_overlay(this + 1992);
  register_font_texture_sheet_wrapper(aObjectsFontFon, 2, 1061158912, 1065353216);
  initialize_font3d_objects(0);
  initialize_font_wave_state();
  initialize_sprite_manager(g_sprite_manager);
  register_sprite_texture((char *)aSpritesDebugTg, 1, 0);
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
  *(_DWORD *)&v379[32] = 0;
  do
  {
    v20 = this + 56 * (__int64)*(float *)&v379[32];
    v21 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 280464), v21);
    initialize_backdrop_slice_quad(*(PathTemplateStripMesh **)(v20 + 280500), aObjectsWorld00, *(float *)&v379[32]);
    v22 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 280912), v22);
    initialize_backdrop_slice_quad(*(PathTemplateStripMesh **)(v20 + 280948), aObjectsWorld00_0, *(float *)&v379[32]);
    v23 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 281360), v23);
    initialize_backdrop_slice_quad(*(PathTemplateStripMesh **)(v20 + 281396), texture_a, *(float *)&v379[32]);
    v24 = *(float *)&v379[32] + 1.0;
    *(float *)&v379[32] = v24;
  }
  while ( v24 < 8.0 );
  set_matrix_identity((TransformMatrix *)&v379[60]);
  v25 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280016), v25);
  load_x_mesh((DirectXLoader *)(this + 298496), mesh_path, *(Object **)(this + 280052), 1);
  transform_48 = 0;
  apply_bod_position((BodBase *)(this + 280016), (TransformMatrix *)&v379[60]);
  v26 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280072), v26);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar2X, *(Object **)(this + 280108), 1);
  transform_48 = 1056964608;
  apply_bod_position((BodBase *)(this + 280072), (TransformMatrix *)&v379[60]);
  v27 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280128), v27);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar3X, *(Object **)(this + 280164), 1);
  transform_48 = 1065353216;
  apply_bod_position((BodBase *)(this + 280128), (TransformMatrix *)&v379[60]);
  v28 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280184), v28);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar4X, *(Object **)(this + 280220), 1);
  transform_48 = 1069547520;
  apply_bod_position((BodBase *)(this + 280184), (TransformMatrix *)&v379[60]);
  v29 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280240), v29);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar5X, *(Object **)(this + 280276), 1);
  transform_48 = 0x40000000;
  apply_bod_position((BodBase *)(this + 280240), (TransformMatrix *)&v379[60]);
  v30 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280296), v30);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar6X, *(Object **)(this + 280332), 1);
  transform_48 = 1075838976;
  apply_bod_position((BodBase *)(this + 280296), (TransformMatrix *)&v379[60]);
  v31 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280352), v31);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar7X, *(Object **)(this + 280388), 1);
  transform_48 = 1077936128;
  apply_bod_position((BodBase *)(this + 280352), (TransformMatrix *)&v379[60]);
  v32 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 280408), v32);
  load_x_mesh((DirectXLoader *)(this + 298496), aPillar8X, *(Object **)(this + 280444), 1);
  transform_48 = 1080033280;
  apply_bod_position((BodBase *)(this + 280408), (TransformMatrix *)&v379[60]);
  v33 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 281808), v33);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)(this + 281844), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(-1, *(_DWORD *)(this + 281844));
  v34 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 281864), v34);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)(this + 281900), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(0, *(_DWORD *)(this + 281900));
  v35 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 281920), v35);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)(this + 281956), aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(1, *(_DWORD *)(this + 281956));
  v36 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279064), v36);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)(this + 279100), aObjectsWorld00);
  v37 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279120), v37);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)(this + 279156), aObjectsWorld00);
  v38 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279232), v38);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)(this + 279268), aObjectsWorld00);
  v39 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279176), v39);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)(this + 279212), aObjectsWorld00);
  v40 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279288), v40);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)(this + 279324), aObjectsWorld00_0);
  v41 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279344), v41);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)(this + 279380), aObjectsWorld00_0);
  v42 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279456), v42);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)(this + 279492), aObjectsWorld00_0);
  v43 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279400), v43);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)(this + 279436), aObjectsWorld00_0);
  v44 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279512), v44);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)(this + 279548), texture_a);
  v45 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279568), v45);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)(this + 279604), texture_a);
  v46 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279680), v46);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)(this + 279716), texture_a);
  v47 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279624), v47);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)(this + 279660), texture_a);
  v48 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 279736), v48);
  load_x_mesh((DirectXLoader *)(this + 298496), aTrampX, *(Object **)(this + 279772), 1);
  *(_DWORD *)(*(_DWORD *)(this + 279772) + 20) = 6;
  v49 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)(this + 279772) + 92) + 12);
  *v49 |= 0x400u;
  v50 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 278784), v50);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)(this + 278820), aObjectsUnivers_0, 0.0);
  *(_DWORD *)(*(_DWORD *)(this + 278820) + 20) = 5;
  v51 = *(int **)(*(_DWORD *)(*(_DWORD *)(this + 278820) + 92) + 12);
  v52 = *v51;
  BYTE1(v52) = BYTE1(*v51) | 4;
  *v51 = v52;
  v53 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 281976), v53);
  load_object_definition(path, *(Object **)(this + 282012));
  v54 = (int *)(this + 3977532);
  *(_DWORD *)&v379[36] = 20;
  do
  {
    set_bod_object((BodBase *)(v54 - 9), *(Object **)(this + 282012));
    v55 = *v54;
    *(_DWORD *)&v379[12] = 1060320051;
    *(_DWORD *)&v379[8] = 1065353216;
    *(_DWORD *)&v379[4] = 1065353216;
    v56 = *(_DWORD *)(v55 + 92);
    *(_DWORD *)v379 = 1065353216;
    v57 = *(int **)(v56 + 12);
    v58 = *v57;
    BYTE1(v58) = BYTE1(*v57) | 4;
    *v57 = v58;
    v54[25] = this + 476696;
    store_color4f((tColour *)(v54 + 1), *(float *)v379, *(float *)&v379[4], *(float *)&v379[8], *(float *)&v379[12]);
    v59 = *v54;
    v54 += 44;
    v61 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v59 + 20) = 9;
    *(_DWORD *)&v379[36] = v61;
  }
  while ( !v60 );
  v62 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 298440), v62);
  load_x_mesh((DirectXLoader *)(this + 298496), aSaltX, *(Object **)(this + 298476), 1);
  v63 = (tColour *)(this + 3981152);
  *(_DWORD *)&v379[36] = 40;
  do
  {
    set_bod_object((BodBase *)&v63[-9].b, *(Object **)(this + 298476));
    *(_DWORD *)&v379[12] = 1063675494;
    *(_DWORD *)&v379[8] = 1065353216;
    *(_DWORD *)&v379[4] = 1065353216;
    *(_DWORD *)v379 = 1065353216;
    LODWORD(v63->r) = this + 476696;
    store_color4f(v63 - 6, *(float *)v379, *(float *)&v379[4], *(float *)&v379[8], *(float *)&v379[12]);
    *(_DWORD *)(LODWORD(v63[-7].a) + 20) = 12;
    set_matrix_identity((TransformMatrix *)&v63[-5]);
    v63 = (tColour *)((char *)v63 + 152);
    --*(_DWORD *)&v379[36];
  }
  while ( *(_DWORD *)&v379[36] );
  for ( i = 0; i < 2; ++i )
  {
    *(_DWORD *)&v379[36] = this + 96 * i;
    v65 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(*(_DWORD *)&v379[36] + 3987096), v65);
    if ( i )
    {
      if ( i != 1 )
        goto LABEL_31;
      v67 = *(_DWORD *)(this + 3987228);
      *(_DWORD *)&v379[12] = 1;
      *(_DWORD *)&v379[8] = v67;
    }
    else
    {
      v66 = *(_DWORD *)(this + 3987132);
      *(_DWORD *)&v379[12] = 1;
      *(_DWORD *)&v379[8] = v66;
    }
    load_x_mesh((DirectXLoader *)(this + 298496), aPostofficestop, *(Object **)&v379[8], *(int *)&v379[12]);
LABEL_31:
    v68 = *(_DWORD **)&v379[36];
    *(_DWORD *)(*(_DWORD *)&v379[36] + 3987120) = 0;
    v68[996779] = 0;
    v68[996778] = 0;
    *(_DWORD *)(32 * (3 * i + 124599) + this) = this + 476696;
    v68[996788] = i;
    v68[996796] = 0;
    v68[996797] = 1004768824;
  }
  v69 = this + 3973556;
  if ( (*(_DWORD *)(this + 3973560) & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v70 = *(_DWORD *)(this + 1452);
    v71 = this + 1452;
    if ( v70 )
    {
      *(_DWORD *)(v70 + 8) = v69;
      *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v71 + 8) + 12) = *(_DWORD *)v71;
      v72 = *(_DWORD *)(*(_DWORD *)v71 + 8);
      *(_DWORD *)v71 = v72;
      *(_DWORD *)(v72 + 8) = 0;
    }
    else
    {
      *(_DWORD *)v71 = v69;
      *(_DWORD *)(this + 3973564) = 0;
      *(_DWORD *)(*(_DWORD *)v71 + 12) = 0;
    }
    v73 = *(_DWORD *)(this + 3973560);
    BYTE1(v73) |= 2u;
    *(_DWORD *)(this + 3973560) = v73;
  }
  v74 = this + 3973612;
  v75 = (int *)(this + 3973616);
  if ( (*(_DWORD *)(this + 3973616) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973620) = v69;
    *(_DWORD *)(this + 3973624) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v74;
    v76 = *(_DWORD *)(this + 3973624);
    if ( v76 )
      *(_DWORD *)(v76 + 8) = v74;
    v77 = *v75;
    BYTE1(v77) = BYTE1(*v75) | 2;
    *v75 = v77;
  }
  v78 = this + 3973668;
  v79 = (int *)(this + 3973672);
  if ( (*(_DWORD *)(this + 3973672) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973676) = v69;
    *(_DWORD *)(this + 3973680) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v78;
    v80 = *(_DWORD *)(this + 3973680);
    if ( v80 )
      *(_DWORD *)(v80 + 8) = v78;
    v81 = *v79;
    BYTE1(v81) = BYTE1(*v79) | 2;
    *v79 = v81;
  }
  v82 = this + 3973948;
  v83 = (int *)(this + 3973952);
  if ( (*(_DWORD *)(this + 3973952) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973956) = v69;
    *(_DWORD *)(this + 3973960) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v82;
    v84 = *(_DWORD *)(this + 3973960);
    if ( v84 )
      *(_DWORD *)(v84 + 8) = v82;
    v85 = *v83;
    BYTE1(v85) = BYTE1(*v83) | 2;
    *v83 = v85;
  }
  v86 = this + 3973500;
  v87 = (int *)(this + 3973504);
  if ( (*(_DWORD *)(this + 3973504) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973508) = v69;
    *(_DWORD *)(this + 3973512) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v86;
    v88 = *(_DWORD *)(this + 3973512);
    if ( v88 )
      *(_DWORD *)(v88 + 8) = v86;
    v89 = *v87;
    BYTE1(v89) = BYTE1(*v87) | 2;
    *v87 = v89;
  }
  v90 = this + 3973836;
  v91 = (int *)(this + 3973840);
  if ( (*(_DWORD *)(this + 3973840) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973844) = v69;
    *(_DWORD *)(this + 3973848) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v90;
    v92 = *(_DWORD *)(this + 3973848);
    if ( v92 )
      *(_DWORD *)(v92 + 8) = v90;
    v93 = *v91;
    BYTE1(v93) = BYTE1(*v91) | 2;
    *v91 = v93;
  }
  v94 = this + 3973892;
  v95 = (int *)(this + 3973896);
  if ( (*(_DWORD *)(this + 3973896) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973900) = v69;
    *(_DWORD *)(this + 3973904) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v94;
    v96 = *(_DWORD *)(this + 3973904);
    if ( v96 )
      *(_DWORD *)(v96 + 8) = v94;
    v97 = *v95;
    BYTE1(v97) = BYTE1(*v95) | 2;
    *v95 = v97;
  }
  v98 = this + 3973724;
  v99 = (int *)(this + 3973728);
  if ( (*(_DWORD *)(this + 3973728) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973732) = v69;
    *(_DWORD *)(this + 3973736) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v98;
    v100 = *(_DWORD *)(this + 3973736);
    if ( v100 )
      *(_DWORD *)(v100 + 8) = v98;
    v101 = *v99;
    BYTE1(v101) = BYTE1(*v99) | 2;
    *v99 = v101;
  }
  v102 = this + 3973780;
  v103 = (int *)(this + 3973784);
  if ( (*(_DWORD *)(this + 3973784) & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    *(_DWORD *)(this + 3973788) = v69;
    *(_DWORD *)(this + 3973792) = *(_DWORD *)(this + 3973568);
    *(_DWORD *)(this + 3973568) = v102;
    v104 = *(_DWORD *)(this + 3973792);
    if ( v104 )
      *(_DWORD *)(v104 + 8) = v102;
    v105 = *v103;
    BYTE1(v105) = BYTE1(*v103) | 2;
    *v103 = v105;
  }
  debug_report_stub();
  v106 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17198892), v106);
  initialize_looptheloop_path_template_pair((Path *)(this + 17198892), 6.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17198916) = 0;
  *(_DWORD *)(this + 17198912) = 0;
  *(_DWORD *)(this + 17198908) = 0;
  v107 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199060), v107);
  mirror_path_template_pair_x((Path *)(this + 17199060), (Path *)(this + 17198892));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17199084) = 0;
  *(_DWORD *)(this + 17199080) = 0;
  *(_DWORD *)(this + 17199076) = 0;
  build_track_fringe_mesh((Path *)(this + 17198892), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17199012) = 0;
  *(_DWORD *)(this + 17199008) = 0;
  *(_DWORD *)(this + 17199004) = 0;
  build_track_fringe_mesh((Path *)(this + 17199060), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17199180) = 0;
  *(_DWORD *)(this + 17199176) = 0;
  *(_DWORD *)(this + 17199172) = 0;
  v108 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199228), v108);
  initialize_looptheloop_path_template_pair((Path *)(this + 17199228), 6.0, 2, (char *)1, texture_a);
  *(_DWORD *)(this + 17199252) = 0;
  *(_DWORD *)(this + 17199248) = 0;
  *(_DWORD *)(this + 17199244) = 0;
  v109 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199396), v109);
  mirror_path_template_pair_x((Path *)(this + 17199396), (Path *)(this + 17199228));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17199420) = 0;
  *(_DWORD *)(this + 17199416) = 0;
  *(_DWORD *)(this + 17199412) = 0;
  build_track_fringe_mesh((Path *)(this + 17199228), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17199348) = 0;
  *(_DWORD *)(this + 17199344) = 0;
  *(_DWORD *)(this + 17199340) = 0;
  build_track_fringe_mesh((Path *)(this + 17199396), aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17199516) = 0;
  *(_DWORD *)(this + 17199512) = 0;
  *(_DWORD *)(this + 17199508) = 0;
  v110 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199564), v110);
  initialize_looptheloop_path_template_pair((Path *)(this + 17199564), 8.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17199588) = 0;
  *(_DWORD *)(this + 17199584) = 0;
  *(_DWORD *)(this + 17199580) = 0;
  v111 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199732), v111);
  mirror_path_template_pair_x((Path *)(this + 17199732), (Path *)(this + 17199564));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17199756) = 0;
  *(_DWORD *)(this + 17199752) = 0;
  *(_DWORD *)(this + 17199748) = 0;
  build_track_fringe_mesh((Path *)(this + 17199564), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17199684) = 0;
  *(_DWORD *)(this + 17199680) = 0;
  *(_DWORD *)(this + 17199676) = 0;
  build_track_fringe_mesh((Path *)(this + 17199732), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17199852) = 0;
  *(_DWORD *)(this + 17199848) = 0;
  *(_DWORD *)(this + 17199844) = 0;
  v112 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200908), v112);
  initialize_looptheloopw_path_template_pair((Path *)(this + 17200908), 8.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17200932) = 0;
  *(_DWORD *)(this + 17200928) = 0;
  *(_DWORD *)(this + 17200924) = 0;
  v113 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201076), v113);
  mirror_path_template_pair_x((Path *)(this + 17201076), (Path *)(this + 17200908));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201100) = 0;
  *(_DWORD *)(this + 17201096) = 0;
  *(_DWORD *)(this + 17201092) = 0;
  build_track_fringe_mesh((Path *)(this + 17200908), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17201028) = 0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201024) = 0;
  *(_DWORD *)(this + 17201020) = 0;
  build_track_fringe_mesh((Path *)(this + 17201076), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17201196) = 0;
  *(_DWORD *)(this + 17201192) = 0;
  *(_DWORD *)(this + 17201188) = 0;
  v114 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17199900), v114);
  initialize_looptheloop_path_template_pair((Path *)(this + 17199900), 3.0, 2, (char *)1, texture_a);
  *(_DWORD *)(this + 17199924) = 0;
  *(_DWORD *)(this + 17199920) = 0;
  *(_DWORD *)(this + 17199916) = 0;
  v115 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200068), v115);
  mirror_path_template_pair_x((Path *)(this + 17200068), (Path *)(this + 17199900));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17200092) = 0;
  *(_DWORD *)(this + 17200088) = 0;
  *(_DWORD *)(this + 17200084) = 0;
  build_track_fringe_mesh((Path *)(this + 17199900), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17200020) = 0;
  *(_DWORD *)(this + 17200016) = 0;
  *(_DWORD *)(this + 17200012) = 0;
  build_track_fringe_mesh((Path *)(this + 17200068), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17200188) = 0;
  *(_DWORD *)(this + 17200184) = 0;
  *(_DWORD *)(this + 17200180) = 0;
  v116 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200236), v116);
  initialize_looptheloop_path_template_pair((Path *)(this + 17200236), 3.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17200260) = 0;
  *(_DWORD *)(this + 17200256) = 0;
  *(_DWORD *)(this + 17200252) = 0;
  v117 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200404), v117);
  mirror_path_template_pair_x((Path *)(this + 17200404), (Path *)(this + 17200236));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(this + 17200428) = 0;
  *(_DWORD *)(this + 17200424) = 0;
  *(_DWORD *)(this + 17200420) = 0;
  build_track_fringe_mesh((Path *)(this + 17200236), aObjectsUnivers_1, *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17200356) = 0;
  *(_DWORD *)(this + 17200352) = 0;
  *(_DWORD *)(this + 17200348) = 0;
  build_track_fringe_mesh((Path *)(this + 17200404), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17200524) = 0;
  *(_DWORD *)(this + 17200520) = 0;
  *(_DWORD *)(this + 17200516) = 0;
  v118 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200572), v118);
  initialize_looptheloop_path_template_pair((Path *)(this + 17200572), 3.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17200596) = 0;
  *(_DWORD *)(this + 17200592) = 0;
  *(_DWORD *)(this + 17200588) = 0;
  v119 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17200740), v119);
  mirror_path_template_pair_x((Path *)(this + 17200740), (Path *)(this + 17200572));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17200764) = 0;
  *(_DWORD *)(this + 17200760) = 0;
  *(_DWORD *)(this + 17200756) = 0;
  build_track_fringe_mesh((Path *)(this + 17200572), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17200692) = 0;
  *(_DWORD *)(this + 17200688) = 0;
  *(_DWORD *)(this + 17200684) = 0;
  build_track_fringe_mesh((Path *)(this + 17200740), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17200860) = 0;
  *(_DWORD *)(this + 17200856) = 0;
  *(_DWORD *)(this + 17200852) = 0;
  v120 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201244), v120);
  initialize_loopbow_path_template_pair((Path *)(this + 17201244), 6.0, 4u, (char *)1, texture_a);
  *(_DWORD *)(this + 17201268) = 0;
  *(_DWORD *)(this + 17201264) = 0;
  *(_DWORD *)(this + 17201260) = 0;
  v121 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201412), v121);
  mirror_path_template_pair_x((Path *)(this + 17201412), (Path *)(this + 17201244));
  *(_DWORD *)(this + 17201436) = 0;
  *(_DWORD *)(this + 17201432) = 0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201428) = 0;
  build_track_fringe_mesh((Path *)(this + 17201244), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201364) = 0;
  *(_DWORD *)(this + 17201360) = 0;
  *(_DWORD *)(this + 17201356) = 0;
  build_track_fringe_mesh((Path *)(this + 17201412), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17201532) = 0;
  *(_DWORD *)(this + 17201528) = 0;
  *(_DWORD *)(this + 17201524) = 0;
  v122 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211324), v122);
  initialize_turnover_path_template_pair((Path *)(this + 17211324), 6.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17211348) = 0;
  *(_DWORD *)(this + 17211344) = 0;
  *(_DWORD *)(this + 17211340) = 0;
  v123 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211492), v123);
  mirror_path_template_pair_x((Path *)(this + 17211492), (Path *)(this + 17211324));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211516) = 0;
  *(_DWORD *)(this + 17211512) = 0;
  *(_DWORD *)(this + 17211508) = 0;
  build_track_fringe_mesh((Path *)(this + 17211324), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211444) = 0;
  *(_DWORD *)(this + 17211440) = 0;
  *(_DWORD *)(this + 17211436) = 0;
  build_track_fringe_mesh((Path *)(this + 17211492), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17211612) = 0;
  *(_DWORD *)(this + 17211608) = 0;
  *(_DWORD *)(this + 17211604) = 0;
  v124 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211660), v124);
  initialize_turnoverdouble_path_template_pair((Path *)(this + 17211660), 6.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17211684) = 0;
  *(_DWORD *)(this + 17211680) = 0;
  *(_DWORD *)(this + 17211676) = 0;
  v125 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211828), v125);
  mirror_path_template_pair_x((Path *)(this + 17211828), (Path *)(this + 17211660));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211852) = 0;
  *(_DWORD *)(this + 17211848) = 0;
  *(_DWORD *)(this + 17211844) = 0;
  build_track_fringe_mesh((Path *)(this + 17211660), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211780) = 0;
  *(_DWORD *)(this + 17211776) = 0;
  *(_DWORD *)(this + 17211772) = 0;
  build_track_fringe_mesh((Path *)(this + 17211828), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17211948) = 0;
  *(_DWORD *)(this + 17211944) = 0;
  *(_DWORD *)(this + 17211940) = 0;
  v126 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213340), v126);
  initialize_twister_path_template_pair((Path *)(this + 17213340), 2.5, 3, 1, texture_a, texture_b);
  *(_DWORD *)(this + 17213364) = 0;
  *(_DWORD *)(this + 17213360) = 0;
  *(_DWORD *)(this + 17213356) = 0;
  v127 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213508), v127);
  mirror_path_template_pair_x((Path *)(this + 17213508), (Path *)(this + 17213340));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213532) = 0;
  *(_DWORD *)(this + 17213528) = 0;
  *(_DWORD *)(this + 17213524) = 0;
  build_track_fringe_mesh((Path *)(this + 17213340), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213460) = 0;
  *(_DWORD *)(this + 17213456) = 0;
  *(_DWORD *)(this + 17213452) = 0;
  build_track_fringe_mesh((Path *)(this + 17213508), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17213628) = 0;
  *(_DWORD *)(this + 17213624) = 0;
  *(_DWORD *)(this + 17213620) = 0;
  v128 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213676), v128);
  initialize_twister_path_template_pair((Path *)(this + 17213676), 2.5, 3, 0, texture_a, texture_b);
  *(_DWORD *)(this + 17213700) = 0;
  *(_DWORD *)(this + 17213696) = 0;
  *(_DWORD *)(this + 17213692) = 0;
  v129 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213844), v129);
  mirror_path_template_pair_x((Path *)(this + 17213844), (Path *)(this + 17213676));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213868) = 0;
  *(_DWORD *)(this + 17213864) = 0;
  *(_DWORD *)(this + 17213860) = 0;
  build_track_fringe_mesh((Path *)(this + 17213676), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213796) = 0;
  *(_DWORD *)(this + 17213792) = 0;
  *(_DWORD *)(this + 17213788) = 0;
  build_track_fringe_mesh((Path *)(this + 17213844), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17213964) = 0;
  *(_DWORD *)(this + 17213960) = 0;
  *(_DWORD *)(this + 17213956) = 0;
  v130 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214012), v130);
  initialize_twister2_path_template_pair((Path *)(this + 17214012), 2.5, 3, 1, texture_a, texture_b);
  *(_DWORD *)(this + 17214036) = 0;
  *(_DWORD *)(this + 17214032) = 0;
  *(_DWORD *)(this + 17214028) = 0;
  v131 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214180), v131);
  mirror_path_template_pair_x((Path *)(this + 17214180), (Path *)(this + 17214012));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214204) = 0;
  *(_DWORD *)(this + 17214200) = 0;
  *(_DWORD *)(this + 17214196) = 0;
  build_track_fringe_mesh((Path *)(this + 17214012), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214132) = 0;
  *(_DWORD *)(this + 17214128) = 0;
  *(_DWORD *)(this + 17214124) = 0;
  build_track_fringe_mesh((Path *)(this + 17214180), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17214300) = 0;
  *(_DWORD *)(this + 17214296) = 0;
  *(_DWORD *)(this + 17214292) = 0;
  v132 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214348), v132);
  initialize_twister2_path_template_pair((Path *)(this + 17214348), 2.5, 3, 0, texture_a, texture_b);
  *(_DWORD *)(this + 17214372) = 0;
  *(_DWORD *)(this + 17214368) = 0;
  *(_DWORD *)(this + 17214364) = 0;
  v133 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214516), v133);
  mirror_path_template_pair_x((Path *)(this + 17214516), (Path *)(this + 17214348));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214540) = 0;
  *(_DWORD *)(this + 17214536) = 0;
  *(_DWORD *)(this + 17214532) = 0;
  build_track_fringe_mesh((Path *)(this + 17214348), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214468) = 0;
  *(_DWORD *)(this + 17214464) = 0;
  *(_DWORD *)(this + 17214460) = 0;
  build_track_fringe_mesh((Path *)(this + 17214516), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17214636) = 0;
  *(_DWORD *)(this + 17214632) = 0;
  *(_DWORD *)(this + 17214628) = 0;
  v134 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211996), v134);
  initialize_turnunder_path_template_pair((Path *)(this + 17211996), 6.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17212020) = 0;
  *(_DWORD *)(this + 17212016) = 0;
  *(_DWORD *)(this + 17212012) = 0;
  v135 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17212164), v135);
  mirror_path_template_pair_x((Path *)(this + 17212164), (Path *)(this + 17211996));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212188) = 0;
  *(_DWORD *)(this + 17212184) = 0;
  *(_DWORD *)(this + 17212180) = 0;
  build_track_fringe_mesh((Path *)(this + 17211996), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212116) = 0;
  *(_DWORD *)(this + 17212112) = 0;
  *(_DWORD *)(this + 17212108) = 0;
  build_track_fringe_mesh((Path *)(this + 17212164), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17212284) = 0;
  *(_DWORD *)(this + 17212280) = 0;
  *(_DWORD *)(this + 17212276) = 0;
  v136 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17212668), v136);
  initialize_invert_path_template_pair((Path *)(this + 17212668), 1086324736, (char *)8, (char *)1);
  *(_DWORD *)(this + 17212692) = 0;
  *(_DWORD *)(this + 17212688) = 0;
  *(_DWORD *)(this + 17212684) = 0;
  v137 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17212836), v137);
  mirror_path_template_pair_x((Path *)(this + 17212836), (Path *)(this + 17212668));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212860) = 0;
  *(_DWORD *)(this + 17212856) = 0;
  *(_DWORD *)(this + 17212852) = 0;
  build_track_fringe_mesh((Path *)(this + 17212668), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212788) = 0;
  *(_DWORD *)(this + 17212784) = 0;
  *(_DWORD *)(this + 17212780) = 0;
  build_track_fringe_mesh((Path *)(this + 17212836), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17212956) = 0;
  *(_DWORD *)(this + 17212952) = 0;
  *(_DWORD *)(this + 17212948) = 0;
  v138 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213004), v138);
  initialize_halfpipe_path_template_pair((Path *)(this + 17213004), 1086324736, (char *)8, (char *)1);
  *(_DWORD *)(this + 17213028) = 0;
  *(_DWORD *)(this + 17213024) = 0;
  *(_DWORD *)(this + 17213020) = 0;
  v139 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17213172), v139);
  mirror_path_template_pair_x((Path *)(this + 17213172), (Path *)(this + 17213004));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213196) = 0;
  *(_DWORD *)(this + 17213192) = 0;
  *(_DWORD *)(this + 17213188) = 0;
  build_track_fringe_mesh((Path *)(this + 17213004), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17213124) = 0;
  *(_DWORD *)(this + 17213120) = 0;
  *(_DWORD *)(this + 17213116) = 0;
  build_track_fringe_mesh((Path *)(this + 17213172), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17213292) = 0;
  *(_DWORD *)(this + 17213288) = 0;
  *(_DWORD *)(this + 17213284) = 0;
  v140 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17212332), v140);
  initialize_wibble_path_template_pair((Path *)(this + 17212332), 1086324736, (char *)8, (char *)1);
  *(_DWORD *)(this + 17212356) = 0;
  *(_DWORD *)(this + 17212352) = 0;
  *(_DWORD *)(this + 17212348) = 0;
  v141 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17212500), v141);
  mirror_path_template_pair_x((Path *)(this + 17212500), (Path *)(this + 17212332));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212524) = 0;
  *(_DWORD *)(this + 17212520) = 0;
  *(_DWORD *)(this + 17212516) = 0;
  build_track_fringe_mesh((Path *)(this + 17212332), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17212452) = 0;
  *(_DWORD *)(this + 17212448) = 0;
  *(_DWORD *)(this + 17212444) = 0;
  build_track_fringe_mesh((Path *)(this + 17212500), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17212620) = 0;
  *(_DWORD *)(this + 17212616) = 0;
  *(_DWORD *)(this + 17212612) = 0;
  v142 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17209308), v142);
  initialize_supertramp_path_template_pair((Path *)(this + 17209308), 6.0, 2, (char *)1, texture_a, texture_b);
  *(_DWORD *)&v379[12] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17209332) = 0;
  *(_DWORD *)(this + 17209328) = 0;
  *(_DWORD *)(this + 17209324) = 0;
  build_track_fringe_supertramp_mesh((Path *)(this + 17209308), *(char **)&v379[12]);
  *(_DWORD *)(this + 17209428) = 0;
  *(_DWORD *)(this + 17209424) = 0;
  *(_DWORD *)(this + 17209420) = 0;
  v143 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17209476), v143);
  initialize_supertramp_path_template_pair((Path *)(this + 17209476), 6.0, 2, (char *)1, texture_a, texture_b);
  *(_DWORD *)&v379[12] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17209500) = 0;
  *(_DWORD *)(this + 17209496) = 0;
  *(_DWORD *)(this + 17209492) = 0;
  build_track_fringe_supertramp_mesh((Path *)(this + 17209476), *(char **)&v379[12]);
  *(_DWORD *)(this + 17209596) = 0;
  *(_DWORD *)(this + 17209592) = 0;
  *(_DWORD *)(this + 17209588) = 0;
  v144 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210988), v144);
  initialize_start_path_template_pair((Path *)(this + 17210988), 4.0, 8, (char *)1);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211012) = 0;
  *(_DWORD *)(this + 17211008) = 0;
  *(_DWORD *)(this + 17211004) = 0;
  build_track_fringe_mesh((Path *)(this + 17210988), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17211108) = 0;
  *(_DWORD *)(this + 17211104) = 0;
  *(_DWORD *)(this + 17211100) = 0;
  v145 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17211156), v145);
  initialize_start_path_template_pair((Path *)(this + 17211156), 4.0, 8, (char *)1);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17211180) = 0;
  *(_DWORD *)(this + 17211176) = 0;
  *(_DWORD *)(this + 17211172) = 0;
  build_track_fringe_mesh((Path *)(this + 17211156), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17211276) = 0;
  *(_DWORD *)(this + 17211272) = 0;
  *(_DWORD *)(this + 17211268) = 0;
  v146 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207292), v146);
  initialize_loopout_path_template_pair((Path *)(this + 17207292), 3.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17207316) = 0;
  *(_DWORD *)(this + 17207312) = 0;
  *(_DWORD *)(this + 17207308) = 0;
  v147 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207460), v147);
  mirror_path_template_pair_x((Path *)(this + 17207460), (Path *)(this + 17207292));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17207484) = 0;
  *(_DWORD *)(this + 17207480) = 0;
  *(_DWORD *)(this + 17207476) = 0;
  build_track_fringe_mesh((Path *)(this + 17207292), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17207412) = 0;
  *(_DWORD *)(this + 17207408) = 0;
  *(_DWORD *)(this + 17207404) = 0;
  build_track_fringe_mesh((Path *)(this + 17207460), aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17207580) = 0;
  *(_DWORD *)(this + 17207576) = 0;
  *(_DWORD *)(this + 17207572) = 0;
  v148 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207964), v148);
  initialize_loopout_path_template_pair((Path *)(this + 17207964), 5.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17207988) = 0;
  *(_DWORD *)(this + 17207984) = 0;
  *(_DWORD *)(this + 17207980) = 0;
  v149 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17208132), v149);
  mirror_path_template_pair_x((Path *)(this + 17208132), (Path *)(this + 17207964));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208156) = 0;
  *(_DWORD *)(this + 17208152) = 0;
  *(_DWORD *)(this + 17208148) = 0;
  build_track_fringe_mesh((Path *)(this + 17207964), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208084) = 0;
  *(_DWORD *)(this + 17208080) = 0;
  *(_DWORD *)(this + 17208076) = 0;
  build_track_fringe_mesh((Path *)(this + 17208132), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17208252) = 0;
  *(_DWORD *)(this + 17208248) = 0;
  *(_DWORD *)(this + 17208244) = 0;
  v150 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207628), v150);
  initialize_loopout_path_template_pair((Path *)(this + 17207628), 3.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17207652) = 0;
  *(_DWORD *)(this + 17207648) = 0;
  *(_DWORD *)(this + 17207644) = 0;
  v151 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207796), v151);
  mirror_path_template_pair_x((Path *)(this + 17207796), (Path *)(this + 17207628));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17207820) = 0;
  *(_DWORD *)(this + 17207816) = 0;
  *(_DWORD *)(this + 17207812) = 0;
  build_track_fringe_mesh((Path *)(this + 17207628), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17207748) = 0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17207744) = 0;
  *(_DWORD *)(this + 17207740) = 0;
  build_track_fringe_mesh((Path *)(this + 17207796), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17207916) = 0;
  *(_DWORD *)(this + 17207912) = 0;
  *(_DWORD *)(this + 17207908) = 0;
  v152 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204268), v152);
  initialize_hump_path_template_pair((Path *)(this + 17204268), 4.0, 1.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17204292) = 0;
  *(_DWORD *)(this + 17204288) = 0;
  *(_DWORD *)(this + 17204284) = 0;
  v153 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204436), v153);
  mirror_path_template_pair_x((Path *)(this + 17204436), (Path *)(this + 17204268));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17204460) = 0;
  *(_DWORD *)(this + 17204456) = 0;
  *(_DWORD *)(this + 17204452) = 0;
  build_track_fringe_mesh((Path *)(this + 17204268), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17204388) = 0;
  *(_DWORD *)(this + 17204384) = 0;
  *(_DWORD *)(this + 17204380) = 0;
  build_track_fringe_mesh((Path *)(this + 17204436), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17204556) = 0;
  *(_DWORD *)(this + 17204552) = 0;
  *(_DWORD *)(this + 17204548) = 0;
  v154 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204604), v154);
  initialize_dump_path_template_pair((Path *)(this + 17204604), 4.0, 1.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17204628) = 0;
  *(_DWORD *)(this + 17204624) = 0;
  *(_DWORD *)(this + 17204620) = 0;
  v155 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204772), v155);
  mirror_path_template_pair_x((Path *)(this + 17204772), (Path *)(this + 17204604));
  *(_DWORD *)(this + 17204796) = 0;
  *(_DWORD *)(this + 17204792) = 0;
  *(_DWORD *)(this + 17204788) = 0;
  build_track_fringe_mesh((Path *)(this + 17204604), aObjectsUnivers_1, 0.0);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17204724) = 0;
  *(_DWORD *)(this + 17204720) = 0;
  *(_DWORD *)(this + 17204716) = 0;
  build_track_fringe_mesh((Path *)(this + 17204772), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17204892) = 0;
  *(_DWORD *)(this + 17204888) = 0;
  *(_DWORD *)(this + 17204884) = 0;
  v156 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204940), v156);
  initialize_hump_path_template_pair((Path *)(this + 17204940), 4.0, 0.30000001, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17204964) = 0;
  *(_DWORD *)(this + 17204960) = 0;
  *(_DWORD *)(this + 17204956) = 0;
  v157 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205108), v157);
  mirror_path_template_pair_x((Path *)(this + 17205108), (Path *)(this + 17204940));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205132) = 0;
  *(_DWORD *)(this + 17205128) = 0;
  *(_DWORD *)(this + 17205124) = 0;
  build_track_fringe_mesh((Path *)(this + 17204940), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205060) = 0;
  *(_DWORD *)(this + 17205056) = 0;
  *(_DWORD *)(this + 17205052) = 0;
  build_track_fringe_mesh((Path *)(this + 17205108), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17205228) = 0;
  *(_DWORD *)(this + 17205224) = 0;
  *(_DWORD *)(this + 17205220) = 0;
  v158 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205276), v158);
  initialize_dump_path_template_pair((Path *)(this + 17205276), 4.0, 0.30000001, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17205300) = 0;
  *(_DWORD *)(this + 17205296) = 0;
  *(_DWORD *)(this + 17205292) = 0;
  v159 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205444), v159);
  mirror_path_template_pair_x((Path *)(this + 17205444), (Path *)(this + 17205276));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205468) = 0;
  *(_DWORD *)(this + 17205464) = 0;
  *(_DWORD *)(this + 17205460) = 0;
  build_track_fringe_mesh((Path *)(this + 17205276), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205396) = 0;
  *(_DWORD *)(this + 17205392) = 0;
  *(_DWORD *)(this + 17205388) = 0;
  build_track_fringe_mesh((Path *)(this + 17205444), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17205564) = 0;
  *(_DWORD *)(this + 17205560) = 0;
  *(_DWORD *)(this + 17205556) = 0;
  v160 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201580), v160);
  initialize_hill_valley_path_template_pair((Path *)(this + 17201580), 8, 4.0, 20.0, 1, texture_a, texture_a);
  *(_DWORD *)(this + 17201604) = 0;
  *(_DWORD *)(this + 17201600) = 0;
  *(_DWORD *)(this + 17201596) = 0;
  v161 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201748), v161);
  mirror_path_template_pair_x((Path *)(this + 17201748), (Path *)(this + 17201580));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201772) = 0;
  *(_DWORD *)(this + 17201768) = 0;
  *(_DWORD *)(this + 17201764) = 0;
  build_track_fringe_mesh((Path *)(this + 17201580), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17201700) = 0;
  *(_DWORD *)(this + 17201696) = 0;
  *(_DWORD *)(this + 17201692) = 0;
  build_track_fringe_mesh((Path *)(this + 17201748), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17201868) = 0;
  *(_DWORD *)(this + 17201864) = 0;
  *(_DWORD *)(this + 17201860) = 0;
  v162 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202252), v162);
  initialize_hill_valley_path_template_pair((Path *)(this + 17202252), 4, 4.0, 20.0, 0, texture_a, texture_b);
  *(_DWORD *)(this + 17202276) = 0;
  *(_DWORD *)(this + 17202272) = 0;
  *(_DWORD *)(this + 17202268) = 0;
  v163 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202420), v163);
  mirror_path_template_pair_x((Path *)(this + 17202420), (Path *)(this + 17202252));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202444) = 0;
  *(_DWORD *)(this + 17202440) = 0;
  *(_DWORD *)(this + 17202436) = 0;
  build_track_fringe_mesh((Path *)(this + 17202252), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202372) = 0;
  *(_DWORD *)(this + 17202368) = 0;
  *(_DWORD *)(this + 17202364) = 0;
  build_track_fringe_mesh((Path *)(this + 17202420), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17202540) = 0;
  *(_DWORD *)(this + 17202536) = 0;
  *(_DWORD *)(this + 17202532) = 0;
  v164 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17201916), v164);
  initialize_hill_valley_path_template_pair((Path *)(this + 17201916), 4, 4.0, 20.0, 1, texture_a, texture_b);
  *(_DWORD *)(this + 17201940) = 0;
  *(_DWORD *)(this + 17201936) = 0;
  *(_DWORD *)(this + 17201932) = 0;
  v165 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202084), v165);
  mirror_path_template_pair_x((Path *)(this + 17202084), (Path *)(this + 17201916));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202108) = 0;
  *(_DWORD *)(this + 17202104) = 0;
  *(_DWORD *)(this + 17202100) = 0;
  build_track_fringe_mesh((Path *)(this + 17201916), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202036) = 0;
  *(_DWORD *)(this + 17202032) = 0;
  *(_DWORD *)(this + 17202028) = 0;
  build_track_fringe_mesh((Path *)(this + 17202084), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17202204) = 0;
  *(_DWORD *)(this + 17202200) = 0;
  *(_DWORD *)(this + 17202196) = 0;
  v166 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203596), v166);
  initialize_sbend_path_template_pair((Path *)(this + 17203596), 8u, 8.0, 14.0, 1, aObjectsWorld00, aObjectsWorld00);
  *(_DWORD *)(this + 17203620) = 0;
  *(_DWORD *)(this + 17203616) = 0;
  *(_DWORD *)(this + 17203612) = 0;
  v167 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203764), v167);
  mirror_path_template_pair_x((Path *)(this + 17203764), (Path *)(this + 17203596));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203788) = 0;
  *(_DWORD *)(this + 17203784) = 0;
  *(_DWORD *)(this + 17203780) = 0;
  build_track_fringe_mesh((Path *)(this + 17203596), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203716) = 0;
  *(_DWORD *)(this + 17203712) = 0;
  *(_DWORD *)(this + 17203708) = 0;
  build_track_fringe_mesh((Path *)(this + 17203764), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17203884) = 0;
  *(_DWORD *)(this + 17203880) = 0;
  *(_DWORD *)(this + 17203876) = 0;
  v168 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202588), v168);
  initialize_hill_valley_path_template_pair((Path *)(this + 17202588), 8, -4.0, 20.0, 1, texture_a, texture_a);
  *(_DWORD *)(this + 17202612) = 0;
  *(_DWORD *)(this + 17202608) = 0;
  *(_DWORD *)(this + 17202604) = 0;
  v169 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202756), v169);
  mirror_path_template_pair_x((Path *)(this + 17202756), (Path *)(this + 17202588));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202780) = 0;
  *(_DWORD *)(this + 17202776) = 0;
  *(_DWORD *)(this + 17202772) = 0;
  build_track_fringe_mesh((Path *)(this + 17202588), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17202708) = 0;
  *(_DWORD *)(this + 17202704) = 0;
  *(_DWORD *)(this + 17202700) = 0;
  build_track_fringe_mesh((Path *)(this + 17202756), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17202876) = 0;
  *(_DWORD *)(this + 17202872) = 0;
  *(_DWORD *)(this + 17202868) = 0;
  v170 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203260), v170);
  initialize_hill_valley_path_template_pair((Path *)(this + 17203260), 4, -4.0, 20.0, 0, texture_a, texture_a);
  *(_DWORD *)(this + 17203284) = 0;
  *(_DWORD *)(this + 17203280) = 0;
  *(_DWORD *)(this + 17203276) = 0;
  v171 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203428), v171);
  mirror_path_template_pair_x((Path *)(this + 17203428), (Path *)(this + 17203260));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203452) = 0;
  *(_DWORD *)(this + 17203448) = 0;
  *(_DWORD *)(this + 17203444) = 0;
  build_track_fringe_mesh((Path *)(this + 17203260), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203380) = 0;
  *(_DWORD *)(this + 17203376) = 0;
  *(_DWORD *)(this + 17203372) = 0;
  build_track_fringe_mesh((Path *)(this + 17203428), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17203548) = 0;
  *(_DWORD *)(this + 17203544) = 0;
  *(_DWORD *)(this + 17203540) = 0;
  v172 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17202924), v172);
  initialize_hill_valley_path_template_pair((Path *)(this + 17202924), 4, -4.0, 20.0, 1, texture_a, texture_a);
  *(_DWORD *)(this + 17202948) = 0;
  *(_DWORD *)(this + 17202944) = 0;
  *(_DWORD *)(this + 17202940) = 0;
  v173 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203092), v173);
  mirror_path_template_pair_x((Path *)(this + 17203092), (Path *)(this + 17202924));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203116) = 0;
  *(_DWORD *)(this + 17203112) = 0;
  *(_DWORD *)(this + 17203108) = 0;
  build_track_fringe_mesh((Path *)(this + 17202924), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17203044) = 0;
  *(_DWORD *)(this + 17203040) = 0;
  *(_DWORD *)(this + 17203036) = 0;
  build_track_fringe_mesh((Path *)(this + 17203092), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17203212) = 0;
  *(_DWORD *)(this + 17203208) = 0;
  *(_DWORD *)(this + 17203204) = 0;
  v174 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205612), v174);
  initialize_dip_path_template_pair((Path *)(this + 17205612), 4.0, 2, (char *)1, texture_a);
  *(_DWORD *)(this + 17205636) = 0;
  *(_DWORD *)(this + 17205632) = 0;
  *(_DWORD *)(this + 17205628) = 0;
  v175 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205780), v175);
  mirror_path_template_pair_x((Path *)(this + 17205780), (Path *)(this + 17205612));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205804) = 0;
  *(_DWORD *)(this + 17205800) = 0;
  *(_DWORD *)(this + 17205796) = 0;
  build_track_fringe_mesh((Path *)(this + 17205612), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17205732) = 0;
  *(_DWORD *)(this + 17205728) = 0;
  *(_DWORD *)(this + 17205724) = 0;
  build_track_fringe_mesh((Path *)(this + 17205780), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17205900) = 0;
  *(_DWORD *)(this + 17205896) = 0;
  *(_DWORD *)(this + 17205892) = 0;
  v176 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17205948), v176);
  initialize_screw_path_template_pair((Path *)(this + 17205948), 24, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17205972) = 0;
  *(_DWORD *)(this + 17205968) = 0;
  *(_DWORD *)(this + 17205964) = 0;
  v177 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206116), v177);
  mirror_path_template_pair_x((Path *)(this + 17206116), (Path *)(this + 17205948));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206140) = 0;
  *(_DWORD *)(this + 17206136) = 0;
  *(_DWORD *)(this + 17206132) = 0;
  build_track_fringe_mesh((Path *)(this + 17205948), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206068) = 0;
  *(_DWORD *)(this + 17206064) = 0;
  *(_DWORD *)(this + 17206060) = 0;
  build_track_fringe_mesh((Path *)(this + 17206116), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17206236) = 0;
  *(_DWORD *)(this + 17206232) = 0;
  *(_DWORD *)(this + 17206228) = 0;
  v178 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206284), v178);
  initialize_slalom_path_template_pair((Path *)(this + 17206284), 32, 4u, (char *)1, texture_a);
  *(_DWORD *)(this + 17206308) = 0;
  *(_DWORD *)(this + 17206304) = 0;
  *(_DWORD *)(this + 17206300) = 0;
  v179 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206452), v179);
  mirror_path_template_pair_x((Path *)(this + 17206452), (Path *)(this + 17206284));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206476) = 0;
  *(_DWORD *)(this + 17206472) = 0;
  *(_DWORD *)(this + 17206468) = 0;
  build_track_fringe_mesh((Path *)(this + 17206284), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206404) = 0;
  *(_DWORD *)(this + 17206400) = 0;
  *(_DWORD *)(this + 17206396) = 0;
  build_track_fringe_mesh((Path *)(this + 17206452), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17206572) = 0;
  *(_DWORD *)(this + 17206568) = 0;
  *(_DWORD *)(this + 17206564) = 0;
  v180 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206620), v180);
  initialize_slalombig_path_template_pair((Path *)(this + 17206620), 32, 4u, (char *)1, texture_a);
  *(_DWORD *)(this + 17206644) = 0;
  *(_DWORD *)(this + 17206640) = 0;
  *(_DWORD *)(this + 17206636) = 0;
  v181 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206788), v181);
  mirror_path_template_pair_x((Path *)(this + 17206788), (Path *)(this + 17206620));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206812) = 0;
  *(_DWORD *)(this + 17206808) = 0;
  *(_DWORD *)(this + 17206804) = 0;
  build_track_fringe_mesh((Path *)(this + 17206620), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17206740) = 0;
  *(_DWORD *)(this + 17206736) = 0;
  *(_DWORD *)(this + 17206732) = 0;
  build_track_fringe_mesh((Path *)(this + 17206788), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17206908) = 0;
  *(_DWORD *)(this + 17206904) = 0;
  *(_DWORD *)(this + 17206900) = 0;
  v182 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17209644), v182);
  *(_DWORD *)&v379[4] = texture_a;
  initialize_slalomdouble_path_template_pair((Path *)(this + 17209644), 32, (char *)4, (char *)1);
  *(_DWORD *)(this + 17209668) = 0;
  *(_DWORD *)(this + 17209664) = 0;
  *(_DWORD *)(this + 17209660) = 0;
  v183 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17209812), v183);
  mirror_path_template_pair_x((Path *)(this + 17209812), (Path *)(this + 17209644));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17209836) = 0;
  *(_DWORD *)(this + 17209832) = 0;
  *(_DWORD *)(this + 17209828) = 0;
  build_track_fringe_mesh((Path *)(this + 17209644), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17209764) = 0;
  *(_DWORD *)(this + 17209760) = 0;
  *(_DWORD *)(this + 17209756) = 0;
  build_track_fringe_mesh((Path *)(this + 17209812), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17209932) = 0;
  *(_DWORD *)(this + 17209928) = 0;
  *(_DWORD *)(this + 17209924) = 0;
  v184 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17206956), v184);
  initialize_worm_path_template_pair((Path *)(this + 17206956), aObjectsWorld00_4);
  *(_DWORD *)(this + 17206980) = 0;
  *(_DWORD *)(this + 17206976) = 0;
  *(_DWORD *)(this + 17206972) = 0;
  v185 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207124), v185);
  mirror_path_template_pair_x((Path *)(this + 17207124), (Path *)(this + 17206956));
  *(_DWORD *)(this + 17207148) = 0;
  *(_DWORD *)(this + 17207144) = 0;
  *(_DWORD *)(this + 17207140) = 0;
  v186 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207052), v186);
  disable_object_rendering(*(_DWORD *)(this + 17207088));
  v187 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17207220), v187);
  disable_object_rendering(*(_DWORD *)(this + 17207256));
  *(_DWORD *)(*(_DWORD *)(this + 17206992) + 20) = 8;
  *(_DWORD *)(*(_DWORD *)(this + 17207160) + 20) = 8;
  v188 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17208300), v188);
  initialize_sweep_path_template_pair((Path *)(this + 17208300), 1082130432, (char *)4, (char *)1);
  *(_DWORD *)(this + 17208324) = 0;
  *(_DWORD *)(this + 17208320) = 0;
  *(_DWORD *)(this + 17208316) = 0;
  v189 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17208468), v189);
  mirror_path_template_pair_x((Path *)(this + 17208468), (Path *)(this + 17208300));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208492) = 0;
  *(_DWORD *)(this + 17208488) = 0;
  *(_DWORD *)(this + 17208484) = 0;
  build_track_fringe_mesh((Path *)(this + 17208300), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208420) = 0;
  *(_DWORD *)(this + 17208416) = 0;
  *(_DWORD *)(this + 17208412) = 0;
  build_track_fringe_mesh((Path *)(this + 17208468), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17208588) = 0;
  *(_DWORD *)(this + 17208584) = 0;
  *(_DWORD *)(this + 17208580) = 0;
  v190 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17203932), v190);
  initialize_cage2_path_template_pair((Path *)(this + 17203932), 3, texture_a, texture_b);
  *(_DWORD *)(this + 17203956) = 0;
  *(_DWORD *)(this + 17203952) = 0;
  *(_DWORD *)(this + 17203948) = 0;
  v191 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17204100), v191);
  mirror_path_template_pair_x((Path *)(this + 17204100), (Path *)(this + 17203932));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17204124) = 0;
  *(_DWORD *)(this + 17204120) = 0;
  *(_DWORD *)(this + 17204116) = 0;
  build_track_fringe_mesh((Path *)(this + 17203932), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17204052) = 0;
  *(_DWORD *)(this + 17204048) = 0;
  *(_DWORD *)(this + 17204044) = 0;
  build_track_fringe_mesh((Path *)(this + 17204100), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17204220) = 0;
  *(_DWORD *)(this + 17204216) = 0;
  *(_DWORD *)(this + 17204212) = 0;
  v192 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17209980), v192);
  initialize_p_path_template_pair(
    (Path *)(this + 17209980),
    0,
    0x40800000u,
    COERCE_FLOAT(3),
    0.5,
    -1071644672,
    (char *)0xE,
    texture_a);
  *(_DWORD *)(this + 17210004) = 0;
  *(_DWORD *)(this + 17210000) = 0;
  *(_DWORD *)(this + 17209996) = 0;
  v193 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210148), v193);
  mirror_path_template_pair_x((Path *)(this + 17210148), (Path *)(this + 17209980));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210172) = 0;
  *(_DWORD *)(this + 17210168) = 0;
  *(_DWORD *)(this + 17210164) = 0;
  build_track_fringe_mesh((Path *)(this + 17209980), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210100) = 0;
  *(_DWORD *)(this + 17210096) = 0;
  *(_DWORD *)(this + 17210092) = 0;
  build_track_fringe_mesh((Path *)(this + 17210148), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17210268) = 0;
  *(_DWORD *)(this + 17210264) = 0;
  *(_DWORD *)(this + 17210260) = 0;
  v194 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210316), v194);
  initialize_p_path_template_pair(
    (Path *)(this + 17210316),
    1,
    0x40800000u,
    COERCE_FLOAT(3),
    -2.5,
    1075838976,
    (char *)0xE,
    texture_a);
  *(_DWORD *)(this + 17210340) = 0;
  *(_DWORD *)(this + 17210336) = 0;
  *(_DWORD *)(this + 17210332) = 0;
  v195 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210484), v195);
  mirror_path_template_pair_x((Path *)(this + 17210484), (Path *)(this + 17210316));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210508) = 0;
  *(_DWORD *)(this + 17210504) = 0;
  *(_DWORD *)(this + 17210500) = 0;
  build_track_fringe_mesh((Path *)(this + 17210316), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210436) = 0;
  *(_DWORD *)(this + 17210432) = 0;
  *(_DWORD *)(this + 17210428) = 0;
  build_track_fringe_mesh((Path *)(this + 17210484), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17210604) = 0;
  *(_DWORD *)(this + 17210600) = 0;
  *(_DWORD *)(this + 17210596) = 0;
  v196 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210652), v196);
  initialize_p_path_template_pair(
    (Path *)(this + 17210652),
    2,
    0x40800000u,
    COERCE_FLOAT(3),
    2.5,
    1056964608,
    (char *)0xE,
    texture_a);
  *(_DWORD *)(this + 17210676) = 0;
  *(_DWORD *)(this + 17210672) = 0;
  *(_DWORD *)(this + 17210668) = 0;
  v197 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17210820), v197);
  mirror_path_template_pair_x((Path *)(this + 17210820), (Path *)(this + 17210652));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210844) = 0;
  *(_DWORD *)(this + 17210840) = 0;
  *(_DWORD *)(this + 17210836) = 0;
  build_track_fringe_mesh((Path *)(this + 17210652), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17210772) = 0;
  *(_DWORD *)(this + 17210768) = 0;
  *(_DWORD *)(this + 17210764) = 0;
  build_track_fringe_mesh((Path *)(this + 17210820), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17210940) = 0;
  *(_DWORD *)(this + 17210936) = 0;
  *(_DWORD *)(this + 17210932) = 0;
  v198 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17208636), v198);
  initialize_snake_path_template_pair((Path *)(this + 17208636), 0x40000000, (char *)4, (char *)1);
  *(_DWORD *)(this + 17208660) = 0;
  *(_DWORD *)(this + 17208656) = 0;
  *(_DWORD *)(this + 17208652) = 0;
  v199 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17208804), v199);
  mirror_path_template_pair_x((Path *)(this + 17208804), (Path *)(this + 17208636));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208828) = 0;
  *(_DWORD *)(this + 17208824) = 0;
  *(_DWORD *)(this + 17208820) = 0;
  build_track_fringe_mesh((Path *)(this + 17208636), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17208756) = 0;
  *(_DWORD *)(this + 17208752) = 0;
  *(_DWORD *)(this + 17208748) = 0;
  build_track_fringe_mesh((Path *)(this + 17208804), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17208924) = 0;
  *(_DWORD *)(this + 17208920) = 0;
  *(_DWORD *)(this + 17208916) = 0;
  v200 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214684), v200);
  initialize_toad_path_template_pair((Path *)(this + 17214684), 1, texture_a, aObjectsWorld00);
  *(_DWORD *)(this + 17214708) = 0;
  *(_DWORD *)(this + 17214704) = 0;
  *(_DWORD *)(this + 17214700) = 0;
  v201 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17214852), v201);
  mirror_path_template_pair_x((Path *)(this + 17214852), (Path *)(this + 17214684));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214876) = 0;
  *(_DWORD *)(this + 17214872) = 0;
  *(_DWORD *)(this + 17214868) = 0;
  build_track_fringe_mesh((Path *)(this + 17214684), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17214804) = 0;
  *(_DWORD *)(this + 17214800) = 0;
  *(_DWORD *)(this + 17214796) = 0;
  build_track_fringe_mesh((Path *)(this + 17214852), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17214972) = 0;
  *(_DWORD *)(this + 17214968) = 0;
  *(_DWORD *)(this + 17214964) = 0;
  v202 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215020), v202);
  initialize_toad_path_template_pair((Path *)(this + 17215020), 0, texture_a, aObjectsWorld00);
  *(_DWORD *)(this + 17215044) = 0;
  *(_DWORD *)(this + 17215040) = 0;
  *(_DWORD *)(this + 17215036) = 0;
  v203 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215188), v203);
  mirror_path_template_pair_x((Path *)(this + 17215188), (Path *)(this + 17215020));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215212) = 0;
  *(_DWORD *)(this + 17215208) = 0;
  *(_DWORD *)(this + 17215204) = 0;
  build_track_fringe_mesh((Path *)(this + 17215020), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215140) = 0;
  *(_DWORD *)(this + 17215136) = 0;
  *(_DWORD *)(this + 17215132) = 0;
  build_track_fringe_mesh((Path *)(this + 17215188), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17215308) = 0;
  *(_DWORD *)(this + 17215304) = 0;
  *(_DWORD *)(this + 17215300) = 0;
  v204 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215356), v204);
  initialize_toad_path_template_pair((Path *)(this + 17215356), 1, texture_a, aObjectsWorld00);
  *(_DWORD *)(this + 17215380) = 0;
  *(_DWORD *)(this + 17215376) = 0;
  *(_DWORD *)(this + 17215372) = 0;
  v205 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215524), v205);
  mirror_path_template_pair_x((Path *)(this + 17215524), (Path *)(this + 17215356));
  *(_DWORD *)&v379[12] = -1082130432;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215548) = 0;
  *(_DWORD *)(this + 17215544) = 0;
  *(_DWORD *)(this + 17215540) = 0;
  build_track_fringe_mesh((Path *)(this + 17215356), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 1065353216;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215476) = 0;
  *(_DWORD *)(this + 17215472) = 0;
  *(_DWORD *)(this + 17215468) = 0;
  build_track_fringe_mesh((Path *)(this + 17215524), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17215644) = 0;
  *(_DWORD *)(this + 17215640) = 0;
  *(_DWORD *)(this + 17215636) = 0;
  v206 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215692), v206);
  initialize_toad_path_template_pair((Path *)(this + 17215692), 0, texture_a, aObjectsWorld00);
  *(_DWORD *)(this + 17215716) = 0;
  *(_DWORD *)(this + 17215712) = 0;
  *(_DWORD *)(this + 17215708) = 0;
  v207 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17215860), v207);
  mirror_path_template_pair_x((Path *)(this + 17215860), (Path *)(this + 17215692));
  *(_DWORD *)&v379[12] = 1065353216;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215884) = 0;
  *(_DWORD *)(this + 17215880) = 0;
  *(_DWORD *)(this + 17215876) = 0;
  build_track_fringe_mesh((Path *)(this + 17215692), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = -1082130432;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17215812) = 0;
  *(_DWORD *)(this + 17215808) = 0;
  *(_DWORD *)(this + 17215804) = 0;
  build_track_fringe_mesh((Path *)(this + 17215860), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17215980) = 0;
  *(_DWORD *)(this + 17215976) = 0;
  *(_DWORD *)(this + 17215972) = 0;
  noop_this_constructor(&v379[40]);
  store_color4f((tColour *)&v379[40], 1.0, 1.0, 1.0, 0.60000002);
  v208 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216028), v208);
  initialize_looptheloop_path_template_pair((Path *)(this + 17216028), 6.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17216052) = 0;
  *(_DWORD *)(this + 17216048) = 0;
  *(_DWORD *)(this + 17216044) = 0;
  v209 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216196), v209);
  mirror_path_template_pair_x((Path *)(this + 17216196), (Path *)(this + 17216028));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17216220) = 0;
  *(_DWORD *)(this + 17216216) = 0;
  *(_DWORD *)(this + 17216212) = 0;
  build_track_fringe_mesh((Path *)(this + 17216028), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17216148) = 0;
  *(_DWORD *)(this + 17216144) = 0;
  *(_DWORD *)(this + 17216140) = 0;
  build_track_fringe_mesh((Path *)(this + 17216196), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17216316) = 0;
  *(_DWORD *)(this + 17216312) = 0;
  *(_DWORD *)(this + 17216308) = 0;
  v210 = *(_DWORD *)(this + 17198928);
  v211 = *(_DWORD *)(this + 17216232);
  *(_DWORD *)(this + 17199052) = *(_DWORD *)(this + 17216064);
  v212 = *(_DWORD *)(this + 17199096);
  *(_DWORD *)(this + 17199056) = v210;
  *(_DWORD *)(this + 17199220) = v211;
  *(_DWORD *)(this + 17199224) = v212;
  v213 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216364), v213);
  initialize_looptheloop_path_template_pair((Path *)(this + 17216364), 6.0, 2, (char *)1, texture_a);
  *(_DWORD *)(this + 17216388) = 0;
  *(_DWORD *)(this + 17216384) = 0;
  *(_DWORD *)(this + 17216380) = 0;
  v214 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216532), v214);
  mirror_path_template_pair_x((Path *)(this + 17216532), (Path *)(this + 17216364));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17216556) = 0;
  *(_DWORD *)(this + 17216552) = 0;
  *(_DWORD *)(this + 17216548) = 0;
  build_track_fringe_mesh((Path *)(this + 17216364), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17216484) = 0;
  *(_DWORD *)(this + 17216480) = 0;
  *(_DWORD *)(this + 17216476) = 0;
  build_track_fringe_mesh((Path *)(this + 17216532), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17216652) = 0;
  *(_DWORD *)(this + 17216648) = 0;
  *(_DWORD *)(this + 17216644) = 0;
  v215 = *(_DWORD *)(this + 17199264);
  v216 = *(_DWORD *)(this + 17216568);
  *(_DWORD *)(this + 17199388) = *(_DWORD *)(this + 17216400);
  *(_DWORD *)(this + 17199560) = *(_DWORD *)(this + 17199432);
  *(_DWORD *)(this + 17199392) = v215;
  *(_DWORD *)(this + 17199556) = v216;
  v217 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216700), v217);
  initialize_looptheloop_path_template_pair((Path *)(this + 17216700), 8.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17216724) = 0;
  *(_DWORD *)(this + 17216720) = 0;
  *(_DWORD *)(this + 17216716) = 0;
  v218 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17216868), v218);
  mirror_path_template_pair_x((Path *)(this + 17216868), (Path *)(this + 17216700));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(this + 17216892) = 0;
  *(_DWORD *)(this + 17216888) = 0;
  *(_DWORD *)(this + 17216884) = 0;
  build_track_fringe_mesh((Path *)(this + 17216700), aObjectsUnivers_1, *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17216820) = 0;
  *(_DWORD *)(this + 17216816) = 0;
  *(_DWORD *)(this + 17216812) = 0;
  build_track_fringe_mesh((Path *)(this + 17216868), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17216988) = 0;
  *(_DWORD *)(this + 17216984) = 0;
  *(_DWORD *)(this + 17216980) = 0;
  v219 = *(_DWORD *)(this + 17199600);
  v220 = *(_DWORD *)(this + 17216904);
  *(_DWORD *)(this + 17199724) = *(_DWORD *)(this + 17216736);
  *(_DWORD *)(this + 17199728) = v219;
  *(_DWORD *)(this + 17199892) = v220;
  *(_DWORD *)(this + 17199896) = *(_DWORD *)(this + 17199768);
  v221 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218044), v221);
  initialize_looptheloopw_path_template_pair((Path *)(this + 17218044), 8.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17218068) = 0;
  *(_DWORD *)(this + 17218064) = 0;
  *(_DWORD *)(this + 17218060) = 0;
  v222 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218212), v222);
  mirror_path_template_pair_x((Path *)(this + 17218212), (Path *)(this + 17218044));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218236) = 0;
  *(_DWORD *)(this + 17218232) = 0;
  *(_DWORD *)(this + 17218228) = 0;
  build_track_fringe_mesh((Path *)(this + 17218044), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218164) = 0;
  *(_DWORD *)(this + 17218160) = 0;
  *(_DWORD *)(this + 17218156) = 0;
  build_track_fringe_mesh((Path *)(this + 17218212), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17218332) = 0;
  *(_DWORD *)(this + 17218328) = 0;
  *(_DWORD *)(this + 17218324) = 0;
  *(_DWORD *)(this + 17201068) = *(_DWORD *)(this + 17218080);
  *(_DWORD *)(this + 17201072) = *(_DWORD *)(this + 17200944);
  *(_DWORD *)(this + 17201236) = *(_DWORD *)(this + 17218248);
  *(_DWORD *)(this + 17201240) = *(_DWORD *)(this + 17201112);
  v223 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217036), v223);
  initialize_looptheloop_path_template_pair((Path *)(this + 17217036), 3.0, 2, (char *)1, texture_a);
  *(_DWORD *)(this + 17217060) = 0;
  *(_DWORD *)(this + 17217056) = 0;
  *(_DWORD *)(this + 17217052) = 0;
  v224 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217204), v224);
  mirror_path_template_pair_x((Path *)(this + 17217204), (Path *)(this + 17217036));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217228) = 0;
  *(_DWORD *)(this + 17217224) = 0;
  *(_DWORD *)(this + 17217220) = 0;
  build_track_fringe_mesh((Path *)(this + 17217036), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217156) = 0;
  *(_DWORD *)(this + 17217152) = 0;
  *(_DWORD *)(this + 17217148) = 0;
  build_track_fringe_mesh((Path *)(this + 17217204), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17217324) = 0;
  *(_DWORD *)(this + 17217320) = 0;
  *(_DWORD *)(this + 17217316) = 0;
  *(_DWORD *)(this + 17200060) = *(_DWORD *)(this + 17217072);
  *(_DWORD *)(this + 17200064) = *(_DWORD *)(this + 17199936);
  *(_DWORD *)(this + 17200228) = *(_DWORD *)(this + 17217240);
  *(_DWORD *)(this + 17200232) = *(_DWORD *)(this + 17200104);
  v225 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217372), v225);
  initialize_looptheloop_path_template_pair((Path *)(this + 17217372), 3.0, 3, (char *)1, texture_a);
  *(_DWORD *)(this + 17217396) = 0;
  *(_DWORD *)(this + 17217392) = 0;
  *(_DWORD *)(this + 17217388) = 0;
  v226 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217540), v226);
  mirror_path_template_pair_x((Path *)(this + 17217540), (Path *)(this + 17217372));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217564) = 0;
  *(_DWORD *)(this + 17217560) = 0;
  *(_DWORD *)(this + 17217556) = 0;
  build_track_fringe_mesh((Path *)(this + 17217372), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217492) = 0;
  *(_DWORD *)(this + 17217488) = 0;
  *(_DWORD *)(this + 17217484) = 0;
  build_track_fringe_mesh((Path *)(this + 17217540), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17217660) = 0;
  *(_DWORD *)(this + 17217656) = 0;
  *(_DWORD *)(this + 17217652) = 0;
  *(_DWORD *)(this + 17200396) = *(_DWORD *)(this + 17217408);
  *(_DWORD *)(this + 17200400) = *(_DWORD *)(this + 17200272);
  *(_DWORD *)(this + 17200564) = *(_DWORD *)(this + 17217576);
  *(_DWORD *)(this + 17200568) = *(_DWORD *)(this + 17200440);
  v227 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217708), v227);
  initialize_looptheloop_path_template_pair((Path *)(this + 17217708), 3.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17217732) = 0;
  *(_DWORD *)(this + 17217728) = 0;
  *(_DWORD *)(this + 17217724) = 0;
  v228 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17217876), v228);
  mirror_path_template_pair_x((Path *)(this + 17217876), (Path *)(this + 17217708));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217900) = 0;
  *(_DWORD *)(this + 17217896) = 0;
  *(_DWORD *)(this + 17217892) = 0;
  build_track_fringe_mesh((Path *)(this + 17217708), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17217828) = 0;
  *(_DWORD *)(this + 17217824) = 0;
  *(_DWORD *)(this + 17217820) = 0;
  build_track_fringe_mesh((Path *)(this + 17217876), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17217996) = 0;
  *(_DWORD *)(this + 17217992) = 0;
  *(_DWORD *)(this + 17217988) = 0;
  *(_DWORD *)(this + 17200732) = *(_DWORD *)(this + 17217744);
  *(_DWORD *)(this + 17200736) = *(_DWORD *)(this + 17200608);
  *(_DWORD *)(this + 17200900) = *(_DWORD *)(this + 17217912);
  *(_DWORD *)(this + 17200904) = *(_DWORD *)(this + 17200776);
  v229 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218380), v229);
  initialize_loopbow_path_template_pair((Path *)(this + 17218380), 6.0, 4u, (char *)1, texture_a);
  *(_DWORD *)(this + 17218404) = 0;
  *(_DWORD *)(this + 17218400) = 0;
  *(_DWORD *)(this + 17218396) = 0;
  v230 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218548), v230);
  mirror_path_template_pair_x((Path *)(this + 17218548), (Path *)(this + 17218380));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218572) = 0;
  *(_DWORD *)(this + 17218568) = 0;
  *(_DWORD *)(this + 17218564) = 0;
  build_track_fringe_mesh((Path *)(this + 17218380), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218500) = 0;
  *(_DWORD *)(this + 17218496) = 0;
  *(_DWORD *)(this + 17218492) = 0;
  build_track_fringe_mesh((Path *)(this + 17218548), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17218668) = 0;
  *(_DWORD *)(this + 17218664) = 0;
  *(_DWORD *)(this + 17218660) = 0;
  *(_DWORD *)(this + 17201404) = *(_DWORD *)(this + 17218416);
  *(_DWORD *)(this + 17201408) = *(_DWORD *)(this + 17201280);
  *(_DWORD *)(this + 17201572) = *(_DWORD *)(this + 17218584);
  *(_DWORD *)(this + 17201576) = *(_DWORD *)(this + 17201448);
  v231 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219724), v231);
  *(_DWORD *)&v379[4] = texture_a;
  initialize_invert_path_template_pair((Path *)(this + 17219724), 1086324736, (char *)8, (char *)1);
  *(_DWORD *)(this + 17219748) = 0;
  *(_DWORD *)(this + 17219744) = 0;
  *(_DWORD *)(this + 17219740) = 0;
  v232 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219892), v232);
  mirror_path_template_pair_x((Path *)(this + 17219892), (Path *)(this + 17219724));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17219916) = 0;
  *(_DWORD *)(this + 17219912) = 0;
  *(_DWORD *)(this + 17219908) = 0;
  build_track_fringe_mesh((Path *)(this + 17219724), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17219844) = 0;
  *(_DWORD *)(this + 17219840) = 0;
  *(_DWORD *)(this + 17219836) = 0;
  build_track_fringe_mesh((Path *)(this + 17219892), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17220012) = 0;
  *(_DWORD *)(this + 17220008) = 0;
  *(_DWORD *)(this + 17220004) = 0;
  *(_DWORD *)(this + 17212828) = *(_DWORD *)(this + 17219760);
  *(_DWORD *)(this + 17212832) = *(_DWORD *)(this + 17212704);
  *(_DWORD *)(this + 17212996) = *(_DWORD *)(this + 17219928);
  *(_DWORD *)(this + 17213000) = *(_DWORD *)(this + 17212872);
  v233 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218716), v233);
  initialize_loopout_path_template_pair((Path *)(this + 17218716), 3.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17218740) = 0;
  *(_DWORD *)(this + 17218736) = 0;
  *(_DWORD *)(this + 17218732) = 0;
  v234 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17218884), v234);
  mirror_path_template_pair_x((Path *)(this + 17218884), (Path *)(this + 17218716));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218908) = 0;
  *(_DWORD *)(this + 17218904) = 0;
  *(_DWORD *)(this + 17218900) = 0;
  build_track_fringe_mesh((Path *)(this + 17218716), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17218836) = 0;
  *(_DWORD *)(this + 17218832) = 0;
  *(_DWORD *)(this + 17218828) = 0;
  build_track_fringe_mesh((Path *)(this + 17218884), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17219004) = 0;
  *(_DWORD *)(this + 17219000) = 0;
  *(_DWORD *)(this + 17218996) = 0;
  *(_DWORD *)(this + 17207452) = *(_DWORD *)(this + 17218752);
  *(_DWORD *)(this + 17207456) = *(_DWORD *)(this + 17207328);
  *(_DWORD *)(this + 17207620) = *(_DWORD *)(this + 17218920);
  *(_DWORD *)(this + 17207624) = *(_DWORD *)(this + 17207496);
  v235 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219388), v235);
  initialize_loopout_path_template_pair((Path *)(this + 17219388), 5.0, 4, (char *)1, texture_a);
  *(_DWORD *)(this + 17219412) = 0;
  *(_DWORD *)(this + 17219408) = 0;
  *(_DWORD *)(this + 17219404) = 0;
  v236 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219556), v236);
  mirror_path_template_pair_x((Path *)(this + 17219556), (Path *)(this + 17219388));
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  *(_DWORD *)(this + 17219580) = 0;
  *(_DWORD *)(this + 17219576) = 0;
  *(_DWORD *)(this + 17219572) = 0;
  build_track_fringe_mesh((Path *)(this + 17219388), *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)(this + 17219508) = 0;
  *(_DWORD *)(this + 17219504) = 0;
  *(_DWORD *)(this + 17219500) = 0;
  build_track_fringe_mesh((Path *)(this + 17219556), aObjectsUnivers_1, 0.0);
  *(_DWORD *)(this + 17219676) = 0;
  *(_DWORD *)(this + 17219672) = 0;
  *(_DWORD *)(this + 17219668) = 0;
  *(_DWORD *)(this + 17208124) = *(_DWORD *)(this + 17219424);
  *(_DWORD *)(this + 17208128) = *(_DWORD *)(this + 17208000);
  *(_DWORD *)(this + 17208292) = *(_DWORD *)(this + 17219592);
  *(_DWORD *)(this + 17208296) = *(_DWORD *)(this + 17208168);
  v237 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219052), v237);
  initialize_loopout_path_template_pair((Path *)(this + 17219052), 3.0, 3, (char *)1, texture_a);
  zero_vector3((_DWORD *)(this + 17219068));
  v238 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17219220), v238);
  mirror_path_template_pair_x((Path *)(this + 17219220), (Path *)(this + 17219052));
  zero_vector3((_DWORD *)(this + 17219236));
  build_track_fringe_mesh((Path *)(this + 17219052), aObjectsUnivers_1, 0.0);
  zero_vector3((_DWORD *)(this + 17219164));
  build_track_fringe_mesh((Path *)(this + 17219220), aObjectsUnivers_1, 0.0);
  zero_vector3((_DWORD *)(this + 17219332));
  v239 = *(_DWORD *)(this + 17219088);
  *(_DWORD *)&v379[12] = aPathGeneration_0;
  *(_DWORD *)(this + 17207788) = v239;
  *(_DWORD *)(this + 17207792) = *(_DWORD *)(this + 17207664);
  *(_DWORD *)(this + 17207956) = *(_DWORD *)(this + 17219256);
  *(_DWORD *)(this + 17207960) = *(_DWORD *)(this + 17207832);
  debug_report_stub();
  v240 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43284A + this + 2), v240);
  case_insensitive_substring = find_case_insensitive_substring(aTest, *(char **)(this + 298496));
  if ( case_insensitive_substring )
  {
    v242 = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring);
    v243 = v242[1];
    v244 = v242 + 1;
    v245 = ArgList;
    if ( v243 != 46 )
    {
      v246 = v244 - ArgList;
      do
      {
        *v245 = v243;
        v243 = (v245++)[v246 + 1];
      }
      while ( v243 != 46 );
    }
    *v245 = 46;
    v247 = v245 + 1;
    *v247 = 120;
    v247[1] = 0;
  }
  else
  {
    rstrcpy_checked_ascii(ArgList, aTurboBase000X);
  }
  load_x_animation_clip((DirectXLoader *)(this + 298496), ArgList, *(Object **)((char *)&loc_432870 + this));
  v248 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4326FF + this + 1), v248);
  load_x_animation_clip((DirectXLoader *)(this + 298496), ArgList, *(Object **)((char *)&loc_432720 + this + 4));
  v249 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4328C8 + this + 4), v249);
  load_x_animation_clip((DirectXLoader *)(this + 298496), mesh_name, *(Object **)((char *)&loc_4328F0 + this));
  v250 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43294C + this), v250);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboBobalong0, *(Object **)((char *)&loc_432970 + this));
  v251 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4329CC + this), v251);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboLookbackl, *(Object **)((char *)&loc_4329EE + this + 2));
  v252 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432A4A + this + 2), v252);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboLookbackr, *(Object **)((char *)&loc_432A6D + this + 3));
  v253 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432ACB + this + 1), v253);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboFall000X, *(Object **)((char *)&loc_432AEF + this + 1));
  v254 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432B49 + this + 3), v254);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboDamaged00, *(Object **)((char *)&loc_432B6E + this + 2));
  v255 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432BCA + this + 2), v255);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboIntoshell, *(Object **)((char *)&loc_432BEF + this + 1));
  v256 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432C48 + this + 4), v256);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboSkidstop0, *(Object **)((char *)&loc_432C6D + this + 3));
  v257 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432CCA + this + 2), v257);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aTurboTalk000X, *(Object **)((char *)&loc_432CE9 + this + 7));
  v258 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433D46 + this + 6), v258);
  load_x_mesh((DirectXLoader *)(this + 298496), aTurbohotspotsX, *(Object **)((char *)&loc_433D6F + this + 1), 2);
  build_snail_hotspots((int)&loc_4326FF + this + 1);
  *(_DWORD *)&v379[36] = 10;
  *(_DWORD *)&v379[32] = (char *)&loc_432870 + this;
  do
  {
    v259 = *(Object ***)&v379[32];
    *(_DWORD *)&v379[12] = 0;
    *(_DWORD *)(**(_DWORD **)&v379[32] + 16) |= 4u;
    apply_object_toon(*v259, *(int32_t *)&v379[12]);
    v260 = **(_DWORD **)&v379[32];
    *(_DWORD *)&v379[32] += 128;
    v261 = *(_DWORD *)&v379[32];
    *(_DWORD *)(v260 + 128) = 0;
    *(_DWORD *)(*(_DWORD *)(v261 - 128) + 132) = 0;
    v262 = *(_DWORD *)(v261 - 128);
    v263 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v262 + 136) = 0;
    *(_DWORD *)&v379[36] = v263;
  }
  while ( !v60 );
  v264 = *(_DWORD *)((char *)&loc_432720 + this + 4);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v264 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_432720 + this + 4), *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432720 + this + 4) + 136) = 0;
  v265 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4338DE + this + 2), v265);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aJetpackBase000, *(Object **)((char *)&loc_433902 + this + 2));
  v266 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433A2C + this + 4), v266);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aJetpackBase000, *(Object **)((char *)&loc_433A54 + this));
  v267 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433AB0 + this), v267);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aJetpackDraw000, *(Object **)((char *)&loc_433AD4 + this));
  *(_DWORD *)&v379[36] = 2;
  *(_DWORD *)&v379[32] = (char *)&loc_433A54 + this;
  do
  {
    v268 = *(Object ***)&v379[32];
    *(_DWORD *)&v379[12] = 0;
    *(_DWORD *)(**(_DWORD **)&v379[32] + 16) |= 4u;
    apply_object_toon(*v268, *(int32_t *)&v379[12]);
    v269 = **(_DWORD **)&v379[32];
    *(_DWORD *)&v379[32] += 128;
    v270 = *(_DWORD *)&v379[32];
    *(_DWORD *)(v269 + 128) = 0;
    *(_DWORD *)(*(_DWORD *)(v270 - 128) + 132) = 0;
    v271 = *(_DWORD *)(v270 - 128);
    v272 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v271 + 136) = 0;
    *(_DWORD *)&v379[36] = v272;
  }
  while ( !v60 );
  v273 = *(_DWORD *)((char *)&loc_433902 + this + 2);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v273 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_433902 + this + 2), *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433902 + this + 2) + 136) = 0;
  v274 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&byte_432D4C[this], v274);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterleftBas, *(Object **)((char *)&loc_432D6D + this + 3));
  v275 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432E9A + this + 2), v275);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterleftBas, *(Object **)((char *)&loc_432EBF + this + 1));
  v276 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432F1A + this + 2), v276);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterleftDra, *(Object **)((char *)&loc_432F40 + this));
  v277 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_432F9B + this + 1), v277);
  load_x_animation_clip(
    (DirectXLoader *)(this + 298496),
    aBlasterleftFir,
    *(Object **)((char *)find_registered_sound_sample_id_by_name + this));
  v278 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43301C + this), v278);
  load_x_animation_clip(
    (DirectXLoader *)(this + 298496),
    aLaserleftBase0,
    *(Object **)((char *)get_authored_view_height + this));
  v279 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43309C + this), v279);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aLaserleftDraw0, *(Object **)((char *)&loc_4330BF + this + 1));
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)&loc_432EBF + this + 1;
  do
  {
    v280 = *(Object ***)&v379[32];
    *(_DWORD *)&v379[12] = 0;
    *(_DWORD *)(**(_DWORD **)&v379[32] + 16) |= 4u;
    apply_object_toon(*v280, *(int32_t *)&v379[12]);
    v281 = **(_DWORD **)&v379[32];
    *(_DWORD *)&v379[32] += 128;
    v282 = *(_DWORD *)&v379[32];
    *(_DWORD *)(v281 + 128) = 0;
    *(_DWORD *)(*(_DWORD *)(v282 - 128) + 132) = 0;
    v283 = *(_DWORD *)(v282 - 128);
    v284 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v283 + 136) = 0;
    *(_DWORD *)&v379[36] = v284;
  }
  while ( !v60 );
  v285 = *(_DWORD *)((char *)&loc_432D6D + this + 3);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v285 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_432D6D + this + 3), *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_432D6D + this + 3) + 136) = 0;
  v286 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433127 + this + 1), v286);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterrightBa, *(Object **)((char *)&loc_43314C + this));
  v287 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433275 + this + 3), v287);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterrightBa, *(Object **)((char *)&loc_43329B + this + 1));
  v288 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4332F7 + this + 1), v288);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterrightDr, *(Object **)((char *)&loc_43331C + this));
  v289 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433378 + this), v289);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlasterrightFi, *(Object **)((char *)&loc_43339A + this + 2));
  v290 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4333F8 + this), v290);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aLaserrightBase, *(Object **)((char *)&loc_433417 + this + 5));
  v291 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433475 + this + 3), v291);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aLaserrightDraw, *(Object **)((char *)&loc_433499 + this + 3));
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)&loc_43329B + this + 1;
  do
  {
    v292 = *(Object ***)&v379[32];
    *(_DWORD *)&v379[12] = 0;
    *(_DWORD *)(**(_DWORD **)&v379[32] + 16) |= 4u;
    apply_object_toon(*v292, *(int32_t *)&v379[12]);
    v293 = **(_DWORD **)&v379[32];
    *(_DWORD *)&v379[32] += 128;
    v294 = *(_DWORD *)&v379[32];
    *(_DWORD *)(v293 + 128) = 0;
    *(_DWORD *)(*(_DWORD *)(v294 - 128) + 132) = 0;
    v295 = *(_DWORD *)(v294 - 128);
    v296 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v295 + 136) = 0;
    *(_DWORD *)&v379[36] = v296;
  }
  while ( !v60 );
  v297 = *(_DWORD *)((char *)&loc_43314C + this);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v297 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_43314C + this), *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + this) + 136) = 0;
  v298 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433504 + this), v298);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlastertopBase, *(Object **)((char *)&loc_433523 + this + 5));
  v299 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433654 + this), v299);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlastertopBase, *(Object **)((char *)&loc_433677 + this + 1));
  v300 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4336D0 + this + 4), v300);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlastertopDraw, *(Object **)((char *)&loc_4336F6 + this + 2));
  v301 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433751 + this + 3), v301);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aBlastertopFire, *(Object **)((char *)&loc_433777 + this + 1));
  v302 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4337D3 + this + 1), v302);
  load_x_animation_clip((DirectXLoader *)(this + 298496), aRocketlauncher, *(Object **)((char *)&loc_4337F6 + this + 2));
  v303 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433853 + this + 1), v303);
  load_x_animation_clip(
    (DirectXLoader *)(this + 298496),
    aRocketlauncher_0,
    *(Object **)((char *)&loc_433877 + this + 1));
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)&loc_433677 + this + 1;
  do
  {
    v304 = *(Object ***)&v379[32];
    *(_DWORD *)&v379[12] = 0;
    *(_DWORD *)(**(_DWORD **)&v379[32] + 16) |= 4u;
    apply_object_toon(*v304, *(int32_t *)&v379[12]);
    v305 = **(_DWORD **)&v379[32];
    *(_DWORD *)&v379[32] += 128;
    v306 = *(_DWORD *)&v379[32];
    *(_DWORD *)(v305 + 128) = 0;
    *(_DWORD *)(*(_DWORD *)(v306 - 128) + 132) = 0;
    v307 = *(_DWORD *)(v306 - 128);
    v308 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    *(_DWORD *)(v307 + 136) = 0;
    *(_DWORD *)&v379[36] = v308;
  }
  while ( !v60 );
  v309 = *(_DWORD *)((char *)&loc_433523 + this + 5);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v309 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_433523 + this + 5), *(int32_t *)&v379[12]);
  v310 = *(_DWORD *)((char *)&loc_433523 + this + 5);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboTga_0;
  *(_DWORD *)(v310 + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433523 + this + 5) + 136) = 0;
  texture_ref = get_or_create_texture_ref(
                  &g_texture_refs,
                  *(char **)&v379[4],
                  *(int32_t *)&v379[8],
                  *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboDam;
  *(_DWORD *)((char *)&loc_434037 + this + 5) = texture_ref;
  v312 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboInv;
  *(_DWORD *)((char *)&loc_43403D + this + 3) = v312;
  *(_DWORD *)((char *)&loc_434042 + this + 2) = get_or_create_texture_ref(
                                                  &g_texture_refs,
                                                  *(char **)&v379[4],
                                                  *(int32_t *)&v379[8],
                                                  *(int16_t *)&v379[12]);
  v313 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433F94 + this), v313);
  load_x_mesh((DirectXLoader *)(this + 298496), aInvincibleBase, *(Object **)((char *)&loc_433FB8 + this), 1);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433FB8 + this) + 16) &= ~0x100000u;
  v314 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4302E3 + this + 1), v314);
  load_x_mesh((DirectXLoader *)(this + 298496), aRocketBase000X, *(Object **)((char *)&loc_430306 + this + 2), 1);
  v315 = (char *)&loc_43026E + this + 2;
  *(_DWORD *)&v379[36] = 12;
  do
  {
    v316 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v315 - 36), v316);
    *(_DWORD *)(*(_DWORD *)v315 + 16) |= 0x100004u;
    *(_DWORD *)(*(_DWORD *)v315 + 20) = 9;
    load_object_definition(aObjectsVapourl, *(Object **)v315);
    initialize_vapour((Vapour *)(v315 - 36), *(Object **)v315, 0.16);
    set_bod_object((BodBase *)(v315 + 116), *(Object **)((char *)&loc_430306 + this + 2));
    v315 += 744;
    --*(_DWORD *)&v379[36];
  }
  while ( *(_DWORD *)&v379[36] );
  v317 = get_or_create_texture_ref(&g_texture_refs, aObjectsVapourl_0, 0, 0);
  flags = v317->flags;
  *(_WORD *)&v379[12] = 0;
  BYTE1(flags) |= 4u;
  *(_DWORD *)&v379[8] = 0;
  v317->flags = flags;
  v319 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_4, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v320 = v319->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v319->flags = v320 | 0x1403;
  v321 = get_or_create_texture_ref(&g_texture_refs, texture_b, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v322 = v321->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v321->flags = v322 | 0x1402;
  v323 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_0, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsUnivers;
  v323->flags = TEXTURE_REF_WRAP_ADDRESSING;
  v324 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v325 = v324->flags;
  *(_WORD *)&v379[12] = 0;
  BYTE1(v325) |= 0x10u;
  *(_DWORD *)&v379[8] = 0;
  v324->flags = v325;
  v326 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v327 = v326->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v326->flags = v327 | 0x1002;
  v328 = get_or_create_texture_ref(&g_texture_refs, texture_a, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v329 = v328->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v328->flags = v329 | 0x1002;
  v330 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_5, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v331 = v330->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v330->flags = v331 | 0x1002;
  v332 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_6, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v333 = v332->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v332->flags = v333 | 0x1002;
  v334 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_7, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v335 = v334->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v334->flags = v335 | 0x1002;
  v336 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_8, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v337 = v336->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v336->flags = v337 | 0x1002;
  v338 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_9, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v339 = v338->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v338->flags = v339 | 0x1002;
  v340 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_10, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  v341 = v340->flags;
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  v340->flags = v341 | 0x1002;
  v342 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00, *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = texture_a;
  *(_DWORD *)(this + 2852) = v342;
  v343 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_5;
  *(_DWORD *)(this + 2868) = v343;
  v344 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_6;
  *(_DWORD *)(this + 2856) = v344;
  v345 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_7;
  *(_DWORD *)(this + 2872) = v345;
  v346 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_8;
  *(_DWORD *)(this + 2860) = v346;
  v347 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_9;
  *(_DWORD *)(this + 2876) = v347;
  v348 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_10;
  *(_DWORD *)(this + 2864) = v348;
  v349 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)(this + 2880) = v349;
  *(_DWORD *)&v379[4] = texture_b;
  *(_DWORD *)(this + 2884) = 0;
  v350 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_0;
  v350->unknown_a0 = 2;
  v351 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsUnivers;
  v351->unknown_a0 = 2;
  v352 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00;
  v352->unknown_a0 = 2;
  v353 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = texture_a;
  v353->unknown_a0 = 2;
  v354 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_5;
  v354->unknown_a0 = 2;
  v355 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_6;
  v355->unknown_a0 = 2;
  v356 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_7;
  v356->unknown_a0 = 2;
  v357 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_8;
  v357->unknown_a0 = 2;
  v358 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_9;
  v358->unknown_a0 = 2;
  v359 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_10;
  v359->unknown_a0 = 2;
  get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12])->unknown_a0 = 2;
  v360 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)(this + 17220060), v360);
  load_object_definition(aObjectsBarrier, *(Object **)(this + 17220096));
  zero_vector3((_DWORD *)(this + 17220076));
  store_color4f((tColour *)(this + 17220100), 1.0, 1.0, 1.0, 0.80000001);
  *(_DWORD *)(*(_DWORD *)(this + 17220096) + 20) = 7;
  initialize_track_render_cache_manager((SegmentCache *)(this + 476788));
  *(_DWORD *)&v379[36] = 0;
  v361 = (PathTemplateStripMesh **)(this + 282068);
  do
  {
    *(_DWORD *)&v379[56] = 0;
    do
    {
      *(_DWORD *)&v379[32] = 0;
      v362 = v361;
      do
      {
        for ( j = 0; j < 3; ++j )
        {
          v364 = add_object_to_list(&g_object_list);
          set_bod_object((BodBase *)(v362 - 9), v364);
          initialize_backdrop_tile_quad(
            *v362,
            *(int *)&v379[36],
            *(int *)&v379[56],
            *(_DWORD *)&v379[32] - 1,
            j - 1,
            aObjectsUnivers_1);
          v365 = *v362;
          v362 += 14;
          *(_DWORD *)v365->_pad_14 = 5;
        }
        ++*(_DWORD *)&v379[32];
      }
      while ( *(int *)&v379[32] < 3 );
      v361 = v362;
      ++*(_DWORD *)&v379[56];
    }
    while ( *(int *)&v379[56] < 4 );
    ++*(_DWORD *)&v379[36];
  }
  while ( *(int *)&v379[36] < 8 );
  v366 = get_or_create_texture_ref(&g_texture_refs, aObjectsUnivers_1, 0, 0);
  v367 = v366->flags;
  v368 = (InputState *)(this + 124);
  BYTE1(v367) = ((unsigned __int16)v366->flags >> 8) | 4;
  v369 = 0;
  v366->flags = v367;
  do
  {
    add_bod_to_front((_DWORD *)(this + 1448), (int)&v368[-1]);
    v368->controller_slot = v369;
    initialize_input(v368);
    ++v369;
    v368 += 2;
  }
  while ( v369 < 2 );
  v370 = *(_DWORD *)(this + 64);
  *(_DWORD *)&v379[32] = 0;
  if ( v370 > 0 )
  {
    do
    {
      v371 = this + 504 * *(_DWORD *)&v379[32];
      *(_DWORD *)&v379[36] = v371;
      set_matrix_identity((TransformMatrix *)(v371 + 348));
      set_matrix_identity((TransformMatrix *)(v371 + 508));
      *(_DWORD *)&v379[12] = 1065353216;
      *(_DWORD *)&v379[8] = 1083131627;
      *(_DWORD *)&v379[4] = 1078412299;
      *(_DWORD *)v379 = -1056307500;
      v372 = 112 * *(_DWORD *)&v379[32] + this + 68;
      *(_DWORD *)(v371 + 644) = 1121714176;
      *(_DWORD *)(v371 + 652) = v372;
      qmemcpy(
        (void *)(v371 + 348),
        initialize_matrix_from_values(
          &v383,
          0.073343001,
          0.0,
          -0.997311,
          0.0,
          0.15212999,
          0.98829699,
          0.011188,
          0.0,
          0.98563898,
          -0.15254,
          0.072484002,
          0.0,
          *(float *)v379,
          *(float *)&v379[4],
          *(float *)&v379[8],
          *(float *)&v379[12]),
        0x40u);
      initialize_frontend_overlay_color_lerp((_DWORD *)(*(_DWORD *)&v379[36] + 680), 0x1000000);
      release_mouse_cursor((MouseCursorState *)(*(_DWORD *)&v379[36] + 656));
      v373 = *(_DWORD *)&v379[32];
      *(_BYTE *)(*(_DWORD *)&v379[36] + 676) = 0;
      if ( !v373 )
        *(_DWORD *)(this + 440) = 12;
      v374 = *(_DWORD *)&v379[36];
      *(_DWORD *)&v379[12] = g_runtime_config.last_entered_player_name;
      *(_BYTE *)(*(_DWORD *)&v379[36] + 781) = 0;
      *(_DWORD *)(v374 + 784) = 0;
      rstrcpy_checked_ascii((char *)(v374 + 420), *(char **)&v379[12]);
      v375 = *(_DWORD *)(this + 64);
      ++*(_DWORD *)&v379[32];
    }
    while ( *(int *)&v379[32] < v375 );
  }
  initialize_high_score_tables((HighScoreBank *)&byte_6FFAE0[this]);
  *(_DWORD *)&v379[12] = aScoreaDat;
  load_high_scores_from_file(&byte_6FFAE0[this], *(CompletionResultScreen *)&v379[12]);
  *(_DWORD *)&v379[12] = aScorebDat;
  load_high_scores_from_file(&byte_6FFAE0[this], *(CompletionResultScreen *)&v379[12]);
  *(_DWORD *)&v379[12] = aScorecDat;
  load_high_scores_from_file(&byte_6FFAE0[this], *(CompletionResultScreen *)&v379[12]);
  *(_BYTE *)(this + 17198057) = 0;
  *(_BYTE *)(this + 17198056) = 0;
  initialize_tip_manager((TipManager *)(this + 19820376));
  add_bod_to_front((_DWORD *)(this + 1448), this + 19820376);
  add_bod_to_front(&g_game_base->active_bod_list.unknown_00, this + 324412);
  open_star_field((StarManager *)(this + 324412), 36);
  *(_DWORD *)(this + 3998116) = 0;
  *(_DWORD *)&v379[12] = this + 322576;
  *(_DWORD *)(this + 3998112) = 0;
  add_bod_to_front((_DWORD *)(this + 1448), *(int *)&v379[12]);
  *(_DWORD *)&v379[12] = this + 2892;
  *(_DWORD *)(this + 324200) = 0;
  append_bod_to_end((_DWORD *)(this + 1448), *(_DWORD **)&v379[12]);
  initialize_border_stack(this + 2948);
  *(_DWORD *)(this + 4556) = this + 2892;
  *(_DWORD *)&v379[12] = 1103626240;
  *(_BYTE *)(this + 278764) = 0;
  set_border_justify_centre((FrameBorderManager *)(this + 2892), *(float *)&v379[12]);
  v376 = (_DWORD *)(this + 4976);
  v377 = 150;
  do
  {
    *v376 = 0;
    v376 += 457;
    --v377;
  }
  while ( v377 );
  build_all_objects(&g_object_list);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216064), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216232), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216400), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216568), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216736), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17216904), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218080), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218248), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217072), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217240), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217408), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217576), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217744), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17217912), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218416), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218584), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219760), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219928), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218752), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17218920), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219424), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219592), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219088), *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(*(Object **)(this + 17219256), *(tColour *)v379);
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  *(_DWORD *)(this + 19813856) = 2;
  return 1;
}
