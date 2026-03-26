from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path


@dataclass(frozen=True, slots=True)
class DecompileHealthCheck:
    name: str
    artifact: str
    required_substrings: tuple[str, ...]
    forbidden_substrings: tuple[str, ...]
    min_counts: dict[str, int]
    max_counts: dict[str, int]


def _load_string_list(raw: dict[str, object], key: str) -> tuple[str, ...]:
    value = raw.get(key, [])
    if not isinstance(value, list):
        raise ValueError(f"{key!r} must be a list")
    result: list[str] = []
    for index, item in enumerate(value):
        if not isinstance(item, str) or not item:
            raise ValueError(f"{key}[{index}] must be a non-empty string")
        result.append(item)
    return tuple(result)


def _load_int_dict(raw: dict[str, object], key: str) -> dict[str, int]:
    value = raw.get(key, {})
    if not isinstance(value, dict):
        raise ValueError(f"{key!r} must be an object")
    result: dict[str, int] = {}
    for token, count in value.items():
        if not isinstance(token, str) or not token:
            raise ValueError(f"{key} keys must be non-empty strings")
        if not isinstance(count, int) or count < 0:
            raise ValueError(f"{key}[{token!r}] must be a non-negative integer")
        result[token] = count
    return result


def load_decompile_health_checks(path: Path) -> tuple[DecompileHealthCheck, ...]:
    raw = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(raw, dict):
        raise ValueError("decompile health config must be a JSON object")
    raw_checks = raw.get("checks")
    if not isinstance(raw_checks, list) or not raw_checks:
        raise ValueError("decompile health config must contain a non-empty 'checks' list")

    checks: list[DecompileHealthCheck] = []
    for index, raw_check in enumerate(raw_checks):
        if not isinstance(raw_check, dict):
            raise ValueError(f"checks[{index}] must be an object")
        name = raw_check.get("name")
        artifact = raw_check.get("artifact")
        if not isinstance(name, str) or not name:
            raise ValueError(f"checks[{index}].name must be a non-empty string")
        if not isinstance(artifact, str) or not artifact:
            raise ValueError(f"checks[{index}].artifact must be a non-empty string")
        checks.append(
            DecompileHealthCheck(
                name=name,
                artifact=artifact,
                required_substrings=_load_string_list(raw_check, "required_substrings"),
                forbidden_substrings=_load_string_list(raw_check, "forbidden_substrings"),
                min_counts=_load_int_dict(raw_check, "min_counts"),
                max_counts=_load_int_dict(raw_check, "max_counts"),
            )
        )
    return tuple(checks)


def evaluate_decompile_health_checks(
    *,
    repo_root: Path,
    checks: tuple[DecompileHealthCheck, ...],
) -> dict[str, object]:
    check_results: list[dict[str, object]] = []
    failing = 0

    for check in checks:
        artifact_path = (repo_root / check.artifact).resolve()
        if not artifact_path.is_file():
            check_results.append(
                {
                    "name": check.name,
                    "artifact": check.artifact,
                    "exists": False,
                    "passed": False,
                    "failures": [f"missing artifact: {check.artifact}"],
                    "observed_counts": {},
                }
            )
            failing += 1
            continue

        text = artifact_path.read_text(encoding="utf-8")
        observed_tokens = {
            *check.required_substrings,
            *check.forbidden_substrings,
            *check.min_counts.keys(),
            *check.max_counts.keys(),
        }
        observed_counts = {token: text.count(token) for token in sorted(observed_tokens)}
        failures: list[str] = []

        for token in check.required_substrings:
            if observed_counts[token] == 0:
                failures.append(f"missing required substring: {token}")
        for token in check.forbidden_substrings:
            if observed_counts[token] != 0:
                failures.append(f"forbidden substring present: {token} ({observed_counts[token]})")
        for token, minimum in sorted(check.min_counts.items()):
            if observed_counts[token] < minimum:
                failures.append(f"count below minimum for {token}: {observed_counts[token]} < {minimum}")
        for token, maximum in sorted(check.max_counts.items()):
            if observed_counts[token] > maximum:
                failures.append(f"count above maximum for {token}: {observed_counts[token]} > {maximum}")

        passed = not failures
        if not passed:
            failing += 1
        check_results.append(
            {
                "name": check.name,
                "artifact": check.artifact,
                "exists": True,
                "passed": passed,
                "failures": failures,
                "observed_counts": observed_counts,
            }
        )

    return {
        "check_count": len(check_results),
        "failing_check_count": failing,
        "passed": failing == 0,
        "checks": check_results,
    }
