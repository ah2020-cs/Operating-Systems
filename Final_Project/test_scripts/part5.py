import os
import datetime as datetime
import pandas
import sys
import time

def _block1():

    write_block_size = 1
    write_block_count = 100
    #df = pandas.DataFrame()
    runtime=0
    count=0

    while count<6:
        runtime=0

        name = 'temp.txt'
        #change the compiled file names below
        os.system(f"./run {name} -w {write_block_size} {write_block_count}")

        start = time.time()
        os.system(f"./run {name} -r {write_block_size} {write_block_count}")
        finish = time.time()
        runtime = (finish - start)
        filesize = write_block_size * write_block_count


        print("filesize:" + str(filesize) + " bytes")
        print("block_size:" + str(write_block_size) + "  block_count:" + str(write_block_count)) 
        print("runtime: " + str(runtime) + " seconds")
        rate = (filesize/float(1000000))/float(runtime)
        print("System calls - B/s:" + str(rate*1000000))
        print("MiB/s:" + str(rate))
        print("")

        os.remove(name)
        write_block_count*=10
        count+=1


def _block1_lseek():

    write_block_size = 1
    write_block_count = 100
    #df = pandas.DataFrame()
    runtime=0
    count=0

    while count<6:
        runtime=0

        name = 'temp.txt'
        #change the compiled file names below
        os.system(f"./run_part5 {name} -w {write_block_size} {write_block_count}")

        start = time.time()
        os.system(f"./run_part5 {name} -r {write_block_size} {write_block_count}")
        finish = time.time()
        runtime = (finish - start)
        filesize = write_block_size * write_block_count


        print("filesize:" + str(filesize) + " bytes")
        print("block_size:" + str(write_block_size) + "  block_count:" + str(write_block_count)) 
        print("runtime: " + str(runtime) + " seconds")
        rate = (filesize/float(1000000))/float(runtime)
        print("System calls - B/s:" + str(rate*1000000))
        print("MiB/s:" + str(rate))
        print("")

        os.remove(name)
        write_block_count*=10
        count+=1


def main():
    _block1()
    print("")
    _block1_lseek()

if __name__ == "__main__":
    main()