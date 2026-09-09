"""Verify linked source objects using PE COFF symbols, including static data.

This establishes source-object preservation and storage ownership in an
integration image. It does not assign original translation units or grant
native code/data matching credit.
"""

import hashlib
import re
import struct
from pathlib import Path

import pefile

from .match import CoffObject, CoffRelocation, CoffSymbol


def verify_runtime_control(
    group: str,
    stdout: str,
    returncode: int,
    *,
    expected_checks: int,
    expected_failures: int,
) -> dict[str, int]:
    """Require one complete summary and exactly the intended failing checks."""
    pattern = re.compile(rf"{re.escape(group)} checks=(\d+) failures=(\d+)")
    summaries = [
        match
        for line in stdout.splitlines()
        if (match := pattern.fullmatch(line)) is not None
    ]
    if len(summaries) != 1:
        raise ValueError("runtime control requires exactly one complete summary")
    checks, failures = map(int, summaries[0].groups())
    reported_failures = sum(line.startswith("FAIL: ") for line in stdout.splitlines())
    if (
        checks != expected_checks
        or failures != expected_failures
        or reported_failures != failures
        or returncode != int(expected_failures != 0)
    ):
        raise ValueError(
            "runtime control outcome differs from the expected checks/failures/exit: "
            f"{checks}/{failures}/{returncode}, failure lines={reported_failures}"
        )
    return {"checks": checks, "failures": failures}


class LinkSymbols:
    def __init__(self, image: bytes, pe: pefile.PE, map_text: str):
        self.addresses: dict[str, set[int]] = {}
        self.owners: dict[tuple[str, str], set[int]] = {}
        self.storage_addresses: dict[tuple[str, int], set[int]] = {}
        self.static_definitions: dict[str, set[str]] = {}
        base = pe.OPTIONAL_HEADER.ImageBase
        self.sections = tuple(
            (
                base + section.VirtualAddress,
                section.Misc_VirtualSize or section.SizeOfRawData,
                section.Characteristics,
                section.Name.rstrip(b"\0").decode("latin1"),
            )
            for section in pe.sections
        )
        table = pe.FILE_HEADER.PointerToSymbolTable
        count = pe.FILE_HEADER.NumberOfSymbols
        strings = table + count * 18
        if not table or not count or strings + 4 > len(image):
            raise ValueError("linked image requires COFF debug symbols")
        string_size = struct.unpack_from("<I", image, strings)[0]
        if string_size < 4 or strings + string_size > len(image):
            raise ValueError("invalid linked COFF string table")
        index = 0
        while index < count:
            record = image[table + index * 18 : table + (index + 1) * 18]
            value, section, _, storage, aux = struct.unpack_from("<IhHBB", record, 8)
            if index + aux >= count:
                raise ValueError("invalid linked COFF auxiliary count")
            if record[:4] == bytes(4):
                offset = struct.unpack_from("<I", record, 4)[0]
                if not 4 <= offset < string_size:
                    raise ValueError("invalid linked COFF symbol name")
                start = strings + offset
                end = image.index(0, start, strings + string_size)
                name = image[start:end].decode("latin1")
            else:
                name = record[:8].rstrip(b"\0").decode("latin1")
            if 0 < section <= len(pe.sections) and storage in (2, 3):
                # LINK's PE COFF symbol values are RVAs, unlike object offsets.
                part = pe.sections[section - 1]
                if not part.VirtualAddress <= value < (
                    part.VirtualAddress + part.Misc_VirtualSize
                ):
                    raise ValueError(f"linked symbol outside its section: {name}")
                self.addresses.setdefault(name, set()).add(base + value)
                self.storage_addresses.setdefault((name, storage), set()).add(base + value)
            index += 1 + aux
        for row in re.finditer(
            r"^\s+[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+(\S+)\s+"
            r"([0-9A-Fa-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$",
            map_text,
            re.MULTILINE,
        ):
            # LINK writes non-printable symbol bytes as octal escapes in maps.
            name = re.sub(r"\\([0-7]{3})", lambda match: chr(int(match[1], 8)), row[1])
            address, owner = int(row[2], 16), row[3]
            if address not in self.addresses.get(name, set()):
                raise ValueError(f"map/COFF symbol disagreement: {name}")
            self.owners.setdefault((owner, name), set()).add(address)

    def bind_objects(self, objects: dict[str, CoffObject]) -> None:
        """Bind static identities against every source object in this link.

        VC6's linked COFF table has static data names but no source-file records.
        The map supplies owners for static functions, but omits some static data.
        A map-less static name is usable only if one input object defines it.
        """
        definitions: dict[str, set[str]] = {}
        for owner, obj in objects.items():
            for symbol in obj.symbols:
                if symbol.storage_class == 3 and symbol.section_number > 0:
                    definitions.setdefault(symbol.name, set()).add(owner)
        # A later verification of a subset must not erase another input's
        # same-named definition and turn an ambiguity into a false proof.
        for name, owners in definitions.items():
            self.static_definitions.setdefault(name, set()).update(owners)

    def section_for_span(
        self, address: int, size: int, *, data: bool = False, code: bool = False,
    ) -> str:
        """Require the entire span to belong to one real linked PE section."""
        matches = [
            name for start, extent, characteristics, name in self.sections
            if size > 0 and start <= address and address + size <= start + extent
            and (not data or characteristics & 0xC0)
            and (not code or characteristics & 0x20)
        ]
        if len(matches) != 1:
            raise ValueError(f"span outside a single linked section: {address:#x}+{size:#x}")
        return matches[0]

    def resolve(self, name: str, owner: str) -> int:
        candidates = self.owners.get((owner, name)) or self.addresses.get(name, set())
        if len(candidates) != 1:
            raise ValueError(f"missing or ambiguous linked symbol: {owner}: {name}")
        return next(iter(candidates))

    def resolve_symbol(self, symbol: CoffSymbol, owner: str) -> int:
        if symbol.storage_class != 3:
            return self.resolve(symbol.name, owner)
        candidates = self.owners.get((owner, symbol.name))
        if candidates is None:
            # Never borrow another object's same-named static merely because
            # it is the only surviving name in the linked symbol table.
            if self.static_definitions.get(symbol.name) != {owner} or any(
                name == symbol.name for _, name in self.owners
            ):
                raise ValueError(f"missing or ambiguous static owner: {owner}: {symbol.name}")
            candidates = self.storage_addresses.get((symbol.name, 3), set())
        if len(candidates) != 1 or not candidates <= self.storage_addresses.get(
            (symbol.name, 3), set()
        ):
            raise ValueError(f"missing or ambiguous linked static: {owner}: {symbol.name}")
        return next(iter(candidates))


def verify_relocated_bytes(
    original: bytes,
    actual: bytes,
    address: int,
    relocations: tuple[CoffRelocation, ...],
    obj: CoffObject,
    symbols: LinkSymbols,
    owner: str,
) -> list[dict]:
    """Reconstruct expected linked bytes from independently resolved symbols."""
    expected = bytearray(original)
    by_index = {symbol.raw_index: symbol for symbol in obj.symbols}
    occupied: set[int] = set()
    evidence = []
    for relocation in relocations:
        offset = relocation.virtual_address
        if not 0 <= offset <= len(original) - 4:
            raise ValueError(f"out-of-bounds relocation in {owner}")
        slots = set(range(offset, offset + 4))
        if occupied & slots:
            raise ValueError(f"overlapping relocations in {owner}")
        occupied |= slots
        target = by_index.get(relocation.symbol_index)
        if target is None:
            raise ValueError(f"missing relocation symbol in {owner}: {relocation.symbol_index}")
        destination = symbols.resolve_symbol(target, owner)
        addend = struct.unpack_from("<i", original, offset)[0]
        value = destination + addend
        if relocation.relocation_type == 0x14:
            value -= address + offset + 4
        elif relocation.relocation_type != 0x06:
            raise ValueError(f"unsupported relocation in {owner}: {relocation.relocation_type:#x}")
        struct.pack_into("<I", expected, offset, value & 0xFFFFFFFF)
        evidence.append({
            "offset": offset,
            "symbol": target.name,
            "addend": addend,
            "address": (destination + addend) & 0xFFFFFFFF,
            "type": "REL32" if relocation.relocation_type == 0x14 else "DIR32",
            "target_storage_class": target.storage_class,
        })
    if actual != expected:
        raise ValueError(f"linked bytes or relocation destination differ: {owner} at {address:#x}")
    return evidence


def _verify_sections(
    objects: dict[str, CoffObject], mapped: bytes, image_base: int, symbols: LinkSymbols,
    *, code: bool,
) -> dict:
    symbols.bind_objects(objects)
    verified = []
    unverified = []
    for owner, obj in objects.items():
        for number, section in enumerate(obj.sections, 1):
            if (
                not section.data
                or not section.characteristics & (0x20 if code else 0xC0)
                or section.characteristics & 0x800  # IMAGE_SCN_LNK_REMOVE
                or section.name.startswith(".debug")
            ):
                continue
            members = [
                symbol for symbol in obj.symbols
                if symbol.section_number == number
                and symbol.name != section.name and symbol.storage_class in (2, 3)
            ]
            anchors = []
            unresolved = []
            for member in members:
                try:
                    linked = symbols.resolve_symbol(member, owner)
                except ValueError as error:
                    unresolved.append({"name": member.name, "reason": str(error)})
                    continue
                anchors.append((member, linked))
            record = {
                "object": owner, "section": section.name, "section_number": number,
                "bytes": len(section.data),
            }
            if not anchors or (code and unresolved):
                unverified.append({
                    **record,
                    "reason": "incomplete independent symbol anchors" if anchors else "no independent linked symbol anchor",
                    "unresolved_symbols": unresolved,
                })
                continue
            bases = {linked - member.value for member, linked in anchors}
            if len(bases) != 1:
                raise ValueError(f"inconsistent section ownership: {owner} {number}")
            address = bases.pop()
            offset = address - image_base
            if not 0 <= offset <= len(mapped) - len(section.data):
                raise ValueError(f"source section outside linked image: {owner} {number}")
            linked_section = symbols.section_for_span(
                address, len(section.data), data=not code, code=code,
            )
            relocations = verify_relocated_bytes(
                section.data, mapped[offset : offset + len(section.data)], address,
                section.relocations, obj, symbols, owner,
            )
            verified.append({
                **record,
                "linked_address": address,
                "linked_section": linked_section,
                "zero_initialized": bool(section.characteristics & 0x80),
                "source_section_sha256": hashlib.sha256(section.data).hexdigest(),
                "symbols": [{"name": m.name, "offset": m.value} for m, _ in anchors],
                "unresolved_symbols": unresolved,
                "verified_relocations": relocations,
            })
    # COMDAT pooling may give several objects the same storage. Count the union.
    ranges = sorted((r["linked_address"], r["linked_address"] + r["bytes"]) for r in verified)
    unique_bytes = 0
    end = 0
    for start, stop in ranges:
        unique_bytes += max(0, stop - max(start, end))
        end = max(end, stop)
    return {
        "scope": (
            "All linked source code sections, including helpers and support; not native function matching"
            if code else "Initial linked source storage; not original PE data-layout matching"
        ),
        "verified_unique_bytes": unique_bytes,
        "verified_sections": verified,
        "unverified_sections": unverified,
    }


def verify_data_sections(
    objects: dict[str, CoffObject], mapped: bytes, image_base: int, symbols: LinkSymbols,
) -> dict:
    return _verify_sections(objects, mapped, image_base, symbols, code=False)


def verify_code_sections(
    objects: dict[str, CoffObject], mapped: bytes, image_base: int, symbols: LinkSymbols,
) -> dict:
    return _verify_sections(objects, mapped, image_base, symbols, code=True)


def load_link_symbols(image_path: Path, map_path: Path) -> tuple[pefile.PE, LinkSymbols]:
    data = image_path.read_bytes()
    pe = pefile.PE(data=data)
    return pe, LinkSymbols(data, pe, map_path.read_text())
