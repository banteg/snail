for git, use conventional commits style

When running anything Python-related, prefer `uv`:
- run scripts: `uv run script.py` (or `uv run script_name` if it's an entrypoint)
- run tests: `uv run pytest`
- run tools: `uv run ruff`, `uv run ty`
- add/remove deps: `uv add`, `uv remove`

When using `gh`:
- PR title must be in the form of a conventional commit
- When asked to merge, use `gh pr merge --squash <pr>`
- To avoid escaping issues, write the PR description to a file and use:
  - `gh pr create --body-file <file>`
  - `gh pr edit --body-file <file>`
