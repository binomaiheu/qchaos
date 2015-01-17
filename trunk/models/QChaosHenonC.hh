#ifndef QChaosHenonC_h
#define QChaosHenonC_h

#include "QChaosModel.hh"

class QChaosHenonC : public QChaosModel {

public:
  QChaosHenonC() :
    QChaosModel( "Henon Conservative Model", 1 ) {


    info = QString("<b>Henon Conservative Model</b><br />"
		   "<em>Equations</em><br />"
		   "&nbsp;x' = ax - (1-a<sup>2</sup>)<sup>1/2</sup> ( y - x<sup>2</sup>)<br />"
		   "&nbsp;y' = (1-a<sup>2</sup>)<sup>1/2</sup>x + a ( y - x<sup>2</sup>)<br />"
		   "<em>Info</em><br />"
		   "Every orbit is set by a randomized start point and 1000 points "
		   "are drawin in each orbit. The number of iterations is the total "
		   "number of points drawn." );

    // start position
    srand( 124579 );
    init(); 
    _ni = 1;
  };
  
  int iterate( double *xp, double *yp ) {

    double a = par[0];
    double b = sqrt(1 - par[0]*par[0] );

    if ( _ni % 1000 == 0 ) {
      // disturb the inital condition, so will draw next
      // orbit...
      startpos();
      _ni = 1;
    }

    *xp = a * x - b * ( y - x * x );
    *yp = b * x + a * ( y - x * x );

    x = *xp;
    y = *yp;

    _ni++;

    if ( sqrt( x*x + y*y ) > 1.2 ) return 1; // divergence

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 0.24;

    startpos();
  };

  void startpos( void ) {
    x = -0.4 + (double) rand() / RAND_MAX;
    y = -0.4 + (double) rand() / RAND_MAX;
  }

private:
  int _ni;

};


#endif /* #ifndef QChaosHenonC_h */
