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

  void on_comboBox_currentIndexChanged(int index);

  void on_approxShadeSurface_toggled(bool checked);

  void on_SubdivSteps_valueChanged(int value);

  void on_tessInner1_valueChanged(int arg1);

  void on_tessInner2_valueChanged(int arg1);

  void on_tessOuter1_valueChanged(int arg1);

  void on_tessOuter2_valueChanged(int arg1);

  void on_tessOuter3_valueChanged(int arg1);

  void on_tessOuter4_valueChanged(int arg1);

  void on_nonTesselatedWireframe_toggled(bool checked);

  void on_analyticalNormalsCheckbox_toggled(bool checked);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
