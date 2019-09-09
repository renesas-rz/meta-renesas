FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://enlarge-max-file-path-size.patch \
    file://0002-workaround-to-reduce-the-maximum-latency-for-pkill_thread.patch \
"

SRC_URI_append_iwg22m += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load.patch \
"

SRC_URI_append_iwg23s += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load.patch \
"