/**************************************************************************
*
*  rel-ref.cpp
*  by oZ/acy
*  (c) 2005-2016 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 2016.10.20
*
**************************************************************************/


#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <metis/parser.h>
#include "rel-ref.h"




namespace {

// hoge.met‚©‚çContent‚ğ‚Â‚­‚èAmap‚É“o˜^
// update: 2013.06.30
void
insertContentToMap_S(
  std::string& src, std::string& srcstr,
  std::map<std::string, rhea::Content>& c1,
  std::map<std::string, rhea::Content>& c2)
{
  using namespace std;
  using namespace metis;

  list<string> lid;

  cout << srcstr << endl;
  metis::Element* root = metis::Parser::parse(src);


  // ID
  list<Element*> le = root->getChildByName("rhea:content-id");
  list<Element*>::iterator it;
  for (it = le.begin(); it != le.end(); ++it)
  {
    lid.push_back((*it)->text()->getText());
  }

  // ƒ^ƒCƒgƒ‹ (Nickname—Dæ)
  std::string title;

  if (root->getChildByName("nickname").empty())
  {
    if (!root->getChildByName("rhea:title").empty())
      title = root->getChildByName("rhea:title").front()->text()->getText();
    else if (!root->getChildByName("title").empty())
      title = root->getChildByName("title").front()->text()->getText();
    else
      title = "???";
  }
  else
    title = root->getChildByName("nickname").front()->text()->getText();

  rhea::Content ct(srcstr, title);

  // Œ‹‰ÊƒpƒX‚ğæ“¾o˜Ò‚½‚ç ct ‚É“o˜^‚µ‚Ä‚¨‚­
  if (!root->getChildByName("rhea:dst-html").empty())
  {
    ct.setDstHtml(
      root->getChildByName("rhea:dst-html").front()->text()->getText());
  }

  // È—ª‘O‚Ì•\Œ»‚ğæ“¾‚Å‚«‚½‚ç ct ‚É“o˜^‚µ‚Ä‚¨‚­
  if (!root->getChildByName("rhea:abbr-from").empty())
  {
    ct.setAbbr(
      root->getChildByName("rhea:abbr-from").front()->text()->getText());
  }

  // ’ç×‚ğæ“¾‚Å‚«‚½‚ç ct ‚É“o˜^‚µ‚Ä‚¨‚­
  if (!root->getChildByName("rhea:annotated").empty())
  {
    ct.setNote(
      root->getChildByName("rhea:annotated").front()->text()->getText());
  }

  // Œê‰ğš˜^‚Ì“à—e‚Å‚ ‚ê‚Î ct ‚É“o˜^‚µ‚Ä‚¨‚­
  if (!root->getChildByName("rhea:word-of-dic").empty())
  {
    ct.setAsWord();
  }

  // ct ‚ğ map ‚É“o˜^
  list<string>::iterator jt;
  jt = lid.begin();
  c1.insert(make_pair(*jt, ct));
  for (++jt; jt != lid.end(); ++jt)
    c2.insert(make_pair(*jt, ct));

  delete root;
}




// contentsˆÈ‰º‚ÌƒfƒBƒŒƒNƒgƒŠ‚ğ~‚è‚Ä‚¢‚­‚Ì‚Ég‚Ó”ŸÉ
// update: 2011.4.25
void
rcsvDownDirContents_S(
  boost::filesystem::directory_iterator dit, std::string dirstr,
  std::map<std::string, rhea::Content>& c1,
  std::map<std::string, rhea::Content>& c2)
{
  using namespace std;
  namespace fs = boost::filesystem;

  fs::directory_iterator end;

  for (fs::directory_iterator djt(*dit); djt != end; ++djt)
  {
    if (fs::is_directory(*djt))
    {
      string dirstr2 = dirstr + "/" + djt->path().filename().string();
      rcsvDownDirContents_S(djt, dirstr2, c1, c2);
    }
    else
    {
      string src = djt->path().string();
      if (src.substr(src.length()-4) != ".met")
        continue;

      string srcstr = dirstr + "/" + djt->path().filename().string();
      insertContentToMap_S(src, srcstr, c1, c2);
    }
  }
}




}//end of namespace




/*===============================
 *  ContentSet::ContentSet()
 *  update: 2011.10.05
 */
rhea::ContentSet::ContentSet()
{
  using namespace std;
  namespace fs = boost::filesystem;

  try
  {
    fs::path tgt("contents");

    fs::directory_iterator end;
    for (fs::directory_iterator it(tgt); it != end; ++it)
    {
      if (fs::is_directory(*it))
      {
        string dirstr = it->path().filename().string();
        rcsvDownDirContents_S(it, dirstr, contents_, contents2_);
      }
    }
  }
  catch (fs::filesystem_error& ferr)
  {
    cerr << "FE: " << ferr.what() << endl;
    return;
  }
  catch (...)
  {
    cerr << "error ???" << endl;
  }
}



/*========================================
*  ContentSet::printMakefile()
*  update: 2011.10.05
*=======================================*/
void rhea::ContentSet::printMakefile()
{
  std::ofstream ofs("mediation/Makefile.R");

  ofs << "XP=xsltproc" << std::endl << std::endl;

  ofs << "all: ";
  std::map<std::string, Content>::iterator it;
  for (it = contents_.begin(); it != contents_.end(); ++it)
  {
    if (!it->second.getDstHtml().empty())
    {
      ofs << " html/" << it->second.getDstHtml();
    }
  }
  ofs << std::endl << std::endl;

  for (it = contents_.begin(); it != contents_.end(); ++it)
  {
    ofs << it->second.toMakefile();
  }
}


/*========================================
*  ContentSet::printLog()
*  update: 2011.10.05
*=======================================*/
void rhea::ContentSet::printLog()
{
  std::ofstream ofs("relation/autogen.rri");

  std::map<std::string, Content>::iterator it;
  for (it = contents_.begin(); it != contents_.end(); ++it)
  {
    ofs << it->second.toLog(it->first);
  }
  for (it = contents2_.begin(); it != contents2_.end(); ++it)
  {
    ofs << it->second.toLog(it->first);
  }
}




/*======================================================
*  Content::toMakefile()
*  Makefile‚ÉˆË‘¶èŒW‚ğo—Í
*=====================================================*/
std::string rhea::Content::toMakefile() const
{
  std::ostringstream oss;

  std::string xml = src_.substr(0, src_.length() - 4) + ".xml";

  // .met to .xml
  oss << "contents/" << xml << " : contents/" << src_ << std::endl;
  oss << "\tmetis2xml contents/"<< src_ << " contents/" << xml << std::endl;
  oss << std::endl;

  // for Html
  if (!dst_.empty())
  {
    oss << "html/" << dst_ << " : contents/" << xml << std::endl;
    oss << "\t$(XP) -o html/" << dst_
        << " rml2html-c.xsl contents/" << xml
        << std::endl;
    oss << std::endl;
  }

  // for Tex (1)
  //if (!dstTex1_.empty())
  //{
  //  oss << "tex/" << dstTex1_ << " : contents/" << xml << std::endl;
  //  oss << "\t$(XP) -o tex/" << dstTex1_ << " rml2tex-c.xsl contents/" << xml
  //      << std::endl;
  //  oss << std::endl;
  //}

  // for Tex (2)
  //if (!dstTex2_.empty())
  //{
  //  oss << "tex-chp/" << dstTex2_ << " : contents/" << xml << std::endl;
  //  oss << "\t$(XP) -o tex-chp/" << dstTex2_
  //      << " rml2texc-c.xsl contents/" << xml
  //      << std::endl;
  //  oss << std::endl;
  //}

  return oss.str();
}


/*=========================================================
 *  Content::toLog()
 *  create: 2011.09.12
 *  update: 2011.10.07
 *========================================================*/
std::string
rhea::Content::toLog(const std::string& id) const
{
  std::ostringstream oss;

  if (dst_.size())
  {
    oss << "I\t" << id << "\t" << dst_ << "\t";
  }
  else
  {
    oss << "N\t" << id << "\tnone\t";
  }
  
  if (!abbr_.empty()) {
    if (isWord_)
      oss << "AW\t" << title_ << "\t" << abbr_ << std::endl;
    else
      oss << "A\t" << title_ << "\t" << abbr_ << std::endl;
  } else if (!note_.empty()) {
    if (isWord_)
      oss << "NW\t" << title_ << "\t" << note_ << std::endl;
    else
      oss << "N\t" << title_ << "\t" << note_ << std::endl;
  }
  else if (isWord_)
    oss << "W\t" << title_ << std::endl;
  else
    oss << "S\t" << title_ << std::endl;

  return oss.str();
}


/*==================================
 *  int main()
 */
int main()
{
  rhea::ContentSet cs;
  cs.printMakefile();
  cs.printLog();

  return 0;
}


//eof
