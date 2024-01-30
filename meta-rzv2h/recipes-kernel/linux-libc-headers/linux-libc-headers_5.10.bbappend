BRANCH = "${@oe.utils.conditional("IS_RT_BSP", "1", "rz-5.10-cip17-rt7", "rz-5.10-cip17",d)}"
SRCREV = "${@oe.utils.conditional("IS_RT_BSP", "1", "0f6cb6312a1a6f22fba03705c1b9816b7d27cf5b", "13dea4598e61893e75eae1c1887fa51ea6b22a07",d)}"
