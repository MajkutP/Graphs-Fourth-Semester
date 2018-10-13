#include "GraphPainter.h"

void GraphPainter::SetStorage(GraphStorage& added)
{
    m_storagePointer = &added;
}

void GraphPainter::paintEvent(QPaintEvent *)
{
    const double pi = 3.14;
    const double circleRadius = 350.0;
    unsigned numberOfVertices =(*m_storagePointer)->getNumberOfVertices();
    double angle = 2*pi/numberOfVertices;
    double currentAngle = -pi/2.0;
    std::vector <double> angles (numberOfVertices, 0.0);
    QPainter p(this);
    p.fillRect(rect(), QColor(255,255,255,255));
    p.translate(p.device()->width()/2.0,p.device()->height()/2.0);

    for (unsigned i = 0; i<numberOfVertices; ++i)
    {
        angles.at(i) = currentAngle;
        currentAngle +=angle;
    }

    std::vector<std::pair<int, int>> edges = (*m_storagePointer)->GetEdges();

    for(unsigned i=0; i<edges.size(); ++i)
    {
        int vertex1 = edges.at(i).first;
        int vertex2 = edges.at(i).second;
        double x_1 = circleRadius * cos(angles[vertex1]);
        double y_1 = circleRadius * sin(angles[vertex1]);

        double x_2 = circleRadius * cos(angles[vertex2]);
        double y_2 = circleRadius * sin(angles[vertex2]);

        p.drawLine(QPoint(x_1, y_1), QPoint(x_2, y_2));
    }

    for (unsigned i = 0; i<numberOfVertices; ++i)
    {
        double x = circleRadius * cos(currentAngle);
        double y = circleRadius * sin(currentAngle);
        currentAngle +=angle;
        p.setBrush(QColor(0,255,0,255));
        p.drawEllipse(QPoint(x,y), 20, 20);
        p.drawText(x-4,y+5, QString("%1").arg(i+1));
    }
}
