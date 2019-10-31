> 信号的发送和捕捉函数 kill()、 raise()、 alarm()以及 pause()

# 信号的发送和捕捉

## kill()

---
> 可以发送kill信号，也可以发送其他信号

> 所需头文件

```c
#include <signal.h>
#include <sys/types.h>
```

> 函数原型

```c
int kill(pid_t pid, int sig)
```

> 参数列表

```c
pid
    正数：要发送信号的进程号
	0：信号被发送到所有和当前进程在同一个进程组的进程
	-1：信号发给所有的进程表中的进程
	<-1：信号发送给进程组号为-pid的每一个进程
```

```
sig
	信号
```

> 返回值

```c
成功：0
出错：-1
```

---

## raise()

---

> 只能向自己发送信号

> 所需头文件

```c
#include <signal.h>
#include <sys/types.h>
```

> 函数原型

```c
int raise(int sig)
```

> 函数传入值

```c
sig
    信号
```

> 返回值

```c
成功：0
出错：-1
```

---

### kill_raise.c

```c
/* kill_raise.c  */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int main()
{
	pid_t pid;
	int ret;
 	/* 创建一子进程 */
 	if ((pid = fork()) < 0)
 	{
		printf("Fork error\n");
 		exit(1);
 	}
	if (pid == 0)
 	{
 		/* 在子进程中使用 raise() 函数发出 SIGSTOP 信号, 使子进程暂停 */
		printf("Child(pid : %d) is waiting for any signal\n", getpid());
 		raise(SIGSTOP);
 		exit(0);
 	}
 	else
 	{
 		/* 在父进程中收集子进程发出的信号，并调用 kill() 函数进行相应的操作 */
		sleep(1);
		if ((waitpid(pid, NULL, WNOHANG) ) == 0)
 		{
 			if ((ret = kill(pid, SIGKILL) ) == 0)
 			{
				printf("Parent killed %d\n",pid);
 			}
 		}
 		exit(0);
 	}
}
```

## alarm()

---

> 它可以在进程中设置一个定时器，当定时器指定的时间到时，它就向进程发送SIGALRM信号
>
> 1个进程只能有1个alarm()。如果重复设，则alarm()倒计时还是现在距离结束还剩的时间，返回值也是这个时间。（返回值正常为0）

> 所需头文件

```c
#include <unistd.h>
```

> 函数原型

```c
unsigned int alarm(unsigned int seconds)
```

> 函数传入值

```c
seconds：指定秒数，系统经过seconds 秒之后向该进程发送SIGALRM信号
```

> 返回值

```c
成功：如果调用此alarm()前，进程中已经设置了闹钟时间，则返回上一个闹钟时间的剩余时间，否则返回0
出错：-1
```

---

## pause()

---

> pause()函数是用于将调用进程挂起直至捕捉到信号为止。
>
> 这个函数很常用，通常可以用于判断信号是否已到。

> 所需头文件

```c
#include <unistd.h>
```

> 函数原型

```c
int pause(void)
```

> 函数返回值

```c
-1，并且把errno值设为EINTR
```

### alarm_pause_mod.c

```c
/* alarm_pause_mod.c */
#include <stdio.h>
#include <stdlib.h>
int main()
{
 	/*调用 alarm 定时器函数*/
	int ret = alarm(5) ;
	printf("I have been waken up.\n"); 
	sleep(3);
	ret = alarm(15);
	printf("alarm = %d\n",ret);
}
```

---

# 信号的处理



