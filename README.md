# meta-renesas

This is a Yocto build layer(version:scarthgap) that provides support for the RZ/G3E 64bit Arm-based MPU from Renesas Electronics.
This layer was used for making the image which was written to the flash memory on the RZ/G3E SMARC EVK.
You can reproduce the image using the following instructions.
All source code of the OSS necessary for building the image is automatically downloaded when building by bitbake command. Also you can downloaded the same source code from the following URL:

https://www.renesas.com/document/swo/open-source-package-rzg3e-bsp-v100-rc1osspkgrzg3eevk7z

For details about the license or copyright information of the OSS, please refer to the source code itself and documentation texts included in the source code archive.
Note that this layer will not be updated. If you find any issues on this layer, please see another branch which is being maintained.

## Dependencies

This layer depends on:

    poky:
        URL: https://git.yoctoproject.org/poky
        Layers: meta, meta-poky, meta-yocto-bsp
        Branch: scarthgap
        Revision: dce4163d42f7036ea216b52b9135968d51bec4c1
        (tag: scarthgap-5.0.5) 

    meta-arm:
        URL: https://git.yoctoproject.org/meta-arm
        Layers: meta-arm, meta-arm-toolchain
        Branch: scarthgap
        Revision: 950a4afce46a359def2958bd9ae33fc08ff9bb0d
        (tag: yocto-5.0.1)

    meta-openembedded:
        URL: https://git.openembedded.org/meta-openembedded
        Layers: meta-oe, meta-python, meta-multimedia
        Branch: scarthgap
        Revision: 1235dd4ed4a57e67683c045ad76b6a0f9e896b45

## Build Instructions

Assume that $WORK is the current working directory.
The following instructions require a Poky installation (or equivalent).

Below git configuration is required:
```bash
    $ git config --global user.email "you@example.com"
    $ git config --global user.name "Your Name"
```

You can download all Yocto related public source to prepare the build environment as below.
```bash
    $ git clone https://git.yoctoproject.org/poky
    $ cd poky
    $ git checkout dce4163d42f7036ea216b52b9135968d51bec4c1
    $ cd ..
    $
    $ git clone https://git.yoctoproject.org/meta-arm
    $ cd meta-arm
    $ git checkout 950a4afce46a359def2958bd9ae33fc08ff9bb0d
    $ cd ..
    $
    $ git clone https://git.openembedded.org/meta-openembedded
    $ cd meta-openembedded
    $ git checkout 1235dd4ed4a57e67683c045ad76b6a0f9e896b45
    $ cd ..
    $
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout f308430e671c23b3769e153f74397fb5647c99ec
    $ cd ..
```

** Build procedure:**
- Initialize a build using the 'oe-init-build-env' script in Poky and point TEMPLATECONF to platform conf path. e.g.:
   ```bash
   $ TEMPLATECONF=$PWD/meta-renesas/meta-rz-boards/conf/templates/rz-conf/ source poky/oe-init-build-env build
   ```

- Build the target file system image using bitbake:
   ```bash
   $ MACHINE=smarc-rzg3e bitbake core-image-minimal
   ```

After completing the images for the target machine will be available in the output
directory _'tmp/deploy/images/\<supported board name\>'_.

Images generated:
* Image (generic Linux Kernel binary image file)
* DTB for target machine
* core-image-\<target\>-\<machine name\>.tar.bz2 (rootfs tar+bzip2)
* core-image-\<target\>-\<machine name\>.ext4  (rootfs ext4 format)
* core-image-\<target\>-\<machine name\>.wic.gz  (rootfs wic gz format)
* core-image-\<target\>-\<machine name\>.wic.bmap  (rootfs wic block map format)
