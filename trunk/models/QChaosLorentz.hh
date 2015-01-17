#ifndef QChaosLorentz_h
#define QChaosLorentz_h

#include "QChaosModel.hh"

class QChaosLorentz : public QChaosModel {

public:
  QChaosLorentz() :
    QChaosModel( "Lorentz Attractor", 4 ) {

    info = QString("<b>Lorentz Attractor</b><br />"
		   "<em>Equations</em><br />"
		   "&nbsp;dx/dt = a ( y - x)<br />"
		   "&nbsp;dy/dt = x ( c - z) - y<br />"
		   "&nbsp;dz/dt = x y - b z<br />"
		   "<em>Info</em><br />"
		   "Shows a 2D projection of the 3D Lorentz Attractor. "
		   "The parameters are : p0 = a, p1 = b, p2 = c, p3 = time step." 
		   "Model by Edward Lorentz (1963)." );

    // start position
    init(); 
  };
  
  int iterate( double *xp, double *yp ) {

    double a = par[0];
    double b = par[1];
    double c = par[2];

    double h = par[3];


    double x1 = x + h * a * ( y - x );
    double y1 = y + h * ( x * ( c - z ) - y );
    double z1 = z + h * ( x * y - b * z );

    double x2 = x1 + h * a * ( y1 - x1 );
    double y2 = y1 + h * ( x1 * ( c - z1 ) - y1 );
    double z2 = z1 + h * ( x1 * y1 - b * z1 );

    // new 3D coordinated
    double xnew = ( x + x2 ) / 2.;
    double ynew = ( y + y2 ) / 2.;
    double znew = ( z + z2 ) / 2;

    // project
    *xp = xnew + ynew;
    *yp = znew;

    x = xnew;
    y = ynew;
    z = znew;

    return 0;
  };

  void init( void ) {
    // initial parameters
    par[0] = 10.;
    par[1] = 8./3.;
    par[2] = 28.;

    par[3] = 0.001;

    startpos();
  }

  void startpos( void ) { 
    x = -12.5;
    y = -17.4;
    z = 26;
  };


private:
  double z; // add a 3th coordinate here since the model is 3d
};


#endif /* #ifndef QChaosLorentz_h */
