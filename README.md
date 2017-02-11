RPi-Info
=============

Raspberry Pi Hardware & Software Information Reporting Tool 


![screen](https://raw.githubusercontent.com/mohdumar644/RPi-Info/master/images/ubuntu-mate.png "Screenshot")

Binary
-------

A ready-to-run binary with all dependencies bundled is [available](https://github.com/mohdumar644/RPi-Info/raw/master/bin/RPi-Info).

It requires FUSE.
```
DEBIAN/UBUNTU/RASPBIAN: sudo apt-get install fuse libfuse-dev
FEDORA: sudo yum install fuse fuse-devel
```

To run the binary, do

```
chmod a+x ./RPi-Info
./RPi-Info
```


Compiling
-------

Requires Qt 5.5+ to build.
