/**************************************************************************
 *
 *  rel.cpp
 *  by oZ/acy
 *  (c) 2005-2018 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 2018.12.21
 *
 */

#include <iostream>
#include <fstream>
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/operations.hpp>
#include <experimental/filesystem>
#include "rel.h"
#include "svisitor4gxml.h"


namespace {

typedef std::map<std::string, rhea::InRefer> InRefMap;
typedef std::map<std::string, rhea::ExRefer> ExRefMap;


std::vector<std::string> split(std::string str, std::string delim)
{
  using namespace std;
  
  vector<string> res;
  int at;

  while((at = str.find_first_of(delim)) != string::npos) {
    if (at > 0) {
      res.push_back(str.substr(0, at));
    }
    str = str.substr(at + 1);
  }

  if(str.size())
    res.push_back(str);

  return res;
}


void readReferInfo(const std::string& dir, InRefMap& irm, ExRefMap& xrm)
{
  using namespace std;
  using namespace rhea;
  //namespace fs = boost::filesystem;
  namespace fs = std::experimental::filesystem;

  fs::path targetdir(dir);
  fs::directory_iterator end;
  for (fs::directory_iterator it(targetdir); it != end; ++it) {
    string src = it->path().string();
    if (src.substr(src.length()-4) != ".rri")
      continue;

    cout << it->path().filename().string() << endl;


    ifstream ifs(src.c_str(), ios::in);
    while (ifs.good()) {
      string line;
      getline(ifs, line);
      vector<string> vs = split(line, "\t");
      if (vs.size() < 5)
        continue;

      string id = vs[1];

      if (vs[0] == "I")
      {
        if (vs[3] == "S")
        {
          InRefer ir(vs[2], vs[4]);
          irm.insert(make_pair(id, ir));
        }
        if (vs[3] == "W")
        {
          InRefer ir(vs[2], vs[4]);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "AW" && vs.size() >= 6)
        {
          InRefer ir(vs[2], vs[4], vs[5], ReferBase::TY_ABBR);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "A" && vs.size() >= 6)
        {
          InRefer ir(vs[2], vs[4], vs[5], ReferBase::TY_ABBR);
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "NW" && vs.size() >= 6)
        {
          InRefer ir(vs[2], vs[4], vs[5], ReferBase::TY_NOTE);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "N" && vs.size() >= 6)
        {
          InRefer ir(vs[2], vs[4], vs[5], ReferBase::TY_NOTE);
          irm.insert(make_pair(id, ir));
        }
      }
      else if (vs[0] == "N")
      {
        if (vs[3] == "S")
        {
          InRefer ir(vs[4]);
          irm.insert(make_pair(id, ir));
        }
        if (vs[3] == "W")
        {
          InRefer ir(vs[2]);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "AW" && vs.size() >= 6)
        {
          InRefer ir(vs[4], vs[5], ReferBase::TY_ABBR);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "A" && vs.size() >= 6)
        {
          InRefer ir(vs[4], vs[5], ReferBase::TY_ABBR);
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "NW" && vs.size() >= 6)
        {
          InRefer ir(vs[4], vs[5], ReferBase::TY_NOTE);
          ir.setAsWord();
          irm.insert(make_pair(id, ir));
        }
        else if (vs[3] == "N" && vs.size() >= 6)
        {
          InRefer ir(vs[4], vs[5], ReferBase::TY_NOTE);
          irm.insert(make_pair(id, ir));
        }
      }
      else if (vs[0] == "X")
      {
        if (vs[3] == "S")
        {
          ExRefer xr(vs[2], vs[4]);
          xrm.insert(make_pair(id, xr));
        }
        else if (vs[3] == "A" && vs.size() >= 6)
        {
          ExRefer xr(vs[2], vs[4], vs[5], ReferBase::TY_ABBR);
          xrm.insert(make_pair(id, xr));
        }
        else if (vs[3] == "N" && vs.size() >= 6)
        {
          ExRefer xr(vs[2], vs[4], vs[5], ReferBase::TY_NOTE);
          xrm.insert(make_pair(id, xr));
        }
      }
      
    }
  }

}




}//end of namespace




/*===============================
 *  Relation::Relation()
 *  update: 2011.10.05
 */
rhea::Relation::Relation()
{
  using namespace std;

  // for RRI
  readReferInfo("relation", inRefers_, exRefers_);
}


/*======================================
 *  Relation::printXsl4Html()
 *  update 2011.10.05
 *====================================*/
void rhea::Relation::printXsl4Html(
  const std::string& path, const std::string& prefix)
{
  using namespace std;

  ofstream ofs(path.c_str());


  ofs << "<?xml version=\"1.0\"?>" << endl;
  ofs << "<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\""
         " xmlns:rhea=\"http://www.hiemalis.org/~acy/\""
         " exclude-result-prefixes=\"rhea\" version=\"1.0\">" << endl;
  ofs << "  <xsl:template match=\"rhea:ref\">" << endl;
  ofs << "    <xsl:choose>" << endl;


  // for RRI
  std::map<std::string, InRefer>::iterator lt;
  for (lt = inRefers_.begin(); lt != inRefers_.end(); ++lt)
    ofs << lt->second.toXsl4Html(prefix, lt->first);

  std::map<std::string, ExRefer>::iterator mt;
  for (mt = exRefers_.begin(); mt != exRefers_.end(); ++mt)
    ofs << mt->second.toXsl4Html("", mt->first);


  ofs << endl;

  // root ‘¦‚¿ƒTƒCƒgƒgƒbƒv
  ofs << "      <xsl:when test=\"@id='root'\"><a><xsl:attribute name=\"href\">"
      << prefix << "index.html"
      << "<xsl:if test=\"boolean(@subid)\">#<xsl:value-of select=\"@subid\" />"
         "</xsl:if></xsl:attribute>";
         
  ofs << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  ofs << "<xsl:apply-templates />";
  ofs << "</xsl:if>";
  ofs << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  ofs << "Top";
  ofs << "</xsl:if>";
         
  ofs << "</a></xsl:when>"
      << endl << endl;

  // this ‘¦‚¿ácŠY•¶‘
  ofs << "      <xsl:when test=\"@id='this' and boolean(@subid)\">"
      << "<a><xsl:attribute name=\"href\">"
      << "#<xsl:value-of select=\"@subid\" /></xsl:attribute>";

  ofs << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  ofs << "<xsl:apply-templates />";
  ofs << "</xsl:if>";
  ofs << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  ofs << "This Page";
  ofs << "</xsl:if>";

  ofs << "</a></xsl:when>" << endl;

  // ‚¢‚Ã‚ê‚É‚àŠYác‚¹‚¸
  ofs << "      <xsl:otherwise><a><xsl:attribute name=\"href\">"
      << prefix << "notfound.html</xsl:attribute>???"
      << "</a></xsl:otherwise>"
      << endl;

  ofs << "    </xsl:choose>" << endl;
  ofs << "  </xsl:template>" << endl;
  ofs << "</xsl:stylesheet>" << endl;
}




/*** ˆÈ‰ºAŽæ‚èŠ¸‚Ö‚¸‚Ì•Û‘¶—p ***/

/*=========================================================
*  Content::toXsl4Html()
*  update: 2011.10.5
*========================================================*/
/*
std::string rhea::Content::toXsl4Html(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";
  oss << "<a>";

  oss << "<xsl:attribute name=\"href\">" << prefix << dst_;
  oss << "<xsl:if test=\"boolean(@subid)\">#<xsl:value-of select=\"@subid\" />"
         "</xsl:if>";
  oss << "</xsl:attribute>";

  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  oss << "<xsl:apply-templates />";
  oss << "</xsl:if>";
  oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";

  SVisitor4GXml svgx;
  title_->accept(svgx);
  oss << svgx.str();

  oss << "</xsl:if>";

  oss << "</a>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}
*/

/*=========================================================
*  ReferredBase::toXsl4Tex1()
*
*========================================================*/
/*
std::string
rhea::ReferredBase::toXsl4Tex1(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";
  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  oss << "<xsl:apply-templates />";
  oss << "</xsl:if>";
  oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";

  SVisitor2Tex svt;
  title_->accept(svt);
  oss << svt.str();

  oss << "</xsl:if>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}
*/
/*=========================================================
*  ReferredBase::toXsl4Tex2()
*
*========================================================*/
/*
std::string
rhea::ReferredBase::toXsl4Tex2(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";
  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  oss << "<xsl:apply-templates />";
  oss << "</xsl:if>";
  oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";

  SVisitor2Tex svt;
  title_->accept(svt);
  oss << svt.str();

  oss << "</xsl:if>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}
*/



//eof
