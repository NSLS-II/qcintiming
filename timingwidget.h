/*
 * =====================================================================================
 *
 *       Filename:  timingwidget.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/09/2017 12:53:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef TIMINGWIDGET_H
#define TIMINGWIDGET_H

#include <QString>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
#include "scopewidget.h"
#include "timingdata.h"

namespace Ui {
class TimingControls;
}

class TimingWidget : public QWidget
{
    Q_OBJECT

public:
  TimingWidget(QWidget *parent = 0);
  ~TimingWidget();
  void setTimingData(TimingData data);
  TimingData getTimingData(void);
  
public slots:
  void updateDisplay(int state);
  void updateTimingData(int state);

private:
  ScopeWidget *scope;    
  QString name[15];
  QLabel *nameLabel[15];
  QCheckBox *invertCheckBox[15];
  QSpinBox *edge1SpinBox[15];
  QSpinBox *edge2SpinBox[15];
  QGroupBox *timingControls;
  QGroupBox *timingWaveforms;
  Ui::TimingControls *ui;
  TimingData timingData;
  int currentState;
  bool inhibitUpdate;
};

#endif
