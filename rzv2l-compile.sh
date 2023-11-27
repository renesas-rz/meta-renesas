#!/bin/bash


make clean
make smarc-rzv2l_defconfig
make -j 4 all
./fiptool create --align 16 --soc-fw bl31-smarc-rzv2l.bin --nt-fw u-boot.bin fip.bin
#cp fip.bin /tftpboot/RZ-G2L
cp fip.bin ~/projects/itp/fip-smarc-rzv2l_pmic.bin
cwd=$(pwd)
echo $cwd
cd ~/projects/itp
rm rzv2l.itb
rm capsule-rzv2l.bin
mkimage -f rzv2l.its rzv2l.itb
./mkeficapsule -f rzv2l.itb -i 1 capsule-rzv2l.bin
cp capsule-rzv2l.bin /media/sf_ubuntu
rm rzv2l.itb
cd $cwd

echo "Files copied successfully."
