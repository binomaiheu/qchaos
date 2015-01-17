#include "QParBox.hh"

QParBox::QParBox( int idx, QWidget *parent ) :
  QDoubleSpinBox( parent ), _idx( idx ) {

  QObject::connect( this, SIGNAL(valueChanged(double)), this, SLOT(acceptChange(double)));
}


void QParBox::acceptChange( double value ) {
  emit parameterChanged( _idx, value );
}
