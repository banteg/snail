# cRBorderManager::Kill candidate @ 0x403360

The native Windows body is exact at 30/30 instructions. It marks one border for
teardown and recursively visits its three owned children. Live analysis types
the entry as `void __thiscall(BorderManager*, FrontendWidget*)`; 55 external
callsites discard `eax`, and the three recursive calls end with a plain
fall-through epilogue. Android and iOS name the member
`cRBorderManager::Kill(cRBorder*)`.

One source-shape issue remains deliberately visible: a natural VC6 `void`
transcription tail-recurses the third child and falls to 73.33%. The exact
scratch uses an `int` result-shaped harness plus disabled missing-return warning
to prevent that transformation, while emitting no source return. Because that
return type is compiler-harness debt rather than recovered Windows authorship,
the matcher has not promoted the method to `Kill` or claimed its decorated
symbol. This exception should be removed only when an equally exact natural
void source shape is found.
