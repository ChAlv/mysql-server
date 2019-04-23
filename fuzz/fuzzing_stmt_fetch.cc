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
    MYSQL_BIND    bind[4];
    MYSQL_RES     *prepare_meta_result;
    MYSQL_TIME    ts;
    unsigned long length[4];
    int           param_count, column_count, row_count;
    short         small_data;
    int           int_data;
    char          str_data[STRING_SIZE];
    bool          is_null[4];
    bool          error[4];
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
      mysql_stmt_close(stmt);
      mysql_close(&mysql);
      return 0;
    }
    if (mysql_stmt_prepare(stmt, "SELECT col1, col2, col3, col4 FROM Cars",(ulong)strlen("SELECT col1, col2, col3, col4 FROM Cars")))
    {
        mysql_stmt_close(stmt);
        mysql_close(&mysql);
        return 0;
    }
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
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
    column_count= mysql_num_fields(prepare_meta_result);
    memset(bind, 0, sizeof(bind));
    /* INTEGER COLUMN */
    bind[0].buffer_type= MYSQL_TYPE_LONG;
    bind[0].buffer= (char *)&int_data;
    bind[0].is_null= &is_null[0];
    bind[0].length= &length[0];
    bind[0].error= &error[0];

    /* STRING COLUMN */
    bind[1].buffer_type= MYSQL_TYPE_STRING;
    bind[1].buffer= (char *)str_data;
    bind[1].buffer_length= STRING_SIZE;
    bind[1].is_null= &is_null[1];
    bind[1].length= &length[1];
    bind[1].error= &error[1];

    /* SMALLINT COLUMN */
    bind[2].buffer_type= MYSQL_TYPE_SHORT;
    bind[2].buffer= (char *)&small_data;
    bind[2].is_null= &is_null[2];
    bind[2].length= &length[2];
    bind[2].error= &error[2];

    /* TIMESTAMP COLUMN */
    bind[3].buffer_type= MYSQL_TYPE_TIMESTAMP;
    bind[3].buffer= (char *)&ts;
    bind[3].is_null= &is_null[3];
    bind[3].length= &length[3];
    bind[3].error= &error[3];

    if (mysql_stmt_bind_result(stmt, bind))
    {
      mysql_free_result(prepare_meta_result);
      mysql_stmt_close(stmt);
      mysql_close(&mysql);
      return 0;
    }
    if (mysql_stmt_store_result(stmt))
    {
      mysql_free_result(prepare_meta_result);
            mysql_stmt_close(stmt);
            mysql_close(&mysql);
            return 0;
    }
    while (!mysql_stmt_fetch(stmt))
    {
    row_count++;

      /* column 1 */
      fprintf(stdout, "   column1 (integer)  : ");
      if (is_null[0])
        fprintf(stdout, " NULL\n");
      else
        fprintf(stdout, " %d(%ld)\n", int_data, length[0]);

      /* column 2 */
      fprintf(stdout, "   column2 (string)   : ");
      if (is_null[1])
        fprintf(stdout, " NULL\n");
      else
        fprintf(stdout, " %s(%ld)\n", str_data, length[1]);

      /* column 3 */
      fprintf(stdout, "   column3 (smallint) : ");
      if (is_null[2])
        fprintf(stdout, " NULL\n");
      else
        fprintf(stdout, " %d(%ld)\n", small_data, length[2]);

      /* column 4 */
      fprintf(stdout, "   column4 (timestamp): ");
      if (is_null[3])
        fprintf(stdout, " NULL\n");
      else
        fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d (%ld)\n",
                         ts.year, ts.month, ts.day,
                         ts.hour, ts.minute, ts.second,
                         length[3]);
      fprintf(stdout, "\n");
     }


    mysql_free_result(prepare_meta_result);
    mysql_stmt_close(stmt);
    mysql_close(&mysql);
    
    return 0;
}
