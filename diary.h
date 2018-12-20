/**************************************************************************
 *
 *  diary.h
 *  by oZ/acy
 *  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 7 Nov MMXI
 *
 *************************************************************************/

#ifndef INC_RHEA_DIARY_H___
#define INC_RHEA_DIARY_H___


#include <sstream>
#include <metis/data.h>


namespace rhea {


/*------------------------------------------------
 *  DiItem
 *
 *  日記の一項目分のデータ
 *
 *  update: 2011.11.7
 *----------------------------------------------*/
class DiItem
{
private:
  std::string year_;
  std::string yid_;
  std::string month_;
  std::string date_;
  std::string ctype_;
  metis::StringData* ctitle_;


public:
  DiItem(
    const std::string& y, const std::string& yi, const std::string& m,
    const std::string& d, const std::string& ty, metis::StringData* ti)
    : year_(y), yid_(yi), month_(m), date_(d), ctype_(ty), ctitle_(ti)
    {}

  DiItem(const DiItem& di);
  DiItem(DiItem&& di);
  ~DiItem() { delete ctitle_; }

  DiItem& operator=(const DiItem& di);
  DiItem& operator=(DiItem&& di);

  bool isMember(const std::string& cate) const
    { return !ctype_.compare(0, cate.length(), cate); }

  bool operator<(const DiItem&) const;
  bool operator==(const DiItem& y) const
    { return yid_ == y.yid_ && month_ == y.month_ && date_ == y.date_; }

  std::string toMetis() const;
  std::string filenamebase() const;

  static std::list<DiItem> read(const std::string& path);
};



}// end of namespace rhea


#endif // INC_RHEA_DIARY_H___
