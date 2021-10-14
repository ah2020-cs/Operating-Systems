//This is the implementation of the uniq command in C

#include "types.h"
#include "stat.h"
#include "user.h"

char buff[1000000];
char* arg;
char* arg2;

int uniq(int fd, char *name) {
    int n,i,j,a,b;
    int count =0,lcount =0,iterr =0,count1 =0,lcount1 =0;
    
    char *result[10000];
    char d_buff[10000];
    int dup[10000];
    char up_buff[10000];
    char copyout[10000];

    while((n = read(fd, buff, sizeof(buff))) >0) {
        buff[n] = '\n';
        buff[n+1] = '\0';
        for(i=0; i<n+1; i++) { 
            if(buff[i] == '\n') {  //Counts # of lines in the file
                lcount++;
            }
        }
        for(i=0;buff[i] != '\n';i++){ //fills the first line of the dummy buffer
            count ++;
            d_buff[i] = buff[i];
        }

        d_buff[i] = '\0';
        dup[0]=1; 
        result[0] = (char*) malloc((count+1)*sizeof(char*)); 

        for(i=0;i<count+1;i++) { //puts the first line in the final list without duplicates
            result[iterr][i] = d_buff[i]; 
        }
        a=i;
        while(lcount1 < lcount-1) { //iterates over each line minus the first
            b=0;
            count1 = 0;
            for(i=a;buff[i] != '\n';i++) { //adds the current line to check to the dummy buffer
                count1++;
                d_buff[b] = buff[i];
                b++;
            }
            a = a+count1+1; //moves to the start of the next line
            
            if(strcmp(arg,"-i") == 0 ||strcmp(arg2,"-i") == 0 ){ //lower case chars are changed to upper
                for(j=0;j<count1;j++) {
                    if(result[iterr][j] >= 97){
                        copyout[j] = result[iterr][j]-32;
                    }else {
                        copyout[j] = result[iterr][j]; 
                    }
                    if(d_buff[j] >= 97){
                        up_buff[j] = d_buff[j]-32;
                    }else {
                        up_buff[j] = d_buff[j];
                    }
                }
                if(strcmp(copyout,up_buff) != 0) { //check for no duplicate
                    iterr = iterr+1;
                    result[iterr] = (char*) malloc((count1+1)*sizeof(char*));
                    for(j=0;j<count1;j++) {
                        result[iterr][j]=d_buff[j];
                    }
                    dup[iterr] = 1; 
                } else {
                    dup[iterr] = dup[iterr] + 1;
                }
            }else if(strcmp(result[iterr],d_buff) != 0) { //check for no duplicate
                iterr = iterr+1;
                result[iterr] = (char*) malloc((count1+1)*sizeof(char*));
                for(j=0;j<count1;j++) {
                    result[iterr][j]=d_buff[j];
                }
                dup[iterr] = 1; 
            } else {
                dup[iterr] = dup[iterr] + 1;
            }
            lcount1++; //goes to 1
        }
    } 

    if(strcmp(arg,"-c") == 0 ||strcmp(arg2,"-c") == 0) {
            for(i=0;i<iterr+1;i++) {
                printf(1, "%d %s \n",dup[i],result[i]); 
            }
    }else if(strcmp(arg,"-d") == 0||strcmp(arg2,"-d") == 0){
        for(i=0;i<iterr+1;i++) {
            if(dup[i] > 1) {
                printf(1, "%s \n",result[i]);
            }
        }      
    }else {
        for(i=0;i<iterr+1;i++) {
            printf(1, "%s \n", result[i]);
        }
    }
    free(result);
    return 0;
}

int main (int argc, char* argv[]) {
    int fd, i;

    if(argc <=1) {
        uniq(0,"");
        exit();
    }
    else if(argc == 4){
        for( i = 3; i< argc; i++) {
            if((fd = open(argv[i],0))<0) { 
                printf(1, "File cannot be opened\n"); 
            }
            else {
                arg=argv[1];
                arg2=argv[2];
                uniq(fd,argv[i]);
            }
            close(fd);
        } 
    } else {
        for(i=1; i<argc; i++) {
            if((fd = open(argv[i],0)) < 0) {
                //printf(1, "File cannot be opened\n");  
            } else {
                arg=argv[1];
                arg2=argv[2];
                uniq(fd,argv[i]);
            }
            close(fd);
        }
    }
    exit();
}
