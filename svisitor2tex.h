/**************************************************************************
*
*  svisitor2tex.h
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb MMVIII
*
**************************************************************************/

#ifndef INC_RHEA_STRING_VISITOR_TO_TEX_H___
#define INC_RHEA_STRING_VISITOR_TO_TEX_H___

#include <map>
#include <metis/strvisitor.h>


namespace rhea {


/*------------------------------------------------
*  SVisitor2Tex
*
*  TeXÇ÷ÇÃùÃä∑Çà”ö§ÇµÇΩStringDataópVisitor
*  update: 2008.2.16
*-----------------------------------------------*/
class SVisitor2Tex : public metis::StringVisitor
{
private:
  static std::map<unsigned int, std::string> cnvmap_S;

public:
  SVisitor2Tex();
  void visit(metis::NormalString& s);
  void visit(metis::CharReference& cr);
};


}// end of namespace rhea


#endif // INC_RHEA_STRING_VISITOR_TO_TEX_H___
