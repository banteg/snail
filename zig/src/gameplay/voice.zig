pub const VoiceManager = struct {
    active: bool = false,
    progress: f32 = 0.0,
    delta: f32 = 1.0 / 60.0,

    pub fn tick(self: *VoiceManager) void {
        if (!self.active or self.progress <= 0.0) return;
        self.progress += self.delta;
        if (self.progress > 1.0) {
            self.active = false;
            self.progress = 0.0;
        }
    }

    pub fn arm(self: *VoiceManager) void {
        self.active = true;
        self.progress = self.delta;
    }

    pub fn clear(self: *VoiceManager) void {
        self.* = .{};
    }
};

pub const NativeSet = enum(u8) {
    damage = 0,
    dying = 1,
    enemies = 2,
    fall = 3,
    misc = 4,
    powerup = 5,
    slow = 6,
    start = 7,
    victory = 8,
    ouch = 9,
    package = 10,
    slugged = 11,
    worm_tunnel = 12,
    tutorial = 13,
    postal = 14,
    supertramp = 15,
};

pub const NativeMode = enum(u2) {
    wait_for_idle = 0,
    wait_for_frequency = 1,
    interrupt_current = 2,
};

const set_cooldown_step: f32 = 1.0 / 240.0;
const manager_global_step: f32 = 1.0 / 60.0;
pub const manager_frequency_seconds: f32 = 20.0;

const NativeSetState = struct {
    next_index: usize = 0,
    cooldown_progress: f32 = 0.0,
    cooldown_step: f32 = set_cooldown_step,

    fn tick(self: *NativeSetState) void {
        if (self.cooldown_progress <= 0.0) return;
        self.cooldown_progress += self.cooldown_step;
        if (self.cooldown_progress > 1.0) {
            self.cooldown_progress = 0.0;
        }
    }
};

pub const NativeManager = struct {
    global_progress: f32 = 0.0,
    global_step: f32 = manager_global_step,
    global_frequency_seconds: f32 = manager_frequency_seconds,
    sets: [16]NativeSetState = [_]NativeSetState{.{}} ** 16,

    pub fn tick(self: *NativeManager) void {
        for (&self.sets) |*set_state| {
            set_state.tick();
        }
        self.global_progress += self.global_step;
    }

    pub fn clear(self: *NativeManager) void {
        self.* = .{};
    }

    pub fn requestPlay(
        self: *NativeManager,
        set_id: NativeSet,
        mode: NativeMode,
        voice_busy: bool,
        sample_count: usize,
    ) ?usize {
        if (sample_count == 0) return null;
        switch (mode) {
            .wait_for_idle => {
                if (voice_busy) return null;
            },
            .wait_for_frequency => {
                if (voice_busy) return null;
                if (self.global_progress < self.global_frequency_seconds) return null;
            },
            .interrupt_current => {},
        }

        const set_state = &self.sets[@intFromEnum(set_id)];
        if (set_state.cooldown_progress != 0.0) return null;

        const sample_index = set_state.next_index % sample_count;
        set_state.next_index = (sample_index + 1) % sample_count;
        set_state.cooldown_progress = set_state.cooldown_step;
        if (mode != .wait_for_idle) {
            self.global_progress = 0.0;
        }
        return sample_index;
    }

    pub fn requestPayloadPlay(
        self: *NativeManager,
        set_id: NativeSet,
        mode: NativeMode,
        voice_busy: bool,
        payload_index: usize,
    ) ?usize {
        switch (mode) {
            .wait_for_idle => {
                if (voice_busy) return null;
            },
            .wait_for_frequency => {
                if (voice_busy) return null;
                if (self.global_progress < self.global_frequency_seconds) return null;
            },
            .interrupt_current => {},
        }

        const set_state = &self.sets[@intFromEnum(set_id)];
        if (set_state.cooldown_progress != 0.0) return null;

        set_state.cooldown_progress = set_state.cooldown_step;
        if (mode != .wait_for_idle) {
            self.global_progress = 0.0;
        }
        return payload_index;
    }
};
