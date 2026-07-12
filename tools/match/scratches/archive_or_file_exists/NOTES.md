# archive_or_file_exists @ 0x430fd0

Initial shape:

- Uses the loaded archive index (`g_archive_index_records`, `0x53c7f8`) when
  present and the caller has not forced the filesystem path.
- Filesystem mode probes with `fopen(path, "rb")`, closes on success, and
  returns a byte boolean.
- Archive mode calls `find_archive_entry(path)` and warns with
  `"Missing Dat File %s"` before returning false on a miss.

Status:

- 2026-06-18: 100%, 36/36 target instructions, 7 masked operands ok.

Cross-port ownership:

- iOS `RShell.o` names the exact public contract
  `RShellFindFile(char*, bool)`.
- Its boolean formal selects the same DAT-index versus direct-filesystem path
  as the Windows byte formal; the stable harness name remains descriptive.
