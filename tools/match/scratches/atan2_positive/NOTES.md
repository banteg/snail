# atan2_positive @ 0x44ca10

Exact match: 100.00%, 48/48 instructions.

This helper computes a quadrant-aware positive-range arctangent for kind-42
attachment transforms and sprite-facing angle updates. The native source shape
normalizes signs into a quadrant id, handles the vertical case with `pi/2`, and
uses `atan(y / x)` rather than a two-argument CRT call; the result is a float
even though it is returned through x87.
