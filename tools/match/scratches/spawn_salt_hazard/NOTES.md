# Pinned — 74.07%, 67/68 insns, layout-only residual

The free-scan loop is the only divergence: the original lays it out as a
single top test with the bound compare as conditional back-edge; every
source shape tried (for-with-increment, while, for(;;)+break,
do-while+goto) rotates and duplicates the state test under our compiler
pass ordering. All semantics verified in the diff body:

- free scan over `slots[i].state` (+0x80, stride 0x98), bails with
  `return index` at 40
- seeding order: state=1, velocity.x +0x8c=0.0f, velocity.y +0x90 =
  `game[+0x74650] * (1/30)`, position triple into the live-matrix
  position row (+0x68), `set_matrix_rotation_identity` on +0x38,
  random world-y rotation `(rand() - 16384) * 0.0001917476` (±π),
  then a one-byte write to velocity.z +0x94
- **+0x94 is velocity.z, not an armed flag** — spawn only pokes its low
  byte to `1`, leaving the float as a tiny denormal; update_salt_hazard
  confirms position integration reads +0x8c/+0x90/+0x94 as a float triple.
- live-list add-after onto the node-shaped anchor at game+0x3ca224,
  flag 0x200, prev/next at +0x08/+0x0c, returns `list_flags |= 0x200`
- spawn's true extent ends at 0x44164c; an uncurated 20-slot pool
  initializer sits between it and deactivate (worth curating)

2026-06-13 pin audit: focused matcher still verifies 74.07%, 68/67 insns.
Keep pinned; the remaining diff is free-scan loop rotation plus scheduling,
while the velocity.z low-byte poke and list-link semantics are recovered.
