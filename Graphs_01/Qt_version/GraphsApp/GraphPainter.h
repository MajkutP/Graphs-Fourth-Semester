#ifndef GRAPHPAINTER_H
#define GRAPHPAINTER_H

#include "GraphStorage.h"
#include <QPainter>

/// This object was created to handle graph painting
class GraphPainter : public QWidget
{
public:
    /// Basic constructor, initializes pointer
    /// to storage with nullptr
    /// Apart from that, it does nothing
    GraphPainter():
        m_storagePointer(nullptr) {}

    /// Sets place where graph is stored.
    void SetStorage(GraphStorage& added);

    /// This function (event) handles painting graph on
    /// the screen using circle representation.
    void paintEvent(QPaintEvent *);

private:
    /// Pointer to place where graph is stored.
    /// It allows quick access to representations
    GraphStorage* m_storagePointer;

};


#endif // GRAPHPAINTER_H
