# save_config_file @ 0x42f540

Writes the config blob directly with `fopen("wb")`, `fwrite`, and `fclose`.
Unlike `save_file_bytes_with_optional_archive_scramble`, this helper does not
scramble data or report save failures; the failure path only calls `_getcwd`
into a 512-byte stack buffer and returns that CRT result.

Match status: 100%, 31/31 target instructions, 5 masked operands ok.
