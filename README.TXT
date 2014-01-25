Tomato RAF is a forked version of Tomato firmware created by Jonathan Zarate, 2007.

THIS SOFTWARE IS OFFERED "AS IS", AND THE AUTHOR GRANTS NO WARRANTIES OF ANY KIND, EXPRESS OR IMPLIED, BY STATUTE,
COMMUNICATION OR OTHERWISE. THE AUTHOR SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE

Firmware packages and features for each version can be found at: http://victek.is-a-geek.com


Supported models:
ASUS: WL500Gp v1-v2, WL520Gu, RT-N10, RT-N10P, RT-N12, RT-N16, RT-N53, RT-N53A1, RT-N66, RT-AC56U, RT-AC66U, RT-AC68U.
Belkin: F7D3301, F7D3302, F7D4302v1, F7D4301v1, F5D8235-4v3.
Cisco-Linksys: WRT160Nv3, E800, E900, E1000, E1200, E1500, E1550, E2000, E2500, E3000, E3200, E4200, WRT-320, WRT-610Nv2

D-Link: DIR320, DIR615, DIR620c1.
Netgear: WNR2000v2, WNR3500L v1-v2, WNR3700 v3.
Others: Ovislink WL1600G, CW-5358U, Huawei FiberHome HG320, ChinaNet RG-200E, ZTE H218N, WX-6615GT, TENDA W1800R.

There are multiple directories provided here. The release directory contains the router source package. The uClibc
directory contains the source for uClibc and the binary tools required to build are provided as a convenience.

To build the router firmware using Ubuntu 13.10 64bits version. 

Packages (example of my environment).
sudo apt-get update && sudo apt-get upgrade && sudo apt-get install build-essential linux-headers-$(uname -r) && sudo apt-get install ubuntu-restricted-extras vlc vlc-plugin-pulse filezilla && sudo add-apt-repository ppa:libreoffice/ppa && sudo apt-get install libreoffice libreoffice-java-common libreoffice-math libreoffice-java-common libreoffice-pdfimport dia xsane unace unrar zip unzip p7zip-full p7zip-rar sharutils rar uudeview mpack arj cabextract file-roller libxine1-ffmpeg gxine mencoder mpeg2dec vorbis-tools id3v2 mpg321 mpg123 libflac++6 ffmpeg totem-mozilla icedax tagtool easytag id3tool lame libmad0 libjpeg-progs flac faac faad sox ffmpeg2theora libmpeg2-4 uudeview flac libmpeg3-1 mpeg3-utils mpegdemux liba52-0.7.4-dev gstreamer0.10-ffmpeg gstreamer0.10-fluendo-mp3 gstreamer0.10-gnonlin gstreamer0.10-plugins-bad-multiverse gstreamer0.10-plugins-bad gstreamer0.10-plugins-ugly gstreamer-dbus-media-service gstreamer-tools subversion build-essential quilt git-core git git-gui gitk kompare meld subversion nfs-common putty

Important: sudo dpkg-reconfigure dash (n)

For Tomato and development.

sudo apt-get install autoconf autogen make automake automake1.7 automake1.9 autopoint binutils bison bzip2 flex gawk xsltproc libxml-parser-perl gcc gcc-multilib gettext gperf g++ g++-4.4-multilib libc6 libncurses5 libncurses5-dev libstdc++6-4.4-dev libtool libssl-dev libxml2-dev libelf1:i386 libc6-i386 lib32z1-dev meld mtd-utils m4 mercurial bzr ecj cvs patch pkg-config shtool sqlite zlib1g-dev re2c

How to build your version:

For MIPSR2 platform:
+ Ensure the tools in the release/tools directory are in your path. 
+ cd tomato/release/src-rt (for n routers) o cd release/src-rt-6.x (for ac routers) 
+ sudo ln -s ~/tomato/tools/brcm /opt/brcm 
+ export PATH=$PATH:/opt/brcm/hndtools-mipsel-linux/bin:/opt/brcm/hndtools-mipsel-uclibc/bin
+ make distclean
+ type 'make help' to see the options to build for each model. (i.e: make V1=9013 V2=RAF r2nf build a rt-n16 version)

This will create a parallel directory named 'image' into src-rt that contains the final firmware build.

For ARM platform:
+ cd tomato/release/src-rt-6.x.4708 
+ ln -s ~/tomato/tools/brcm /opt/brcm 
+ ln -s ~/tomato/release/src-rt-6.x.4708/toolchains/hndtools-arm-linux-2.6.36-uclibc-4.5.3 /opt/brcm-arm 
+ export PATH=$PATH:/opt/brcm/hndtools-mipsel-linux/bin:/opt/brcm/hndtools-mipsel-uclibc/bin:/opt/brcm-arm/bin
+ make distclean
+ 
+ Type 'make help' to see the options to build for each model. (i.e: make V1=9013 V2=RAF ac56u build a rt-ac56u version)


This site contains all source files for Tomato-RAF-RT-N build 9013
