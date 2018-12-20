/**************************************************************************
*
*  svisitor2met.cpp
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb MMVIII
*
**************************************************************************/

#include <iostream>
#include "svisitor2met.h"


/*=======*/
std::map<char, std::string> rhea::SVisitor2Metis::cnvmap_S;


/*===========================================
*  SVisitor2Metis::SVisitor2Metis()
*
*  create: 2008.2.16
*/
rhea::SVisitor2Metis::SVisitor2Metis()
{
  // ��łȂ���Ί��ɏ���������Ă��ƊŘ�
  if (!cnvmap_S.empty())
    return;

  // ������
  cnvmap_S['@'] = "&at;";
  cnvmap_S['#'] = "&sharp;";
  cnvmap_S['{'] = "&lb;";
  cnvmap_S['}'] = "&rb;";
  cnvmap_S['&'] = "&amp;";
}


/*===========================================
*  SVisitor2Metis::visit(NormalString&)
*
*  �ꕔ�̕�����Metis�p�ɃG�X�P�[�v����
*
*  create: 2008.2.16
*/
void rhea::SVisitor2Metis::visit(metis::NormalString& ns)
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




//eof
