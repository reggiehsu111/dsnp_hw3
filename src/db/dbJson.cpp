/****************************************************************************
  FileName     [ dbJson.cpp ]
  PackageName  [ db ]
  Synopsis     [ Define database Json member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2015-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <cmath>
#include <string>
#include <algorithm>
#include "dbJson.h"
#include "util.h"

using namespace std;

/*****************************************/
/*          Global Functions             */
/*****************************************/
ostream&
operator << (ostream& os, const DBJsonElem& j)
{
   os << "\"" << j._key << "\" : " << j._value;
   return os;
}

istream& operator >> (istream& is, DBJson& j)
{
   // TODO: to read in data from Json file and store them in a DB 
   // - You can assume the input file is with correct JSON file format
   // - NO NEED to handle error file format
   assert(j._obj.empty());
   streambuf *backup = is.rdbuf();
   string line;
    int line_count = 0;
      while ( getline (is,line) ){
        line_count += 1;
        if (line.find('\"') != string::npos){
          string key = line.substr(line.find('\"')+1,line.rfind('\"')-line.find('\"')-1);
          string value = line.substr(line.find(':') + 1,line.find(';'));
          value.erase(remove(value.begin(),value.end(),' '),value.end());
          value.erase(remove(value.begin(),value.end(),','),value.end());
          int num = stoi(value);
          DBJsonElem newElem(key,num);
          j._obj.push_back(newElem);
        }
    }
    is.rdbuf(backup);
   return is;
}

ostream& operator << (ostream& os, const DBJson& j)
{
   // TODO
  os << '{' << endl;
  if (j._obj.size()){
    for (unsigned int i=0; i<j._obj.size()-1 ; i++){
      os << "  \"" << j._obj[i].key() << "\" : " << j._obj[i].value() << ',' << endl;
    }
    os << "  \"" << j._obj[j._obj.size()-1].key() << "\" : " << j._obj[j._obj.size()-1].value()<< endl;
  }
    os << '}' << endl;
   return os;
}

/**********************************************/
/*   Member Functions for class DBJsonElem    */
/**********************************************/
/*****************************************/
/*   Member Functions for class DBJson   */
/*****************************************/


void
DBJson::reset()
{
   // TODO
  _obj.clear();
  return;
}

// return false if key is repeated
bool
DBJson::add(const DBJsonElem& elm)
{
   // TODO
  bool flag = true;
  for (unsigned i=0;i<_obj.size();i++){
    if (elm.key()==_obj[i].key())
      flag = false;
  }
  if (flag)
    _obj.push_back(elm);
  return flag;
}

// return NAN if DBJson is empty
float
DBJson::ave() const
{
   // TODO
  if (!_obj.size())
    return NAN;
  else{
    float sum = 0.0;
    for (float i=0; i<_obj.size(); i++){
      sum += _obj[i].value();
    }
    return float(sum)/_obj.size();
  }
}

// If DBJson is empty, set idx to size() and return INT_MIN
int
DBJson::max(size_t& idx) const
{
   // TODO
  int maxN = INT_MIN;
  if (!_obj.size()){
    return  maxN;
  }
  else{
    maxN = _obj[0].value();
    for (unsigned i=0;i<_obj.size();i++){
      if(_obj[i].value()>maxN)
        maxN = _obj[i].value();
    }
    return maxN;
  }
}

// If DBJson is empty, set idx to size() and return INT_MIN
int
DBJson::min(size_t& idx) const
{
   // TODO
   int minN = INT_MAX;
   if (!_obj.size()){
    return  minN;
  }
  else{
    minN = _obj[0].value();
    for (unsigned i=0;i<_obj.size();i++){
      if(_obj[i].value()<minN)
        minN = _obj[i].value();
    }
    return minN;
  }
}

void
DBJson::sort(const DBSortKey& s)
{
   // Sort the data according to the order of columns in 's'
   ::sort(_obj.begin(), _obj.end(), s);
}

void
DBJson::sort(const DBSortValue& s)
{
   // Sort the data according to the order of columns in 's'
   ::sort(_obj.begin(), _obj.end(), s);
}

// return 0 if empty
int
DBJson::sum() const
{
   // TODO
  if (!_obj.size())
    return 0;
  else{
    int s = 0;;
    for (float i=0; i<_obj.size(); i++){
      s += _obj[i].value();
    }
    return s;
  }
}
