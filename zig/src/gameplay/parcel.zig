//! Parcel pickup + home-flight + delivery runtime pool.
//!
//! Native references:
//! - 50-slot `cRTrackParcel` pool at `game + 0x125e480` (stride 0x8c)
//! - `spawn_track_parcel` / `update_track_parcel` / `register_parcel_delivery`
//!
//! The Runner reaches in through `runner.parcel` for all parcel slot state.
//! Cross-cutting logic (collision → damage/score, row-event staging) still
//! lives on Runner for now; this module owns the pool shape + the
//! collected-row dedup table.

const gameplay_runtime_entities = @import("runtime_entities.zig");

const TrackParcel = gameplay_runtime_entities.TrackParcel;
const TrackParcelHomeAnchor = gameplay_runtime_entities.TrackParcelHomeAnchor;

pub const max_active_track_parcels: usize = 50;
pub const max_collected_parcel_rows: usize = 1024;

pub const Pool = struct {
    home_anchor: TrackParcelHomeAnchor = .{},
    slots: [max_active_track_parcels]TrackParcel = [_]TrackParcel{.{}} ** max_active_track_parcels,
    last_scan_end: usize = 0,
    collected_rows: [max_collected_parcel_rows]usize = [_]usize{0} ** max_collected_parcel_rows,
    collected_row_count: usize = 0,

    pub fn reset(self: *Pool) void {
        self.* = .{};
    }

    pub fn active(self: *const Pool) []const TrackParcel {
        return self.slots[0..];
    }

    pub fn slot(self: *Pool, index: usize) *TrackParcel {
        return &self.slots[index];
    }

    /// Walks the slot table looking for the first live parcel (state != 0)
    /// that carries `global_row`. Used by `collectLiveTrackParcel` and
    /// `liveTrackParcelAt`.
    pub fn findSlotIndex(self: *const Pool, global_row: usize) ?usize {
        for (0..self.slots.len) |index| {
            const parcel = self.slots[index];
            if (parcel.active() and parcel.row == global_row) return index;
        }
        return null;
    }

    /// Claim the first vacant slot (state == 0). Returns a mutable pointer
    /// or null if the pool is saturated (50 live parcels).
    pub fn allocateSlot(self: *Pool) ?*TrackParcel {
        for (&self.slots) |*parcel| {
            if (!parcel.active()) return parcel;
        }
        return null;
    }

    pub fn isCollected(self: *const Pool, global_row: usize) bool {
        for (0..self.collected_row_count) |index| {
            if (self.collected_rows[index] == global_row) return true;
        }
        return false;
    }

    /// Appends the row to the collected-row dedup table. Returns false if
    /// the row was already collected (caller should treat as a no-op).
    pub fn markCollected(self: *Pool, global_row: usize) bool {
        if (self.isCollected(global_row)) return false;
        if (self.collected_row_count < max_collected_parcel_rows) {
            self.collected_rows[self.collected_row_count] = global_row;
            self.collected_row_count += 1;
        }
        return true;
    }
};
