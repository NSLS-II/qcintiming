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
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class TimingState
{
  public:

    TimingState();

    int getPasses();
    int getNextState();
    int getNumLoops();
    int getLoopBackState();
    int getEndValue();

    int getInverted(int n);
    int getEdge1(int n);
    int getEdge2(int n);

    void setPasses(int n);
    void setNextState(int n);
    void setNumLoops(int n);
    void setLoopBackState(int n);
    void setEndValue(int n);

    void setInverted(int n, int m);
    void setEdge1(int n, int m);
    void setEdge2(int n, int m);
  private:
    int passes;
    int nextState;
    int numLoops;
    int loopBackState;
    int endValue;
    int inverted[15];
    int edge1[15];
    int edge2[15];
};

class TimingData
{
  public:
    TimingData();      
    bool readFromFile(string file);
    void writeToFile(string file);
    string getErrorMessage(void);
    TimingState* getState(int n);
  private:
    TimingState state[16];
    string writeLine(int i, int o, int v);
    string errorMessage;
};

#endif
