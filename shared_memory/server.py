from subprocess import call
call(["gcc","-o","server.out","server.c","-lrt","-pthread"])
call(["./server.out"])