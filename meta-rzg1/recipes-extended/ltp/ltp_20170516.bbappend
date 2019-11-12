FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://enlarge-max-file-path-size.patch \
    file://0002-workaround-to-reduce-the-maximum-latency-for-pkill_thread.patch \
    file://0003-prio-preempt-set-affinity-the-CPUs-core-for-each.patch \
"

SRC_URI_append_iwg22m += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load.patch \
    file://0004-async_handler-increase-pass-criterial-and-apply-warn.patch \
"

SRC_URI_append_iwg23s += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load.patch \
    file://0004-async_handler-increase-pass-criterial-and-apply-warn.patch \
"
