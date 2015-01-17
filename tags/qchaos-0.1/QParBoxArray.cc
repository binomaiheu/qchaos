#include <stdio.h>

#include <QGridLayout>
#include <QLabel>

#include "QParBox.hh"
#include "QParBoxArray.hh"

QParBoxArray::QParBoxArray( const char *name, int size, QWidget *parent ) :
  QGroupBox( name, parent ), _npars(size) {
  
  if ( _npars > NMAX_PARAMETERS ) _npars = NMAX_PARAMETERS;
  
  _ly = new QGridLayout;
  
  char s[20];
  
  for ( int i = 0; i< _npars; i++ ){
    sprintf( s, "p%d = ", i );
    _label[i] = new QLabel( s );
    _pbox[i] = new QParBox( i, this );
    
    _pbox[i]->setDecimals( 4 );
    _pbox[i]->setSingleStep( 0.01 );
    
    QObject::connect( _pbox[i], SIGNAL(parameterChanged(int,double)),
		      this, SIGNAL(parameterChanged(int,double)) );
    _ly->addWidget( _label[i], i, 0 );
    _ly->addWidget( _pbox[i], i, 1 );
  }
  
  setLayout( _ly );
}

QParBoxArray::~QParBoxArray( ) {
  for ( int i = 0; i< _npars; i++ ) {
    delete _label[i];
    delete _pbox[i];
  }
}

void QParBoxArray::setParameters( int n, double *pars ) {
  for ( int i = 0; i < n; i++ ){
    _pbox[i]->setEnabled( true );
    _pbox[i]->setValue( pars[i] );
  }
  for ( int i = n; i < _npars; i++ ) {
    _pbox[i]->setEnabled( false );
  }
} 
