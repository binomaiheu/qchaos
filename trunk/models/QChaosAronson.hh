#ifndef QChaosAronson_h
#define QChaosAronson_h

#include "QChaosModel.hh"

class QChaosAronson : public QChaosModel {

public:
  QChaosAronson() : 
    QChaosModel( "Aronson Model", 1 ) {

    info = QString("<b>Aronson Model</b><br />"
                   "<em>Equations</em><br />"
                   "&nbsp;x' = y<br />"
                   "&nbsp;y' = a y ( 1 - x )<br />"
                   "<em>Info</em><br />"
                   "Based on Aronson's population model x<sup>n+1</sup> = a x<sup>n</sup> "
		   "(1 - x<sup>n-1</sup>) with a &lt; 0. Has a stable region for 1 &le; a &lt; 2 "
                   "which gets reached by a spiral with 6 branches, above 2.2710 it reaches a "
                   "strange attactor. " );

    // start position
    init();
  };
  
  int iterate( double *xp, double *yp ) {

    *xp = y;
    *yp = par[0] * y * ( 1. - x );

    x = *xp;
    y = *yp;

    if ( sqrt( x*x + y*y ) > 5. ) return 1; // divergence

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 1.99;

    startpos();
  }

  void startpos( void ) {
    x = 0.01;
    y = 0.01;
  };

};


#endif /* #ifndef QChaosAronson_h */
