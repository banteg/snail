"""Binary Ninja 6 DOL view. Import normally; do not exec/reload registered types."""

import binaryninja as bn

from .format import HEADER_SIZE, InvalidDOL, parse_header


class NintendoDOLView(bn.BinaryView):
    name = "Nintendo DOL"
    long_name = "Nintendo GameCube/Wii DOL (paired-single PowerPC)"

    def __init__(self, parent):
        super().__init__(parent_view=parent, file_metadata=parent.file)
        self._entry_point = 0

    @classmethod
    def is_valid_for_data(cls, data):
        try:
            parse_header(data.read(0, HEADER_SIZE), data.length)
            return True
        except InvalidDOL:
            return False

    def init(self):
        try:
            parent = self.parent_view
            layout = parse_header(parent.read(0, HEADER_SIZE), parent.length)
            # Plain ppc cannot lift Gekko/Broadway paired-single instructions.
            self.arch = bn.Architecture["ppc_ps"]
            self.platform = self.arch.standalone_platform
            self._entry_point = layout.entry_point
            for section in (*layout.sections, *layout.bss):
                flags = bn.SegmentFlag.SegmentReadable
                if section.executable:
                    flags |= bn.SegmentFlag.SegmentExecutable
                    semantics = bn.SectionSemantics.ReadOnlyCodeSectionSemantics
                else:
                    flags |= bn.SegmentFlag.SegmentWritable
                    semantics = bn.SectionSemantics.ReadWriteDataSectionSemantics
                self.add_auto_segment(
                    section.address,
                    section.size,
                    section.offset or 0,
                    section.size if section.offset is not None else 0,
                    flags,
                )
                self.add_auto_section(
                    section.name, section.address, section.size, semantics
                )
            if not self.parse_only:
                self.define_auto_symbol(
                    bn.Symbol(bn.SymbolType.FunctionSymbol, self._entry_point, "_start")
                )
                self.add_entry_point(self._entry_point)
                self.store_metadata(
                    "dol.layout",
                    {
                        "version": 1,
                        "entry_point": layout.entry_point,
                        "bss_address": layout.bss_address,
                        "bss_size": layout.bss_size,
                        "initialized_sections": len(layout.sections),
                        "bss_intervals": len(layout.bss),
                    },
                )
            return True
        except (InvalidDOL, KeyError) as error:
            bn.log_error(f"Nintendo DOL: {error}")
            return False

    def perform_is_executable(self):
        return True

    def perform_get_entry_point(self):
        return self._entry_point

    def perform_get_address_size(self):
        return 4

    def perform_get_default_endianness(self):
        return bn.Endianness.BigEndian


# Core stores native callback pointers, so retain the registered class for the
# lifetime of the process, including across accidental importlib.reload calls.
# Source changes to the view require a restart; never replace live callbacks.
def _register_view(view_class):
    existing = getattr(bn, "_snail_nintendo_dol_view", None)
    if existing is not None:
        return existing
    if view_class.name in {view.name for view in bn.BinaryViewType}:
        raise RuntimeError(f"A different loader already registered {view_class.name!r}")
    view_class.register()
    bn._snail_nintendo_dol_view = view_class
    return view_class


NintendoDOLView = _register_view(NintendoDOLView)
