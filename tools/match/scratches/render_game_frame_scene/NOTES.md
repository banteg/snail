# render_game_frame_scene

Frame scene wrapper at `0x4134c0`. It clears the backbuffer, begins a Direct3D
scene, resets the per-frame successful primitive counter, updates display-mode
view state, calls `render_game_frame`, and ends the Direct3D scene. The
separate `present_backbuffer` helper at `0x413520` presents the backbuffer.
