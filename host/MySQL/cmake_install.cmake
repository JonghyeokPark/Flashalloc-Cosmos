# Install script for directory: /home/csoyee/git/mysql-dwblr-salloc

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xInfox" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE FILE OPTIONAL FILES "/home/csoyee/git/mysql-dwblr-salloc/Docs/mysql.info")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xReadmex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE OPTIONAL FILES
    "/home/csoyee/git/mysql-dwblr-salloc/COPYING"
    "/home/csoyee/git/mysql-dwblr-salloc/LICENSE.mysql"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xReadmex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "/home/csoyee/git/mysql-dwblr-salloc/README")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE FILE FILES
    "/home/csoyee/git/mysql-dwblr-salloc/Docs/INFO_SRC"
    "/home/csoyee/git/mysql-dwblr-salloc/Docs/INFO_BIN"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xReadmex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "/home/csoyee/git/mysql-dwblr-salloc/Docs/INSTALL-BINARY")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDocumentationx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/docs" TYPE DIRECTORY FILES "/home/csoyee/git/mysql-dwblr-salloc/Docs/" REGEX "/INSTALL\\-BINARY$" EXCLUDE REGEX "/Makefile\\.[^/]*$" EXCLUDE REGEX "/glibc[^/]*$" EXCLUDE REGEX "/linuxthreads\\.txt$" EXCLUDE REGEX "/myisam\\.txt$" EXCLUDE REGEX "/mysql\\.info$" EXCLUDE REGEX "/sp\\-imp\\-spec\\.txt$" EXCLUDE)
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/csoyee/git/mysql-dwblr-salloc/zlib/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/extra/yassl/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/extra/yassl/taocrypt/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/cmd-line-utils/libedit/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/libevent/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/archive/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/blackhole/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/csv/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/example/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/federated/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/heap/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/innobase/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/myisam/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/myisammrg/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/ndb/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/storage/perfschema/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/audit_null/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/auth/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/daemon_example/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/fulltext/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/innodb_memcached/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/password_validation/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/plugin/semisync/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/include/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/dbug/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/strings/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/vio/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/regex/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/mysys/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/mysys_ssl/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/libmysql/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/unittest/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/unittest/examples/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/unittest/mytap/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/unittest/mytap/t/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/unittest/gunit/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/extra/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/client/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/sql/share/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/scripts/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/man/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/tests/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/sql/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/libservices/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/libmysqld/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/libmysqld/examples/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/mysql-test/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/mysql-test/lib/My/SafeProcess/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/support-files/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/sql-bench/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/packaging/rpm-uln/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/packaging/WiX/cmake_install.cmake")
  include("/home/csoyee/git/mysql-dwblr-salloc/packaging/solaris/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/csoyee/git/mysql-dwblr-salloc/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
