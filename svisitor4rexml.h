/**************************************************************************
*
*  svisitor4rexml.h
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb MMVIII
*
**************************************************************************/

#ifndef INC_RHEA_STRING_VISITOR_FOR_RHEA_ELEMENT_XML_H___
#define INC_RHEA_STRING_VISITOR_FOR_RHEA_ELEMENT_XML_H___

#include <map>
#include <metis/strvisitor.h>


namespace rhea {


/*----------------------------------------------------------
*  SVisitor4REXml
*
*  RHEAópóvëfXMLÇ÷ÇÃùÃä∑Çà”ö§ÇµÇΩStringDataópVisitor
*  update: 2008.2.16
*---------------------------------------------------------*/
class SVisitor4REXml : public metis::StringVisitor
{
private:
  static std::map<unsigned int, std::string> cnvmap_S;

public:
  SVisitor4REXml();
  void visit(metis::NormalString& ns);
  void visit(metis::CharReference& cr);
};


}// end of namespace rhea


#endif // INC_RHEA_STRING_VISITOR_FOR_RHEA_ELEMENT_XML_H___
