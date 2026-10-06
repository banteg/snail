"""Resolve the port's link names between recovered sources.

Matching compares call targets by address, so recovered sources may call a
function under a stand-in owner (`RuntimeSlot::initialize_garbage_hazard`) while
its own file defines it under the real one (`cRSubGarbage::cRSubGarbage`), or call
one of several identical-code-folded owners of one body. A linker needs one name.
This module finds every function the port's objects call but do not define,
resolves it through the function manifest to the recovered function at that
address, and emits a wasm forwarder from the called name to the defined one:

- equal signatures forward every argument and the result;
- a target that takes a prefix of the arguments (a folded empty body called as a
  member) drops the rest;
- a caller expecting `this` back from a target that returns nothing gets `this`.

Anything else is reported for a hand-written shim. Calls that resolve to no
compiled function remain for the shell, and the report lists them: it is the
port's link-progress measure.
"""

import json
import re
import subprocess
from dataclasses import dataclass
from pathlib import Path

from . import port
from .wasm_object import SYMBOL_FUNCTION, Signature, read_symbols

FUNCTIONS = Path("analysis/symbols/gameplay-functions.json")
OUTPUT = Path("port/generated/link_aliases.s")
REPORT = Path("port/generated/link_report.json")


@dataclass(frozen=True)
class Reference:
    name: str
    demangled: str
    signature: Signature


def demangle(names: list[str]) -> list[str]:
    completed = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True, check=True)
    return completed.stdout.split("\n")[: len(names)]


def object_symbols(root: Path, sources: list[str]):
    defined: dict[str, Signature] = {}
    referenced: dict[str, set[Signature]] = {}
    by_source: dict[str, list[str]] = {}
    for source in sources:
        for symbol in read_symbols(port.object_path(root, source)):
            if symbol.kind != SYMBOL_FUNCTION:
                continue
            if symbol.strong_global:
                defined[symbol.name] = symbol.signature
                by_source.setdefault(source, []).append(symbol.name)
            elif not symbol.defined:
                referenced.setdefault(symbol.name, set()).add(symbol.signature)
    return defined, referenced, by_source


def manifest_index(root: Path) -> dict[str, str]:
    """Function name or alias (also `Owner::name` spellings) -> manifest name."""
    index = {}
    for function in json.loads((root / FUNCTIONS).read_text())["functions"]:
        for name in (function["name"], *function.get("aliases", ())):
            index.setdefault(name, function["name"])
            index.setdefault(name.replace("_", "::", 1), function["name"])
    return index


def resolve(demangled: str, index: dict[str, str]) -> str | None:
    base = re.sub(r"\(.*", "", demangled)
    leaf = base.rsplit("::", 1)[-1]
    owner = base.rsplit("::", 1)[0] if "::" in base else ""
    for candidate in (base, f"{owner}_{leaf}" if owner else None, leaf):
        if candidate and candidate in index:
            return index[candidate]
    return None


def forwarder(name: str, call: Signature, target: str, defined: Signature) -> list[str] | None:
    """wasm assembly forwarding `name` to `target`, or None if unsafe."""
    taken = len(defined.params)
    if call.params[:taken] != defined.params:
        return None
    body = [f"\tlocal.get\t{i}" for i in range(taken)] + [f"\tcall\t{target}"]
    if call.results == defined.results:
        pass
    elif not call.results:
        body += ["\tdrop"] * len(defined.results)
    elif call.results == ("i32",) and not defined.results and call.params[:1] == ("i32",):
        body.append("\tlocal.get\t0")
    else:
        return None
    return [
        f"\t.section\t.text.{name},\"\",@",
        f"\t.globl\t{name}",
        f"\t.type\t{name},@function",
        f"{name}:",
        f"\t.functype\t{name} {call.functype()}",
        *body,
        "\tend_function",
    ]


def generate(root: Path) -> dict:
    sources = port.source_list(root)
    if errors := port.compile_objects(root, sources):
        raise ValueError("port sources do not compile:\n" + "\n".join(errors))
    defined, referenced, by_source = object_symbols(root, sources)
    function_source = {
        function: f"../{source['path']}"
        for unit in json.loads((root / port.LAYOUT).read_text())["units"]
        for source in unit["sources"]
        for function in (source["function"],)
    }
    index = manifest_index(root)
    missing = sorted(name for name in referenced if name not in defined)
    names = demangle(missing)
    aliases, manual, shell = [], [], []
    declared: set[str] = set()
    for name, readable in zip(missing, names):
        signatures = referenced[name]
        function = resolve(readable, index)
        source = function_source.get(function)
        targets = [t for t in by_source.get(source, ()) if "C2E" not in t] if source else []
        if not targets:
            shell.append({"symbol": name, "demangled": readable, "function": function})
            continue
        if len(signatures) != 1 or len(targets) != 1:
            manual.append({"symbol": name, "demangled": readable, "targets": targets, "why": "ambiguous"})
            continue
        (call,), (target,) = signatures, targets
        lines = forwarder(name, call, target, defined[target])
        if lines is None:
            manual.append(
                {"symbol": name, "demangled": readable, "targets": targets,
                 "why": f"{call.functype()} cannot forward to {defined[target].functype()}"}
            )
            continue
        if target not in declared:
            lines.insert(0, f"\t.functype\t{target} {defined[target].functype()}")
            declared.add(target)
        aliases.append({"symbol": name, "demangled": readable, "target": target, "lines": lines})
    text = ["# Generated by `snail port link`. Do not edit."]
    for alias in aliases:
        text += alias.pop("lines")
    (root / OUTPUT).parent.mkdir(parents=True, exist_ok=True)
    (root / OUTPUT).write_text("\n".join(text) + "\n")
    report = {"aliases": aliases, "manual": manual, "shell": shell}
    (root / REPORT).write_text(json.dumps(report, indent=1) + "\n")
    return report
