/**************************************************************************
*
*  svisitor4rexml.cpp
*  by oZ/acy
*  (c) 2008-2009 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 15 Nov MMIX
*
**************************************************************************/

#include <iostream>
#include "svisitor4rexml.h"


/*=============*/
std::map<unsigned int, std::string> rhea::SVisitor4REXml::cnvmap_S;


/*===========================================
*  SVisitor4REXml::SVisitor4REXml()
*
*  create: 2008.2.16
*  update: 2008.3.9
*/
rhea::SVisitor4REXml::SVisitor4REXml()
{
  // 空でないなら初期化されてゐると看做す
  if (!cnvmap_S.empty())
    return;

  // 以下、テーブル初期化

  // ASCII
  cnvmap_S['&'] = "<rhea:amp />";
  cnvmap_S['\"'] = "<rhea:quot />";
  cnvmap_S['<'] = "<rhea:lt />";
  cnvmap_S['>'] = "<rhea:gt />";
  cnvmap_S['_'] = "<rhea:ul />";
  cnvmap_S['$'] = "<rhea:dollar />";
  cnvmap_S['#'] = "<rhea:sharp />";
  cnvmap_S['%'] = "<rhea:pct />";
  cnvmap_S['{'] = "<rhea:lbrace />";
  cnvmap_S['}'] = "<rhea:rbrace />";
  cnvmap_S['^'] = "<rhea:hat />";
  cnvmap_S['~'] = "<rhea:tilde />";
  cnvmap_S['|'] = "<rhea:bar />";
  cnvmap_S['\\'] = "<rhea:bksl />";

  // この後を成る可く補完する必要はある
  //// 希臘文字
  cnvmap_S[0x0391] = "<rhea:Alpha />";
  cnvmap_S[0x0392] = "<rhea:Beta />";
  cnvmap_S[0x0393] = "<rhea:Gamma />";
  cnvmap_S[0x0394] = "<rhea:Delta />";
  cnvmap_S[0x0395] = "<rhea:Epsilon />";
  cnvmap_S[0x0396] = "<rhea:Zeta />";
  cnvmap_S[0x0397] = "<rhea:Eta />";
  cnvmap_S[0x0398] = "<rhea:Theta />";
  cnvmap_S[0x0399] = "<rhea:Iota />";
  cnvmap_S[0x039A] = "<rhea:Kappa />";
  cnvmap_S[0x039B] = "<rhea:Lambda />";
  cnvmap_S[0x039C] = "<rhea:Mu />";
  cnvmap_S[0x039D] = "<rhea:Nu />";
  cnvmap_S[0x039E] = "<rhea:Xi />";
  cnvmap_S[0x039F] = "<rhea:Omicron />";
  cnvmap_S[0x03A0] = "<rhea:Pi />";
  cnvmap_S[0x03A1] = "<rhea:Rho />";
  cnvmap_S[0x03A3] = "<rhea:Sigma />";
  cnvmap_S[0x03A4] = "<rhea:Tau />";
  cnvmap_S[0x03A5] = "<rhea:Upsilon />";
  cnvmap_S[0x03A6] = "<rhea:Phi />";
  cnvmap_S[0x03A7] = "<rhea:Chi />";
  cnvmap_S[0x03A8] = "<rhea:Psi />";
  cnvmap_S[0x03A9] = "<rhea:Omega />";
  cnvmap_S[0x03AC] = "<rhea:alpha-t />";
  cnvmap_S[0x03AD] = "<rhea:epsilon-t />";
  cnvmap_S[0x03AE] = "<rhea:eta-t />";
  cnvmap_S[0x03AF] = "<rhea:iota-t />";
  ////
  cnvmap_S[0x03B1] = "<rhea:alpha />";
  cnvmap_S[0x03B2] = "<rhea:beta />";
  cnvmap_S[0x03B3] = "<rhea:gamma />";
  cnvmap_S[0x03B4] = "<rhea:delta />";
  cnvmap_S[0x03B5] = "<rhea:epsilon />";
  cnvmap_S[0x03B6] = "<rhea:zeta />";
  cnvmap_S[0x03B7] = "<rhea:eta />";
  cnvmap_S[0x03B8] = "<rhea:theta />";
  cnvmap_S[0x03B9] = "<rhea:iota />";
  cnvmap_S[0x03BA] = "<rhea:kappa />";
  cnvmap_S[0x03BB] = "<rhea:lambda />";
  cnvmap_S[0x03BC] = "<rhea:mu />";
  cnvmap_S[0x03BD] = "<rhea:nu />";
  cnvmap_S[0x03BE] = "<rhea:xi />";
  cnvmap_S[0x03BF] = "<rhea:omicron />";
  cnvmap_S[0x03C0] = "<rhea:pi />";
  cnvmap_S[0x03C1] = "<rhea:rho />";
  cnvmap_S[0x03C2] = "<rhea:sigmaf />";
  cnvmap_S[0x03C3] = "<rhea:sigma />";
  cnvmap_S[0x03C4] = "<rhea:tau />";
  cnvmap_S[0x03C5] = "<rhea:upsilon />";
  cnvmap_S[0x03C6] = "<rhea:phi />";
  cnvmap_S[0x03C7] = "<rhea:chi />";
  cnvmap_S[0x03C8] = "<rhea:psi />";
  cnvmap_S[0x03C9] = "<rhea:omega />";
  cnvmap_S[0x03CC] = "<rhea:omicron-t />";
  cnvmap_S[0x03CD] = "<rhea:upsilon-t />";
  cnvmap_S[0x03CE] = "<rhea:omega-t />";
  cnvmap_S[0x03D1] = "<rhea:thetav />";
  cnvmap_S[0x03D5] = "<rhea:phiv />";
  cnvmap_S[0x03D6] = "<rhea:piv />";

  // 修飾附ラテン文字
  cnvmap_S[0x00C0] = "<rhea:Ag />";
  cnvmap_S[0x00E0] = "<rhea:ag />";
  cnvmap_S[0x00C1] = "<rhea:Aa />";
  cnvmap_S[0x00E1] = "<rhea:aa />";
  cnvmap_S[0x00C2] = "<rhea:Aci />";
  cnvmap_S[0x00E2] = "<rhea:aci />";
  cnvmap_S[0x00C3] = "<rhea:At />";
  cnvmap_S[0x00E3] = "<rhea:at />";
  cnvmap_S[0x00C4] = "<rhea:Au />";
  cnvmap_S[0x00E4] = "<rhea:au />";
  cnvmap_S[0x00C5] = "<rhea:Ar />";
  cnvmap_S[0x00E5] = "<rhea:ar />";
  cnvmap_S[0x0100] = "<rhea:Ao />";
  cnvmap_S[0x0101] = "<rhea:ao />";
  cnvmap_S[0x00C6] = "<rhea:AE />";
  cnvmap_S[0x00E6] = "<rhea:ae />";
  cnvmap_S[0x00C7] = "<rhea:Cce />";
  cnvmap_S[0x00E7] = "<rhea:cce />";
  cnvmap_S[0x0106] = "<rhea:Ca />";
  cnvmap_S[0x0107] = "<rhea:ca />";
  cnvmap_S[0x00D0] = "<rhea:DH />";
  cnvmap_S[0x00F0] = "<rhea:dh />";
  cnvmap_S[0x00C8] = "<rhea:Eg />";
  cnvmap_S[0x00E8] = "<rhea:eg />";
  cnvmap_S[0x00C9] = "<rhea:Ea />";
  cnvmap_S[0x00E9] = "<rhea:ea />";
  cnvmap_S[0x00CA] = "<rhea:Eci />";
  cnvmap_S[0x00EA] = "<rhea:eci />";
  cnvmap_S[0x00CB] = "<rhea:Eu />";
  cnvmap_S[0x00EB] = "<rhea:eu />";
  cnvmap_S[0x0112] = "<rhea:Eo />";
  cnvmap_S[0x0113] = "<rhea:eo />";
  cnvmap_S[0x00CC] = "<rhea:Ig />";
  cnvmap_S[0x00EC] = "<rhea:ig />";
  cnvmap_S[0x00CD] = "<rhea:Ia/>";
  cnvmap_S[0x00ED] = "<rhea:ia />";
  cnvmap_S[0x00CE] = "<rhea:Ici />";
  cnvmap_S[0x00EE] = "<rhea:ici />";
  cnvmap_S[0x00CF] = "<rhea:Iu />";
  cnvmap_S[0x00EF] = "<rhea:iu />";
  cnvmap_S[0x012B] = "<rhea:io />";
  cnvmap_S[0x0131] = "<rhea:i-dl />";
  cnvmap_S[0x0132] = "<rhea:IJ />";
  cnvmap_S[0x0133] = "<rhea:ij />";
  cnvmap_S[0x00D1] = "<rhea:Nt />";
  cnvmap_S[0x00F1] = "<rhea:nt />";
  cnvmap_S[0x00D2] = "<rhea:Og />";
  cnvmap_S[0x00F2] = "<rhea:og />";
  cnvmap_S[0x00D3] = "<rhea:Oa />";
  cnvmap_S[0x00F3] = "<rhea:oa />";
  cnvmap_S[0x00D4] = "<rhea:Oci />";
  cnvmap_S[0x00F4] = "<rhea:oci />";
  cnvmap_S[0x00D5] = "<rhea:Ot />";
  cnvmap_S[0x00F5] = "<rhea:ot />";
  cnvmap_S[0x00D6] = "<rhea:Ou />";
  cnvmap_S[0x00F6] = "<rhea:ou />";
  cnvmap_S[0x00D8] = "<rhea:Osl />";
  cnvmap_S[0x00F8] = "<rhea:osl />";
  cnvmap_S[0x0152] = "<rhea:OE />";
  cnvmap_S[0x0153] = "<rhea:oe />";
  cnvmap_S[0x00DF] = "<rhea:ss />";
  cnvmap_S[0x015C] = "<rhea:Sci />";
  cnvmap_S[0x015D] = "<rhea:sci />";
  cnvmap_S[0x015E] = "<rhea:Sce />";
  cnvmap_S[0x015F] = "<rhea:sce />";
  cnvmap_S[0x0160] = "<rhea:S-car />";
  cnvmap_S[0x0161] = "<rhea:s-car />";
  cnvmap_S[0x00DE] = "<rhea:THORN />";
  cnvmap_S[0x00FE] = "<rhea:thorn />";
  cnvmap_S[0x00D9] = "<rhea:Ug />";
  cnvmap_S[0x00F9] = "<rhea:ug />";
  cnvmap_S[0x00DA] = "<rhea:Ua />";
  cnvmap_S[0x00FA] = "<rhea:ua />";
  cnvmap_S[0x00DB] = "<rhea:Uci />";
  cnvmap_S[0x00FB] = "<rhea:uci />";
  cnvmap_S[0x00DC] = "<rhea:Uu />";
  cnvmap_S[0x00FC] = "<rhea:uu />";
  cnvmap_S[0x016A] = "<rhea:Uo />";
  cnvmap_S[0x016B] = "<rhea:uo />";
  cnvmap_S[0x0175] = "<rhea:wci />";
  cnvmap_S[0x00DD] = "<rhea:Ya />";
  cnvmap_S[0x00FD] = "<rhea:ya />";
  cnvmap_S[0x0178] = "<rhea:Yu />";
  cnvmap_S[0x00FF] = "<rhea:yu />";


/*
  cnvmap_S[0x] = "<rhea: />";
  cnvmap_S[0x] = "<rhea: />";
*/



  // 記號
  cnvmap_S[0x00A9] = "<rhea:copy />";
  cnvmap_S[0x21D0] = "<rhea:LArr />";
  cnvmap_S[0x21D2] = "<rhea:RArr />";
  cnvmap_S[0x2661] = "<rhea:heart />";
  cnvmap_S[0x00A7] = "<rhea:sect />";
  cnvmap_S[0x00A1] = "<rhea:inv-exc />";
  cnvmap_S[0x00A5] = "<rhea:yen />";
  cnvmap_S[0x00AC] = "<rhea:not />";
  cnvmap_S[0x00AE] = "<rhea:reg />";
  cnvmap_S[0x00B0] = "<rhea:degree />";
  cnvmap_S[0x00B6] = "<rhea:pilcrow />";
  cnvmap_S[0x00BF] = "<rhea:inv-ques />";
  cnvmap_S[0x3012] = "<rhea:postal />";

}



/*===========================================
*  SVisitor4REXml::visit(NormalString&)
*
*  一部の文字をXML用にエスケープする
*
*  create: 2008.2.16
*  modify: 2009.11.15
*/
void rhea::SVisitor4REXml::visit(metis::NormalString& ns)
{
  using namespace std;

  string::const_iterator it;
  for (it = ns.refer().begin(); it != ns.refer().end(); ++it)
  {
    if (*it & 0x0080)
    {
      oss() << *it;
    }
    else
    {
      map<unsigned int, string>::iterator jt = cnvmap_S.find((int)*it);
      if (jt == cnvmap_S.end())
        oss() << *it;
      else
        oss() << jt->second;
    }
  }
}


/*===========================================
*  SVisitor4REXml::visit(metis::CharReference&)
*
*  文字參照をエスケープする
*
*  create: 2008.2.16
*  modify: 2009.11.15
*/
void rhea::SVisitor4REXml::visit(metis::CharReference& cr)
{
  using namespace std;

  map<unsigned int, string>::iterator jt = cnvmap_S.find(cr.codeval());
  if (jt == cnvmap_S.end())
    oss() << "&#x" << cr.code() << ";";
  else
    oss() << jt->second;
}



//eof
