"""Install a small startup shim; the loader source stays in this checkout."""

import argparse
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--plugin-dir", required=True, type=Path)
    args = parser.parse_args()
    module_root = Path(__file__).resolve().parent
    shim = (
        "# Nintendo DOL loader installed from the Snail Mail tools checkout.\n"
        "import sys\n"
        f"_dol_tools = {str(module_root)!r}\n"
        "if _dol_tools not in sys.path:\n"
        "    sys.path.insert(0, _dol_tools)\n"
        "import dol_loader.view\n"
        "import binaryninja\n"
        "if binaryninja.core_ui_enabled():\n"
        "    import dol_loader.gui\n"
    )
    destination = args.plugin_dir.expanduser() / "snail_nintendo_dol.py"
    if destination.exists():
        if destination.read_text() != shim:
            raise SystemExit(f"Refusing to overwrite a different plugin: {destination}")
    else:
        destination.parent.mkdir(parents=True, exist_ok=True)
        # Exclusive create also prevents overwriting a file created after the check.
        with destination.open("x") as stream:
            stream.write(shim)
    print(destination)


if __name__ == "__main__":
    main()
