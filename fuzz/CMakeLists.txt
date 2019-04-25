IF (FUZZING)
MYSQL_ADD_EXECUTABLE(fuzz_network_1 fuzz_network_1.cc)
TARGET_LINK_LIBRARIES(fuzz_network_1 mysqlclient)
TARGET_LINK_LIBRARIES(fuzz_network_1 FuzzingEngine)

#SET(LIBFUZZER_LIBRARIES FuzzingEngine)

#MYSQL_ADD_EXECUTABLE(fuzz_router_uri fuzz_router_uri.cc
  #                      ${PROJECT_SOURCE_DIR}/router/src/router/src/uri.cc
 #                         ${PROJECT_SOURCE_DIR}/router/src/router/src/utils.cc)

#TARGET_LINK_LIBRARIES(fuzz_router_uri harness-library ${MySQL_CLIENT_LIB}
   #                     ${SSL_LIBRARIES} ${LIBFUZZER_LIBRARIES})
  #TARGET_INCLUDE_DIRECTORIES(fuzz_router_uri
  #  PRIVATE
 #   ${PROJECT_SOURCE_DIR}/router/src/router/include/)


#MYSQL_ADD_EXECUTABLE(fuzz_router_uri_tostring
    #fuzz_router_uri_tostring.cc
   # ${PROJECT_SOURCE_DIR}/router/src/router/src/uri.cc
  #  ${PROJECT_SOURCE_DIR}/router/src/router/src/utils.cc
 # )

#TARGET_LINK_LIBRARIES(fuzz_router_uri_tostring harness-library ${MySQL_CLIENT_LIB}
   #                     ${SSL_LIBRARIES} ${LIBFUZZER_LIBRARIES})
  #TARGET_INCLUDE_DIRECTORIES(fuzz_router_uri_tostring
 #   PRIVATE
#    ${PROJECT_SOURCE_DIR}/router/src/router/include/)

MYSQL_ADD_EXECUTABLE(fuzz_real_query fuzz_real_query.cc)
TARGET_LINK_LIBRARIES(fuzz_real_query library_mysys)
TARGET_LINK_LIBRARIES(fuzz_real_query mysqlclient)
TARGET_LINK_LIBRARIES(fuzz_real_query FuzzingEngine)

MYSQL_ADD_EXECUTABLE(fuzz_stmt_fetch fuzz_stmt_fetch.cc)
TARGET_LINK_LIBRARIES(fuzz_stmt_fetch library_mysys)
TARGET_LINK_LIBRARIES(fuzz_stmt_fetch mysqlclient)
TARGET_LINK_LIBRARIES(fuzz_stmt_fetch FuzzingEngine)

MYSQL_ADD_EXECUTABLE(fuzz_stmt_execute fuzz_stmt_execute.cc)
TARGET_LINK_LIBRARIES(fuzz_stmt_execute library_mysys)
TARGET_LINK_LIBRARIES(fuzz_stmt_execute mysqlclient)
TARGET_LINK_LIBRARIES(fuzz_stmt_execute FuzzingEngine)

MYSQL_ADD_EXECUTABLE(fuzzQuery fuzzQuery.cc)
TARGET_LINK_LIBRARIES(fuzzQuery sql_main)
TARGET_LINK_LIBRARIES(fuzzQuery libbinlogevents)
TARGET_LINK_LIBRARIES(fuzzQuery FuzzingEngine)
ENDIF()

ADD_SUBDIRECTORY(client_fuzz)
ADD_SUBDIRECTORY(server_fuzz)
ADD_SUBDIRECTORY(debug)
