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

void disk_read(char *filename) {

    //we arrived to this conclusion based on our results from the part6.py script which showed that 4096 had the fastest performace rate

    int block_size = 4096;
    int fd = open(filename, O_RDONLY);

    //divide byte size of unsigned int and round up using ceiling
    int size = ceil(block_size/(long)sizeof(unsigned int));
    unsigned int buf[size];

    unsigned int xor = 0;
    int r;
    unsigned int mem;

    while ((r=read(fd, buf, block_size)) > 0) {

        //printf("r value:%u",r);

        mem = ceil(r/sizeof(unsigned int));
        //printf(" Iteration_memory:%u",mem);

        xor ^= xorbuf(buf, mem);

        //printf(" block_count:%u",block_count);

        //printf("\n");

        continue;
    }
    
    printf("xor: %08x\n", xor);
    close(fd);
}

void error() {
    printf("%s","Please enter the arguments in this order <filename>");
}
 
int main(int argc, char *argv[]) {
    char * filename;
    //clock_t t;

    if (argc != 2) {
        error();
    }

    // arg[0] isnt parsed

    //filename
    filename = argv[1];

    //t = clock();
    disk_read(filename);
    //t = clock() - t;
    //double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    //printf("The program took %f seconds to execute", time_taken);
    //printf("\n");

}