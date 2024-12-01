#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/timekeeping.h> // Za ktime_get_real_seconds

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vaše Ime");
MODULE_DESCRIPTION("Jezgrin modul za ispis broja jiffiesa i vremena u sekundama");

static int __init mojmodul_init(void)
{
    unsigned long jiffies_now = jiffies;
    unsigned long seconds_now = ktime_get_real_seconds();

    printk(KERN_INFO "mojmodul: Modul učitan.\n");
    printk(KERN_INFO "mojmodul: Jiffies: %lu\n", jiffies_now);
    printk(KERN_INFO "mojmodul: Sekunde od Unix epohe: %lu\n", seconds_now);

    return 0;
}

static void __exit mojmodul_exit(void)
{
    unsigned long jiffies_now = jiffies;
    unsigned long seconds_now = ktime_get_real_seconds();

    printk(KERN_INFO "mojmodul: Modul uklonjen.\n");
    printk(KERN_INFO "mojmodul: Jiffies: %lu\n", jiffies_now);
    printk(KERN_INFO "mojmodul: Sekunde od Unix epohe: %lu\n", seconds_now);
}

module_init(mojmodul_init);
module_exit(mojmodul_exit);
