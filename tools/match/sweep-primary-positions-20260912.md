# Sweep primary position ownership

Sharing the primary position operation across Sweep's three sample phases
improves `initialize_sweep_path_template_pair` from **99.38650307% to
99.69325153%**. The function retains **652/652 instructions** and all **37
references at identical instruction and byte positions**. Its exact normalized
prefix grows from **45 to 90 instructions**.

The helper initializes primary X/Y/Z and returns Z for the secondary sample.
It borrows the live primary bank, preserving rereads around calls. Straight
samples use their logical index for Z; curved samples add the three lead-in
nodes and calculate the sine-derived Y. Metadata and Identity initialization
remain in the caller. Using this operation in all three phases recovers the
lead-in and curve receiver setup, while changing the departure setup to the
remaining normalized difference.

The native departure receiver copies the physical offset to ECX before the
primary Y/Z stores, then adds the secondary bank. The candidate instead loads
the bank into ECX after those stores and adds the offset. This is still open.
The retained source has one normalized difference region, down from two.

An independent positional relocation audit compares the complete **2,428-byte
body** and finds **42 to 22 unequal bytes**. The four terminal padding bytes
are accounted separately. Every reference's identity, kind, operand slot,
instruction position and encoded field is checked; all candidate body
relocations are consumed. Ordinary addressing bytes are compared literally.
This change improves the total body comparison but does not preserve every
previously equal byte: departure scheduling changes as described above.

Fourteen controls cross returning Z versus writing an output reference with
each nonempty subset of the three phases. Only the shared returning helper in
all three phases reaches 99.69%. Lead-in alone improves the prefix but retains
99.39%; other combinations are neutral or worse. Further parameter-reference,
secondary-helper separation and Z-lifetime controls produce no additional
retained improvement. Forward and reverse official probes reproduce the gain.

No new exact-function or encoded-body credit is claimed. Compiler, flags,
headers, ABI, extents and matcher policy are unchanged. The
[receipt](sweep-primary-positions-20260912.json) preserves full sources,
hashes, raw and audited bytes, positional references, audit scripts and both
probe directions. The [campaign](four-builder-controls-20260912.md) explains
the complete bounded controls and replay command.

Validation passes all 785 scratches, the exact-reference audit, extern lint,
strict experiment/specification checks, and all 1,140 tests. The complete
source/evidence refresh and saved-evidence validation agree: only Sweep's
normalized ratio improves, with no exact-classification or extent changes.
