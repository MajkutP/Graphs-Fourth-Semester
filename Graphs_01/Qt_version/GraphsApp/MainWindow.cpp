#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include "Output.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::EnableButtons()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose file"));
    if (fileName!=""){
        Input inputGetter(fileName);
        inputGetter.OpenFile();
        if (inputGetter.GetInputFromFile(storedGraph)==false){
            QMessageBox msgBox;
            msgBox.setText("File format was not valid.");
            msgBox.exec();
            return;
        }
        update();
        storedGraph->PrintGraph(*(this->ui));
        EnableButtons();


        if (storedGraph->GetRepresentation()=='l'){
            int index = ui->comboBox->findText("Adjacency list");
            ui->comboBox->setCurrentIndex(index);
        }
        else if (storedGraph->GetRepresentation()=='a'){
            int index = ui->comboBox->findText("Adjacency matrix");
            ui->comboBox->setCurrentIndex(index);
        }
        else
        {
            int index = ui->comboBox->findText("Incidence matrix");
            ui->comboBox->setCurrentIndex(index);
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    update();
    painter.SetStorage(storedGraph);
    ui->verticalLayout->addWidget(&painter);

}

void MainWindow::on_pushButton_3_clicked()
{

    Output save (QFileDialog::getSaveFileName(this, tr("Where to save?")));
    if (save.GetFileName()!="")
        save.SaveToFile(storedGraph);

}



void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1=="Adjacency list")
        storedGraph->ChangeToAdjacencyList();
    else if (arg1 == "Adjacency matrix")
        storedGraph->ChangeToAdjacencyMatrix();
    else
        storedGraph->ChangeToIncidenceMatrix();

    update();
    storedGraph->PrintGraph(*(this->ui));

}

void MainWindow::on_pushButton_4_clicked()
{
    std::vector<std::vector<int>> temp;
    storedGraph.AddGraphToStorage(temp, 'a');
    int numberOfVertices = QInputDialog::getInt(this, tr("Please enter number of vertices."),
                                                    tr("Number of vertices: "), 0, 0);

    int numberOfEdges = QInputDialog::getInt(this, tr("Please enter number of edges."),
                                                    tr("Number of edges: "), 0, 0);

    storedGraph->GenerateRandomGraphBasedOnDensity( numberOfVertices, numberOfEdges);
    update();
    storedGraph->PrintGraph(*(this->ui));
    EnableButtons();
    int index = ui->comboBox->findText("Adjacency matrix");
    ui->comboBox->setCurrentIndex(index);
}

void MainWindow::on_pushButton_5_clicked()
{
    std::vector<std::vector<int>> temp;
    storedGraph.AddGraphToStorage(temp, 'a');
    int numberOfVertices, probability;
    bool ok;
    numberOfVertices = QInputDialog::getInt(this, tr("Please enter number of vertices."),
                                                    tr("Number of vertices: "), 0, 0);

    probability = QInputDialog::getDouble(this, tr("Please enter probability."),
                                                    tr("Probability: "), 0.0 , 0.0, 100.0, 2 ,&ok);

    storedGraph->GenerateRandomGraphBasedOnProbability(numberOfVertices, probability);
    update();
    storedGraph->PrintGraph(*(this->ui));
    EnableButtons();
    int index = ui->comboBox->findText("Adjacency matrix");
    ui->comboBox->setCurrentIndex(index);

}
