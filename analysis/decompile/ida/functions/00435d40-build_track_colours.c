/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_track_colours @ 0x435d40 */
/* selector: build_track_colours */

// Exact Windows `cRSubGame::BuildColours()`: seeds the CheckBlack, Floor, two physical Slide, Wall, Trampoline, Ramp, Empty, Path, PathWorm, and PathWarp banks. Android and iOS preserve the ten original gLocColourLookup* symbols and the same 13-call order; their two Slide calls alias one owner while Windows keeps separate storage.
void __thiscall build_track_colours(SubgameRuntime *game)
{
  int i; // esi

  for ( i = 0; i < 816; i += 16 )
  {
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_check_black + i));
    set_color_white(&g_loc_colour_lookup_floor_slide_0.floor[i / 0x10u]);
    set_color_white(&g_loc_colour_lookup_floor_slide_0.slide_0[i / 0x10u]);
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_slide_1 + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_wall + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_trampoline + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_ramp + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_empty + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_path + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_path_worm + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_path_worm + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_path_warp + i));
    set_color_white((tColour *)((char *)&g_loc_colour_lookup_path_warp + i));
  }
}
