/*
 * =====================================================================================
 *
 *       Filename:  scopewidget.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/30/2017 07:14:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef SCOPEWIDGET_H
#define SCOPEWIDGET_H

#include <QWidget>
#include <QPen>

class ScopeTrace : public QWidget
{
    Q_OBJECT

public:
    ScopeTrace(QWidget *parent = 0);
    void setWaveform(int a, int b);

protected:
    void paintEvent(QPaintEvent *event);

signals:
  void edge1Changed(int e);
  void edge2Changed(int e);
  void invertedChanged(int i);

public slots:
  void setEdge1(int e);
  void setEdge2(int e);
  void setInverted(int i);

private:
    int edge1;
    int edge2;
    int height1;
    int height2;
    int length;
    bool inverted;
    QPen pen;
};

class ScopeWidget : public QWidget
{
    Q_OBJECT

public:
  ScopeWidget(QWidget *parent = 0, int num_traces = 1);
  ~ScopeWidget();
  ScopeTrace *getTrace(int n);

public slots:
  void setEndValue(int i);

protected:
  void paintEvent(QPaintEvent *event);

private:
  ScopeTrace *trace[256];
  int nTraces;
  int endValue;
  QPen pen1;
  QPen pen2;
  QPen pen3;
};

#endif
