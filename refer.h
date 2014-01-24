/**************************************************************************
 *
 *  refer.h
 *  by oZ/acy
 *  (c) 2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 8 Oct MMXI
 *
 *************************************************************************/

#ifndef INC_RHEA_REFER_H___
#define INC_RHEA_REFER_H___

#include <sstream>
#include <string>
#include "metis/data.h"


namespace rhea {

/*-------------------------------------------
 *  ReferBase
 *  �ҏƛ��ۊ��
 *
 *  update: 2011.10.08
 *-----------------------------------------*/
class ReferBase
{
public:
  enum T_ {
    TY_SIMPLE,
    TY_WORD,
    TY_ABBR,
    TY_NOTE
  };

private:
  std::string dst_;     // �����p�X or URL
  std::string title_;   // �^�C�g��
  std::string subtext_; // �T�u�e�L�X�g
  T_ typ_;              // �T�u�e�L�X�g�^�C�v
  bool isWord_;

protected:
  ReferBase(const std::string& t)
    : title_(t), typ_(TY_SIMPLE), isWord_(false)
    {}

  ReferBase(const std::string& d, const std::string& t)
    : dst_(d), title_(t), typ_(TY_SIMPLE), isWord_(false)
    {}

  ReferBase(
    const std::string& d, const std::string& t, const std::string& st, T_ ty)
    : dst_(d), title_(t), subtext_(st), typ_(ty), isWord_(false)
    {}

  ReferBase(const std::string& t, const std::string& st, T_ ty)
    : title_(t), subtext_(st), typ_(ty), isWord_(false)
    {}

  void setDst_(const std::string& d) { dst_ = d; }
  const std::string& getDst_() const { return dst_; }
  const std::string& getTitle_() const { return title_; }
  const std::string& getSubText_() const { return subtext_; }
  const T_ getType() const { return typ_; }

public:
  virtual ~ReferBase() {}

  void setAsWord() { isWord_ = true; }

  std::string toXsl4Html(
    const std::string& prefix, const std::string& id) const;

  std::string toLog(const std::string& id) const;
};




/*---------------------------------------------------------------
 *  class InRefer
 *  ���������ւ̙ҏƏ�� (�ҏƐ�Ȃ������̃N���X�ň���)
 *  update: 2011.9.12
 *-------------------------------------------------------------*/
class InRefer : public ReferBase
{
public:
  InRefer(const std::string& t) : ReferBase(t) {}
  InRefer(const std::string& d, const std::string& t) : ReferBase(d, t) {}

  InRefer(
    const std::string& d, const std::string& t, const std::string& st, T_ ty)
    : ReferBase(d, t, st, ty)
    {}

  InRefer(const std::string& t, const std::string& st, T_ ty)
    : ReferBase(t, st, ty)
    {}
};


/*------------------------------------------------
 *  class ExRefer
 *  �O���ҏƏ��
 *  update: 2011.9.12
 *----------------------------------------------*/
class ExRefer : public ReferBase
{
public:
  ExRefer(const std::string& d, const std::string& t) : ReferBase(d, t) {}
  ExRefer(
    const std::string& d, const std::string& t, const std::string& st, T_ ty)
    : ReferBase(d, t, st, ty)
    {}
};


}// end of namespace rhea




#endif // INC_RHEA_REFER_H___
