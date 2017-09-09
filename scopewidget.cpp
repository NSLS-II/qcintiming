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

ScopeWidget::ScopeWidget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
  elapsed = 0;
  setFixedSize(200, 200);
}

void ScopeWidget::paintEvent(QPaintEvent *event)
{
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  helper->paint(&painter, event, elapsed);
  painter.end();
}


