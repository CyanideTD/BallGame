#include <QMouseEvent>
#include <iostream>
#include "view.h"
#include <QLayout>

void GraphicsView::wheelEvent(QWheelEvent *) {

}

View::View(QWidget *parent) : QFrame(parent) {
  graphics_view = new GraphicsView(this);
  graphics_view->show();
  graphics_view->setInteractive(true);
  graphics_view->setRenderHint(QPainter::Antialiasing, false);
  graphics_view->setDragMode(QGraphicsView::RubberBandDrag);
  graphics_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  graphics_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  graphics_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(graphics_view);
  setLayout(layout);
}

QGraphicsView *View::GetView() const {
  return graphics_view;
}
