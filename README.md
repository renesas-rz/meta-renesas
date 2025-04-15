# meta-renesas

This is a Yocto build layer(version:scarthgap) that provides support for the RZ/G2 Group of 64bit Arm-based MPUs from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: RZG2L SMARC Evaluation Kit / MPU: R9A07G044L (RZ/G2L)
- Board: RZG2LC SMARC Evaluation Kit / MPU: R9A07G044C (RZ/G2LC)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies

This layer depends on:

    poky:
    URL: https://git.yoctoproject.org/poky
    branch: scarthgap
    revision: dce4163d42f7036ea216b52b9135968d51bec4c1
    (tag: scarthgap-5.0.8)

    meta-arm:
    URL: https://git.yoctoproject.org/meta-arm
    Branch: scarthgap
    Revision: 950a4afce46a359def2958bd9ae33fc08ff9bb0d
    (tag: yocto-5.0.1)

    meta-openembedded:
    URL: https://github.com/openembedded/meta-openembedded.git
    branch: scarthgap
    revision: 67ad83dd7c2485dae0c90eac345007af6195b84d

    meta-virtualization (for Docker):
    URL: https://git.yoctoproject.org/git/meta-virtualization
    branch: scarthgap
    revision: 9287a355b338361e42027ce371444111a791d64f

## Build Instructions

Assume that $WORK is the current working directory.
The following instructions require a Poky installation (or equivalent).

Below git configuration is required:
```bash
    $ git config --global user.email "you@example.com"
    $ git config --global user.name "Your Name"
```

Download proprietary graphics and multimedia drivers from Renesas.
To download Multimedia and Graphics library and related Linux drivers, please use the following link:

    English: https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rz-mpus/rzg-linux-platform/rzg-marketplace/verified-linux-package/rzg-verified-linux-package
    Japanese: https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/rz-mpus/rzg-linux-platform/rzg-marketplace/verified-linux-package/rzg-verified-linux-package

Please choose correct packages that matches with your MPU.
Graphic drivers are required for Wayland. Multimedia drivers are optional.
After downloading the proprietary package, please decompress them then put meta-rz-features folder at $WORK.

Below is the combination of Tag with BSP released versions:

**1. RZ/G2{L,LC}:**

|VLP Version|Tag|
|:---------:|:---------:|
|4.0.0|4.0.0|

(\*1) Please note that the naming rule of version is changed from the release.
v1.5.0 is newer version of v1.4.

You can get all Yocto build environment from Renesas, or download all Yocto related public source to prepare the build environment as below.
```bash
    $ git clone https://git.yoctoproject.org/poky
    $ cd poky
    $ git checkout dc4827b3660bc1a03a2bc3b0672615b50e9137ff
    $ cd ..
    $
    $ git clone https://git.yoctoproject.org/meta-arm
    $ cd meta-arm
    $ git checkout 950a4afce46a359def2958bd9ae33fc08ff9bb0d
    $ cd ..
    $
    $ git clone https://github.com/openembedded/meta-openembedded.git
    $ cd meta-openembedded
    $ git checkout 67ad83dd7c2485dae0c90eac345007af6195b84d
    $ cd ..
    $
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout <tag>
    $ cd ..
    $
    $ git clone  https://git.yoctoproject.org/git/meta-virtualization
    $ cd meta-virtualization
    $ git checkout 9287a355b338361e42027ce371444111a791d64f
    $ cd ..
```
\<tag\> can be selected in any tags of meta-renesas.
Now the latest version is **VLP-4.0.x** or **VLP-4.0.x-updatey** if any new updates are applied.

Currently, there are 2 types of build procedure supported in below description:

**1. New build procedure (Recommended):**
- Initialize a build using the 'oe-init-build-env' script in Poky and point TEMPLATECONF to platform conf path. e.g.:
   ```bash
   $ TEMPLATECONF=$PWD/meta-renesas/meta-rz-distro/conf/templates/rz-conf/* source poky/oe-init-build-env build
   ```
- To build optional features (Docker, Codec or Graphics), add necessary layers:
   ```bash
   # For Docker
   $ bitbake-layers add-layer ../meta-openembedded/meta-networking
   $ bitbake-layers add-layer ../meta-openembedded/meta-filesystems
   $ bitbake-layers add-layer ../meta-virtualization

   # For Codec
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs

   # For Graphics
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics

   ```
- Build the target file system image using bitbake:
   ```bash
   $ MACHINE=<board> bitbake core-image-<target>
   ```
\<platform\> and \<board\> can be selected in below table:

|Renesas MPU| platform |        board           |
|:---------:|:--------:|:----------------------:|
|RZ/G2L     |rzg2l     |smarc-rzg2l |
|RZ/G2LC    |rzg2l     |smarc-rzg2lc |

After completing the images for the target machine will be available in the output
directory _'tmp/deploy/images/\<supported board name\>'_.

Images generated:
* Image (generic Linux Kernel binary image file)
* DTB for target machine
* core-image-\<target\>-\<machine name\>.tar.bz2 (rootfs tar+bzip2)
* core-image-\<target\>-\<machine name\>.ext4  (rootfs ext4 format)
* core-image-\<target\>-\<machine name\>.wic.gz  (rootfs wic gz format)
* core-image-\<target\>-\<machine name\>.wic.bmap  (rootfs wic block map format)

## Build Instructions for SDK

Use bitbake -c populate_sdk for generating the toolchain SDK:
For 64-bit target SDK (aarch64):
```bash
    $ bitbake core-image-weston -c populate_sdk
```
The SDK can be found in the output directory _'tmp/deploy/sdk'_

    rz-vlp-glibc-x86_64-core-image-weston-cortexa55-x.x-toolchain-x.x.sh

Usage of toolchain SDK: Install the SDK to the default: _/opt/poky/x.x_
For 64-bit target SDK:
```bash
    $ sh rz-vlp-glibc-x86_64-core-image-weston-cortexa55-x.x-toolchain-x.x.sh
```
For 64-bit application use environment script in _/opt/poky/x.x_
```bash
    $ source /opt/poky/x.x/environment-setup-cortexa55-poky-linux
```

## Build configs
It is possible to change some build configs as below:
* Realtime Linux: choose realtime characteristic of Linux kernel to build with. You can enable this feature by setting "linux-renesas-rt" in local.conf:
  ```
  PREFERRED_PROVIDER_virtual/kernel = "linux-renesas-rt"
  ```

* Docker: choose Docker characteristic to build with. You can enable this feature by comment out below setting in local.conf:
  ```
  DISTRO_FEATURES:append = " virtualization docker"
