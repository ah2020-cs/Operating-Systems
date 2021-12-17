import os
import datetime as datetime
import pandas
import sys
import time

def _test(num):

    write_block_size = num
    write_block_count = 500
    runtime=0
    count=0

    while count<=6:
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
        print("MiB/s:" + str(rate))
        print("")
        count+=1
        os.remove(name)
        write_block_count*=5


def main():

    _test(512)
    _test(1024)
    _test(2048)


if __name__ == "__main__":
    main()