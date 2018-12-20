/**************************************************************************
*
*  svisitor4gxml.cpp
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 13 Mar MMVIII
*
**************************************************************************/

#include <iostream>
#include "svisitor4gxml.h"


/*=======*/
std::map<char, std::string> rhea::SVisitor4GXml::cnvmap_S;


/*===========================================
*  SVisitor4GXml::SVisitor4GXml()
*
*  create: 2008.2.16
*/
rhea::SVisitor4GXml::SVisitor4GXml()
{
  // 空でなければ既に初期化されてゐると看做す
  if (!cnvmap_S.empty())
    return;

  // 初期化
  cnvmap_S['&'] = "&amp;";
  cnvmap_S['\"'] = "&quot;";
  cnvmap_S['<'] = "&lt;";
  cnvmap_S['>'] = "&gt;";
}


/*===========================================
*  SVisitor4GXml::visit(NormalString&)
*
*  一部の文字をXML用にエスケープする
*
*  create: 2008.2.16
*/
void rhea::SVisitor4GXml::visit(metis::NormalString& ns)
{
  using namespace std;

  string::const_iterator it;
  for (it = ns.refer().begin(); it != ns.refer().end(); ++it)
  {
    map<char, string>::iterator jt = cnvmap_S.find(*it);
    if (jt == cnvmap_S.end())
      oss() << *it;
    else
      oss() << jt->second;
  }
}


/*===========================================
*  SVisitor4GXml::visit(CharReference&)*
*  update: 2008.3.13
*/
void rhea::SVisitor4GXml::visit(metis::CharReference& cr)
{
  using namespace std;

  if (cr.code() == "FFFFFFFF")
    cerr << "WARNING: " << cr.code() << endl;

  oss() << "&#x" << cr.code() << ";";
}




//eof
