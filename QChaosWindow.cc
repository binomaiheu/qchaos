#include <QtGui>

#include <qwt_plot.h>

#include "QChaosWindow.hh"
#include "QChaosPlot.hh"
#include "QChaosModel.hh"
#include "QParBoxArray.hh"

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>


QChaosWindow::QChaosWindow( QWidget *parent ) :
  QWidget( parent ) {
  
  resize( 800, 600 );
  
// The plot
  plot = new QChaosPlot( this );
  
  /*
// the Export button
  QPushButton *expButton = new QPushButton( "&Save pdf" );
  expButton->resize( 75, 30 );
  QObject::connect(expButton, SIGNAL(clicked()), this, SLOT(exportPDF()));
  */

// the Draw button
  drawButton = new QPushButton( "&Draw" );
  drawButton->resize( 75, 30 );
  QObject::connect(drawButton, SIGNAL(clicked()), plot, SLOT(drawModel()));
  
// the Quit button
  quitButton = new QPushButton( "&Quit" );
  quitButton->resize( 75, 30 );
  QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
  
// the Reset button
  resetButton = new QPushButton( "&Reset Model" );
  resetButton->resize( 75, 30 );
  QObject::connect(resetButton, SIGNAL(clicked()), plot, SLOT(resetModel()));
  
  
// the Zoom button
  zoomButton = new QPushButton( "&Zoom" );
  zoomButton->resize( 75, 30 );
  zoomButton->setCheckable( true );
  QObject::connect(zoomButton, SIGNAL(toggled(bool)), plot, SLOT(enableZoom(bool)));
  
  
  QGroupBox *modelBox = new QGroupBox( tr("Model Selection") );
  
  modelComboBox = new QComboBox( modelBox );
  modelComboBox->addItem( tr("Henon Model"), QChaosPlot::Henon );
  modelComboBox->addItem( tr("Lozi Model"), QChaosPlot::Lozi );
  modelComboBox->addItem( tr("Aronson Model"), QChaosPlot::Aronson );
  modelComboBox->addItem( tr("Henon Conservative Model"), QChaosPlot::HenonC );
  modelComboBox->addItem( tr("Barnsley's Fern"), QChaosPlot::Barnsley );
  modelComboBox->addItem( tr("Smith Model"), QChaosPlot::Smith );
  modelComboBox->addItem( tr("Lorentz Attractor"), QChaosPlot::Lorentz );
  modelLabel = new QLabel(tr("&Model:") );
  modelLabel->setBuddy(modelComboBox);
  QObject::connect(modelComboBox, SIGNAL(activated(int)), plot, SLOT(setActive(int)));
  
  
// iterations spin box
  niterBox = new QSpinBox( modelBox );
  niterBox->setRange( 100, NMAX_ITERATIONS );
  niterBox->setSingleStep( 500 );
  niterBox->setValue( NDEF_ITERATIONS );
  QLabel *niterLabel = new QLabel( tr("Iterations:") );
  niterLabel->setBuddy( niterBox );
  QObject::connect( niterBox, SIGNAL(valueChanged(int)), plot, SLOT(setIterations(int)));
  
  
  QGridLayout *modelBoxLayout = new QGridLayout;
  modelBoxLayout->addWidget( modelComboBox, 0, 0, 1, 3, Qt::AlignRight );
  modelBoxLayout->addWidget( niterLabel, 1, 0, Qt::AlignLeft );
  modelBoxLayout->addWidget( niterBox, 1, 1, 1, 2, Qt::AlignRight );
  modelBoxLayout->addWidget( drawButton, 2, 0 );
  modelBoxLayout->addWidget( resetButton, 2, 1 );
  modelBoxLayout->addWidget( zoomButton, 2, 2 );
  
  modelBox->setLayout( modelBoxLayout );
  
  
// The parameters
  QParBoxArray *parCtrl = new QParBoxArray( "Model Parameters", 5 ,this );
  QObject::connect( parCtrl, SIGNAL(parameterChanged(int,double)),
		    plot, SLOT(setParameter(int,double)));
  
// When new model selected, need to set the parameters
  QObject::connect( plot, SIGNAL(modelParameters(int,double*)),
		    parCtrl, SLOT(setParameters(int,double*)) );
  
// initialize
  parCtrl->setParameters( plot->getActiveModel()->getNPars(),
			  plot->getActiveModel()->getPars() );
  
  parCtrl->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) );
  
  QTextEdit *infoText = new QTextEdit( this );
  infoText->setReadOnly ( true );
  QObject::connect( plot, SIGNAL(modelInfo(const QString&)),
		    infoText, SLOT(setText(const QString&)));
  
  infoText->setText( plot->getActiveModel()->getInfo() );
  
  
  
// Define the layout of the program
  QGridLayout *butLayout = new QGridLayout;
  butLayout->addWidget( modelBox, 0, 0, 1, 3 );
  butLayout->addWidget( parCtrl, 1, 0, 1, 3 );
  butLayout->addWidget( infoText, 2, 0, 1, 3 );
  //butLayout->addWidget( expButton, 4, 1, 1, 1 );
  butLayout->addWidget( quitButton, 4, 2, 1, 1 );
  
  
  mainLayout = new QGridLayout;
  mainLayout->addWidget( plot, 0, 0 );
  mainLayout->addLayout( butLayout, 0, 1 );
  
  
  this->setLayout( mainLayout );
  
  this->setWindowTitle( tr("QChaos - Chaotic Systems Viewer") );
  
// draw the first model...
  plot->drawModel();
  
  this->update();
}



// export the graphic as a pdf...
void QChaosWindow::exportPDF() {
  
    /*
  const QString fileName = QFileDialog::getSaveFileName(
    this, "Export File Name", QString(),
    "PDF Documents (*.pdf)");
  
  if ( !fileName.isEmpty() ) {
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName(fileName);
    plot->print(printer);
  }
  */

  
  return;
}

