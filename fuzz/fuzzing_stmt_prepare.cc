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
          		return 0; //ce n'est pas une erreur en soi
      	}

    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);

    if (stmt && mysql_stmt_prepare(stmt, "SELECT * FROM Cars",(ulong)strlen("SELECT * FROM Cars")))
    {
    	printf("Error:%d %s\n",mysql_errno(&mysql),mysql_error(&mysql));
    }
    
    mysql_stmt_close(stmt);
    mysql_close(&mysql);
    
    return 0;
}
