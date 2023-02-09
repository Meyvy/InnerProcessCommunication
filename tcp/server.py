from subprocess import call
call(["gcc", "-o","server.out","server.c"])
port="8080"
ip="127.0.0.1"
call(["./server.out","-h",ip,"-p",port])