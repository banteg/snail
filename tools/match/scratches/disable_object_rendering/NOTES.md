# disable_object_rendering @ 0x41a0a0

Marks one `Object` with the `0x40000` flag that makes exact `render_object`
reject the object before drawing. Both recovered callsites pass the `Object*`
borrowed by a `BodBase::object` lane immediately after startup binds the object
to that BOD, proving the argument owner and render-suppression meaning.
