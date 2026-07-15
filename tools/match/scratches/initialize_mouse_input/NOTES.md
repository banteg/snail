# initialize_mouse_input

- Seeds the live mouse position to the center of the authored viewport.
- Creates the DirectInput mouse device, installs the mouse data format, sets
  exclusive foreground cooperative level flags (`4`), acquires the device, and
  returns zero on successful setup.
- Native does not test the `SetCooperativeLevel` result after `SetDataFormat`
  succeeds; it calls `Acquire` and returns zero.
- The interface identifier and system-mouse identifier are complete 0x10-byte
  DirectInput GUIDs, and the installed mouse format is the SDK 0x18-byte
  `DIDATAFORMAT`; all three are borrowed static SDK records rather than byte
  anchors.
- Current focused match: 100.00%, 46/46 instructions, with 18 clean masked
  operands. The source-shape key is naming the X/Y half-viewport products as
  locals before storing them; this lets VC6 keep the native schedule where the
  X store precedes the nested `GetModuleHandleA(0)` argument push and the hide
  flag store.
