### select()函数的作用

> 作用一

```
select()函数的作用是在规定的时间内阻塞进程，轮询某个文件描述符集中的文件是否准备好（可读、可写或出错），如果文件没有准备好，则select继续阻塞进程并持续轮询所有文件；如果有文件做好了准备，则返回准备好的文件数量，并解除阻塞。
```

> 作用二

```
select()也可以实现精确计时，计时精度可达到微秒（百万分之一秒）级。

1s=10^3ms(毫秒)=10^6μs(微秒)=10^9ns(纳秒)=10^12ps(皮秒)=10^15fs(飞秒)=10^18as(阿秒)=10^21zm(仄秒)=10^24ym(幺秒)
select()函数可以精确到微秒
```

> 作用三

```
select()函数适用于网络编程。
```

## select()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
```

> 函数原型

```c
int select(int numfds, fd_set *readfds, fd_set *writefds，fd_set *exceptfds, struct timeval *timeout)
```
[^fd_set]:long类型的数组
> 函数传入值

```c
numfds
    需要监视的文件的个数，即需要监视的文件描述符的最大值加1。
因为select()函数遍历文件列表中[0，numfds)的内容，所以只有numfds的值比文件描述符的最大值多1，才能遍历所有的文件。
```

```
readfds
	由select()监视的读文件描述符集合
```

```
writefds
	由select()监视的写文件描述符集合
```

```
exeptfds
	由select()监视的异常处理文件描述符集合
```

```
timeout
	NULL:永远等待，直到捕捉到信号或文件描述符已准备好为止
	具体值:struct timeval类型的指针，若等待了timeout时间还没有检测到任何文件描符准备好，就立即返回
	0:从不等待，测试所有指定的描述符并立即返回
```

```c
struct timeval
{
long tv_sec; /* 秒 */
long tv_usec; /* 微秒 */
}
```


> 函数返回值

```
大于0：成功，表示有文件已经准备好（可读、可写或出错），返回准备好的文件描述符的数目
0：超时；
-1：出错
```

> select()函数相关的宏定义函数
>
> 宏定义--预编译期间直接替换内容

```c
FD_ZERO(fd_set *set)
    清除一个文件描述符集
```

```c
FD_SET(int fd, fd_set *set)
    将一个文件描述符加入文件描述符集中
```

```c
FD_CLR(int fd, fd_set *set)
    将一个文件描述符从文件描述符集中清除
```

```CQL
FD_ISSET(int fd, fd_set *set)
    判断文件描述符fd是否在文件描述符集fd_set里。如果文件描述符fd是fd_set集中的一个元素，则返回非零值，否则返回0。
可以用于调用select()之后测试文件描述符集中的文件描述符是否有变化，因为select()轮询时会把没有准备好的fd剔除。
```

> select()函数相关的宏定义函数
>
> 一般来说，在使用select()函数之前，首先使用FD_ZERO()和FD_SET()来初始化文件描述符集，在使用了select()函数时，可循环使用FD_ISSET()来测试描述符集，在执行完对相关文件描述符的操作之后，使用FD_CLR()来清除描述符集。

---

> 由于多路复用通常用于I/O操作可能会被阻塞的情况，而对于可能会有阻塞I/O的管道、网络编程，到现在为止还没有涉及，所以这里通过手动创建两个管道文件（用mknod或者mkfifo命令），重点说明如何使用多路复用函数。

