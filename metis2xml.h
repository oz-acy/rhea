/**************************************************************************
*
*  metis2xml.h
*  by oZ/acy
*  (c) 2005-2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 15 Feb 2008
*
*  system "RHEA" �p  Metis => XML �|���N���X
**************************************************************************/

#ifndef INC_RHEA_METIS_TO_XML_H___
#define INC_RHEA_METIS_TO_XML_H___

#include <iostream>
#include <metis/data.h>


namespace rhea
{

class StringEsc2Xml;
class StringEsc2XmlAttr;
std::ostream& operator<<(std::ostream&, const StringEsc2Xml&);
std::ostream& operator<<(std::ostream&, const StringEsc2XmlAttr&);


/*-----------------------------------------------
*  StringEsc2Xml
*  XML�p�ɕ�������G�X�P�[�v����t�B���^
*  system RHEA �p�ɗv�f�ɒu������^�C�v
*----------------------------------------------*/
class StringEsc2Xml
{
  friend std::ostream& operator<<(std::ostream&, const StringEsc2Xml&);

private:
  const std::string& str_;

public:
  explicit StringEsc2Xml(const std::string& s) : str_(s) {}
};


/*------------------------------------------------------------
*  StringEsc2XmlAttr
*  XML�p�ɕ�������G�X�P�[�v����t�B���^
*  �����p (XML�ėp�Ƃ��ӂׂ����c�c)
*-----------------------------------------------------------*/
class StringEsc2XmlAttr
{
  friend std::ostream& operator<<(std::ostream&, const StringEsc2XmlAttr&);

private:
  const std::string& str_;

public:
  explicit StringEsc2XmlAttr(const std::string& s) : str_(s) {}
};



/*------------------------------------------------
*  class StrVisitor2Xml
*  ��������o�͂���Visitor
*
*  create: 2008.2.15
*-----------------------------------------------*/
class StrVisitor2Xml : public metis::DatumVisitor
{
private:
  std::ostream& os_;

public:
  explicit StrVisitor2Xml(std::ostream& o) : os_(o) {}

  void visit(metis::NormalString& s) { os_ << s.refer(); }

  void visit(metis::CharReference& cr)
  {  /* ���̂Ƃ���none */
  }
};


/*------------------------------------------------
*  class AttrVisitor2Xml
*  �������o�͂��� Visitor
*
*  update: 2008.2.15
*-----------------------------------------------*/
class AttrVisitor2Xml : public metis::DatumVisitor
{
private:
  std::ostream& os_;

public:
  explicit AttrVisitor2Xml(std::ostream& o) : os_(o) {}
  void visit(metis::Attribute& a);
};


/*----------------------------------------------------
*  WriteVisitor2Xml
*  XML (RHEA �p) ���o�͂��� Visitor
*  ���������� AttrVisitor2Xml �ɓ�����
*
*  update: 2008.2.15
*---------------------------------------------------*/
class WriteVisitor2Xml : public metis::DatumVisitor
{
private:
  std::ostream& os_;

public:
  explicit WriteVisitor2Xml(std::ostream& o) : os_(o) {}
  void visit(metis::StringData& str);
  void visit(metis::Element&);
};


}//end of namespace rhea



#endif // INC_RHEA_METIS_TO_XML_H___
