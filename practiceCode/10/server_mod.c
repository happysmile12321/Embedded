#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#define MESSAGE_BUFF_SIZE 512
struct msgbuf
{
long mtype;
char mtext[MESSAGE_BUFF_SIZE];
};
int mqid,mqid2;
struct msgbuf mb,mb2;
void msg_send2();
void msg_receive();
int get_message_quene();


int main(void)
{
	pid_t pid;
	if((pid = fork())<0)
	{
		perror("fork process error!!!");
		exit(1);
	}else if(pid==0)
	{
		printf("[Server]:Father process'd pid is:%d\n",getpid() );
		//s-f-mq-receive
		mqid = create_message_quene();
		msg_receive();
		exit(0);

	}else
	{
		printf("[Server]:Child process'd pid is:%d\n",getpid() );
		//s-c-mq2-send
		mqid2 = create_message_quene2();
		msg_send2(pid);
		exit(0);
	}


	
	return 0;
}


int create_message_quene()
{
	key_t key;
	if((key = ftok("/",'a')) < 0)
	{
		printf("errno is:%d",errno);
		exit(1);
	}
	if((mqid = msgget(key,IPC_CREAT|0666))<0)
    {
        perror("message quene create failed!!!");
        exit(1);
    }
    printf("[Server]:father process %d created message quene :%d\n",getpid(),mqid);
    return mqid;
}

int create_message_quene2()
{
	key_t key;
	if((key = ftok("/",'b')) < 0)
	{
		printf("errno is:%d",errno);
		exit(1);
	}
	if((mqid2 = msgget(key,IPC_CREAT|0666))<0)
    {
        perror("message quene create failed!!!");
        exit(1);
    }
    printf("[Server]:child process created message quene2 :%d\n",mqid2);
    return mqid2;
}


//f
void msg_send2(int arg)
{
int child=arg;
int pc;
	mb2.mtype=getpid();
    while(1)
    {
if((pc=waitpid(child,NULL,WNOHANG))==0)
{
        printf("input some data to message quene buff:\n");
        if(fgets(mb2.mtext,MESSAGE_BUFF_SIZE,stdin)==NULL)
        {
            printf("No message from stdin!\n");
            exit(1);
        }
        if(msgsnd(mqid2,&mb2,strlen(mb2.mtext),IPC_NOWAIT)<0)
//        if(msgsnd(mqid2,&mb2,strlen(mb2.mtext),0)<0)
        {
            perror("message send error!");
            exit(1);
        }
        if (strncmp(mb2.mtext, "quit", 4) == 0)
        {
    		if ((msgctl(mqid2, IPC_RMID, NULL)) < 0)
    		{
    			perror("remove message quene2 error");
    			exit(1);
    		}
    		printf("messages be removed by process %d\n",getpid());
    		// if ((msgctl(mqid, IPC_RMID, NULL)) < 0)
    		// {
    		// 	perror("remove message quene error");
    		// 	exit(1);
    		// }
kill(child,2);
		//open1,close mq1
		mqid=get_message_quene();
		if ((msgctl(mqid, IPC_RMID, NULL)) < 0)
    		 {
    		 	perror("remove message quene error");
    			exit(1);
    		 }
    		break;
        }
}
else if(pc>0)
{
	break;
}
    }
}
//c
void msg_receive(int arg)
{
int child = arg;
	do
    {
    	memset(mb.mtext, 0, MESSAGE_BUFF_SIZE);
    	//如果接受到杀死信号，则将消息队列关闭
        if(msgrcv(mqid,&mb,MESSAGE_BUFF_SIZE,0,0)<0)
        {
            perror("message receive error!");
        }
        printf("Server's Process %d received data from client:%s",getpid(),mb.mtext);
    }while(strncmp(mb.mtext, "quit", 4)!=0);
}int get_message_quene()
{
	key_t key;
	if((key = ftok("/",'a')) < 0)
	{
		printf("errno is:%d",errno);
		exit(1);
	}
	if((mqid = msgget(key,IPC_EXCL))<0)
	{
		printf("Server is not started!!!\n");
		exit(1);
	}
	if((mqid = msgget(key,0666))<0)
	{
		perror("message quene open fail!!!");
		exit(1);
	}
	printf("[Client]:father process %d opened message quene: %d\n",getpid(),mqid);
    return mqid;
}
