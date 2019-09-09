FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = " \
    file://enlarge-max-file-path-size.patch \
"

SRC_URI_append_iwg22m += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load \
"

SRC_URI_append_iwg23s += " \
    file://0001-Reconfig-LOOPS_MULTIPLIER-to-fix-issue-periodic_cpu_load \
"