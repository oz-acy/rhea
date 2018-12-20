/**************************************************************************
*
*  m2x_main.cpp
*  by oZ/acy
*  (c) 2005-2010 oZ/acy.  ALL RIGHTS RESERVED.
*
*  last update: 6 Sep MMX
**************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <metis/parser.h>
#include "metis2xml.h"


int main(int argc, char** argv)
{
  using namespace std;

  if (argc != 3)
  {
    cerr << "usage: " << argv[0] << " infile outpath" << endl;
    return 1;
  }

  metis::Element* root = metis::Parser::parse(argv[1]);
  if (!root)
  {
    cerr << "parsing is fault." << endl;
    return 1;
  }

  ofstream ofs(argv[2], ios::binary);
  if (!ofs)
  {
    cerr << "cannot open file " << argv[2] << endl;
    return 1;
  }


  ofs << "<?xml version=\"1.0\"?>" << endl << endl;
  rhea::WriteVisitor2Xml wv2x(ofs);
  root->accept(wv2x);

  delete root;

  return 0;
}


//eof
