# disable_object_rendering @ 0x41a0a0

Marks one `Object` with `OBJECT_FLAG_RENDER_DISABLED`, which makes exact
`render_object` reject the object before drawing. Both recovered callsites pass the `Object*`
borrowed by a `BodBase::object` lane immediately after startup binds the object
to that BOD, proving the argument owner and render-suppression meaning.

Android and iOS retain the authored free-function name
`ObjectProcNull(cRObject*)` in `ObjectProc.o`. This is an exact cross-port
identity rather than a name-only candidate: both mobile `cRGame::LoadPaths`
bodies call it on the same pair of newly bound path objects, in the same order
as Windows, and all three implementations OR the `0x40000` flag. The mobile
`cRObject` layouts keep flags at `+0x00` while Windows keeps them at `+0x10`,
so the ownership and contract transfer without importing a false field
offset.
