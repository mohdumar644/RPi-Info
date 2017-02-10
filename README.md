RPi-Info
=============

Raspberry Pi Hardware & Software Information Reporting Tool 


![screen](https://raw.githubusercontent.com/mohdumar644/RPi-Info/master/images/screenshot.png "Screenshot")

Binary
-------

A ready-to-run binary with all dependencies bundled is [available](https://github.com/mohdumar644/RPi-Info/raw/master/bin/RPi-Info).

It requires FUSE.
```
DEBIAN/UBUNTU/RASPBIAN: sudo apt-get install fuse libfuse-dev
FEDORA: yum install fuse fuse-devel
```

To run the binary, do

```
sudo chmod a+x ./RPi-Info
./RPi-Info
```


Compiling
-------

Requires Qt 5.5+ to build.
