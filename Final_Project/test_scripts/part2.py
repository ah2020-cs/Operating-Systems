import os
import datetime as datetime
import pandas
import sys
import time

def main():

    write_block_size = 1024
    write_block_count = 10
    runtime=0

    while runtime<10:
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
        print("block size:" + str(write_block_size) + " block count:" + str(write_block_count)) 
        print("runtime: " + str(runtime) + " seconds")
        print("")
        os.remove(name)
        write_block_count*=5

if __name__ == "__main__":
    main()