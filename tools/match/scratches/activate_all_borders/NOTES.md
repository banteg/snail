# `activate_all_borders` notes

## 2026-07-16 disabled-state restoration

Windows clears `DISABLED` only when bit `0x80000000` is absent, then clears
that high bit unconditionally. Android supplies the missing producer side:
`cRBorderManager::DeActivateBorders()` and its four `DeActivateOtherBorders()`
overloads set the high bit only for widgets that were disabled before the
manager temporarily disabled the batch. The exact lifecycle role is named
`FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION`; no return-value or
register-shaping source was introduced.
