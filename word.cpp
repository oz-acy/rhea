/**************************************************************************
 *
 *  word.cpp
 *  by oZ/acy
 *  (c) 2005-2016 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  履歴
 *    2016.3.1  修正
 *
 *************************************************************************/

#include <algorithm>
#include <utility>
#include <iostream>
#include <sstream>
#include <metis/parser.h>
#include "word.h"
#include "svisitor4gxml.h"
#include "svisitor2tex.h"



/*=====================================================
 *  Word::Word()
 *  update: 2011.11.7
 *====================================================*/
rhea::Word::Word(metis::Element* word)
  : entry_(nullptr), order_(nullptr), abbr_(nullptr), note_(nullptr)
{
  using namespace std;
  using namespace metis;

  // 見出し・順番
  entry_ = word->getChildByName("entry").front()->text()->clone();
  order_ = word->getChildByName("order").front()->text()->clone();

  // 略語
  if (!word->getChildByName("abbr").empty())
    abbr_ = word->getChildByName("abbr").front()->text()->clone();

  // 註釋
  if (!word->getChildByName("note").empty())
    note_ = word->getChildByName("note").front()->text()->clone();

  // 語解
  existdefs_ = !word->getChildByName("def").empty();

  // 雜説
  existbody_ = !word->getChildByName("body").empty();


  // 選擇情報
  list<Element*>::iterator it;
  list<Element*> sels = word->getChildByName("select");
  for (it = sels.begin(); it != sels.end(); ++it)
    selects_.push_back((*it)->text()->clone());
  if (selects_.empty())
    selects_.push_back(entry_->clone());

  // 分類
  list<Element*> cates = word->getChildByName("category");
  for (it = cates.begin(); it != cates.end(); ++it)
    categories_.push_back((*it)->text()->clone());
}


/*=====================================================
 *  Word::Word(const Word&)
 *  update: 2011.11.7
 *===================================================*/
rhea::Word::Word(const rhea::Word& w)
  : entry_(nullptr), order_(nullptr), abbr_(nullptr), note_(nullptr),
    existdefs_(w.existdefs_), existbody_(w.existbody_)
{
  using namespace std;
  using namespace metis;

  entry_ = w.entry_->clone();
  order_ = w.order_->clone();

  if (w.abbr_)
    abbr_ = w.abbr_->clone();

  if (w.note_) {
    note_ = w.note_->clone();
  }


  list<StringData*>::const_iterator it;

  // 選擇情報
  for (it = w.selects_.begin(); it != w.selects_.end(); ++it)
    selects_.push_back((*it)->clone());

  // 分類
  for (it = w.categories_.begin(); it != w.categories_.end(); ++it)
    categories_.push_back((*it)->clone());
}


/*=====================================================
 *  Word::Word(Word&&)
 *  update: 2011.11.7
 *===================================================*/
rhea::Word::Word(rhea::Word&& w)
  : entry_(w.entry_), order_(w.order_), abbr_(w.abbr_), note_(w.note_),
    existdefs_(w.existdefs_), existbody_(w.existbody_)
{
  w.entry_ = nullptr;
  w.order_ = nullptr;
  w.abbr_ = nullptr;
  w.note_ = nullptr;
  std::swap(selects_, w.selects_);
  std::swap(categories_, w.categories_);
}




/*=====================================================
*  Word::~Word()
*  update: 2008.2.17
*====================================================*/
rhea::Word::~Word()
{
  using namespace std;
  using namespace metis;

  delete entry_;
  delete order_;
  delete abbr_;
  delete note_;

  list<StringData*>::iterator it;

  // 選擇情報
  for (it = selects_.begin(); it != selects_.end(); ++it)
    delete *it;

  // 分類
  for (it = categories_.begin(); it != categories_.end(); ++it)
    delete *it;
}


/*=====================================================
 *  Word::operator=(const Word&)
 *  update: 2011.11.7
 *===================================================*/
rhea::Word& rhea::Word::operator=(const rhea::Word& w)
{
  using namespace std;
  using namespace metis;

  if (this == &w)
    return *this;

  delete entry_; 
  delete order_;
  entry_ = w.entry_->clone();
  order_ = w.order_->clone();

  delete abbr_;
  abbr_ = w.abbr_ ? w.abbr_->clone() : nullptr;

  delete note_;
  note_ = w.note_ ? w.note_->clone() : nullptr;

  existdefs_ = w.existdefs_;
  existbody_ = w.existbody_;


  list<StringData*>::const_iterator it;

  // 選擇情報
  for (it = selects_.begin(); it != selects_.end(); ++it)
    delete *it;

  selects_.clear();

  for (it = w.selects_.begin(); it != w.selects_.end(); ++it)
    selects_.push_back((*it)->clone());


  // 分類
  for (it = categories_.begin(); it != categories_.end(); ++it)
    delete *it;

  categories_.clear();

  for (it = w.categories_.begin(); it != w.categories_.end(); ++it)
    categories_.push_back((*it)->clone());


  return *this;
}


/*=====================================================
 *  Word::operator=(Word&&)
 *  update: 2011.11.7
 *===================================================*/
rhea::Word& rhea::Word::operator=(rhea::Word&& w)
{
  std::swap(*this, w);
  return *this;
}




/*=====================================================
*  Word_::parseDic()
*  update: 2008.2.14
*====================================================*/
std::list<rhea::Word> rhea::Word::parseDic(const std::string& path)
{
  metis::Element* root = metis::Parser::parse(path);
  std::list<Word> words;
  std::list<metis::Element*> ws = root->getChildByName("word");
  std::list<metis::Element*>::iterator it;

  for (it = ws.begin(); it != ws.end(); ++it)
    words.push_back(Word(*it));

  return words;
}




/*=====================================================
 *  Word::toXsl4Html()
 *
 *  履歴
 *    2008.9.19  update
 *    2016.3.1   修正(Clang + libc++-v3でリンクエラーが出たので廻避)
 */
std::string rhea::Word::toXsl4Html(const std::string& prefix) const
{
  using namespace std;

  ostringstream oss;
  SVisitor4GXml svgx;

  list<metis::StringData*>::const_iterator it;
  for (it = selects_.begin(); it != selects_.end(); ++it)
  {
    (*it)->accept(svgx);
    oss << "      <xsl:when test=\"@select='" << svgx.str() << "'\">";

    // entryに指定された文字列
    entry_->accept(svgx);
    string es
      = "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">"
        "<xsl:apply-templates /></xsl:if><xsl:if test=\"not(boolean(text())) "
        "and (count(child::node())=0)\">";
    es += svgx.str();
    es += "</xsl:if>";
    //string es = svgx.str();
    //es = "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">"
    //     "<xsl:apply-templates /></xsl:if><xsl:if test=\"not(boolean(text())) "
    //     "and (count(child::node())=0)\">" + es + "</xsl:if>";

    if (existbody_ || existdefs_)
    { // リンクを生成
      string target = prefix + "dict/" + htmlFileName();
      oss << "<a href=\"" << target << "\" class=\"word\">";

      if (!abbr_)
      { // 略語ではない
        if (!note_)
        { // 註釋附きでもない
          oss << es;
        }
        else
        { // 註釋附き
          note_->accept(svgx);
          oss << "<span class=\"note\" title=\"" << svgx.str() << "\">";
          oss << es;
          oss << "</span>";
        }
      }
      else
      { // 略語
        abbr_->accept(svgx);
        oss << "<abbr title=\"" << svgx.str() << "\">";
        entry_->accept(svgx);
        oss << svgx.str();
        oss << "</abbr>";
      }
      oss << "</a>";
    }
    else
    { // リンクは不要
      if (!abbr_)
      { // 略語ではない
        if (!note_)
        { // 註釋附きでもない
          oss << es;
        }
        else
        { // 註釋附き
          note_->accept(svgx);
          oss << "<span class=\"note\" title=\"" << svgx.str() << "\">";
          oss << es;
          oss << "</span>";
        }
      }
      else
      { // 略語
        abbr_->accept(svgx);
        oss << "<abbr title=\"" << svgx.str() << "\">";
        oss << es;
        oss << "</abbr>";
      }
    }
    oss << "</xsl:when>" << endl;
  }

  return oss.str();
}


/*=====================================================
*  Word::toXsl4Tex()
*  update: 2008.2.17
*====================================================*/
std::string rhea::Word::toXsl4Tex() const
{
  using namespace std;

  ostringstream oss;
  SVisitor4GXml svgx;
  SVisitor2Tex svt;

  list<metis::StringData*>::const_iterator it;
  for (it = selects_.begin(); it != selects_.end(); ++it)
  {
    (*it)->accept(svgx);
    oss << "      <xsl:when test=\"@select='" << svgx.str() << "'\">";

    //
    entry_->accept(svt);
    oss << svt.str();

    if (!abbr_)
    { // 略語ではない
      if (note_)
      { // 註釋附き
        oss << "\\footnote{";
        note_->accept(svt);
        oss << svt.str();
        oss << "}";
      }
    }
    else
    { // 略語
      oss << "\\footnote{";
      abbr_->accept(svt);
      oss << svt.str();
      oss << "}";
    }

    oss << "</xsl:when>" << endl;
  }

  return oss.str();
}


/*================================================
*  Word::isListedUp()
*  update: 2008.2.14
*===============================================*/
namespace {

class IsEqu_
{
private:
  std::string s_;

public:
  IsEqu_(const std::string& s) : s_(s) {}

  bool operator()(metis::StringData* sd) const
    {
      metis::StringVisitor sv;
      sd->accept(sv);
      return (s_ == sv.str());
    }
};


}// end of namespace


bool rhea::Word::isListedUp(const std::string& ct) const
{
  if (!existdefs_ && !existbody_)
    return false;

  IsEqu_ ie(ct);
  std::list<metis::StringData*>::const_iterator it;
  it = std::find_if(categories_.begin(), categories_.end(), ie);

  if (it == categories_.end())
    return false;
  else
    return true;
}



//eof
