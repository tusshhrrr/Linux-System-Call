//
// Created by Tushar Malyan on 27/09/19.
//
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/pid_namespace.h>
#include <linux/syscalls.h>
#include <linux/fcntl.h>
#include <linux/file.h>
#include <linux/errno.h>
#include <uapi/asm-generic/errno-base.h>


asmlinkage long sys_sh_task_info(long pid, char* filename)
{
    struct task_struct *task;
    FILE *file;
    int a=sys_open(filename, O_WRONLY|O_CREAT,0755);
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);
    char buffer[100000];
    file=fopen(filename,"w");
    if (pid<0 || pid>32768)
    {
        return EINVAL;
    }
    for_each_process(task)
    {
        if ((int) task->pid == pid) {
            printk("Process : %s\n pid_number : %ld\n process state : %ld\n priority : %ld\n rt_priority : %ld\n static priority : %ld\n normal priority : %ld\n, on_cpu : %ld\n, sched_entity : %u\n, sigset blocked : %d\n,igset real_blocked : %d\n, thread_sp : %lu\n",
                   task->comm, (long) task_pid_nr(task), (long) task->state, (long) task->prio,
                   (long) task->rt_priority, (long) task->static_prio, (long) task->normal_prio, (long) task->on_cpu,
                   (unsigned int) task->se.on_rq, task->blocked, task->real_blocked, task->thread.sp);
            if (a < 0)
                return EISDIR;
            sprintf(buffer, file,
                    "Process : %s\n pid_number : %ld\n process state : %ld\n priority : %ld\n rt_priority : %ld\n static priority : %ld\n normal priority : %ld\n, on_cpu : %ld\n, sched_entity : %u\n, sigset blocked : %d\n,igset real_blocked : %d\n, thread_sp : %lu\n",
                    task->comm, (long) task_pid_nr(task), (long) task->state, (long) task->prio,
                    (long) task->rt_priority, (long) task->static_prio, (long) task->normal_prio, (long) task->on_cpu,
                    (unsigned int) task->se.on_rq, task->blocked, task->real_blocked, task->thread.sp);

            sys_write(fd, arr, strlen(arr));
            file = fget(fd);
            if (file) {
                vfs_write(file, arr, strlen(arr), &pos);
                fput(file);
            }
            sys_close(fd);


        }
    }
    set_fs(old_fs);
    return 0;
}
