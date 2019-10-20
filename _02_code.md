# 文件IO

> 文件I/O操作的系统调用。
>
> API：open()、read()、write()、lseek()和close()。
>
> 这些函数的特点是不带缓存，直接对文件（包括设备）进行读写操作。这些函数虽然不是ANSI C的组成部分，但是是POSIX的组成部分。

> 函数简略说明

| open()  | 打开或创建文件                                               |
| ------- | ------------------------------------------------------------ |
| close() | 关闭一个被打开的文件                                         |
| read()  | 从指定的文件描述符中读出的数据放到缓存区中，并返回实际读入的字节数。 |
| write() | 向打开的文件写数据，写操作从文件的当前指针位置开始           |
| lseek() | 在指定的文件描述符中将文件指针定位到相应的位置               |

> 函数详细说明

| open()  | 在打开或创建文件时可以指定文件的属性及用户的权限等各种参数。 |
| ------- | ------------------------------------------------------------ |
| close() | 当一个进程终止时，所有被它打开的文件都由内核自动关闭，很多程序都使用这一功能而不显示地关闭一个文件。 |
| read()  | 函数若返回0，则表示没有数据可读，即已达到文件尾。读操作从文件的当前指针位置开始。当从终端设备文件中读出数据时，通常一次最多读一行。 |
| write() | 对磁盘文件进行写操作，若磁盘已满或超出该文件的长度，则write()函数返回失败。 |
| lseek() | 它只能用在可定位（可随机访问）文件操作中。管道、套接字和大部分字符设备文件是不可定位的，所以在这些文件的操作中无法使用lseek()调用。 |

## open()

---

> 所需头文件

```c
#include <sys/types.h>  /*提供类型pid_t的定义*/
#include <sys/stat.h>  /*获取文件属性*/
#include <fcntl.h>  /*定义open等函数原型*/
```

> 函数原型

```c
int open(const char *pathname, int flags, int perms)
```

> 函数参数

```c
pathname
    被打开的文件名（可包括路径名）
```

```c
flag
    文件打开的方式
    	O_RDONLY：以只读方式打开文件
    	O_WRONLY：以只写方式打开文件
    	O_RDWR：以读写方式打开文件
    	O_CREAT：如果该文件不存在，就创建一个新的文件，并用第三个参数为其设置权限
    	O_EXCL：如果使用O_CREAT 时文件存在，则可返回错误消息。这一参数可测试文件是否存在。此时open是原子操作，防止多个进程同时创建同一个文件
    	O_NOCTTY：使用本参数时，若文件为终端，那么该终端不会成为调用 `open()` 的那个进程的控制终端
    	O_TRUNC：若文件已经存在，那么会删除文件中的全部原有数据，并且设置文件大小为0。
    	O_APPEND：以添加方式打开文件，在打开文件的同时，文件指针指向文件的末尾，即将写入的数据添加到文件的末尾
```

```
perms
	创建的新文件的存取权限
		可以用一组宏定义：S_I(R/W/X)(USR/GRP/OTH)
		其中R/W/X 分别表示读/写/执行权限
		USR/GRP/OTH 分别表示文件所有者/文件所属组/其他用户
		例如，S_IRUSR | S_IWUSR 表示设置文件所有者的可读可写属性。
		八进制表示法中600也表示同样的权限
```

> 函数返回值

```c
成功：返回文件描述符
失败：-1
```
### tips:

> 在open()函数中，flags参数可通过“|”组合构成，但前3个标志常量（O_RDONLY、O_WRONLY以及O_RDWR）不能相互组合。perms是文件的存取权限，既可以用宏定义表示法，也可以用八进制表示法。

---

## close()

---

> 所需头文件

```c
#include <unistd.h>
```

> 函数原型

```c
int close(int  fd)
```

> 函数输入值

```c
fd：文件描述符
```

> 函数返回值

```c
0：成功
-1：出错
```

---

## read()

---

> 所需头文件

```c
#include <unistd.h>
```

> 函数原型

```c
ssize_t read(int fd, void *buf, size_t count)
```

> 函数传入值

```c
fd
    文件描述符
```

```c
buf
    指定存储器读出数据的缓冲区
```

```c
count
    指定读出的字节数
```

> 函数返回值

```c
成功：读到的字节数
0：已到达文件尾
-1：出错
```
### tips:

> 在读普通文件时，若读到要求的字节数之前已到达文件的尾部，则返回的字节数会小于希望读出的字节数。

---

## write()

---

> 所需头文件

```c
#include <unistd.h>
```

> 函数原型

```c
ssize_t write(int fd, void *buf, size_t count)
```

> 函数传入值

```c
fd
    文件描述符
```

```c
buf
    指定存储器写入数据的缓冲区
```

```c
count
    指定读出的字节数
```

> 函数返回值

```c
成功：已写的字节数
-1：出错
```

### tips:

> 在写普通文件时，写操作从文件的当前指针位置开始。

---

## lseek()

---

> 所需头文件

```c
#include <unistd.h>
#include <sys/types.h>
```

> 函数原型

```c
off_t lseek(int fd, off_t offset, int whence)
```

> 函数传入值

```c
fd
    文件描述符
```

```c
offset
    偏移量，每一读写操作所需要移动的距离，单位是字节，可正可负（向前移，向后移）
```

```c
whence
    当前位置的基点
    	SEEK_SET：当前位置为文件的开头，新位置为偏移量的大小
    	SEEK_CUR：当前位置为文件指针的位置，新位置为当前位置加上偏移量
    	SEEK_END：当前位置为文件的结尾，新位置为文件的大小加上偏移量的大小
```

> 函数返回值

```c
成功：文件的当前位移
-1：出错
```

---

## code

```
下面列出文件基本操作的实例，基本功能是从一个文件（源文件）中读取最后5B 数据并拷贝到另一个文件（目标文件）。在实例中源文件是以只读方式打开，目标文件是以只写方式打开（可以是读写方式）。若目标文件不存在，可以创建并设置权限的初始值为0644，即文件所有者可读可写，文件所属组和其他用户只能读。
```

### copy_file.c

```c
/* copy_file.c */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 1 /* 每次读写缓存大小，单位为字节，影响运行效率*/
#define SRC_FILE_NAME "src_file" /* 源文件名*/
#define DEST_FILE_NAME "dest_file" /* 目标文件名文件名*/
#define OFFSET 5 /* 复制的数据大小，单位为字节，即5个字节*/
int main()
{
int src_file, dest_file;
unsigned char buff[BUFFER_SIZE];
int real_read_len;
/* 以只读方式打开源文件，若文件不存在则出错*/
src_file = open(SRC_FILE_NAME, O_RDONLY);
/* 以只写方式打开目标文件，若此文件不存在则创建该文件, 访问权限值为644 */
dest_file = open(DEST_FILE_NAME,
O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
if (src_file< 0 || dest_file< 0)
{
printf("Open file error\n");
exit(1);
}
/* 将源文件的读写指针移到最后5B的起始位置*/
lseek(src_file, -OFFSET, SEEK_END);
/* 读取源文件的最后5B数据并写到目标文件中（指针向前移动OFFSET），每次读写1B */
while ((real_read_len = read(src_file, buff, sizeof(buff))) > 0)
{
write(dest_file, buff, real_read_len);
}
close(dest_file);
close(src_file);
return 0;
}
```




































