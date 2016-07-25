# meta-renesas-private

This is the private version of the public repository meta-renesas. This is a working area where all collaborators can commit features and fixes. Tested and stable updates will be periodically pushed to the public meta-renesas repository.

INSTRUCTIONS:

The recipes and scripts in this layer refer to the name of the public repository, which is meta-renesas. To make them work correctly with the private repository, either create a symlink to the cloned private repository or rename it during cloning.

Option 1 - Clone the repository using the original name and create a symbolic link to it named meta-rzg-demos:

$ git clone https://github.com/renesas-rz/meta-renesas-private<br>
$ ln -s ./meta-renesas-private ./meta-renesas

Option 2 - rename the repository during cloning:

$ git clone https://github.com/renesas-rz/meta-renesas-private meta-renesas


======================================================================================
Branch yocto_2.0
--------------------------------------------------------------------------------------
This branch supports building a Yocto 2.0 based BSP with the following components:

GCC 5.2

U-Boot 2015.07

Linux kernel 4.4

Weston 1.9

GStreamer 1.4.5

GPU support



This layer depends on:

URI: git://git.yoctoproject.org/poky

revision: 3b223f75eec1738fbc913858e8e11c8305e3edcb

URI: git://git.openembedded.org/meta-openembedded

revision: dc5634968b270dde250690609f0015f881db81f2

URI: git://git.linaro.org/openembedded/meta-linaro.git

revision: 12993e6bc8658ee37d303d8d59007f8dd9ab2b30



The layer also requires the modified proprietary Graphics libraries and drivers.





