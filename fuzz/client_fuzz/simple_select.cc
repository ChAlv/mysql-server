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
		printf( "Failed to connect to MySQL: Error: %s\n",
		mysql_error(&mysql)); 
      		return 0; //ce n'est pas une erreur en soi
  	}

  if (mysql_query(&mysql, "SELECT * FROM Cars")) 
  {
  	printf("Error:%d %s\n",mysql_errno(&mysql),mysql_error(&mysql));
  }
  mysql_close(&mysql);
  return 0;
}

