# zeromemory
An utility to zero free memory on linux. Useful to make the Intel Rapid Start Technology actually Rapid, or to shrink virtual machine snapshots.
It requires root access as caches are cleared and RAM is zeroed by the kernel through page pinning.

## Compilation
Run `make && sudo make install`.

## Usage
Run `zeromemory` without arguments.

## Speeding up Intel Rapid Start Technology (IRST)
Since linux uses all the available RAM for file buffers, the firmware writes the whole RAM to disk, usually making IRST much slower than standard hibernation. It is not sufficient to just drop the caches, because the RAM will still contain the old data (new pages are cleared upon allocation), and the firwmare cannot tell which area of RAM is to be saved or not. However, the firmware appears to compress heavily (or discard?) pages with all zeroes. Hence, if you execute `zeromemory` right before sleep you get a huge speedup, both at shutdown and resume.

`make install` adds a systemd scripts that can automatize `zeromemory` right before sleep. To enable it, run `sudo systemctl enable zeromemory-presleep`.
