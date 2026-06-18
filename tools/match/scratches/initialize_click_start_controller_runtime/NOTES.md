# Exact match

`initialize_click_start_controller_runtime` @ 0x408670 constructs the
renderable click-start controller and installs callback table `data_497348`.
Reading that table in Binary Ninja shows its first entry is
`update_click_start`, so this is the runtime constructor for the controller,
not the later gameplay setup helper `initialize_click_start` @ 0x442170.
