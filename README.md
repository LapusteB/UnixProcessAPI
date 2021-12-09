# UnixProcessAPI
**Required: Unix/Linux/Ubuntu system library**
Compile and run the server file with specified channel ./server 365 then run ./client 365 to send messages to the server (one-Way)

The  objective  of  this  program  is  to  experiment  with  process  API  in  Unix  and  to  better  understand how the Unix shell works by trying to mimic its behavior. 

This is a C program that can send arbitrarily long messages to a chat server. The chat server’s binary 
code is provided for you. Your program is the client that communicates with the server through the 
following protocol. 
 
We Establish an IPC channel with the chat server through shared memory. Both the server and client 
programs are invoked through command line, with an integer provided as the key of the shared 
memory. 
     e.g.,     server 365 
                  client 365 
Here 365 is the key of the shared memory. It serves as a channel identifier. Processes that attach a shared 
memory segment with the same key will have the corresponding page table entr[ies] mapped to the same 
physical frame[s].

This 12-byte memory region can be specified by the following C struct 
struct{ 
   int recv_count; 
   int send_count; 
   char buf[4]; 
}; 

The client program shall send user typed-in messages correctly to the server. The server will print 
out the received messages. There shall be no missing, duplicate, or out of order chunks.  
