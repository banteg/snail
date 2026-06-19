# initialize_game_assets_and_world @ 0x40acf0

Starter scratch for the large root-world bootstrap.

This is intentionally a semantic partial, not a line-for-line transcription. It
captures the recovered early root defaults, texture/object-list startup, overlay
registration, landscape/menu/audio/font/sprite setup, the first backdrop/pillar
world-object islands, and a small track-template setup island. The body remains
raw-offset based because the cRGame/cRSubGame root layout is far larger than the
currently shared headers expose.

Expected residuals:
- most later path-template, pickup, replay, score, and frontend pools are not
  modeled yet;
- several list-link operations are expressed through a local helper, while the
  target has the inline intrusive-list sequence;
- string literals are used for concrete asset paths recovered from the binary,
  so masked-operand audit may still need reference-manifest promotion later.
