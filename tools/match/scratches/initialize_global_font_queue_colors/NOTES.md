# initialize_global_font_queue_colors @ 0x449c50

Startup constructs exactly 1024 `FontQueueEntry::color` subobjects. The first
receiver is `g_font_queue + 0x6c`, each receiver advances by the exact
`sizeof(FontQueueEntry) == 0x84` stride, and every call targets the folded
trivial constructor at `0x44db50`. This proves the queue capacity and member
ownership independently of queue consumers.
