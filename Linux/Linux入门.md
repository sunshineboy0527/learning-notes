## Linux常用指令

---

### 目录结构

- bin (binaries)存放二进制可执行文件
- sbin (super user binaries)存放二进制可执行文件，只有root才能访问
- etc(etcetera)存放系统配置文件
- usr(unix shared resources)用于存放共享的系统资源
- home存放用户文件的根目录
- root 超级用户目录
- dev(devices)用于存放设备文件
- lib(library)存放跟文件系统中的程序运行所需要的共享库及内核模块
- mnt(mount)系统管理员安装临时文件系统的安装点
- boot存放用于系统引导时使用的各种文件
- tmp(temporany)用于存放各种临时文件
- var(variable)用于存放运行时需要改变数据的文件

---

### 常见命令

1. **切换目录命令 `cd`**

`cd app` 切换到 app 目录  
`cd ..` 切换到上一层目录 
`cd /` 切换到系统根目录 
`cd ~` 切换到用户主目录 
`cd -` 切换到上一个所在目录中

2. **列出文件列表 `ls`**

`ls`(list)是一个非常有用的命令，用来显示当前目录下的内容。配合参数的使用，能以不同的方式显示目录内容。
> 格式:`ls[参数][路径或文件名]`

在 linux 中以 `.`开头的文件都是隐藏的文件
>> `ls` 显示当前目录下的所有普通文件(非隐藏文件)
>> `ls -a` 显示所有文件或目录(包含隐藏的文件)
>> `ls -l` 可以简写为`ll`, 显示详细的文件列表信息

3. **创建目录和移除目录 `mkdir` `rmdir`**

`rmdir`(remove directory)命令可用来删除**空**的子目录
`mkdir`(make directory)命令可用来创建子目录。
> `mkdir -p`可以级联常见父文件夹以及子文件夹。



4. **浏览文件**

`cat` 用于显示文件的内容。
`more` 一般用于要显示的内容会超过一个画面长度的情况。按空格键显示下一个画面。回车显示下一行内容。
`less` 用法和 `more` 类似，不同的是`less`可以通过 PgUp、PgDn 键来控制。
> 可以通过`Q`或`CTRL+C`结束

`tail` 命令是在实际使用过程中使用非常多的一个命令，它的功能是:用于显示文件后几行的内容。
> `tail-10 /etc/passwd` 查看后10行数据
> `tail -f catalina.log` 动态査看日志 

> 按`CTRL+C`结束

5. **文件操作**

`rm` 删除文件
`cp` (copy)命令可以将文件从一处复制到另一处
`mv` 移动或者重命名
`tar` 打包或解压
> 常用参数:
>> `-c`:创建-个新 tar 文件
>> `-v`:显示运行过程的信息中
>> `-f`:指定文件名“
>> `-z`:调用 gzip 压缩命令进行压缩
>> `-t`:查看压缩文件的内容
>> `-x`:解开 tar 文件
> - `tar` 命令位于`/bin` 目录下，它能够将用户所指定的文件或目录打包成一个文件，但**不做压缩**。
>- 一般Linux 上常用的压缩方式是选用`tar`将许多文件打包成一个文件，再以 `gzip` 压缩命令压缩成`xxx.tar.gz`(或称为xxx.tgz)的文件。

`find` 指令用于查找符合条件的文件
> `find / -name "hello*"` 从根目录下查找文件名称是以hello开头的文件

`grep` 查找文件里符合条件的字符串
> 用法:`grep [选项]... PATTERN [FILE]... `
>> `--color` 高亮显示符合条件的字符串
>> `-A1` 该字符串前面一行 `-B1` 该字符串后面一行

6. **其他**
`pwd` 显示当前所在目录
`touch` 创建一个空文件

7. **重定向输出`>` 和 `>>`**
前面内容只要是打印到控制台的都可以进行重定向输出。如：`cat` `ifconfig` ...
`>` 重定向输出，覆盖原有内容
`>>` 重定向输出，有追加功能

8. **系统管理命令**
`ps`: 正在运行的某个进程的状态
`p3 -ef`查看所有进程
`ki11 -9 [进程号]` 强制杀死进程

9. **管道 `|`**
管道是 Linux 命令中重要的一个概念，其作用是将一个命令的输出用作另一个命令的输入。
> `cat a.txt | grep java` 查找`a.txt`文件中`java`字符串
>> 等价于 `grep java a.txt`

### 常见网络操作

1. **主机名配置**
`hostname` 查看主机名
> `hostname` xxx修改主机名 重启后无效
如果想要永久生效，可以修改`/etc/sysconfig/network`文件

2. **IP 地址配置**
`ifconfig` 查看(修改)ip地址(重启后无效)
`ifconfig [网络名] [新IP地址]` 修改 ip 地址
> 如果想要永久生效，修改 `/etc/sysconfig/network-scripts/ifcfg-eth0` 文件
> - `DEVICE=eth0` 网卡名称
> - `B00TPR0T0=static` 获取ip的方式`(static/dhcp/bootp/none)`
> - `HWADDR=00:0C:29:B5:B2:69` MAC地址
> - `IPADDR=12.168.177.129` IP地址
> - `NETMASK-255.255.255.0` 子网掩码
> - `NETWORK-192.168.177.0` 网络地址
> - `BROADCAST=192.168.0.255` 广播地址
> - `NB00T=yes` 系统启动时是否设置此网络接口，设置为yes时，系统启动时激活此设备。

3. **域名映射**
`/etc/hogts` 文件用于在通过主机名进行访问时做ip地址解析,相当于 `windows` 系统的`C:\Windows\System32\drivers\etc\hosts`文件的功能

4. **网络服务管理**
`service network status` 查看指定服务的状态
`service network stop` 停止指定服务
`service network start` 启动指定服务
`service network reastart` 重启指定服务
--
`service--status-a11` 查看系统中所有后台服务
`netatat -nltp` 查看系统中网络进程的端口监听情况

5. **防火墙设置**
`service iptables status` 查看防火墙状态
`service iptables stop` 关闭防火墙
`service iptables start` 启动防火墙
`chkconfig iptables off` 禁止防火墙自启
> 防火墙根据配置文件`/etc/ayaconfig/iptables`来控制本机的“出”，”入“网络访问行为。