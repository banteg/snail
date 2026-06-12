//! Original-bug policy switch for the native-mirror modules.
//!
//! The port fixes documented native bugs by default; `--preserve-bugs`
//! flips this switch so mirrors reproduce the original behavior for
//! differential testing against the Windows build. Every divergence must
//! have an entry in docs/rewrite/original-bugs.md citing the matched
//! evidence, and the mirror branch should reference the entry id.

const std = @import("std");

/// Set once at startup from app Options; read by mirror modules at the
/// documented divergence points.
pub var preserve: bool = false;

test "defaults to fixed behavior" {
    try std.testing.expect(!preserve);
}
