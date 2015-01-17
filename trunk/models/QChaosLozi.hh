#ifndef QChaosLozi_h
#define QChaosLozi_h

#include "QChaosModel.hh"

class QChaosLozi : public QChaosModel {

public:
  QChaosLozi() : 
    QChaosModel( "Lozi Model", 2 ) {

    info = QString("<b>Lozi Attractor</b><br />"
		   "<em>Equations</em><br />"
		   "&nbsp;x' = y + 1 - a | x |<br />"
		   "&nbsp;y' = bx<br />"
		   "<em>Info</em><br />"
                   "Similar model as the Henon Attractor, but is linear only not continuously " 
		   "differentiable. Forms a strange attactor around a = 1.7 and b = 0.5, and "
		   "diverges otherwise. Discovered by Rene Lozi (1978)." );

    // start position
    init();
  };
  
  int iterate( double *xp, double *yp ) {

    *xp = 1. - par[0] * fabs( x ) + y;
    *yp = par[1] * x;

    x = *xp;
    y = *yp;

    if ( sqrt( x*x + y*y ) > 5. ) return 1; // divergence

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 1.7;
    par[1] = 0.5;

    startpos();
  };
  
  void startpos( void ) {
    x = 0.6;
    y = 0.6;
  };

};


#endif /* #ifndef QChaosLozi_h */
