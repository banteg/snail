"""Exercise the macOS host imports with the minimal memory view wasm2c supplies."""

import shlex
import shutil
import subprocess
import sys

import pytest

from snail.symbols import REPO_ROOT

pytestmark = pytest.mark.skipif(
    sys.platform != "darwin" or not shutil.which("c++"), reason="needs the macOS host"
)


@pytest.fixture
def run_probe(tmp_path):
    (tmp_path / "game.h").write_text(
        "struct w2c_game { struct { uint8_t* data; } w2c_memory; };\n"
    )

    def run(cpp, *args, flags=()):
        source = tmp_path / "probe.cpp"
        source.write_text(cpp)
        executable = tmp_path / "probe"
        subprocess.run(
            ["c++", "-std=c++17", "-I", str(tmp_path), "-I", str(REPO_ROOT / "port/native"),
             str(source), *flags, "-o", str(executable)], check=True,
        )  # fmt: skip
        subprocess.run([executable, *args], check=True)

    return run


def test_native_wasi_filesystem_boundary(tmp_path, run_probe):
    root = tmp_path / "game"
    (root / "saves").mkdir(parents=True)
    outside = tmp_path / "outside"
    (outside / "subdir").mkdir(parents=True)
    (outside / "existing").write_bytes(b"preserve")
    (root / "linked.dat").symlink_to(outside / "existing")
    (root / "linked-dir").symlink_to(outside, target_is_directory=True)
    run_probe(
        """
#include "wasi.cpp"
#include <assert.h>

int main(int argc, char** argv) {
    uint8_t bytes[256] = {};
    w2c_game game = {{bytes}};
    w2c_wasi__snapshot__preview1 wasi = {&game, wasi_create(argv[1])};
    auto path = [&](const char* name) {
        memcpy(bytes, name, strlen(name));
        return (uint32_t)strlen(name);
    };
    auto open_file = [&](const char* name, bool write) {
        return w2c_wasi__snapshot__preview1_path_open(&wasi, ROOT_FD, 1, 0, path(name),
            write ? OFLAGS_CREAT | OFLAGS_TRUNC : 0, write ? RIGHT_FD_WRITE : 0, 0, 0, 128);
    };
    assert(open_file("linked.dat", false) == 0);
    assert(open_file("linked.dat", true) != 0);
    assert(open_file("linked-dir/existing", true) != 0);
    assert(open_file("linked-dir/new", true) != 0);
    assert(w2c_wasi__snapshot__preview1_path_unlink_file(&wasi, ROOT_FD, 0, path("linked-dir/existing")) != 0);
    assert(w2c_wasi__snapshot__preview1_path_remove_directory(&wasi, ROOT_FD, 0, path("linked-dir/subdir")) != 0);
    assert(open_file("saves/../saves/ScoreA.dat", true) == 0);
    assert(w2c_wasi__snapshot__preview1_path_unlink_file(&wasi, ROOT_FD, 0, path("saves/scorea.dat")) == 0);
}
""",
        root,
    )
    assert (outside / "existing").read_bytes() == b"preserve"
    assert (outside / "subdir").is_dir()
    assert not (outside / "new").exists()


def test_native_audio_bus_scales_current_and_future_tracks(run_probe):
    if (
        not shutil.which("pkg-config")
        or subprocess.run(["pkg-config", "--exists", "sdl3-mixer"], check=False).returncode
    ):
        pytest.skip("needs SDL3_mixer")
    flags = shlex.split(
        subprocess.check_output(
            ["pkg-config", "--cflags", "--libs", "sdl3-mixer"], text=True
        )
    )
    run_probe(
        """
#include "mixer.cpp"
#include <assert.h>

int main() {
    assert(SDL_Init(0) && MIX_Init());
    SDL_AudioSpec spec = {SDL_AUDIO_F32, 2, 44100};
    MixerPresenter presenter;
    presenter.mixer = MIX_CreateMixer(&spec);
    assert(presenter.mixer);
    w2c_snail host = {};
    host.mixer = &presenter;
    float pcm[128] = {};
    presenter.sounds[1] = {MIX_LoadRawAudio(presenter.mixer, pcm, sizeof(pcm), &spec), nullptr, spec.freq};
    assert(presenter.sounds[1].audio);
    w2c_snail_bus_volume(&host, 0, 0);
    w2c_snail_channel_play(&host, 1, 1, 0, 0.5f, 0, 0, 0);
    assert(MIX_GetTrackGain(presenter.channels.at(1).track) == 0);
    w2c_snail_bus_volume(&host, 0, 0.25f);
    assert(MIX_GetTrackGain(presenter.channels.at(1).track) == 0.125f);
    w2c_snail_channel_play(&host, 1, 1, 1, 0.5f, 0, 0, 0);
    w2c_snail_bus_volume(&host, 0, 0);
    assert(MIX_GetTrackGain(presenter.channels.at(1).track) == 0.5f);
    MIX_DestroyMixer(presenter.mixer);
    MIX_Quit();
    SDL_Quit();
}
""",
        flags=flags,
    )
