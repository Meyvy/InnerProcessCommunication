from subprocess import call
call(["gcc","-o","client.out","client.c","-lrt","-pthread"])
msg="a"*8000
call(["./client.out",msg])