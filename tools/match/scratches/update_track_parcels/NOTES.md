# Exact match

`update_track_parcels` walks the 50 fixed `TrackParcelRuntime` slots and makes
the native vtable call for every nonzero state. The pool owns slot storage;
individual slots only borrow the subgame, Player, and sprite handles. The
shared typed version remains 100% (16/16) with a narrow dispatch overlay used
only to express the native virtual call without adding a second C++ vptr to
the explicit `BodNode` layout.
