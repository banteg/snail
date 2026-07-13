# initialize_parcel_set_bucket_pool_thunk

CRT table entry `0x4a1058` points to this one-instruction thunk at `0x443860`,
which tail-jumps over 11 alignment nops to the already recovered parcel-set
bucket constructor. The source-level tail call matches the native 1/1
instruction exactly, with its single masked target resolved.
