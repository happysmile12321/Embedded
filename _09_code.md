## 函数说明

> 共享内存分4步

- 创建共享内存或获取已存在的共享内存的标识符
  - shmget()
  - 从内存中获得一段共享内存区域
- 映射共享内存
  - shmat()
  - 把这段创建的共享内存映射到具体的进程空间中
  - 可以使用**不带缓冲的I/O读写命令**对其这段内存进行操作
- 撤销内存映射
  - shmdt()
- 删除共享内存
  - shmctl()

---

## shmget()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int  shmget(key_t  key, int  size, int  shmflg)
```

> 函数传入值

```c
key
    共享内存的键值，可由ftok()创建，多个进程可以通过它访问同一个共享内存，如果键值不存在，第三个参数shmflg应该使用IPC_CREAT来创建新的共享内存；有个特殊键值0（IPC_PRIVATE），用于创建当前进程的私有共享内存，该键值不需要使用IPC_CREAT参数。
```

```c
size
    共享内存区大小
```

```c
shmflg
    同open()函数的权限位，也可以用八进制表示法
```

> 返回值

```c
成功：共享内存段标识符
出错：-1（错误原因在errno中）
```

---

## shmat()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
char *shmat(int  shmid, const void *shmaddr, int  shmflg)
```

> 函数传入值

```c
shmid
    要映射的共享内存区标识符
```

```c
shmaddr
    将共享内存映射到指定地址（若为0则表示系统自动分配地址并把该段共享内存映射到调用进程的地址空间）
```

```c
shmflg
    SHM_RDONLY：共享内存只读
	默认0：共享内存可读写
```

> 返回值

```c
成功：被映射的段地址
出错：-1（错误原因在errno中）
```

---

## shmdt()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int  shmdt(const void *shmaddr)
```

> 函数传入值

```c
shmaddr
    被映射的共享内存段地址
```

> 返回值

```c
成功：0
出错：-1（错误原因在errno中）
```

---

## shmctl()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/shm.h>
```

> 函数原型

```c
int  shmctl(int  shmid, int  cmd, struct  shmid_ds  *buf)
```

> 函数传入值

```c
shmid
    共享内存区标识符
```

```c
cmd
    IPC_STAT:得到共享内存的状态，把共享内存的shmid_ds结构复制到buf中
    IPC_SET:改变共享内存的状态，把buf所指的shmid_ds结构中的uid、gid、mode等复制到共享内存的shmid_ds结构内
    IPC_RMID:删除这片共享内存
#######shmid_ds结构体定义######
struct shmid_ds{
struct ipc_perm shm_perm;	/*操作权限*/
int shm_segsz;				/*段的大小（以字节为单位）*/
time_t shm_atime;			/*最后一个进程附加到该段的时间*/
time_t shm_dtime;			/*最后一个进程离开该段的时间*/
time_t shm_ctime;			/*最后一个进程修改该段的时间*/
unsigned short shm_cpid;	/*创建该段进程的pid*/
unsigned short shm_lpid;	/*在该段上操作的最后1个进程的pid*/
short shm_nattch;			/*当前附加到该段的进程的个数*/
};
#######ipc_perm结构体定义######
struct ipc_perm
{
key_t	key;				/*调用shmget()时给出的关键字 */
uid_t	uid;				/*共享内存所有者的有效用户ID */
gid_t	gid;				/*共享内存所有者所属组的有效组ID*/ 
uid_t	cuid;				/*共享内存创建 者的有效用户ID*/
gid_t	cgid;				/*共享内存创建者所属组的有效组ID*/
unsigned short		mode;	/*Permissions + SHM_DEST和SHM_LOCKED标志*/
unsignedshort		seq;		/*序列号*/
};
```

```c
buf
    共享内存管理结构体，作用和semctl()中的结构体类似
```

> 返回值

```c
成功：0
出错：-1（错误原因在errno中）
```

---

## strncmp()

---

> 所需头文件

```c
#include <string.h>
```

> 函数原型

```c
int strncmp ( const char * str1, const char * str2, size_t num );
```

> 函数传入值

```c
str1
    待比较字符串1
```

```c
str2
    待比较字符串2
```

```c
num
    比较字符串的前num位
```

> 返回值

```c
比较str1和str2两个字符串的前num个字符。
如果相同，则返回0，否则返回str1[i]-str2[i]。
其中i表示两个字符串前num个字符中首次不同的位置。
```

---

## strcpy()

---

> 所需头文件

```c
#include <string.h>
```

> 函数原型

```c
char *strcpy(char* dest, const char *src)：
```

> 函数传入值

```c
dest
    待处理字符类型数据的首地址
```

```c
src
    待添加的常量型的字符类型数据的首地址
```

> 函数返回值

```c
I don't know
```

---

## strncpy()

---

> 所需头文件

```c
#include <string.h>
```

> 函数原型

```c
char *strncpy(char *dest, char *src, int n);
```

> 传递参数

```c
dest
    要被粘贴的字符数组的首地址
```

```c
src
    要被copy的数组的首地址
```

```c
n
    从src里面拿多少个字节
```

> 函数返回值

```c
成功：指向dest的指针
```

> 函数意思

```c
从src里面拿出第n个字符，放到dest哪个地址后头。
1.src是以NULL为结尾的字符串
2.其他作用程序中会体现
```

---

### shmem.c

> 此版本为原版，后面有我自己写的版本

```c
/* shmem.c */
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE 2048
int main()
{
pid_t pid;
int shmid; /*共享内存标识符 */
char *shm_addr; /* 共享内存映射地址 */
char flag[] = "WROTE";
char buff[BUFFER_SIZE];
/* 创建共享内存 */
if ((shmid = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666)) < 0)
{
perror("shmget");
exit(1);
}
else
{
printf("Create shared-memory: %d\n",shmid);
}
/* 显示共享内存情况 */
system("ipcs -m");
pid = fork();
if (pid == -1)
{
perror("fork");
exit(1);
}
else if (pid == 0) /* 子进程处理 */
{
/*映射共享内存*/
if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
{
perror("Child: shmat");
exit(1);
}
else
{
printf("Child: Attach shared-memory: %p\n", shm_addr);
}
system("ipcs -m");
/* 通过检查在共享内存的头部是否标志字符串"WROTE"来确认父进程已经向共享内存写入有效数据 */
while (strncmp(shm_addr, flag, strlen(flag)))
{
printf("Child: Wait for enable data...\n");
sleep(5);
}
/* 获取共享内存的有效数据并显示 */
strcpy(buff, shm_addr + strlen(flag));
printf("Child: Shared-memory :%s\n", buff);
/* 解除共享内存映射 */
if ((shmdt(shm_addr)) < 0)
{
perror("shmdt");
exit(1);
}
else
{
printf("Child: Deattach shared-memory\n");
}
system("ipcs -m");
/* 删除共享内存 */
if (shmctl(shmid, IPC_RMID, NULL) == -1)
{
perror("Child: shmctl(IPC_RMID)\n");
exit(1);
}
else
{
printf("Delete shared-memory\n");
}
system("ipcs -m");
}
else/* 父进程处理 */
{
/*映射共享内存*/
if ((shm_addr = shmat(shmid, 0, 0)) == (void*)-1)
{
perror("Parent: shmat");
exit(1);
}
else
{
printf("Parent: Attach shared-memory: %p\n", shm_addr);
}
sleep(1);
printf("\nInput some string:\n");
fgets(buff, BUFFER_SIZE, stdin);
strncpy(shm_addr + strlen(flag), buff, strlen(buff));
strncpy(shm_addr, flag, strlen(flag));
/* 解除共享内存映射 */
if ((shmdt(shm_addr)) < 0)
{
perror("Parent: shmdt");
exit(1);
}
else
{
printf("Parent: Deattach shared-memory\n");
}
system("ipcs -m");
waitpid(pid, NULL, 0);
printf("Finished\n");
}
exit(0);
}
```

### myshmem.c

> 我的shmem.c，为我自己写的

```c
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#define SHARE_MEMORY_SIZE 2048
/*child read from shm,
 * father write
 * */
int main(void)
{
/*private shared memory,used by relations of parents*/
int shmid;
/*mapped address in father and child's program.*/
char* s_addr;
/*used to verify whether or not the data is from*/
char flag[]="WRITE";
/*used to write*/
char buff[SHARE_MEMORY_SIZE];
if((shmid=shmget(0,SHARE_MEMORY_SIZE,0666))<0)
{
printf("malloc shared memory errno!\nerrno is %d",errno);
exit(1);
}
system("ipcs -m");
pid_t p=fork();
if(p<0)
{
printf("errno is :%d\n",errno);
return -1;
}
else if(p==0)
{
/*
  before attach this process to shared memory,you need to warn user.
*/
printf("the current pid is :%d\n",getpid());
/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((s_addr=shmat(shmid,0,0))<0)
{
printf("mapped error,and errno is %d\n",errno);
exit(1);
}else{
printf("child process has mapped the sharedmemory_address %p\n",s_addr);
}
/* could add PV . 
 * here is use is there has data 'WRITE' of the headers?
 * */
while(strncmp(s_addr,flag,strlen(flag)))
{
printf("child is waitting for father send him some dates...\n");
sleep(5);
}

/*get date but except the flag--WRITE*/
strcpy(buff,s_addr+strlen(flag));
printf("child has received data (%s) from parents!!!\n",buff);

/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((shmdt(s_addr))<0)
{
printf("shared memory map delete errno,errno is:%d\n",errno);
exit(1);
}else
{
printf("child has delete the mapper of shared-memory!!!\n");
}

/*delete shared memory*/
if((shmctl(shmid,IPC_RMID,NULL))==-1)
{
printf("delete shared memory failed!!!\n");
exit(1);
}
else{
printf("child has deleted shared-memory!!!\n");
}

system("ipcs -m");
}
else{
/*
  before attach this process to shared memory,you need to warn user.
*/
sleep(1);
printf("the current pid is :%d\n",getpid());
/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((s_addr=shmat(shmid,0,0))<0)
{
printf("mapped error,and errno is %d\n",errno);
exit(1);
}else{
printf("father process has mapped the sharedmemory_address %p\n",s_addr);
}
printf("Please input some date to your child!\n");
fgets(buff,SHARE_MEMORY_SIZE,stdin);
strncpy(s_addr+strlen(flag),buff,strlen(buff));
strncpy(s_addr,flag,strlen(flag));
if((shmdt(s_addr))<0)
{
printf("shared memory map delete errno,errno is:%d\n",errno);
exit(1);
}
/*when child process isn't wake,the father is blocked!!!*/
waitpid(p,NULL,0);

printf("done!\n");
}//end of father progress
return 0;
}
```

### 改进的shmem.c

> 使用PV操作来代替WRITE

```c
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <stdlib.h>
#define SHARE_MEMORY_SIZE 2048
/*child read from shm,
 * father write
 * */
int main(void)
{
/*private shared memory,used by relations of parents*/
int shmid;
/*mapped address in father and child's program.*/
char* s_addr;
/*used to verify whether or not the data is from*/
//char flag[]="WRITE"; //it's useless!!!
/*used to write*/
char buff[SHARE_MEMORY_SIZE];
if((shmid=shmget(0,SHARE_MEMORY_SIZE,0666))<0)
{
printf("malloc shared memory errno!\nerrno is %d",errno);
exit(1);
}
system("ipcs -m");
/*do some works for semaphore*/
/*1.create new semaphore set*/
int ipc;
key_t key;
pid_t pid;
if((key = ftok("/",1))<0)
{
printf("create ipc key error,errno is %d\n",errno);
exit(1);
}
else
{
printf("successed produce ipc : %#x\n",key);
}
if((ipc=semget(key,1,0666|IPC_CREAT))<0)
{
printf("create semaphore set error!!!\nerrno is:%d\n",errno);
exit(1);
}
/*2.init semaphore*/
init_sem(ipc,0);
/*finished some works for semaphore*/

pid_t p=fork();
if(p<0)
{
printf("errno is :%d\n",errno);
return -1;
}
else if(p==0)
{
/*
  before attach this process to shared memory,you need to warn user.
*/
printf("the current pid is :%d\n",getpid());
/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((s_addr=shmat(shmid,0,0))<0)
{
printf("mapped error,and errno is %d\n",errno);
exit(1);
}else{
printf("child process has mapped the sharedmemory_address %p\n",s_addr);
}
/* could add PV . 
 * here is use is there has data 'WRITE' of the headers?
 * */
/*
while(strncmp(s_addr,flag,strlen(flag)))
{
printf("child is waitting for father send him some dates...\n");
sleep(5);
}
*/
/*Add P&V*/
P(ipc);
/*get date but except the flag--WRITE*/
strcpy(buff,s_addr);
printf("child has received data (%s) from parents!!!\n",buff);
/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((shmdt(s_addr))<0)
{
printf("shared memory map delete errno,errno is:%d\n",errno);
exit(1);
}else
{
printf("child has delete the mapper of shared-memory!!!\n");
}
/*delete shared memory*/
if((shmctl(shmid,IPC_RMID,NULL))==-1)
{
printf("delete shared memory failed!!!\n");
exit(1);
}
else{
printf("child has deleted shared-memory!!!\n");
}
system("ipcs -m");
}
/*father process*/
else
{
/*
  before attach this process to shared memory,you need to warn user.
*/
printf("the current pid is :%d\n",getpid());
/*
 *shared memory's address is anywhere,and it's read-write.
 * */
if((s_addr=shmat(shmid,0,0))<0)
{
printf("mapped error,and errno is %d\n",errno);
exit(1);
}else{
printf("father process has mapped the sharedmemory_address %p\n",s_addr);
}
printf("Please input some date to your child!\n");
fgets(buff,SHARE_MEMORY_SIZE,stdin);
strncpy(s_addr,buff,strlen(buff));
V(ipc);
if((shmdt(s_addr))<0)
{
printf("shared memory map delete errno,errno is:%d\n",errno);
exit(1);
}
/*when child process isn't wake,the father is blocked!!!*/
waitpid(p,NULL,0);

printf("done!\n");
}//end of father progress
return 0;
}


/*init semaphore set*/
int init_sem(int sem_id,int init_value)
{
union semum
{
int val;
struct semid_ds *buf;
unsigned short int *array;
};
union semum sem_union;
/*SETVAL*/
sem_union.val=init_value;
if(semctl(sem_id,0,SETVAL,sem_union)==-1)
{
printf("init error!!!\nerrno is : %d\n",errno);
exit(1);
}
return 0;
}
/*P&V*/
int P(int sem_id)
{
struct sembuf sb;
sb.sem_num=0;
/*if -1 equals P,if +1 equals V*/
sb.sem_op=-1;
sb.sem_flg=SEM_UNDO;
semop(sem_id,&sb,1);
return 0;
}

int V(int sem_id)
{
struct sembuf sb;
sb.sem_num=0;
/*if -1 equals P,if +1 equals V*/
sb.sem_op=+1;
sb.sem_flg=SEM_UNDO;
semop(sem_id,&sb,1);
return 0;
}


/*end of P&V*/
int sem_del(int sem_id)
{
if(semctl(sem_id,0,IPC_RMID,NULL)==-1)
{
printf("delete semaphore set error!!!\nerrno is : %d\n",errno);
exit(1);
}
return 0;
}
```







































