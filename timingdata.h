/*
 * =====================================================================================
 *
 *       Filename:  timingdata.h
 *
 *    Description:  gT
 *
 *        Version:  1.0
 *        Created:  09/09/2017 03:24:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef TIMINGDATA_H
#define TIMINGDATA_H

#include <string>

class TimingState
{
  public:
    int passes;
    int next_state;
    int num_loops;
    int loop_back_state;
    int end_count;
    int inverted[15];
    int edge1[15];
    int edge2[15];

};

class TimingData
{
  public:
    TimingData();      
    void readFromFile(std::string file);
  private:
    TimingState state[8];
};

#endif
