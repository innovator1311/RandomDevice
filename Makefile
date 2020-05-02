obj-m+=OSRandom.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) getrandom.c -o getrandom
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm getrandom
makeall:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) getrandom.c -o getrandom
	sudo insmod OSRandom.ko
	sudo mknod /dev/RandomDevice c 241 1
cleanall:
	sudo rm /dev/RandomDevice
	sudo rmmod OSRandom.ko
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm getrandom

