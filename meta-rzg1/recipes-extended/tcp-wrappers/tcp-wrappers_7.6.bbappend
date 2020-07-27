#Fix build break with glibc 2.28 (not provide libnsl anymore)
EXTRA_OEMAKE_remove = "'LIBS=-lnsl'"
