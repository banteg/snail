"""Export classification from a temporary IDB copy, without saving analysis changes.

Arguments: original PE path, output JSON path. Uses only IDAPython and stdlib.
"""

import hashlib
import json
import struct
from pathlib import Path

import ida_auto
import ida_bytes
import ida_nalt
import ida_pro
import idaapi
import idautils
import idc


def main():
    image = Path(idc.ARGV[1]).read_bytes()
    digest = hashlib.sha256(image).hexdigest()
    if ida_nalt.retrieve_input_file_sha256().hex() != digest:
        raise ValueError("IDA database input hash does not match original PE")
    pe = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe:pe + 4] != b"PE\0\0":
        raise ValueError("not a PE image")
    count = struct.unpack_from("<H", image, pe + 6)[0]
    optional_size = struct.unpack_from("<H", image, pe + 20)[0]
    if struct.unpack_from("<H", image, pe + 24)[0] != 0x10B:
        raise ValueError("expected PE32")
    base = struct.unpack_from("<I", image, pe + 24 + 28)[0]
    sections = []
    ida_auto.auto_wait()
    for index in range(count):
        offset = pe + 24 + optional_size + index * 40
        name, size, rva, raw_size, raw_offset = struct.unpack_from("<8sIIII", image, offset)
        flags = struct.unpack_from("<I", image, offset + 36)[0]
        if not flags & 0x20000000:
            continue
        start, end = base + rva, base + rva + size
        expected = image[raw_offset:raw_offset + min(size, raw_size)].ljust(size, b"\0")
        actual = ida_bytes.get_bytes(start, size)
        if actual != expected:
            raise ValueError("IDA section bytes differ from original PE")
        classification = []
        kind = None
        run_start = start
        for address in range(start, end):
            flags = ida_bytes.get_full_flags(address)
            if ida_bytes.is_code(flags):
                current = "code"
            elif ida_bytes.is_align(flags):
                current = "alignment"
            elif ida_bytes.is_data(flags):
                current = "data"
            elif ida_bytes.is_tail(flags):
                current = kind or "unknown"
            else:
                current = "unknown"
            if current != kind:
                if kind is not None:
                    classification.append([run_start, address, kind])
                run_start, kind = address, current
        if kind is not None:
            classification.append([run_start, end, kind])
        sections.append({
            "name": name.rstrip(b"\0").decode(), "start": start, "end": end,
            "sha256": hashlib.sha256(actual).hexdigest(), "classification": classification,
        })
    output = {
        "schema_version": 1, "tool": "IDA", "tool_version": idaapi.get_kernel_version(),
        "input_sha256": digest, "sections": sections,
        "functions": [
            {"start": a, "name": idc.get_func_name(a), "ranges": list(idautils.Chunks(a))}
            for a in idautils.Functions()
            if any(s["start"] <= a < s["end"] for s in sections)
        ],
    }
    Path(idc.ARGV[2]).write_text(json.dumps(output, indent=2) + "\n")


try:
    main()
except Exception:  # noqa: BLE001 -- every IDAPython failure must exit headless IDA nonzero
    import traceback
    traceback.print_exc()
    ida_pro.qexit(1)
else:
    ida_pro.qexit(0)
