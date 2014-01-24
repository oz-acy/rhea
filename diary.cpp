/**************************************************************************
 *
 *  diary.cpp
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 7 Nov MMXI
 *
 *************************************************************************/

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <utility>
#include <metis/parser.h>
#include "diary.h"
#include "svisitor2met.h"




/*================================================
 *  DiItem::DiItem(const DiItem&)
 *
 *  update: 2011.11.7
 */
rhea::DiItem::DiItem(const DiItem& di)
  : year_(di.year_), yid_(di.yid_), month_(di.month_), date_(di.date_),
    ctype_(di.ctype_)
{
  ctitle_ = di.ctitle_ ? di.ctitle_->clone() : nullptr;
}


/*================================================
 *  DiItem::DiItem(DiItem&&)
 *
 *  update: 2011.11.7
 */
rhea::DiItem::DiItem(DiItem&& di)
  : year_(di.year_), yid_(di.yid_), month_(di.month_), date_(di.date_),
    ctype_(di.ctype_)
{
  ctitle_ = di.ctitle_;
  di.ctitle_ = nullptr;
}




/*================================================
*  DiItem::operator=(const DiItem&)
*
*  update: 2008.2.17
*/
rhea::DiItem& rhea::DiItem::operator=(const DiItem& di)
{
  if (this == &di)
    return *this;

  year_ = di.year_;
  yid_ = di.yid_;
  month_ = di.month_;
  date_ = di.date_;
  ctype_ = di.ctype_;

  delete ctitle_;
  ctitle_ = di.ctitle_ ? di.ctitle_->clone() : nullptr;

  return *this;
}


/*================================================
*  DiItem::operator=(DiItem&& di)
*
*  update: 2011.11.7
*/
rhea::DiItem& rhea::DiItem::operator=(DiItem&& di)
{
  std::swap(*this, di);

/*
  if (this == &di)
    return *this;

  year_ = di.year_;
  yid_ = di.yid_;
  month_ = di.month_;
  date_ = di.date_;
  ctype_ = di.ctype_;

  delete ctitle_;
  ctitle_ = di.ctitle_ ? di.ctitle_->clone() : nullptr;
*/
  return *this;
}




/*================================================
*  DiItem::operator<(const DiItem&)
*
*  大小關係は日附で決める
*  改元された場合、年の大小の判定部分を
*  修正する必要があることに注意
*
*  update: 2008.2.9
*===============================================*/
bool rhea::DiItem::operator<(const rhea::DiItem& y) const
{
  using boost::lexical_cast;

  if (lexical_cast<int>(yid_.substr(1)) < lexical_cast<int>(y.yid_.substr(1)))
  {
    return true;
  }
  else if (yid_.substr(1) == y.yid_.substr(1))
  {
    if (lexical_cast<int>(month_) < lexical_cast<int>(y.month_))
    {
      return true;
    }
    else if (month_ == y.month_)
    {
      if (lexical_cast<int>(date_) < lexical_cast<int>(y.date_))
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}


/*================================================
*  DiItem::toMetis()
*  リストソース用Metis記述を出力
*  update: 2008.2.16
*===============================================*/
std::string rhea::DiItem::toMetis() const
{
  std::ostringstream oss;

  oss << "@rhea:diary[year {";
  
  if (yid_[0] == 'H')
    oss << yid_.substr(1);
  else
    oss << yid_;

  oss << "}, month {" << month_ << "}, date {" << date_
      << "}, subid {" << ctype_ << "}]{";
  oss << year_ << "年" << month_ << "月" << date_ << "日";

  if (ctitle_)
  {
    rhea::SVisitor2Metis svm;
    ctitle_->accept(svm);
    oss << " " << svm.str();
  }

  oss << "}";

  return oss.str();
}


/*=====================================================
*  DiItem::filenamebase()
*  年月から、ファイル名から擴張子を除いた部分を導出
*  update: 2008.2.9
*====================================================*/
std::string rhea::DiItem::filenamebase() const
{
  std::ostringstream oss;

  if (yid_[0] == 'H')
    oss << yid_.substr(1);
  else
    oss << yid_;

  int m = boost::lexical_cast<int>(month_);
  if (m < 10)
    oss << "0" << m;
  else
    oss << m;

  return oss.str();
}




/*================================================
 *  DiItem::read()
 *  日記用記述を讀み込み、DiItemのリストを作成
 *  update: 2011.11.7
 *==============================================*/
std::list<rhea::DiItem> rhea::DiItem::read(const std::string& path)
{
  using namespace std;
  using metis::Element;
  using metis::StringData;

  cout << "process " << path << endl;

  Element* root = metis::Parser::parse(path);
  rhea::SVisitor2Metis svm;

  root->getChildByName("rhea:year").front()->text()->accept(svm);
  string year = svm.str();

  root->getChildByName("rhea:yearid").front()->text()->accept(svm);
  string yid = svm.str();

  root->getChildByName("rhea:month").front()->text()->accept(svm);
  string mon = svm.str();

  Element* body = root->getChildByName("rhea:body").front();
  list<DiItem> dis;
  list<Element*> days = body->getChildByName("rhea:day");
  list<Element*>::iterator it_d;

  for (it_d = days.begin(); it_d != days.end(); ++it_d)
  {
    (*it_d)->getAttrByName("date")->content()->accept(svm);
    string date = svm.str();

    // 經過措置的として殘置
    list<Element*> lcate = (*it_d)->getChildByName("rhea:category");
    list<Element*>::iterator it_c;
    for (it_c = lcate.begin(); it_c != lcate.end(); ++it_c)
    {
      (*it_c)->getAttrByName("type")->content()->accept(svm);
      string typ = svm.str();

      StringData* ti = nullptr;
      if ((*it_c)->getAttrByName("title"))
        ti = (*it_c)->getAttrByName("title")->content()->clone();

      dis.push_back(DiItem(year, yid, mon, date, typ, ti));
    }

    // 經過措置として殘置
    list<Element*> lgrp = (*it_d)->getChildByName("rhea:dgroup");
    if (!lgrp.empty())
    {
      Element* dgrp = lgrp.front();
      list<Element*> ldi = dgrp->getChildByName("rhea:ditem");
      list<Element*>::iterator it_i;
      for (it_i = ldi.begin(); it_i != ldi.end(); ++it_i)
      {
        (*it_i)->getAttrByName("type")->content()->accept(svm);
        string typ = svm.str();

        StringData* ti = nullptr;
        if (!(*it_i)->getChildByName("rhea:title").empty()
            && (*it_i)->getChildByName("rhea:title").front()->text())
          ti = (*it_i)->getChildByName("rhea:title").front()->text()->clone();

        dis.push_back(DiItem(year, yid, mon, date, typ, ti));
      }
    }

    // 本命はここ
    list<Element*> ldi = (*it_d)->getChildByName("rhea:ditem");
    list<Element*>::iterator it_i;
    for (it_i = ldi.begin(); it_i != ldi.end(); ++it_i)
    {
      (*it_i)->getAttrByName("type")->content()->accept(svm);
      string typ = svm.str();

      StringData* ti = nullptr;
      if (!(*it_i)->getChildByName("rhea:title").empty()
          && (*it_i)->getChildByName("rhea:title").front()->text())
        ti = (*it_i)->getChildByName("rhea:title").front()->text()->clone();

      dis.push_back(DiItem(year, yid, mon, date, typ, ti));
    }
  }

  return dis;
}




//eof
