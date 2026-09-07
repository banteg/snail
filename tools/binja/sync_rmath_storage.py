"""Run through bn py; APPLY=True saves verified math-array storage types."""

from pathlib import Path

bv = globals()["bv"]
bn = globals()["bn"]

if "SnailMail_unwrapped" not in Path(bv.file.filename).name:
    raise ValueError("select the Snail Mail database explicitly")
if bv.read(0x44C955, 7) != bytes.fromhex("d9 1c 85 38 7f 77 00"):
    raise ValueError("native cosine initializer store changed")
if bv.read(0x44C95E, 7) != bytes.fromhex("d9 1c 85 88 ff 77 00"):
    raise ValueError("native sine initializer store changed")

specs = [
    (0x777F3C, "g_cosine_table", bn.Type.array(bn.Type.float(4), 8192)),
    (0x77FF8C, "g_sine_table", bn.Type.array(bn.Type.float(4), 8192)),
    (0x77FF3C, "g_math_random_index", bn.Type.int(4, True)),
    (0x787F8C, "g_math_random_table", bn.Type.array(bn.Type.int(4, True), 8191)),
]
apply = globals().get("APPLY", False)
changes = []
undo = bv.begin_undo_actions()
try:
    for address, name, kind in specs:
        symbol = bv.get_symbol_at(address)
        if symbol and symbol.name not in (name, f"data_{address:x}"):
            raise ValueError(f"preserve existing meaningful name: {symbol.name}")
        variable = bv.get_data_var_at(address)
        changed = (
            not variable or variable.type != kind or not symbol or symbol.name != name
        )
        if changed:
            bv.define_user_data_var(address, kind)
            bv.define_user_symbol(bn.Symbol(bn.SymbolType.DataSymbol, address, name))
        actual = bv.get_data_var_at(address)
        if not actual or actual.type != kind or bv.get_symbol_at(address).name != name:
            raise ValueError(f"storage readback failed at {address:#x}")
        changes.append(
            {
                "address": hex(address),
                "name": name,
                "type": str(kind),
                "bytes": kind.width,
                "changed": changed,
            }
        )
except Exception:
    bv.revert_undo_actions(undo)
    raise
else:
    if apply:
        bv.commit_undo_actions(undo)
    else:
        bv.revert_undo_actions(undo)

if apply:
    bv.update_analysis_and_wait()
    if not bv.file.save_auto_snapshot():
        raise ValueError("snapshot not saved")
result = {"apply": apply, "storage": changes, "snapshot_saved": bool(apply)}
