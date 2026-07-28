# hide_gameplay_scores @ 0x445f10

Exact `cRSubGame::HideScores()` helper over the active `cRSubGame`.
Windows, Android, and iOS all null-check and hide the same two owned gameplay
score widgets in the same order. The port-specific widget offsets differ, but
the receiver, two-borrow ownership, guard shape, and void contract agree.
