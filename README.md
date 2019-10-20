# Embeded
嵌入式学习

## 目录 Index

- 00 课程说明&所需软件
- 01 vm虚拟机调试&嵌入式系统概述&gcc使用手册&vi|vim编辑器的使用手册&嵌入式系统概述
- 02 linux内核空间和用户空间的辩证关系&shell命令和API和系统调用三者的关系&中断&posix标准&中断&文件描述符&linux中的6种文件&文件IO和标准IO区别

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
  
    