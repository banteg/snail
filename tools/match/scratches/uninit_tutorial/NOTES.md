# Exact cRTutorial::UnInit

`0x448dd0` is the authored `cRTutorial::UnInit()` method. Android and iOS
`Tutorial.o` preserve the same owner and method with one body each. VC6 emits
`?UnInit@cRTutorial@@QAEXXZ`; the three-instruction Windows thunk and both
relocated operands match exactly.

The method delegates tutorial UI teardown to the root-owned cRTipManager; the
embedded tutorial object owns no tip allocation. Windows retains the authored
receiver even though this tiny thunk does not read its fields.
