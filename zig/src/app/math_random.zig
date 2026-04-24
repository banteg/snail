pub fn nextInt15(random_state: *u32) u32 {
    random_state.* = (random_state.* *% 0x343fd) +% 0x269ec3;
    return (random_state.* >> 16) & 0x7fff;
}
