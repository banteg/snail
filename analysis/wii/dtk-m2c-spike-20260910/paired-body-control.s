.text
.global paired_load_probe
paired_load_probe:
    psq_l f1, 0(r3), 0, 0
    stfs f1, 0(r4)
    blr
.global paired_store_probe
paired_store_probe:
    psq_st f1, 0(r3), 0, 0
    blr
