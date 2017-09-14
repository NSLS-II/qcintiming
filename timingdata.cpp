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
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "timingdata.h"

using namespace std;

string int_to_hex(int i)
{
  stringstream stream;
  stream << setfill('0') << setw(4)
         << uppercase << hex << i;
  return stream.str();
}

TimingState::TimingState()
{
  passes = 0;
  nextState = 0;
  numLoops = 0;
  loopBackState = 0;
  endValue = 0;

  for(int n=0;n<15;n++)
  {
    inverted[n] = 0;
    edge1[n] = 0;
    edge2[n] = 0;
  }
}

TimingData::TimingData()
{
  errorMessage = "";
}

bool TimingData::readFromFile(string name)
{
  ifstream file;
  bool valid = true;

  file.open(name.c_str());
  if(!file.is_open()){
    errorMessage = "Unable to open file";
    return false;
  }

  int data[55*16];
  string line;
  int i = 0, j = 0;
  stringstream errorMessageStream;

  errorMessageStream.clear();
  errorMessageStream.str("");

  while(getline(file, line))
  {
    if(line[0] != '#'){
      stringstream ss(line);
      string s1, s2;
      ss >> s1; ss >> s2;
      transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
      transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
      if((i % 3) == 0)
      {
        if(s1 == "8106")
        {
          // End of file
          valid = true;
          break;
        }
        if((s1 != "8200") || (s2 != int_to_hex(j * 2)))
        {
          // File is out of order
          valid = false;
          errorMessageStream << "INVALID FILE : Expected \"8200 " << int_to_hex(j * 2) << "\"";
          errorMessageStream << " at line " << i << endl;
          break;
        }
      } else if((i % 3) == 1) {

        if(s1 != "8201")
        {
          errorMessageStream << "INVALID FILE : Expected \"8201\" at line " << i << endl;
          valid = false;
          break;
        }
        ss >> s2;
        try {
          data[j++] = stoi(s2, nullptr, 16);
        } 
        catch(...) {
          errorMessageStream << "INVALID FILE : Could not convert hex to dec at line " << i << endl;
          valid = false;
          break;
        }
      } else {
        // (i % 3) == 2
        if((s1 != "8001") || (s2 != "0103"))
        {
          valid = false;
          errorMessageStream << "INVALID FILE : was expecting \"8001 0103\" at line " << i << endl;
          break;
        }
      }
      i++;
    }
  }

  file.close();

  if(valid == true)
  {
    for(int s=0;s<8;s++)
    {
      int n = s * 55;
      getState(s)->setPasses(data[n]); 
      getState(s)->setNextState(data[n+1]);
      getState(s)->setNumLoops((data[n+2] << 24) + (data[n+3] << 16) + (data[n+4] << 8) + (data[n+5]));
      getState(s)->setLoopBackState(data[n+6]);
      getState(s)->setEndValue(data[n+7]);

      for(int i=0;i<15;i++)
      {
        getState(s)->setInverted(i, data[n + 8 + i]);
      }
      for(int i=0;i<15;i++)
      {
        getState(s)->setEdge1(i, data[n + 23 + i]);
      }
      for(int i=0;i<15;i++)
      {
        getState(s)->setEdge2(i, data[n + 38 + i]);
      }
    }
  }

  if(valid)
  {
    errorMessage = "";
    return true;
  }

  errorMessage = errorMessageStream.str();
  return false;
}

void TimingData::writeToFile(string name)
{
  ofstream file;
  file.open(name.c_str());

  if(file.is_open())
  {
    for(int i=0;i<16;i++)
    {
      file << writeLine(i, 0, state[i].getPasses());
      file << writeLine(i, 1, state[i].getNextState());
      file << writeLine(i, 2, (state[i].getNumLoops() >> 24) & 0xFF);
      file << writeLine(i, 3, (state[i].getNumLoops()>> 16) & 0xFF);
      file << writeLine(i, 4, (state[i].getNumLoops()>> 8) & 0xFF);
      file << writeLine(i, 5, state[i].getNumLoops() & 0xFF);
      file << writeLine(i, 6, state[i].getLoopBackState());
      file << writeLine(i, 7, state[i].getEndValue());

      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 8+j, state[i].getInverted(j));
      }
      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 23+j, state[i].getEdge1(j));
      }
      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 38+j, state[i].getEdge2(j));
      }
      
      file << writeLine(i, 53, 2);
      file << writeLine(i, 54, 0);
    }

    file << "8106 0000";
  }
}

string TimingData::writeLine(int i, int o, int v)
{
  stringstream str;
  str << "8200 " << int_to_hex((i * 55 + o) * 2) << endl;
  str << "8201 " << int_to_hex(v & 0xFFFF) << endl;
  str << "8001 0103" << endl;
  return str.str();
}

string TimingData::getErrorMessage(void)
{
  return errorMessage;
}

TimingState* TimingData::getState(int n)
{
  return &state[n];
}

int TimingState::getPasses()
{
  return passes;
}

int TimingState::getNextState()
{
  return nextState;
}

int TimingState::getNumLoops()
{
  return numLoops;
}

int TimingState::getLoopBackState()
{
  return loopBackState;
}

int TimingState::getEndValue()
{
  return endValue;
}

int TimingState::getInverted(int n)
{
  return inverted[n];
}

int TimingState::getEdge1(int n)
{
  return edge1[n];
}

int TimingState::getEdge2(int n)
{
  return edge2[n];
}

void TimingState::setPasses(int n)
{
  passes = n;
}

void TimingState::setNextState(int n)
{
  nextState = n;
}

void TimingState::setNumLoops(int n)
{
  numLoops = n;
}

void TimingState::setLoopBackState(int n)
{
  loopBackState = n;
}

void TimingState::setEndValue(int n)
{
  endValue = n;
}

void TimingState::setInverted(int n, int m)
{
  inverted[n] = m;
}

void TimingState::setEdge1(int n, int m)
{
  edge1[n] = m;
}

void TimingState::setEdge2(int n, int m)
{
  edge2[n] = m;
}
