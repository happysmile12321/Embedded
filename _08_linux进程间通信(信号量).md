## 信号量
> 信号量存在于并发的环境。  
> 多个进程可以为了某个任务而相互合作--同步  
> 多个进程可能在某个时刻抢夺对某种资源的使用权（CPU）--互斥  

> 这些资源被叫做临界资源  
> > 硬件资源（处理器、内存、存储器、外围设备）  
> > 软件资源（共享代码段、共享结构、变量）  

> 访问临界资源的代码叫临界区，临界区本身也会成为临界资源  

### 信号量的实现
> PV操作   
> P--通过  
> V--释放  

其中信号量对应于某一种资源。  

信号量值指的是当前可用的该资源的数量。  
当它的值大于0时，表示当前可用资源的数量；  
当它等于0则意味着目前没有可用的资源；  
当它的值小于0时，其绝对值表示等待使用该资源的进程个数。  

> PV操作的具体定义  

> R表示资源  
> S表示该资源的信号量值,同是可用资源的数量。  

> PV操作的具体实现
```c
p()
{
	s--;
	if(s<0)
	{
		block();
	}
}
```
```c
V()
{
	s++;
	if(s<=0)
	{
		release();
	}
}

```
#### 二维信号量
> 最简单的，s的值只取0或1,叫做2维信号量。
- s=0,可以表示信号的互斥。

### 生产者消费者问题

> In our processes,there would be two guy.--producer,consumer.
> Each time,producer produce "data" to buffer;
> 	  consumer consume "data" from buffer.
> So they will share [buffer].

-		----------		-
[producer] -- 	- BUFFER -  -- 		[consumer]
-		----------		-
```
In this situation,4 tips for you:
	1.Each time put  one "data"
	2.Each time take one "data"
	3.BUFFER full,  then stop put.
	4.BUFFER empty, then stop take.
```

```c
producer()
{
while(1)
{
	produce "data";
	P(empty);
	P(mutex);
	put "data" to buffer;
	V(mutex);
	V(full);
}
}
consumer()
{
while(1)
{
	consume"data";
	P(full);
	P(mutex);
	take "data" from buffer;
	V(mutex);
	V(empty);
}
}
```




