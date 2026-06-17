# queue_frontend_widget_flag_after_delay @ 0x403f60

Arms the border-manager delayed-widget flag lane. If the target widget carries
the front-end fade bit, it starts the shared fade object at `g_game_base+0x24`,
then stores the widget, active byte, zero progress, fixed `1/12` progress step,
and queued flag mask.
