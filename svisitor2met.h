/**************************************************************************
*
*  svisitor2met.h
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb MMVIII
*
**************************************************************************/

#ifndef INC_RHEA_STRING_VISITOR_TO_METIS_H___
#define INC_RHEA_STRING_VISITOR_TO_METIS_H___

#include <map>
#include <metis/strvisitor.h>


namespace rhea {


/*------------------------------------------------
*  SVisitor2Metis
*
*  MetisãLèqÇ÷ÇÃùÃä∑Çà”ö§ÇµÇΩStringDataópVisitor
*  update: 2008.2.16
*-----------------------------------------------*/
class SVisitor2Metis : public metis::StringVisitor
{
private:
  static std::map<char, std::string> cnvmap_S;

public:
  SVisitor2Metis();
  void visit(metis::NormalString& s);
};


}// end of namespace rhea


#endif // INC_RHEA_STRING_VISITOR_TO_METIS_H___
