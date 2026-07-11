# Authored owner — `cRWarning::Stop`

Android and iOS retain `cRWarning::Stop()`. Android
`cRDamageGuage::AI()` calls it through the embedded warning owner, matching
Windows; both clear the state and hide the owned border.

2026-07-11 focused Wibo verifies an exact 100.00% match, 3/3 instructions,
with one clean masked operand.
