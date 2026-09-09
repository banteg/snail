"""Live Binary Ninja verification; usable via bn py or the GUI console."""

import hashlib
from pathlib import Path

from .format import parse_header


def verify_view(view, source):
    """Raise on any discrepancy between the declared DOL and the live view."""
    source = Path(source)
    blob = source.read_bytes()
    layout = parse_header(blob[:256], len(blob))
    assert view.view_type == "Nintendo DOL", view.view_type
    assert view.arch.name == "ppc_ps", view.arch.name
    assert view.address_size == 4
    assert view.endianness.name == "BigEndian"
    assert view.entry_point == layout.entry_point
    expected = (*layout.sections, *layout.bss)
    records = []
    for section in expected:
        mapped = view.sections[section.name]
        assert (mapped.start, mapped.end) == (section.address, section.end)
        segment = view.get_segment_at(section.address)
        assert (segment.start, segment.end) == (section.address, section.end)
        assert segment.readable
        assert segment.executable == section.executable
        assert segment.writable == (not section.executable)
        assert segment.data_offset == (section.offset or 0)
        assert segment.data_length == (
            section.size if section.offset is not None else 0
        )
        reference = (
            blob[section.offset : section.offset + section.size]
            if section.offset is not None
            else bytes(section.size)
        )
        assert view.read(section.address, section.size) == reference, section.name
        records.append(
            {
                "name": section.name,
                "address": hex(section.address),
                "size": section.size,
                "file_offset": section.offset,
                "sha256": hashlib.sha256(reference).hexdigest(),
            }
        )
    # BN itself may append a .synthetic_builtins segment. It must never obscure
    # any DOL region; do not count it as file content or reject it as loader data.
    extras = [
        s for name, s in view.sections.items() if name not in {x.name for x in expected}
    ]
    assert all(s.name == ".synthetic_builtins" for s in extras)
    assert all(
        not (s.start < x.end and x.address < s.end) for s in extras for x in expected
    )
    assert not view.is_valid_offset(0), "DOL header must not be mapped at address zero"
    return {
        "source_sha256": hashlib.sha256(blob).hexdigest(),
        "source_size": len(blob),
        "view_type": view.view_type,
        "architecture": view.arch.name,
        "entry_point": hex(view.entry_point),
        "initialized_bytes_verified": sum(s.size for s in layout.sections),
        "bss_bytes_verified": sum(s.size for s in layout.bss),
        "regions": records,
        "synthetic_sections": [s.name for s in extras],
    }
