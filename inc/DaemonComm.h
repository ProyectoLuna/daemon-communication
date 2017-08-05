/*
 * DaemonComm.h
 *
 *  Created on: Aug 5, 2017
 *      Author: migarna
 */

#ifndef DAEMONCOMM_H_
#define DAEMONCOMM_H_

#define SOCKET_PATH_MAX_LEN 32

class DaemonComm {
private:
	int	socket_fd;
	char sock_path[SOCKET_PATH_MAX_LEN];
	char daemon_sock_path[SOCKET_PATH_MAX_LEN];
	void set_sock_addr(struct sockaddr_un* to, struct sockaddr_un* from, char* socket_path);

public:
	DaemonComm(const char* daemonpath, const char* socketpath);
	virtual ~DaemonComm();
	int send_request(void* reqmsg, size_t reqmsglen, void* respmsg, size_t respmsglen);
};

#endif /* DAEMONCOMM_H_ */
