#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sql_main.h>

extern "C" int LLVMFuzzerTestQueryInput(const uint8_t data,size_t size){
	// MYSQL *mysql;
	int i;
	int j = 0;
	size_t offset = 0;
	size_t sizereq = 0;
	THD *thd = new THD();
	thd->thread_stack = (char *)&thd;
	thd->store_globals();
	thd->reset_for_next_command();
	// mysql_stmt_precheck(thd, com_data, command, &stmt);
	// dispatch_command(NULL,NULL,0);
	while (offset+sizereq < size) {
		sizereq++;
		if (data[offset+sizereq-1] == 0) {
			Prepare_statement *stmt; 
			stmt = new Prepared_statement(thd);
			mysqld_stmt_prepare(thd,data+offset,sizereq,stmt);
			delete stmt;
			offset+=sizereq;
			sizereq = 0;
		}
	}
	delete thd;
	return 0; 
}