# store_color4f @ 0x44dbb0

Exact Windows four-float `tColour` write at `+0/+4/+8/+12`, retained at 9/9
instructions as a void member. Android and iOS preserve a semantically
equivalent four-float constructor, but VC6 source trials reject that spelling
for Windows: a real constructor inserts an extra `mov eax, ecx`, shifts the
stores to an `eax` receiver, and falls to a 0/9 prefix. The value left in `edx`
by the native body is incidental, and the descriptive member remains honest
until an authored non-constructor name is recovered.
