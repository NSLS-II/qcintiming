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

#include "timingdata.h"

using namespace std;

string int_to_hex(int i)
{
  stringstream stream;
  stream << setfill('0') << std::setw(4) 
         << hex << i;
  return stream.str();
}

TimingData::TimingData()
{
  // Zero data

  for(int i=0;i<16;i++)
  {
    state[i].passes = 0;
    state[i].next_state = 0;
    state[i].num_loops = 0;
    state[i].loop_back_state = 0;
    state[i].end_count = 0;
    for(int j=0;j<15;j++)
    {
      state[i].inverted[j] = 0;
      state[i].edge1[j] = 0;
      state[i].edge2[j] = 0;
    }
  }
}

void TimingData::readFromFile(string name)
{
  ifstream file;
  file.open(name);

  int data[55*16];

  if(file.is_open())
  {
    string line;
    int i = 0;
    int j = 0;
    while(getline(file, line))
    {
      if(line[0] != '#'){
        if((i % 3) == 1){
          stringstream ss(line);
          string s1;
          string s2;
          ss >> s1;
          ss >> s2;
          data[j++] = stoi(s2, nullptr, 16);
          cout << s2 << endl;
        }
        i++;
      }
    }
    file.close();
  }

  for(int s=0;s<8;s++)
  {
    int n = s * 55;
    state[s].passes = data[n]; 
    state[s].next_state = data[n+1]; 
    state[s].num_loops = (data[n+2] << 24) + (data[n+3] << 16) + (data[n+4] << 8) + (data[n+5]);
    state[s].loop_back_state = data[n+6]; 
    state[s].end_count = data[n+7]; 
    for(int i=0;i<15;i++)
    {
      state[s].inverted[i] = data[n + 8 + i];
    }
    for(int i=0;i<15;i++)
    {
      state[s].edge1[i] = data[n + 23 + i];
    }
    for(int i=0;i<15;i++)
    {
      state[s].edge2[i] = data[n + 38 + i];
    }
  }
}

void TimingData::writeToFile(string name)
{
  ofstream file;
  file.open(name);

  if(file.is_open())
  {
    for(int i=0;i<16;i++)
    {
      file << writeLine(i, 0, state[i].passes);
      file << writeLine(i, 1, state[i].next_state);
      file << writeLine(i, 2, (state[i].num_loops >> 24) & 0xFF);
      file << writeLine(i, 3, (state[i].num_loops >> 16) & 0xFF);
      file << writeLine(i, 4, (state[i].num_loops >> 8) & 0xFF);
      file << writeLine(i, 5, state[i].num_loops & 0xFF);
      file << writeLine(i, 6, state[i].loop_back_state);
      file << writeLine(i, 7, state[i].end_count);

      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 8+j, state[i].inverted[j]);
      }
      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 23+j, state[i].edge1[j]);
      }
      for(int j=0;j<15;j++)
      {
        file << writeLine(i, 38+j, state[i].edge2[j]);
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

