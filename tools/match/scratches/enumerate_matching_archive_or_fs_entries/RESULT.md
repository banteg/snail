# enumerate_matching_archive_or_fs_entries @ 0x431740

| Metric | Whole RShell unit, MSVC6 SP3 |
|---|---:|
| Normalized match | 92.31% |
| Candidate / target instructions | 182 / 182 |
| Common prefix | 9 / 182 |
| Reference audit | 26 clean |
| Encoded body | Partial |

The current source walks the typed archive entries and uses the VC6 CRT's
`_finddata_t`, `_findfirst`, `_findnext`, `_getcwd`, and `_chdir` for loose
files. The remaining differences lie in the two archive-index stack slots
and the wildcard comparison. Windows carries the pattern byte through the
first `RstrASC` call in BL and spills the folded basename byte across the
second. [Scratch notes](NOTES.md)
