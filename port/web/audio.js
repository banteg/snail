// Web Audio presenter for the emulated BASS library (port/shell/
// audio_backend.h). Sounds are the game's encoded OGG files, decoded by the
// browser; a channel plays one sound on the sample or stream bus with a
// volume, pan, rate and loop flag. Browsers start audio only after a user
// gesture, so the context resumes when the splash is clicked (snail.js); until
// then channels wait silently, as if paused. `muted` silences everything.

export class AudioPresenter {
  constructor({ muted = false } = {}) {
    this.context = new AudioContext();
    this.master = this.context.createGain();
    this.master.gain.value = muted ? 0 : 1;
    this.master.connect(this.context.destination);
    this.memory = null;
    this.sounds = new Map(); // id -> { buffer, failed, decoding }
    this.channels = new Map(); // id -> { sound, options, source, ended }
    this.unlocked = false;
    this.paused = false;
    this.buses = [this.context.createGain(), this.context.createGain()];
    for (const bus of this.buses) bus.connect(this.master);
    this.warned = false;
  }

  bind(memory) {
    this.memory = memory;
  }

  // Call from a user gesture.
  unlock() {
    if (this.unlocked) return;
    this.unlocked = true;
    this.apply();
  }

  apply() {
    if (this.unlocked && !this.paused) this.context.resume();
    else this.context.suspend();
  }

  start(id, channel) {
    const sound = this.sounds.get(channel.sound);
    if (!sound || sound.failed) {
      channel.ended = true;
      return;
    }
    if (!sound.buffer) return; // started when decoding finishes
    const { bus, volume, pan, frequency, loop } = channel.options;
    const source = this.context.createBufferSource();
    source.buffer = sound.buffer;
    source.loop = loop;
    if (frequency) source.playbackRate.value = frequency / sound.buffer.sampleRate;
    const gain = this.context.createGain();
    gain.gain.value = volume;
    const panner = this.context.createStereoPanner();
    panner.pan.value = pan;
    source.connect(gain).connect(panner).connect(this.buses[bus]);
    source.onended = () => {
      if (this.channels.get(id) === channel) channel.ended = true;
    };
    source.start();
    channel.source = source;
  }

  imports() {
    return {
      sound_create: (id, pointer, size) => {
        const bytes = new Uint8Array(this.memory.buffer, pointer, size).slice();
        const sound = { buffer: null, failed: false };
        this.sounds.set(id, sound);
        this.context.decodeAudioData(bytes.buffer).then(
          (buffer) => {
            sound.buffer = buffer;
            for (const [channelId, channel] of this.channels) {
              if (channel.sound === id && !channel.source && !channel.ended) this.start(channelId, channel);
            }
          },
          (error) => {
            sound.failed = true;
            for (const channel of this.channels.values()) if (channel.sound === id) channel.ended = true;
            if (!this.warned) {
              this.warned = true;
              console.warn("Snail Mail: this browser cannot decode the game's audio", error);
            }
          },
        );
      },
      sound_destroy: (id) => {
        this.sounds.delete(id);
      },
      channel_play: (id, sound, bus, volume, pan, frequency, loop) => {
        this.stop(id);
        const channel = { sound, options: { bus, volume, pan, frequency, loop: !!loop }, source: null, ended: false };
        this.channels.set(id, channel);
        this.start(id, channel);
      },
      channel_stop: (id) => this.stop(id),
      channel_active: (id) => {
        const channel = this.channels.get(id);
        return channel && !channel.ended ? 1 : 0;
      },
      bus_volume: (bus, volume) => {
        this.buses[bus].gain.value = volume;
      },
      set_paused: (paused) => {
        this.paused = !!paused;
        this.apply();
      },
    };
  }

  stop(id) {
    const channel = this.channels.get(id);
    if (!channel) return;
    this.channels.delete(id);
    if (channel.source) {
      channel.source.onended = null;
      channel.source.stop();
    }
  }
}
