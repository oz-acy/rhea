/**************************************************************************
*
*  metis2xml.cpp
*  by oZ/acy
*  (c) 2005-2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb 2008
*
*  system "RHEA" óp  Metis => XML ô|óùÉNÉâÉX
**************************************************************************/

#include <sstream>
#include "metis2xml.h"
#include "svisitor4gxml.h"
#include "svisitor4rexml.h"


/*================================================
*  AttrVisitor2Xml::visit()
*
*  update: 2008.2.16
*===============================================*/
void rhea::AttrVisitor2Xml::visit(metis::Attribute& a)
{
  os_ << " " << a.name() << "=\"";

  SVisitor4GXml svgx;
  a.content()->accept(svgx);
  os_ << svgx.str();

  os_ << "\"";
}


/*================================================
*  WriteVisitor2Xml::visit(StringData&)
*
*  update: 2008.2.16
*===============================================*/
void rhea::WriteVisitor2Xml::visit(metis::StringData& str)
{
  SVisitor4REXml svrex;
  str.accept(svrex);
  os_ << svrex.str();
}


/*================================================
*  WriteVisitor2Xml::visit(Element&)
*===============================================*/
void rhea::WriteVisitor2Xml::visit(metis::Element& elm)
{
  std::list<metis::Datum*>::iterator it;

  os_ << "<" << elm.name();

  AttrVisitor2Xml attrv(os_);
  for (it = elm.children().begin(); it != elm.children().end(); ++it)
    (*it)->accept(attrv);

  if (elm.empty())
    os_ << " />";
  else
  {
    os_ << ">";

    for (it = elm.children().begin(); it != elm.children().end(); ++it)
      (*it)->accept(*this);

    os_ << "</" << elm.name() << ">";
  }
}


//eof
