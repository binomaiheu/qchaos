#include "QChaosModel.hh"

QChaosModel::QChaosModel( std::string nm, int n ) :
  name( nm ), npars( n ) {
  par = new double[npars];
  std::cout << "Constructed model " << name << " with "
	    << npars << " parameters." << std::endl;
}

QChaosModel::~QChaosModel(){
  if ( par ) delete [] par;
}


double QChaosModel::getParameter( int idx ) {
  if ( idx >= npars ) {
    std::cerr << "*** error : index out of range (max. "
	      << npars - 1 << ") !" << std::endl;
    return 0.;
  }
  return par[idx];
}


void QChaosModel::setParameter( int idx, double value ) {
  if ( idx >= npars ) {
    std::cerr << "*** error : index out of range (max. "
	      << npars - 1 << ") !" << std::endl;
    return;
  }
  
  if ( value != par[idx] ) {
    par[idx] = value;
    emit parameterChanged( idx, value );
  }
  
  return;
}
