#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// From the sample code
unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
        //printf("%u",result);
    }
    return result;
}

void disk_read(char *filename, int block_size, int block_count) {

    int fd = open(filename, O_RDONLY);

    //divide byte size of unsigned int and round up using ceiling
    int size = ceil(block_size/(long)sizeof(unsigned int));
    unsigned int buf[size];

    unsigned int xor = 0;
    int r;
    unsigned int mem;

    while (((r=read(fd, buf, block_size)) > 0) && (block_count != 0)) {

        //printf("r value:%u",r);

        mem = ceil(r/sizeof(unsigned int));
        //printf(" Iteration_memory:%u",mem);

        xor ^= xorbuf(buf, mem);
        block_count-=1;
        //printf(" block_count:%u",block_count);

        //printf("\n");

        continue;
    }
    
    printf("xor: %08x\n", xor);
    close(fd);
}

void disk_write(char *filename, int block_size, int block_count){
    int fd = open(filename, O_CREAT|O_WRONLY, 777);
    char buf[block_size];

    for (int i=0; i < block_count; i++) {
        for (int j=0; j < block_size; j++) {
            buf[j] = 'x';
        }
        write(fd, buf, block_size);
    }
    close(fd);
}

void error() {
    printf("%s","Please enter the arguments in this order <filename> [-r|-w] <block_size> <block_count>");
}
 
int main(int argc, char *argv[]) {
    char * filename;
    char flag;
    int block_size;
    int block_count;
    clock_t t;

    if (argc != 5) {
        error();
    }

    // arg[0] isnt parsed

    //filename
    filename = argv[1];

    // read|write flag has to have atleast 2 characters 
    if (strlen((argv[2])) != 2) {
        error();
    }
    else {
    	//if correct you parse in the flag
        flag = argv[2][1];
    }

    //convert to int
    block_size = atoi(argv[3]);
    block_count = atoi(argv[4]);

    if (flag == 'r') {
        //disk_read(filename, block_size, block_count);
        t = clock();
        disk_read(filename, block_size, block_count);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
        //printf("The program took %f seconds to execute", time_taken);
        //printf("\n");
    }
    else if (flag == 'w') {
        disk_write(filename, block_size, block_count);  
    }

}