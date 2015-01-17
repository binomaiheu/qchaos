#include <iostream>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_picker.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_marker.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_canvas.h>
#include <qwt-qt4/qwt_plot_layout.h>
#include <qwt-qt4/qwt_plot_zoomer.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_picker.h>

#include "QChaosPlot.hh"
#include "QChaosModel.hh"

#include "models/QChaosHenon.hh"
#include "models/QChaosLozi.hh"
#include "models/QChaosAronson.hh"
#include "models/QChaosHenonC.hh"
#include "models/QChaosBarnsley.hh"
#include "models/QChaosSmith.hh"
#include "models/QChaosLorentz.hh"


class Zoomer: public QwtPlotZoomer
{
public:
  Zoomer(int xAxis, int yAxis, QwtPlotCanvas *canvas):
    QwtPlotZoomer(xAxis, yAxis, canvas)
    {
      setSelectionFlags(QwtPicker::DragSelection | QwtPicker::CornerToCorner);
      setTrackerMode(QwtPicker::AlwaysOff);
      setRubberBand(QwtPicker::NoRubberBand);
      
// RightButton: zoom out by 1
// Ctrl+RightButton: zoom out to full size
      
      
      setMousePattern(QwtEventPattern::MouseSelect2,
		      Qt::RightButton, Qt::ControlModifier);
      setMousePattern(QwtEventPattern::MouseSelect3,
		      Qt::RightButton);
    }
};



QChaosPlot::QChaosPlot( QWidget *parent ) :
  QwtPlot( parent ) {
  
  _nIter = NDEF_ITERATIONS;
  
// set plot width/heigth in pixels
  setMinimumSize( 300, 300 );
  
  setAutoReplot( false );
  
// setup the canvas
  setCanvasBackground( Qt::white );
  
// grid
  QwtPlotGrid *grid = new QwtPlotGrid;
  grid->enableXMin(true);
  grid->enableYMin(true);
  grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
  grid->attach(this);
  
  
  _curve = new QwtPlotCurve( "Model Curve" );
  _curve->attach( this );
  _curve->setStyle( QwtPlotCurve::Dots );
  _curve->setPen(QPen(Qt::red,1));
  
  addModel( QChaosPlot::Henon, new QChaosHenon() );
  addModel( QChaosPlot::Lozi, new QChaosLozi() );
  addModel( QChaosPlot::Aronson, new QChaosAronson() );
  addModel( QChaosPlot::HenonC, new QChaosHenonC() );
  addModel( QChaosPlot::Barnsley, new QChaosBarnsley() );
  addModel( QChaosPlot::Smith, new QChaosSmith() );
  addModel( QChaosPlot::Lorentz, new QChaosLorentz() );
  
// enable zooming
  _zoomer = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft, canvas() );
  _zoomer->setRubberBand(QwtPicker::RectRubberBand);
  _zoomer->setRubberBandPen(QPen(Qt::red, 1, Qt::DotLine));
  _zoomer->setTrackerMode(QwtPicker::ActiveOnly);
  _zoomer->setTrackerPen(QPen(Qt::red));
  
  enableZoom( false );
  
  setAutoReplot(true);
}


// -------------------------------------------------------------------
void QChaosPlot::drawModel( ) {
  
  const bool doReplot = autoReplot( );
  setAutoReplot( false );
  
  setTitle( getActiveModel()->getName() );
  
// current active model
  QChaosModel *m = getActiveModel();
  int i = 0;
  
// set initial conditions for model
  m->startpos();
  
// get values from the model
  while ( i < getIterations() ) {
    if ( m->iterate( &(_x[i]), &(_y[i]) ) ) break;
// std::cout << "i=" << i << "x=" << _x[i] << ", y=" << _y[i] << std::endl;
    i++;
  }
  
  _curve->setData( _x, _y, i );
  
// make sure the axes update automatically, looks like the zoomer may
// screw this up...
  setAxisAutoScale( QwtPlot::xBottom );
  setAxisAutoScale( QwtPlot::yLeft );
  setAutoReplot( doReplot );
  
// replot the plot
  this->replot();
  
// update the zoom base
  _zoomer->setZoomBase();
}

// -------------------------------------------------------------------
void QChaosPlot::resetModel( void ) {
  getActiveModel()->init();
  emit modelParameters( getActiveModel()->getNPars(), getActiveModel()->getPars() );
  drawModel();
}

// -------------------------------------------------------------------
void QChaosPlot::setParameter( int idx, double value ) {
  _model[_iActiveModel]->setParameter( idx, value );
  return;
}

// -------------------------------------------------------------------
void QChaosPlot::setActive( int iModel ) {
  _iActiveModel = iModel;
// emit modelParameters( _model[_iActiveModel]->getNPars(), _model[_iActiveModel]->getPars() );
  emit modelParameters( getActiveModel()->getNPars(), getActiveModel()->getPars() );
  
  emit modelInfo( getActiveModel()->getInfo() );
  return;
}

// -------------------------------------------------------------------
void QChaosPlot::enableZoom( bool on ){
  _zoomer->setEnabled( on );
  _zoomer->zoom( 0 );
} 
