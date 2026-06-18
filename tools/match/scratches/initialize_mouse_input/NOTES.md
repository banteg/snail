# initialize_mouse_input

- Seeds the live mouse position to the center of the authored viewport.
- Creates the DirectInput mouse device, installs the mouse data format, sets
  exclusive foreground cooperative level flags (`4`), acquires the device, and
  returns zero on successful setup.
- Native does not test the `SetCooperativeLevel` result after `SetDataFormat`
  succeeds; it calls `Acquire` and returns zero.
- Current focused match: 95.65%, 46/46 instructions, with 17 clean masked
  operands. The only residual is startup scheduling: native stores
  `g_mouse_live_x` before the `GetModuleHandleA(0)` argument push and cursor
  hide flag store, while VC6 keeps those two setup instructions before the X
  store for this source spelling.
