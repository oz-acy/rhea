# Makefile.am for RHEA

AM_CFLAGS = -O2
AM_CXXFLAGS = -O2

bin_PROGRAMS = \
	metis2xml rhea-diary rhea-word rhea-content rhea-rel
#	rhea-db

metis2xml_SOURCES = \
	m2x_main.cpp metis2xml.cpp metis2xml.h \
	svisitor4gxml.h svisitor4gxml.cpp \
	svisitor4rexml.h svisitor4rexml.cpp

rhea_diary_SOURCES = \
	diary.cpp diary_main.cpp diary.h \
	svisitor2met.h svisitor2met.cpp

rhea_content_SOURCES = \
	rel-ref.cpp rel-ref.h 

#	svisitor4gxml.h svisitor4gxml.cpp

rhea_rel_SOURCES = \
	rel.cpp rel_main.cpp rel.h \
	refer.cpp refer.h \
	svisitor4gxml.h svisitor4gxml.cpp

##	svisitor2tex.h svisitor2tex.cpp

rhea_word_SOURCES = \
	word.cpp word_main.cpp word.h \
	dict.cpp dict.h \
	svisitor4gxml.h svisitor4gxml.cpp \
	svisitor2tex.h svisitor2tex.cpp \
	svisitor2met.h svisitor2met.cpp


#rhea_db_SOURCES = db.cpp \
#	svisitor4gxml.h svisitor4gxml.cpp


libs = -lmetis -lthemis -lboost_filesystem -lboost_system
metis2xml_LDADD  = $(libs)
rhea_diary_LDADD = $(libs)
rhea_word_LDADD  = $(libs)
rhea_content_LDADD = $(libs)
rhea_rel_LDADD   = $(libs)
#rhea_db_LDADD    = $(libs)

AM_LDFLAGS = -static

INSTALL_SCRIPT = ${INSTALL}

bin_SCRIPTS = rhea-dicout rhea-top
EXTRA_DIST = rhea-dicout rhea-top

CLEANFILES = *~




#eof
