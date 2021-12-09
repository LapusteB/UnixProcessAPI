#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>


#define BUFFSIZE 1024

typedef struct BLOCK{
    int recv_count;
    int send_count;
    char buff[4];
}msgBLOCK;

void send_Block(int ID)
{
    printf("Attaching memory segmentation...\n");
    msgBLOCK *msg;
    msg = (msgBLOCK *) shmat(ID, NULL, 0);
    if ((char *) msg == (char *)-1)
    {
        printf("shmat Error");
        return;
    }
    printf("Memory segmentation complete...\n");

    char IO[100];
    printf("Enter Message: ");
    fgets(IO, BUFFSIZE, stdin);
    
    while(*IO != '\n')
    {
        int i = 0;
        while(i+4 <= strlen(IO))
        {
            while(msg->send_count > msg->recv_count);
                for(int j=0; j<4; j++)
                {
                    msg->buff[j] = IO[i+j];
                }
            
            msg->send_count++;
            i+=4;
        }
        while(msg->send_count > msg->recv_count);
        int flag = 0;
        while( i < strlen(IO))
        {
            msg->buff[flag] = IO[i];
            i++;
            flag++;
        }
        for(flag; flag<4; flag++)
        {
            msg->buff[flag] = NULL;
        }
        msg->send_count++;
        printf("Message Sent\n");
        printf("Enter Message: ");
        fgets(IO, BUFFSIZE, stdin);  
    }
    if(shmdt(msg) < 0)
    {
        printf("error messageBLOCK...\n");
        return;
    }

}

int main(int argc, char *argv[])
{   
    int key = atoi(argv[1]);
    printf("Acquiring shared memory...\n");
    int ID;
    ID = shmget(key, sizeof(msgBLOCK), 0666);
    if(ID == 0)
    {
        printf("Memory ID error");
        return -1;
    }

    printf("shared memory complete...\n");
    
    send_Block(ID);
    return 0;  
    
}


