# Exact match

`update_tip_manager` matches exactly at 14/14 instructions and is the Windows
`cRTipManager::AI()` member. It walks the manager's three inline Tips and calls
the exact `cRTip::AI()` body for every active entry.
