#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objfile.h"
#include <QFileDialog>
#include "mesh.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  QVector<Mesh> meshes;
  void importOBJ();

private slots:
  void on_ImportOBJ_clicked();
  void on_approxShadeSurface_toggled(bool checked);
  void on_approxShadeLimitSurface_toggled(bool checked);
  void on_fillLimitSurface_toggled(bool checked);
  void on_limitVertices_toggled(bool checked);
  void on_SubdivSteps_valueChanged(int value);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
