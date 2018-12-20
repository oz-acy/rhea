/**************************************************************************
*
*  metis2xml.h
*  by oZ/acy
*  (c) 2005-2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 15 Feb 2008
*
*  system "RHEA" 用  Metis => XML 處理クラス
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
*  XML用に文字列をエスケープするフィルタ
*  system RHEA 用に要素に置換するタイプ
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
*  XML用に文字列をエスケープするフィルタ
*  屬性用 (XML汎用といふべきか……)
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
*  文字列を出力するVisitor
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
  {  /* 今のところnone */
  }
};


/*------------------------------------------------
*  class AttrVisitor2Xml
*  屬性を出力する Visitor
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
*  XML (RHEA 用) を出力する Visitor
*  屬性部分は AttrVisitor2Xml に投げる
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
