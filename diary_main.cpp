/**************************************************************************
 *
 *  diary_main.cpp
 *  by oZ/acy
 *  (c) 2005-2018 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 21 Dec MMXVIII
 *
 *************************************************************************/

#include <fstream>
#include <experimental/filesystem>
//#include <filesystem>
//#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <metis/strescape.h>
#include "diary.h"


/*=====================================================
*  createDiItemList()
*  DiItem のリストをつくり、Makefile.D2 を出力
*  update: 2018.12.21 とりあへず假置き
*====================================================*/
std::list<rhea::DiItem> createDiItemList()
{
  using namespace std;
  using namespace rhea;
  //namespace fs = boost::filesystem;
  //namespace fs = std::filesystem;
  namespace fs = std::experimental::filesystem;

  ostringstream mkos;
  ostringstream alos;

  list<DiItem> dis;
  fs::path targetdir("diary");
  fs::directory_iterator end;
  for (fs::directory_iterator it(targetdir); it != end; ++it)
  {
    string src = it->path().string();
    if (src.substr(src.length() - 4) != ".met")
      continue;

    list<DiItem> a = DiItem::read(src);

    dis.splice(dis.end(), a);

    string fn = it->path().filename().string();
    string tgtsrc = fn.substr(0, fn.length() - 4);
    string tgtxml = string("diary/") + tgtsrc + ".xml";
    string tgthtml = string("html/diary/") + tgtsrc + ".html";

    mkos << tgtxml << " : diary/" << fn << endl;
    mkos << "\tmetis2xml diary/" << fn << " " << tgtxml << endl << endl;

    mkos << tgthtml << " : " << tgtxml << endl;
    mkos << "\t$(XP) -o " << tgthtml << " diml2html-c.xsl " << tgtxml
         << endl << endl;

    alos << " " << tgthtml;
  }

  // ファイルを開いて先頭部分を出力
  ofstream ofs("mediation/Makefile.D2", ios::binary);
//  ofs << "XT=java "
//         "-Dcom.jclark.xsl.sax.parser=org.apache.xerces.parsers.SAXParser "
//         "com.jclark.xsl.sax.Driver"
//      << endl << endl;
  ofs << "XP=xsltproc" << endl << endl;


  // ターゲット關係
  ofs << "all:" << alos.str()
      //<< " html/diary/latest.html html/diary/latest.rdf"
      //   " mediation/top/diary.html"
      << endl << endl;


  // latest關係
  //dis.sort();
  //string latest = dis.back().filenamebase() + ".xml";

  //ofs << "html/diary/latest.html : diary/" << latest << endl;
  //ofs << "\t$(XP) -o html/diary/latest.html diml2html-l.xsl diary/" << latest
  //    << endl << endl;

  //ofs << "html/diary/latest.rdf : diary/" << latest << endl;
  //ofs << "\t$(XP) -o html/diary/latest.rdf diml2rss-l.xsl diary/" << latest
  //    << endl << endl;


  // 一覽關係
  //ofs << "mediation/top/diary.html : diary/" << latest << endl;
  //ofs << "\t$(XP) -o mediation/top/diary.html diml2html-t.xsl diary/" << latest
  //    << endl << endl;

  // 各日記の依存關係
  ofs << mkos.str();


  // 終端
  ofs << "#eof" << endl;

  return dis;
}




/*=========================================================================
 *  outputCategoryList()
 *  分類一覽を出力
 *  基本的にソースは .rdi であるので、
 *  ベタテキスト => Metis となる。
 *  Metis => 中間構造 => Metis になる部分の出力は
 *  it->toMetis() の部分のみ
 *
 *  H23.4.25 update for boost-1.46.1
 *  H30.12.21 update for C++17? (filesystem: boost->std::experimental) 
 *======================================================================*/
void outputCategoryList(std::list<rhea::DiItem>& dis)
{
  using namespace std;
  //namespace fs = boost::filesystem;
  //namespace fs = std::filesystem;
  namespace fs = std::experimental::filesystem;
  fs::path targetdir("contents");
  targetdir /= "diary";

  fs::directory_iterator end;
  for (fs::directory_iterator it(targetdir); it != end; ++it)
  {
    string src = it->path().string();
    if (src.substr(src.length()-4) != ".rdi")
      continue;

    ifstream ifs(src.c_str());
    ostringstream bos;
//    ostringstream los;
    string tstr, idstr, dhstr;

    getline(ifs, tstr);
    getline(ifs, idstr);
    getline(ifs, dhstr);

    while (ifs)
    {
      string typ, ti;
      ifs >> typ;
      if (!ifs)
        break;
      ifs >> ti;
      if (!ifs)
        break;

//      los << "@item{@rhea:ref[id{this}, subid{"
//          << metis::StringEscape(typ) << "}]{"
//          << metis::StringEscape(ti)
//          << "}}" << endl;

      bos << "@rhea:section[id{"
          << metis::StringEscape(typ) << "}]{" << endl;
      bos << "@rhea:title{" << metis::StringEscape(ti) << "}" << endl;
      bos << "@rhea:list{" << endl;

      list<rhea::DiItem>::reverse_iterator it;
      for (it = dis.rbegin(); it != dis.rend(); ++it)
      {
        if (it->isMember(typ))
          bos << "@rhea:item{" << it->toMetis() << "}" << endl;
      }

      bos << "}" << endl;
      bos << "}" << endl;
    }

    //norn::CharCodeConverter cnvSjisEuc(norn::CC_SHIFT_JIS, norn::CC_EUC_JP);
    string dst = src.substr(0, src.length() - 4) + ".met";
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    ofstream ofs(dst.c_str(), ios::binary);

    ofs << "@rhea:content[xmlns:rhea {http://www.hiemalis.org/~acy/}]{" << endl;
    ofs << "@rhea:content-id{" << idstr << "}" << endl;
    ofs << "@rhea:dst-html{" << dhstr << "}" << endl;
    ofs << "@title{" << metis::StringEscape(tstr) << "}" << endl;
    ofs << "@nickname{穴拔け日記}" << endl;

    ofs << "@rhea:css{def3.css}" << endl;

    ofs << "@rhea:foot-notice{"
        << "@rhea:copy; 2000-" << today.year()
        << " oZ/acy, 多言數窮."
        << " ALL RIGHTS RESERVED."
        << "}" << endl;

    ofs << "@rhea:navi{" << endl;
    ofs << "@rhea:path{@rhea:ref[id {root}];}" << endl;
    ofs << "@rhea:path{@rhea:ref[id {diary-index}];}" << endl;
    ofs << "@rhea:notice{@rhea:ref[id {guide-top}];}" << endl;
    ofs << "}" << endl;

//    ofs << "@rhea:flist{" << endl;
//    ofs << los.str() << endl;
//    ofs << "}" << endl;

    ofs << "@rhea:body{" << endl;
    ofs << bos.str() << endl;
    ofs << "}" << endl;

    ofs << "}" << endl;
  }
}


/*=====================================================
*  main()
*====================================================*/
int main()
{
  using namespace std;

  list<rhea::DiItem> dis = createDiItemList();
  outputCategoryList(dis);

  return 0;
}


//eof
