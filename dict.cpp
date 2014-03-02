/**************************************************************************
 *
 *  dict.cpp
 *  by oZ/acy
 *  (c) 2005-2014 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 3 March MMXIV
 *
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <metis/strescape.h>
#include "svisitor2met.h"
#include "dict.h"


/*=====================================================
*  Dictionary::Dictionary()
*  update: 2011.4.25
*====================================================*/
rhea::Dictionary::Dictionary()
{
  using namespace std;
  namespace fs = boost::filesystem;

  fs::directory_iterator end;

  // for 'dict'
  fs::path targetdir1("dict");
  for (fs::directory_iterator it(targetdir1); it != end; ++it)
  {
    string src = it->path().string();
    if (src.substr(src.length()-4) != ".met")
      continue;

    cout << "input file " << src << endl;
    list<Word> ws = Word::parseDic(src);
    words_.insert(words_.end(), ws.begin(), ws.end());
  }

  words_.sort();
}


/*=====================================================
*  Dictionary::printXsl4Html()
*  update: 2010.9.6
*====================================================*/
void
rhea::Dictionary::printXsl4Html(std::ostream& os, const std::string& prefix)
{
  os << "<?xml version=\"1.0\"?>" << std::endl;
  os << "<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\""
        " xmlns:rhea=\"http://www.hiemalis.org/~acy/\""
        " exclude-result-prefixes=\"rhea\" version=\"1.0\">"
     << std::endl;
  os << "  <xsl:template match=\"rhea:word\">" << std::endl;
  os << "    <xsl:choose>" << std::endl;

  std::list<Word>::iterator it;
  for (it = words_.begin(); it != words_.end(); ++it)
    os << it->toXsl4Html(prefix);

  os << "    </xsl:choose>" << std::endl;
  os << "  </xsl:template>" << std::endl;
  os << "</xsl:stylesheet>" << std::endl;
}


/*=====================================================
*  Dictionary::printXsl4Tex()
*  update: 2010.9.6
*====================================================*/
void rhea::Dictionary::printXsl4Tex(std::ostream& os)
{
  os << "<?xml version=\"1.0\"?>" << std::endl;
  os << "<xsl:stylesheet xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\""
        " xmlns:rhea=\"http://www.hiemalis.org/~acy/\""
        " exclude-result-prefixes=\"rhea\" version=\"1.0\">"
     << std::endl;
  os << "  <xsl:template match=\"rhea:word\">" << std::endl;
  os << "    <xsl:choose>" << std::endl;

  std::list<Word>::iterator it;
  for (it = words_.begin(); it != words_.end(); ++it)
    os << it->toXsl4Tex();

  os << "    </xsl:choose>" << std::endl;
  os << "  </xsl:template>" << std::endl;
  os << "</xsl:stylesheet>" << std::endl;
}


/*=====================================================
*  Dictionary_::printMakefile4Html()
*  update: 2010.4.13
*====================================================*/
void rhea::Dictionary::printMakefile4Html(std::ostream& os)
{
  using namespace std;
  namespace fs = boost::filesystem;

  ostringstream mkos;
  ostringstream alos;

  fs::path targetdir("dict");
  fs::directory_iterator end;
  for (fs::directory_iterator it(targetdir); it != end; ++it)
  {
    string src = it->path().string();
    if (src.substr(src.length()-4) != ".met")
      continue;

    string fn = it->path().filename().string();
    string tgtsrc = fn.substr(0, fn.length() - 4);
    string tgtxml = string("dict/") + tgtsrc + ".xml";
    string tgthtml = string("mediation/dict/") + tgtsrc + ".xml.html";

    mkos << tgtxml << " : dict/" << fn << endl;
    mkos << "\tmetis2xml dict/" << fn << " " << tgtxml << endl << endl;

    mkos << tgthtml << " : " << tgtxml << endl;
    mkos << "\t$(XP) -o " << tgthtml << " dic2html.xsl " << tgtxml << endl;
    mkos << "\trhea-dicout " << tgthtml << " html/dict" << endl << endl;

    alos << " " << tgthtml;
  }


//  os << "XT=java "
//        "-Dcom.jclark.xsl.sax.parser=org.apache.xerces.parsers.SAXParser "
//        "com.jclark.xsl.sax.Driver"
//     << endl << endl;
  os << "XP=xsltproc" << endl << endl;
  os << "all:" << alos.str() << endl << endl;
  os << mkos.str();
  os << "#eof" << endl;
}


/*=====================================================
*  Dictionary::outputList()
*  update: 2014.3.3
*====================================================*/
void
rhea::Dictionary::outputList(
  const std::string& cate, const std::string& id,
  const std::string& pf_html, const std::string& poststr)
{
  using namespace std;

  string tgt = string("contents/dict/top") + pf_html + ".met";
  ofstream ofs(tgt.c_str(), ios::binary);
  boost::gregorian::date today = boost::gregorian::day_clock::local_day();


  ofs << "@rhea:content[xmlns:rhea {http://www.hiemalis.org/~acy/}]{" << endl;
  ofs << "@rhea:content-id{" << id << "}" << endl;
  ofs << "@rhea:dst-html{dict/index" << pf_html << ".html}" << endl;

  ofs << "@title{" << "語解字録" << metis::StringEscape(poststr)
      << "}" << endl;
  ofs << "@nickname{語解字録}" << endl;

  ofs << "@rhea:foot-notice{" << endl;
  ofs << "@rhea:copy; 2000-" << today.year() << " oZ/acy, 多言數窮." << endl;
  ofs << " ALL RIGHTS RESERVED." << endl;
  ofs << "}" << endl;

  ofs << "@rhea:css{shift-r3a.css}" << endl;
  ofs << "@rhea:navi{" << endl;
  ofs << "@rhea:path{@rhea:ref[id {root}];}" << endl;
  ofs << "@rhea:notice{@rhea:ref[id {guide-top}, subid {doc}]"
         "{此の文書に就いて}}" << endl;
  ofs << "}" << endl;

  ofs << "@rhea:body{" << endl;
  ofs << "@section{" << endl;
  ofs << "@title{見出し一覽}" << endl;
  ofs << "  @list[type {runin}]{" << endl;

  list<Word>::iterator it;
  for (it = words_.begin(); it != words_.end(); ++it)
  {
    if (it->isListedUp(cate))
    {
      ofs << "    @item{";

      SVisitor2Metis svm;
      it->entry()->accept(svm);
      ofs << "@link[url {" << it->htmlFileName() << "}]{"
          << svm.str() << "}";

      ofs << "}" << endl;
    }
  }

  ofs << "  }" << endl;
  ofs << "}" << endl;
  ofs << "}" << endl;
  ofs << "}" << endl;
}


//eof
