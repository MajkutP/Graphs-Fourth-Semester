#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Input.h"
#include "GraphPainter.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Constructor of main window that displays all information to user
    explicit MainWindow(QWidget *parent = 0);

    /// This function enables locked buttons when graph has been
    /// correctly loaded from file.
    void EnableButtons();

    /// Basic destructor for class MainWindow
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphPainter painter;
    GraphStorage storedGraph;

private slots:
    /// Defines what happens when "Load graph from file" button
    /// has been pressed. Displays file dialog that allows user
    /// to choose file with existing graph representation. If loading
    /// graph from file was succesful, enables locked buttons.
    void on_pushButton_clicked();

    /// Defines what happens when "Draw as circle" button has been pressed.
    /// Draws graph in a circle representation
    void on_pushButton_2_clicked();

    /// Defines what happens when "Save as text file" button has been
    /// pressed. Displays file dialog that allows user to save current
    /// graph representation to some kind of text file.
    void on_pushButton_3_clicked();

    /// Defines what happens when "Generate G(n,l)" button has been pressed.
    /// Generates random graph based on user input - number of vertices and edges.
    /// Displays graph on screen.
    void on_pushButton_4_clicked();

    /// Defines what happens when "Generate G(n,p)" button has been pressed.
    /// Generates random graph based on user input - number of vertices and probability
    /// of placing edge between vertices. Displays generated graph on screen using circle
    /// representation.
    void on_pushButton_5_clicked();

    /// Handles choosing graph representation
    void on_comboBox_currentIndexChanged(const QString &arg1);

};

#endif // MAINWINDOW_H
