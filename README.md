How to build the program:
make all
sudo insmod OSRandom.ko
cat /proc/devices     => find the major of device => suppose it is 239
mknod /dev/RandomDevice c 239 1
