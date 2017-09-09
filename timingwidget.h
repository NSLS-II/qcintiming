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

namespace Ui {
class TimingControls;
}

class TimingWidget : public QWidget
{
    Q_OBJECT

public:
  TimingWidget(QWidget *parent = 0);
  ~TimingWidget();

private:
  ScopeWidget *scope;    
  QString name[14];
  QLabel *nameLabel[14];
  QCheckBox *invertCheckBox[14];
  QSpinBox *edge1SpinBox[14];
  QSpinBox *edge2SpinBox[14];
  QGroupBox *timingControls;
  QGroupBox *timingWaveforms;
  Ui::TimingControls *ui;
};

#endif
