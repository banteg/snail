import copy
import hashlib
import json
import zipfile

import pytest

from snail import ports
from snail.cli import main


def test_binary_hash_applies_to_selected_archive_slice(tmp_path):
    with zipfile.ZipFile(tmp_path / "port.zip", "w") as archive:
        archive.writestr("app/executable", b"prefixTARGETsuffix")
    build = {
        "id": "test-build",
        "binary": {
            "path": "port.zip",
            "archive_member": "app/executable",
            "offset": 6,
            "size": 6,
            "sha256": hashlib.sha256(b"TARGET").hexdigest(),
        },
    }
    assert ports.read_build_binary(build, tmp_path) == b"TARGET"
    build["binary"]["offset"] = 5
    with pytest.raises(ValueError, match="SHA-256 mismatch"):
        ports.read_build_binary(build, tmp_path)
    build["binary"]["size"] = 100
    with pytest.raises(ValueError, match="outside the source"):
        ports.read_build_binary(build, tmp_path)


def test_reference_paths_cannot_escape_repository(tmp_path):
    with pytest.raises(ValueError, match="escapes repository"):
        ports.repo_path(tmp_path, "../outside")


def test_registry_has_one_primary_matching_target(tmp_path):
    registry = ports.load_builds()
    assert registry["primary_build"] == "windows-reflexive-x86"
    registry["builds"][1]["role"] = "primary"
    path = tmp_path / "builds.json"
    path.write_text(json.dumps(registry))
    with pytest.raises(ValueError, match="exactly one"):
        ports.load_builds(path)


def test_tracked_indexes_and_relationships_are_bound_to_builds():
    assert not ports.check_registry(
        ports.load_builds(),
        ports.read_json(ports.DEFAULT_RELATIONSHIPS),
        binaries=False,
    )


def test_name_transfer_does_not_inherit_body_verification():
    result = ports.function_leads(
        "extract_snail_local_hotspots",
        ports.load_builds(),
        ports.read_json(ports.DEFAULT_RELATIONSHIPS),
    )
    leads = {lead["build_id"]: lead for lead in result["leads"]}
    old = leads["ios-1.5-armv6"]
    new = leads["ios-1.9-armv6"]
    assert old["association"] == "curated-windows-correspondence"
    assert new["association"] == "same-symbol-only"
    assert new["body_parity"] == "not-reviewed-for-this-build"
    assert "decompile" not in new
    android = leads["android-armv7"]
    assert int(android["analysis_address"], 16) - int(android["address"], 16) == 0x10000
    assert android["address_space"] == "link-time-va"


def test_stale_index_cannot_supply_leads():
    registry = copy.deepcopy(ports.load_builds())
    registry["builds"][1]["binary"]["sha256"] = "0" * 64
    with pytest.raises(ValueError, match="stale symbol index"):
        ports.function_leads(
            "extract_snail_local_hotspots",
            registry,
            ports.read_json(ports.DEFAULT_RELATIONSHIPS),
        )


def test_unverified_fuzzy_candidates_are_not_cross_build_correspondences():
    result = ports.function_leads(
        "initialize_game_assets_and_world",
        ports.load_builds(),
        ports.read_json(ports.DEFAULT_RELATIONSHIPS),
    )
    assert result["leads"] == []


def test_cli_preserves_constructor_variants_and_wii_evidence(capsys):
    assert main(["match", "leads", "initialize_quaternion_from_matrix", "--json"]) == 0
    result = json.loads(capsys.readouterr().out)
    android = [lead for lead in result["leads"] if lead["build_id"] == "android-armv7"]
    assert len(android) == 2
    assert len({lead["mangled"] for lead in android}) == 2
    assert result["relationships"][0]["build_id"] == "wii-usa-ppc"
