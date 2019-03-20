
#include "my_config.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#ifndef _WIN32
#include <netdb.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#include "my_compiler.h"
#include "my_dbug.h"
#include "my_inttypes.h"
#include "my_io.h"
#include "my_macros.h"
#include "vio/vio_priv.h"

#ifdef FIONREAD_IN_SYS_FILIO
#include <sys/filio.h>
#endif
#ifndef _WIN32
#include <netinet/tcp.h>
#endif
#ifdef HAVE_POLL_H
#include <poll.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

//#include "mysql/psi/mysql_socket.h"


static const uint8_t *fuzzBuffer;
static size_t fuzzSize;
static size_t fuzzPos;


void sock_initfuzz(const uint8_t *Data, size_t Size) {
	fuzzPos = 0;
	fuzzSize = Size;
	fuzzBuffer = Data;
}

int fuzz_recv(void *bufp, size_t size) {
	if (size > fuzzSize - fuzzPos) {
		size = fuzzSize - fuzzPos;
	}
	if (fuzzPos < fuzzSize) {
		memcpy(bufp, fuzzBuffer + fuzzPos, size);
	}
	fuzzPos += size;
	return size;
}

bool vio_connect_fuzz(Vio *vio, struct sockaddr *addr, socklen_t len,
                        int timeout) {
  int ret, wait;
  int retry_count = 0;
  DBUG_ENTER("vio_socket_connect");

  /* Only for socket-based transport types. */
  DBUG_ASSERT(vio->type == VIO_TYPE_SOCKET || vio->type == VIO_TYPE_TCPIP);

  /* Initiate the connection. */
  ret=0;


  DBUG_RETURN(MY_TEST(ret));
}


int vio_socket_timeout_fuzz(Vio *vio, uint which, bool b) {
	DBUG_ENTER("Socket timeout\n");
	return 1;
}


size_t vio_read_buff_fuzz(Vio *vio, uchar *buf, size_t size) {
	DBUG_ENTER("Read buff.\n");
	return fuzz_recv(buf, size);
}
size_t vio_write_buff_fuzz(Vio *vio, const uchar *buf, size_t size) {
	DBUG_ENTER("Write buff\n");
	return size;
}


bool vio_is_connected_fuzz(Vio *vio) {
	DBUG_ENTER("Is connected.\n");
	return true;
}

bool vio_was_timeout_fuzz(Vio *vio) { 
	DBUG_ENTER("was timeout?\n");
	return false; 
}


int vio_shutdown_fuzz(Vio *vio) {
		  DBUG_ENTER("shutdown vio");

  DBUG_ENTER("Shutdown\n");
  int r = 0;
  return 0;
}

int vio_keepalive_fuzz(Vio *vio, bool set_keep_alive) {
  DBUG_ENTER("Keepalive\n");
  int r = 0;
  return r;
}
int vio_io_wait_fuzz(Vio *vio, enum enum_vio_io_event event, int timeout) {
	  DBUG_ENTER("vio_io_wait");
	return 1;
}

int vio_fastsend_fuzz(Vio *vio) {
	DBUG_ENTER("Fastsend\n");
	return 0;
}