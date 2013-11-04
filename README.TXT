Tomato RAF is a forked version of Tomato firmware created by Jonathan Zarate, 2007.

THIS SOFTWARE IS OFFERED "AS IS", AND THE AUTHOR GRANTS NO WARRANTIES OF ANY KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. THE AUTHOR SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE

Firmware packages can be downloaded from the official download site: http://victek.is-a-geek.com

Supported models:
ASUS: WL500Gp v1-v2, WL520Gu, RT-N10, RT-N12, RT-N16, RT-N53, RT-N66, RT-AC56U, RT-AC66U, RT-AC68U.
Belkin: F7D3301, F7D3302, F7D4302v1, F7D4301v1, F5D8235-4v3.
Cisco-Linksys: WRT160Nv3, E800, E900, E1000, E1200, E1500, E1550, E2000, E2500, E3000, E3200, E4200, WRT-320, WRT-610Nv2.
D-Link: DIR320, DIR615, DIR620c1.
Netgear: WNR2000v2, WNR3500L v1-v2.
Others: Ovislink WL1600G, CW-5358U, Huawei FiberHome HG320, ChinaNet RG-200E, ZTE H218N, WX-6615GT, TENDA W1800R.

There are multiple directories provided here. The release directory contains the router source package. The uClibc directory contains the source for uClibc and the binary tools required to build are provided as a convenience.

To build the router firmware using Ubuntu 13.04 64bits version. 

Environment packages.
sudo apt-get update && sudo apt-get upgrade && sudo apt-get install build-essential linux-headers-$(uname -r) && sudo apt-get install ubuntu-restricted-extras unace unrar zip unzip p7zip-full p7zip-rar sharutils rar uudeview mpack arj cabextract file-roller meld kompare putty subversion build-essential libncurses5-dev zlib1g-dev gawk flex quilt git-core libncurses5-dev zlib1g-dev gawk flex quilt libssl-dev xsltproc libxml-parser-perl mercurial bzr ecj cvs

Important: sudo dpkg-reconfigure dash (n)

For Tomato and development.
sudo apt-get install libncurses5 libncurses5-dev m4 bison flex libstdc++6-4.4-dev g++-4.4 g++ libtool sqlite gcc g++ binutils patch bzip2 flex bison make gettext unzip zlib1g-dev libc6 libncurses5-dev automake automake1.7 automake1.9 git-core gitk git-gui ia32-libs libc6-i386 lib32z1-dev

For MIPSR2 platform:
+ Ensure the tools in the release/tools directory are in your path. 
+ cd release/src-rt (for n routers) o cd release/src-rt-6.x (for ac routers) 
+ sudo ln -s ~/tomato/tools/brcm /opt/brcm 
+ export PATH=$PATH:/opt/brcm/hndtools-mipsel-linux/bin:/opt/brcm/hndtools-mipsel-uclibc/bin 
+ type 'make help' to see the options to build for each model.

This will create a parallel directory named 'image' into src-rt that contains the final firmware build.

For ARM platform:
+ cd release/src-rt-6.x.4708 
+ ln -s ~/tomato/tools/brcm /opt/brcm 
+ ln -s ~/tomato/release/src-rt-6.x.4708/toolchains/hndtools-arm-linux-2.6.36-uclibc-4.5.3 /opt/brcm-arm 
+ export PATH=$PATH:/opt/brcm/hndtools-mipsel-linux/bin:/opt/brcm/hndtools-mipsel-uclibc/bin:/opt/brcm-arm/bin 
+ Type 'make help' to see the options to build for each model.

This site contains all source files for Tomato-RAF-RT-N build 9013 release v1.2v

3rd November 2013
