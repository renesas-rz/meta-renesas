# meta-renesas

This is a Yocto build layer(version:dunfell) that provides support for the RZ/V2N of 64bit Arm-based MPU from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: RZV2N Development Evaluation Kit / MPU: R9A09G056 (RZ/V2N)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies

This layer depends on:

    URI: git://git.yoctoproject.org/poky
    layers: meta, meta-poky, meta-yocto-bsp
    branch: dunfell
    revision: a9e3cc3b9eab7a83c715bb8440454e8fea852c2a
    (tag: dunfell-23.0.31)
    For Docker build:
    cherry-pick commit eb0915c699fbe86488de172d529f073a30d05b6a

    URI: git://git.openembedded.org/meta-openembedded
    layers: meta-oe, meta-python, meta-multimedia
    branch: dunfell
    revision: daa4619fe3fbf8c28f342c4a7163a84a330f7653

    URI: https://git.yoctoproject.org/meta-gplv2
    layers: meta-gplv2
    branch: dunfell
    revision: 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac

    (Optional: Docker)
    URI: https://git.yoctoproject.org/git/meta-virtualization
    layers: meta-virtualization
    branch: dunfell
    revision: 521459bf588435e847d981657485bae8d6f003b5

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
    $ git checkout dunfell-23.0.31
    $ git cherry-pick eb0915c699fbe86488de172d529f073a30d05b6a
    $ cd ..
    $
    $ git clone https://github.com/openembedded/meta-openembedded
    $ cd meta-openembedded
    $ git checkout daa4619fe3fbf8c28f342c4a7163a84a330f7653
    $ cd ..
    $
    $ git clone https://git.yoctoproject.org/git/meta-gplv2
    $ cd meta-gplv2
    $ git checkout 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac
    $ cd ..
    $
    $ tar xvf meta-renesas-v2n.tar.gz -C .
    $
    $ git clone https://git.yoctoproject.org/git/meta-virtualization
    $ cd meta-virtualization
    $ git checkout 521459bf588435e847d981657485bae8d6f003b5
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
To build for Weston with Graphics Library, add necessary layers:
```bash
    $ bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics
```

Build the target file system image using bitbake:
```bash
    $ MACHINE=<board> bitbake core-image-<target>
```

\<platform\> and \<board\> can be selected in below table:

|Renesas MPU| platform |  board  |
|:---------:|:--------:|:-------:|
|RZ/V2N     |rzv2n     |rzv2n-dev, rzv2n-evk|

\<target\> for 3 built types:
* RZ/V2N: minimal, bsp, weston

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
