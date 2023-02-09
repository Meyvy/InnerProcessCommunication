from subprocess import call
call(["gcc", "-o","client.out","client.c"])
port="8080"
ip="127.0.0.1"
num=8000
msg="a"*num
call(["./client.out","-h",ip,"-p",port,"-m",msg])