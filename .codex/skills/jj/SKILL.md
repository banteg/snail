---
name: "jj"
description: "Use Jujutsu (`jj`) for version control in this repository. Prefer it over `git` for status, diff, log, change descriptions, splitting or squashing work, bookmark management, undo, and Git remote sync."
---

# jj

Use `jj` instead of `git` for version control work in this repo.

## Defaults

- Run `jj` from the repository root.
- Start with `jj status` so you can see the working-copy change and its parent.
- Prefer `jj diff`, `jj log`, and `jj show` for inspection.
- Use conventional-commit descriptions when naming changes, for example `feat: add score importer`.
- Fall back to `git` only when another tool requires Git-specific behavior or `jj` lacks the needed command.

## Common tasks

- Inspect state: `jj status`, `jj diff`, `jj show`, `jj log`
- Describe the current change: `jj describe -m "fix: handle empty score file"`
- Create a new child change: `jj new`
- Split work into a new change: `jj split`
- Fold changes together: `jj squash`
- Move a change: `jj rebase -s <rev> -d <rev>`
- Restore paths from a parent or revision: `jj restore path/to/file`
- Undo the last repo operation: `jj undo`
- Abandon a change: `jj abandon <rev>`
- Manage bookmarks: `jj bookmark list`, `jj bookmark set <name> -r <rev>`, `jj bookmark delete <name>`
- Sync with Git remotes: `jj git fetch`, `jj git push --bookmark <name>`

## Git interop

- This repo is colocated with Git. Prefer `jj` for local history editing and `gh` for GitHub operations.
- Avoid `git commit`, `git checkout`, and `git reset` unless the user explicitly asks for Git or another tool requires those commands.
- When a workflow needs a branch-like ref, use a bookmark and keep its name aligned with the branch or PR purpose.

## Reporting

- Translate `jj` terms when helpful: bookmarks are branch-like refs, and changes are mutable commits.
- Before running commands that rewrite history, say so explicitly.
