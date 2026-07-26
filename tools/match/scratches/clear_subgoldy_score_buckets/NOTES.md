# clear_subgoldy_score_buckets

## 2026-07-26 ScoreStatsInit ownership

Android and iOS preserve this owner method as
`cRSubGoldy::ScoreStatsInit()`. Their port layout clears seven adjacent score
buckets while Windows clears six at `Player + 0x310`; `ScoreAdd` and
`ScoreStatsDisplay` consume the corresponding block on every port. The
historical `initialize_score_stats` compatibility name has therefore moved
here from unrelated `cRSquidge::Init`.

Exact match: 100.00%, 7/7 instructions.

The helper clears the six `Player::score_buckets` shared by score production
and display. Both callers discard EAX; the zero register left by the final
store is not a result. The natural void method emits the same seven native
instructions, so the matching header and durable BN/IDA declarations now keep
the real `Player` receiver without a synthetic fastcall integer contract.
