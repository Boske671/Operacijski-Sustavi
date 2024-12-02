#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>

MODULE_LICENSE("GPL");

static int __init mojmodul_init(void)
{
    unsigned long jiffies_now = jiffies;

    printk(KERN_INFO "mojmodul: Modul učitan.\n");
    printk(KERN_INFO "mojmodul: Jiffies: %lu\n", jiffies_now);
    printk(KERN_INFO "mojmodul: Sekunde od Unix pocetka: %lu\n", jiffies_now / HZ);

    return 0;
}

static void __exit mojmodul_exit(void)
{
    unsigned long jiffies_now = jiffies;

    printk(KERN_INFO "mojmodul: Modul učitan.\n");
    printk(KERN_INFO "mojmodul: Jiffies: %lu\n", jiffies_now);
    printk(KERN_INFO "mojmodul: Sekunde od Unix pocetka: %lu\n", jiffies_now / HZ);
}

module_init(mojmodul_init);
module_exit(mojmodul_exit);
