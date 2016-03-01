# CMakeLists.txt for System RHEA

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
SET(CMAKE_VERBOSE_MAKEFILE 1)

#PROJECT(rhea CXX)

#SET(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-clang++)
SET(CMAKE_CXX_FLAGS "-Wall -std=c++14 -O3")
SET(CMAKE_EXE_LINKER_FLAGS "-static")

INCLUDE_DIRECTORIES("${CMAKE_INSTALL_PREFIX}/include")
LINK_DIRECTORIES("${CMAKE_INSTALL_PREFIX}/lib")



ADD_EXECUTABLE(metis2xml
  m2x_main.cpp metis2xml.cpp
  svisitor4gxml.cpp
  svisitor4rexml.cpp
)
TARGET_LINK_LIBRARIES(metis2xml themis metis)

ADD_EXECUTABLE(rhea_diary
  diary.cpp diary_main.cpp
  svisitor2met.cpp
)
TARGET_LINK_LIBRARIES(rhea_diary themis metis boost_filesystem boost_system)


ADD_EXECUTABLE(rhea_rel
  rel.cpp rel_main.cpp
  refer.cpp
  svisitor4gxml.cpp
)
TARGET_LINK_LIBRARIES(rhea_rel themis metis boost_filesystem boost_system)

ADD_EXECUTABLE(rhea_word
  word.cpp word_main.cpp
  dict.cpp dict.h
  svisitor4gxml.cpp
  svisitor2tex.cpp
  svisitor2met.cpp
)
TARGET_LINK_LIBRARIES(rhea_word themis metis boost_filesystem boost_system)


INSTALL(TARGETS metis2xml rhea_diary rhea_rel rhea_word DESTINATION bin)
INSTALL(FILES rhea-dicout rhea-top
  DESTINATION bin
  PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)


#eof
