from pathlib import Path

from snail.recon import sha256_bytes
from snail.reflexive import decrypt_reflexive_wrapper_config, unwrap_reflexive_executable


ARTIFACTS_DIR = Path(__file__).resolve().parents[1] / "artifacts/bin"
UNWRAPPED_SHA256 = "d365acf3db5335dded4dfd944e876ee2f23156595503693e0bf1baee1c8c83e5"


def test_decrypt_reflexive_wrapper_config_extracts_expected_fields() -> None:
    config_text = decrypt_reflexive_wrapper_config(
        ARTIFACTS_DIR / "SnailMail.RWG",
        ARTIFACTS_DIR / "ReflexiveArcade/RAW_002.wdt",
    )

    assert "Application Name=Snail Mail" in config_text
    assert "Application ID=195" in config_text
    assert "Game Needs Short Fixed Encryption=1" not in config_text


def test_unwrap_reflexive_executable_matches_known_unwrapped_image() -> None:
    decrypted = unwrap_reflexive_executable(
        ARTIFACTS_DIR / "SnailMail.RWG",
        ARTIFACTS_DIR / "ReflexiveArcade/RAW_002.wdt",
    )

    assert len(decrypted) == 741376
    assert sha256_bytes(decrypted) == UNWRAPPED_SHA256
