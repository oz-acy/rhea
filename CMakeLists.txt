# CMakeLists.txt for project RHEA

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_VERBOSE_MAKEFILE 1)

#PROJECT(rhea CXX)

#find_package(FLEX)
#find_package(BISON)

SET(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O3")

#FLEX_TARGET(MyScanner lex.ll lex.cc)
#BISON_TARGET(MyParser parse.yy parse.cc)
#ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

ADD_EXECUTABLE(metis2xml
  m2x_main.cpp
  metis2xml.cpp
  svisitor4gxml.cpp
  svisitor4rexml.cpp
)
TARGET_LINK_LIBRARIES(metis2xml metis boost_filesystem boost_system)

ADD_EXECUTABLE(rhea-diary
  diary.cpp
  diary_main.cpp
  svisitor2met.cpp
)
TARGET_LINK_LIBRARIES(rhea-diary metis boost_filesystem boost_system)

ADD_EXECUTABLE(rhea-rel
  rel.cpp
  rel_main.cpp
  refer.cpp
  svisitor4gxml.cpp
)
TARGET_LINK_LIBRARIES(rhea-rel metis boost_filesystem boost_system)

#ADD_EXECUTABLE(rhea-word
#  word.cpp
#  word_main.cpp
#  dict.cpp
#  svisitor4gxml.cpp
#  svisitor2tex.cpp
#  svisitor2met.cpp
#)
#TARGET_LINK_LIBRARIES(rhea-word metis boost_filesystem boost_system)

ADD_EXECUTABLE(rhea-content
  rel-ref.cpp
)
TARGET_LINK_LIBRARIES(rhea-content metis boost_filesystem boost_system)

INSTALL(
  TARGETS
      metis2xml
      rhea-diary
      rhea-rel
#      rhea-word
      rhea-content
  DESTINATION
      bin
)




#eof
