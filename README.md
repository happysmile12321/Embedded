# Embeded
嵌入式学习

## 目录 Index

- 00 课程说明





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

