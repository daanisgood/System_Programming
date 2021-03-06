/*mycp program, by Choi Daan, dadols53@gmail.com*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#define MAX_BUF 64

int main(int argc, char *argv[]){
        int fd1, fd2, read_size, write_size;
        char buf[MAX_BUF];
        struct stat sb;

        if(argc != 3) {
                printf("USAGE : %s source_file destination_file\n", argv[0]);
                exit(-1);
        }
	if(stat(argv[1], &sb) == -1) {
		perror("stat");
		exit(-1);
	}

        fd1 = open(argv[1], O_RDONLY);
        if(fd1 < 0) {
                printf("Can not open %s. No such file\n", argv[1]);
                exit(-1);
        }

        fd2 = open(argv[2], O_RDWR | O_CREAT | O_EXCL, sb.st_mode);
        if(fd2 < 0) {
                printf("Can not create %s. May already exist\n", argv[2]);
                exit(-1);
        }

        while(1) {
                read_size = read(fd1, buf, MAX_BUF);
                if(read_size == 0) {
                        break;
                }
                write_size = write(fd2, buf, read_size);
        }

        close(fd1);
        close(fd2);
        return 0;
}
