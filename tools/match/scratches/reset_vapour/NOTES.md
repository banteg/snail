# reset_vapour

Exact 100.00% Windows match: 7/7 instructions. Android and iOS preserve this
member as the void `cRVapour::ReSet(float*)`.

The method clears `point_count`, retains the optional borrowed z-floor pointer,
and clears visibility bit `0x20`. Android returns with the receiver still in its
result register after the same stores, proving that the final flags value left
in Windows EAX is incidental rather than an integer return contract.

## 2026-08-09 authored ReSet promotion

The matcher now defines `cRVapour::ReSet(float*)` with the mobile-preserved
capitalization and exports `?ReSet@cRVapour@@QAEXPAM@Z`. The borrowed z-floor
pointer, point-count clear, and visibility-bit update remain byte-identical at
7/7 instructions and full prefix.
