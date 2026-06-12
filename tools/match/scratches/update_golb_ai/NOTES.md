# Dossier — scratch not yet written (700 insns, 2656 bytes)

update_golb_ai @ 0x414820. target.asm committed. Focus: the path-follow
lane the Zig port lacks (checklist Phase 4 item).

## Path-follow entry (IDA export lines ~180-198)

When the shot's local y (+504) is in (0,1) and it advances past its
stored z: grid-cell lookup at the shot position (+684 vec); if the
cell tile == 30 (0x1e), stash position.z into the anchor slot (+740)
and call the matched initialize_path_follow_golb(state at +700, cell,
position vec at +500, this). A second entry lane checks +596 > 1.0 with
the adjacent row's cell (cell - 612 bytes) and seeds anchor z+1 via
cell - 672. **Naming correction for the matched init scratch: the third
int arg is the owner golb pointer (returned through eax), not a search
slot id.**

## Trail dispatch by state (+448)

- 0: trail sprites at position, position - 0.3*velocity, - 0.6*velocity
- 1: add_vapour_point from the live matrix
- 2 (rocket?): live-matrix copy, spin accumulate +0x1b4 with the 2pi
  wrap, golb smoke at position and position - 0.5*velocity

Velocity triple at +600/604/608, position at +684/688/692, live matrix
at +636 (0x40 copy), path-follow state at +700 (the matched
GolbPathFollowState layout), owner game ptr at +624.

## Zig gap

The port has the level band + gravity + despawn (checklist) but not the
tile-30 path-follow entry, the per-state trail dispatch offsets, or the
adjacent-row second entry. The matched search_path_for_golb (100%) and
initialize_path_follow_golb (100%) make the mirror transcription of the
entry lane mechanical once the in-follow stepping region of this
function is read (next session).
