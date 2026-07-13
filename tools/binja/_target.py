from __future__ import annotations


# Repo-specific scripts must not silently follow another project's focused
# Binary Ninja tab. Callers can still request ``--target active`` explicitly.
DEFAULT_TARGET = "SnailMail_unwrapped.exe.bndb"
