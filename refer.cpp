/**************************************************************************
 *
 *  refer.cpp
 *  by oZ/acy
 *  (c) 2011 oZ/acy.  ALL RIGHTS RESERVED.
 *
 *  last update: 8 Oct MMXI
 *
 *************************************************************************/

#include <sstream>
#include "refer.h"


/*=========================================================
 *  ReferBase::toXsl4Html()
 *  update: 2011.10.08
 *=======================================================*/
std::string rhea::ReferBase::toXsl4Html(
  const std::string& prefix, const std::string& id) const
{
  std::ostringstream oss;

  oss << "      <xsl:when test=\"@id='" << id <<  "'\">";

  if (dst_.size()) {
    oss << "<a>";

    oss << "<xsl:attribute name=\"href\">" << prefix << dst_;
    oss << "<xsl:if test=\"boolean(@subid)\">#"
           "<xsl:value-of select=\"@subid\" /></xsl:if>";
    oss << "</xsl:attribute>";

    if (isWord_)
      oss << "<xsl:attribute name=\"class\">word</xsl:attribute>";
  }

  if (typ_ == TY_ABBR) {
    oss << "<abbr title=\"" << subtext_ << "\">";
  } else if (typ_ == TY_NOTE) {
    oss << "<span class=\"note\" title=\"" << subtext_ << "\">";
  }

  oss << "<xsl:if test=\"boolean(text()) or (count(child::node())!=0)\">"
         "<xsl:apply-templates />"
         "</xsl:if>"
         "<xsl:if test=\"not(boolean(text())) and (count(child::node())=0)\">";
  oss << title_;
  oss << "</xsl:if>";

  if (typ_ == TY_ABBR) {
    oss << "</abbr>";
  } else if (typ_ == TY_NOTE) {
    oss << "</span>";
  }

  if (dst_.size()) {
    oss << "</a>";
  }

  oss << "</xsl:when>" << std::endl;

  return oss.str();
}








//eof
