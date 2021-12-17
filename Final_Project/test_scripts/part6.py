import os
import datetime as datetime
import pandas
import sys
import time
import math

def _test(num):

    read_block_size = num
    #write_block_count = 1000
    sz=1000
    #df = pandas.DataFrame()
    runtime=0
    count=0

    while count<3:
        runtime=0

        name = 'temp.txt'
        #change the compiled file names below
        os.system(f"./run {name} -w {sz} {sz}")

        read_block_count = math.ceil((sz*sz)/read_block_size)

        start = time.time()
        os.system(f"./run {name} -r {read_block_size} {read_block_count}")
        finish = time.time()
        runtime = (finish - start)
        filesize = sz * sz

        print("filesize:" + str(filesize) + " bytes")
        print("block_size:" + str(read_block_size) + "  block_count:" + str(read_block_count)) 

        print("runtime: " + str(runtime) + " seconds")
        rate = (filesize/float(1000000))/float(runtime)
        print("MiB/s:" + str(rate))
        print("")
        count+=1
        sz*=10
        os.remove(name)


def main():

    _test(512)
    _test(1024)
    _test(2048)
    _test(4096)
    _test(8192)

if __name__ == "__main__":
    main()