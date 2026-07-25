# resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20

Exact 11/11 helper returning `1.0f` while player zero's cursor is captured and
otherwise applying the native `scale * 1.79999995f + 0.699999988f` transform.

## 2026-07-25 cursor-owner replay

The root-owned player layout places `MouseCursorState` at
`GameRoot::players[0].mouse_cursor`, not an independent `GameRoot + 0x290`
allocation. Binary Ninja and IDA now retain that inline borrow directly, with
health checks rejecting raw byte-offset renderings. No source or codegen
change was needed.
