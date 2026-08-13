# Authored owner — `cRWarning::StopSample`

Android and iOS retain `cRWarning::StopSample()`. The Windows method does not
read its receiver but routes the warning sample through the shared sound
manager; Android keeps the owner and call edge from `cRDamageGuage::AI()` but
ships a no-op body. Treat that as a port behavior difference, not a free
Windows helper.

2026-07-11 focused Wibo verifies the member-shaped source as an exact 100.00%
match, 7/7 instructions, with four clean masked operands.

The exact Windows sequence also proves both nested audio helpers are
`SoundEffectManager` methods: it loads `g_sound_effect_manager @ 0x78ff88`
before the play call, passes the returned handle, reloads the same receiver,
and calls the stop helper. Both callee bodies remain exact after promotion.

2026-07-17 paired replay: IDA now retains the authored
`void __thiscall(Warning*)` ABI even though the Windows body does not read its
receiver, matching the mobile `cRWarning::StopSample` ownership edge. Both
tracked decompilers also preserve the nested `g_sound_effect_manager` receiver.
Focused matching remains exact at 7/7 instructions with four clean masked
operands.

## 2026-08-09 primary cRWarning ownership

The matcher now emits this sample edge as `cRWarning::StopSample()` and binds
the owner-qualified VC6 symbol `?StopSample@cRWarning@@QAEXXZ`; `Warning`
remains a compatibility typedef. The live Windows view confirms the member ABI
and sole direct call at `0x441105`, while the seven-instruction body never
reads the incoming ECX receiver: it binds `g_sound_effect_manager`, plays
sample `0x32`, then stops the returned handle. Android and iOS independently
retain the authored method even though Android's body is a port-specific no-op.
Keeping the receiver-free Windows body source-honest remains exact at 7/7
instructions with all four masked operands clean.

## 2026-08-13 canonical analysis-owner replay

The live receiver remains unused by Windows code, but both databases now retain
its canonical `cRWarning*` ABI rather than the generic analysis spelling. The
guarded replay verifies the complete owner and Player embed before applying the
method type, preserving the mobile-owned member edge without inventing a
receiver read. Focused matching remains exact at 7/7 instructions with all four
operands clean.
