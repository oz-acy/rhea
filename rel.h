/**************************************************************************
*
*  rel.h
*  by oZ/acy
*  (c) 2005-2011 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 5 Oct MMXI
*
**************************************************************************/

#ifndef INC_RHEA_RELATION_H___
#define INC_RHEA_RELATION_H___

#include <map>
#include "refer.h"



namespace rhea {


/*--------------------------------------
*  class Relation
*
*-------------------------------------*/
class Relation
{
private:
  std::map<std::string, InRefer> inRefers_;
  std::map<std::string, ExRefer> exRefers_;

public:
  Relation();
  void printXsl4Html(const std::string& path, const std::string& prefix);
};


}// end of namespace rhea


#endif // INC_RHEA_RELATION_REFERRED_H___
