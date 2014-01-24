/**************************************************************************
 *
 *  word.h
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 7 Nov MMXI
 *
 *************************************************************************/

#ifndef INC_RHEA_WORD_H___
#define INC_RHEA_WORD_H___

#include <metis/data.h>




namespace rhea {


/*-----------------------------------------------------
 *  class Word
 *  update: 2011.11.7
 *----------------------------------------------------*/
class Word
{
private:
  metis::StringData* entry_;
  metis::StringData* order_;
  std::list<metis::StringData*> selects_;
  std::list<metis::StringData*> categories_;
  metis::StringData* abbr_;  // 略語の註釋
  metis::StringData* note_;  // 註釋
  bool existdefs_;  // 定義は存在するか
  bool existbody_;  // 雜説は存在するか


  //std::list<metis::StringData*> defs_;  // あるかないかが必要
  //metis::StringData* body_;  // あるかないかの情報が必要


public:
  Word(metis::Element* word);
  Word(const Word& w);
  Word(Word&& w);
  ~Word();

  Word& operator=(const Word& w);
  Word& operator=(Word&& w);

  metis::StringData* entry() const { return entry_; }
  std::string toXsl4Html(const std::string& prefix) const;
  std::string toXsl4Tex() const;

  std::string htmlFileName() const { return id() + ".html"; }
  std::string id() const { return selects_.front()->getUtf8Code(); }

  bool operator<(const Word& y) const { return *order_ < *(y.order_); }
  bool operator==(const Word& y) const { return *order_ == *(y.order_); }

  bool isListedUp(const std::string& ct) const;

  static std::list<Word> parseDic(const std::string& path);
};


}// end of namespace rhea



#endif // INC_RHEA_WORD_H___
