/**************************************************************************
*
*  svisitor4gxml.h
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 13 Mar MMVIII
*
**************************************************************************/

#ifndef INC_RHEA_STRING_VISITOR_FOR_GENERAL_XML_H___
#define INC_RHEA_STRING_VISITOR_FOR_GENERAL_XML_H___

#include <map>
#include <metis/strvisitor.h>


namespace rhea {


/*------------------------------------------------
*  SVisitor4GXml
*
*  îƒópXMLÇ÷ÇÃùÃä∑Çà”ö§ÇµÇΩStringDataópVisitor
*  update: 2008.3.13
*-----------------------------------------------*/
class SVisitor4GXml : public metis::StringVisitor
{
private:
  static std::map<char, std::string> cnvmap_S;

public:
  SVisitor4GXml();
  void visit(metis::NormalString& s);
  void visit(metis::CharReference& cr);
};


}// end of namespace rhea


#endif // INC_RHEA_STRING_VISITOR_FOR_GENERAL_XML_H___
