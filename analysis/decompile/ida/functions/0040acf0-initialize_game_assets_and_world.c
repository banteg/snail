/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_game_assets_and_world @ 0x40acf0 */
/* selector: initialize_game_assets_and_world */

// Bootstraps the shared app world, front-end managers, score tables, star field, and the embedded 63-pair path-template bank. Public Path= slots 0..50 are constructed in place at GameRoot+0x1066f2c; slots 51..62 own transition meshes for flagged loop/invert families, HALFPIPE is the direct slot-42 constructor call, and WARP slot 30 remains unbuilt.
uint8_t __thiscall initialize_game_assets_and_world(GameRoot *game)
{
  FrameOverlay *p_overlay_0; // eax
  uint32_t *p_list_flags; // edx
  BodNode **p_first; // ecx
  BodNode *first; // edi
  struct BodNode *list_prev; // eax
  uint32_t v7; // eax
  FrameOverlay *p_overlay_2; // eax
  BodNode **v9; // ecx
  BodNode *v10; // edx
  struct BodNode *v11; // eax
  uint32_t v12; // ecx
  FrameOverlay *p_overlay_1; // ecx
  BodNode **v14; // eax
  BodNode *v15; // edx
  struct BodNode *v16; // ecx
  uint32_t v17; // ecx
  char *v18; // edi
  Object *v19; // eax
  Object *v20; // eax
  Object *v21; // eax
  double v22; // st7
  Object *v23; // eax
  Object *v24; // eax
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
  TextureRef *texture_ref; // eax
  Object *v48; // eax
  TextureRef *v49; // eax
  TextureRefFlags flags; // ecx
  Object *v51; // eax
  Object **p_object; // edi
  TextureRef *v53; // eax
  TextureRefFlags v54; // ecx
  Object *v55; // ecx
  bool v56; // zf
  Object *v57; // eax
  SubgameRuntime **p_owner_game; // edi
  int i; // edi
  Object *v60; // eax
  BodBase *p_track_body_list_head; // edi
  BodNode *v62; // ecx
  BodNode **v63; // eax
  struct BodNode *v64; // ecx
  uint32_t list_flags; // eax
  BodBase *p_barrier_sub_lazer_list_head; // eax
  uint32_t *v67; // ecx
  struct BodNode *list_next; // edx
  uint32_t v69; // eax
  BodBase *p_salt_hazard_list_head; // eax
  uint32_t *v71; // edx
  struct BodNode *v72; // ecx
  uint32_t v73; // eax
  BodBase *p_golb_vapour_list_head; // eax
  uint32_t *v75; // edx
  struct BodNode *v76; // ecx
  uint32_t v77; // eax
  BodBase *p_fringe_attachment_list_head; // eax
  uint32_t *v79; // edx
  struct BodNode *v80; // ecx
  uint32_t v81; // eax
  BodBase *p_special_track_cell_list_head; // eax
  uint32_t *v83; // edx
  struct BodNode *v84; // ecx
  uint32_t v85; // eax
  BodBase *p_unknown_bod_355cec; // eax
  uint32_t *v87; // edx
  struct BodNode *v88; // ecx
  uint32_t v89; // eax
  BodBase *p_landscape_slice_list_head; // eax
  uint32_t *v91; // edx
  struct BodNode *v92; // ecx
  uint32_t v93; // eax
  BodBase *p_unknown_bod_355c7c; // eax
  uint32_t *v95; // edx
  struct BodNode *v96; // ecx
  uint32_t v97; // eax
  Object *v98; // eax
  Object *v99; // eax
  Object *v100; // eax
  Object *v101; // eax
  Object *v102; // eax
  Object *v103; // eax
  Object *v104; // eax
  Object *v105; // eax
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
  Object *object; // ecx
  Object *v203; // edx
  Object *v204; // eax
  Object *v205; // eax
  Object *v206; // eax
  Object *v207; // edx
  Object *v208; // eax
  Object *v209; // eax
  Object *v210; // eax
  Object *v211; // eax
  Object *v212; // ecx
  Object *v213; // eax
  Object *v214; // eax
  Object *v215; // eax
  Object *v216; // eax
  Object *v217; // eax
  Object *v218; // eax
  Object *v219; // eax
  Object *v220; // eax
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
  char *case_insensitive_substring; // eax
  char *v233; // eax
  char v234; // cl
  char *v235; // edx
  char *v236; // eax
  int v237; // edx
  _BYTE *v238; // eax
  Object *v239; // eax
  Object *v240; // eax
  Object *v241; // eax
  Object *v242; // eax
  Object *v243; // eax
  Object *v244; // eax
  Object *v245; // eax
  Object *v246; // eax
  Object *v247; // eax
  Object *v248; // eax
  Object *v249; // eax
  Object *v250; // ecx
  Object *v251; // eax
  Object *v252; // eax
  Object *v253; // eax
  Object *v254; // edx
  Object *v255; // eax
  Object *v256; // eax
  Object *v257; // eax
  Object *v258; // eax
  Object *v259; // eax
  Object *v260; // eax
  Object *v261; // ecx
  Object *v262; // eax
  Object *v263; // eax
  Object *v264; // eax
  Object *v265; // eax
  Object *v266; // eax
  Object *v267; // eax
  Object *v268; // edx
  Object *v269; // eax
  Object *v270; // eax
  Object *v271; // eax
  Object *v272; // eax
  Object *v273; // eax
  Object *v274; // eax
  Object *v275; // ecx
  Object *v276; // eax
  Object *v277; // eax
  char *v278; // esi
  Object *v279; // eax
  TextureRef *v280; // eax
  TextureRefFlags v281; // ecx
  TextureRef *v282; // eax
  TextureRef *v283; // eax
  TextureRef *v284; // eax
  TextureRefFlags v285; // ecx
  TextureRef *v286; // eax
  TextureRef *v287; // eax
  TextureRef *v288; // eax
  TextureRef *v289; // eax
  TextureRef *v290; // eax
  TextureRef *v291; // eax
  TextureRef *v292; // eax
  TextureRef *v293; // eax
  Object *v294; // eax
  Object **v295; // eax
  Object **v296; // esi
  int j; // edi
  Object *v298; // eax
  Object *v299; // eax
  TextureRef *v300; // eax
  TextureRefFlags v301; // ecx
  InputState *p_input; // esi
  int v303; // edi
  int32_t *p_flags; // eax
  int v305; // ecx
  float x_offset; // [esp+10h] [ebp-12Ch]
  Object **x_offseta; // [esp+10h] [ebp-12Ch]
  Object **x_offsetb; // [esp+10h] [ebp-12Ch]
  Object **x_offsetc; // [esp+10h] [ebp-12Ch]
  Object **x_offsetd; // [esp+10h] [ebp-12Ch]
  Object **x_offsete; // [esp+10h] [ebp-12Ch]
  int x_offsetf; // [esp+10h] [ebp-12Ch]
  int32_t x_offsetg; // [esp+10h] [ebp-12Ch]
  uint32_t *edge_selector; // [esp+14h] [ebp-128h]
  uint32_t *edge_selectora; // [esp+14h] [ebp-128h]
  int32_t edge_selectorb; // [esp+14h] [ebp-128h]
  int32_t edge_selectorc; // [esp+14h] [ebp-128h]
  char *edge_selectord; // [esp+14h] [ebp-128h]
  int32_t edge_selectore; // [esp+14h] [ebp-128h]
  int32_t edge_selectorf; // [esp+14h] [ebp-128h]
  int32_t edge_selectorg; // [esp+14h] [ebp-128h]
  int32_t edge_selectorh; // [esp+14h] [ebp-128h]
  int32_t edge_selectori; // [esp+14h] [ebp-128h]
  int32_t edge_selectorj; // [esp+14h] [ebp-128h]
  int edge_selectork; // [esp+14h] [ebp-128h]
  char *edge_selectorl; // [esp+14h] [ebp-128h]
  Color4f color; // [esp+18h] [ebp-124h] BYREF
  int32_t orientation; // [esp+28h] [ebp-114h]
  TransformMatrix transform; // [esp+2Ch] [ebp-110h] BYREF
  char self[16]; // [esp+6Ch] [ebp-D0h] BYREF
  char ArgList[128]; // [esp+7Ch] [ebp-C0h] BYREF
  TransformMatrix v333; // [esp+FCh] [ebp-40h] BYREF

  noop_this_constructor(self);
  store_color4f((tColour *)&game->fog_color, 1.0, 1.0, 1.0, 1.0);
  game->fog_density = 1.0;
  game->fog_start = 30.0;
  game->fog_end = 50.0;
  game->fog_enabled = 1;
  game->player_count = 2;
  initialize_border_stack(&game->fade.state);
  game->frontend_link_latch = 0;
  game->subgame.subgame_pause_gate = 0;
  initialize_cheat(&g_cheat_state);
  game->intro.hide_for_replay_latch = 0;
  initialize_blink_random((float *)&game->subgame.scan_reset);
  set_subgame_rate(&game->subgame, 1.1);
  game->render_skip_count = 2;
  game->fixed_update_count = 1;
  initialize_texture_list(&g_texture_refs, 500);
  initialize_object_list(&g_object_list, 3000);
  game->unknown_000514 = 0;
  game->fixed_update_accumulator = 0.0;
  game->frame_counter = 0;
  game->inactive_bod_sentinel.bod.list_next = nullptr;
  game->active_bod_list.free_top = (BodNode *)&game->inactive_bod_sentinel;
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
      first->list_prev = (struct BodNode *)p_overlay_0;
      (*p_first)->list_prev->list_next = *p_first;
      list_prev = (*p_first)->list_prev;
      *p_first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      *p_first = (BodNode *)p_overlay_0;
      game->overlay_0.bod.bod.bod.list_prev = nullptr;
      (*p_first)->list_next = nullptr;
    }
    v7 = *p_list_flags;
    BYTE1(v7) = BYTE1(*p_list_flags) | 2;
    *p_list_flags = v7;
  }
  initialize_overlay((int)&game->overlay_0);
  memset(&g_directx_loader_scratch, 0, 0x15Cu);
  initialize_directx_loader(&game->directx_loader);
  reset_landscape_manager(&game->subgame.landscape_manager);
  load_segment_definitions(&game->subgame.sm_tracks);
  load_landscape_script_by_name(&game->subgame.landscape_manager, aStarmapTxt);
  load_landscape_script_by_name(&game->subgame.landscape_manager, aSplashTxt);
  load_landscape_script_by_name(&game->subgame.landscape_manager, g_help_script_path);
  game->subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector;
  bind_subgame_owner((SubgameOwnerLink *)&game->subgame.gui);
  bind_subgame_owner((SubgameOwnerLink *)&game->subgame.thanks_screen);
  load_galaxy_layout(&game->subgame.galaxy);
  initialize_cameraman((Cameraman *)((char *)&loc_42FF7C + (_DWORD)game));
  open_logo(&game->logo);
  initialize_sound_bank(&g_sound_effect_manager, g_sound_bank_entries);
  initialize_voice_manager(&g_voice_manager);
  apply_audio_config_volumes(&game->options);
  load_level_definitions(&game->subgame.sm_tracks);
  load_landscape_script_by_name(&g_game_base->subgame.landscape_manager, g_menu_background_script_path);
  load_builtin_segment_definitions(
    &game->subgame.level_definition_scratch,
    (SubSegmentRaw **)&g_builtin_segment_definitions);
  game->render_camera_slots[1].sort_key = 1;
  game->render_camera_slots[1].flags = 33554433;
  attach_render_camera_source(&game->render_camera_slots[1].unknown_00, (int)&game->players[0].camera);
  game->players[0].camera.render_mask = 0x2000000;
  game->render_camera_slots[4].sort_key = 1;
  game->render_camera_slots[4].flags = 268435459;
  attach_render_camera_source(&game->render_camera_slots[4].unknown_00, (int)&game->players[1].camera);
  game->players[1].camera.render_mask = 0x10000000;
  game->render_camera_slots[3].sort_key = 3;
  game->render_camera_slots[3].flags = 134217731;
  game->render_camera_slots[3].source = &game->overlay_2.camera;
  game->render_camera_slots[3].viewport_x = 0.0;
  game->render_camera_slots[3].viewport_y = 0.0;
  game->render_camera_slots[3].viewport_width = 1.0;
  game->render_camera_slots[3].viewport_height = 1.0;
  p_overlay_2 = &game->overlay_2;
  edge_selector = &game->overlay_2.bod.bod.bod.list_flags;
  if ( (game->overlay_2.bod.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v9 = &g_game_base->active_bod_list.first;
    v10 = g_game_base->active_bod_list.first;
    if ( v10 )
    {
      v10->list_prev = (struct BodNode *)p_overlay_2;
      (*v9)->list_prev->list_next = *v9;
      v11 = (*v9)->list_prev;
      *v9 = v11;
      v11->list_prev = nullptr;
    }
    else
    {
      *v9 = (BodNode *)p_overlay_2;
      game->overlay_2.bod.bod.bod.list_prev = nullptr;
      (*v9)->list_next = nullptr;
    }
    v12 = *edge_selector;
    BYTE1(v12) = BYTE1(*edge_selector) | 2;
    *edge_selector = v12;
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
  edge_selectora = &game->overlay_1.bod.bod.bod.list_flags;
  if ( (game->overlay_1.bod.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v14 = &g_game_base->active_bod_list.first;
    v15 = g_game_base->active_bod_list.first;
    if ( v15 )
    {
      v15->list_prev = (struct BodNode *)p_overlay_1;
      (*v14)->list_prev->list_next = *v14;
      v16 = (*v14)->list_prev;
      *v14 = v16;
      v16->list_prev = nullptr;
    }
    else
    {
      *v14 = (BodNode *)p_overlay_1;
      game->overlay_1.bod.bod.bod.list_prev = nullptr;
      (*v14)->list_next = nullptr;
    }
    v17 = *edge_selectora;
    BYTE1(v17) = BYTE1(*edge_selectora) | 2;
    *edge_selectora = v17;
  }
  initialize_overlay((int)&game->overlay_1);
  register_font_texture_sheet_wrapper(aObjectsFontFon, 2, 0.75, 1.0);
  initialize_font3d_objects(0);
  initialize_font_wave_state();
  initialize_sprite_manager(&g_sprite_manager);
  register_sprite_texture(&g_sprite_manager, (char *)aSpritesDebugTg, 1, 0);
  register_sprite_texture(&g_sprite_manager, aSpritesOverlay, 2, 0);
  register_sprite_texture(&g_sprite_manager, aSpritesBorderT, 5, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesMouseTg, 22, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesWarning, 94, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesPlayTga, 27, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesStartai, 32, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesJetTga, 33, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesHealthT, 57, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesDamageg, 89, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesDamageg_0, 90, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesDamageg_1, 91, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSparkTg, 92, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesBlackTg, 93, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesBorderg, 99, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSlug000, 118, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSlug001, 119, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSlugmas, 120, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParcel0, 121, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParceli, 122, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesGarbage, 114, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesGarbage_0, 115, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesGarbage_1, 116, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesGarbage_2, 117, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesLifeTga, 123, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesJetpack, 124, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSmokeTg, 128, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSluggoo, 129, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSliderb, 36, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesSliderb_0, 37, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesLessTga, 38, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesLesshov, 40, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesLessmas, 41, 1056);
  register_sprite_texture(&g_sprite_manager, aSpritesMoreTga, 42, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesMorehov, 44, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesMoremas, 45, 1056);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl, 130, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_0, 131, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_1, 132, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_2, 133, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_3, 134, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_4, 135, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesParticl_5, 136, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesCollisi, 137, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxySpacemap, 138, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00, 139, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_0, 140, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_1, 141, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_2, 142, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_3, 143, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_4, 144, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_5, 145, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_6, 146, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_7, 147, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxy00_8, 148, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyGalaxyse, 149, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyLevelsel, 150, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyLevelsta, 151, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyBordersp, 152, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyLineTga, 153, 1024);
  register_sprite_texture(&g_sprite_manager, aGalaxyLinestar, 154, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesProgres, 155, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesProgres_0, 156, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesProgres_1, 157, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesJetpack_0, 158, 1024);
  register_sprite_texture(&g_sprite_manager, aSpritesGhostTg, 159, 1024);
  x_offset = 0.0;
  do
  {
    v18 = (char *)game + 56 * (__int64)x_offset;
    v19 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v18 + 280464), v19);
    initialize_backdrop_slice_quad(*((Object **)v18 + 70125), aObjectsWorld00, x_offset);
    v20 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v18 + 280912), v20);
    initialize_backdrop_slice_quad(*((Object **)v18 + 70237), cap_texture, x_offset);
    v21 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v18 + 281360), v21);
    initialize_backdrop_slice_quad(*((Object **)v18 + 70349), texture_a, x_offset);
    v22 = x_offset + 1.0;
    x_offset = v22;
  }
  while ( v22 < 8.0 );
  set_matrix_identity(&transform);
  v23 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)game->root_bod_catalog.pillars, v23);
  load_x_mesh(&game->directx_loader, mesh_path, game->root_bod_catalog.pillars[0].object, 1);
  transform.position.x = 0.0;
  apply_bod_position((BodBase *)game->root_bod_catalog.pillars, &transform);
  v24 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[1], v24);
  load_x_mesh(&game->directx_loader, aPillar2X, game->root_bod_catalog.pillars[1].object, 1);
  transform.position.x = 0.5;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[1], &transform);
  v25 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[2], v25);
  load_x_mesh(&game->directx_loader, aPillar3X, game->root_bod_catalog.pillars[2].object, 1);
  transform.position.x = 1.0;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[2], &transform);
  v26 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[3], v26);
  load_x_mesh(&game->directx_loader, aPillar4X, game->root_bod_catalog.pillars[3].object, 1);
  transform.position.x = 1.5;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[3], &transform);
  v27 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[4], v27);
  load_x_mesh(&game->directx_loader, aPillar5X, game->root_bod_catalog.pillars[4].object, 1);
  transform.position.x = 2.0;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[4], &transform);
  v28 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[5], v28);
  load_x_mesh(&game->directx_loader, aPillar6X, game->root_bod_catalog.pillars[5].object, 1);
  transform.position.x = 2.5;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[5], &transform);
  v29 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[6], v29);
  load_x_mesh(&game->directx_loader, aPillar7X, game->root_bod_catalog.pillars[6].object, 1);
  transform.position.x = 3.0;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[6], &transform);
  v30 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.pillars[7], v30);
  load_x_mesh(&game->directx_loader, aPillar8X, game->root_bod_catalog.pillars[7].object, 1);
  transform.position.x = 3.5;
  apply_bod_position((BodBase *)&game->root_bod_catalog.pillars[7], &transform);
  v31 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)game->root_bod_catalog.ramp_edges, v31);
  initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[0].object, aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(-1, game->root_bod_catalog.ramp_edges[0].object);
  v32 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.ramp_edges[1], v32);
  initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[1].object, aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(0, game->root_bod_catalog.ramp_edges[1].object);
  v33 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.ramp_edges[2], v33);
  initialize_textured_backdrop_quad(game->root_bod_catalog.ramp_edges[2].object, aObjectsUnivers, 0.0);
  raise_backdrop_quad_edge_pair(1, game->root_bod_catalog.ramp_edges[2].object);
  v34 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.floor_corners, v34);
  initialize_backdrop_corner_quad(0, game->root_bod_catalog.floor_corners.storage[0].object, aObjectsWorld00);
  v35 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.floor_corners.storage[1], v35);
  initialize_backdrop_corner_quad(1, game->root_bod_catalog.floor_corners.storage[1].object, aObjectsWorld00);
  v36 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.floor_corners.storage[3], v36);
  initialize_backdrop_corner_quad(2, game->root_bod_catalog.floor_corners.storage[3].object, aObjectsWorld00);
  v37 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.floor_corners.storage[2], v37);
  initialize_backdrop_corner_quad(3, game->root_bod_catalog.floor_corners.storage[2].object, aObjectsWorld00);
  v38 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.warning_corners, v38);
  initialize_backdrop_corner_quad(0, game->root_bod_catalog.warning_corners.storage[0].object, cap_texture);
  v39 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.warning_corners.storage[1], v39);
  initialize_backdrop_corner_quad(1, game->root_bod_catalog.warning_corners.storage[1].object, cap_texture);
  v40 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.warning_corners.storage[3], v40);
  initialize_backdrop_corner_quad(2, game->root_bod_catalog.warning_corners.storage[3].object, cap_texture);
  v41 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.warning_corners.storage[2], v41);
  initialize_backdrop_corner_quad(3, game->root_bod_catalog.warning_corners.storage[2].object, cap_texture);
  v42 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.slide_corners, v42);
  initialize_backdrop_corner_quad(0, game->root_bod_catalog.slide_corners.storage[0].object, texture_a);
  v43 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.slide_corners.storage[1], v43);
  initialize_backdrop_corner_quad(1, game->root_bod_catalog.slide_corners.storage[1].object, texture_a);
  v44 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.slide_corners.storage[3], v44);
  initialize_backdrop_corner_quad(2, game->root_bod_catalog.slide_corners.storage[3].object, texture_a);
  v45 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.slide_corners.storage[2], v45);
  initialize_backdrop_corner_quad(3, game->root_bod_catalog.slide_corners.storage[2].object, texture_a);
  v46 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.trampoline, v46);
  load_x_mesh(&game->directx_loader, aTrampX, game->root_bod_catalog.trampoline.object, 1);
  game->root_bod_catalog.trampoline.object->blend_mode = 6;
  texture_ref = game->root_bod_catalog.trampoline.object->facequads->texture_ref;
  texture_ref->flags |= 0x400u;
  v48 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog, v48);
  initialize_textured_backdrop_quad(game->root_bod_catalog.universe_hole.object, aObjectsUnivers_0, 0.0);
  game->root_bod_catalog.universe_hole.object->blend_mode = 5;
  v49 = game->root_bod_catalog.universe_hole.object->facequads->texture_ref;
  flags = v49->flags;
  BYTE1(flags) = ((unsigned __int16)v49->flags >> 8) | 4;
  v49->flags = flags;
  v51 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.lazer_model, v51);
  load_object_definition(path, game->root_bod_catalog.lazer_model.object);
  p_object = &game->subgame.sub_lazers.slots[0].body.bod.object;
  edge_selectorb = 20;
  do
  {
    set_bod_object((BodBase *)(p_object - 9), game->root_bod_catalog.lazer_model.object);
    v53 = (*p_object)->facequads->texture_ref;
    v54 = v53->flags;
    BYTE1(v54) = ((unsigned __int16)v53->flags >> 8) | 4;
    v53->flags = v54;
    p_object[25] = (Object *)&game->subgame;
    store_color4f((tColour *)(p_object + 1), 1.0, 1.0, 1.0, 0.69999999);
    v55 = *p_object;
    p_object += 44;
    v56 = edge_selectorb == 1;
    v55->blend_mode = 9;
    --edge_selectorb;
  }
  while ( !v56 );
  v57 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&game->root_bod_catalog.salt_model, v57);
  load_x_mesh(&game->directx_loader, aSaltX, game->root_bod_catalog.salt_model.object, 1);
  p_owner_game = &game->subgame.salt_hazards.slots[0].owner_game;
  edge_selectorc = 40;
  do
  {
    set_bod_object((BodBase *)(p_owner_game - 34), game->root_bod_catalog.salt_model.object);
    *p_owner_game = &game->subgame;
    store_color4f((tColour *)p_owner_game - 6, 1.0, 1.0, 1.0, 0.89999998);
    (*(p_owner_game - 25))->sub_pause.options_widget = (FrontendWidget *)12;
    set_matrix_identity((TransformMatrix *)(p_owner_game - 20));
    p_owner_game += 38;
    --edge_selectorc;
  }
  while ( edge_selectorc );
  for ( i = 0; i < 2; ++i )
  {
    edge_selectord = (char *)game + 96 * i;
    v60 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(edge_selectord + 3987096), v60);
    if ( i )
    {
      if ( i == 1 )
        load_x_mesh(&game->directx_loader, aPostofficestop, game->subgame.banners.slots[1].bod.object, 1);
    }
    else
    {
      load_x_mesh(&game->directx_loader, aPostofficestop, game->subgame.banners.slots[0].bod.object, 1);
    }
    *((_DWORD *)edge_selectord + 996780) = 0;
    *((_DWORD *)edge_selectord + 996779) = 0;
    *((_DWORD *)edge_selectord + 996778) = 0;
    game->subgame.banners.slots[i].owner_game = &game->subgame;
    *((_DWORD *)edge_selectord + 996788) = i;
    *((_DWORD *)edge_selectord + 996796) = 0;
    *((_DWORD *)edge_selectord + 996797) = 1004768824;
  }
  p_track_body_list_head = &game->subgame.track_body_list_head;
  if ( (game->subgame.track_body_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    v62 = game->active_bod_list.first;
    v63 = &game->active_bod_list.first;
    if ( v62 )
    {
      v62->list_prev = &p_track_body_list_head->bod;
      (*v63)->list_prev->list_next = *v63;
      v64 = (*v63)->list_prev;
      *v63 = v64;
      v64->list_prev = nullptr;
    }
    else
    {
      *v63 = &p_track_body_list_head->bod;
      game->subgame.track_body_list_head.bod.list_prev = nullptr;
      (*v63)->list_next = nullptr;
    }
    list_flags = game->subgame.track_body_list_head.bod.list_flags;
    BYTE1(list_flags) |= 2u;
    game->subgame.track_body_list_head.bod.list_flags = list_flags;
  }
  p_barrier_sub_lazer_list_head = &game->subgame.barrier_sub_lazer_list_head;
  v67 = &game->subgame.barrier_sub_lazer_list_head.bod.list_flags;
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
    v69 = *v67;
    BYTE1(v69) = BYTE1(*v67) | 2;
    *v67 = v69;
  }
  p_salt_hazard_list_head = &game->subgame.salt_hazard_list_head;
  v71 = &game->subgame.salt_hazard_list_head.bod.list_flags;
  if ( (game->subgame.salt_hazard_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.salt_hazard_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.salt_hazard_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_salt_hazard_list_head->bod;
    v72 = game->subgame.salt_hazard_list_head.bod.list_next;
    if ( v72 )
      v72->list_prev = &p_salt_hazard_list_head->bod;
    v73 = *v71;
    BYTE1(v73) = BYTE1(*v71) | 2;
    *v71 = v73;
  }
  p_golb_vapour_list_head = &game->subgame.golb_vapour_list_head;
  v75 = &game->subgame.golb_vapour_list_head.bod.list_flags;
  if ( (game->subgame.golb_vapour_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.golb_vapour_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.golb_vapour_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_golb_vapour_list_head->bod;
    v76 = game->subgame.golb_vapour_list_head.bod.list_next;
    if ( v76 )
      v76->list_prev = &p_golb_vapour_list_head->bod;
    v77 = *v75;
    BYTE1(v77) = BYTE1(*v75) | 2;
    *v75 = v77;
  }
  p_fringe_attachment_list_head = &game->subgame.fringe_attachment_list_head;
  v79 = &game->subgame.fringe_attachment_list_head.bod.list_flags;
  if ( (game->subgame.fringe_attachment_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.fringe_attachment_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.fringe_attachment_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_fringe_attachment_list_head->bod;
    v80 = game->subgame.fringe_attachment_list_head.bod.list_next;
    if ( v80 )
      v80->list_prev = &p_fringe_attachment_list_head->bod;
    v81 = *v79;
    BYTE1(v81) = BYTE1(*v79) | 2;
    *v79 = v81;
  }
  p_special_track_cell_list_head = &game->subgame.special_track_cell_list_head;
  v83 = &game->subgame.special_track_cell_list_head.bod.list_flags;
  if ( (game->subgame.special_track_cell_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.special_track_cell_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.special_track_cell_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_special_track_cell_list_head->bod;
    v84 = game->subgame.special_track_cell_list_head.bod.list_next;
    if ( v84 )
      v84->list_prev = &p_special_track_cell_list_head->bod;
    v85 = *v83;
    BYTE1(v85) = BYTE1(*v83) | 2;
    *v83 = v85;
  }
  p_unknown_bod_355cec = &game->subgame.unknown_bod_355cec;
  v87 = &game->subgame.unknown_bod_355cec.bod.list_flags;
  if ( (game->subgame.unknown_bod_355cec.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.unknown_bod_355cec.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.unknown_bod_355cec.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_unknown_bod_355cec->bod;
    v88 = game->subgame.unknown_bod_355cec.bod.list_next;
    if ( v88 )
      v88->list_prev = &p_unknown_bod_355cec->bod;
    v89 = *v87;
    BYTE1(v89) = BYTE1(*v87) | 2;
    *v87 = v89;
  }
  p_landscape_slice_list_head = &game->subgame.landscape_slice_list_head;
  v91 = &game->subgame.landscape_slice_list_head.bod.list_flags;
  if ( (game->subgame.landscape_slice_list_head.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.landscape_slice_list_head.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.landscape_slice_list_head.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_landscape_slice_list_head->bod;
    v92 = game->subgame.landscape_slice_list_head.bod.list_next;
    if ( v92 )
      v92->list_prev = &p_landscape_slice_list_head->bod;
    v93 = *v91;
    BYTE1(v93) = BYTE1(*v91) | 2;
    *v91 = v93;
  }
  p_unknown_bod_355c7c = &game->subgame.unknown_bod_355c7c;
  v95 = &game->subgame.unknown_bod_355c7c.bod.list_flags;
  if ( (game->subgame.unknown_bod_355c7c.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    game->subgame.unknown_bod_355c7c.bod.list_prev = &p_track_body_list_head->bod;
    game->subgame.unknown_bod_355c7c.bod.list_next = game->subgame.track_body_list_head.bod.list_next;
    game->subgame.track_body_list_head.bod.list_next = &p_unknown_bod_355c7c->bod;
    v96 = game->subgame.unknown_bod_355c7c.bod.list_next;
    if ( v96 )
      v96->list_prev = &p_unknown_bod_355c7c->bod;
    v97 = *v95;
    BYTE1(v97) = BYTE1(*v95) | 2;
    *v95 = v97;
  }
  debug_report_stub();
  v98 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[0].primary.bod, v98);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[0].primary,
    6.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[0].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[0].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[0].primary.bod.position.x = 0.0;
  v99 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[0].secondary.bod, v99);
  mirror_path_template_pair_x(&game->subgame.path_pairs[0].secondary, &game->subgame.path_pairs[0].primary);
  game->subgame.path_pairs[0].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[0].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[0].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[0].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[0].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[0].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[0].secondary.fringe_mesh_bod.position.x = 0.0;
  v100 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[1].primary.bod, v100);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[1].primary,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[1].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[1].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[1].primary.bod.position.x = 0.0;
  v101 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[1].secondary.bod, v101);
  mirror_path_template_pair_x(&game->subgame.path_pairs[1].secondary, &game->subgame.path_pairs[1].primary);
  game->subgame.path_pairs[1].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[1].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[1].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[1].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[1].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[1].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[1].secondary.fringe_mesh_bod.position.x = 0.0;
  v102 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[2].primary.bod, v102);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[2].primary,
    8.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[2].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[2].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[2].primary.bod.position.x = 0.0;
  v103 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[2].secondary.bod, v103);
  mirror_path_template_pair_x(&game->subgame.path_pairs[2].secondary, &game->subgame.path_pairs[2].primary);
  game->subgame.path_pairs[2].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[2].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[2].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[2].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[2].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[2].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[2].secondary.fringe_mesh_bod.position.x = 0.0;
  v104 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[6].primary.bod, v104);
  initialize_looptheloopw_path_template_pair(
    &game->subgame.path_pairs[6].primary,
    8.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[6].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[6].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[6].primary.bod.position.x = 0.0;
  v105 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[6].secondary.bod, v105);
  mirror_path_template_pair_x(&game->subgame.path_pairs[6].secondary, &game->subgame.path_pairs[6].primary);
  game->subgame.path_pairs[6].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[6].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[6].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[6].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[6].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[6].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[6].secondary.fringe_mesh_bod.position.x = 0.0;
  v106 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[3].primary.bod, v106);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[3].primary,
    3.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[3].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[3].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[3].primary.bod.position.x = 0.0;
  v107 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[3].secondary.bod, v107);
  mirror_path_template_pair_x(&game->subgame.path_pairs[3].secondary, &game->subgame.path_pairs[3].primary);
  game->subgame.path_pairs[3].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[3].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[3].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[3].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[3].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[3].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[3].secondary.fringe_mesh_bod.position.x = 0.0;
  v108 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[4].primary.bod, v108);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[4].primary,
    3.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[4].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[4].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[4].primary.bod.position.x = 0.0;
  v109 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[4].secondary.bod, v109);
  mirror_path_template_pair_x(&game->subgame.path_pairs[4].secondary, &game->subgame.path_pairs[4].primary);
  game->subgame.path_pairs[4].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[4].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[4].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[4].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[4].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[4].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[4].secondary.fringe_mesh_bod.position.x = 0.0;
  v110 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[5].primary.bod, v110);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[5].primary,
    3.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[5].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[5].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[5].primary.bod.position.x = 0.0;
  v111 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[5].secondary.bod, v111);
  mirror_path_template_pair_x(&game->subgame.path_pairs[5].secondary, &game->subgame.path_pairs[5].primary);
  game->subgame.path_pairs[5].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[5].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[5].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[5].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[5].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[5].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[5].secondary.fringe_mesh_bod.position.x = 0.0;
  v112 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[7].primary.bod, v112);
  initialize_loopbow_path_template_pair(
    &game->subgame.path_pairs[7].primary,
    6.0,
    4u,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[7].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[7].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[7].primary.bod.position.x = 0.0;
  v113 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[7].secondary.bod, v113);
  mirror_path_template_pair_x(&game->subgame.path_pairs[7].secondary, &game->subgame.path_pairs[7].primary);
  game->subgame.path_pairs[7].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[7].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[7].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[7].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[7].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[7].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[7].secondary.fringe_mesh_bod.position.x = 0.0;
  v114 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[37].primary.bod, v114);
  initialize_turnover_path_template_pair(
    &game->subgame.path_pairs[37].primary,
    6.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[37].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[37].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[37].primary.bod.position.x = 0.0;
  v115 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[37].secondary.bod, v115);
  mirror_path_template_pair_x(&game->subgame.path_pairs[37].secondary, &game->subgame.path_pairs[37].primary);
  game->subgame.path_pairs[37].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[37].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[37].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[37].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[37].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[37].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[37].secondary.fringe_mesh_bod.position.x = 0.0;
  v116 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[38].primary.bod, v116);
  initialize_turnoverdouble_path_template_pair(
    &game->subgame.path_pairs[38].primary,
    6.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[38].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[38].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[38].primary.bod.position.x = 0.0;
  v117 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[38].secondary.bod, v117);
  mirror_path_template_pair_x(&game->subgame.path_pairs[38].secondary, &game->subgame.path_pairs[38].primary);
  game->subgame.path_pairs[38].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[38].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[38].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[38].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[38].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[38].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[38].secondary.fringe_mesh_bod.position.x = 0.0;
  v118 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[43].primary.bod, v118);
  initialize_twister_path_template_pair(
    &game->subgame.path_pairs[43].primary,
    2.5,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[43].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[43].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[43].primary.bod.position.x = 0.0;
  v119 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[43].secondary.bod, v119);
  mirror_path_template_pair_x(&game->subgame.path_pairs[43].secondary, &game->subgame.path_pairs[43].primary);
  game->subgame.path_pairs[43].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[43].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[43].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[43].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[43].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[43].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[43].secondary.fringe_mesh_bod.position.x = 0.0;
  v120 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[44].primary.bod, v120);
  initialize_twister_path_template_pair(
    &game->subgame.path_pairs[44].primary,
    2.5,
    3,
    0,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[44].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[44].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[44].primary.bod.position.x = 0.0;
  v121 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[44].secondary.bod, v121);
  mirror_path_template_pair_x(&game->subgame.path_pairs[44].secondary, &game->subgame.path_pairs[44].primary);
  game->subgame.path_pairs[44].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[44].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[44].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[44].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[44].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[44].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[44].secondary.fringe_mesh_bod.position.x = 0.0;
  v122 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[45].primary.bod, v122);
  initialize_twister2_path_template_pair(
    &game->subgame.path_pairs[45].primary,
    2.5,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[45].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[45].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[45].primary.bod.position.x = 0.0;
  v123 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[45].secondary.bod, v123);
  mirror_path_template_pair_x(&game->subgame.path_pairs[45].secondary, &game->subgame.path_pairs[45].primary);
  game->subgame.path_pairs[45].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[45].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[45].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[45].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[45].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[45].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[45].secondary.fringe_mesh_bod.position.x = 0.0;
  v124 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[46].primary.bod, v124);
  initialize_twister2_path_template_pair(
    &game->subgame.path_pairs[46].primary,
    2.5,
    3,
    0,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[46].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[46].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[46].primary.bod.position.x = 0.0;
  v125 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[46].secondary.bod, v125);
  mirror_path_template_pair_x(&game->subgame.path_pairs[46].secondary, &game->subgame.path_pairs[46].primary);
  game->subgame.path_pairs[46].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[46].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[46].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[46].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[46].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[46].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[46].secondary.fringe_mesh_bod.position.x = 0.0;
  v126 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[39].primary.bod, v126);
  initialize_turnunder_path_template_pair(
    &game->subgame.path_pairs[39].primary,
    6.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[39].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[39].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[39].primary.bod.position.x = 0.0;
  v127 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[39].secondary.bod, v127);
  mirror_path_template_pair_x(&game->subgame.path_pairs[39].secondary, &game->subgame.path_pairs[39].primary);
  game->subgame.path_pairs[39].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[39].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[39].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[39].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[39].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[39].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[39].secondary.fringe_mesh_bod.position.x = 0.0;
  v128 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[41].primary.bod, v128);
  initialize_invert_path_template_pair(
    &game->subgame.path_pairs[41].primary,
    6.0,
    8,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[41].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[41].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[41].primary.bod.position.x = 0.0;
  v129 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[41].secondary.bod, v129);
  mirror_path_template_pair_x(&game->subgame.path_pairs[41].secondary, &game->subgame.path_pairs[41].primary);
  game->subgame.path_pairs[41].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[41].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[41].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[41].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[41].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[41].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[41].secondary.fringe_mesh_bod.position.x = 0.0;
  v130 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[42].primary.bod, v130);
  initialize_halfpipe_path_template_pair(
    &game->subgame.path_pairs[42].primary,
    6.0,
    8,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[42].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[42].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[42].primary.bod.position.x = 0.0;
  v131 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[42].secondary.bod, v131);
  mirror_path_template_pair_x(&game->subgame.path_pairs[42].secondary, &game->subgame.path_pairs[42].primary);
  game->subgame.path_pairs[42].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[42].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[42].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[42].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[42].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[42].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[42].secondary.fringe_mesh_bod.position.x = 0.0;
  v132 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[40].primary.bod, v132);
  initialize_wibble_path_template_pair(
    &game->subgame.path_pairs[40].primary,
    6.0,
    8,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[40].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[40].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[40].primary.bod.position.x = 0.0;
  v133 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[40].secondary.bod, v133);
  mirror_path_template_pair_x(&game->subgame.path_pairs[40].secondary, &game->subgame.path_pairs[40].primary);
  game->subgame.path_pairs[40].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[40].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[40].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[40].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[40].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[40].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[40].secondary.fringe_mesh_bod.position.x = 0.0;
  v134 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[31].primary.bod, v134);
  initialize_supertramp_path_template_pair(
    &game->subgame.path_pairs[31].primary,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture,
    cap_texture);
  game->subgame.path_pairs[31].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[31].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[31].primary.bod.position.x = 0.0;
  build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[31].primary, aObjectsUnivers_1);
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[31].primary.fringe_mesh_bod.position.x = 0.0;
  v135 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[31].secondary.bod, v135);
  initialize_supertramp_path_template_pair(
    &game->subgame.path_pairs[31].secondary,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture,
    cap_texture);
  game->subgame.path_pairs[31].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[31].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[31].secondary.bod.position.x = 0.0;
  build_track_fringe_supertramp_mesh(&game->subgame.path_pairs[31].secondary, aObjectsUnivers_1);
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[31].secondary.fringe_mesh_bod.position.x = 0.0;
  v136 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[36].primary.bod, v136);
  initialize_start_path_template_pair(
    &game->subgame.path_pairs[36].primary,
    4.0,
    8,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[36].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[36].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[36].primary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[36].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[36].primary.fringe_mesh_bod.position.x = 0.0;
  v137 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[36].secondary.bod, v137);
  initialize_start_path_template_pair(
    &game->subgame.path_pairs[36].secondary,
    4.0,
    8,
    1,
    texture_a,
    aObjectsWorld00_3,
    vertical_texture);
  game->subgame.path_pairs[36].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[36].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[36].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[36].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[36].secondary.fringe_mesh_bod.position.x = 0.0;
  v138 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[25].primary.bod, v138);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[25].primary,
    3.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[25].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[25].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[25].primary.bod.position.x = 0.0;
  v139 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[25].secondary.bod, v139);
  mirror_path_template_pair_x(&game->subgame.path_pairs[25].secondary, &game->subgame.path_pairs[25].primary);
  game->subgame.path_pairs[25].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[25].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[25].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[25].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[25].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[25].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[25].secondary.fringe_mesh_bod.position.x = 0.0;
  v140 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[27].primary.bod, v140);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[27].primary,
    5.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[27].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[27].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[27].primary.bod.position.x = 0.0;
  v141 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[27].secondary.bod, v141);
  mirror_path_template_pair_x(&game->subgame.path_pairs[27].secondary, &game->subgame.path_pairs[27].primary);
  game->subgame.path_pairs[27].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[27].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[27].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[27].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[27].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[27].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[27].secondary.fringe_mesh_bod.position.x = 0.0;
  v142 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[26].primary.bod, v142);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[26].primary,
    3.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[26].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[26].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[26].primary.bod.position.x = 0.0;
  v143 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[26].secondary.bod, v143);
  mirror_path_template_pair_x(&game->subgame.path_pairs[26].secondary, &game->subgame.path_pairs[26].primary);
  game->subgame.path_pairs[26].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[26].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[26].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[26].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[26].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[26].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[26].secondary.fringe_mesh_bod.position.x = 0.0;
  v144 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[16].primary.bod, v144);
  initialize_hump_path_template_pair(
    &game->subgame.path_pairs[16].primary,
    4.0,
    1.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[16].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[16].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[16].primary.bod.position.x = 0.0;
  v145 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[16].secondary.bod, v145);
  mirror_path_template_pair_x(&game->subgame.path_pairs[16].secondary, &game->subgame.path_pairs[16].primary);
  game->subgame.path_pairs[16].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[16].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[16].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[16].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[16].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[16].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[16].secondary.fringe_mesh_bod.position.x = 0.0;
  v146 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[17].primary.bod, v146);
  initialize_dump_path_template_pair(
    &game->subgame.path_pairs[17].primary,
    4.0,
    1.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[17].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[17].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[17].primary.bod.position.x = 0.0;
  v147 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[17].secondary.bod, v147);
  mirror_path_template_pair_x(&game->subgame.path_pairs[17].secondary, &game->subgame.path_pairs[17].primary);
  game->subgame.path_pairs[17].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[17].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[17].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[17].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[17].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[17].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[17].secondary.fringe_mesh_bod.position.x = 0.0;
  v148 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[18].primary.bod, v148);
  initialize_hump_path_template_pair(
    &game->subgame.path_pairs[18].primary,
    4.0,
    0.30000001,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[18].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[18].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[18].primary.bod.position.x = 0.0;
  v149 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[18].secondary.bod, v149);
  mirror_path_template_pair_x(&game->subgame.path_pairs[18].secondary, &game->subgame.path_pairs[18].primary);
  game->subgame.path_pairs[18].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[18].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[18].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[18].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[18].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[18].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[18].secondary.fringe_mesh_bod.position.x = 0.0;
  v150 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[19].primary.bod, v150);
  initialize_dump_path_template_pair(
    &game->subgame.path_pairs[19].primary,
    4.0,
    0.30000001,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[19].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[19].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[19].primary.bod.position.x = 0.0;
  v151 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[19].secondary.bod, v151);
  mirror_path_template_pair_x(&game->subgame.path_pairs[19].secondary, &game->subgame.path_pairs[19].primary);
  game->subgame.path_pairs[19].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[19].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[19].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[19].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[19].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[19].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[19].secondary.fringe_mesh_bod.position.x = 0.0;
  v152 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[8].primary.bod, v152);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[8].primary,
    8,
    4.0,
    20.0,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[8].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[8].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[8].primary.bod.position.x = 0.0;
  v153 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[8].secondary.bod, v153);
  mirror_path_template_pair_x(&game->subgame.path_pairs[8].secondary, &game->subgame.path_pairs[8].primary);
  game->subgame.path_pairs[8].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[8].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[8].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[8].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[8].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[8].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[8].secondary.fringe_mesh_bod.position.x = 0.0;
  v154 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[10].primary.bod, v154);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[10].primary,
    4,
    4.0,
    20.0,
    0,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[10].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[10].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[10].primary.bod.position.x = 0.0;
  v155 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[10].secondary.bod, v155);
  mirror_path_template_pair_x(&game->subgame.path_pairs[10].secondary, &game->subgame.path_pairs[10].primary);
  game->subgame.path_pairs[10].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[10].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[10].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[10].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[10].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[10].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[10].secondary.fringe_mesh_bod.position.x = 0.0;
  v156 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[9].primary.bod, v156);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[9].primary,
    4,
    4.0,
    20.0,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[9].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[9].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[9].primary.bod.position.x = 0.0;
  v157 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[9].secondary.bod, v157);
  mirror_path_template_pair_x(&game->subgame.path_pairs[9].secondary, &game->subgame.path_pairs[9].primary);
  game->subgame.path_pairs[9].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[9].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[9].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[9].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[9].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[9].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[9].secondary.fringe_mesh_bod.position.x = 0.0;
  v158 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[14].primary.bod, v158);
  initialize_sbend_path_template_pair(
    &game->subgame.path_pairs[14].primary,
    8,
    8.0,
    14.0,
    1,
    aObjectsWorld00,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[14].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[14].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[14].primary.bod.position.x = 0.0;
  v159 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[14].secondary.bod, v159);
  mirror_path_template_pair_x(&game->subgame.path_pairs[14].secondary, &game->subgame.path_pairs[14].primary);
  game->subgame.path_pairs[14].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[14].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[14].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[14].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[14].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[14].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[14].secondary.fringe_mesh_bod.position.x = 0.0;
  v160 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[11].primary.bod, v160);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[11].primary,
    8,
    -4.0,
    20.0,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[11].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[11].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[11].primary.bod.position.x = 0.0;
  v161 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[11].secondary.bod, v161);
  mirror_path_template_pair_x(&game->subgame.path_pairs[11].secondary, &game->subgame.path_pairs[11].primary);
  game->subgame.path_pairs[11].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[11].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[11].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[11].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[11].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[11].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[11].secondary.fringe_mesh_bod.position.x = 0.0;
  v162 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[13].primary.bod, v162);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[13].primary,
    4,
    -4.0,
    20.0,
    0,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[13].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[13].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[13].primary.bod.position.x = 0.0;
  v163 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[13].secondary.bod, v163);
  mirror_path_template_pair_x(&game->subgame.path_pairs[13].secondary, &game->subgame.path_pairs[13].primary);
  game->subgame.path_pairs[13].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[13].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[13].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[13].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[13].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[13].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[13].secondary.fringe_mesh_bod.position.x = 0.0;
  v164 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[12].primary.bod, v164);
  initialize_hill_valley_path_template_pair(
    &game->subgame.path_pairs[12].primary,
    4,
    -4.0,
    20.0,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[12].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[12].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[12].primary.bod.position.x = 0.0;
  v165 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[12].secondary.bod, v165);
  mirror_path_template_pair_x(&game->subgame.path_pairs[12].secondary, &game->subgame.path_pairs[12].primary);
  game->subgame.path_pairs[12].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[12].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[12].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[12].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[12].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[12].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[12].secondary.fringe_mesh_bod.position.x = 0.0;
  v166 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[20].primary.bod, v166);
  initialize_dip_path_template_pair(
    &game->subgame.path_pairs[20].primary,
    4.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[20].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[20].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[20].primary.bod.position.x = 0.0;
  v167 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[20].secondary.bod, v167);
  mirror_path_template_pair_x(&game->subgame.path_pairs[20].secondary, &game->subgame.path_pairs[20].primary);
  game->subgame.path_pairs[20].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[20].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[20].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[20].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[20].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[20].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[20].secondary.fringe_mesh_bod.position.x = 0.0;
  v168 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[21].primary.bod, v168);
  initialize_screw_path_template_pair(
    &game->subgame.path_pairs[21].primary,
    24,
    3,
    1,
    texture_a,
    texture_a,
    vertical_texture);
  game->subgame.path_pairs[21].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[21].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[21].primary.bod.position.x = 0.0;
  v169 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[21].secondary.bod, v169);
  mirror_path_template_pair_x(&game->subgame.path_pairs[21].secondary, &game->subgame.path_pairs[21].primary);
  game->subgame.path_pairs[21].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[21].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[21].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[21].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[21].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[21].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[21].secondary.fringe_mesh_bod.position.x = 0.0;
  v170 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[22].primary.bod, v170);
  initialize_slalom_path_template_pair(
    &game->subgame.path_pairs[22].primary,
    32,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[22].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[22].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[22].primary.bod.position.x = 0.0;
  v171 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[22].secondary.bod, v171);
  mirror_path_template_pair_x(&game->subgame.path_pairs[22].secondary, &game->subgame.path_pairs[22].primary);
  game->subgame.path_pairs[22].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[22].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[22].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[22].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[22].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[22].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[22].secondary.fringe_mesh_bod.position.x = 0.0;
  v172 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[23].primary.bod, v172);
  initialize_slalombig_path_template_pair(
    &game->subgame.path_pairs[23].primary,
    32,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[23].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[23].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[23].primary.bod.position.x = 0.0;
  v173 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[23].secondary.bod, v173);
  mirror_path_template_pair_x(&game->subgame.path_pairs[23].secondary, &game->subgame.path_pairs[23].primary);
  game->subgame.path_pairs[23].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[23].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[23].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[23].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[23].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[23].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[23].secondary.fringe_mesh_bod.position.x = 0.0;
  v174 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[32].primary.bod, v174);
  initialize_slalomdouble_path_template_pair(
    &game->subgame.path_pairs[32].primary,
    32,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[32].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[32].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[32].primary.bod.position.x = 0.0;
  v175 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[32].secondary.bod, v175);
  mirror_path_template_pair_x(&game->subgame.path_pairs[32].secondary, &game->subgame.path_pairs[32].primary);
  game->subgame.path_pairs[32].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[32].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[32].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[32].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[32].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[32].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[32].secondary.fringe_mesh_bod.position.x = 0.0;
  v176 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].primary.bod, v176);
  initialize_worm_path_template_pair(&game->subgame.path_pairs[24].primary, aObjectsWorld00_4);
  game->subgame.path_pairs[24].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[24].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[24].primary.bod.position.x = 0.0;
  v177 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].secondary.bod, v177);
  mirror_path_template_pair_x(&game->subgame.path_pairs[24].secondary, &game->subgame.path_pairs[24].primary);
  game->subgame.path_pairs[24].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[24].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[24].secondary.bod.position.x = 0.0;
  v178 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].primary.fringe_mesh_bod, v178);
  disable_object_rendering((int)game->subgame.path_pairs[24].primary.fringe_mesh_bod.object);
  v179 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[24].secondary.fringe_mesh_bod, v179);
  disable_object_rendering((int)game->subgame.path_pairs[24].secondary.fringe_mesh_bod.object);
  game->subgame.path_pairs[24].primary.bod.object->blend_mode = 8;
  game->subgame.path_pairs[24].secondary.bod.object->blend_mode = 8;
  v180 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[28].primary.bod, v180);
  initialize_sweep_path_template_pair(
    &game->subgame.path_pairs[28].primary,
    4.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[28].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[28].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[28].primary.bod.position.x = 0.0;
  v181 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[28].secondary.bod, v181);
  mirror_path_template_pair_x(&game->subgame.path_pairs[28].secondary, &game->subgame.path_pairs[28].primary);
  game->subgame.path_pairs[28].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[28].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[28].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[28].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[28].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[28].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[28].secondary.fringe_mesh_bod.position.x = 0.0;
  v182 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[15].primary.bod, v182);
  initialize_cage2_path_template_pair(&game->subgame.path_pairs[15].primary, 3, texture_a, texture_b, vertical_texture);
  game->subgame.path_pairs[15].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[15].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[15].primary.bod.position.x = 0.0;
  v183 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[15].secondary.bod, v183);
  mirror_path_template_pair_x(&game->subgame.path_pairs[15].secondary, &game->subgame.path_pairs[15].primary);
  game->subgame.path_pairs[15].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[15].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[15].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[15].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[15].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[15].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[15].secondary.fringe_mesh_bod.position.x = 0.0;
  v184 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[33].primary.bod, v184);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[33].primary,
    0,
    4.0,
    3,
    0.5,
    -2.5,
    14,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[33].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[33].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[33].primary.bod.position.x = 0.0;
  v185 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[33].secondary.bod, v185);
  mirror_path_template_pair_x(&game->subgame.path_pairs[33].secondary, &game->subgame.path_pairs[33].primary);
  game->subgame.path_pairs[33].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[33].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[33].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[33].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[33].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[33].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[33].secondary.fringe_mesh_bod.position.x = 0.0;
  v186 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[34].primary.bod, v186);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[34].primary,
    1,
    4.0,
    3,
    -2.5,
    2.5,
    14,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[34].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[34].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[34].primary.bod.position.x = 0.0;
  v187 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[34].secondary.bod, v187);
  mirror_path_template_pair_x(&game->subgame.path_pairs[34].secondary, &game->subgame.path_pairs[34].primary);
  game->subgame.path_pairs[34].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[34].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[34].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[34].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[34].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[34].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[34].secondary.fringe_mesh_bod.position.x = 0.0;
  v188 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[35].primary.bod, v188);
  initialize_p_path_template_pair(
    &game->subgame.path_pairs[35].primary,
    2,
    4.0,
    3,
    2.5,
    0.5,
    14,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[35].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[35].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[35].primary.bod.position.x = 0.0;
  v189 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[35].secondary.bod, v189);
  mirror_path_template_pair_x(&game->subgame.path_pairs[35].secondary, &game->subgame.path_pairs[35].primary);
  game->subgame.path_pairs[35].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[35].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[35].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[35].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[35].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[35].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[35].secondary.fringe_mesh_bod.position.x = 0.0;
  v190 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[29].primary.bod, v190);
  initialize_snake_path_template_pair(
    &game->subgame.path_pairs[29].primary,
    2.0,
    4,
    1,
    texture_a,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[29].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[29].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[29].primary.bod.position.x = 0.0;
  v191 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[29].secondary.bod, v191);
  mirror_path_template_pair_x(&game->subgame.path_pairs[29].secondary, &game->subgame.path_pairs[29].primary);
  game->subgame.path_pairs[29].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[29].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[29].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[29].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[29].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[29].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[29].secondary.fringe_mesh_bod.position.x = 0.0;
  v192 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[47].primary.bod, v192);
  initialize_toad_path_template_pair(
    &game->subgame.path_pairs[47].primary,
    1,
    texture_a,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[47].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[47].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[47].primary.bod.position.x = 0.0;
  v193 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[47].secondary.bod, v193);
  mirror_path_template_pair_x(&game->subgame.path_pairs[47].secondary, &game->subgame.path_pairs[47].primary);
  game->subgame.path_pairs[47].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[47].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[47].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[47].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[47].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[47].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[47].secondary.fringe_mesh_bod.position.x = 0.0;
  v194 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[48].primary.bod, v194);
  initialize_toad_path_template_pair(
    &game->subgame.path_pairs[48].primary,
    0,
    texture_a,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[48].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[48].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[48].primary.bod.position.x = 0.0;
  v195 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[48].secondary.bod, v195);
  mirror_path_template_pair_x(&game->subgame.path_pairs[48].secondary, &game->subgame.path_pairs[48].primary);
  game->subgame.path_pairs[48].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[48].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[48].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[48].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[48].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[48].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[48].secondary.fringe_mesh_bod.position.x = 0.0;
  v196 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[49].primary.bod, v196);
  initialize_toad_path_template_pair(
    &game->subgame.path_pairs[49].primary,
    1,
    texture_a,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[49].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[49].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[49].primary.bod.position.x = 0.0;
  v197 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[49].secondary.bod, v197);
  mirror_path_template_pair_x(&game->subgame.path_pairs[49].secondary, &game->subgame.path_pairs[49].primary);
  game->subgame.path_pairs[49].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[49].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[49].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[49].primary, aObjectsUnivers_1, -1.0);
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[49].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[49].secondary, aObjectsUnivers_1, 1.0);
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[49].secondary.fringe_mesh_bod.position.x = 0.0;
  v198 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[50].primary.bod, v198);
  initialize_toad_path_template_pair(
    &game->subgame.path_pairs[50].primary,
    0,
    texture_a,
    aObjectsWorld00,
    vertical_texture);
  game->subgame.path_pairs[50].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[50].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[50].primary.bod.position.x = 0.0;
  v199 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[50].secondary.bod, v199);
  mirror_path_template_pair_x(&game->subgame.path_pairs[50].secondary, &game->subgame.path_pairs[50].primary);
  game->subgame.path_pairs[50].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[50].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[50].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[50].primary, aObjectsUnivers_1, 1.0);
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[50].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[50].secondary, aObjectsUnivers_1, -1.0);
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[50].secondary.fringe_mesh_bod.position.x = 0.0;
  noop_this_constructor(&color);
  store_color4f((tColour *)&color, 1.0, 1.0, 1.0, 0.60000002);
  v200 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[51].primary.bod, v200);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[51].primary,
    6.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[51].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[51].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[51].primary.bod.position.x = 0.0;
  v201 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[51].secondary.bod, v201);
  mirror_path_template_pair_x(&game->subgame.path_pairs[51].secondary, &game->subgame.path_pairs[51].primary);
  game->subgame.path_pairs[51].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[51].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[51].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[51].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[51].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[51].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[51].secondary.fringe_mesh_bod.position.x = 0.0;
  object = game->subgame.path_pairs[0].primary.bod.object;
  v203 = game->subgame.path_pairs[51].secondary.bod.object;
  game->subgame.path_pairs[0].primary.entry_transition_strip_mesh = game->subgame.path_pairs[51].primary.bod.object;
  v204 = game->subgame.path_pairs[0].secondary.bod.object;
  game->subgame.path_pairs[0].primary.entry_base_strip_mesh = object;
  game->subgame.path_pairs[0].secondary.entry_transition_strip_mesh = v203;
  game->subgame.path_pairs[0].secondary.entry_base_strip_mesh = v204;
  v205 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[52].primary.bod, v205);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[52].primary,
    6.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[52].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[52].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[52].primary.bod.position.x = 0.0;
  v206 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[52].secondary.bod, v206);
  mirror_path_template_pair_x(&game->subgame.path_pairs[52].secondary, &game->subgame.path_pairs[52].primary);
  game->subgame.path_pairs[52].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[52].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[52].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[52].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[52].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[52].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[52].secondary.fringe_mesh_bod.position.x = 0.0;
  v207 = game->subgame.path_pairs[1].primary.bod.object;
  v208 = game->subgame.path_pairs[52].secondary.bod.object;
  game->subgame.path_pairs[1].primary.entry_transition_strip_mesh = game->subgame.path_pairs[52].primary.bod.object;
  game->subgame.path_pairs[1].secondary.entry_base_strip_mesh = game->subgame.path_pairs[1].secondary.bod.object;
  game->subgame.path_pairs[1].primary.entry_base_strip_mesh = v207;
  game->subgame.path_pairs[1].secondary.entry_transition_strip_mesh = v208;
  v209 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[53].primary.bod, v209);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[53].primary,
    8.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[53].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[53].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[53].primary.bod.position.x = 0.0;
  v210 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[53].secondary.bod, v210);
  mirror_path_template_pair_x(&game->subgame.path_pairs[53].secondary, &game->subgame.path_pairs[53].primary);
  game->subgame.path_pairs[53].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[53].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[53].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[53].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[53].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[53].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[53].secondary.fringe_mesh_bod.position.x = 0.0;
  v211 = game->subgame.path_pairs[2].primary.bod.object;
  v212 = game->subgame.path_pairs[53].secondary.bod.object;
  game->subgame.path_pairs[2].primary.entry_transition_strip_mesh = game->subgame.path_pairs[53].primary.bod.object;
  game->subgame.path_pairs[2].primary.entry_base_strip_mesh = v211;
  game->subgame.path_pairs[2].secondary.entry_transition_strip_mesh = v212;
  game->subgame.path_pairs[2].secondary.entry_base_strip_mesh = game->subgame.path_pairs[2].secondary.bod.object;
  v213 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[57].primary.bod, v213);
  initialize_looptheloopw_path_template_pair(
    &game->subgame.path_pairs[57].primary,
    8.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[57].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[57].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[57].primary.bod.position.x = 0.0;
  v214 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[57].secondary.bod, v214);
  mirror_path_template_pair_x(&game->subgame.path_pairs[57].secondary, &game->subgame.path_pairs[57].primary);
  game->subgame.path_pairs[57].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[57].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[57].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[57].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[57].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[57].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[57].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[6].primary.entry_transition_strip_mesh = game->subgame.path_pairs[57].primary.bod.object;
  game->subgame.path_pairs[6].primary.entry_base_strip_mesh = game->subgame.path_pairs[6].primary.bod.object;
  game->subgame.path_pairs[6].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[57].secondary.bod.object;
  game->subgame.path_pairs[6].secondary.entry_base_strip_mesh = game->subgame.path_pairs[6].secondary.bod.object;
  v215 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[54].primary.bod, v215);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[54].primary,
    3.0,
    2,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[54].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[54].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[54].primary.bod.position.x = 0.0;
  v216 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[54].secondary.bod, v216);
  mirror_path_template_pair_x(&game->subgame.path_pairs[54].secondary, &game->subgame.path_pairs[54].primary);
  game->subgame.path_pairs[54].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[54].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[54].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[54].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[54].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[54].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[54].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[3].primary.entry_transition_strip_mesh = game->subgame.path_pairs[54].primary.bod.object;
  game->subgame.path_pairs[3].primary.entry_base_strip_mesh = game->subgame.path_pairs[3].primary.bod.object;
  game->subgame.path_pairs[3].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[54].secondary.bod.object;
  game->subgame.path_pairs[3].secondary.entry_base_strip_mesh = game->subgame.path_pairs[3].secondary.bod.object;
  v217 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[55].primary.bod, v217);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[55].primary,
    3.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[55].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[55].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[55].primary.bod.position.x = 0.0;
  v218 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[55].secondary.bod, v218);
  mirror_path_template_pair_x(&game->subgame.path_pairs[55].secondary, &game->subgame.path_pairs[55].primary);
  game->subgame.path_pairs[55].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[55].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[55].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[55].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[55].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[55].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[55].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[4].primary.entry_transition_strip_mesh = game->subgame.path_pairs[55].primary.bod.object;
  game->subgame.path_pairs[4].primary.entry_base_strip_mesh = game->subgame.path_pairs[4].primary.bod.object;
  game->subgame.path_pairs[4].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[55].secondary.bod.object;
  game->subgame.path_pairs[4].secondary.entry_base_strip_mesh = game->subgame.path_pairs[4].secondary.bod.object;
  v219 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[56].primary.bod, v219);
  initialize_looptheloop_path_template_pair(
    &game->subgame.path_pairs[56].primary,
    3.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[56].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[56].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[56].primary.bod.position.x = 0.0;
  v220 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[56].secondary.bod, v220);
  mirror_path_template_pair_x(&game->subgame.path_pairs[56].secondary, &game->subgame.path_pairs[56].primary);
  game->subgame.path_pairs[56].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[56].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[56].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[56].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[56].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[56].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[56].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[5].primary.entry_transition_strip_mesh = game->subgame.path_pairs[56].primary.bod.object;
  game->subgame.path_pairs[5].primary.entry_base_strip_mesh = game->subgame.path_pairs[5].primary.bod.object;
  game->subgame.path_pairs[5].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[56].secondary.bod.object;
  game->subgame.path_pairs[5].secondary.entry_base_strip_mesh = game->subgame.path_pairs[5].secondary.bod.object;
  v221 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[58].primary.bod, v221);
  initialize_loopbow_path_template_pair(
    &game->subgame.path_pairs[58].primary,
    6.0,
    4u,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[58].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[58].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[58].primary.bod.position.x = 0.0;
  v222 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[58].secondary.bod, v222);
  mirror_path_template_pair_x(&game->subgame.path_pairs[58].secondary, &game->subgame.path_pairs[58].primary);
  game->subgame.path_pairs[58].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[58].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[58].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[58].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[58].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[58].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[58].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[7].primary.entry_transition_strip_mesh = game->subgame.path_pairs[58].primary.bod.object;
  game->subgame.path_pairs[7].primary.entry_base_strip_mesh = game->subgame.path_pairs[7].primary.bod.object;
  game->subgame.path_pairs[7].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[58].secondary.bod.object;
  game->subgame.path_pairs[7].secondary.entry_base_strip_mesh = game->subgame.path_pairs[7].secondary.bod.object;
  v223 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[62].primary.bod, v223);
  initialize_invert_path_template_pair(
    &game->subgame.path_pairs[62].primary,
    6.0,
    8,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[62].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[62].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[62].primary.bod.position.x = 0.0;
  v224 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[62].secondary.bod, v224);
  mirror_path_template_pair_x(&game->subgame.path_pairs[62].secondary, &game->subgame.path_pairs[62].primary);
  game->subgame.path_pairs[62].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[62].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[62].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[62].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[62].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[62].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[62].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[41].primary.entry_transition_strip_mesh = game->subgame.path_pairs[62].primary.bod.object;
  game->subgame.path_pairs[41].primary.entry_base_strip_mesh = game->subgame.path_pairs[41].primary.bod.object;
  game->subgame.path_pairs[41].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[62].secondary.bod.object;
  game->subgame.path_pairs[41].secondary.entry_base_strip_mesh = game->subgame.path_pairs[41].secondary.bod.object;
  v225 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[59].primary.bod, v225);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[59].primary,
    3.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[59].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[59].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[59].primary.bod.position.x = 0.0;
  v226 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[59].secondary.bod, v226);
  mirror_path_template_pair_x(&game->subgame.path_pairs[59].secondary, &game->subgame.path_pairs[59].primary);
  game->subgame.path_pairs[59].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[59].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[59].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[59].primary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[59].primary.fringe_mesh_bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[59].secondary, aObjectsUnivers_1, 0.0);
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.z = 0.0;
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.y = 0.0;
  game->subgame.path_pairs[59].secondary.fringe_mesh_bod.position.x = 0.0;
  game->subgame.path_pairs[25].primary.entry_transition_strip_mesh = game->subgame.path_pairs[59].primary.bod.object;
  game->subgame.path_pairs[25].primary.entry_base_strip_mesh = game->subgame.path_pairs[25].primary.bod.object;
  game->subgame.path_pairs[25].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[59].secondary.bod.object;
  game->subgame.path_pairs[25].secondary.entry_base_strip_mesh = game->subgame.path_pairs[25].secondary.bod.object;
  v227 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[61].primary.bod, v227);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[61].primary,
    5.0,
    4,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  game->subgame.path_pairs[61].primary.bod.position.z = 0.0;
  game->subgame.path_pairs[61].primary.bod.position.y = 0.0;
  game->subgame.path_pairs[61].primary.bod.position.x = 0.0;
  v228 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[61].secondary.bod, v228);
  mirror_path_template_pair_x(&game->subgame.path_pairs[61].secondary, &game->subgame.path_pairs[61].primary);
  game->subgame.path_pairs[61].secondary.bod.position.z = 0.0;
  game->subgame.path_pairs[61].secondary.bod.position.y = 0.0;
  game->subgame.path_pairs[61].secondary.bod.position.x = 0.0;
  build_track_fringe_mesh(&game->subgame.path_pairs[61].primary, aObjectsUnivers_1, 0.0);
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
  v229 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[60].primary.bod, v229);
  initialize_loopout_path_template_pair(
    &game->subgame.path_pairs[60].primary,
    3.0,
    3,
    1,
    texture_a,
    texture_b,
    vertical_texture);
  zero_vector3(&game->subgame.path_pairs[60].primary.bod.position.x);
  v230 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.path_pairs[60].secondary.bod, v230);
  mirror_path_template_pair_x(&game->subgame.path_pairs[60].secondary, &game->subgame.path_pairs[60].primary);
  zero_vector3(&game->subgame.path_pairs[60].secondary.bod.position.x);
  build_track_fringe_mesh(&game->subgame.path_pairs[60].primary, aObjectsUnivers_1, 0.0);
  zero_vector3(&game->subgame.path_pairs[60].primary.fringe_mesh_bod.position.x);
  build_track_fringe_mesh(&game->subgame.path_pairs[60].secondary, aObjectsUnivers_1, 0.0);
  zero_vector3(&game->subgame.path_pairs[60].secondary.fringe_mesh_bod.position.x);
  game->subgame.path_pairs[26].primary.entry_transition_strip_mesh = game->subgame.path_pairs[60].primary.bod.object;
  game->subgame.path_pairs[26].primary.entry_base_strip_mesh = game->subgame.path_pairs[26].primary.bod.object;
  game->subgame.path_pairs[26].secondary.entry_transition_strip_mesh = game->subgame.path_pairs[60].secondary.bod.object;
  game->subgame.path_pairs[26].secondary.entry_base_strip_mesh = game->subgame.path_pairs[26].secondary.bod.object;
  debug_report_stub();
  v231 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_43284A + 2), v231);
  case_insensitive_substring = find_case_insensitive_substring(aTest, game->directx_loader.animation_bytes);
  if ( case_insensitive_substring )
  {
    v233 = find_case_insensitive_substring(asc_4A1644, case_insensitive_substring);
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
  load_x_animation_clip(&game->directx_loader, ArgList, *(Object **)((char *)&loc_432870 + (_DWORD)game));
  v239 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4326FF + 1), v239);
  load_x_animation_clip(&game->directx_loader, ArgList, *(Object **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4));
  v240 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4328C8 + 4), v240);
  load_x_animation_clip(&game->directx_loader, mesh_name, *(Object **)((char *)&loc_4328F0 + (_DWORD)game));
  v241 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43294C + (_DWORD)game), v241);
  load_x_animation_clip(&game->directx_loader, aTurboBobalong0, *(Object **)((char *)&loc_432970 + (_DWORD)game));
  v242 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4329CC + (_DWORD)game), v242);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboLookbackl,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_4329EE + 2));
  v243 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432A4A + 2), v243);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboLookbackr,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432A6D + 3));
  v244 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432ACB + 1), v244);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboFall000X,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432AEF + 1));
  v245 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432B49 + 3), v245);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboDamaged00,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432B6E + 2));
  v246 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432BCA + 2), v246);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboIntoshell,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432BEF + 1));
  v247 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432C48 + 4), v247);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboSkidstop0,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432C6D + 3));
  v248 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432CCA + 2), v248);
  load_x_animation_clip(
    &game->directx_loader,
    aTurboTalk000X,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432CE9 + 7));
  v249 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433D46 + 6), v249);
  load_x_mesh(&game->directx_loader, aTurbohotspotsX, *(Object **)((char *)&game->vtable + (_DWORD)&loc_433D6F + 1), 2);
  build_snail_hotspots((Snail *)((char *)game + (_DWORD)&loc_4326FF + 1));
  edge_selectore = 10;
  x_offseta = (Object **)((char *)&loc_432870 + (_DWORD)game);
  do
  {
    (*x_offseta)->flags |= 4u;
    apply_object_toon(*x_offseta, 0);
    v250 = *x_offseta;
    x_offseta += 32;
    v250->distort.z_wave = 0.0;
    (*(x_offseta - 32))->distort.y_squash = 0.0;
    v56 = edge_selectore == 1;
    (*(x_offseta - 32))->distort.xyz_scale = 0.0;
    --edge_selectore;
  }
  while ( !v56 );
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4))[4] |= 4u;
  apply_object_toon(*(Object **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4), 0);
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4))[32] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4))[33] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432720 + 4))[34] = 0;
  v251 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4338DE + 2), v251);
  load_x_animation_clip(
    &game->directx_loader,
    aJetpackBase000,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2));
  v252 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433A2C + 4), v252);
  load_x_animation_clip(&game->directx_loader, aJetpackBase000, *(Object **)((char *)&loc_433A54 + (_DWORD)game));
  v253 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433AB0 + (_DWORD)game), v253);
  load_x_animation_clip(&game->directx_loader, aJetpackDraw000, *(Object **)((char *)&loc_433AD4 + (_DWORD)game));
  edge_selectorf = 2;
  x_offsetb = (Object **)((char *)&loc_433A54 + (_DWORD)game);
  do
  {
    (*x_offsetb)->flags |= 4u;
    apply_object_toon(*x_offsetb, 0);
    v254 = *x_offsetb;
    x_offsetb += 32;
    v254->distort.z_wave = 0.0;
    (*(x_offsetb - 32))->distort.y_squash = 0.0;
    v56 = edge_selectorf == 1;
    (*(x_offsetb - 32))->distort.xyz_scale = 0.0;
    --edge_selectorf;
  }
  while ( !v56 );
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2))[4] |= 4u;
  apply_object_toon(*(Object **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2), 0);
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2))[32] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2))[33] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433902 + 2))[34] = 0;
  v255 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)&byte_432D4C[(_DWORD)game], v255);
  load_x_animation_clip(
    &game->directx_loader,
    aBlasterleftBas,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3));
  v256 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432E9A + 2), v256);
  load_x_animation_clip(
    &game->directx_loader,
    aBlasterleftBas,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_432EBF + 1));
  v257 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432F1A + 2), v257);
  load_x_animation_clip(&game->directx_loader, aBlasterleftDra, *(Object **)((char *)&loc_432F40 + (_DWORD)game));
  v258 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_432F9B + 1), v258);
  load_x_animation_clip(
    &game->directx_loader,
    aBlasterleftFir,
    *(Object **)((char *)find_registered_sound_sample_id_by_name + (_DWORD)game));
  v259 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43301C + (_DWORD)game), v259);
  load_x_animation_clip(
    &game->directx_loader,
    aLaserleftBase0,
    *(Object **)((char *)get_authored_view_height + (_DWORD)game));
  v260 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_43309C + (_DWORD)game), v260);
  load_x_animation_clip(
    &game->directx_loader,
    aLaserleftDraw0,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_4330BF + 1));
  edge_selectorg = 5;
  x_offsetc = (Object **)((char *)game + (_DWORD)&loc_432EBF + 1);
  do
  {
    (*x_offsetc)->flags |= 4u;
    apply_object_toon(*x_offsetc, 0);
    v261 = *x_offsetc;
    x_offsetc += 32;
    v261->distort.z_wave = 0.0;
    (*(x_offsetc - 32))->distort.y_squash = 0.0;
    v56 = edge_selectorg == 1;
    (*(x_offsetc - 32))->distort.xyz_scale = 0.0;
    --edge_selectorg;
  }
  while ( !v56 );
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3))[4] |= 4u;
  apply_object_toon(*(Object **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3), 0);
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3))[32] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3))[33] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_432D6D + 3))[34] = 0;
  v262 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433127 + 1), v262);
  load_x_animation_clip(&game->directx_loader, aBlasterrightBa, *(Object **)((char *)&loc_43314C + (_DWORD)game));
  v263 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433275 + 3), v263);
  load_x_animation_clip(
    &game->directx_loader,
    aBlasterrightBa,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_43329B + 1));
  v264 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4332F7 + 1), v264);
  load_x_animation_clip(&game->directx_loader, aBlasterrightDr, *(Object **)((char *)&loc_43331C + (_DWORD)game));
  v265 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433378 + (_DWORD)game), v265);
  load_x_animation_clip(
    &game->directx_loader,
    aBlasterrightFi,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_43339A + 2));
  v266 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_4333F8 + (_DWORD)game), v266);
  load_x_animation_clip(
    &game->directx_loader,
    aLaserrightBase,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433417 + 5));
  v267 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433475 + 3), v267);
  load_x_animation_clip(
    &game->directx_loader,
    aLaserrightDraw,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433499 + 3));
  edge_selectorh = 5;
  x_offsetd = (Object **)((char *)game + (_DWORD)&loc_43329B + 1);
  do
  {
    (*x_offsetd)->flags |= 4u;
    apply_object_toon(*x_offsetd, 0);
    v268 = *x_offsetd;
    x_offsetd += 32;
    v268->distort.z_wave = 0.0;
    (*(x_offsetd - 32))->distort.y_squash = 0.0;
    v56 = edge_selectorh == 1;
    (*(x_offsetd - 32))->distort.xyz_scale = 0.0;
    --edge_selectorh;
  }
  while ( !v56 );
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 16) |= 4u;
  apply_object_toon(*(Object **)((char *)&loc_43314C + (_DWORD)game), 0);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 128) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 132) = 0;
  *(_DWORD *)(*(_DWORD *)((char *)&loc_43314C + (_DWORD)game) + 136) = 0;
  v269 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433504 + (_DWORD)game), v269);
  load_x_animation_clip(
    &game->directx_loader,
    aBlastertopBase,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5));
  v270 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433654 + (_DWORD)game), v270);
  load_x_animation_clip(
    &game->directx_loader,
    aBlastertopBase,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433677 + 1));
  v271 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4336D0 + 4), v271);
  load_x_animation_clip(
    &game->directx_loader,
    aBlastertopDraw,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_4336F6 + 2));
  v272 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433751 + 3), v272);
  load_x_animation_clip(
    &game->directx_loader,
    aBlastertopFire,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433777 + 1));
  v273 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4337D3 + 1), v273);
  load_x_animation_clip(
    &game->directx_loader,
    aRocketlauncher,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_4337F6 + 2));
  v274 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_433853 + 1), v274);
  load_x_animation_clip(
    &game->directx_loader,
    aRocketlauncher_0,
    *(Object **)((char *)&game->vtable + (_DWORD)&loc_433877 + 1));
  edge_selectori = 5;
  x_offsete = (Object **)((char *)game + (_DWORD)&loc_433677 + 1);
  do
  {
    (*x_offsete)->flags |= 4u;
    apply_object_toon(*x_offsete, 0);
    v275 = *x_offsete;
    x_offsete += 32;
    v275->distort.z_wave = 0.0;
    (*(x_offsete - 32))->distort.y_squash = 0.0;
    v56 = edge_selectori == 1;
    (*(x_offsete - 32))->distort.xyz_scale = 0.0;
    --edge_selectori;
  }
  while ( !v56 );
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5))[4] |= 4u;
  apply_object_toon(*(Object **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5), 0);
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5))[32] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5))[33] = 0;
  (*(_DWORD **)((char *)&game->vtable + (_DWORD)&loc_433523 + 5))[34] = 0;
  *(void **)((char *)&game->vtable + (_DWORD)&loc_434037 + 5) = get_or_create_texture_ref(
                                                                  &g_texture_refs,
                                                                  aXSnailTurboTga_0,
                                                                  nullptr,
                                                                  0);
  *(void **)((char *)&game->vtable + (_DWORD)&loc_43403D + 3) = get_or_create_texture_ref(
                                                                  &g_texture_refs,
                                                                  aXSnailTurboDam,
                                                                  nullptr,
                                                                  0);
  *(void **)((char *)&game->vtable + (_DWORD)&loc_434042 + 2) = get_or_create_texture_ref(
                                                                  &g_texture_refs,
                                                                  aXSnailTurboInv,
                                                                  nullptr,
                                                                  0);
  v276 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)&loc_433F94 + (_DWORD)game), v276);
  load_x_mesh(&game->directx_loader, aInvincibleBase, *(Object **)((char *)&loc_433FB8 + (_DWORD)game), 1);
  *(_DWORD *)(*(_DWORD *)((char *)&loc_433FB8 + (_DWORD)game) + 16) &= ~0x100000u;
  v277 = add_object_to_list(&g_object_list);
  set_bod_object((BodBase *)((char *)game + (_DWORD)&loc_4302E3 + 1), v277);
  load_x_mesh(&game->directx_loader, aRocketBase000X, *(Object **)((char *)&game->vtable + (_DWORD)&loc_430306 + 2), 1);
  v278 = (char *)game + (_DWORD)&loc_43026E + 2;
  edge_selectorj = 12;
  do
  {
    v279 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(v278 - 36), v279);
    *(_DWORD *)(*(_DWORD *)v278 + 16) |= 0x100004u;
    *(_DWORD *)(*(_DWORD *)v278 + 20) = 9;
    load_object_definition(aObjectsVapourl, *(Object **)v278);
    initialize_vapour((Vapour *)(v278 - 36), *(Object **)v278, 0.16);
    set_bod_object((BodBase *)(v278 + 116), *(Object **)((char *)&game->vtable + (_DWORD)&loc_430306 + 2));
    v278 += 744;
    --edge_selectorj;
  }
  while ( edge_selectorj );
  v280 = get_or_create_texture_ref(&g_texture_refs, aObjectsVapourl_0, nullptr, 0);
  v281 = v280->flags;
  BYTE1(v281) = ((unsigned __int16)v280->flags >> 8) | 4;
  v280->flags = v281;
  v282 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_4, nullptr, 0);
  v282->flags |= 0x1403u;
  v283 = get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0);
  v283->flags |= 0x1402u;
  get_or_create_texture_ref(&g_texture_refs, cap_texture, nullptr, 0)->flags = TEXTURE_REF_WRAP_ADDRESSING;
  v284 = get_or_create_texture_ref(&g_texture_refs, aObjectsUnivers, nullptr, 0);
  v285 = v284->flags;
  BYTE1(v285) = ((unsigned __int16)v284->flags >> 8) | 0x10;
  v284->flags = v285;
  v286 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00, nullptr, 0);
  v286->flags |= 0x1002u;
  v287 = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
  v287->flags |= 0x1002u;
  v288 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_5, nullptr, 0);
  v288->flags |= 0x1002u;
  v289 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_6, nullptr, 0);
  v289->flags |= 0x1002u;
  v290 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_7, nullptr, 0);
  v290->flags |= 0x1002u;
  v291 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_8, nullptr, 0);
  v291->flags |= 0x1002u;
  v292 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_9, nullptr, 0);
  v292->flags |= 0x1002u;
  v293 = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_10, nullptr, 0);
  v293->flags |= 0x1002u;
  game->track.track_textures[0] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00, nullptr, 0);
  game->track.slide_textures[0] = get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0);
  game->track.track_textures[1] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_5, nullptr, 0);
  game->track.slide_textures[1] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_6, nullptr, 0);
  game->track.track_textures[2] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_7, nullptr, 0);
  game->track.slide_textures[2] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_8, nullptr, 0);
  game->track.track_textures[3] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_9, nullptr, 0);
  game->track.slide_textures[3] = get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_10, nullptr, 0);
  game->track.current_texture_set = 0;
  get_or_create_texture_ref(&g_texture_refs, texture_b, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, cap_texture, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsUnivers, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, texture_a, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_5, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_6, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_7, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_8, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_9, nullptr, 0)->mip_levels = 2;
  get_or_create_texture_ref(&g_texture_refs, aObjectsWorld00_10, nullptr, 0)->mip_levels = 2;
  v294 = add_object_to_list(&g_object_list);
  set_bod_object(&game->subgame.barrier.bod, v294);
  load_object_definition(aObjectsBarrier, game->subgame.barrier.bod.object);
  zero_vector3(&game->subgame.barrier.bod.position.x);
  store_color4f(&game->subgame.barrier.bod.color, 1.0, 1.0, 1.0, 0.80000001);
  game->subgame.barrier.bod.object->blend_mode = 7;
  initialize_track_render_cache_manager(&game->subgame.segment_cache);
  edge_selectork = 0;
  v295 = &game->root_bod_catalog.fringe_catalog.entries[0][0][0][0].object;
  do
  {
    for ( orientation = 0; orientation < 4; ++orientation )
    {
      x_offsetf = 0;
      v296 = v295;
      do
      {
        for ( j = 0; j < 3; ++j )
        {
          v298 = add_object_to_list(&g_object_list);
          set_bod_object((BodBase *)(v296 - 9), v298);
          initialize_backdrop_tile_quad(*v296, edge_selectork, orientation, x_offsetf - 1, j - 1, aObjectsUnivers_1);
          v299 = *v296;
          v296 += 14;
          v299->blend_mode = 5;
        }
        ++x_offsetf;
      }
      while ( x_offsetf < 3 );
      v295 = v296;
    }
    ++edge_selectork;
  }
  while ( edge_selectork < 8 );
  v300 = get_or_create_texture_ref(&g_texture_refs, aObjectsUnivers_1, nullptr, 0);
  v301 = v300->flags;
  p_input = &game->game_inputs[0].input;
  BYTE1(v301) = ((unsigned __int16)v300->flags >> 8) | 4;
  v303 = 0;
  v300->flags = v301;
  do
  {
    add_bod_to_front(&game->active_bod_list.unknown_00, (int)&p_input[-1]);
    p_input->controller_slot = v303;
    initialize_input(p_input);
    ++v303;
    p_input += 2;
  }
  while ( v303 < 2 );
  for ( x_offsetg = 0; x_offsetg < game->player_count; ++x_offsetg )
  {
    edge_selectorl = (char *)game + 504 * x_offsetg;
    set_matrix_identity((TransformMatrix *)(edge_selectorl + 348));
    set_matrix_identity((TransformMatrix *)(edge_selectorl + 508));
    *((_DWORD *)edge_selectorl + 161) = 1121714176;
    *((_DWORD *)edge_selectorl + 163) = &game->game_inputs[x_offsetg];
    qmemcpy(
      edge_selectorl + 348,
      initialize_matrix_from_values(
        &v333,
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
        -8.626667,
        3.113528,
        4.477407,
        1.0),
      0x40u);
    initialize_frontend_overlay_color_lerp((_DWORD *)edge_selectorl + 170, 0x1000000);
    release_mouse_cursor((MouseCursorState *)(edge_selectorl + 656));
    edge_selectorl[676] = 0;
    if ( !x_offsetg )
      game->players[0].frontend_state = 12;
    edge_selectorl[781] = 0;
    *((_DWORD *)edge_selectorl + 196) = 0;
    rstrcpy_checked_ascii(edge_selectorl + 420, g_runtime_config.last_entered_player_name);
  }
  initialize_high_score_tables((SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position
                                              + (_DWORD)game));
  load_high_scores_from_file(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)game),
    file_name);
  load_high_scores_from_file(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)game),
    aScorebDat);
  load_high_scores_from_file(
    (SubHighScore *)((char *)&g_parcel_set_buckets[1431].candidates[30].position + (_DWORD)game),
    aScorecDat);
  game->subgame.selected_level_record_persistent = 0;
  game->subgame.selected_level_record_active = 0;
  initialize_tip_manager(&game->tip_manager);
  add_bod_to_front(&game->active_bod_list.unknown_00, (int)&game->tip_manager);
  add_bod_to_front(&g_game_base->active_bod_list.unknown_00, (int)&game->star_manager);
  open_star_field(&game->star_manager, 36);
  game->subgame.bottom_score_widget = nullptr;
  game->subgame.top_score_widget = nullptr;
  add_bod_to_front(&game->active_bod_list.unknown_00, (int)&game->backdrop);
  game->backdrop.backdrop_render_enabled = 0;
  append_bod_to_end(&game->active_bod_list.unknown_00, &game->border_manager.vtable);
  initialize_border_stack(&game->border_manager.border_stack.generation);
  game->border_manager.border_stack.owner = &game->border_manager;
  game->border_manager.delayed_widget_active = 0;
  set_border_justify_centre(&game->border_manager, 25.0);
  p_flags = &game->border_manager.borders[0].flags;
  v305 = 150;
  do
  {
    *p_flags = 0;
    p_flags += 457;
    --v305;
  }
  while ( v305 );
  build_all_objects(&g_object_list);
  set_object_color(game->subgame.path_pairs[51].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[51].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[52].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[52].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[53].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[53].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[57].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[57].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[54].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[54].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[55].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[55].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[56].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[56].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[58].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[58].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[62].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[62].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[59].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[59].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[61].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[61].secondary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[60].primary.bod.object, (tColour)color);
  set_object_color(game->subgame.path_pairs[60].secondary.bod.object, (tColour)color);
  set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
  set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
  game->subgame.subgame_rebuild_selector = 2;
  return 1;
}
