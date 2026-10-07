# Original replay fixtures

Score bank files written by the original Windows game (`ScoreA.dat` =
postal, `ScoreB.dat` = challenge, `ScoreC.dat` = completion records with
the Time Trial ghost lane). Each high-score record embeds its run as
per-tick samples (`ReplayRunRecord`: lateral x, z delta, flags) in the
compact format of `cRSubSolution::Save` / its loader, xor-masked with
`xor_decode_buffer_with_index` (`byte ^= i & 0xff`).

`uv run snail port oracle` copies these into a game directory under their
game names and replays every postal and challenge record in the headless
port, comparing the simulated z per tick with the recording (see
docs/port/README.md, "Oracles").

## Score?.windows-2026-04-17.dat

Banks from banteg's Windows host (original game, saves dated 2026-04-17).
25 records, all checksum-valid, every record with a replay, 71,535 samples:

- ScoreA (postal): 10 rows, top run score 141030 on level 12; levels 5-26
- ScoreB (challenge): 10 rows, top 69190; the longest run 7196 ticks
- ScoreC (completion/time-trial ghosts): 3 records, routes 1, 6, 13

Name new fixtures by provenance, e.g. `ScoreA.tutorial-run-2026-06-12.dat`,
and note what was played and on which level.
