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

  ui->MainDisplay->updateBuffers( meshes[0]);
  ui->MainDisplay->settings.modelLoaded = true;
  ui->MainDisplay->update();
}

void MainWindow::on_ImportOBJ_clicked() {
  importOBJ();
  ui->SubdivSteps->setEnabled(true);
}

void MainWindow::on_enableTesselation_toggled(bool checked) {
    ui->MainDisplay->settings.tesselation = checked;
    ui->MainDisplay->update();
}

void MainWindow::on_approxShadeSurface_toggled(bool checked) {
    ui->MainDisplay->settings.approxFlatShadeSurface = checked;
    ui->MainDisplay->update();
}

void MainWindow::on_approxShadeLimitSurface_toggled(bool checked) {
    ui->MainDisplay->settings.approxFlatShadeLimitSurface = checked;
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

void MainWindow::on_limitVertices_toggled(bool checked) {
    ui->MainDisplay->settings.limitVertices = checked;
    auto value = ui->MainDisplay->settings.lastSubdivLevel;
    ui->MainDisplay->updateBuffers( meshes[value] );
    ui->MainDisplay->update();
}

void MainWindow::on_fillLimitSurface_toggled(bool checked) {
    ui->MainDisplay->settings.limitFilledTriangles = checked;
    auto value = ui->MainDisplay->settings.lastSubdivLevel;
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
