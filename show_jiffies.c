
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buffer, size_t count, loff_t *pos);

static struct proc_ops proc_ops = {
    .proc_read = proc_read,
};

static int simple_init(void)
{
    printk(KERN_INFO "Loading jiffies Module\n");
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "%lu", jiffies);
    remove_proc_entry(PROC_NAME, NULL);
}

ssize_t proc_read(struct file *file, char __user *usr_buffer, size_t count, loff_t *pos) {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;

    if (completed) {
        completed = 0;
        return 0;
    }

    completed = 1;
    rv = sprintf(buffer, "%lu", jiffies);

    copy_to_user(usr_buffer, buffer, rv);

    return rv;
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
