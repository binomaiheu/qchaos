#ifndef QChaosHenon_h
#define QChaosHenon_h

#include "QChaosModel.hh"

class QChaosHenon : public QChaosModel {

public:
  QChaosHenon() :
    QChaosModel( "Henon Model", 2 ) {

    info = QString("<b>Henon Attractor</b><br />"
		   "<em>Equations</em><br />"
		   "&nbsp;x' = y + 1 - a x<sup>2</sup><br />"
		   "&nbsp;y' = bx<br />"
		   "<em>Info</em><br />"
		   "Shows the Henon Attractor, which reaches a stable orbit around " 
		   "a = 1.4 and b = 0.3, and diverges otherwise. Discovered by "
		   "Michel Henon (1976)." );

    // start position
    init(); 
  };
  
  int iterate( double *xp, double *yp ) {

    *xp = 1. + y - par[0] * x * x;
    *yp = par[1] * x;

    x = *xp;
    y = *yp;

    if ( sqrt( x*x + y*y ) > 5. ) return 1; // divergence

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 1.4;
    par[1] = 0.3;

    startpos();
  }

  void startpos( void ) { 
    x = 0.6;
    y = 0.6;
  };

};


#endif /* #ifndef QChaosHenon_h */
