#ifndef QParBoxArray_h
#define QParBoxArray_h

#include <QWidget>
#include <QGroupBox>

class QParBox;
class QLabel;
class QGridLayout;

#define NMAX_PARAMETERS  10

// the class definition
class QParBoxArray : public QGroupBox {

  Q_OBJECT

public:
  QParBoxArray( const char *name, int size, QWidget *parent = 0 );
  ~QParBoxArray();
  
public slots:
  void setParameters( int n, double *pars );

signals:
  void parameterChanged( int idx, double value );

private:
  int          _npars;
  QParBox     *_pbox[NMAX_PARAMETERS];
  QLabel      *_label[NMAX_PARAMETERS];
  QGridLayout *_ly;
  };



#endif /* #ifndef QParBoxArray_h */
