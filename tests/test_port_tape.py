"""Lockstep tapes: conversion for the port and per-tick comparison."""

import struct
from pathlib import Path

from snail import port_tape
from snail.port_tape import RECORD, Session, compare, tape_bytes


def make_session():
    tick = {
        "t": "tick", "n": 0, "rq": 1, "k": [1, 0xc8], "kp": [1], "s0": "11" * 0x38, "s1": "22" * 0x38,
        "mx": 320.0, "my": 240.0, "lb": [1, 0], "rb": [0, 0], "wh": 0,
        "s": {"frontend_state": 11, "z": 5.249268054962158}, "rng": [42, 7], "r": 0,
    }  # fmt: skip
    session = Session(Path("session"), 628, (42, 7), [("frontend_state", 0x1B8, "i32"), ("z", 0x42FDEC, "f32")])
    session.ticks = [tick]
    session.renders_after = [1]
    return session


def states(seed, index, frontend_state, z, rng=(42, 7), result=0):
    return b"SNTO" + struct.pack("<IiI", seed, index, 2) + struct.pack("<ifIii", frontend_state, z, *rng, result)


def test_record_matches_the_replayer():
    assert RECORD.size == 152  # static_assert in port/shell/lockstep_tape.cpp


def test_tape_layout():
    data = tape_bytes(make_session())
    assert data[:4] == b"SNTP"
    version, warmup, renders_before, fields = struct.unpack_from("<IiII", data, 4)
    assert (version, warmup, renders_before, fields) == (port_tape.TAPE_VERSION, 628, 0, 2)
    header = 4 + 16 + fields * 8 + 4
    record = RECORD.unpack_from(data, header)
    keys = record[1]
    assert keys[1 >> 3] & (1 << 1) and keys[0xc8 >> 3] & (1 << (0xc8 & 7))
    assert record[3] == b"\x11" * port_tape.SLOT_BYTES
    assert record[-1] == 1  # one render after the tick
    assert len(data) == header + RECORD.size


def test_compare_exact_and_ulp_divergence():
    session = make_session()
    assert compare(session, states(42, 7, 11, 5.249268054962158)).matches
    result = compare(session, states(42, 7, 11, 5.249268531799316))
    assert result.divergent_ticks == 1
    assert set(result.first.differences) == {"z"}
    assert 0 < result.max_error["z"] < 1e-6
    assert not compare(session, states(1, 7, 11, 5.249268054962158)).startup_rng_matches
    assert "frontend_state" in compare(session, states(42, 7, 12, 5.249268054962158)).first.differences
