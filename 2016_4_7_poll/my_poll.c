#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<poll.h>
int main()
{
	int read_fd=0;
	int write_fd=1;
	struct pollfd _poll_fd[2];
	_poll_fd[0].fd=read_fd;
	_poll_fd[1].fd=write_fd;
	_poll_fd[0].events=POLLIN;
	_poll_fd[1].events=POLLOUT;
	_poll_fd[0].revents=0;
	_poll_fd[1].revents=0;
	nfds_t fds=2;
	int timeout=1000;
	char buf[1024];
	memset(buf,'\0',sizeof(buf));
	while(1){
		switch(poll(_poll_fd,2,timeout)){
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					//int i=0;
					if((_poll_fd[0].revents) & (POLLIN)){
						ssize_t _size=read(0,buf,sizeof(buf)-1);
						if(_size>0){
							buf[_size]='\0';
						if((_poll_fd[1].revents) & (POLLOUT)){
							printf("%s\n",buf);
						}
						}
					}
				}
				break;
		}
	}
	return 0;
}
