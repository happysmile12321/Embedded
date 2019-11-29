## 函数说明

> 消息队列就是信箱

> 消息队列的应用包括创建或打开消息队列、添加消息、读取消息和控制消息队列这4 种操作。

> 其中创建或打开消息队列使用的函数是msgget()，这里创建的消息队列的数量会受到系统消息队列数量的限制；
>
> 添加消息使用的函数是msgsnd()函数，它把消息添加到已打开的消息队列末尾；
>
> 读取消息使用的函数是msgrcv()，它把消息从消息队列中取走，
>
> 与FIFO 不同的是，这里可以指定取走某一条消息；
>
> 最后控制消息队列使用的函数是msgctl()，它可以完成多项功能。

### msgget()

> msgget()函数可以用来判断消息队列是否存在。此时，仅仅用IPC_EXCL参数。
>
> `msgget(key,IPC_EXCL)`,不存在--返回<0。

> msgget()函数可以用来打开已经存在的消息队列。此时，需要制定打开的权限。
>
> `msgget(key,0600)`，此时如果一个没有权限的用户来打开，就会报文件描述符错误的提示。

> msgget()函数可以使用`IPC_CREAT`&`IPC_EXCL`拼接判断。
>
> `msgget(key,IPC_CREAT|IPC_EXCL)`，如果创建的是不存在的消息队列，则不会出错。否则，成功创建。

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int  msgget(key_t  key, int  msgflg)
```

> 函数传入值

```c
key
    消息队列的键值，可由ftok()生成，多个进程可以通过它访问同一个消息队列。 
```

```c
msgflg
    同open()函数的权限位，也可以用八进制表示法。此外，IPC_CREAT用于消息队列不存在时创建消息队列。IPC_PRIVATE用于创建当前进程的私有消息队列，IPC_EXCL用于判断消息队列是否存在，若已经存在，则在创建时出错返回；
```

> 返回值

```c
成功：消息队列ID
出错：-1（错误原因在errno中）
```

---

### msgsnd()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg)
```

> 函数传入值

```c
msgid
    消息队列的队列ID
```

```c
msgp
    指向消息缓冲区的指针, 此位置用来暂时存储发送和接收的消息，是一个用户可定义的通用结构。该消息结构msgbuf通常为：
struct msgbuf
{
long mtype; /* 消息类型，必须大于0 */
char mtext[1]; /* 消息正文 */
}
```

```c
msgsz
    消息正文的字节数（不包括消息类型指针变量）
```

```c
msgflg
    IPC_NOWAIT：若消息无法立即发送（比如：当前消息队列已满），函数会立即返回
    0：阻塞直到发送成功为止
```

> 返回值

```c
成功：0
出错：-1（错误原因在errno中）
```

---

### msgrcv()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int msgrcv(int msgid, void *msgp, size_t msgsz, long int msgtyp, int msgflg)
```

> 函数传入值

```c
msgid
    消息队列的队列ID
```

```c
msgp
    消息缓冲区, 同于msgsnd()函数的msgp
```

```c
msgsz
    消息正文的字节数（不包括消息类型指针变量）
```

```c
msgtyp
    0：接收消息队列中第一个消息
	大于0：接收消息队列中第一个类型为msgtyp的消息
	小于0：接收消息队列中第一个类型值不小于msgtyp绝对值且类型值又最小的消息
```

```c
msgflg
    MSG_NOERROR：若返回的消息比msgsz字节多，则消息就会截短到msgsz字节，且不通知消息发送进程
	IPC_NOWAIT若在消息队列中并没有相应类型的消息可以接收，则函数立即返回
	0：阻塞直到接收一条相应类型的消息为止
```

> 返回值

```c
成功：0
出错：-1（错误原因在errno中）
```

---

### msgctl()

---

> 所需头文件

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

> 函数原型

```c
int msgctl (int msgqid, int cmd, struct msgid_ds *buf )
```

> 函数传入值

```c
msgid
    消息队列的队列ID
```

```c
cmd(命令参数)
    IPC_STAT：读取消息队列的数据结构msgid_ds，并将其存储在buf 指定的地址中
	IPC_SET：设置消息队列的数据结构msgid_ds中的ipc_perm域（IPC操作权限描述结构）值。这个值取自buf参数
	IPC_RMID：从系统内核中删除消息队列
```

```c
buf
    描述消息队列的msgqid_ds结构类型变量
```

> 返回值

```c
成功：0
出错：-1（错误原因在errno中）
```

---

> 这个实例体现了如何使用消息队列进行两个进程（发送端和接收端）之间的通信，包括消息队列的创建、消息发送与读取、消息队列的撤消和删除等多种操作。
>
> ***\*消息发送端进程和消息接收端进程之间不需要额外实现进程之间的同步\****。在该实例中，发送端发送的消息类型设置为该进程的进程号（可以取其他值），因此接收端根据消息类型确定消息发送者的进程号。实例中使用函数ftok()获取键值，它可以根据不同的路径和关键字产生标准的key。

> 以下是消息队列发送端的代码：

### msgsnd.c

```c
/* msgsnd.c */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 512
/*自定义消息缓冲区*/
struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
};
int main()
{
	int qid;
	key_t key;
	struct message msg;
	/*根据不同的路径和关键字产生标准的key*/
	if ((key = ftok("/", 'a')) == -1)
	{
		perror("ftok");
		exit(1);
	}
	/*创建消息队列*/
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1)
	{
		perror("msgget");
		exit(1);
	}
	printf("Open queue %d\n",qid);
	while(1)
	{
		printf("Enter some message to the queue:");
		if ((fgets(msg.msg_text, BUFFER_SIZE, stdin)) == NULL)
		{
			printf("no message");
			exit(1);
		}
		msg.msg_type = getpid();
		/*添加消息到消息队列*/
		if ((msgsnd(qid, &msg, strlen(msg.msg_text), 0)) < 0)
		{
			perror("message posted");
			exit(1);
		}
		if (strncmp(msg.msg_text, "quit", 4) == 0)
		{
			break;
		}
	}
	exit(0);
}
```

> 以下是消息队列接收端的代码：

```c
/* msgrcv.c */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 512
struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
};
int main()
{
	int qid;
	key_t key;
	struct message msg;
	/*根据不同的路径和关键字产生标准的key*/
	if ((key = ftok("/", 'a')) == -1)
	{
		perror("ftok");
		exit(1);
	}
	/*获取消息队列*/
	if ((qid = msgget(key, 0666)) == -1)
	{
		perror("msgget");
		exit(1);
	}
	printf("Open queue %d\n", qid);
	do
	{
	/*读取消息队列*/
	memset(msg.msg_text, 0, BUFFER_SIZE);
	if (msgrcv(qid, &msg, BUFFER_SIZE, 0, 0) < 0)
	{
		perror("msgrcv");
		exit(1);
	}
	printf("The message from process %d : %s", msg.msg_type, msg.msg_text);
	} while(strncmp(msg.msg_text, "quit", 4));
	/*从系统内核中移走消息队列 */
	if ((msgctl(qid, IPC_RMID, NULL)) < 0)
	{
		perror("msgctl");
		exit(1);
	}
	exit(0);
}
```

### removeMessageQuene.c

> 用来删除已经创建的消息队列

```c
/* msgrcv.c */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MESSAGE_BUFF_SIZE 512
struct msgbuf
{
long mtype; /* 消息类型，必须大于0 */
char mtext[MESSAGE_BUFF_SIZE]; /* 消息正文 */
};
int main(void)
{
	int key,mqid;
	struct msgbuf mb;
	if((key = ftok("/",'a'))<0)
	{
		perror("ftok error!");
		exit(1);
	}
	//1.get message quene id
	if((mqid = msgget(key,0666))<0)
	{
		perror("1.Get message quene fail!!!");
		exit(1);
	}
	//2.remove message quene id from kernel
	if ((msgctl(mqid, IPC_RMID, NULL)) < 0)
	{
	perror("2.Remove message quene id error!!!");
	exit(1);
	}
	return 0;
}
```

> mycode

### message.c

```c
/*send message to message quene's such as sender */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MESSAGE_BUFF_SIZE 512
struct msgbuf
{
long mtype; /* 消息类型，必须大于0 */
char mtext[MESSAGE_BUFF_SIZE]; /* 消息正文 */
};
int main(void)
{
	int key,mqid;
	struct msgbuf mb;
	char *buf="I am message quene\n";
	//create message quene key
	if((key = ftok("/",'a'))<0)
	{
		perror("ftok error!");
		exit(1);
	}
	//create message quene
	if((mqid = msgget(key,IPC_CREAT|0666))<0)
	{
		perror("message quene create fail!!!");
		exit(1);
	}
	//init message quene buff
	mb.mtype=getpid();
	//input data to message quene struct's buff
	while(1)
	{
		printf("input some data to message quene buff:\n");
		if(fgets(mb.mtext,MESSAGE_BUFF_SIZE,stdin)==NULL)
		{
			printf("No message from stdin!\n");
			exit(1);
		}
		//send message
		if(msgsnd(mqid,&mb,strlen(mb.mtext),0)<0)
		{
			perror("message send error!");
			exit(1);
		}
		//exit while before send "quit"
		if (strncmp(mb.mtext, "quit", 4) == 0)
		{
		break;
		}
	}
	exit(0);
}
```

### reMessage.c

```c
/* receive message from message quene */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MESSAGE_BUFF_SIZE 512
struct msgbuf
{
long mtype; /* 消息类型，必须大于0 */
char mtext[MESSAGE_BUFF_SIZE]; /* 消息正文 */
};
int main(void)
{
	int key,mqid;
	struct msgbuf mb;
	if((key = ftok("/",'a'))<0)
	{
		perror("ftok error!");
		exit(1);
	}
	//1.get message quene id
	if((mqid = msgget(key,0666))<0)
	{
		perror("message quene create fail!!!");
		exit(1);
	}
	//2.message receive
	do
	{
		//receive message from message quene
		if(msgrcv(mqid,&mb,MESSAGE_BUFF_SIZE,0,0)<0)
		{
			perror("message receive error!");
		}
		printf("Data from message quene:%s",mb.mtext);
	}while(strncmp(mb.mtext, "quit", 4)!=0);
	//3.remove message quene id from kernel
	if ((msgctl(mqid, IPC_RMID, NULL)) < 0)
	{
	perror("remove message quene id error");
	exit(1);
	}
	return 0;
}
```

