# Install script for directory: /home/csoyee/git/mysql-dwblr-salloc/man

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xManPagesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man1" TYPE FILE FILES
    "/home/csoyee/git/mysql-dwblr-salloc/man/comp_err.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/innochecksum.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/msql2mysql.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/my_print_defaults.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/myisam_ftdump.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/myisamchk.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/myisamlog.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/myisampack.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql-stress-test.pl.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql-test-run.pl.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql.server.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_client_test.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_client_test_embedded.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_config.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_config_editor.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_convert_table_format.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_find_rows.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_fix_extensions.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_install_db.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_plugin.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_secure_installation.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_setpermission.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_tzinfo_to_sql.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_upgrade.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_waitpid.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysql_zap.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlaccess.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqladmin.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlbinlog.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlbug.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlcheck.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqld_multi.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqld_safe.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqldump.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqldumpslow.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlhotcopy.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlimport.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlman.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlshow.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqlslap.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqltest.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/mysqltest_embedded.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/perror.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/replace.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/resolve_stack_dump.1"
    "/home/csoyee/git/mysql-dwblr-salloc/man/resolveip.1"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xManPagesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/man/man8" TYPE FILE FILES "/home/csoyee/git/mysql-dwblr-salloc/man/mysqld.8")
endif()

