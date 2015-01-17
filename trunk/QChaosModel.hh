#ifndef QChaosModel_h
#define QChaosModel_h

#include <stdlib.h>
#include <math.h>

// abstract base class for a dynamic system model
#include <iostream>
#include <string>

#include <QObject>

class QChaosModel : public QObject {

  Q_OBJECT

public:
  QChaosModel( std::string nm, int n );
  virtual ~QChaosModel( );
 
  double getParameter( int idx );

  const char*    getName(){ return name.c_str(); }
  int            getNPars(){ return npars; }
  double*        getPars(){ return par; }
  const QString  getInfo() { return info; }

  // Pure virtual fuction that returns the next point in the
  // model, keeps track internally of the iteration, returns
  // 0 if all is fine, 1 if max iterations reached or problem...
  virtual int   iterate( double *xp, double *yp ) = 0;

  // pure virtual function to reset the model, iter = 0 and 
  // set x and y to initial conditions
  virtual void  init( void ) = 0;

  // pure virtual function to reset the model, iter = 0 and 
  // set x and y to initial conditions
  virtual void  startpos( void ) = 0;

public slots:
  void setParameter( int idx, double value );

signals:
  void parameterChanged( int idx, double value );

protected:
  std::string   name;
  QString       info;

  double        x;
  double        y;
  double       *par;
  int           npars;
};


#endif /* #ifndef QChaosModel_h */
