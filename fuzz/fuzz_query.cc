#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "sql/sql_class.h"
#include "sql/sql_prepare.h"

extern "C" int LLVMFuzzerTestQueryInput(const uint8_t* data,size_t size){
	size_t offset = 0;
	size_t sizereq = 0;
	THD *thd = new THD();
	thd->thread_stack = (char *)&thd;
	thd->store_globals();
	thd->reset_for_next_command();
	while (offset+sizereq < size) {
		sizereq++;
		if (data[offset+sizereq-1] == 0) {
			Prepared_statement *stmt; 
			stmt = new Prepared_statement(thd);
			mysqld_stmt_prepare(thd,(const char*)data+offset,sizereq,stmt);
			delete stmt;
			offset+=sizereq;
			sizereq = 0;
		}
	}
	delete thd;
	return 0; 
}