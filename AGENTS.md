for git, use conventional commits style

When running anything Python-related, prefer `uv`:
- run scripts: `uv run script.py` (or `uv run script_name` if it's an entrypoint)
- run tests: `uv run pytest`
- run tools: `uv run ruff`, `uv run ty`
- add/remove deps: `uv add`, `uv remove`

When doing version control work in this repo, prefer `jj` over `git`. Use the repo-local `jj` skill for status, diff, log, change descriptions, splitting or squashing work, bookmark management, and Git remote sync. Fall back to `git` only when a tool explicitly requires it.

When using `gh`:
- PR title must be in the form of a conventional commit
- When asked to merge, use `gh pr merge --squash <pr>`
- To avoid escaping issues, write the PR description to a file and use:
  - `gh pr create --body-file <file>`
  - `gh pr edit --body-file <file>`

## Skills
### Available skills
- jj: Use Jujutsu (`jj`) for version control in this repo. Prefer it over `git` for status, diff, log, change descriptions, splitting or squashing work, bookmarks, undo, and Git remote sync. Fall back to `git` only for GitHub integration or when `jj` cannot express the needed operation. (file: /Users/banteg/dev/banteg/snail-mail/.codex/skills/jj/SKILL.md)

### How to use skills
- Trigger rules: If the task involves version control in this repo, use the `jj` skill.
- Missing or blocked: If `jj` is unavailable or a workflow truly needs Git-only behavior, say so briefly and fall back to `git`.
- Context hygiene: Read the skill body first and only load extra skill files if they are actually needed.
