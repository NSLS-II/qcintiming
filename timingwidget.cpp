/*
 * =====================================================================================
 *
 *       Filename:  timingwidget.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/09/2017 12:53:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Stuart B. Wilkins (sbw), stuwilkins@mac.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>

#include "timingwidget.h"
#include "timingdata.h"
#include "scopewidget.h"

#include "ui_timing.h"

TimingWidget::TimingWidget(QWidget *parent)
  : QWidget(parent),
    ui(new Ui::TimingControls)
{
  setFixedSize(1000,1000);

  inhibitUpdate = false;

  // Create Scope Controls

  timingControls = new QGroupBox(this);
  timingWaveforms = new QGroupBox(this);
  ui->setupUi(timingControls);
  timingControls->move(0,0);
  timingWaveforms->move(0,80);
  timingWaveforms->resize(880,660);
  timingWaveforms->setTitle("Timing Waveforms");

  // Create scope 

  scope = new ScopeWidget(timingWaveforms, 15);  
  scope->move(350,40);

  // Define trace names

  name[0] = QString("V1");
  name[1] = QString("V2");
  name[2] = QString("V3");
  name[3] = QString("ATG");
  name[4] = QString("VF1");
  name[5] = QString("VF2");
  name[6] = QString("VF3");
  name[7] = QString("H1");
  name[8] = QString("H2");
  name[9] = QString("H3");
  name[10] = QString("OSW");
  name[11] = QString("RG");
  name[12] = QString("CONV");
  name[13] = QString("SAVE");
  name[14] = QString("SPARE");

  for(int i=0;i<15;i++)
  {
    nameLabel[i] = new QLabel(name[i], timingWaveforms);
    nameLabel[i]->move(20,i*40 + 40);
    nameLabel[i]->resize(80,40);

    invertCheckBox[i] = new QCheckBox(timingWaveforms);
    invertCheckBox[i]->move(300, i*40 + 40);
    invertCheckBox[i]->resize(30,40);

    connect(invertCheckBox[i], SIGNAL(stateChanged(int)),
            scope->getTrace(i), SLOT(setInverted(int)));
    connect(invertCheckBox[i], SIGNAL(stateChanged(int)),
            this, SLOT(updateTimingData(int)));

    edge1SpinBox[i] = new QSpinBox(timingWaveforms);
    edge1SpinBox[i]->setMinimum(0);
    edge1SpinBox[i]->setMaximum(255);
    edge1SpinBox[i]->setSingleStep(1);
    edge1SpinBox[i]->move(100, i*40 + 40 + 5);
    edge1SpinBox[i]->resize(80,25);
    connect(edge1SpinBox[i], SIGNAL(valueChanged(int)),
            scope->getTrace(i), SLOT(setEdge1(int)));
    connect(edge1SpinBox[i], SIGNAL(valueChanged(int)),
            this, SLOT(updateTimingData(int)));
    connect(scope->getTrace(i), SIGNAL(edge1Changed(int)),
            edge1SpinBox[i], SLOT(setValue(int)));

    edge2SpinBox[i] = new QSpinBox(timingWaveforms);
    edge2SpinBox[i]->setMinimum(0);
    edge2SpinBox[i]->setMaximum(255);
    edge2SpinBox[i]->setSingleStep(8);
    edge2SpinBox[i]->move(200, i*40 + 40 + 5);
    edge2SpinBox[i]->resize(80,25);

    connect(edge2SpinBox[i], SIGNAL(valueChanged(int)),
            scope->getTrace(i), SLOT(setEdge2(int)));
    connect(edge2SpinBox[i], SIGNAL(valueChanged(int)),
            this, SLOT(updateTimingData(int)));
    connect(scope->getTrace(i), SIGNAL(edge2Changed(int)),
            edge2SpinBox[i], SLOT(setValue(int)));
  }

  // Setup connection to loop through states

  connect(ui->stateSpinBox, SIGNAL(valueChanged(int)),
          this, SLOT(updateDisplay(int)));

  // Setup connections to change timing data if controls are changed

  connect(ui->passesSpinBox, SIGNAL(valueChanged(int)),
          this, SLOT(updateTimingData(int)));

  connect(ui->nextStateSpinBox, SIGNAL(valueChanged(int)), 
          this, SLOT(updateTimingData(int)));

  connect(ui->loopsSpinBox, SIGNAL(valueChanged(int)),
          this, SLOT(updateTimingData(int)));

  connect(ui->loopStateSpinBox, SIGNAL(valueChanged(int)),
          this, SLOT(updateTimingData(int)));

  connect(ui->endValueSpinBox, SIGNAL(valueChanged(int)), 
          this, SLOT(updateTimingData(int)));

  // Now move the end value line
  
  connect(ui->endValueSpinBox, SIGNAL(valueChanged(int)),
          scope, SLOT(setEndValue(int)));

  currentState = 0;
}

void TimingWidget::setTimingData(TimingData data)
{
  timingData = data;  
  updateDisplay(0);
}

TimingData TimingWidget::getTimingData(void)
{
  return timingData;
}

void TimingWidget::updateDisplay(int state)
{

  inhibitUpdate = true;

  ui->passesSpinBox->setValue(timingData.getState(state)->getPasses());
  ui->nextStateSpinBox->setValue(timingData.getState(state)->getNextState());
  ui->loopsSpinBox->setValue(timingData.getState(state)->getNumLoops());
  ui->loopStateSpinBox->setValue(timingData.getState(state)->getLoopBackState());
  ui->endValueSpinBox->setValue(timingData.getState(state)->getEndValue());

  for(int i=0;i<15;i++)
  {
    edge1SpinBox[i]->setValue(timingData.getState(state)->getEdge1(i));
    edge2SpinBox[i]->setValue(timingData.getState(state)->getEdge2(i));
    invertCheckBox[i]->setChecked(timingData.getState(state)->getInverted(i));
  }

  currentState = state;
  ui->stateSpinBox->setValue(state);

  inhibitUpdate = false;
}

void TimingWidget::updateTimingData(int /* state */ )
{
  if(!inhibitUpdate)
  {
    int state = ui->stateSpinBox->value();

    timingData.getState(state)->setPasses(ui->passesSpinBox->value());
    timingData.getState(state)->setNextState(ui->nextStateSpinBox->value());
    timingData.getState(state)->setNumLoops(ui->loopsSpinBox->value());
    timingData.getState(state)->setLoopBackState(ui->loopStateSpinBox->value());
    timingData.getState(state)->setEndValue(ui->endValueSpinBox->value());

    for(int i=0;i<15;i++)
    {
      timingData.getState(state)->setEdge1(i, edge1SpinBox[i]->value());
      timingData.getState(state)->setEdge2(i, edge2SpinBox[i]->value());
      timingData.getState(state)->setInverted(i, invertCheckBox[i]->isChecked());
    }
  }
}

TimingWidget::~TimingWidget()
{
  delete scope;
  delete timingControls;
  delete timingWaveforms;

  for(int i=0;i<15;i++)
  {
    delete nameLabel[i];
    delete invertCheckBox[i];
    delete edge1SpinBox[i];
    delete edge2SpinBox[i];
  }
}
