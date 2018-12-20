/**************************************************************************
*
*  db.cpp
*  by oZ/acy
*  (c) 2005-2018 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 20 Dec MMXVIII
*
**************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <filesystem>
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/operations.hpp>
#include <metis/parser.h>
#include <metis/strescape.h>
#include "svisitor4gxml.h"


namespace {

/*-------------------------------------------
*  DbItem_
*  DB å¬ï èÓïÒ
*------------------------------------------*/
class DbItem_
{
private:
  std::string dbid_;
  std::string itemid_;
  std::string dst_;
  std::string src_;
  std::string title_;

public:
  DbItem_(
    const std::string& di, const std::string& ii, const std::string& d,
    const std::string& s, const std::string& t)
    : dbid_(di), itemid_(ii), dst_(d), src_(s), title_(t)
    {}

  std::string toXsl4Html(const std::string& prefix) const;


//  std::string toXsl4Tex1(
//    const std::string& prefix, const std::string& id) const;
//  std::string toXsl4Tex2(
//    const std::string& prefix, const std::string& id) const;

  std::string toMakefile() const;

  const std::string& getDstHtml() const { return dst_; }
};


/*=========================================================
*  DbItem_::toXsl4Html()
*
*========================================================*/
std::string DbItem_::toXsl4Html(const std::string& prefix) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@db='" << dbid_ <<  "' and @id='"
      << itemid_ << "'\">";
  oss << "<a>";

  oss << "<xsl:attribute name=\"href\">" << prefix << dst_;
  oss << "<xsl:if test=\"boolean(@subid)\">#<xsl:value-of select=\"@subid\" />"
         "</xsl:if>";
  oss << "</xsl:attribute>";

  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">"
         "<xsl:apply-templates /></xsl:if><xsl:if test=\"not(boolean(text())) "
         "and (count(child::node())=0)\">" + title_ + "</xsl:if>";

  //oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  //oss << "<xsl:apply-templates />";
  //oss << "</xsl:if>";
  //oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  //oss << title_;
  //oss << "</xsl:if>";

  oss << "</a>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}


/*=========================================================
*  ReferredBase_::toXsl4Tex1()
*
*========================================================*/
/*
std::string
ReferredBase_::toXsl4Tex1(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";
  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  oss << "<xsl:apply-templates />";
  oss << "</xsl:if>";
  oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  oss << title_;
  oss << "</xsl:if>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}
*/

/*=========================================================
*  ReferredBase_::toXsl4Tex2()
*
*========================================================*/
/*
std::string
ReferredBase_::toXsl4Tex2(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";
  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">";
  oss << "<xsl:apply-templates />";
  oss << "</xsl:if>";
  oss << "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  oss << title_;
  oss << "</xsl:if>";
  oss << "</xsl:when>" << std::endl;

  return oss.str();
}
*/






/*======================================================
*  DbItem_::toMakefile()
*  last update: 2010.4.13
*=====================================================*/
std::string DbItem_::toMakefile() const
{
  std::ostringstream oss;

  std::string xml = src_.substr(0, src_.length() - 4) + ".xml";

  // .met to .xml
  oss << "db/" << xml << " : db/" << src_ << std::endl;
  oss << "\tmetis2xml db/"<< src_ << " db/" << xml << std::endl;
  oss << std::endl;

  // for Html
  oss << "html/" << dst_ << " : db/" << xml << std::endl;
  oss << "\t$(XP) -o html/" << dst_ 
      << " dbml2html.xsl db/" << xml << std::endl;
  oss << std::endl;


  // for Tex (1)
  //if (!dstTex1_.empty())
  //{
  //  oss << "tex/" << dstTex1_ << " : contents/" << xml << std::endl;
  //  oss << "\t$(XT) contents/" << xml << " rml2tex-c.xsl tex/"
  //      << dstTex1_ << std::endl;
  //  oss << std::endl;
  //}

  // for Tex (2)
  //if (!dstTex2_.empty())
  //{
  //  oss << "tex-chp/" << dstTex2_ << " : contents/" << xml << std::endl;
  //  oss << "\t$(XT) contents/" << xml << " rml2texc-c.xsl tex-chp/"
  //      << dstTex2_ << std::endl;
  //  oss << std::endl;
  //}

  return oss.str();
}




/*--------------------------------------
*  class DbInfo_
*
*-------------------------------------*/
class DbInfo_
{
private:
  std::list<DbItem_> items_;

public:
  DbInfo_();

  void printXsl4Html(const std::string& path, const std::string& prefix);
  //void printXsl4Tex1(const std::string& path, const std::string& prefix);
  void printMakefile();
};


/*===============================
*  DbInfo_::DbInfo_()
*  last update: 2008.9.5
*==============================*/
DbInfo_::DbInfo_()
{
  using namespace std;
  namespace fs = std::filesystem;

  fs::directory_iterator end;

  // for DataBase Items
  fs::path targetdir1("db");
  for (fs::directory_iterator it(targetdir1); it != end; ++it)
  {
    if (fs::is_directory(*it))
    {
      string dirstr = it->path().filename().string();

      for (fs::directory_iterator jt(*it); jt != end; ++jt)
      {
        string src = jt->path().string();
        if (src.substr(src.length()-4) != ".met")
          continue;

        string srcstr = dirstr + "/" + jt->path().filename().string();

        metis::Element* root = metis::Parser::parse(src);
        rhea::SVisitor4GXml svgx;

        root->getChildByName("rhea:dbid").front()->text()->accept(svgx);
        string dbid = svgx.str();
        root->getChildByName("rhea:itemid").front()->text()->accept(svgx);
        string itemid = svgx.str();
        root->getChildByName("rhea:dst-html").front()->text()->accept(svgx);
        string dst = svgx.str();

        root->getChildByName("rhea:itemtitle").front()->text()->accept(svgx);
        string tt = svgx.str();


        DbItem_ di(dbid, itemid, dst, srcstr, tt);
        items_.push_back(di);

        delete root;
      }
    }
  }
}


/*======================================
*  DbInfo_::printXsl4Html()
*  last update: 2010.9.6
*=====================================*/
void DbInfo_::printXsl4Html(
  const std::string& path, const std::string& prefix)
{
  using namespace std;

  ofstream ofs(path.c_str());


  ofs << "<?xml version=\"1.0\"?>" << endl;
  ofs << "<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\""
         " xmlns:rhea=\"http://www.hiemalis.org/~acy/\""
         " exclude-result-prefixes=\"rhea\" version=\"1.0\">" << endl;
  ofs << "  <xsl:template match=\"rhea:dbitem\">" << endl;
  ofs << "    <xsl:choose>" << endl;

  std::list<DbItem_>::iterator it;
  for (it = items_.begin(); it != items_.end(); ++it)
    ofs << it->toXsl4Html(prefix);

  ofs << "    </xsl:choose>" << endl;
  ofs << "  </xsl:template>" << endl;
  ofs << "</xsl:stylesheet>" << endl;
}




/*========================================
*  DbInfo_::printMakefile()
*  last update: 2010.4.13
*=======================================*/
void DbInfo_::printMakefile()
{
  std::ofstream ofs("mediation/Makefile.D3");

//  ofs << "XT=java -Dcom.jclark.xsl.sax.parser="
//         "org.apache.xerces.parsers.SAXParser com.jclark.xsl.sax.Driver"
//      << std::endl << std::endl;

  ofs << "XP=xsltproc" << std::endl << std::endl;

  ofs << "all: ";
  std::list<DbItem_>::iterator it;
  for (it = items_.begin(); it != items_.end(); ++it)
    ofs << " html/" << it->getDstHtml();
  ofs << std::endl << std::endl;

  for (it = items_.begin(); it != items_.end(); ++it)
    ofs << it->toMakefile();
}


}// end of namespace




/*==========================================================
*  int main()
*=========================================================*/
int main()
{
  DbInfo_ dinfo;
  dinfo.printXsl4Html("mediation/db2html-d.xsl", "../");
  dinfo.printXsl4Html("mediation/db2html-t.xsl", "");

  dinfo.printMakefile();

  return 0;
}


//eof
