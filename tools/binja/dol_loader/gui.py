"""A DOL-only open command bypasses BN 6.1's false LZMA container detection."""

from pathlib import Path

import binaryninja as bn
from binaryninjaui import FileContext, UIContext

from .format import HEADER_SIZE, InvalidDOL, parse_header
from .view import NintendoDOLView


def open_dol(_view):
    filename = bn.get_open_filename_input("Open Nintendo DOL", "Nintendo DOL (*.dol)")
    if not filename:
        return
    try:
        path = Path(filename)
        with path.open("rb") as stream:
            parse_header(stream.read(HEADER_SIZE), path.stat().st_size)
        view = bn.load(
            filename,
            options={"files.container.mode": "Disabled"},
            update_analysis=False,
        )
        if view is None:
            raise InvalidDOL("Binary Ninja could not load the file")
        if view.view_type != NintendoDOLView.name:
            kind = view.view_type
            view.file.close()
            raise InvalidDOL(f"unexpected loader: {kind}")
    except (OSError, InvalidDOL) as error:
        bn.show_message_box("Cannot open Nintendo DOL", str(error))
        return

    def show():
        context = UIContext.activeContext()
        if context is None:
            view.file.close()
            return
        file_context = FileContext(view.file, view.parent_view, filename)
        frame = context.openFileContext(file_context)
        if frame is None:
            file_context.close()
            return
        view.update_analysis()

    bn.execute_on_main_thread(show)


bn.PluginCommand.register(
    "Nintendo DOL\\Open...",
    "Open a validated GameCube/Wii DOL without container transforms.",
    open_dol,
)
