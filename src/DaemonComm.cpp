/*
 * DaemonComm.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: migarna
 */

#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

#include "DaemonComm.h"

#define MAX_DAEMONAPI_RETRIES 50

DaemonComm::DaemonComm(const char* daemonpath, const char* socketpath) {
	if((socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
		return;

	strncpy(daemon_sock_path, daemonpath, SOCKET_PATH_MAX_LEN);

	fcntl(socket_fd, F_SETFD, FD_CLOEXEC);

	struct timeval now;
	int retries = 0;
	do {
	    if(gettimeofday(&now, NULL)){
			return;
		}
		srand(now.tv_sec+now.tv_usec);
		sprintf(sock_path, "%s%d", socketpath, (int)(100.0*rand()/(RAND_MAX)));
		retries ++;
	} while(!access(sock_path, R_OK) && retries < MAX_DAEMONAPI_RETRIES);

	if(retries == MAX_DAEMONAPI_RETRIES)
		unlink(sock_path);

	struct sockaddr_un sin;
	memset(&sin, 0x00, sizeof(struct sockaddr_un));
	sin.sun_family = AF_UNIX;
	strcpy(sin.sun_path, sock_path);

	if(bind(socket_fd, (struct sockaddr *)&sin, sizeof(struct sockaddr_un)))
		return;
}

DaemonComm::~DaemonComm() {
	close(socket_fd);
	unlink(sock_path);
}

void DaemonComm::set_sock_addr(struct sockaddr_un* to, struct sockaddr_un* from, char* socket_path)
{
	memset(to, 0x00, sizeof(struct sockaddr_un));
	memset(from, 0x00, sizeof(struct sockaddr_un));
	to->sun_family = from->sun_family = AF_UNIX;
	strcpy(to->sun_path, socket_path);
}

int DaemonComm::send_request(void* reqmsg, size_t reqmsglen, void* respmsg, size_t respmsglen)
{
	// Variable definition section
	struct sockaddr_un	to, from;
	socklen_t fromlen;

	// Initialize the socket
	set_sock_addr(&to, &from, daemon_sock_path);

	// Send it
	if(sendto(socket_fd, reqmsg, reqmsglen, 0, (struct sockaddr *)&to, sizeof(to)) < 0 )
		return -1;

	// Receive the answer
	fromlen = sizeof(struct sockaddr_un);
	if(recvfrom(socket_fd, respmsg, respmsglen, 0, (struct sockaddr *)&from, &fromlen) < 0)
		return -1;

	return 0;
}
