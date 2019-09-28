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
    struct file *file;
    int a=sys_open(filename, O_WRONLY|O_CREAT,0755);
    char buff[100000];
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    if (pid<0 || pid>32768)
    {
        return EINVAL;
    }
    for_each_process(task)
    {
        if ((int) task->pid == pid) {
            printk(" Process : %s\n Process PID : %ld\n Process State : %ld\n Process Group : %d\n Session: %d\n Counter: %ld\n Parent Process PID: %d\n Priority : %ld\n normal priority : %ld\n RT_priority : %ld\n static priority : %ld\n on_cpu : %ld\n sched_entity : %u\n thread_sp : %lu\n",
                   task->comm, (long) task_pid_nr(task), (long) task->state,(int)task->pgrp,(long)task->session,(long)task->counter,(int)task->p_pptr->pid, (long) task->prio,
                    (long) task->normal_prio,(long) task->rt_priority, (long) task->static_prio, (long) task->on_cpu,
                   (unsigned int) task->se.on_rq, task->thread.sp);

            sprintf(buff,
                    " Process : %s\n pid_number : %ld\n process state : %ld\n Process Group : %d\n Session: %d\n Counter: %ld\n Parent Process PID: %d\n priority : %ld\n normal priority : %ld\n rt_priority : %ld\n static priority : %ld\n on_cpu : %ld\n sched_entity : %u\n thread_sp : %lu\n",
                    task->comm, (long) task_pid_nr(task), (long) task->state,(int)task->pgrp,(long)task->session,(long)task->counter,(int)task->p_pptr->pid, (long) task->prio,
                     (long) task->normal_prio,(long) task->rt_priority, (long) task->static_prio, (long) task->on_cpu,
                    (unsigned int) task->se.on_rq, task->thread.sp);
            if (a < 0)
                return EISDIR;
            file = fget(a);
            file->f_op->write(file, buff, strlen(buff), &file->f_pos);


        }
    }
    set_fs(old_fs);
    return 0;
}
