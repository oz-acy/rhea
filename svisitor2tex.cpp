/**************************************************************************
*
*  svisitor2tex.cpp
*  by oZ/acy
*  (c) 2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 16 Feb MMVIII
*
**************************************************************************/

#include <iostream>
#include "svisitor2tex.h"


/*=======*/
std::map<unsigned int, std::string> rhea::SVisitor2Tex::cnvmap_S;


/*===========================================
 *  SVisitor2Tex::SVisitor2Tex()
 *
 *  create: 2008.2.17
 */
rhea::SVisitor2Tex::SVisitor2Tex()
{
  // ��łȂ���Ί��ɏ���������Ă��ƊŘ�
  if (!cnvmap_S.empty())
    return;

  // ������
  cnvmap_S['\\'] = "{\\textbackslash}";
  cnvmap_S['\"'] = "&quot;";
  cnvmap_S['<'] = "{\\textless}";
  cnvmap_S['>'] = "{\\textgreater}";
  cnvmap_S['_'] = "{\\_}";
  cnvmap_S['$'] = "{\\$}";
  cnvmap_S['#'] = "{\\#}";
  cnvmap_S['{'] = "{\\{}";
  cnvmap_S['}'] = "{\\}}";
  cnvmap_S['^'] = "{\\textasciicircum}";
  cnvmap_S['~'] = "{\\textasciitilde}";
  cnvmap_S['|'] = "{\\textbar}";
  cnvmap_S['&'] = "{\\&amp;}";

}


/*===========================================
 *  SVisitor2Metis::visit(NormalString&)
 *
 *  �ꕔ�̕�����Metis�p�ɃG�X�P�[�v����
 *
 *  create: 2008.2.17
 */
void rhea::SVisitor2Tex::visit(metis::NormalString& ns)
{
  using namespace std;

  string::const_iterator it;
  for (it = ns.refer().begin(); it != ns.refer().end(); ++it)
  {
    map<unsigned int, string>::iterator jt = cnvmap_S.find(*it);
    if (jt == cnvmap_S.end())
      oss() << *it;
    else
      oss() << jt->second;
  }
}


/*================================================
 *  SVisitor2Tex::visit(metis::CharReference&)
 *
 *  �����ҏƂ��G�X�P�[�v����
 *
 *  create: 2008.2.17
 */
void rhea::SVisitor2Tex::visit(metis::CharReference& cr)
{
  using namespace std;

  map<unsigned int, string>::iterator jt = cnvmap_S.find(cr.codeval());
  if (jt == cnvmap_S.end())
    oss() << "\\UTF{" << cr.code() << "}";
  else
    oss() << jt->second;
}




//eof
