---
title: ssh key
date: 2019-03-02 18:07:29
tags:
- ssh key
- 
---

## 生成 RSA key
执行下面的命令，Enter

<!-- more -->

$ rsa@octopus:~$ ssh-keygen -t rsa
  Generating public/private rsa key pair.
  Enter file in which to save the key (/home/rsa/.ssh/id_rsa):
    **此处按下 Enter **
Created directory '/home/rsa/.ssh'.
Enter passphrase (empty for no passphrase):
    **此处按下 Enter **
Enter same passphrase again:
Your identification has been saved in /home/rsa/.ssh/id_rsa.
Your public key has been saved in /home/rsa/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:xxxxxxxxxxxxxxxxx
The key's randomart image is:
    xxxxxxxx
```

命令执行完成后，在选择的路径下会生成 .ssh 这个文件夹，文件夹下面有 id_rsa ( 私钥 ) , id_rsa.pub 公钥 。

## 将公钥信息注册到服务器上，使用 ssh-copy-id 命令

```
$  ssh-copy-id -i ~/.ssh/id_rsa.pub pi@192.168.31.82
usr/bin/ssh-copy-id: INFO: Source of key(s) to be installed: ".ssh/id_rsa.pub"
The authenticity of host '192.168.31.82 (192.168.31.82)' can't be established.
ECDSA key fingerprint is SHA256:eLMcnKdwqOAluHd8mcInpfQWefiluEgqH102hoqNAuU.
Are you sure you want to continue connecting (yes/no)? yes
/usr/bin/ssh-copy-id: INFO: attempting to log in with the new key(s), to filter out any that are already installed
/usr/bin/ssh-copy-id: INFO: 1 key(s) remain to be installed -- if you are prompted now it is to install the new keys
pi@192.168.31.82's password:
    **此处输入密码，以后就不用输入密码了**

Number of key(s) added: 1
Now try logging into the machine, with:   "ssh 'pi@192.168.31.82'"
and check to make sure that only the key(s) you wanted were added.

```

## ssh 登录远端设备

	`$ ssh pi@192.168.31.82`


