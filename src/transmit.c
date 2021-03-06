#ifdef __unix__
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <netinet/in.h>

	#define OS_UNIX
#elif defined(_WIN32) || defined(WIN32)
	#include <winsock2.h>

	#define OS_WINDOWS
#endif

#include <stdio.h>
#include "debug.h"

/**
 * send_data - Sends character array to socket server
 * @sock - Socket to send message to
 * @msg - Character array to send
 *
 * Returns 0 on succes or -1 on error
 */
int send_data(int sock, const char* msg)
{
	int msg_len = strlen(msg);

	int send_bytes = send(sock, msg, msg_len, 0);

	if (send_bytes == 0) {
		FEATHER_DBG_PRINT("ERROR: No bytes have been send\n");
		return -1;
	} else if (send_bytes < 0) {
		FEATHER_DBG_PRINT(("ERROR: An error has occured while "
                "trying to send a message:\n%s\n", msg));
		return -1;
	}

	return 0;
}

/**
 * receive_data - Receives message from socket
 * @sock - Socket to receive a message from
 * @buf - Character array to fill with the message
 * @buf_len - Length of the buffer @buf
 *
 * Returns the amount of bytes received on succes 
 * or -1 on error.
 */
int receive_data(int sock, char* buf, int buf_len)
{
	int recv_bytes = recv(sock, buf, buf_len - 1, 0);
	if (recv_bytes < 1) {
        FEATHER_DBG_PRINT("ERROR: An error occured while "
                "receiving a message\n");
		return -1;
	}

    buf[recv_bytes] = '\0';
	return recv_bytes;
}
