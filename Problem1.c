#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{   
    
    char *lines;
    lines = malloc(sizeof(char*));
    int space_end = 0;
   
    fgets(lines, 50, stdin);
    int s = 0;
    for(int i = 0; i <strlen(lines); i++)
    {
        if(lines[i] == ' ')
        {
            s++;
        }
    }

    char args[s+1][50];
    for(int i = 0; i < s+1; i++)
    {
        int columns = 0;
        while(lines[space_end + columns] != ' ')
        {
            if(lines[space_end + columns] == '\0' || lines[space_end + columns] == '\n')
            {
                break;
            }
        args[i][columns] = lines[space_end + columns];
        columns++;
        }
        space_end += columns+1;
        args[i][columns] = '\0';
    }
    char* argF[s+2];
    argF[s+2];
    for(int i = 0; i < s+1; i++)
    {
        argF[i] = args[i];
    }


    //later..
    argF[s+2] = '\0';
    int id = fork();
    if(id == 0)
    {
        execvp(argF[0], argF);
    }else{
        wait(&id);
        printf("++++\n");
    }
}