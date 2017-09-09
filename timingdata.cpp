/*
 * =====================================================================================
 *
 *       Filename:  timingdata.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/09/2017 03:22:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string>
#include <fstream>
#include <iostream>

#include "timingdata.h"

using namespace std;

TimingData::TimingData()
{
  
}

void TimingData::readFromFile(string name)
{
  ifstream file;
  file.open(name);

  if(file.is_open())
  {
    string line;

    while(getline(file, line))
    {
      cout << line << '\n';
    }
    file.close();
  }
}
