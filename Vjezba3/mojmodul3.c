#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>  // Za struct task_struct i for_each_process
#include <linux/sched/signal.h>  // Potrebno za pristup listi procesa

MODULE_LICENSE("GPL");

static int __init sviprocesi_init(void)
{
    struct task_struct *task; // Pokazivač na strukturu koja opisuje proces

    printk(KERN_INFO "sviprocesi: Modul učitan.\n");
    printk(KERN_INFO "sviprocesi: Lista svih procesa:\n");

    // Iteracija kroz sve procese u sistemu
    for_each_process(task)
    {
        printk(KERN_INFO "Proces: %s - PID: %d - PPID: %d - Prioritet: %d - Broj niti: %d\n",
               task->comm,                   // Ime izvršne datoteke
               task->pid,                    // PID procesa
               task->parent->pid,            // PID roditeljskog procesa
               task->prio,                   // Prioritet
               get_nr_threads(task));        // Broj niti  
    }

    return 0; 
}


static void __exit sviprocesi_exit(void)
{
    printk(KERN_INFO "sviprocesi: Modul uklonjen.\n");
}

module_init(sviprocesi_init);
module_exit(sviprocesi_exit);
