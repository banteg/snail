#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys


REPO_ROOT = Path(__file__).resolve().parents[1]
SRC_ROOT = REPO_ROOT / "src"
if str(SRC_ROOT) not in sys.path:
    sys.path.insert(0, str(SRC_ROOT))

from snail.decompile_health import evaluate_decompile_health_checks, load_decompile_health_checks  # noqa: E402


DEFAULT_CONFIG_PATH = REPO_ROOT / "analysis/decompile/health_checks.json"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run tracked decompile hotspot health checks against the repo snapshot."
    )
    parser.add_argument(
        "--config",
        type=Path,
        default=DEFAULT_CONFIG_PATH,
        help="Path to the decompile health-check config.",
    )
    parser.add_argument(
        "--strict",
        action="store_true",
        help="Exit nonzero when any configured health check fails.",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    config_path = args.config.resolve()
    checks = load_decompile_health_checks(config_path)
    summary = {
        "config": str(config_path.relative_to(REPO_ROOT)),
        **evaluate_decompile_health_checks(repo_root=REPO_ROOT, checks=checks),
    }
    print(json.dumps(summary, indent=2))
    if args.strict and not summary["passed"]:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
