# OSKernelRandom

Hệ Điều Hành

**ĐÔ ÁN 1. TÌM HIỂU VÀ LẬP TRÌNH LINUX KERNEL MODULE**

**Linux kernel module**

- Tác giả
- Định nghĩa
  - Mỗi module là một driver có thể lắp vào kernel khi cần thiết
  - Linux kernel module Còn gọi là Loadable kernel module
- Chức năng:
  - The kernel consists of a set of kernel modules that interact with each other, each performing a specific function. Some kernel modules perform software functions exclusively, while others (such as device drivers) control the operation of system hardware components.
  - A purpose for writing a kernel module is to provide a middle layer of code, or common code, thus increasing the efficiency of your system by combining like tasks in a single area and eliminating redundant code.
- Đặc tính| Charactics
  - Is statically loaded as part of /vmunix or dynamically loaded into memory
  - Runs in kernel mode
  - Has a file name ending with the extension .mod
  - Contains a well-defined routine that executes first to initialize the module
  - May be a device driver when it performs any one of these additional tasks:
    - Handles interrupts from hardware devices
    - Accepts I/O requests from applications
- Các thành phần
  - Process management
  - Memory management
  - Device management
  - File systems
  - Networking
  - System call
- Cách tạo module
  - Tạo module file.c:
    - Cần thư viện khởi tạo và kết thúc 1 module: linux/module.h
    - Description module: tác giả chức năng, thiết bị hỗ trợ
    - Hàm khởi tạo và hàm exit
  - Tạo makefile
  - Tạo Kbuild:
    - ?

Biên dịch module =\&gt;make all =\&gt; file.ko

  - Xem thông tin module:
    - Modinfo file.ko
  - Gắn module vào kernel
    - Sudo insmod file.ko
  - Check module running, các module đng hoạt động
    - Lsmod | grep file
  - Check kernel log running
    - Dmesg
  - Remove module from kernel
    - Sudo rmmod file.ko

**Hệ thống quản lí file và device trong linux**

- **Source code ở thư mục, chức năng**
  - Arch
  - Fs
  - Mm
  - Block
  - Device
  - Net
  - Ipc
- **Device file:**
  - Mỗi thiết bị được xem là một device file tương ứng
  - Giao tiếp với device như một file
  - Nhận biết device driver -\&gt; device file : device number: 32 bit
    - Major: phân biệt các device với nhau: 12 bit =\&gt; 0-\&gt;2^12-1
    - Minor: phân biệt các driver cho 1 device: 20 bit
  - Danh sách device:
    - Ls -l /dev
  - Tạo character driver | 1 module:
    - OS specific
      - Create
        - Yêu cầu cấp phát device number
          - Cấp phát tĩnh
            - Xem major device: cat /proc/devices
            - Đăng kí device : register\_chrdev\_region
        - Yêu cầu kernel device file
        - Yêu cầu bộ nhớ cấu trúc dữ liệu
        - Yêu cầu khởi tạo vật lí
        - Đăng kí entry point với kernel
        - Đăng kí hàm ngắt với kernel
      - exit function
        - Hủy các yêu cầu trên
      - Entry point
        - pen()
        - release()
        - read()
        - write()
    - Device specific
      - Nhóm hàm khởi tạo giải phóng thiết bị
      - Nhóm đọc ghi thanh ghi thiết bị
        - Đọc, ghi thanh ghi dữ liệu
        - Lấy thông tin từ thanh ghi trạng thái
        - Thiết lập lệnh cho thanh ghi điều khiển
      - Nhóm hàm xử lí ngắt

- **Some knowledge and experiment in practice:**
  - If the custom module has a fault, it will lock up the entire system.
  - Can not programing kernel module in Subsystem in Window, because it do not have Linux header on WSL
  - Programing kernel API with virtual machine is prefer than physical machine to avoid data loss or memory leaking
  - Create function:
    - Use EXPORT\_SYMBOL macro to export this function
  - Module define basic info
    - MODULE\_LICENSE , MODULE\_AUTHOR, MODULE\_DESCRIPTION, MODULE\_VERSION=\&gt; : info of module example as lecense, athor, version…
  - Requirement
    - GCC
    - Ubuntu 18.04
    - Makefile

**Giao tiếp giữa tiến trình ở user space và kernel space**

![](RackMultipart20200428-4-xixcy3_html_812f53552f100e73.png)

By definition we have:

- Kernel Space
  - Activities that happen within the UNIX kernel. Modules may be statically loaded as part of /vmunix or dynamically loaded as needed. The module framework, which in can be thought of as the background area of kernel space, loads, unloads, makes management requests, and keeps track of the modules in kernel space.
- User Space
  - User application level or command-line interface to the operating system.

**Reference**

[http://www.frascati.enea.it/documentation/tru6450/ARHYGATE/NTRKRNLM.HTM](http://www.frascati.enea.it/documentation/tru6450/ARHYGATE/NTRKRNLM.HTM)

[https://sites.google.com/site/embedded247/ddcourse/kernelmoduleprogramming](https://sites.google.com/site/embedded247/ddcourse/kernelmoduleprogramming)

[https://github.com/nhathuy13598/Kernel\_Random\_Numbers/blob/master/Random.c](https://github.com/nhathuy13598/Kernel_Random_Numbers/blob/master/Random.c)

[https://stackoverflow.com/questions/53180342/trying-to-compile-kernel-module-in-windows-subsystem-for-linux-error](https://stackoverflow.com/questions/53180342/trying-to-compile-kernel-module-in-windows-subsystem-for-linux-error)
