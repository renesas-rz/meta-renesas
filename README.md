# meta-renesas

This is a Yocto build layer(version:dunfell) that provides support for the RZ/G1 Group of 32bit Arm-based MPUs, RZ/G2 Group of 64bit Arm-based MPUs and RZ/Five 64bit RISC-V based MPU from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: EK874 / MPU: R8A774C0 (RZ/G2E)
- Board: HIHOPE-RZG2M / MPU: R8A774A1 (RZ/G2M v1.3) and R8A774A3 (RZ/G2M v3.0)
- Board: HIHOPE-RZG2N / MPU: R8A774B1 (RZG2N)
- Board: HIHOPE-RZG2H / MPU: R8A774E1 (RZG2H)
- Board: RZG2L SMARC Evaluation Kit / MPU: R9A07G044L (RZ/G2L)
- Board: RZG2L Development Evaluation Kit / MPU: R9A07G044L (RZ/G2L)
- Board: RZG2LC SMARC Evaluation Kit / MPU: R9A07G044C (RZ/G2LC)
- Board: RZG2LC Development Evaluation Kit / MPU: R9A07G044C (RZ/G2L)
- Board: RZG2UL SMARC Evaluation Kit / MPU: R9A07G043U (RZ/G2UL)
- Board: RZG2UL Development Evaluation Kit / MPU: R9A07G043U (RZ/G2UL)
- Board: RZV2L SMARC Evaluation Kit / MPU: R9A07G054L (RZ/V2L)
- Board: RZV2L Development Evaluation Kit / MPU: R9A07G054L (RZ/V2L)
- Board: CSM Solution RZV2M Evaluation Board Kit / MPU: R9A09G011GBG (RZ/V2M)
- Board: Shimafuji Electric RZV2MA Evaluation Board Kit / MPU: R9A09G055MA3GBG (RZ/V2MA)
- Board: RZFive SMARC Evaluation Kit / MPU: R9A07G043F (RZ/Five)
- Board: RZFive SMARC Evaluation Kit / MPU: R9A07G043F (RZ/Five)
- Board: iWave RZ/G1H-PF Qseven Development Platform R2.1 / MPU: R8A7742 (RZ/G1H)
- Board: iWave RZ/G1M-PF Qseven Development Platform R2.0 / MPU: R8A7743 (RZ/G1M)
- Board: iWave RZ/G1N-PF Qseven Development Platform R3.4 / MPU: R8A7744 (RZ/G1N)
- Board: iWave RZ/G1E-PF SODIMM Development Platform R3.1 / MPU: R8A7745 (RZ/G1E)
- Board: iWave RZ/G1C-PF Pi SBC Development Platform R2.0 / MPU: R8A77470 (RZ/G1C)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies

This layer depends on:

    URI: git://git.yoctoproject.org/poky
    layers: meta, meta-poky, meta-yocto-bsp
    branch: dunfell
    revision: bab87089ad998afc980adb45c11ae356bc35a460
    (tag: dunfell-23.0.26)

    URI: git://git.openembedded.org/meta-openembedded
    layers: meta-oe, meta-python, meta-multimedia
    branch: dunfell
    revision: 6334241447e461f849035c47f071fa4a2125fee1
    
    URI: https://git.yoctoproject.org/meta-gplv2
    layers: meta-gplv2
    branch: dunfell
    revision: 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac

    core-image-qt: Optional (unsupported for RZ/V2M and RZ/V2MA)
    URI: https://github.com/meta-qt5/meta-qt5.git
    layers: meta-qt5
    revision: c1b0c9f546289b1592d7a895640de103723a0305

    Docker: Optional (unsupported for RZ/V2M and RZ/V2MA)
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

Download proprietary graphics and multimedia drivers from Renesas.
To download Multimedia and Graphics library and related Linux drivers, please use the following link:

    English: https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rz-mpus/rzg-linux-platform/rzg-marketplace/verified-linux-package/rzg-verified-linux-package
    Japanese: https://www.renesas.com/jp/ja/products/microcontrollers-microprocessors/rz-mpus/rzg-linux-platform/rzg-marketplace/verified-linux-package/rzg-verified-linux-package

Please choose correct packages that matches with your MPU.
Graphic drivers are required for Wayland. Multimedia drivers are optional.
After downloading the proprietary package, please decompress them then put meta-rz-features folder at $WORK.

Below is the combination of Codec/Graphics library with BSP released versions:

**1. RZ/G2{H,M,N,E}:**

|BSP Version|Codec Version|Graphics Version|
|:---------:|:-----------:|:--------------:|
|3.0.0 - 3.0.2|1.0|1.0|
|3.0.3|1.0.1|1.0.1|
|3.0.5|1.0.1|1.0.2|

**2. RZ/G2{L,LC,UL} and RZ/V2L:**

|BSP Version|Codec Version|Graphics Version|
|:---------:|:-----------:|:--------------:|
|3.0.0|0.58|1.2|
|3.0.1|1.0|1.3|
|3.0.2|1.0.1|1.4|
|3.0.3|1.1.0|1.0.5(\*1)|
|3.0.4|1.1.0|1.1.0(\*1)|
|3.0.5|1.1.0|1.1.0|
|3.0.5-update2|1.2.0|1.2.0|

(\*1) Please note that the naming rule of version is changed from the release.
v1.0.5 is newer version of v1.4.

You can get all Yocto build environment from Renesas, or download all Yocto related public source to prepare the build environment as below.
```bash
    $ git clone https://git.yoctoproject.org/git/poky
    $ cd poky
    $ git checkout dunfell-23.0.26
    $ cd ..
    $     
    $ git clone https://github.com/openembedded/meta-openembedded
    $ cd meta-openembedded
    $ git checkout 6334241447e461f849035c47f071fa4a2125fee1
    $ cd ..
    $    
    $ git clone https://git.yoctoproject.org/git/meta-gplv2
    $ cd meta-gplv2 
    $ git checkout 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac
    $ cd ..
    $
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout <tag>
    $ cd ..
    $
    $ git clone  https://github.com/meta-qt5/meta-qt5.git
    $ cd meta-qt5
    $ git checkout -b tmp c1b0c9f546289b1592d7a895640de103723a0305
    $ cd ..
    $
    $ git clone  https://git.yoctoproject.org/git/meta-virtualization -b dunfell
    $ cd meta-virtualization
    $ git checkout 521459bf588435e847d981657485bae8d6f003b5
    $ cd ..
```
\<tag\> can be selected in any tags of meta-renesas.
Now the latest version is **BSP-3.0.x** or **BSP-3.0.x-updatey** if any new updates are applied.

Currently, there are 2 types of build procedure supported in below description:

**1. New build procedure (Recommended):**
- Initialize a build using the 'oe-init-build-env' script in Poky and point TEMPLATECONF to platform conf path. e.g.:
   ```bash
   $ TEMPLATECONF=$PWD/meta-renesas/meta-<platform>/docs/template/conf/ source poky/oe-init-build-env build
   ```
- To build optional features (Docker, Codec or Graphics, QT5, Bootloaders, Security), add necessary layers:
   ```bash
   # For Docker
   $ bitbake-layers add-layer ../meta-openembedded/meta-filesystems
   $ bitbake-layers add-layer ../meta-openembedded/meta-networking
   $ bitbake-layers add-layer ../meta-virtualization

   # For Codec
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs

   # For Graphics
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics

   # For QT5
   $ bitbake-layers add-layer ../meta-qt5

   # For Bootloaders (only for RZ/V2M and RZ/V2MA)
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-bootloaders

   # For Security (supported for RZ/G2[H,M,N,E], RZ/G2[L,LC,UL] and RZ/V2L)
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-security
   ```
- Build the target file system image using bitbake:
   ```bash
   $ MACHINE=<board> bitbake core-image-<target>
   ```
\<platform\> and \<board\> can be selected in below table:

|Renesas MPU| platform |        board           |
|:---------:|:--------:|:----------------------:|
|RZ/G1M     |rzg1      |iwg20m-g1m              |
|RZ/G1N     |rzg1      |iwg20m-g1n              |
|RZ/G1H     |rzg1      |iwg21m            	|
|RZ/G1E     |rzg1      |iwg22m                  |
|RZ/G1C     |rzg1      |iwg23s                  |
|RZ/G2H     |rzg2h     |hihope-rzg2h            |
|RZ/G2M     |rzg2h     |hihope-rzg2m            |
|RZ/G2N     |rzg2h     |hihope-rzg2n            |
|RZ/G2E     |rzg2h     |ek874                   |
|RZ/G2L     |rzg2l     |smarc-rzg2l, rzg2l-dev  |
|RZ/G2LC    |rzg2l     |smarc-rzg2lc, rzg2lc-dev|
|RZ/G2UL    |rzg2l     |smarc-rzg2ul, rzg2ul-dev|
|RZ/V2L     |rzv2l     |smarc-rzv2l, rzv2l-dev  |
|RZ/V2M     |rzv2m     |rzv2m                   |
|RZ/V2MA    |rzv2m     |rzv2ma                  |
|RZ/Five    |rzfive    |smarc-rzfive, rzfive-dev|

**2. Build procedure for legacy users (common procedure) (unsupported for RZ/G1 Series, RZ/V2M and RZ/V2MA):**
- Initialize a build using the 'oe-init-build-env' script in Poky. e.g.:
    ```bash
    $ source poky/oe-init-build-env
    ```
- Prepare default configuration files. :
    ```bash
    $ cp $WORK/meta-renesas/docs/template/conf/<board>/*.conf ./conf/
    ```
\<board\>: can be selected in any platforms:
* RZ/G2H:  hihope-rzg2h
* RZ/G2M:  hihope-rzg2m
* RZ/G2N:  hihope-rzg2n
* RZ/G2E:  ek874
* RZ/G2L:  smarc-rzg2l, rzg2l-dev
* RZ/G2LC: smarc-rzg2lc, rzg2lc-dev
* RZ/G2UL: smarc-rzg2ul, rzg2ul-dev
* RZ/V2L:  smarc-rzv2l, rzv2l-dev
* RZ/Five:  smarc-rzfive, rzfive-dev
- Build the target file system image using bitbake:
    ```bash
    $ bitbake core-image-<target>
    ```
- To build Docker (optional): comment out a line in conf/local.conf:
   ```
   DISTRO_FEATURES_remove = " docker"
   ```

\<target\> for these built types:
* RZ/Five, RZ/V2M, RZ/V2MA: bsp
* Others: bsp, weston, qt

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

    poky-glibc-x86_64-core-image-weston-aarch64-toolchain-x.x.sh

Usage of toolchain SDK: Install the SDK to the default: _/opt/poky/x.x_
For 64-bit target SDK:
```bash
    $ sh poky-glibc-x86_64-core-image-weston-aarch64-toolchain-x.x.sh
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
* QT Demo (unsupported for RZ/V2M and RZ/V2MA): choose QT5 Demonstration to build with core-image-qt. QT5 Demos are some applications to demonstrate QT5 framework.
  * Unset QT_DEMO (default): all QT5 Demos are not built with core-image-qt.
  ```
  #QT_DEMO = "1"
  ```
  * Allow QT_DEMO: all QT5 Demos are built and included in core-image-qt.
  ```
  QT_DEMO = "1"
  ```
* Realtime Linux (unsupported for RZ/V2M and RZ/V2MA): choose realtime characteristic of Linux kernel to build with. You can enable this feature by setting the value "1" to IS_RT_BSP variable in local.conf:
  ```
  IS_RT_BSP = "1"
  ```
* Create SBoM SPDX: generate JSON SPDX for images.
  * **Disable creating SBoM SPDX (default):** creating SPDX is not supported.
  ```
  #INHERIT += "create-spdx"
  ```
  * **Enable creating SBoM SPDX:** creating SPDX is supported and built.
  ```
  INHERIT += "create-spdx"
  ```
    * Below variables are optional settings to create spdx. Uncomment out them to enable the features (disabled by default):
      * SPDX_PRETTY: Make generated files more human readable (newlines, indentation)
      ```
      SPDX_PRETTY = "1"
      ```
      * SPDX_ARCHIVE_PACKAGED: Add compressed archives of the files in the generated target packages.
      ```
      SPDX_ARCHIVE_PACKAGED = "1"
      ```
    * When enabling SBoM SPDX support, SDK will be failed to build. To fix it, please apply below changes in "poky/meta/classes/populate_sdk_base.bbclass":
      ```
      -do_populate_sdk[cleandirs] = "${SDKDEPLOYDIR}"
      +do_populate_sdk[cleandirs] += "${SDKDEPLOYDIR}"

      ```
* WIC image (unsupported for RZ/G1 MPUs): deploy disk images format. It is enabled by default in local.conf. To disable it, please comment out or set 0 to below setting:
  ```
  WKS_SUPPORT ?= "1"
  ```
  If you do not want to use default wic image file, please update "WKS_DEFAULT_FILE" or "WKS_FILE" to your desirable file.
