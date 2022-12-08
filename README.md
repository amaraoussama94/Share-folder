 
 
# PIKA_PIKA  
 
## Project veriosn  : 
  0.1 
## Project overview :  
-The aim of this application is to make  a two PC (aka client) connect using  socket  to share  a directory.

-The user  can use  some bash command  to maybe, list the directory files this options will be  extended all along  the project.

-Basically, we will have  a server and  client, we  will use HTTP /IP standard for this project.

![ALT](/Server-based-network.png "Server-based-network")

- C, bash and maybe other language will be used in this  project to make it  functional and  simple as much as we  can.

![ALT](/Socket_server_flowchart%20.png "flowchart")

*The entire process can be broken down into following steps:

*TCP Server 

-using create(), Create TCP socket. 

-using bind(), Bind the socket to server address.

-using listen(), put the server socket in a passive mode, where it waits for the client to approach the server to make a connection.

-using accept(), At this point, connection is established between client and server, and they are ready to transfer data.

-Go back to Step 3.

*TCP Client

-Create TCP socket.

-connect newly created client socket to server.

## Useful link 
-[socket-programming-cc](https://www.geeksforgeeks.org/socket-programming-cc/)

-[tcp-server-client-implementation-in-c](https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/)  

-[socket-programming](https://www.cs.dartmouth.edu/~campbell/cs50/socketprogramming.html)

-[socket](https://pubs.opengroup.org/onlinepubs/009619199/socket.htm) 
