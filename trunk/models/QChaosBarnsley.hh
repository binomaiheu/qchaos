#ifndef QChaosBarnsley_h
#define QChaosBarnsley_h

#include "QChaosModel.hh"

class QChaosBarnsley : public QChaosModel {

public:
  QChaosBarnsley() :
    QChaosModel( "Barnsley's Fern", 3 ) {


    info = QString("<b>Barnsley's Fern</b><br />"
		   "<em>Info</em><br />"
		   "A fractal fern defined by an afine transformation "
		   );

    init(); 
    srand( 124513 );

    d1 =  0.16;

    a2 =  0.85;
    b2 =  0.04;
    c2 = -0.04;
    d2 =  0.85;
    f2 =  1.6;

    a3 =  0.20;
    b3 = -0.26;
    c3 =  0.23;
    d3 =  0.22;
    f3 =  1.6;

    a4 = -0.15;
    b4 =  0.28;
    c4 =  0.26;
    d4 =  0.24;
    f4 =  0.44; 
  };
  
  int iterate( double *xp, double *yp ) {

    double r = (double) rand() / RAND_MAX;

    double Q1 = par[0];
    double Q2 = par[1];
    double Q3 = par[2];

    if ( r < Q1 ) {
      *xp = 0.;
      *yp = d1 * y;
    } else if ( r < Q2 ) {
      *xp = a2 * x + b2 * y;
      *yp = c2 * x + d2 * y + f2;
    } else if ( r < Q3 ) {
      *xp = a3 * x + b3 * y;
      *yp = c3 * x + d3 * y + f3;
    } else {
      *xp = a4 * x + b4 * y;
      *yp = c4 * x + d4 * y + f4;
    }

    x = *xp;
    y = *yp;

    return 0;
  };

  void init( void ) {
    startpos();

    par[0] = 0.01; // Q1
    par[1] = 0.86; // Q2
    par[2] = 0.93; // Q3
  };

  void startpos( void ) {
    x = 0.;
    y = 0.;
  }

private:
  double d1;
  double a2, b2, c2, d2, f2;
  double a3, b3, c3, d3, f3;
  double a4, b4, c4, d4, f4; 
};


#endif /* #ifndef QChaosBarnsley_h */
