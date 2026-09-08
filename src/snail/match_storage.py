"""Selected source-defined initial storage compared with the original PE.

Contracts require independently recovered extents and exact accessor/constructor
bodies. They do not infer ownership from runs of zeroes, reconstruct original
translation units, or contribute to the public data/linked denominators.
"""

import hashlib
import struct
from dataclasses import dataclass

import pefile

from .match import CoffObject


@dataclass(frozen=True)
class StorageContract:
    object: str
    symbol: str
    native_name: str
    size: int
    proof_functions: tuple[str, ...]
    zero_initialized: bool = True
    size_symbol: str | None = None
    size_index: int = 0


CONTRACTS = (
    StorageContract(
        "rmath_storage.obj",
        "?g_cosine_table@@3PAMA",
        "g_cosine_table",
        0x8000,
        ("initialize_trigonometry_tables", "cosine"),
        size_symbol="_rmath_storage_sizes",
    ),
    StorageContract(
        "rmath_storage.obj",
        "?g_sine_table@@3PAMA",
        "g_sine_table",
        0x8000,
        ("initialize_trigonometry_tables", "sine"),
        size_symbol="_rmath_storage_sizes",
        size_index=1,
    ),
    StorageContract(
        "rmath_storage.obj",
        "?g_math_random_table@@3PAHA",
        "g_math_random_table",
        0x7FFC,
        ("initialize_math_random_table", "next_math_random_value"),
        size_symbol="_rmath_storage_sizes",
        size_index=2,
    ),
    StorageContract(
        "rmath_storage.obj",
        "?g_math_random_index@@3HA",
        "g_math_random_index",
        4,
        ("initialize_math_random_table", "next_math_random_value"),
        size_symbol="_rmath_storage_sizes",
        size_index=3,
    ),
    StorageContract(
        "allocator_storage.obj",
        "?g_tracked_allocation_stack@@3VTrackedAllocationStack@@A",
        "g_tracked_allocation_stack",
        0x2BF28,
        (
            "push_tracked_allocation",
            "pop_tracked_allocation",
            "get_tracked_allocation_size",
        ),
        size_symbol="_allocator_storage_sizes",
    ),
    StorageContract(
        "allocator_storage.obj",
        "?g_tracked_allocation_total_bytes@@3HA",
        "g_tracked_allocation_total_bytes",
        4,
        ("allocate_tracked_memory", "free_tracked_memory"),
        size_symbol="_allocator_storage_sizes",
        size_index=1,
    ),
    StorageContract(
        "path-nodes_storage.obj",
        "?g_bod_base_vtable@@3PAXA",
        "g_bod_base_vtable",
        4,
        ("initialize_bod_base", "noop_runtime_ai"),
        False,
        "_path_nodes_storage_sizes",
    ),
    StorageContract(
        "path-nodes_storage.obj",
        "?g_path_template_record_vtable@@3PAXA",
        "g_path_template_record_vtable",
        4,
        ("initialize_path_template_record_pair", "noop_runtime_ai"),
        False,
        "_path_nodes_storage_sizes",
        1,
    ),
)


def original_span(pe: pefile.PE, address: int, size: int) -> bytes:
    """Read only inside a declared virtual data extent, including its BSS tail."""
    rva = address - pe.OPTIONAL_HEADER.ImageBase
    sections = [
        s
        for s in pe.sections
        if s.VirtualAddress <= rva
        and rva + size <= s.VirtualAddress + s.Misc_VirtualSize
    ]
    if size <= 0 or len(sections) != 1 or not sections[0].Characteristics & 0xC0:
        raise ValueError(f"native storage outside a data section: {address:#x}")
    section = sections[0]
    offset = rva - section.VirtualAddress
    data = section.get_data()[: section.Misc_VirtualSize].ljust(
        section.Misc_VirtualSize, b"\0"
    )
    return data[offset : offset + size]


def verify_owner(
    contract: StorageContract,
    obj: CoffObject,
    native: bytes,
    native_targets: dict[str, int],
) -> dict:
    """Compare a bounded source symbol, resolving every pointer to native code."""
    definitions = [
        s
        for s in obj.symbols
        if s.name == contract.symbol and s.storage_class == 2 and s.section_number > 0
    ]
    if len(definitions) != 1:
        raise ValueError(f"missing or ambiguous storage definition: {contract.symbol}")
    symbol = definitions[0]
    section = obj.sections[symbol.section_number - 1]
    if (
        not section.characteristics & 0xC0
        or section.characteristics & 0x800
        or bool(section.characteristics & 0x80) != contract.zero_initialized
    ):
        raise ValueError(f"wrong source storage kind: {contract.symbol}")
    end = symbol.value + contract.size
    if contract.size <= 0 or symbol.value < 0 or end > len(section.data):
        raise ValueError(f"source storage extent is too small: {contract.symbol}")
    if any(
        s.section_number == symbol.section_number
        and s.storage_class in (2, 3)
        and s.name != section.name
        and s.raw_index != symbol.raw_index
        and symbol.value <= s.value < end
        for s in obj.symbols
    ):
        raise ValueError(f"source storage overlaps another owner: {contract.symbol}")
    source = section.data[symbol.value : end]
    if contract.zero_initialized and any(source):
        raise ValueError(f"nonzero source BSS initializer: {contract.symbol}")
    if contract.size_symbol:
        sizes = [
            s
            for s in obj.symbols
            if s.name == contract.size_symbol
            and s.storage_class == 2
            and s.section_number > 0
        ]
        if len(sizes) != 1 or contract.size_index < 0:
            raise ValueError(f"missing compiler size witness: {contract.symbol}")
        size_owner = sizes[0]
        size_section = obj.sections[size_owner.section_number - 1]
        size_offset = size_owner.value + contract.size_index * 4
        if (
            not size_section.characteristics & 0x40
            or not 0 <= size_offset <= len(size_section.data) - 4
            or any(
                r.virtual_address < size_offset + 4
                and r.virtual_address + 4 > size_offset
                for r in size_section.relocations
            )
        ):
            raise ValueError(f"invalid compiler size witness: {contract.symbol}")
        source_size = struct.unpack_from("<I", size_section.data, size_offset)[0]
    else:
        # Without an emitted sizeof witness, only an unpadded symbol interval
        # can establish the complete source extent. Do not silently take a prefix.
        following = [
            s.value
            for s in obj.symbols
            if s.section_number == symbol.section_number
            and s.storage_class in (2, 3)
            and s.value > symbol.value
        ]
        source_size = min(following, default=len(section.data)) - symbol.value
    if source_size != contract.size:
        raise ValueError(
            f"source storage extent disagrees with contract: {contract.symbol}"
        )
    expected = bytearray(source)
    by_index = {s.raw_index: s for s in obj.symbols}
    occupied = set()
    pointers = []
    for relocation in section.relocations:
        if not (
            relocation.virtual_address < end
            and relocation.virtual_address + 4 > symbol.value
        ):
            continue
        offset = relocation.virtual_address - symbol.value
        if contract.zero_initialized or relocation.relocation_type != 0x06:
            raise ValueError(
                f"unsupported native storage relocation: {contract.symbol}"
            )
        if not 0 <= offset <= contract.size - 4 or occupied.intersection(
            range(offset, offset + 4)
        ):
            raise ValueError(
                f"overlapping or unbounded storage relocation: {contract.symbol}"
            )
        occupied.update(range(offset, offset + 4))
        target = by_index.get(relocation.symbol_index)
        if target is None or target.name not in native_targets:
            raise ValueError(
                f"storage pointer lacks an exact source definition: {contract.symbol}"
            )
        addend = struct.unpack_from("<i", source, offset)[0]
        # These contracts describe whole callback entry points, not interior code.
        if addend:
            raise ValueError(f"unexpected callback pointer addend: {contract.symbol}")
        address = native_targets[target.name]
        struct.pack_into("<I", expected, offset, address)
        pointers.append(
            {"offset": offset, "symbol": target.name, "native_target": address}
        )
    if not contract.zero_initialized and occupied != set(range(contract.size)):
        raise ValueError(f"callback storage is not source relocated: {contract.symbol}")
    if bytes(expected) != native:
        raise ValueError(f"source/native initial storage differs: {contract.symbol}")
    return {
        "name": contract.native_name,
        "symbol": contract.symbol,
        "object": contract.object,
        "source_offset": symbol.value,
        "bytes": contract.size,
        "source_size_witness": contract.size_symbol or "unpadded COFF symbol interval",
        "kind": "zero-initialized owner"
        if contract.zero_initialized
        else "callback-table projection",
        "source_sha256": hashlib.sha256(source).hexdigest(),
        "native_sha256": hashlib.sha256(native).hexdigest(),
        "proof_functions": list(contract.proof_functions),
        "pointers": pointers,
    }


def verify_native_storage(
    objects: dict[str, CoffObject],
    pe: pefile.PE,
    references: list[dict],
    functions: list[dict],
    contracts: tuple[StorageContract, ...] = CONTRACTS,
) -> dict:
    """Verify contracts belonging to the supplied source storage objects."""
    exact = {r["function"] for r in functions if r["normalized_exact"]}
    native_targets = {
        r["symbol"]: r["native_address"] for r in functions if r["normalized_exact"]
    }
    by_name = {r["name"]: r for r in references}
    verified = []
    ranges = []
    for contract in contracts:
        if contract.object not in objects:
            continue
        if not set(contract.proof_functions) <= exact:
            raise ValueError(
                f"storage contract lacks exact code witnesses: {contract.native_name}"
            )
        reference = by_name[contract.native_name]
        if int(reference["size"], 0) != contract.size or reference["kind"] not in (
            "global",
            "vtable",
        ):
            raise ValueError(
                f"native storage extent/kind disagrees with manifest: {contract.native_name}"
            )
        address = int(reference["address"], 0)
        if any(
            address < end and start < address + contract.size for start, end in ranges
        ):
            raise ValueError(f"native storage owners overlap: {contract.native_name}")
        ranges.append((address, address + contract.size))
        evidence = verify_owner(
            contract,
            objects[contract.object],
            original_span(pe, address, contract.size),
            native_targets,
        )
        verified.append({**evidence, "native_address": address})
    return {
        "scope": "Selected initial storage spans; no original placement, original TU, runtime-state, or public data credit",
        "verified_bytes": sum(r["bytes"] for r in verified),
        "verified_owners": verified,
    }
