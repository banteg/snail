# initialize_subgoldy_resurrect

Exact match: 100.00%, 6/6 instructions.

The helper seeds the `Player`-owned resurrection state with an explicit
final-loss selector. `initialize_subgoldy_death` tail-forwards into it, but the
two external death callers consume no result. Removing the synthetic
`return final_loss` preserves all six instructions: EAX still carries the
argument used by the real store. BN, IDA, and the matching header now retain
the authored void `cRSubGoldy::RessurectInit(int)` contract.
