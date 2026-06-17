# Exact match

`get_track_skirt_color` @ 0x442120 fills an output `Color4f` with the current
track skirt RGB and alpha `0.400000006f`, then returns the same output pointer.

The exact source shape is the direct aggregate expression:

```cpp
*out = *color.set_color_rgba(
    track_skirt_r,
    track_skirt_g,
    track_skirt_b,
    0.400000006f);
return out;
```

Naming the returned color pointer or a destination pointer was semantically
equivalent, but it left a 68.00% scheduler residual around the 16-byte copy:
VC6 loaded `out` into `ecx` first and returned it with a final `mov eax, ecx`.
The direct expression reproduces native's `mov ecx, eax; mov eax, [esp+...]`
copy order without register forcing.

The shared sparse `SubgameRuntime` root now carries the track skirt RGB fields
at +0x1b0140..+0x1b0148. This helper remains exact after moving those fields to
the header, so the larger track-runtime scratches can reference the same root
view without duplicating a local class.
