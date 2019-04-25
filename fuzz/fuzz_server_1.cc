#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <mysql.h>
#include <mysql/client_plugin.h>
#include <mysqld_error.h>
#include "violite.h"
#include <unistd.h>

#include "sql/conn_handler/fuzz_connection.cc"
#include "sql/conn_handler/channel_info.h"                // Channel_info
#include "sql/conn_handler/connection_handler_manager.h"  // Connection_handler_manager


using namespace std;

extern int mysqld_main(int argc, char **argv);

static int result = 0;

void *main_serv(void *arg) {
	int argc = 4;
	const char **argv = (const char**)malloc(argc*sizeof(const char*));
	argv[0]="mysqld";
	argv[1]="--basedir=./basedirserver";
	argv[2]="--datadir=./basedirserver/datadirserver";
	argv[3]="--user=root";


	result = mysqld_main(argc, (char**)argv);

	free(argv);
	printf("Server closed\n");
	return NULL;
}


int init_serv() {
	pthread_t thr;
	printf("0\n");
	if (pthread_create(&thr, NULL, main_serv, NULL)) {
		printf("1\n");
		printf("Error creating server thread\n");		
		return 1;
	}

	sleep(10);
	return 0;
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  //static int inits = init_serv();
  //if (inits) return inits;

  //Connection_handler_manager *mgr =
  //      Connection_handler_manager::get_instance();
  Channel_info *channel_info = new Channel_info_fuzz((uint8_t*)Data, Size);
	printf("1\n");
 // if (channel_info != NULL) mgr->process_new_connection(channel_info);

	THD *thd = channel_info->create_thd();

	printf("2\n");
//	mgr->wait_till_no_connection();
//	printf("End!\n");
  return result;
}

