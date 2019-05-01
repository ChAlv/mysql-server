#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <mysql.h>
#include <mysql/client_plugin.h>
#include <mysqld_error.h>
#include "violite.h"

int main() {
  MYSQL mysql;
  mysql_init(&mysql);
  mysql.options.protocol = MYSQL_PROTOCOL_TCP;
    if (!mysql_real_connect(&mysql,"localhost","root","root","",1232,NULL,0)) {
		mysql_error(&mysql)); 
      		return 0;
  	}

  mysql_query(&mysql, "SELECT * FROM Cars")
  mysql_close(&mysql);
  return 0;
}

