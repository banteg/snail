// kill_border @ 0x403360 (thiscall-shaped helper, ret 0x4)

#include "border_manager.h"

int BorderManager::kill_border(FrontendWidget* border)
{
    int result;
    if (border != 0) {
        int flags = border->widget_flags;
        if (flags != 0) {
            if ((flags & 0x400) == 0) {
                flags = (flags & 0xffffff01) | 0x200;
                border->widget_flags = flags;
                if ((flags & 0x100000) != 0) {
                    kill_border(border->child_widget_0);
                    kill_border(border->child_widget_1);
                    kill_border(border->child_widget_2);
                }
            }
        }
    }
    return result;
}
