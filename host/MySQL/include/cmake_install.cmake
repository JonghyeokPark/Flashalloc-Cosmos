# Install script for directory: /home/csoyee/git/mysql-dwblr-salloc/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local/mysql")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql_com.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql_time.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_list.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_alloc.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/typelib.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql/plugin.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql/plugin_audit.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql/plugin_ftparser.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql/plugin_validate_password.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_dbug.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/m_string.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_sys.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_xml.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql_embed.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_pthread.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/decimal.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/errmsg.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_global.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_net.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_getopt.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/sslopt-longopts.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_dir.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/sslopt-vars.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/sslopt-case.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/sql_common.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/keycache.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/m_ctype.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_attribute.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_compiler.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql_com_server.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_byteorder.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/byte_order_generic.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/byte_order_generic_x86.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/byte_order_generic_x86_64.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/little_endian.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/big_endian.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysql_version.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/my_config.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysqld_ername.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/mysqld_error.h"
    "/home/csoyee/git/mysql-dwblr-salloc/include/sql_state.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelopmentx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mysql" TYPE DIRECTORY FILES "/home/csoyee/git/mysql-dwblr-salloc/include/mysql/" REGEX "/[^/]*\\.h$" REGEX "/psi\\_abi[^/]*$" EXCLUDE)
endif()

