# initialize_voice_set @ 0x448df0

Initializes the VoiceSet-owned playlist and bite-index arrays. Both tracked
allocations now derive their four-byte stride from the destination `int`
members rather than shift literals. Matching remains exact at 33/33
instructions with all five operands clean.
