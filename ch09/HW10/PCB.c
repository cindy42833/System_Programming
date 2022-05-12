#define __KERNEL__
#include <linux/sched.h>
#include <stdio.h>
#include <stdlib.h>
main()
{
    printf("sizeof(struct task_struct) - %d\n",
    sizeof(struct task_struct));
}