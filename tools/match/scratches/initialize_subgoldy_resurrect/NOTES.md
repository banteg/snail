# initialize_subgoldy_resurrect

Exact match: 100.00%, 6/6 instructions.

The helper seeds the `Player`-owned resurrection state with an explicit
final-loss selector. `initialize_subgoldy_death` tail-forwards into it, but the
two external death callers consume no result. Removing the synthetic
`return final_loss` preserves all six instructions: EAX still carries the
argument used by the real store. BN, IDA, and the matching header now retain
the authored void `cRSubGoldy::RessurectInit(int)` contract.

The selector handoff is runtime-closed. The March 15 CDB session stopped at
both `initialize_subgoldy_death` callsites and then observed this helper with
`final_loss = 0` for Postal spare-life respawn and `final_loss = 1` for Postal
zero-life final loss. Android `cRSubGoldy::RessurectInit(int)` independently
stores the same selector, arms the resurrect controller, clears its progress,
and seeds the `1/120` progress step. The current focused Windows scratch remains
exact at `100.00%`, `6/6` instructions.
