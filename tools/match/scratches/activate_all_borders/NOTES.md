# `activate_all_borders` notes

## 2026-07-16 disabled-state restoration

Windows clears `DISABLED` only when bit `0x80000000` is absent, then clears
that high bit unconditionally. Android supplies the missing producer side:
`cRBorderManager::DeActivateBorders()` and its four `DeActivateOtherBorders()`
overloads set the high bit only for widgets that were disabled before the
manager temporarily disabled the batch. The exact lifecycle role is named
`FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION`; no return-value or
register-shaping source was introduced.

## 2026-07-26 authored manager owner

Android's exact-demangled `cRBorderManager::ActivateBorders()` body closes the
Windows receiver provenance. Both implementations walk 150 manager-owned
records, restore `DISABLED` only when
`DISABLED_BEFORE_DEACTIVATION` is clear, clear that saved-state bit
unconditionally, copy idle padding into both live lanes, and clear the hover
target.

Android reaches its border storage through a platform pointer and uses a
different record offset. Windows retains the exact inline `BorderRecord[150]`
layout at `BorderManager +0x684`. No mobile offset transfers, and the Windows
member remains 19/19 with no source-shaping concession.
