# meta-rzg2

This is a Yocto build layer(version:dunfell) that provides support for the RZ/G2L Group of 64bit Arm-based MPUs from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: RZG2L SMARC Evaluation Kit / MPU: R9A77G044L2 (RZ/G2L)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies

This layer depends on:

    URI: git://git.yoctoproject.org/poky
    layers: meta, meta-poky, meta-yocto-bsp
    branch: dunfell
    revision: e32d854e33bc86c2a616df8708e021a098afcf73
    (tag: dunfell-23.0.5)
    (Need to cherry-pick a commit: git cherry-pick 9e444)

    URI: git://git.openembedded.org/meta-openembedded
    layers: meta-oe, meta-python, meta-multimedia
    branch: dunfell
    revision: cc6fc6b1641ab23089c1e3bba11e0c6394f0867c
    
    URI:http://git.yoctoproject.org/cgit.cgi/meta-gplv2/
    layers: meta-gplv2
    branch: dunfell
    revision: 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac

## Build Instructions

Assume that $WORK is the current working directory.
The following instructions require a Poky installation (or equivalent).

Below git configuration is required:
```bash
    $ git config --global user.email "you@example.com"
    $ git config --global user.name "Your Name"
```

Download proprietary graphics and multimedia drivers from Renesas, include:
- proprietary_mmp.tar.gz
- vspmfilter.tar.xz
(Graphic drivers are required for Wayland. Multimedia drivers are optional)

You can get all Yocto build environment from Renesas, or download all Yocto related public source to prepare the build environment as below.
```bash
    $ git clone https://git.yoctoproject.org/git/poky
    $ cd poky
    $ git checkout dunfell-23.0.5
    $ git cherry-pick 9e444
    $ cd ..
    $     
    $ git clone https://github.com/openembedded/meta-openembedded
    $ cd meta-openembedded
    $ git checkout cc6fc6b1641ab23089c1e3bba11e0c6394f0867c
    $ cd ..
    $    
    $ git clone https://git.yoctoproject.org/git/meta-gplv2
    $ cd meta-gplv2 
    $ git checkout 60b251c25ba87e946a0ca4cdc8d17b1cb09292ac
    $
    $ git clone  https://github.com/renesas-rz/meta-rzg2.git
    $ cd meta-rzg2
    $ git checkout <tag>
    $ cd ..
```
\<tag\> can be selected in any tags of meta-rzg2.
Now the latest version is **rzg2l_bsp_v1.1**

[Optional] If you need GPU/Codec support, or build Weston image, this step helps to copy them to build environment. Copy file proprietary_mmp.tar.gz and vspmfilter.tar.xz to $WORK and do below commands.
```bash
    $ tar -xf proprietary_mmp.tar.gz
    $ cd proprietary_mmp
    $ ./copy_gfx_mmp.sh ../meta-rzg2
    $ cd ..
    $
    $ cp vspmfilter.tar.xz meta-rzg2/recipes-multimedia/gstreamer/gstreamer1.0-plugin-vspmfilter
    $ 
```

Initialize a build using the 'oe-init-build-env' script in Poky. e.g.:
```bash
    $ source poky/oe-init-build-env
```

Prepare default configuration files. :
```bash
    $ cp $WORK/meta-rzg2/docs/template/conf/<board>/*.conf ./conf/
```
\<board\> : smarc-rzg2l, rzg2l-dev

Build the target file system image using bitbake:
```bash
    $ bitbake core-image-<target>
```
\<target\>:minimal,weston

After completing the images for the target machine will be available in the output
directory _'tmp/deploy/images/\<supported board name\>'_.

Images generated:
* Image (generic Linux Kernel binary image file)
* DTB for target machine
* core-image-\<target\>-\<machine name\>.tar.bz2 (rootfs tar+bzip2)
* core-image-\<target\>-\<machine name\>.ext4  (rootfs ext4 format)

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
* CIP Core: choose the version of CIP Core to build with. CIP Core are software packages that are maintained for long term by CIP community. You can select the value "1" or "0" for CIP_CORE variable
  ```
  CIP_CORE = "1"
  ```
