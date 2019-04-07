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

    if (!mysql_real_connect(&mysql,"localhost","root","root","",0,NULL,0))
    {
          		return 0; //ce n'est pas une erreur en soi
    }

    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
    if (!stmt)
    {
      printf(" mysql_stmt_init(), out of memory\n");
      mysql_stmt_close(stmt);
      mysql_close(&mysql);
      return 0;
    }
    if (mysql_stmt_prepare(stmt, "SELECT * FROM Cars",(ulong)strlen("SELECT * FROM Cars")))
    {
        //printf("Error:%d %s\n",mysql_errno(&mysql),mysql_error(&mysql));
        printf(" %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&mysql);
        return 0;
    }
    if (mysql_stmt_execute(stmt))
    {
        printf(" %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&mysql);
        return 0;
    }
    MYSQL_RES     *prepare_meta_result;
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        printf(" %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&mysql);
        return 0;
    }

    int column_count;
    column_count= mysql_num_fields(prepare_meta_result);
    MYSQL_BIND    bind[column_count];
    memset(bind, 0, sizeof(bind));
    if (mysql_stmt_bind_result(stmt, bind))
    {
      printf(" mysql_stmt_bind_result() failed\n");
      printf(" %s\n", mysql_stmt_error(stmt));
      mysql_free_result(prepare_meta_result);
      mysql_stmt_close(stmt);
      mysql_close(&mysql);
      return 0;
    }
    while (!mysql_stmt_fetch(stmt))
    {
     }


    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(&mysql);
    
    return 0;
}
