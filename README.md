# Embedded
嵌入式学习

## 目录 Index

- 00 课程说明&所需软件&开发环境搭建(百度网盘分享)
- 01 vm虚拟机调试&嵌入式系统概述&gcc使用手册&vi|vim编辑器的使用手册&嵌入式系统概述
- 02 linux内核空间和用户空间的辩证关系&shell命令和API和系统调用三者的关系&中断&posix标准&中断&文件描述符&linux中的6种文件&文件IO和标准IO区别
- 02 code   -- 2019/10/21日更新
  - 文件IO的系统调用的相关API函数的详细用法，讲解，代码demo，以及扩展分析
  - 文件锁
  - 记录锁
  - 强制记录锁（由kernel加）
  - 结尾 -- errno代码 中文版
- 02 实验--待完成(2019/10/24日更新)
- 03 IO多路复用&IO多路复用5种模型&IO系统概述&IO通道图解&DMA和中断&IO多路复用使用场景&inode和有名管道
- 03 code -- 2019/10/24日更新
  - select()函数
  - 宏定义的意思
  - poll()函数
- 04 linux进程控制(第二大部分)&PCB&linux进程管理&前后台进程手工管理&调度启动
- 04 code linux进程控制编程&fork()&vfork()&exec函数族&exit和_exit函数&wait和waitpid函数
- 05 linux进程控制2&守护进程(Daemon)&终端&编写守护进程
  - 因为内容比较少，因此这一讲不出code，code包含在这里面
- 06 linux进程间通信（管道）&  进程之间通信的几种方式
  - 同样内容比较少，因此这一讲不出code，code包含在这里面
- 07 linux进程间通信(信号)
-  07 code kill()&raise()&alarm()&pause()&信号的处理&signal()&sigaction()&信号集函数&sigprocmask()&sigpending()
- 08 linux进程间通信(信号量)&PV操作&二维信号量
- 08 code 信号量编程&semget()&ftok()&IPCS命令&semctl()&semop()

## 环境说明

```
由于学校的机房不连接Internet，故只能使用linux镜像自带的rpm源安装软件。
因为学校机房的问题，所以在vmware中无法安装linux，需要执行一下脚本，reinstall.sh。
系统是老旧的red hat企业版6 32位
```

> reinstall.sh

```sh
#!/bin/bash
mkdir /aa
mount /dev/sr0 /aa
rpm -e gcc-c++
rpm -e gcc
rpm -e glibc-devel
rpm -e glibc-headers
rpm -e cpp
rpm -e mpfr
rpm -e cloog-ppl
rpm -e ppl
yum install gcc -y
yum install gcc-c++ -y
```

## 笔记更新日志

- 2019/10/20日更新 **(XXX手册 )**
  - eg:gcc使用手册
    - gcc使用手册简略
      - 我自己总结的，具有较强的实用价值
    - gcc使用手册详细
      - 课件上的，很详细，也很复杂
  
- 2019/10/20日更新 (新文件名说明)
  
  - 从02开始，不仅仅有重要的理论知识，更重要的code也新鲜上线。但我想为了区分这些内容，因此把code单独命名为`_02_code.md`，其中，里面既有写好的嵌入式代码，也有关于用到的函数的详细讲解。
  
  - `code.md`说明：因为都是函数嘛。首先得先弄清楚函数都有哪些功能。因此函数简略说明都是对函数最最精炼的说明。但往往很片面，后面紧接着跟函数的详细说明。再往后就是函数的用法表格。
  
- 2019/10/24日更新(新文件说明)
  
  - 从02开始，不仅有理论知识&code，还有实验。实验是这种课程基本上都要有的。这种课程是操作性极强的课程。因此开始实验很有必要。那么，我也将实验添加到里面。实验可以当做是对自己的一次小测试。
  - 因为11月初有一个期中测试，而02的代码涉及到生产消费者问题，过于复杂。因此先暂停02的实验。
  - 新加入一种笔记格式，脚注。脚注是`[^note]:`。它的作用等同于注释。
  
- 2019/11/2日更新
  
  - 近期说明，已经更新到同步老师的进度。最近有期中考试，因此应该不会再讲课。
  
  
