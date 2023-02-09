# Inner Process Communication
A two part part project of inner process communication between one multi threaded server and multiple clientes. The server answers all the clients simultaneously with creating one thread for every client.
# TCP
The server and the client communicate over the tcp protocl the server creates a tcp socket on a predefined port and listens on the local host on that port and the client has to send a TCP connection request to the server on the predefined port
#Shared Memmory
The server and the clinet communicate using shared memory the sever creates two shared memories of A and B the clients write to one of them in their own segmnets and read from the other one.
# Misc
TCP and Shared Memmory both have python scripts to help compile and run their codes and They also both have helper files to validate and etc.
