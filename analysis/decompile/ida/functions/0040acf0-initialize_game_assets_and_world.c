/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_assets_and_world @ 0x40acf0 */
/* selector: initialize_game_assets_and_world */

// Bootstraps the shared app world, front-end managers, score tables, star field, and the embedded 63-pair path-template bank. Public Path= slots 0..50 are constructed in place at GameRoot+0x1066f2c; slots 51..62 own transition meshes for flagged loop/invert families, HALFPIPE is the direct slot-42 constructor call, and WARP slot 30 remains unbuilt.
uint8_t __thiscall initialize_game_assets_and_world(GameRoot *game)
{
  FrameOverlay *p_overlay_0; // eax
  uint32_t *p_list_flags; // edx
  FrameBodBase **p_first; // ecx
  FrameBodBase *first; // edi
  FrameBodBase *list_prev; // eax
  uint32_t v7; // eax
  FrameOverlay *p_overlay_2; // eax
  uint32_t list_flags; // edx
  FrameBodBase **v10; // ecx
  FrameBodBase *v11; // edx
  FrameBodBase *v12; // eax
  int v13; // ecx
  FrameOverlay *p_overlay_1; // ecx
  uint32_t v15; // edx
  FrameBodBase **v16; // eax
  FrameBodBase *v17; // edx
  FrameBodBase *v18; // ecx
  int v19; // ecx
  char *v20; // edi
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
  Object **p_object; // edi
  Object *v55; // edx
  ObjectFaceQuad *facequads; // eax
  TextureRef *texture_ref; // eax
  TextureRefFlags flags; // ecx
  Object *v59; // ecx
  bool v60; // zf
  int v61; // eax
  Object *v62; // eax
  SubgameRuntime **p_owner_game; // edi
  int i; // edi
  Object *v65; // eax
  Object *v66; // ecx
  Object *object; // edx
  _DWORD *v68; // eax
  BodBase *p_track_body_list_head; // edi
  FrameBodBase *v70; // ecx
  FrameBodBase **v71; // eax
  FrameBodBase *v72; // ecx
  uint32_t v73; // eax
  BodBase *p_barrier_sub_lazer_list_head; // eax
  uint32_t *v75; // ecx
  struct BodNode *list_next; // edx
  uint32_t v77; // eax
  BodBase *p_salt_hazard_list_head; // eax
  uint32_t *v79; // edx
  struct BodNode *v80; // ecx
  uint32_t v81; // eax
  BodBase *p_golb_vapour_list_head; // eax
  uint32_t *v83; // edx
  struct BodNode *v84; // ecx
  uint32_t v85; // eax
  BodBase *p_fringe_attachment_list_head; // eax
  uint32_t *v87; // edx
  struct BodNode *v88; // ecx
  uint32_t v89; // eax
  BodBase *p_special_track_cell_list_head; // eax
  uint32_t *v91; // edx
  struct BodNode *v92; // ecx
  uint32_t v93; // eax
  BodBase *p_unknown_bod_355cec; // eax
  uint32_t *v95; // edx
  struct BodNode *v96; // ecx
  uint32_t v97; // eax
  BodBase *p_landscape_slice_list_head; // eax
  uint32_t *v99; // edx
  struct BodNode *v100; // ecx
  uint32_t v101; // eax
  BodBase *p_unknown_bod_355c7c; // eax
  uint32_t *v103; // edx
  struct BodNode *v104; // ecx
  uint32_t v105; // eax
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
  Object *v210; // ecx
  Object *v211; // edx
  Object *v212; // eax
  Object *v213; // eax
  Object *v214; // eax
  Object *v215; // edx
  Object *v216; // eax
  Object *v217; // eax
  Object *v218; // eax
  Object *v219; // eax
  Object *v220; // ecx
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
  Object *v239; // edx
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
  TextureRef *v311; // eax
  TextureRef *v312; // eax
  Object *v313; // eax
  Object *v314; // eax
  uint8_t *v315; // esi
  Object *v316; // eax
  TextureRef *v317; // eax
  TextureRefFlags v318; // ecx
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
  uint8_t *v361; // eax
  PathTemplateStripMesh **v362; // esi
  int j; // edi
  Object *v364; // eax
  PathTemplateStripMesh *v365; // eax
  TextureRef *v366; // eax
  TextureRefFlags v367; // ecx
  InputState *p_input; // esi
  int v369; // edi
  int32_t player_count; // eax
  char *v371; // esi
  GameInput *v372; // edx
  int v373; // eax
  int v374; // eax
  int32_t v375; // ecx
  uint8_t *v376; // eax
  int v377; // ecx
  _BYTE v379[92]; // [esp-10h] [ebp-14Ch] BYREF
  int transform_48; // [esp+5Ch] [ebp-E0h]
  char self[16]; // [esp+6Ch] [ebp-D0h] BYREF
  char ArgList[128]; // [esp+7Ch] [ebp-C0h] BYREF
  TransformMatrix v383; // [esp+FCh] [ebp-40h] BYREF

  noop_this_constructor(self);
  store_color4f((tColour *)&game->unknown_000000[20], 1.0, 1.0, 1.0, 1.0);
  *(_DWORD *)&game->unknown_000000[16] = 1065353216;
  *(_DWORD *)&game->unknown_000000[8] = 1106247680;
  *(_DWORD *)&game->unknown_000000[12] = 1112014848;
  game->unknown_000000[4] = 1;
  game->player_count = 2;
  initialize_border_stack(&game->fade);
  game->unknown_000521[71] = 0;
  game->subgame.subgame_pause_gate = 0;
  initialize_cheat(&g_cheat_state);
  game->intro.hide_for_replay_latch = 0;
  initialize_blink_random((float *)&game->subgame.scan_reset);
  set_subgame_rate(&game->subgame, 1.1);
  game->render_skip_count = 2;
  *(_DWORD *)&v379[12] = 500;
  game->fixed_update_count = 1;
  initialize_texture_list(&g_texture_refs, *(int *)&v379[12]);
  initialize_object_list(&g_object_list, 3000);
  *(_DWORD *)game->unknown_000514 = 0;
  game->fixed_update_accumulator = 0.0;
  game->frame_counter = 0;
  game->inactive_bod_sentinel.bod.list_next = nullptr;
  game->active_bod_list.free_top = &game->inactive_bod_sentinel;
  game->active_bod_list.first = nullptr;
  game->unknown_000b48 = 0;
  memset(g_sprite_depth_buckets, 0, sizeof(g_sprite_depth_buckets));
  game->render_camera_slots[0].sort_key = 0;
  game->render_camera_slots[0].flags = 16777219;
  game->render_camera_slots[0].source = &game->overlay_0.camera;
  game->render_camera_slots[0].viewport_x = 0.0;
  game->render_camera_slots[0].viewport_y = 0.0;
  game->render_camera_slots[0].viewport_width = 1.0;
  game->render_camera_slots[0].viewport_height = 1.0;
  game->render_camera_slots[2].draw_world = 0;
  p_overlay_0 = &game->overlay_0;
  p_list_flags = &game->overlay_0.bod.bod.bod.list_flags;
  if ( (game->overlay_0.bod.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->bod.list_prev = &p_overlay_0->bod.bod;
      (*p_first)->bod.list_prev->bod.list_next = *p_first;
      list_prev = (*p_first)->bod.list_prev;
      *p_first = list_prev;
      list_prev->bod.list_prev = nullptr;
    }
    else
    {
      *p_first = &p_overlay_0->bod.bod;
      game->overlay_0.bod.bod.bod.list_prev = nullptr;
      (*p_first)->bod.list_next = nullptr;
    }
    v7 = *p_list_flags;
    BYTE1(v7) = BYTE1(*p_list_flags) | 2;
    *p_list_flags = v7;
  }
  initialize_overlay((int)&game->overlay_0);
  memset(&g_directx_loader_scratch, 0, 0x15Cu);
  initialize_directx_loader((DirectXLoader *)&game->unknown_044100[19712]);
  reset_landscape_manager(&game->subgame.landscape_manager);
  load_segment_definitions(&game->subgame.sm_tracks);
  load_landscape_script_by_name((char *)&game->subgame.landscape_manager, aStarmapTxt);
  load_landscape_script_by_name((char *)&game->subgame.landscape_manager, aSplashTxt);
  load_landscape_script_by_name((char *)&game->subgame.landscape_manager, g_help_script_path);
  game->subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector;
  bind_subgame_owner((SubgameOwnerLink *)&game->subgame.gui);
  bind_subgame_owner((SubgameOwnerLink *)&game->subgame.thanks_screen);
  load_galaxy_layout((char *)&game->subgame.galaxy);
  initialize_cameraman((Cameraman *)((char *)&loc_42FF7C + (_DWORD)game));
  open_logo(&game->logo);
  initialize_sound_bank(&g_sound_bank_entries);
  initialize_voice_manager(g_voice_manager);
  apply_audio_config_volumes(&game->options);
  load_level_definitions(&game->subgame.sm_tracks);
  load_landscape_script_by_name((char *)&g_game_base->subgame.landscape_manager, g_menu_background_script_path);
  load_builtin_segment_definitions(
    &game->subgame.level_definition_scratch,
    (SubSegmentRaw **)&g_builtin_segment_definitions);
  game->render_camera_slots[1].sort_key = 1;
  *(_DWORD *)&v379[12] = &game->players[0].camera;
  game->render_camera_slots[1].flags = 33554433;
  attach_render_camera_source(&game->render_camera_slots[1].unknown_00, *(int *)&v379[12]);
  game->players[0].camera.render_mask = 0x2000000;
  *(_DWORD *)&v379[12] = &game->players[1].camera;
  game->render_camera_slots[4].sort_key = 1;
  game->render_camera_slots[4].flags = 268435459;
  attach_render_camera_source(&game->render_camera_slots[4].unknown_00, *(int *)&v379[12]);
  game->players[1].camera.render_mask = 0x10000000;
  game->render_camera_slots[3].sort_key = 3;
  game->render_camera_slots[3].flags = 134217731;
  game->render_camera_slots[3].source = &game->overlay_2.camera;
  game->render_camera_slots[3].viewport_x = 0.0;
  game->render_camera_slots[3].viewport_y = 0.0;
  game->render_camera_slots[3].viewport_width = 1.0;
  game->render_camera_slots[3].viewport_height = 1.0;
  p_overlay_2 = &game->overlay_2;
  list_flags = game->overlay_2.bod.bod.bod.list_flags;
  *(_DWORD *)&v379[36] = &game->overlay_2.bod.bod.bod.list_flags;
  if ( (list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v10 = &g_game_base->active_bod_list.first;
    v11 = g_game_base->active_bod_list.first;
    if ( v11 )
    {
      v11->bod.list_prev = &p_overlay_2->bod.bod;
      (*v10)->bod.list_prev->bod.list_next = *v10;
      v12 = (*v10)->bod.list_prev;
      *v10 = v12;
      v12->bod.list_prev = nullptr;
    }
    else
    {
      *v10 = &p_overlay_2->bod.bod;
      game->overlay_2.bod.bod.bod.list_prev = nullptr;
      (*v10)->bod.list_next = nullptr;
    }
    v13 = **(_DWORD **)&v379[36];
    BYTE1(v13) = BYTE1(**(_DWORD **)&v379[36]) | 2;
    **(_DWORD **)&v379[36] = v13;
  }
  initialize_overlay((int)&game->overlay_2);
  game->render_camera_slots[2].sort_key = 2;
  game->render_camera_slots[2].flags = 67108867;
  game->render_camera_slots[2].source = &game->overlay_1.camera;
  game->render_camera_slots[2].viewport_x = 0.0;
  game->render_camera_slots[2].viewport_y = 0.0;
  p_overlay_1 = &game->overlay_1;
  game->render_camera_slots[2].viewport_width = 1.0;
  game->render_camera_slots[2].viewport_height = 1.0;
  v15 = game->overlay_1.bod.bod.bod.list_flags;
  *(_DWORD *)&v379[36] = &game->overlay_1.bod.bod.bod.list_flags;
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
      v17->bod.list_prev = &p_overlay_1->bod.bod;
      (*v16)->bod.list_prev->bod.list_next = *v16;
      v18 = (*v16)->bod.list_prev;
      *v16 = v18;
      v18->bod.list_prev = nullptr;
    }
    else
    {
      *v16 = &p_overlay_1->bod.bod;
      game->overlay_1.bod.bod.bod.list_prev = nullptr;
      (*v16)->bod.list_next = nullptr;
    }
    v19 = **(_DWORD **)&v379[36];
    BYTE1(v19) = BYTE1(**(_DWORD **)&v379[36]) | 2;
    **(_DWORD **)&v379[36] = v19;
  }
  initialize_overlay((int)&game->overlay_1);
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
    v20 = (char *)game + 56 * (__int64)*(float *)&v379[32];
    v21 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 280464), v21);
    initialize_backdrop_slice_quad(*((PathTemplateStripMesh **)v20 + 70125), aObjectsWorld00, *(float *)&v379[32]);
    v22 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 280912), v22);
    initialize_backdrop_slice_quad(*((PathTemplateStripMesh **)v20 + 70237), aObjectsWorld00_0, *(float *)&v379[32]);
    v23 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v20 + 281360), v23);
    initialize_backdrop_slice_quad(*((PathTemplateStripMesh **)v20 + 70349), texture_a, *(float *)&v379[32]);
    v24 = *(float *)&v379[32] + 1.0;
    *(float *)&v379[32] = v24;
  }
  while ( v24 < 8.0 );
  set_matrix_identity((TransformMatrix *)&v379[60]);
  v25 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1232], v25);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], mesh_path, *(Object **)&game->unknown_044100[1268], 1);
  transform_48 = 0;
  apply_bod_position((BodBase *)&game->unknown_044100[1232], (TransformMatrix *)&v379[60]);
  v26 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1288], v26);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar2X, *(Object **)&game->unknown_044100[1324], 1);
  transform_48 = 1056964608;
  apply_bod_position((BodBase *)&game->unknown_044100[1288], (TransformMatrix *)&v379[60]);
  v27 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1344], v27);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar3X, *(Object **)&game->unknown_044100[1380], 1);
  transform_48 = 1065353216;
  apply_bod_position((BodBase *)&game->unknown_044100[1344], (TransformMatrix *)&v379[60]);
  v28 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1400], v28);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar4X, *(Object **)&game->unknown_044100[1436], 1);
  transform_48 = 1069547520;
  apply_bod_position((BodBase *)&game->unknown_044100[1400], (TransformMatrix *)&v379[60]);
  v29 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1456], v29);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar5X, *(Object **)&game->unknown_044100[1492], 1);
  transform_48 = 0x40000000;
  apply_bod_position((BodBase *)&game->unknown_044100[1456], (TransformMatrix *)&v379[60]);
  v30 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1512], v30);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar6X, *(Object **)&game->unknown_044100[1548], 1);
  transform_48 = 1075838976;
  apply_bod_position((BodBase *)&game->unknown_044100[1512], (TransformMatrix *)&v379[60]);
  v31 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1568], v31);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar7X, *(Object **)&game->unknown_044100[1604], 1);
  transform_48 = 1077936128;
  apply_bod_position((BodBase *)&game->unknown_044100[1568], (TransformMatrix *)&v379[60]);
  v32 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[1624], v32);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPillar8X, *(Object **)&game->unknown_044100[1660], 1);
  transform_48 = 1080033280;
  apply_bod_position((BodBase *)&game->unknown_044100[1624], (TransformMatrix *)&v379[60]);
  v33 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[3024], v33);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)&game->unknown_044100[3060], aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(-1, *(_DWORD *)&game->unknown_044100[3060]);
  v34 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[3080], v34);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)&game->unknown_044100[3116], aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(0, *(_DWORD *)&game->unknown_044100[3116]);
  v35 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[3136], v35);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)&game->unknown_044100[3172], aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(1, *(_DWORD *)&game->unknown_044100[3172]);
  v36 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[280], v36);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)&game->unknown_044100[316], aObjectsWorld00);
  v37 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[336], v37);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)&game->unknown_044100[372], aObjectsWorld00);
  v38 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[448], v38);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)&game->unknown_044100[484], aObjectsWorld00);
  v39 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[392], v39);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)&game->unknown_044100[428], aObjectsWorld00);
  v40 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[504], v40);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)&game->unknown_044100[540], aObjectsWorld00_0);
  v41 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[560], v41);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)&game->unknown_044100[596], aObjectsWorld00_0);
  v42 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[672], v42);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)&game->unknown_044100[708], aObjectsWorld00_0);
  v43 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[616], v43);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)&game->unknown_044100[652], aObjectsWorld00_0);
  v44 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[728], v44);
  initialize_backdrop_corner_quad(0, *(PathTemplateStripMesh **)&game->unknown_044100[764], texture_a);
  v45 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[784], v45);
  initialize_backdrop_corner_quad(1, *(PathTemplateStripMesh **)&game->unknown_044100[820], texture_a);
  v46 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[896], v46);
  initialize_backdrop_corner_quad(2, *(PathTemplateStripMesh **)&game->unknown_044100[932], texture_a);
  v47 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[840], v47);
  initialize_backdrop_corner_quad(3, *(PathTemplateStripMesh **)&game->unknown_044100[876], texture_a);
  v48 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[952], v48);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aTrampX, *(Object **)&game->unknown_044100[988], 1);
  *(_DWORD *)(*(_DWORD *)&game->unknown_044100[988] + 20) = 6;
  v49 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)&game->unknown_044100[988] + 92) + 12);
  *v49 |= 0x400u;
  v50 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)game->unknown_044100, v50);
  initialize_textured_backdrop_quad(*(PathTemplateStripMesh **)&game->unknown_044100[36], aObjectsUnivers_0, 0.0);
  *(_DWORD *)(*(_DWORD *)&game->unknown_044100[36] + 20) = 5;
  v51 = *(int **)(*(_DWORD *)(*(_DWORD *)&game->unknown_044100[36] + 92) + 12);
  v52 = *v51;
  BYTE1(v52) = BYTE1(*v51) | 4;
  *v51 = v52;
  v53 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[3192], v53);
  load_object_definition(path, *(Object **)&game->unknown_044100[3228]);
  p_object = &game->subgame.sub_lazers.slots[0].body.bod.object;
  *(_DWORD *)&v379[36] = 20;
  do
  {
    set_bod_object((BodBase *)(p_object - 9), *(Object **)&game->unknown_044100[3228]);
    v55 = *p_object;
    *(_DWORD *)&v379[12] = 1060320051;
    *(_DWORD *)&v379[8] = 1065353216;
    *(_DWORD *)&v379[4] = 1065353216;
    facequads = v55->facequads;
    *(_DWORD *)v379 = 1065353216;
    texture_ref = facequads->texture_ref;
    flags = texture_ref->flags;
    BYTE1(flags) = ((unsigned __int16)texture_ref->flags >> 8) | 4;
    texture_ref->flags = flags;
    p_object[25] = (Object *)&game->subgame;
    store_color4f(
      (tColour *)(p_object + 1),
      *(float *)v379,
      *(float *)&v379[4],
      *(float *)&v379[8],
      *(float *)&v379[12]);
    v59 = *p_object;
    p_object += 44;
    v61 = *(_DWORD *)&v379[36] - 1;
    v60 = *(_DWORD *)&v379[36] == 1;
    v59->blend_mode = 9;
    *(_DWORD *)&v379[36] = v61;
  }
  while ( !v60 );
  v62 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_044100[19656], v62);
  load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aSaltX, *(Object **)&game->unknown_044100[19692], 1);
  p_owner_game = &game->subgame.salt_hazards.slots[0].owner_game;
  *(_DWORD *)&v379[36] = 40;
  do
  {
    set_bod_object((BodBase *)(p_owner_game - 34), *(Object **)&game->unknown_044100[19692]);
    *(_DWORD *)&v379[12] = 1063675494;
    *(_DWORD *)&v379[8] = 1065353216;
    *(_DWORD *)&v379[4] = 1065353216;
    *(_DWORD *)v379 = 1065353216;
    *p_owner_game = &game->subgame;
    store_color4f(
      (tColour *)p_owner_game - 6,
      *(float *)v379,
      *(float *)&v379[4],
      *(float *)&v379[8],
      *(float *)&v379[12]);
    (*(p_owner_game - 25))->sub_pause.options_widget = (FrontendWidget *)12;
    set_matrix_identity((TransformMatrix *)(p_owner_game - 20));
    p_owner_game += 38;
    --*(_DWORD *)&v379[36];
  }
  while ( *(_DWORD *)&v379[36] );
  for ( i = 0; i < 2; ++i )
  {
    *(_DWORD *)&v379[36] = (char *)game + 96 * i;
    v65 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(*(_DWORD *)&v379[36] + 3987096), v65);
    if ( i )
    {
      if ( i != 1 )
        goto LABEL_31;
      object = game->subgame.banners.slots[1].bod.object;
      *(_DWORD *)&v379[12] = 1;
      *(_DWORD *)&v379[8] = object;
    }
    else
    {
      v66 = game->subgame.banners.slots[0].bod.object;
      *(_DWORD *)&v379[12] = 1;
      *(_DWORD *)&v379[8] = v66;
    }
    load_x_mesh((DirectXLoader *)&game->unknown_044100[19712], aPostofficestop, *(Object **)&v379[8], *(int *)&v379[12]);
LABEL_31:
    v68 = *(_DWORD **)&v379[36];
    *(_DWORD *)(*(_DWORD *)&v379[36] + 3987120) = 0;
    v68[996779] = 0;
    v68[996778] = 0;
    *(_DWORD *)&game->subgame.banners.slots[i]._pad_3c[12] = &game->subgame;
    v68[996788] = i;
    v68[996796] = 0;
    v68[996797] = 1004768824;
  }
  p_track_body_list_head = &game->subgame.track_body_list_head;
  if ( (game->subgame.track_body_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v70 = game->active_bod_list.first;
    v71 = &game->active_bod_list.first;
    if ( v70 )
    {
      v70->bod.list_prev = (FrameBodBase *)p_track_body_list_head;
      (*v71)->bod.list_prev->bod.list_next = *v71;
      v72 = (*v71)->bod.list_prev;
      *v71 = v72;
      v72->bod.list_prev = nullptr;
    }
    else
    {
      *v71 = (FrameBodBase *)p_track_body_list_head;
      game->subgame.track_body_list_head.bod.list_prev = nullptr;
      (*v71)->bod.list_next = nullptr;
    }
    v73 = game->subgame.track_body_list_head.bod.list_flags;
    BYTE1(v73) |= 2u;
    game->subgame.track_body_list_head.bod.list_flags = v73;
  }
  p_barrier_sub_lazer_list_head = &game->subgame.barrier_sub_lazer_list_head;
  v75 = &game->subgame.barrier_sub_lazer_list_head.bod.list_flags;
  if ( (game->subgame.barrier_sub_lazer_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.barrier_sub_lazer_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.barrier_sub_lazer_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_barrier_sub_lazer_list_head->bod;
    list_next = game->subgame.barrier_sub_lazer_list_head.bod.list_next;
    if ( list_next )
      list_next->list_prev = &p_barrier_sub_lazer_list_head->bod;
    v77 = *v75;
    BYTE1(v77) = BYTE1(*v75) | 2;
    *v75 = v77;
  }
  p_salt_hazard_list_head = &game->subgame.salt_hazard_list_head;
  v79 = &game->subgame.salt_hazard_list_head.bod.list_flags;
  if ( (game->subgame.salt_hazard_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.salt_hazard_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.salt_hazard_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_salt_hazard_list_head->bod;
    v80 = game->subgame.salt_hazard_list_head.bod.list_next;
    if ( v80 )
      v80->list_prev = &p_salt_hazard_list_head->bod;
    v81 = *v79;
    BYTE1(v81) = BYTE1(*v79) | 2;
    *v79 = v81;
  }
  p_golb_vapour_list_head = &game->subgame.golb_vapour_list_head;
  v83 = &game->subgame.golb_vapour_list_head.bod.list_flags;
  if ( (game->subgame.golb_vapour_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.golb_vapour_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.golb_vapour_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_golb_vapour_list_head->bod;
    v84 = game->subgame.golb_vapour_list_head.bod.list_next;
    if ( v84 )
      v84->list_prev = &p_golb_vapour_list_head->bod;
    v85 = *v83;
    BYTE1(v85) = BYTE1(*v83) | 2;
    *v83 = v85;
  }
  p_fringe_attachment_list_head = &game->subgame.fringe_attachment_list_head;
  v87 = &game->subgame.fringe_attachment_list_head.bod.list_flags;
  if ( (game->subgame.fringe_attachment_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.fringe_attachment_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.fringe_attachment_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_fringe_attachment_list_head->bod;
    v88 = game->subgame.fringe_attachment_list_head.bod.list_next;
    if ( v88 )
      v88->list_prev = &p_fringe_attachment_list_head->bod;
    v89 = *v87;
    BYTE1(v89) = BYTE1(*v87) | 2;
    *v87 = v89;
  }
  p_special_track_cell_list_head = &game->subgame.special_track_cell_list_head;
  v91 = &game->subgame.special_track_cell_list_head.bod.list_flags;
  if ( (game->subgame.special_track_cell_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.special_track_cell_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.special_track_cell_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_special_track_cell_list_head->bod;
    v92 = game->subgame.special_track_cell_list_head.bod.list_next;
    if ( v92 )
      v92->list_prev = &p_special_track_cell_list_head->bod;
    v93 = *v91;
    BYTE1(v93) = BYTE1(*v91) | 2;
    *v91 = v93;
  }
  p_unknown_bod_355cec = &game->subgame.unknown_bod_355cec;
  v95 = &game->subgame.unknown_bod_355cec.bod.list_flags;
  if ( (game->subgame.unknown_bod_355cec.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.unknown_bod_355cec.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.unknown_bod_355cec.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_unknown_bod_355cec->bod;
    v96 = game->subgame.unknown_bod_355cec.bod.list_next;
    if ( v96 )
      v96->list_prev = &p_unknown_bod_355cec->bod;
    v97 = *v95;
    BYTE1(v97) = BYTE1(*v95) | 2;
    *v95 = v97;
  }
  p_landscape_slice_list_head = &game->subgame.landscape_slice_list_head;
  v99 = &game->subgame.landscape_slice_list_head.bod.list_flags;
  if ( (game->subgame.landscape_slice_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.landscape_slice_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.landscape_slice_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_landscape_slice_list_head->bod;
    v100 = game->subgame.landscape_slice_list_head.bod.list_next;
    if ( v100 )
      v100->list_prev = &p_landscape_slice_list_head->bod;
    v101 = *v99;
    BYTE1(v101) = BYTE1(*v99) | 2;
    *v99 = v101;
  }
  p_unknown_bod_355c7c = &game->subgame.unknown_bod_355c7c;
  v103 = &game->subgame.unknown_bod_355c7c.bod.list_flags;
  if ( (game->subgame.unknown_bod_355c7c.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.unknown_bod_355c7c.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.unknown_bod_355c7c.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_unknown_bod_355c7c->bod;
    v104 = game->subgame.unknown_bod_355c7c.bod.list_next;
    if ( v104 )
      v104->list_prev = &p_unknown_bod_355c7c->bod;
    v105 = *v103;
    BYTE1(v105) = BYTE1(*v103) | 2;
    *v103 = v105;
  }
  debug_report_stub();
  v106 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[0].primary.bod, v106);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[0].primary, 6.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[0].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[0].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[0].primary.bod.position.x = 0.0;
  v107 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[0].secondary.bod, v107);
  mirror_path_template_pair_x(&game->subgame.path_pairs[0].secondary, &game->subgame.path_pairs[0].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[0].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[0].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[0].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[0].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[0].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.x = 0.0;
  v108 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[1].primary.bod, v108);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[1].primary, 6.0, 2, (char *)1, texture_a);
  game->subgame.path_pairs[1].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[1].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[1].primary.bod.position.x = 0.0;
  v109 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[1].secondary.bod, v109);
  mirror_path_template_pair_x(&game->subgame.path_pairs[1].secondary, &game->subgame.path_pairs[1].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[1].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[1].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[1].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[1].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[1].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.x = 0.0;
  v110 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[2].primary.bod, v110);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[2].primary, 8.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[2].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[2].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[2].primary.bod.position.x = 0.0;
  v111 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[2].secondary.bod, v111);
  mirror_path_template_pair_x(&game->subgame.path_pairs[2].secondary, &game->subgame.path_pairs[2].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[2].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[2].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[2].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[2].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[2].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.x = 0.0;
  v112 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[6].primary.bod, v112);
  initialize_looptheloopw_path_template_pair(&game->subgame.path_pairs[6].primary, 8.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[6].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[6].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[6].primary.bod.position.x = 0.0;
  v113 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[6].secondary.bod, v113);
  mirror_path_template_pair_x(&game->subgame.path_pairs[6].secondary, &game->subgame.path_pairs[6].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[6].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[6].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[6].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[6].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.z = 0.0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[6].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.x = 0.0;
  v114 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[3].primary.bod, v114);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[3].primary, 3.0, 2, (char *)1, texture_a);
  game->subgame.path_pairs[3].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[3].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[3].primary.bod.position.x = 0.0;
  v115 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[3].secondary.bod, v115);
  mirror_path_template_pair_x(&game->subgame.path_pairs[3].secondary, &game->subgame.path_pairs[3].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[3].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[3].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[3].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[3].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[3].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.x = 0.0;
  v116 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[4].primary.bod, v116);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[4].primary, 3.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[4].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[4].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[4].primary.bod.position.x = 0.0;
  v117 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[4].secondary.bod, v117);
  mirror_path_template_pair_x(&game->subgame.path_pairs[4].secondary, &game->subgame.path_pairs[4].primary);
  *(_DWORD *)&v379[12] = 0;
  game->subgame.path_pairs[4].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[4].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[4].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[4].primary, aObjectsUnivers_1, *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[4].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.x = 0.0;
  v118 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[5].primary.bod, v118);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[5].primary, 3.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[5].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[5].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[5].primary.bod.position.x = 0.0;
  v119 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[5].secondary.bod, v119);
  mirror_path_template_pair_x(&game->subgame.path_pairs[5].secondary, &game->subgame.path_pairs[5].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[5].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[5].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[5].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[5].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[5].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.x = 0.0;
  v120 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[7].primary.bod, v120);
  initialize_loopbow_path_template_pair(&game->subgame.path_pairs[7].primary, 6.0, 4u, (char *)1, texture_a);
  game->subgame.path_pairs[7].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[7].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[7].primary.bod.position.x = 0.0;
  v121 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[7].secondary.bod, v121);
  mirror_path_template_pair_x(&game->subgame.path_pairs[7].secondary, &game->subgame.path_pairs[7].primary);
  game->subgame.path_pairs[7].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[7].secondary.bod.position.y = 0.0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[7].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[7].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[7].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.x = 0.0;
  v122 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[37].primary.bod, v122);
  initialize_turnover_path_template_pair(&game->subgame.path_pairs[37].primary, 6.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[37].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[37].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[37].primary.bod.position.x = 0.0;
  v123 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[37].secondary.bod, v123);
  mirror_path_template_pair_x(&game->subgame.path_pairs[37].secondary, &game->subgame.path_pairs[37].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[37].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[37].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[37].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[37].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[37].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.x = 0.0;
  v124 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[38].primary.bod, v124);
  initialize_turnoverdouble_path_template_pair(&game->subgame.path_pairs[38].primary, 6.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[38].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[38].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[38].primary.bod.position.x = 0.0;
  v125 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[38].secondary.bod, v125);
  mirror_path_template_pair_x(&game->subgame.path_pairs[38].secondary, &game->subgame.path_pairs[38].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[38].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[38].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[38].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[38].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[38].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.x = 0.0;
  v126 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[43].primary.bod, v126);
  initialize_twister_path_template_pair(&game->subgame.path_pairs[43].primary, 2.5, 3, 1, texture_a, texture_b);
  game->subgame.path_pairs[43].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[43].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[43].primary.bod.position.x = 0.0;
  v127 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[43].secondary.bod, v127);
  mirror_path_template_pair_x(&game->subgame.path_pairs[43].secondary, &game->subgame.path_pairs[43].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[43].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[43].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[43].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[43].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[43].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.x = 0.0;
  v128 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[44].primary.bod, v128);
  initialize_twister_path_template_pair(&game->subgame.path_pairs[44].primary, 2.5, 3, 0, texture_a, texture_b);
  game->subgame.path_pairs[44].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[44].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[44].primary.bod.position.x = 0.0;
  v129 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[44].secondary.bod, v129);
  mirror_path_template_pair_x(&game->subgame.path_pairs[44].secondary, &game->subgame.path_pairs[44].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[44].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[44].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[44].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[44].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[44].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.x = 0.0;
  v130 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[45].primary.bod, v130);
  initialize_twister2_path_template_pair(&game->subgame.path_pairs[45].primary, 2.5, 3, 1, texture_a, texture_b);
  game->subgame.path_pairs[45].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[45].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[45].primary.bod.position.x = 0.0;
  v131 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[45].secondary.bod, v131);
  mirror_path_template_pair_x(&game->subgame.path_pairs[45].secondary, &game->subgame.path_pairs[45].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[45].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[45].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[45].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[45].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[45].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.x = 0.0;
  v132 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[46].primary.bod, v132);
  initialize_twister2_path_template_pair(&game->subgame.path_pairs[46].primary, 2.5, 3, 0, texture_a, texture_b);
  game->subgame.path_pairs[46].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[46].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[46].primary.bod.position.x = 0.0;
  v133 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[46].secondary.bod, v133);
  mirror_path_template_pair_x(&game->subgame.path_pairs[46].secondary, &game->subgame.path_pairs[46].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[46].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[46].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[46].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[46].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[46].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.x = 0.0;
  v134 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[39].primary.bod, v134);
  initialize_turnunder_path_template_pair(&game->subgame.path_pairs[39].primary, 6.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[39].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[39].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[39].primary.bod.position.x = 0.0;
  v135 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[39].secondary.bod, v135);
  mirror_path_template_pair_x(&game->subgame.path_pairs[39].secondary, &game->subgame.path_pairs[39].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[39].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[39].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[39].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[39].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[39].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.x = 0.0;
  v136 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[41].primary.bod, v136);
  initialize_invert_path_template_pair(&game->subgame.path_pairs[41].primary, 1086324736, (char *)8, (char *)1);
  game->subgame.path_pairs[41].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[41].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[41].primary.bod.position.x = 0.0;
  v137 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[41].secondary.bod, v137);
  mirror_path_template_pair_x(&game->subgame.path_pairs[41].secondary, &game->subgame.path_pairs[41].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[41].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[41].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[41].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[41].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[41].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.x = 0.0;
  v138 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[42].primary.bod, v138);
  initialize_halfpipe_path_template_pair(&game->subgame.path_pairs[42].primary, 1086324736, (char *)8, (char *)1);
  game->subgame.path_pairs[42].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[42].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[42].primary.bod.position.x = 0.0;
  v139 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[42].secondary.bod, v139);
  mirror_path_template_pair_x(&game->subgame.path_pairs[42].secondary, &game->subgame.path_pairs[42].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[42].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[42].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[42].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[42].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[42].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.x = 0.0;
  v140 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[40].primary.bod, v140);
  initialize_wibble_path_template_pair(&game->subgame.path_pairs[40].primary, 1086324736, (char *)8, (char *)1);
  game->subgame.path_pairs[40].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[40].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[40].primary.bod.position.x = 0.0;
  v141 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[40].secondary.bod, v141);
  mirror_path_template_pair_x(&game->subgame.path_pairs[40].secondary, &game->subgame.path_pairs[40].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[40].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[40].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[40].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[40].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[40].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.x = 0.0;
  v142 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[31].primary.bod, v142);
  initialize_supertramp_path_template_pair(
    &game->subgame.path_pairs[31].primary,
    6.0,
    2,
    (char *)1,
    texture_a,
    texture_b);
  *(_DWORD *)&v379[12] = aObjectsUnivers_1;
  game->subgame.path_pairs[31].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[31].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[31].primary.bod.position.x = 0.0;
  build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[31].primary, *(char **)&v379[12]);
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.x = 0.0;
  v143 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[31].secondary.bod, v143);
  initialize_supertramp_path_template_pair(
    &game->subgame.path_pairs[31].secondary,
    6.0,
    2,
    (char *)1,
    texture_a,
    texture_b);
  *(_DWORD *)&v379[12] = aObjectsUnivers_1;
  game->subgame.path_pairs[31].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[31].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[31].secondary.bod.position.x = 0.0;
  build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[31].secondary, *(char **)&v379[12]);
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.x = 0.0;
  v144 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[36].primary.bod, v144);
  initialize_start_path_template_pair(&game->subgame.path_pairs[36].primary, 4.0, 8, (char *)1);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[36].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[36].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[36].primary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[36].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.x = 0.0;
  v145 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[36].secondary.bod, v145);
  initialize_start_path_template_pair(&game->subgame.path_pairs[36].secondary, 4.0, 8, (char *)1);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[36].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[36].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[36].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[36].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.x = 0.0;
  v146 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[25].primary.bod, v146);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[25].primary, 3.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[25].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[25].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[25].primary.bod.position.x = 0.0;
  v147 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[25].secondary.bod, v147);
  mirror_path_template_pair_x(&game->subgame.path_pairs[25].secondary, &game->subgame.path_pairs[25].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[25].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[25].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[25].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[25].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[25].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.x = 0.0;
  v148 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[27].primary.bod, v148);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[27].primary, 5.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[27].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[27].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[27].primary.bod.position.x = 0.0;
  v149 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[27].secondary.bod, v149);
  mirror_path_template_pair_x(&game->subgame.path_pairs[27].secondary, &game->subgame.path_pairs[27].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[27].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[27].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[27].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[27].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[27].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.x = 0.0;
  v150 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[26].primary.bod, v150);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[26].primary, 3.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[26].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[26].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[26].primary.bod.position.x = 0.0;
  v151 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[26].secondary.bod, v151);
  mirror_path_template_pair_x(&game->subgame.path_pairs[26].secondary, &game->subgame.path_pairs[26].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[26].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[26].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[26].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[26].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.z = 0.0;
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[26].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.x = 0.0;
  v152 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[16].primary.bod, v152);
  initialize_hump_path_template_pair(&game->subgame.path_pairs[16].primary, 4.0, 1.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[16].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[16].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[16].primary.bod.position.x = 0.0;
  v153 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[16].secondary.bod, v153);
  mirror_path_template_pair_x(&game->subgame.path_pairs[16].secondary, &game->subgame.path_pairs[16].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[16].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[16].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[16].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[16].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[16].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.x = 0.0;
  v154 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[17].primary.bod, v154);
  initialize_dump_path_template_pair(&game->subgame.path_pairs[17].primary, 4.0, 1.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[17].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[17].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[17].primary.bod.position.x = 0.0;
  v155 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[17].secondary.bod, v155);
  mirror_path_template_pair_x(&game->subgame.path_pairs[17].secondary, &game->subgame.path_pairs[17].primary);
  game->subgame.path_pairs[17].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[17].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[17].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[17].primary, aObjectsUnivers_1, 0.0);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[17].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.x = 0.0;
  v156 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[18].primary.bod, v156);
  initialize_hump_path_template_pair(&game->subgame.path_pairs[18].primary, 4.0, 0.30000001, 3, (char *)1, texture_a);
  game->subgame.path_pairs[18].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[18].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[18].primary.bod.position.x = 0.0;
  v157 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[18].secondary.bod, v157);
  mirror_path_template_pair_x(&game->subgame.path_pairs[18].secondary, &game->subgame.path_pairs[18].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[18].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[18].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[18].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[18].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[18].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.x = 0.0;
  v158 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[19].primary.bod, v158);
  initialize_dump_path_template_pair(&game->subgame.path_pairs[19].primary, 4.0, 0.30000001, 3, (char *)1, texture_a);
  game->subgame.path_pairs[19].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[19].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[19].primary.bod.position.x = 0.0;
  v159 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[19].secondary.bod, v159);
  mirror_path_template_pair_x(&game->subgame.path_pairs[19].secondary, &game->subgame.path_pairs[19].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[19].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[19].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[19].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[19].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[19].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.x = 0.0;
  v160 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[8].primary.bod, v160);
  initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[8].primary, 8, 4.0, 20.0, 1, texture_a, texture_a);
  game->subgame.path_pairs[8].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[8].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[8].primary.bod.position.x = 0.0;
  v161 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[8].secondary.bod, v161);
  mirror_path_template_pair_x(&game->subgame.path_pairs[8].secondary, &game->subgame.path_pairs[8].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[8].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[8].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[8].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[8].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[8].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.x = 0.0;
  v162 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[10].primary.bod, v162);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[10].primary,
    4,
    4.0,
    20.0,
    0,
    texture_a,
    texture_b);
  game->subgame.path_pairs[10].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[10].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[10].primary.bod.position.x = 0.0;
  v163 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[10].secondary.bod, v163);
  mirror_path_template_pair_x(&game->subgame.path_pairs[10].secondary, &game->subgame.path_pairs[10].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[10].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[10].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[10].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[10].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[10].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.x = 0.0;
  v164 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[9].primary.bod, v164);
  initialize_hill_valley_path_template_pair(&game->subgame.path_pairs[9].primary, 4, 4.0, 20.0, 1, texture_a, texture_b);
  game->subgame.path_pairs[9].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[9].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[9].primary.bod.position.x = 0.0;
  v165 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[9].secondary.bod, v165);
  mirror_path_template_pair_x(&game->subgame.path_pairs[9].secondary, &game->subgame.path_pairs[9].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[9].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[9].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[9].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[9].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[9].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.x = 0.0;
  v166 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[14].primary.bod, v166);
  initialize_sbend_path_template_pair(
    &game->subgame.path_pairs[14].primary,
    8u,
    8.0,
    14.0,
    1,
    aObjectsWorld00,
    aObjectsWorld00);
  game->subgame.path_pairs[14].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[14].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[14].primary.bod.position.x = 0.0;
  v167 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[14].secondary.bod, v167);
  mirror_path_template_pair_x(&game->subgame.path_pairs[14].secondary, &game->subgame.path_pairs[14].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[14].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[14].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[14].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[14].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[14].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.x = 0.0;
  v168 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[11].primary.bod, v168);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[11].primary,
    8,
    -4.0,
    20.0,
    1,
    texture_a,
    texture_a);
  game->subgame.path_pairs[11].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[11].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[11].primary.bod.position.x = 0.0;
  v169 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[11].secondary.bod, v169);
  mirror_path_template_pair_x(&game->subgame.path_pairs[11].secondary, &game->subgame.path_pairs[11].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[11].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[11].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[11].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[11].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[11].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.x = 0.0;
  v170 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[13].primary.bod, v170);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[13].primary,
    4,
    -4.0,
    20.0,
    0,
    texture_a,
    texture_a);
  game->subgame.path_pairs[13].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[13].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[13].primary.bod.position.x = 0.0;
  v171 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[13].secondary.bod, v171);
  mirror_path_template_pair_x(&game->subgame.path_pairs[13].secondary, &game->subgame.path_pairs[13].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[13].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[13].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[13].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[13].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[13].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.x = 0.0;
  v172 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[12].primary.bod, v172);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[12].primary,
    4,
    -4.0,
    20.0,
    1,
    texture_a,
    texture_a);
  game->subgame.path_pairs[12].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[12].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[12].primary.bod.position.x = 0.0;
  v173 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[12].secondary.bod, v173);
  mirror_path_template_pair_x(&game->subgame.path_pairs[12].secondary, &game->subgame.path_pairs[12].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[12].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[12].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[12].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[12].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[12].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.x = 0.0;
  v174 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[20].primary.bod, v174);
  initialize_dip_path_template_pair(&game->subgame.path_pairs[20].primary, 4.0, 2, (char *)1, texture_a);
  game->subgame.path_pairs[20].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[20].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[20].primary.bod.position.x = 0.0;
  v175 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[20].secondary.bod, v175);
  mirror_path_template_pair_x(&game->subgame.path_pairs[20].secondary, &game->subgame.path_pairs[20].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[20].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[20].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[20].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[20].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[20].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.x = 0.0;
  v176 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[21].primary.bod, v176);
  initialize_screw_path_template_pair(&game->subgame.path_pairs[21].primary, 24, 3, (char *)1, texture_a);
  game->subgame.path_pairs[21].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[21].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[21].primary.bod.position.x = 0.0;
  v177 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[21].secondary.bod, v177);
  mirror_path_template_pair_x(&game->subgame.path_pairs[21].secondary, &game->subgame.path_pairs[21].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[21].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[21].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[21].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[21].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[21].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.x = 0.0;
  v178 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[22].primary.bod, v178);
  initialize_slalom_path_template_pair(&game->subgame.path_pairs[22].primary, 32, 4u, (char *)1, texture_a);
  game->subgame.path_pairs[22].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[22].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[22].primary.bod.position.x = 0.0;
  v179 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[22].secondary.bod, v179);
  mirror_path_template_pair_x(&game->subgame.path_pairs[22].secondary, &game->subgame.path_pairs[22].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[22].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[22].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[22].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[22].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[22].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.x = 0.0;
  v180 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[23].primary.bod, v180);
  initialize_slalombig_path_template_pair(&game->subgame.path_pairs[23].primary, 32, 4u, (char *)1, texture_a);
  game->subgame.path_pairs[23].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[23].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[23].primary.bod.position.x = 0.0;
  v181 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[23].secondary.bod, v181);
  mirror_path_template_pair_x(&game->subgame.path_pairs[23].secondary, &game->subgame.path_pairs[23].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[23].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[23].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[23].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[23].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[23].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.x = 0.0;
  v182 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[32].primary.bod, v182);
  *(_DWORD *)&v379[4] = texture_a;
  initialize_slalomdouble_path_template_pair(&game->subgame.path_pairs[32].primary, 32, (char *)4, (char *)1);
  game->subgame.path_pairs[32].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[32].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[32].primary.bod.position.x = 0.0;
  v183 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[32].secondary.bod, v183);
  mirror_path_template_pair_x(&game->subgame.path_pairs[32].secondary, &game->subgame.path_pairs[32].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[32].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[32].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[32].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[32].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[32].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.x = 0.0;
  v184 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].primary.bod, v184);
  initialize_worm_path_template_pair(&game->subgame.path_pairs[24].primary, aObjectsWorld00_4);
  game->subgame.path_pairs[24].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[24].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[24].primary.bod.position.x = 0.0;
  v185 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].secondary.bod, v185);
  mirror_path_template_pair_x(&game->subgame.path_pairs[24].secondary, &game->subgame.path_pairs[24].primary);
  game->subgame.path_pairs[24].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[24].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[24].secondary.bod.position.x = 0.0;
  v186 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].primary.fringe_mesh_bod, v186);
  disable_object_rendering((int)game->subgame.path_pairs[24].primary.fringe_mesh_bod.object);
  v187 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].secondary.fringe_mesh_bod, v187);
  disable_object_rendering((int)game->subgame.path_pairs[24].secondary.fringe_mesh_bod.object);
  game->subgame.path_pairs[24].primary.bod.object->blend_mode = 8;
  game->subgame.path_pairs[24].secondary.bod.object->blend_mode = 8;
  v188 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[28].primary.bod, v188);
  initialize_sweep_path_template_pair(&game->subgame.path_pairs[28].primary, 1082130432, (char *)4, (char *)1);
  game->subgame.path_pairs[28].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[28].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[28].primary.bod.position.x = 0.0;
  v189 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[28].secondary.bod, v189);
  mirror_path_template_pair_x(&game->subgame.path_pairs[28].secondary, &game->subgame.path_pairs[28].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[28].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[28].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[28].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[28].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[28].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.x = 0.0;
  v190 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[15].primary.bod, v190);
  initialize_cage2_path_template_pair(&game->subgame.path_pairs[15].primary, 3, texture_a, texture_b);
  game->subgame.path_pairs[15].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[15].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[15].primary.bod.position.x = 0.0;
  v191 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[15].secondary.bod, v191);
  mirror_path_template_pair_x(&game->subgame.path_pairs[15].secondary, &game->subgame.path_pairs[15].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[15].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[15].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[15].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[15].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[15].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.x = 0.0;
  v192 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[33].primary.bod, v192);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[33].primary,
    0,
    0x40800000u,
    COERCE_FLOAT(3),
    0.5,
    -1071644672,
    (char *)0xE,
    texture_a);
  game->subgame.path_pairs[33].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[33].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[33].primary.bod.position.x = 0.0;
  v193 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[33].secondary.bod, v193);
  mirror_path_template_pair_x(&game->subgame.path_pairs[33].secondary, &game->subgame.path_pairs[33].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[33].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[33].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[33].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[33].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[33].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.x = 0.0;
  v194 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[34].primary.bod, v194);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[34].primary,
    1,
    0x40800000u,
    COERCE_FLOAT(3),
    -2.5,
    1075838976,
    (char *)0xE,
    texture_a);
  game->subgame.path_pairs[34].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[34].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[34].primary.bod.position.x = 0.0;
  v195 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[34].secondary.bod, v195);
  mirror_path_template_pair_x(&game->subgame.path_pairs[34].secondary, &game->subgame.path_pairs[34].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[34].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[34].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[34].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[34].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[34].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.x = 0.0;
  v196 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[35].primary.bod, v196);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[35].primary,
    2,
    0x40800000u,
    COERCE_FLOAT(3),
    2.5,
    1056964608,
    (char *)0xE,
    texture_a);
  game->subgame.path_pairs[35].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[35].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[35].primary.bod.position.x = 0.0;
  v197 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[35].secondary.bod, v197);
  mirror_path_template_pair_x(&game->subgame.path_pairs[35].secondary, &game->subgame.path_pairs[35].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[35].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[35].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[35].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[35].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[35].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.x = 0.0;
  v198 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[29].primary.bod, v198);
  initialize_snake_path_template_pair(&game->subgame.path_pairs[29].primary, 0x40000000, (char *)4, (char *)1);
  game->subgame.path_pairs[29].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[29].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[29].primary.bod.position.x = 0.0;
  v199 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[29].secondary.bod, v199);
  mirror_path_template_pair_x(&game->subgame.path_pairs[29].secondary, &game->subgame.path_pairs[29].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[29].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[29].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[29].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[29].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[29].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.x = 0.0;
  v200 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[47].primary.bod, v200);
  initialize_toad_path_template_pair(&game->subgame.path_pairs[47].primary, 1, texture_a, aObjectsWorld00);
  game->subgame.path_pairs[47].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[47].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[47].primary.bod.position.x = 0.0;
  v201 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[47].secondary.bod, v201);
  mirror_path_template_pair_x(&game->subgame.path_pairs[47].secondary, &game->subgame.path_pairs[47].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[47].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[47].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[47].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[47].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[47].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.x = 0.0;
  v202 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[48].primary.bod, v202);
  initialize_toad_path_template_pair(&game->subgame.path_pairs[48].primary, 0, texture_a, aObjectsWorld00);
  game->subgame.path_pairs[48].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[48].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[48].primary.bod.position.x = 0.0;
  v203 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[48].secondary.bod, v203);
  mirror_path_template_pair_x(&game->subgame.path_pairs[48].secondary, &game->subgame.path_pairs[48].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[48].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[48].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[48].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[48].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[48].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.x = 0.0;
  v204 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[49].primary.bod, v204);
  initialize_toad_path_template_pair(&game->subgame.path_pairs[49].primary, 1, texture_a, aObjectsWorld00);
  game->subgame.path_pairs[49].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[49].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[49].primary.bod.position.x = 0.0;
  v205 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[49].secondary.bod, v205);
  mirror_path_template_pair_x(&game->subgame.path_pairs[49].secondary, &game->subgame.path_pairs[49].primary);
  *(_DWORD *)&v379[12] = -1082130432;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[49].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[49].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[49].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[49].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 1065353216;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[49].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.x = 0.0;
  v206 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[50].primary.bod, v206);
  initialize_toad_path_template_pair(&game->subgame.path_pairs[50].primary, 0, texture_a, aObjectsWorld00);
  game->subgame.path_pairs[50].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[50].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[50].primary.bod.position.x = 0.0;
  v207 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[50].secondary.bod, v207);
  mirror_path_template_pair_x(&game->subgame.path_pairs[50].secondary, &game->subgame.path_pairs[50].primary);
  *(_DWORD *)&v379[12] = 1065353216;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[50].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[50].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[50].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[50].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = -1082130432;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[50].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.x = 0.0;
  noop_this_constructor(&v379[40]);
  store_color4f((tColour *)&v379[40], 1.0, 1.0, 1.0, 0.60000002);
  v208 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[51].primary.bod, v208);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[51].primary, 6.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[51].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[51].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[51].primary.bod.position.x = 0.0;
  v209 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[51].secondary.bod, v209);
  mirror_path_template_pair_x(&game->subgame.path_pairs[51].secondary, &game->subgame.path_pairs[51].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[51].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[51].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[51].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[51].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[51].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.x = 0.0;
  v210 = game->subgame.path_pairs[0].primary.bod.object;
  v211 = game->subgame.path_pairs[51].secondary.bod.object;
  game->subgame.path_pairs[0].primary.entry_transition_strip_mesh = game->subgame.path_pairs[51].primary.bod.object;
  v212 = game->subgame.path_pairs[0].secondary.bod.object;
  game->subgame.path_pairs[0].primary.entry_base_strip_mesh = v210;
  game->subgame.path_pairs[0].secondary.entry_transition_strip_mesh = v211;
  game->subgame.path_pairs[0].secondary.entry_base_strip_mesh = v212;
  v213 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[52].primary.bod, v213);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[52].primary, 6.0, 2, (char *)1, texture_a);
  game->subgame.path_pairs[52].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[52].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[52].primary.bod.position.x = 0.0;
  v214 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[52].secondary.bod, v214);
  mirror_path_template_pair_x(&game->subgame.path_pairs[52].secondary, &game->subgame.path_pairs[52].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[52].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[52].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[52].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[52].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[52].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.x = 0.0;
  v215 = game->subgame.path_pairs[1].primary.bod.object;
  v216 = game->subgame.path_pairs[52].secondary.bod.object;
  game->subgame.path_pairs[1].primary.entry_transition_strip_mesh = game->subgame.path_pairs[52].primary.bod.object;
  game->subgame.path_pairs[1].secondary.entry_base_strip_mesh = game->subgame.path_pairs[1].secondary.bod.object;
  game->subgame.path_pairs[1].primary.entry_base_strip_mesh = v215;
  game->subgame.path_pairs[1].secondary.entry_transition_strip_mesh = v216;
  v217 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[53].primary.bod, v217);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[53].primary, 8.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[53].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[53].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[53].primary.bod.position.x = 0.0;
  v218 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[53].secondary.bod, v218);
  mirror_path_template_pair_x(&game->subgame.path_pairs[53].secondary, &game->subgame.path_pairs[53].primary);
  *(_DWORD *)&v379[12] = 0;
  game->subgame.path_pairs[53].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[53].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[53].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[53].primary, aObjectsUnivers_1, *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[53].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.x = 0.0;
  v219 = game->subgame.path_pairs[2].primary.bod.object;
  v220 = game->subgame.path_pairs[53].secondary.bod.object;
  game->subgame.path_pairs[2].primary.entry_transition_strip_mesh = game->subgame.path_pairs[53].primary.bod.object;
  game->subgame.path_pairs[2].primary.entry_base_strip_mesh = v219;
  game->subgame.path_pairs[2].secondary.entry_transition_strip_mesh = v220;
  game->subgame.path_pairs[2].secondary.entry_base_strip_mesh = game->subgame.path_pairs[2].secondary.bod.object;
  v221 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[57].primary.bod, v221);
  initialize_looptheloopw_path_template_pair(&game->subgame.path_pairs[57].primary, 8.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[57].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[57].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[57].primary.bod.position.x = 0.0;
  v222 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[57].secondary.bod, v222);
  mirror_path_template_pair_x(&game->subgame.path_pairs[57].secondary, &game->subgame.path_pairs[57].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[57].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[57].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[57].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[57].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[57].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[6].primary.entry_transition_strip_mesh = game->subgame.path_pairs[57].primary.bod.object;
  game->subgame.path_pairs[6].primary.entry_base_strip_mesh = game->subgame.path_pairs[6].primary.bod.object;
  game->subgame.path_pairs[6].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[57].secondary.bod.object;
  game->subgame.path_pairs[6].secondary.entry_base_strip_mesh = game->subgame.path_pairs[6].secondary.bod.object;
  v223 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[54].primary.bod, v223);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[54].primary, 3.0, 2, (char *)1, texture_a);
  game->subgame.path_pairs[54].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[54].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[54].primary.bod.position.x = 0.0;
  v224 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[54].secondary.bod, v224);
  mirror_path_template_pair_x(&game->subgame.path_pairs[54].secondary, &game->subgame.path_pairs[54].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[54].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[54].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[54].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[54].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[54].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[3].primary.entry_transition_strip_mesh = game->subgame.path_pairs[54].primary.bod.object;
  game->subgame.path_pairs[3].primary.entry_base_strip_mesh = game->subgame.path_pairs[3].primary.bod.object;
  game->subgame.path_pairs[3].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[54].secondary.bod.object;
  game->subgame.path_pairs[3].secondary.entry_base_strip_mesh = game->subgame.path_pairs[3].secondary.bod.object;
  v225 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[55].primary.bod, v225);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[55].primary, 3.0, 3, (char *)1, texture_a);
  game->subgame.path_pairs[55].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[55].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[55].primary.bod.position.x = 0.0;
  v226 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[55].secondary.bod, v226);
  mirror_path_template_pair_x(&game->subgame.path_pairs[55].secondary, &game->subgame.path_pairs[55].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[55].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[55].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[55].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[55].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[55].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[4].primary.entry_transition_strip_mesh = game->subgame.path_pairs[55].primary.bod.object;
  game->subgame.path_pairs[4].primary.entry_base_strip_mesh = game->subgame.path_pairs[4].primary.bod.object;
  game->subgame.path_pairs[4].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[55].secondary.bod.object;
  game->subgame.path_pairs[4].secondary.entry_base_strip_mesh = game->subgame.path_pairs[4].secondary.bod.object;
  v227 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[56].primary.bod, v227);
  initialize_looptheloop_path_template_pair(&game->subgame.path_pairs[56].primary, 3.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[56].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[56].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[56].primary.bod.position.x = 0.0;
  v228 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[56].secondary.bod, v228);
  mirror_path_template_pair_x(&game->subgame.path_pairs[56].secondary, &game->subgame.path_pairs[56].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[56].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[56].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[56].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[56].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[56].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[5].primary.entry_transition_strip_mesh = game->subgame.path_pairs[56].primary.bod.object;
  game->subgame.path_pairs[5].primary.entry_base_strip_mesh = game->subgame.path_pairs[5].primary.bod.object;
  game->subgame.path_pairs[5].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[56].secondary.bod.object;
  game->subgame.path_pairs[5].secondary.entry_base_strip_mesh = game->subgame.path_pairs[5].secondary.bod.object;
  v229 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[58].primary.bod, v229);
  initialize_loopbow_path_template_pair(&game->subgame.path_pairs[58].primary, 6.0, 4u, (char *)1, texture_a);
  game->subgame.path_pairs[58].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[58].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[58].primary.bod.position.x = 0.0;
  v230 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[58].secondary.bod, v230);
  mirror_path_template_pair_x(&game->subgame.path_pairs[58].secondary, &game->subgame.path_pairs[58].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[58].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[58].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[58].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[58].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[58].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[7].primary.entry_transition_strip_mesh = game->subgame.path_pairs[58].primary.bod.object;
  game->subgame.path_pairs[7].primary.entry_base_strip_mesh = game->subgame.path_pairs[7].primary.bod.object;
  game->subgame.path_pairs[7].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[58].secondary.bod.object;
  game->subgame.path_pairs[7].secondary.entry_base_strip_mesh = game->subgame.path_pairs[7].secondary.bod.object;
  v231 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[62].primary.bod, v231);
  *(_DWORD *)&v379[4] = texture_a;
  initialize_invert_path_template_pair(&game->subgame.path_pairs[62].primary, 1086324736, (char *)8, (char *)1);
  game->subgame.path_pairs[62].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[62].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[62].primary.bod.position.x = 0.0;
  v232 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[62].secondary.bod, v232);
  mirror_path_template_pair_x(&game->subgame.path_pairs[62].secondary, &game->subgame.path_pairs[62].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[62].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[62].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[62].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[62].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[62].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[41].primary.entry_transition_strip_mesh = game->subgame.path_pairs[62].primary.bod.object;
  game->subgame.path_pairs[41].primary.entry_base_strip_mesh = game->subgame.path_pairs[41].primary.bod.object;
  game->subgame.path_pairs[41].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[62].secondary.bod.object;
  game->subgame.path_pairs[41].secondary.entry_base_strip_mesh = game->subgame.path_pairs[41].secondary.bod.object;
  v233 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[59].primary.bod, v233);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[59].primary, 3.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[59].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[59].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[59].primary.bod.position.x = 0.0;
  v234 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[59].secondary.bod, v234);
  mirror_path_template_pair_x(&game->subgame.path_pairs[59].secondary, &game->subgame.path_pairs[59].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[59].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[59].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[59].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[59].primary, *(char **)&v379[8], *(float *)&v379[12]);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[59].secondary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[25].primary.entry_transition_strip_mesh = game->subgame.path_pairs[59].primary.bod.object;
  game->subgame.path_pairs[25].primary.entry_base_strip_mesh = game->subgame.path_pairs[25].primary.bod.object;
  game->subgame.path_pairs[25].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[59].secondary.bod.object;
  game->subgame.path_pairs[25].secondary.entry_base_strip_mesh = game->subgame.path_pairs[25].secondary.bod.object;
  v235 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[61].primary.bod, v235);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[61].primary, 5.0, 4, (char *)1, texture_a);
  game->subgame.path_pairs[61].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[61].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[61].primary.bod.position.x = 0.0;
  v236 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[61].secondary.bod, v236);
  mirror_path_template_pair_x(&game->subgame.path_pairs[61].secondary, &game->subgame.path_pairs[61].primary);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = aObjectsUnivers_1;
  game->subgame.path_pairs[61].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[61].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[61].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[61].primary, *(char **)&v379[8], *(float *)&v379[12]);
  game->subgame.path_pairs[61].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[61].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[61].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[61].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[61].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[61].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[61].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[27].primary.entry_transition_strip_mesh = game->subgame.path_pairs[61].primary.bod.object;
  game->subgame.path_pairs[27].primary.entry_base_strip_mesh = game->subgame.path_pairs[27].primary.bod.object;
  game->subgame.path_pairs[27].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[61].secondary.bod.object;
  game->subgame.path_pairs[27].secondary.entry_base_strip_mesh = game->subgame.path_pairs[27].secondary.bod.object;
  v237 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[60].primary.bod, v237);
  initialize_loopout_path_template_pair(&game->subgame.path_pairs[60].primary, 3.0, 3, (char *)1, texture_a);
  zero_vector3(&game->subgame.path_pairs[60].primary.bod.position.x);
  v238 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[60].secondary.bod, v238);
  mirror_path_template_pair_x(&game->subgame.path_pairs[60].secondary, &game->subgame.path_pairs[60].primary);
  zero_vector3(&game->subgame.path_pairs[60].secondary.bod.position.x);
  build_track_fringe_mesh(&game->subgame.path_pairs[60].primary, aObjectsUnivers_1, 0.0);
  zero_vector3(&game->subgame.path_pairs[60].primary.fringe_mesh_bod.position.x);
  build_track_fringe_mesh(&game->subgame.path_pairs[60].secondary, aObjectsUnivers_1, 0.0);
  zero_vector3(&game->subgame.path_pairs[60].secondary.fringe_mesh_bod.position.x);
  v239 = game->subgame.path_pairs[60].primary.bod.object;
  *(_DWORD *)&v379[12] = aPathGeneration_0;
  game->subgame.path_pairs[26].primary.entry_transition_strip_mesh = v239;
  game->subgame.path_pairs[26].primary.entry_base_strip_mesh = game->subgame.path_pairs[26].primary.bod.object;
  game->subgame.path_pairs[26].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[60].secondary.bod.object;
  game->subgame.path_pairs[26].secondary.entry_base_strip_mesh = game->subgame.path_pairs[26].secondary.bod.object;
  debug_report_stub();
  v240 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_43284A + 2], v240);
  case_insensitive_substring = find_case_insensitive_substring(aTest, *(char **)&game->unknown_044100[19712]);
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
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    ArgList,
    *(Object **)((char *)&loc_432870 + (_DWORD)game));
  v248 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4326FF + 1], v248);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    ArgList,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432720 + 4]);
  v249 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4328C8 + 4], v249);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    mesh_name,
    *(Object **)((char *)&loc_4328F0 + (_DWORD)game));
  v250 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43294C + (_DWORD)game), v250);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboBobalong0,
    *(Object **)((char *)&loc_432970 + (_DWORD)game));
  v251 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4329CC + (_DWORD)game), v251);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboLookbackl,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_4329EE + 2]);
  v252 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432A4A + 2], v252);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboLookbackr,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432A6D + 3]);
  v253 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432ACB + 1], v253);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboFall000X,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432AEF + 1]);
  v254 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432B49 + 3], v254);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboDamaged00,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432B6E + 2]);
  v255 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432BCA + 2], v255);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboIntoshell,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432BEF + 1]);
  v256 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432C48 + 4], v256);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboSkidstop0,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432C6D + 3]);
  v257 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432CCA + 2], v257);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurboTalk000X,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432CE9 + 7]);
  v258 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433D46 + 6], v258);
  load_x_mesh(
    (DirectXLoader *)&game->unknown_044100[19712],
    aTurbohotspotsX,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433D6F + 1],
    2);
  build_snail_hotspots((int)&game->unknown_000000[(_DWORD)&loc_4326FF + 1]);
  *(_DWORD *)&v379[36] = 10;
  *(_DWORD *)&v379[32] = (char *)&loc_432870 + (_DWORD)game;
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
  v264 = *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432720 + 4];
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v264 + 16) |= 4u;
  apply_object_toon(*(Object **)&game->unknown_000000[(_DWORD)&loc_432720 + 4], *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432720 + 4] + 128) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432720 + 4] + 132) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432720 + 4] + 136) = 0;
  v265 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4338DE + 2], v265);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aJetpackBase000,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433902 + 2]);
  v266 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433A2C + 4], v266);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aJetpackBase000,
    *(Object **)((char *)&loc_433A54 + (_DWORD)game));
  v267 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433AB0 + (_DWORD)game), v267);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aJetpackDraw000,
    *(Object **)((char *)&loc_433AD4 + (_DWORD)game));
  *(_DWORD *)&v379[36] = 2;
  *(_DWORD *)&v379[32] = (char *)&loc_433A54 + (_DWORD)game;
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
  v273 = *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433902 + 2];
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v273 + 16) |= 4u;
  apply_object_toon(*(Object **)&game->unknown_000000[(_DWORD)&loc_433902 + 2], *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433902 + 2] + 128) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433902 + 2] + 132) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433902 + 2] + 136) = 0;
  v274 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&byte_432D4C[(_DWORD)game], v274);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterleftBas,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432D6D + 3]);
  v275 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432E9A + 2], v275);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterleftBas,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_432EBF + 1]);
  v276 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432F1A + 2], v276);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterleftDra,
    *(Object **)((char *)&loc_432F40 + (_DWORD)game));
  v277 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_432F9B + 1], v277);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterleftFir,
    *(Object **)((char *)find_registered_sound_sample_id_by_name + (_DWORD)game));
  v278 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43301C + (_DWORD)game), v278);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aLaserleftBase0,
    *(Object **)((char *)get_authored_view_height + (_DWORD)game));
  v279 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43309C + (_DWORD)game), v279);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aLaserleftDraw0,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_4330BF + 1]);
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)game + (_DWORD)&loc_432EBF + 1;
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
  v285 = *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432D6D + 3];
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v285 + 16) |= 4u;
  apply_object_toon(*(Object **)&game->unknown_000000[(_DWORD)&loc_432D6D + 3], *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432D6D + 3] + 128) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432D6D + 3] + 132) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_432D6D + 3] + 136) = 0;
  v286 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433127 + 1], v286);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterrightBa,
    *(Object **)((char *)&loc_43314C + (_DWORD)game));
  v287 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433275 + 3], v287);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterrightBa,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_43329B + 1]);
  v288 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4332F7 + 1], v288);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterrightDr,
    *(Object **)((char *)&loc_43331C + (_DWORD)game));
  v289 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433378 + (_DWORD)game), v289);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlasterrightFi,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_43339A + 2]);
  v290 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4333F8 + (_DWORD)game), v290);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aLaserrightBase,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433417 + 5]);
  v291 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433475 + 3], v291);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aLaserrightDraw,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433499 + 3]);
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)game + (_DWORD)&loc_43329B + 1;
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
  v297 = *(_DWORD *)((char *)&loc_43314C + (_DWORD)game);
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v297 + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_43314C + (_DWORD)game), *(int32_t *)&v379[12]);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 136) = 0;
  v298 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433504 + (_DWORD)game), v298);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlastertopBase,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433523 + 5]);
  v299 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433654 + (_DWORD)game), v299);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlastertopBase,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433677 + 1]);
  v300 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4336D0 + 4], v300);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlastertopDraw,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_4336F6 + 2]);
  v301 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433751 + 3], v301);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aBlastertopFire,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433777 + 1]);
  v302 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4337D3 + 1], v302);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aRocketlauncher,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_4337F6 + 2]);
  v303 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_433853 + 1], v303);
  load_x_animation_clip(
    (DirectXLoader *)&game->unknown_044100[19712],
    aRocketlauncher_0,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_433877 + 1]);
  *(_DWORD *)&v379[36] = 5;
  *(_DWORD *)&v379[32] = (char *)game + (_DWORD)&loc_433677 + 1;
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
  v309 = *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433523 + 5];
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)(v309 + 16) |= 4u;
  apply_object_toon(*(Object **)&game->unknown_000000[(_DWORD)&loc_433523 + 5], *(int32_t *)&v379[12]);
  v310 = *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433523 + 5];
  *(_DWORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboTga_0;
  *(_DWORD *)(v310 + 128) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433523 + 5] + 132) = 0;
  *(_DWORD *)(*(_DWORD *)&game->unknown_000000[(_DWORD)&loc_433523 + 5] + 136) = 0;
  v311 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboDam;
  *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_434037 + 5] = v311;
  v312 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aXSnailTurboInv;
  *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_43403D + 3] = v312;
  *(_DWORD *)&game->unknown_000000[(_DWORD)&loc_434042 + 2] = get_or_create_texture_ref(
                                                                &g_texture_refs,
                                                                *(char **)&v379[4],
                                                                *(int32_t *)&v379[8],
                                                                *(int16_t *)&v379[12]);
  v313 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433F94 + (_DWORD)game), v313);
  load_x_mesh(
    (DirectXLoader *)&game->unknown_044100[19712],
    aInvincibleBase,
    *(Object **)((char *)&loc_433FB8 + (_DWORD)game),
    1);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433FB8 + (_DWORD)game) + 16) &= ~0x100000u;
  v314 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->unknown_000000[(_DWORD)&loc_4302E3 + 1], v314);
  load_x_mesh(
    (DirectXLoader *)&game->unknown_044100[19712],
    aRocketBase000X,
    *(Object **)&game->unknown_000000[(_DWORD)&loc_430306 + 2],
    1);
  v315 = &game->unknown_000000[(_DWORD)&loc_43026E + 2];
  *(_DWORD *)&v379[36] = 12;
  do
  {
    v316 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v315 - 36), v316);
    *(_DWORD *)(*(_DWORD *)v315 + 16) |= 0x100004u;
    *(_DWORD *)(*(_DWORD *)v315 + 20) = 9;
    load_object_definition(aObjectsVapourl, *(Object **)v315);
    initialize_vapour((Vapour *)(v315 - 36), *(Object **)v315, 0.16);
    set_bod_object((BodBase *)(v315 + 116), *(Object **)&game->unknown_000000[(_DWORD)&loc_430306 + 2]);
    v315 += 744;
    --*(_DWORD *)&v379[36];
  }
  while ( *(_DWORD *)&v379[36] );
  v317 = get_or_create_texture_ref(&g_texture_refs, aObjectsVapourl_0, 0, 0);
  v318 = v317->flags;
  *(_WORD *)&v379[12] = 0;
  BYTE1(v318) |= 4u;
  *(_DWORD *)&v379[8] = 0;
  v317->flags = v318;
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
  game->texture_set_selector.primary_textures[0] = v342;
  v343 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_5;
  game->texture_set_selector.secondary_textures[0] = v343;
  v344 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_6;
  game->texture_set_selector.primary_textures[1] = v344;
  v345 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_7;
  game->texture_set_selector.secondary_textures[1] = v345;
  v346 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_8;
  game->texture_set_selector.primary_textures[2] = v346;
  v347 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_9;
  game->texture_set_selector.secondary_textures[2] = v347;
  v348 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  *(_DWORD *)&v379[4] = aObjectsWorld00_10;
  game->texture_set_selector.primary_textures[3] = v348;
  v349 = get_or_create_texture_ref(&g_texture_refs, *(char **)&v379[4], *(int32_t *)&v379[8], *(int16_t *)&v379[12]);
  *(_WORD *)&v379[12] = 0;
  *(_DWORD *)&v379[8] = 0;
  game->texture_set_selector.secondary_textures[3] = v349;
  *(_DWORD *)&v379[4] = texture_b;
  game->texture_set_selector.current_texture_set = 0;
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
  set_bod_object(&game->subgame.barrier.bod, v360);
  load_object_definition(aObjectsBarrier, game->subgame.barrier.bod.object);
  zero_vector3(&game->subgame.barrier.bod.position.x);
  store_color4f(&game->subgame.barrier.bod.color, 1.0, 1.0, 1.0, 0.80000001);
  game->subgame.barrier.bod.object->blend_mode = 7;
  initialize_track_render_cache_manager(&game->subgame.segment_cache);
  *(_DWORD *)&v379[36] = 0;
  v361 = &game->unknown_044100[3284];
  do
  {
    *(_DWORD *)&v379[56] = 0;
    do
    {
      *(_DWORD *)&v379[32] = 0;
      v362 = (PathTemplateStripMesh **)v361;
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
      v361 = (uint8_t *)v362;
      ++*(_DWORD *)&v379[56];
    }
    while ( *(int *)&v379[56] < 4 );
    ++*(_DWORD *)&v379[36];
  }
  while ( *(int *)&v379[36] < 8 );
  v366 = get_or_create_texture_ref(&g_texture_refs, aObjectsUnivers_1, 0, 0);
  v367 = v366->flags;
  p_input = &game->game_inputs[0].input;
  BYTE1(v367) = ((unsigned __int16)v366->flags >> 8) | 4;
  v369 = 0;
  v366->flags = v367;
  do
  {
    add_bod_to_front(&game->active_bod_list.unknown_00, (int)&p_input[-1]);
    p_input->controller_slot = v369;
    initialize_input(p_input);
    ++v369;
    p_input += 2;
  }
  while ( v369 < 2 );
  player_count = game->player_count;
  *(_DWORD *)&v379[32] = 0;
  if ( player_count > 0 )
  {
    do
    {
      v371 = (char *)game + 504 * *(_DWORD *)&v379[32];
      *(_DWORD *)&v379[36] = v371;
      set_matrix_identity((TransformMatrix *)(v371 + 348));
      set_matrix_identity((TransformMatrix *)(v371 + 508));
      *(_DWORD *)&v379[12] = 1065353216;
      *(_DWORD *)&v379[8] = 1083131627;
      *(_DWORD *)&v379[4] = 1078412299;
      *(_DWORD *)v379 = -1056307500;
      v372 = &game->game_inputs[*(_DWORD *)&v379[32]];
      *((_DWORD *)v371 + 161) = 1121714176;
      *((_DWORD *)v371 + 163) = v372;
      qmemcpy(
        v371 + 348,
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
        game->players[0].frontend_state = 12;
      v374 = *(_DWORD *)&v379[36];
      *(_DWORD *)&v379[12] = g_runtime_config.last_entered_player_name;
      *(_BYTE *)(*(_DWORD *)&v379[36] + 781) = 0;
      *(_DWORD *)(v374 + 784) = 0;
      rstrcpy_checked_ascii((char *)(v374 + 420), *(char **)&v379[12]);
      v375 = game->player_count;
      ++*(_DWORD *)&v379[32];
    }
    while ( *(int *)&v379[32] < v375 );
  }
  initialize_high_score_tables((HighScoreBank *)&byte_6FFAE0[(_DWORD)game]);
  *(_DWORD *)&v379[12] = aScoreaDat;
  load_high_scores_from_file(&byte_6FFAE0[(_DWORD)game], *(CompletionResultScreen *)&v379[12]);
  *(_DWORD *)&v379[12] = aScorebDat;
  load_high_scores_from_file(&byte_6FFAE0[(_DWORD)game], *(CompletionResultScreen *)&v379[12]);
  *(_DWORD *)&v379[12] = aScorecDat;
  load_high_scores_from_file(&byte_6FFAE0[(_DWORD)game], *(CompletionResultScreen *)&v379[12]);
  game->subgame.selected_level_record_persistent = 0;
  game->subgame.selected_level_record_active = 0;
  initialize_tip_manager(&game->tip_manager);
  add_bod_to_front(&game->active_bod_list.unknown_00, (int)&game->tip_manager);
  add_bod_to_front(&g_game_base->active_bod_list.unknown_00, (int)&game->star_manager);
  open_star_field(&game->star_manager, 36);
  game->subgame.bottom_score_widget = nullptr;
  *(_DWORD *)&v379[12] = &game->backdrop;
  game->subgame.top_score_widget = nullptr;
  add_bod_to_front(&game->active_bod_list.unknown_00, *(int *)&v379[12]);
  *(_DWORD *)&v379[12] = &game->border_manager;
  game->backdrop.backdrop_render_enabled = 0;
  append_bod_to_end(&game->active_bod_list.unknown_00, *(_DWORD **)&v379[12]);
  initialize_border_stack(&game->border_manager.unknown_000010[40]);
  *(_DWORD *)&game->border_manager.unknown_000010[1648] = &game->border_manager;
  *(_DWORD *)&v379[12] = 1103626240;
  game->border_manager.unknown_000010[275856] = 0;
  set_border_justify_centre(&game->border_manager, *(float *)&v379[12]);
  v376 = &game->border_manager.unknown_000010[2068];
  v377 = 150;
  do
  {
    *(_DWORD *)v376 = 0;
    v376 += 1828;
    --v377;
  }
  while ( v377 );
  build_all_objects(&g_object_list);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[51].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[51].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[52].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[52].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[53].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[53].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[57].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[57].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[54].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[54].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[55].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[55].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[56].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[56].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[58].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[58].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[62].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[62].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[59].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[59].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[61].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[61].secondary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[60].primary.bod.object, *(tColour *)v379);
  *(_DWORD *)v379 = *(_DWORD *)&v379[40];
  *(_DWORD *)&v379[4] = *(_DWORD *)&v379[44];
  *(_DWORD *)&v379[8] = *(_DWORD *)&v379[48];
  *(_DWORD *)&v379[12] = *(_DWORD *)&v379[52];
  set_object_color(game->subgame.path_pairs[60].secondary.bod.object, *(tColour *)v379);
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  game->subgame.subgame_rebuild_selector = 2;
  return 1;
}
