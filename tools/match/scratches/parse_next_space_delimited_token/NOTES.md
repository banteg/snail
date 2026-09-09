# RTextExtractString

Exact at 27/27 instructions with no masked operands. It skips leading spaces,
copies through the next space or CR, terminates the output, and advances the
caller-owned cursor.

Android and iOS preserve the authored void
`RTextExtractString(char**, char*)` contract in `RShell.o`; the sole Windows
caller also discards EAX.

## 2026-09-09 authored void contract recovered

The previous `char**` result workaround is removed. Simply deleting the result
from the old decompiler-shaped source recolors registers and gives 22.22%, but
directly expressing the leading-space and token-copy loops through `*cursor`
recovers all 27 instructions and the identical 60-byte body. The retained source
includes `rtext.h` and emits `?RTextExtractString@@YAXPAPADPAD@Z`, matching the
existing caller in `load_object_definition`. Its conservative function code
identity remains `55140009270e84007b3ce5e36e3db4d02e0af505001da48fbd645d9cf7f7c059`.

The recorded accepted probe binds both source versions. It temporarily selected
the unique authored function name to permit the before/after ABI comparison;
the canonical configuration now selects the authentic decorated void symbol,
which is independently checked by linkage.
The older claim that natural void transcriptions could not retain the body is
superseded by this complete-function result.

The new `rtext` linked group exercises all seven shared RShell text declarations
with 22 assertions, plus a deliberate token corruption that fails exactly one
assertion. Cases preserve shipped delimiter/cursor quirks: tabs are content,
CR is not consumed by token extraction, and float extraction leaves a leading
plus unconsumed. Fixtures provide required delimiters; they do not establish
bounded-input safety. See [the source and runtime receipt](../../rtext-void-and-runtime-20260909.md).
