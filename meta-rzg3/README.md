# meta-renesas

This is a Yocto build layer(version:dunfell) that provides support for the RZ/G3S of 64bit Arm-based MPU from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: RZG3S Development Evaluation Kit / MPU: R9A08G045 (RZ/G3S)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies

This layer depends on:

    URI: git://git.yoctoproject.org/poky
    layers: meta, meta-poky, meta-yocto-bsp
    branch: dunfell
    revision: aa0073041806c9f417a33b0b7f747d2a86289eda
    (tag: dunfell-23.0.21)

    URI: git://git.openembedded.org/meta-openembedded
    layers: meta-oe, meta-python, meta-multimedia
    branch: dunfell
    revision: 7952135f650b4a754e2255f5aa03973a32344123

    URI: https://git.yoctoproject.org/meta-gplv2
    layers: meta-gplv2
    branch: dunfell
    revision: 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac

    (Optional: Docker)
    URI: https://git.yoctoproject.org/git/meta-virtualization
    layers: meta-virtualization
    branch: dunfell
    revision: a63a54df3170fed387f810f23cdc2f483ad587df

## Build Instructions

Assume that $WORK is the current working directory.
The following instructions require a Poky installation (or equivalent).

Below git configuration is required:
```bash
    $ git config --global user.email "you@example.com"
    $ git config --global user.name "Your Name"
```

You can get all Yocto build environment from Renesas, or download all Yocto related public source to prepare the build environment as below.
```bash
    $ git clone https://git.yoctoproject.org/git/poky
    $ cd poky
    $ git checkout dunfell-23.0.21
    $ cd ..
    $
    $ git clone https://github.com/openembedded/meta-openembedded
    $ cd meta-openembedded
    $ git checkout 7952135f650b4a754e2255f5aa03973a32344123
    $ cd ..
    $
    $ git clone https://git.yoctoproject.org/git/meta-gplv2
    $ cd meta-gplv2
    $ git checkout 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac
    $ cd ..
    $
    $ tar xvf meta-renesas-g3s.tar.gz -C .
    $
    $ git clone https://git.yoctoproject.org/git/meta-virtualization
    $ cd meta-virtualization
    $ git checkout a63a54df3170fed387f810f23cdc2f483ad587df
    $ ..
```
Initialize a build using the 'oe-init-build-env' script in Poky and point TEMPLATECONF to platform conf path. e.g.:
```bash
    $ TEMPLATECONF=${PWD}/meta-renesas/meta-<platform>/docs/template/conf/ \
      source poky/oe-init-build-env
```

To build Docker (optional), add necessary layers:
```bash
    $ bitbake-layers add-layer ../meta-openembedded/meta-filesystems
    $ bitbake-layers add-layer ../meta-openembedded/meta-networking
    $ bitbake-layers add-layer ../meta-virtualization
```
To include bootloaders and FlashWriter to image, add necessary layers:
```bash
    $ bitbake-layers add-layer ../meta-rz-features/meta-rz-bootloaders
```

Build the target file system image using bitbake:
```bash
    $ $ MACHINE=<board> bitbake core-image-<target>
```
\<platform\> and \<board\> can be selected in below table:

|Renesas MPU| platform |        board         |
|:---------:|:--------:|:--------------------:|
|RZ/G3S     |rzg3      |       rzg3s-dev      |

\<target\> for 2 built types:
* RZ/G3S: minimal, bsp

After completing the images for the target machine will be available in the output
directory _'tmp/deploy/images/\<supported board name\>'_.

Images generated:
* Image (generic Linux Kernel binary image file)
* DTB for target machine
* core-image-\<target\>-\<machine name\>.tar.bz2 (rootfs tar+bzip2)
* core-image-\<target\>-\<machine name\>.ext4  (rootfs ext4 format)
* core-image-\<target\>-\<machine name\>.wic.gz (partitioned image file)
* core-image-\<target\>-\<machine name\>.wic.bmap (bmapfile for bmaptool)

## Build Instructions for SDK

Use bitbake -c populate_sdk for generating the toolchain SDK:
For 64-bit target SDK (aarch64):
```bash
    $ bitbake core-image-minimal -c populate_sdk
```
The SDK can be found in the output directory _'tmp/deploy/sdk'_

    poky-glibc-x86_64-core-image-minimal-aarch64-toolchain-x.x.sh

Usage of toolchain SDK: Install the SDK to the default: _/opt/poky/x.x_
For 64-bit target SDK:
```bash
    $ sh poky-glibc-x86_64-core-image-moinimal-aarch64-toolchain-x.x.sh
```
For 64-bit application use environment script in _/opt/poky/x.x_
```bash
    $ source /opt/poky/x.x/environment-setup-aarch64-poky-linux
```

## Build configs

It is possible to change some build configs as below:
* GPLv3: choose to not allow, or allow, GPLv3 packages
  * **Non-GPLv3 (default):** not allow GPLv3 license. All recipes that has GPLv3 license will be downgrade to older version that has alternative license (done by meta-gplv2). In this setting customer can ignore the risk of strict license GPLv3
  ```
  INCOMPATIBLE_LICENSE = "GPLv3 GPLv3+"
  ```
  * Allow-GPLv3: allow GPLv3 license. If user is fine with strict copy-left license GPLv3, can use this setting to get newer software version.
  ```
  #INCOMPATIBLE_LICENSE = "GPLv3 GPLv3+"
  ```
* CIP Core: choose the version of CIP Core to build with. CIP Core are software packages that are maintained for long term by CIP community. You can select by changing "CIP_MODE".
  * **Buster (default):** use as many packages from CIP Core Buster as possible.
  ```
  CIP_MODE = "Buster"
  ```
  * Bullseye: use as many packages from CIP Core Bullseye.
  ```
  CIP_MODE = "Bullseye"
  ```
  * None CIP Core: not use CIP Core at all, use all default version from Yocto 3.1 Dunfell
  ```
  CIP_MODE = "None" or unset CIP_MODE
  ```
