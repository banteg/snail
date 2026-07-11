# Authored owner — `cRWarning::StopSample`

Android and iOS retain `cRWarning::StopSample()`. The Windows method does not
read its receiver but routes the warning sample through the shared sound
manager; Android keeps the owner and call edge from `cRDamageGuage::AI()` but
ships a no-op body. Treat that as a port behavior difference, not a free
Windows helper.

2026-07-11 focused Wibo verifies the member-shaped source as an exact 100.00%
match, 7/7 instructions, with four clean masked operands.
