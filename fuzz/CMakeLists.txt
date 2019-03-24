

MYSQL_ADD_EXECUTABLE(fuzzing_network_1 fuzzing_network_1.cc)
TARGET_LINK_LIBRARIES(fuzzing_network_1 library_mysys)
TARGET_LINK_LIBRARIES(fuzzing_network_1 mysqlclient)
TARGET_LINK_LIBRARIES(fuzzing_network_1 FuzzingEngine)

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




MYSQL_ADD_EXECUTABLE(fuzzing_stmt_prepare fuzzing_stmt_prepare.cc)
TARGET_LINK_LIBRARIES(fuzzing_stmt_prepare library_mysys)
TARGET_LINK_LIBRARIES(fuzzing_stmt_prepare mysqlclient)
TARGET_LINK_LIBRARIES(fuzzing_stmt_prepare FuzzingEngine)