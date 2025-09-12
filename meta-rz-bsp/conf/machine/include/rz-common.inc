IMAGE_FSTYPES:append = " tar.gz tar.bz2 ext4 wic.gz wic.bmap"
WKS_FILE ?= "rz-image-bootpart-mmc.wks"
WICVARS:append = " FIP_WIC_OFFSET"
