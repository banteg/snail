"""Run via bn py before applying attribution; export graph and demangled names."""
import json
from pathlib import Path

view = globals()["bv"]
binaryninja = globals()["bn"]
root = Path(view.file.filename).resolve().parents[2]
if Path(view.file.filename).name != "SnailMail_unwrapped.exe.bndb":
    raise ValueError("select the Snail Mail database explicitly")
output = root / "artifacts/ownership"
output.mkdir(parents=True, exist_ok=True)
functions = [{"address": f.start, "name": f.name, "size": sum(b.end-b.start for b in f.basic_blocks),
              "callees": sorted({c.start for c in f.callees}), "callers": sorted({c.start for c in f.callers})}
             for f in view.functions]
strings = []
for entry in view.strings:
    if entry.length < 5:
        continue
    refs = sorted({r.function.start for r in view.get_code_refs(entry.start) if r.function})
    if refs:
        strings.append({"address": entry.start, "text": str(entry.value), "refs": refs})
(output / "snail-ownership-live.json").write_text(json.dumps({"functions": functions, "strings": strings}, indent=2) + "\n")
rows = json.loads((output / "resolved.json").read_text())["accepted"]
names = {}
for row in rows:
    symbol = row["symbol"]
    if symbol.startswith("?"):
        function_type, name = binaryninja.demangle_ms(view.arch, symbol)
        names[symbol] = {"name": str(name), "type": str(function_type)}
    else:
        names[symbol] = {"name": symbol, "type": None}
(output / "demangled.json").write_text(json.dumps(names, indent=2) + "\n")
result = {"functions": len(functions), "strings": len(strings), "names": len(names)}
