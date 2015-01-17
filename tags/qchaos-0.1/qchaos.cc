/*
qdynsys

Some dynamic system action in Qt...
*/

#include <QApplication>

#include "QChaosWindow.hh"

int main( int argc, char *argv[] ) {

  QApplication theApp( argc, argv );
  
  QChaosWindow mw;
  mw.show();
  
  return theApp.exec();
} 
