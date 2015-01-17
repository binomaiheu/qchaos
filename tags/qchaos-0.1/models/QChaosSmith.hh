#ifndef QChaosSmith_h
#define QChaosSmith_h

#include "QChaosModel.hh"

class QChaosSmith : public QChaosModel {

public:
  QChaosSmith() :
    QChaosModel( "Smith Model", 2 ) {

    info = QString("<b>Smith Attractor</b><br />"
		   "<em>Equations</em><br />"
		   "&nbsp;x' = a x - b y<br />"
		   "&nbsp;y' = b x + z y ( 1 - y )<br />"
		   "<em>Info</em><br />"
		   "Shows a model from population dynamics by the biologist Maynard Smith " 
		   "p0 = PHI and p1 = R, where in the above equations a = R cos( PHI ) and "
		   "b = R sin( PHI )" );

    // start position
    init(); 
  };
  
  int iterate( double *xp, double *yp ) {

    double a = par[1] * cos( par[0] );
    double b = par[1] * sin( par[0] );

    *xp = a * x - b * y ;
    *yp = b * x + a * y * ( 1. - y );

    x = *xp;
    y = *yp;

    if ( sqrt( x*x + y*y ) > 10. ) return 1; // divergence

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 3.14159265 / 4;
    par[1] = 1.0564;

    startpos();
  }

  void startpos( void ) { 
    x = 0.1;
    y = 0.;
  };

};


#endif /* #ifndef QChaosSmith_h */
