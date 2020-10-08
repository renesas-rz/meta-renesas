# Avoid error in update-alternatives in rootfs task
#     update-alternatives: Error: cannot register alternative readlink to /usr/bin/readlink since it is already registered to /bin/readlink
bindir_progs_remove = "readlink"
