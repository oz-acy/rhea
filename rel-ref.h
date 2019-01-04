/**************************************************************************
*
*  rel-ref.h
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 7 Oct MMXI
*
**************************************************************************/

#ifndef INC_RHEA_RELATION_REFERRED_H___
#define INC_RHEA_RELATION_REFERRED_H___

#include <string>
#include <map>
#include "metis/data.h"



namespace rhea {


/*-------------------------------------------
 *  class Content : public ReferredBase
 *  コンテント (サイト内文書) の情報
 *  update: 2011.10.7
 *------------------------------------------*/
class Content
{
private:
  std::string dst_;
  std::string src_;
  std::string title_;

  std::string abbr_;
  std::string note_;
  bool isWord_;

public:
  Content(const std::string& s, const std::string& t)
    : title_(t), src_(s), isWord_(false)
    {}

  void setDstHtml(const std::string& d) { dst_ = d; }
  const std::string& getDstHtml() const { return dst_; }

  void setAbbr(const std::string& a) { abbr_ = a; }
  void setNote(const std::string& n) { note_ = n; }
  void setAsWord() { isWord_ = true; }

  std::string toMakefile() const;
  std::string toLog(const std::string& id) const;
};


class ContentSet
{
private:
  std::map<std::string, Content> contents_;
  std::map<std::string, Content> contents2_;

public:
  ContentSet();

  void printMakefile();
  void printLog();
};




}// end of namespace rhea




#endif // INC_RHEA_RELATION_REFERRED_H___
