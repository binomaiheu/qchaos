#ifndef QChaosWindow_h
#define QChaosWindow_h


#include <QWidget>

class QComboBox;
class QLabel;
class QPushButton;
class QGridLayout;
class QSpinBox;
class QChaosPlot;

class QChaosWindow : public QWidget {
  Q_OBJECT

public:
  QChaosWindow( QWidget *parent = 0 );

private slots:
  void exportPDF();

private:
  QChaosPlot    *plot;
  QComboBox      *modelComboBox;
  QLabel         *modelLabel;
  QPushButton    *quitButton;
  QPushButton    *zoomButton;
  QPushButton    *drawButton;
  QPushButton    *resetButton;
  QGridLayout    *mainLayout;
  QSpinBox       *niterBox;
};


#endif /* #ifndef QChaosWindow_h */
