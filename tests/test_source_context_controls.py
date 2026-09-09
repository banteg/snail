"""Context promotions must preserve exact peers and each proof dimension."""

import copy
import runpy
from pathlib import Path

import pytest

TOOL = Path(__file__).resolve().parents[1] / "tools/match/probe_translation_unit_context.py"
assert_nonregression = runpy.run_path(str(TOOL))["assert_member_nonregression"]


def partial():
    return {
        "function": "loader", "state": "wip", "match_ratio": 0.88,
        "candidate_instructions": 942, "target_instructions": 926,
        "prefix_instructions": 20,
        "references": {"ok": 183, "unresolved": 0, "mismatch": 0, "unaudited": 2},
    }


def test_partial_gain_preserves_prior_evidence():
    baseline = partial()
    candidate = copy.deepcopy(baseline)
    candidate.update(match_ratio=0.89, candidate_instructions=931)
    candidate["references"]["unaudited"] = 0
    assert_nonregression(baseline, candidate)


@pytest.mark.parametrize(
    ("field", "value"),
    [("prefix_instructions", 19), ("candidate_instructions", 945)],
)
def test_higher_score_does_not_pay_for_instruction_regression(field, value):
    baseline = partial()
    candidate = copy.deepcopy(baseline)
    candidate.update(match_ratio=0.99)
    candidate[field] = value
    with pytest.raises(ValueError, match="regressed"):
        assert_nonregression(baseline, candidate)


@pytest.mark.parametrize(("field", "value"), [("ok", 182), ("mismatch", 1), ("unaudited", 3)])
def test_higher_score_does_not_pay_for_reference_regression(field, value):
    baseline = partial()
    candidate = copy.deepcopy(baseline)
    candidate.update(match_ratio=0.99)
    candidate["references"][field] = value
    with pytest.raises(ValueError, match="references regressed"):
        assert_nonregression(baseline, candidate)


def test_exact_peer_cannot_become_partial():
    baseline = partial()
    baseline.update(state="match", match_ratio=1.0, candidate_instructions=926, prefix_instructions=926)
    baseline["references"]["unaudited"] = 0
    candidate = copy.deepcopy(baseline)
    candidate["state"] = "wip"
    with pytest.raises(ValueError, match="exact member regressed"):
        assert_nonregression(baseline, candidate)
