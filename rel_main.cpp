/**************************************************************************
 *
 *  rel_main.cpp
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 5 Oct MMXI
 *
 *************************************************************************/


#include "rel.h"


/*==========================================================
 *  int main()
 *========================================================*/
int main()
{
  rhea::Relation rel;
  rel.printXsl4Html("mediation/ref2html-d.xsl", "../");
  rel.printXsl4Html("mediation/ref2html-t.xsl", "");

  return 0;
}


//eof
