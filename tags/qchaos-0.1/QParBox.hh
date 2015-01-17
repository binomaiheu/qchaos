#ifndef QParBox_h
#define QParBox_h

#include <QWidget>
#include <QDoubleSpinBox>

class QParBox : public QDoubleSpinBox {

  Q_OBJECT

public:
  QParBox( int idx, QWidget *parent = 0 );

private slots:
  void acceptChange( double value );
  
signals:
  void parameterChanged( int idx, double value );

private:
  int        _idx;
};


#endif /**/
