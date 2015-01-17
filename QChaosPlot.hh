#ifndef QChaosPlot_h
#define QChaosPlot_h

#include <vector>

#include <qwt_plot.h>

#define  MIN(a,b) ( a < b ? a : b )

#define  NDEF_ITERATIONS  30000
#define  NMAX_ITERATIONS 100000
#define  NMAX_MODELS         20

// Forward class declarations
class QwtPlotCurve;
class QwtPlotZoomer;
class QChaosModel;

// the class
class QChaosPlot : public QwtPlot {
  Q_OBJECT

public:
  QChaosPlot( QWidget *parent = 0 );

  int           getIterations( void ) { return _nIter; }
  QChaosModel *getActiveModel( void ) { return _model[_iActiveModel]; }

  enum Type { Henon, Lozi, Aronson, HenonC, Barnsley, Smith, Lorentz };

private:
  void  addModel( int idx, QChaosModel *m ) { _model[idx] = m; }

public slots:
  void drawModel( void );
  void resetModel( void );
  void setActive( int iModel );
  void setIterations( int n ) { _nIter = MIN( n, NMAX_ITERATIONS ); }
  void setParameter( int idx, double value );
  void enableZoom( bool on );

signals:
  void modelParameters( int n, double *values );
  void modelInfo( const QString& );

private:
  double                       _x[NMAX_ITERATIONS];
  double                       _y[NMAX_ITERATIONS];
  QwtPlotCurve                *_curve;
  int                          _nIter;

  QChaosModel                *_model[NMAX_MODELS];
  int                          _iActiveModel;

  QwtPlotZoomer               *_zoomer;

};


#endif /* #ifndef QChaosPlot_h */
