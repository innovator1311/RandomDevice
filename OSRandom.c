#include <linux/init.h>   
#include <linux/module.h> 
#include <linux/device.h> 
#include <linux/kernel.h> 
#include <linux/fs.h>     
#include <linux/random.h> 
#include <linux/uaccess.h>     

//module infomation
MODULE_LICENSE("APCS_1751087_1751108");
MODULE_AUTHOR("Nguyen Minh Tri - Do Tri Nhan");
MODULE_DESCRIPTION("Module device kernel to random number, user can access through device file /dev/RandomDevice");
MODULE_VERSION("3.0.1");
                
static int Major; // device register major
static ssize_t random_read(struct file *, char *, size_t, loff_t *); // random read function

static struct file_operations fops =
{
        .read = random_read,
};


// init the device register
static int __init init(void)
{
  
   Major = register_chrdev(0,"RandomDevice",&fops);
   if (Major < 0) {
        printk(KERN_INFO "Regis fail for RandomDevice\n");
        return Major;
    }
    else{
        printk(KERN_INFO "Regis success major for RandomDevice %d\n",Major); }

    return 0;
}

// exit the device unregister
static void __exit exit(void)
{
      printk(KERN_INFO "Unregis success\n");
      unregister_chrdev(Major,"RandomDevice");
}

// main function
static ssize_t random_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    // get random char byte
    unsigned char randomNumber;
    get_random_bytes(&randomNumber, sizeof(char));
  
    // we convert char to int and pass each digit to number array
    char digit[10]; 
    int i = 0;

    if (randomNumber == 0) digit[i++] = '0'; //add 0 digit
    while (randomNumber != 0) {
	char value = randomNumber % 10 + '0';
    	randomNumber = randomNumber/10;
	digit[i++] = value;
    }

    char number[10];
    int j = i - 1;
    while (j >= 0) number[j--] = digit[i - j - 1]; // pass from digit to number in reverse order
    while (i < 10) number[i++] = '\0'; // pass null character for remain number index

    // we pass number array to buffer with size i
    copy_to_user(buffer,&number, sizeof(number));
    return 0;
}

module_init(init);
module_exit(exit);
