FILESEXTRAPATHS_prepend_rzg1 := '${THISDIR}/${PN}:'

SRC_URI += " \
			file://0001-gst1122-v4l2src-Add-NV16-color-format-support.patch \
			file://0002-gst1122-v4l2src-support-v4l2src-for-rcar.patch \
			file://0003-gst1122-v4l2bufferpool-Associate-a-V4L2-buffer-with-a.patch \
			file://0004-gst1122-v4l2src-v4l2bufferpool-Keep-the-information.patch \
			file://0005-gst1122-v4l2bufferpool-Change-the-buffer-number-to-be.patch \
			file://0006-gst1122-Add-the-Copyright-year.patch \
			file://0007-gst1122-v4l2src-Support-crop-function.patch \
			file://0008-gst1122-v4l2src-Update-feature-for-crop-function.patch \
		   "
