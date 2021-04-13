#Revision for qt5.6.3
# Note that this package is not officially released with Qt 5.6
# This revision is just a buildable version with Qt 5.6.3

PV = "git${SRCPV}"
SRCREV = "0c623fab420102c54fa533da3b8ca774290d6d13"

# Not support openssl 1.1 yet
PACKAGECONFIG_remove = "openssl"
