/*
   Copyright (c) 2013, 2018, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/


#include "my_config.h"

#include <errno.h>
#include <fcntl.h>

#ifndef _WIN32
#include <netdb.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <algorithm>
#include <atomic>
#include <new>
#include <utility>
#include "sql/auth/sql_security_ctx.h"

#include "sql/mysqld.h"
#include "m_string.h"
#include "my_dbug.h"
#include "my_io.h"
#include "my_loglevel.h"
#include "my_sys.h"
#include "my_thread.h"
#include "mysql/psi/mysql_thread.h"
#include "mysqld_error.h"
#include "sql/conn_handler/channel_info.h"               // Channel_info
#include "sql/conn_handler/init_net_server_extension.h"  // init_net_server_extension
#include "sql/sql_class.h"  // THD
#include "sql/sql_const.h"
#include "violite.h"  // Vio

#include "connection_handler_manager.h"

using std::max;






class Channel_info_fuzz : public Channel_info {
  // connect socket object
  uint8_t *buffer;
  size_t size;

 protected:
  virtual Vio *create_and_init_vio() const {
   // Vio *vio =
   //     mysql_socket_vio_new(m_connect_sock, VIO_TYPE_SOCKET, VIO_LOCALHOST);
    Vio *vio = vio_new(0, VIO_TYPE_FUZZ, 0);
    return vio;
  }

 public:
  /**
    Constructor that sets the connect socket.

    @param connect_socket set connect socket descriptor.
  */
  Channel_info_fuzz(uint8_t *bufferParam, size_t sizeParam) {
    buffer=bufferParam;
    size=sizeParam;
    sock_initfuzz((const uint8_t*)buffer, size);
  }

  virtual THD *create_thd() {
    THD *thd = Channel_info::create_thd();

    if (thd != NULL) {
      init_net_server_extension(thd);
      thd->security_context()->set_host_ptr(my_localhost, strlen(my_localhost));
    }
    return thd;
  }

  virtual void send_error_and_close_channel(uint errorcode, int error,
                                            bool senderror) {
    Channel_info::send_error_and_close_channel(errorcode, error, senderror);

    //There were some close there...
  }
};