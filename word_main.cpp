/**************************************************************************
*
*  word_main.cpp
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 9 Sep MMXI
*
**************************************************************************/

#include <fstream>
#include "dict.h"


/*======================================
 *  main()
 *  update: 2011.9.9
 *=====================================*/
int main()
{
  using namespace std;

  rhea::Dictionary dic;

  ofstream ofs1("mediation/word2html-d.xsl", ios::binary);
  dic.printXsl4Html(ofs1, "../");

  ofstream ofs2("mediation/word2html-t.xsl", ios::binary);
  dic.printXsl4Html(ofs2, "");

  ofstream ofs3("mediation/word2tex.xsl", ios::binary);
  dic.printXsl4Tex(ofs3);

  ofstream ofs4("mediation/Makefile.D1", ios::binary);
  dic.printMakefile4Html(ofs4);

  dic.outputList("U", "dic-univ", "", "");
  dic.outputList("I", "dic-info", "-i", " 計算機・情報篇");

  return 0;
}

//eof
