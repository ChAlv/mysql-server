<<<<<<< HEAD
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <mysql.h>
#include <mysql/client_plugin.h>
#include <mysqld_error.h>
#include "violite.h"




using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MYSQL mysql;
  mysql_init(&mysql);
  mysql.options.protocol = MYSQL_PROTOCOL_FUZZ;
  sock_initfuzz(Data,Size);

    if (!mysql_real_connect(&mysql,"localhost","root","root","",0,NULL,0)) {
	///	printf( "Failed to connect to MySQL: Error: %s\n",
	//	mysql_error(&mysql)); 
      		return 0; //ce n'est pas une erreur en soi
  	}



	//printf("Timeout : %d\n", mysql.thd.variables.net_wait_timeout);

  if (mysql_query(&mysql, "SELECT * FROM Cars")) 
  {
  	printf("Error:%d %s\n",mysql_errno(&mysql),mysql_error(&mysql));
  }
  mysql_close(&mysql);
  return 0;
}

||||||| merged common ancestors
=======
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <mysql.h>
#include <mysql/client_plugin.h>
#include <mysqld_error.h>
#include "violite.h"




using namespace std;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MYSQL mysql;
  mysql_init(&mysql);
  mysql.options.protocol = MYSQL_PROTOCOL_FUZZ;
  sock_initfuzz(Data,Size);

    if (!mysql_real_connect(&mysql,"localhost","root","root","",0,NULL,0)) {
            return 0;
    }

  mysql_query(&mysql, "SELECT * FROM Cars")
  mysql_close(&mysql);
  return 0;
}

>>>>>>> ca50e1017ecf832a4db73dd45382ac7d4b2b9d37
