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
class ScopeHelper
{
public:
  ScopeHelper();

public:
  void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
  QBrush background;
  QBrush circleBrush;
  QFont textFont;
  QPen circlePen;
  QPen textPen;
};

Class ScopeHelper;

class ScopeWidget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;
    int elapsed;
};
