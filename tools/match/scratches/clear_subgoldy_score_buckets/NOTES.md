# clear_subgoldy_score_buckets

Exact match: 100.00%, 7/7 instructions.

The helper clears the six `Player::score_buckets` shared by score production
and display. Both callers discard EAX; the zero register left by the final
store is not a result. The natural void method emits the same seven native
instructions, so the matching header and durable BN/IDA declarations now keep
the real `Player` receiver without a synthetic fastcall integer contract.
