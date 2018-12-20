/**************************************************************************
*
*  dict.h
*  by oZ/acy
*  (c) 2005-2008 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 17 Feb MMVIII
*
**************************************************************************/

#ifndef INC_RHEA_DICTIONARY_H___
#define INC_RHEA_DICTIONARY_H___

#include <iostream>
#include <list>
#include "word.h"


namespace rhea{


/*----------------------------------------------------------
*  class Dictionary
*  update: 2008.2.17
*---------------------------------------------------------*/
class Dictionary
{
private:
  std::list<Word> words_;

public:
  Dictionary();
  void printXsl4Html(std::ostream& os, const std::string& prefix);
  void printXsl4Tex(std::ostream& os);
  void printMakefile4Html(std::ostream& os);
  void outputList(
    const std::string& cate, const std::string& id,
    const std::string& pf_html, const std::string& poststr ="");
};


}// end of namespace rhea




#endif // INC_RHEA_DICTIONARY_H___
