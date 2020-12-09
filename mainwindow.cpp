#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow) {
  qDebug() << "✓✓ MainWindow constructor";
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  qDebug() << "✗✗ MainWindow destructor";
  delete ui;
}


void MainWindow::importOBJ() {
  OBJFile newModel = OBJFile(QFileDialog::getOpenFileName(this, "Import OBJ File", "models/", tr("Obj Files (*.obj)")));
  meshes.clear();
  meshes.append( Mesh(&newModel) );

  unsigned short k;

  for (k = meshes.size(); k < ui->MainDisplay->settings.lastSubdivLevel+1; k++) {
      meshes.append(Mesh());
      meshes[k-1].subdivideCatmullClark(meshes[k]);
  }

  ui->MainDisplay->updateBuffers( meshes[ui->MainDisplay->settings.lastSubdivLevel]);
  ui->MainDisplay->settings.modelLoaded = true;
  ui->MainDisplay->update();
}

void MainWindow::on_ImportOBJ_clicked() {
  importOBJ();
  ui->SubdivSteps->setEnabled(true);
}

void MainWindow::on_approxShadeSurface_toggled(bool checked) {
    ui->MainDisplay->settings.approxFlatShading = checked;
    ui->MainDisplay->update();
}

void MainWindow::on_SubdivSteps_valueChanged(int value) {
    unsigned short k;

    for (k = meshes.size(); k < value+1; k++) {
        meshes.append(Mesh());
        meshes[k-1].subdivideCatmullClark(meshes[k]);
    }

    ui->MainDisplay->settings.lastSubdivLevel = value;
    ui->MainDisplay->updateBuffers( meshes[value] );
    ui->MainDisplay->update();
}

void MainWindow::on_tessInner1_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelInner0 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessInner2_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelInner1 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessOuter1_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelOuter0 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessOuter2_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelOuter1 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessOuter3_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelOuter2 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_tessOuter4_valueChanged(int arg1)
{
    ui->MainDisplay->settings.tessLevelOuter3 = arg1;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    ui->MainDisplay->update();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->MainDisplay->settings.renderingMode = index;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    auto value = ui->MainDisplay->settings.lastSubdivLevel;
    ui->MainDisplay->updateBuffers( meshes[value] );
    ui->MainDisplay->update();
}

void MainWindow::on_nonTesselatedWireframe_toggled(bool checked)
{
    ui->MainDisplay->settings.showNonTesselatedWireframe = checked;
    ui->MainDisplay->settings.uniformUpdateRequired = true;
    auto value = ui->MainDisplay->settings.lastSubdivLevel;
    ui->MainDisplay->updateBuffers( meshes[value] );
    ui->MainDisplay->update();
}
