/*
 * =====================================================================================
 *
 *       Filename:  scopewidget.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/30/2017 07:17:09 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "scopewidget.h"
#include <QPainter>
#include <stdio.h>

ScopeWidget::ScopeWidget(QWidget *parent, int num_traces)
  : QWidget(parent)
{

  nTraces = num_traces;

  // Now make the scope traces
  for(int i=0;i<nTraces;i++)
  {
    trace[i] = new ScopeTrace(this);
    trace[i]->move(0,40*i);
  }

  pen1 = QPen(Qt::gray, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
  pen2 = QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  setFixedSize(256*2,40*nTraces);
}

ScopeWidget::~ScopeWidget()
{
  for(int i=0;i<nTraces;i++)
  {
    delete trace[i];
  }
}

void ScopeWidget::paintEvent(QPaintEvent * /* event */ )
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  
  painter.setPen(pen2);
  painter.drawRect(0,0,255*2,nTraces*40 - 8);

  painter.setPen(pen1);
  for(int i=7;i<255;i+=8)
  {
    painter.drawLine(i*2,0,i*2,nTraces * 40 - 8);
  }
}

ScopeTrace* ScopeWidget::getTrace(int n)
{
  return trace[n];
}

ScopeTrace::ScopeTrace(QWidget *parent)
    : QWidget(parent)
{
  edge1 = 0;
  edge2 = 0;
  height1 = 32;
  height2 = 0;
  length = 255 * 2;
  inverted = false;

  setFixedSize(length * 2 + 6, height1);
  pen = QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void ScopeTrace::paintEvent(QPaintEvent * /* event */ )
{
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  int _height1, _height2;
  if(inverted) {
    _height2 = height1;
    _height1 = height2;
  } else {
    _height1 = height1;
    _height2 = height2;
  }

  painter.setPen(pen);
  
  painter.drawLine(0,_height1,edge1 * 2,_height1);
  painter.drawLine(edge1 * 2,_height1,edge1 * 2,_height2);
  painter.drawLine(edge1 * 2,_height2,edge2 * 2,_height2);
  painter.drawLine(edge2 * 2,_height2,edge2 * 2,_height1);
  painter.drawLine(edge2 * 2,_height1,length,_height1);
}

void ScopeTrace::setWaveform(int a, int b)
{
  edge1 = a;
  edge2 = b;
}

void ScopeTrace::setEdge1(int e)
{
  edge1 = e;
  if(edge2 < edge1)
  {
    edge2 = edge1;
    emit edge2Changed(edge2);
  }
  repaint();
}

void ScopeTrace::setEdge2(int e)
{
  edge2 = e;
  if(edge1 > edge2)
  {
    edge1 = edge2;
    emit edge1Changed(edge1);
  }
  repaint();
}

void ScopeTrace::setInverted(int i)
{
  if(i)
  {
    inverted = true;
  } else {
    inverted = false;
  }
  repaint();
}

