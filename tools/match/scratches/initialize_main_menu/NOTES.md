# initialize_main_menu @ 0x419b50

Main-menu initializer, spelling the `MainMenu` slots as the six observed widget
fields at `+0x00..+0x14`.

- Hides the shared `StarManager` immediately after `MainMenu` (`+0x4f33c`), proving
  the `MainMenu` size as `0x18` in the front-end root.
- Loads `music/mainmenu.ogg`, activates `Menubg.txt`, and sets the backdrop
  center-justify runtime to `25.0f` through the raw-bit `BorderRuntime` view.
- Seeds the render-skip countdown at game `+0x56c` to `2`.
- Native allocates the Options widget twice into the same slot and stacks the
  second one under High Scores; preserve that source shape because it is real
  binary behavior, not a decompiler duplication.
