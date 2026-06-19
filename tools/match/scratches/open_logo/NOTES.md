# open_logo @ 0x419110

Initializes the 32 intro logo renderable slots and preloads every texture
matching `Intro/*.tga`.

Recovered layout:

- `this + 0x24018`: first `IntroLogoRenderable`;
- logo renderable stride: `0x90`;
- each slot is a `RenderableBod` followed by 0x18 bytes of intro-logo runtime
  state, matching the existing intro logo update scratch;
- the local archive enumeration buffer stores names in 0x80-byte entries.

The function uses the shared object and texture lists: each renderable receives
an object from `g_object_list`, loads `Objects/Font3D`, marks object flag `0x4`,
then sets texture flag `0x400` on every loaded `Intro/%s` texture.

The retained source uses the native object-field cursor at `this + 0x2403c`.
VC6 still strength-reduces the first loop into separate object-field and slot
pointers, which adds an `ebx` save and shifts the local stack offsets. Typed
renderable-array and raw byte-cursor variants compiled to the same residual.
