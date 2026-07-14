// kill_border @ 0x403360 (thiscall-shaped helper, ret 0x4)

#include "border_manager.h"

// Keep the native fallthrough return while blocking VC6's final
// self-tail-recursion.
#pragma warning(disable:4716)

int BorderManager::kill_border(FrontendWidget* border)
{
    int result;
    if (border != 0) {
        int flags = border->widget_flags;
        if (flags != 0) {
            if ((flags & FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE) == 0) {
                flags = (flags & 0xffffff01) | FRONTEND_WIDGET_FLAG_KILL_PENDING;
                border->widget_flags = flags;
                if ((flags & 0x100000) != 0) {
                    kill_border(border->child_widget_0);
                    kill_border(border->child_widget_1);
                    result = kill_border(border->child_widget_2);
                }
            }
        }
    }
}
