# commit_high_score_entry_into_top_ten

Commits the edited high-score display rows into the active persistent top-ten
bank after name entry.

This helper is a member of the front-end record view at `game+0x6ffae0`, not a
free function taking a raw `HighScoreRecord*`. The first two fields are the
active persistent bank pointer and row count; the native copy source begins at
view offset `+0x17c108`.
