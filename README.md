# meta-renesas

This is a Yocto build layer that provides support for the RZ/G1 Group of Arm-based MPUs from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: iWave RZ/G1H-PF Development Kit (iwg21m) / MPU: R8A7742 (RZ/G1H)
- Board: iWave RZ/G1M-PF Development Kit (iwg20m) / MPU: R8A7743 (RZ/G1M)
- Board: iWave RZ/G1N-PF Development Kit (iwg20m) / MPU: R8A7744 (RZ/G1N)
- Board: iWave RZ/G1E-PF Development Kit (iwg22m) / MPU: R8A7745 (RZ/G1E)
- Board: iWave RZ/G1C-PF Development Kit (iwg23s) / MPU: R8A77470 (RZ/G1C)

## Dependencies

This layer depends on:

* poky
  * URI: git://git.yoctoproject.org/poky
  * layers: meta, meta-yocto, meta-yocto-bsp
  * branch: rocko
  * revision: 342fbd6a3e57021c8e28b124b3adb241936f3d9d

* meta-linaro
  * URI: git://git.linaro.org/openembedded/meta-linaro.git
  * layers: meta-optee
  * branch: rocko
  * revision: 75dfb67bbb14a70cd47afda9726e2e1c76731885

* meta-openembedded
  * URI: git://git.openembedded.org/meta-openembedded
  * layers: meta-oe
  * branch: rocko
  * revision: dacfa2b1920e285531bec55cd2f08743390aaf57

(additional dependencies for Qt)

* meta-qt5
  * URI: https://github.com/meta-qt5/meta-qt5.git
  * revision: c1b0c9f546289b1592d7a895640de103723a0305

(additional dependencies for Gecko)

* meta-browser
  * URI: https://github.com/webdino/meta-browser.git
  * branch: firefox-60esr
  * revision: 61861aa694d41a8c77960d317a82d6676135bef7

* meta-rust
  * URI: https://github.com/webdino/meta-rust.git
  * revision: 4110f1d92af4dbcb73ed5ad6f18b25bd097451ae

## Build Instructions

Configure Git as below:

```bash
    git config --global user.email "you@example.com"
    git config --global user.name "Your Name"
```

Clone above dependencies to the same place as this layer and checkout each revision.

Download "RZ/G Multimedia Package" (proprietary graphics and multimedia drivers) from the following links:

* English: https://www.renesas.com/us/en/products/rzg-linux-platform/rzg-marcketplace/verified-linux-package/rzg-mlp-eva.html
* Japanese: https://www.renesas.com/jp/ja/products/rzg-linux-platform/rzg-marcketplace/verified-linux-package/rzg-mlp-eva.html

After downloading the proprietary package, please put the files on $WORK/proprietary then run copy scripts as below:

```bash
    export WORK=`pwd`
    export PKGS_DIR=$WORK/proprietary
    cd $WORK/meta-renesas/mera-rzg1
    ./copy_mm_software_lcb.sh $PKGS_DIR
    ./copy_gfx_software_<MPU>.sh $PKGS_DIR
    unset PKGS_DIR
```
\<MPU\> : rzg1h, rzg1m, rzg1n, rzg1e, rzg1c

Initialize a build using the 'oe-init-build-env' script in Poky. e.g.:

```bash
    cd $WORK
    source poky/oe-init-build-env
```

Prepare configuration files.

```bash
No GUI Framework:
    cp $WORK/meta-renesas/meta-rzg1/templates/<board>/*.conf ./conf

Enable Gekco:
    cp $WORK/meta-renesas/meta-rzg1/templates/<board>/gecko/*.conf ./conf

Enable Qt:
    cp $WORK/meta-renesas/meta-rzg1/templates/<board>/qt/*.conf ./conf
```
\<board\> :
  * RZ/G1H: iwg21m
  * RZ/G1M: iwg20m-g1m
  * RZ/G1N: iwg20m-g1n
  * RZ/G1E: iwg22m
  * RZ/G1C: iwg23s

Build a target file system image using bitbake:

```bash
    bitbake core-image-weston
```

After completing, images for the target machine will be available in the output directory _'tmp/deploy/images/\<supported board name\>'_.

Images to be generated:
  * u-boot-\<machine name\>.bin (u-boot binary image file)
  * uImage-\<machine name\>.bin (generic Linux Kernel binary image file)
  * uImage-\<machine name\>.dtb (DTB for target machine)
  * core-image-weston-\<machine name\>.tar.bz2 (rootfs tar+bzip2)

For more details, please refer to the "RZ/G Yocto Recipe Start-Up Guide" here:

* English: https://www.renesas.com/us/en/products/rzg-linux-platform/rzg-marcketplace/document.html
* Japanese: https://www.renesas.com/jp/ja/products/rzg-linux-platform/rzg-marcketplace/document.html

## Build Instructions for SDK

Prepare configuration files using templates for Qt environment as described above.  
Run bitbake to generate a toolchain SDK:

```bash
    bitbake core-image-weston-sdk -c populate_sdk
```

An installer of SDK will be stored at the output directory _'tmp/deploy/sdk'_  
Run the installer to install SDK to the default directory _'/opt/poky/x.x'_

```bash
    ./tmp/deploy/sdk/poky-glibc-x86_64-core-image-weston-sdk-<arch>-toolchain-2.4.2.sh
```

## Build configs

* CIP Core: choose the version of CIP Core to build with. CIP Core are software packages that are maintained for long term by CIP community.
  * Buster-limited: use limited packages from CIP Core Buster
  ```
  CIP_MODE = "Buster-limited"
  ```
  * Buster-full: use as many packages from CIP Core Buster as possible. Note that currently GPLv3 must be allowed for building Buster-full.
  CIP_MODE = "Buster-full"
  ```
  * **Jessie (default)**: not use CIP Core Buster, use limited packages from CIP Core Jessie instead
  ```
  CIP_MODE = "Jessie"
  ```
  * None CIP Core: not use CIP Core at all, use all default version from Yocto 2.4 Rocko
  ```
  CIP_MODE = "none"
  ```
Below table show the version of recipes that change due to above setting.  
Note that this table only show packages that change version, others are not shown.  
Package versions noted with `(debian)` mean they are CIP Core packages. The source code is taken from Debian repo. Different with original version, Debian version has many bug fixes backported from newer version.

|                        | **Buster-limited (non-GPLv3)** | Buster-full (allow GPLv3) | Jessie (non-GPLv3) | None CIP Core (allow GPLv3) |
|------------------------|--------------------------------|---------------------------|--------------------|-----------------------------|
| busybox                |  1.30.1 (debian)               |  1.30.1 (debian)          | 1.22   (debian)    | 1.24.1                      |
| openssl                |  1.1.1d (debian)               |  1.1.1d (debian)          | 1.0.1t (debian)    | 1.0.2o                      |
| glibc                  |  2.28   (debian)               |  2.28   (debian)          | 2.19   (debian)    | 2.26                        |
| binutils               |  -                             |  2.31.1 (debian)          | -                  | -                           |
| coreutils              |  6.9                           |  8.30   (debian)          | 6.9                | 8.27                        |
| gnupg                  |  1.4.7                         |  2.2.12 (debian)          | 1.4.7              | 2.2.0                       |
| libassuan              |  2.4.3                         |  2.5.2  (debian)          | 2.4.3              | 2.4.3                       |
| libpam                 |  1.3.0                         |  1.3.1  (debian)          | 1.3.0              | 1.3.0                       |
| libgcrypt              |  1.7.3                         |  1.8.4  (debian)          | 1.7.3              | 1.7.3                       |
| libunistring           |  0.9.7                         |  0.9.10 (debian)          | 0.9.7              | 0.9.7                       |
| perl                   |  5.24.1                        |  5.28.1 (debian)          | 5.24.1             | 5.24.1                      |
| bash                   |  3.2.57                        |  4.4                      | 3.2.57             | 4.4                         |
| diffutils              |  -                             |  3.6                      | -                  |                             |
| dosfstools             |  2.11                          |  4.1                      | 2.11               | 4.1                         |
| gawk                   |                                |  4.1.4                    | 3.1.5              | 4.1.4                       |
| m4                     |                                |  1.4.18                   | 1.4.9              | 1.4.18                      |
| make                   |  3.81                          |  4.2.1                    | 3.81               | 4.2.1                       |
| sed                    |  4.1.2                         |  4.2.2                    | 4.1.2              | 4.2.2                       |

binutils is an optional package, and will not be added to core-image at default, except in Buster-full (allow GPLv3) setting.  
Besides, due to the license GPLv3, binutils cannot be added to core-image with non-GPLv3 setting

## Patches

To contribute to this layer, you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.
