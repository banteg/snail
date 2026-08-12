# Exact cRBorderManager::DelayClick

`0x403f60` is the authored
`cRBorderManager::DelayClick(cRBorder*, int)` method.

Evidence:

- Windows uses a void `__thiscall` on the complete manager; all three callers
  discard EAX and pass the same manager-owned cRBorder view.
- Android `Border.o` preserves the standalone owner, name, parameter list, and
  one body. Its cRBorder::AI calls the method in the same three interaction
  branches as Windows.
- iOS inlines the lane three times in cRBorder::AI, corroborating the fade gate
  and fixed `1/12` step but not a standalone iOS function.
- VC6 emits `?DelayClick@cRBorderManager@@QAEXPAVcRBorder@@H@Z`; the method
  matches all 22 instructions with two clean operands. The 647-instruction
  Windows caller retains its 95.83% baseline and all three call relocations are
  now audited.

If no delayed action is active, the method optionally starts the root-owned
cRFade for borders carrying `FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION`, then
stores the borrowed border, active byte, zero progress, fixed `1/12` progress
step, and queued flag mask. The fields follow the manager's 150-record border
pool at `+0x4359c..+0x435ac`; mobile offsets are not transferred.
