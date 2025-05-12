# meta-renesas

This is a Yocto build layer(version:scarthgap) that provides support for the RZ/G2 Group of 64bit Arm-based MPUs from Renesas Electronics.
Currently the following boards and MPUs are supported:

- Board: RZG2L SMARC Evaluation Kit / MPU: R9A07G044L (RZ/G2L)
- Board: RZG2LC SMARC Evaluation Kit / MPU: R9A07G044C (RZ/G2LC)

## Patches

To contribute to this layer you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## Dependencies
This layer (for the Scarthgap release) depends on the following specific revisions:

**poky:**
- URL: `https://git.yoctoproject.org/poky`
- Branch: `scarthgap`
- Revision: `dc4827b3660bc1a03a2bc3b0672615b50e9137ff`
- (Tag: `scarthgap-5.0.8`)

**meta-arm:**
- URL: `https://git.yoctoproject.org/meta-arm`
- Branch: `scarthgap`
- Revision: `950a4afce46a359def2958bd9ae33fc08ff9bb0d`
- (Tag: `yocto-5.0.1`)

**meta-openembedded:**
- URL: `https://github.com/openembedded/meta-openembedded.git`
- Branch: `scarthgap`
- Revision: `67ad83dd7c2485dae0c90eac345007af6195b84d`

**meta-virtualization (for Docker):**
- URL: `https://git.yoctoproject.org/git/meta-virtualization`
- Branch: `scarthgap`
- Revision: `9287a355b338361e42027ce371444111a791d64f`

## Build Instructions

### Build Yocto BSP

Assume that $WORK is the current working directory.
The following instructions require a Poky installation (or equivalent).

Below git configuration is required:
```bash
    $ git config --global user.email "you@example.com"
    $ git config --global user.name "Your Name"
```

To download Multimedia and Graphics library and related Linux drivers, please contact Renesas 's Customer Sevice. 
Graphic drivers are required for Wayland. Multimedia drivers are optional.
After downloading the proprietary package, please decompress them then put meta-rz-features folder at $WORK directory,
alongside poky, meta-arm, etc. (e.g., $WORK/meta-rz-features).

Below is an example of VLP (Verified Linux Package) versions and their corresponding tags in the meta-renesas repository.

| VLP Version | Tag        | Notes           |
| :---------- | :--------- | :-------------- |
| 4.0.0       | BSP-v4.0.0 | Initial version |

**Note on Versioning:** The VLP versioning scheme indicates that higher numbers represent newer releases (e.g., VLP v4.2.0 is newer than VLP v4.0.0).


You can obtain the complete Yocto build environment from Renesas, or download the public Yocto Project source layers to prepare the build environment as shown below. Ensure you checkout the specific revisions listed in the "Dependencies" section.
```bash
    $ cd $WORK # Ensure you are in your working directory
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

Replace the \<tag\> with the latest tag. 

The BSP can be built default normally: copy the template files to build folder, manually modifying *bblayer.conf*, *local.conf*
files then using bitbake to build the image. Or you can do the steps below:

- Initialize a build using the 'oe-init-build-env' script in Poky and point TEMPLATECONF to platform conf path. e.g.:
   ```bash
   $ TEMPLATECONF=$PWD/meta-renesas/meta-rz-distro/conf/templates/rz-conf/ source poky/oe-init-build-env build
   ```

- To build optional features (Docker, Codec, or Graphics), you can use "bitbake-layers add-layer" from within the build directory:
   ```bash
   # For Docker
   $ bitbake-layers add-layer ../meta-openembedded/meta-networking
   $ bitbake-layers add-layer ../meta-openembedded/meta-filesystems
   $ bitbake-layers add-layer ../meta-virtualization

   # For Codec (requires meta-rz-features, see "Download Proprietary Drivers")
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-codecs

   # For Graphics (requires meta-rz-features, see "Download Proprietary Drivers")
   $ bitbake-layers add-layer ../meta-rz-features/meta-rz-graphics

   ```

- Build the target file system image using bitbake:
   ```bash
    # Replace <board> with your target board (e.g., smarc-rzg2l)
    # Replace <target> with your desired image type (e.g., minimal, weston)
    $ MACHINE=<board> bitbake core-image-<target>
   ```
Example: MACHINE=smarc-rzg2l bitbake core-image-weston
\<platform\>  (often synonymous with MPU series for configuration) and \<board\> can be selected from below table:

| Renesas MPU | Platform |    Board     |
| :---------: | :------: | :----------: |
|   RZ/G2L    |  rzg2l   | smarc-rzg2l  |
|   RZ/G2LC   |  rzg2lc  | smarc-rzg2lc |

After completing the images for the target machine will be available in the output
directory _'tmp/deploy/images/\<board name\>'_.

Images generated:
* Image (generic Linux Kernel binary image file)
* DTB for target machine
* core-image-\<target\>-\<board name\>.tar.bz2 (rootfs tar+bzip2)
* core-image-\<target\>-\<board name\>.ext4  (rootfs ext4 format)
* core-image-\<target\>-\<board name\>.wic.gz  (rootfs wic gz format)
* core-image-\<target\>-\<board name\>.wic.bmap  (rootfs wic block map format)

### Build BSP SDK

Use bitbake -c populate_sdk for generating the toolchain SDK. For example, to build an SDK for core-image-weston on a specific <board>:

```bash
    # For a 64-bit target SDK (aarch64) based on core-image-weston:
    $ bitbake core-image-weston -c populate_sdk
```
The SDK installer script can be found in the output directory _'tmp/deploy/sdk'_

It will be named similarly to: _'rz-vlp-glibc-x86_64-core-image-weston-cortexa55-<board-name>-toolchain-<version>.sh'_

**Usage of toolchain SDK:**
Install the SDK to the default location: _/opt/poky/<version>_
For 64-bit target SDK:
```bash
    $ sh rz-vlp-glibc-x86_64-core-image-weston-cortexa55-smarc-rzg2l-toolchain-5.0.8.sh
```

To use the 64-bit application development environment, source the environment script (adjust path if you installed elsewhere or if <version> differs):
```bash
    $ source /opt/poky/<version>/environment-setup-cortexa55-poky-linux
```

### Build configs

It is possible to change some build configs by modifying your _local.conf_ file (usually $WORK/build/conf/local.conf):
* **Realtime Linux:** To build with the PREEMPT_RT Linux kernel, add or modify the following line in _local.conf_:
  ```
  PREFERRED_PROVIDER_virtual/kernel = "linux-renesas-rt"
  ```

* **Docker:** To include Docker support in your image, ensure the following line is present and uncommented in _local.conf_:
  ```
  DISTRO_FEATURES:append = " virtualization docker"
  ```

## Using kas tool to build BSP

Kas provides an easy mechanism to set up and build Yocto BSP projects.
For kas's user guide, how to install kas..., please refer to: https://kas.readthedocs.io/en/latest/userguide.html.
For command-line usage and kas environment variables, please also refer to the user guide.

Assume $KAS_WORK_DIR is the path of the kas working directory (defaults to the current working directory if not set).

### How to buid with kas command

**Step 1: Clone meta-renesas in KAS_WORK_DIR**

KAS_WORK_DIR is the path of the kas work directory, current working directory is the default.
Run the below commands to clone meta-renesas and check out corresponding tag.

```bash
    $ cd ${KAS_WORK_DIR}
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout <tag>
    $ cd ..
```

**Step 2: Config and build the BSP**

Run the "kas build" command, pointing to the appropriate YAML configuration files within the meta-renesas directory

```bash
    $ kas build meta-renesas/kas/base.yml:meta-renesas/kas/machines/smarc-rzg2l.yml:meta-renesas/kas/images/core-image-weston.yml
```

To specify a download directory, you can use this command instead: 
```bash
    $ DL_DIR=<download-directory-path> kas build meta-renesas/kas/base.yml:meta-renesas/kas/machines/smarc-rzg2l.yml:meta-renesas/kas/images/core-image-weston.yml
```

### How to buid with kas-container command

This method uses a containerized environment for the build.

**Step 1: Clone meta-renesas in KAS_WORK_DIR**

```bash
    $ cd ${KAS_WORK_DIR}
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout <tag>
    $ cd ..
```

**Step 2: Config and build the BSP**

```bash
    $ kas-container build meta-renesas/kas/base.yml:meta-renesas/kas/machines/smarc-rzg2l.yml:meta-renesas/kas/images/core-image-weston.yml
```

### How to buid with kas menu

The kas menu command allows for interactive configuration, typically based on _Kconfig_ files if provided by the kas setup.

**Step 1: Clone meta-renesas in KAS_WORK_DIR**

```bash
    $ cd ${KAS_WORK_DIR}
    $ git clone  https://github.com/renesas-rz/meta-renesas.git
    $ cd meta-renesas
    $ git checkout <tag>
    $ cd .. 
```

**Step 2: Launch kas menu**

The kas menu command targets a _Kconfig_ file in the folder _meta-renesas_.
```bash
    $ kas menu meta-renesas/Kconfig
```

When the menu appears, continue to select the expected configuration(machine, image, docker option...).
Then push "Save & Build" button to save the current configuration and build the image. The defaut build folder is
*${KAS_WORK_DIR}/build*.

With kas menu, you also can use it to change the configuration when building with kas or kas container.
Just run the menu, re-configuration, push "Save & Exit" button, exit the menu and rebuild.
