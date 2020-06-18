
#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) {}

protected:
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *) override;
#endif

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

    QGraphicsView *GetView() const;

private:

    GraphicsView* graphics_view;
};

#endif // VIEW_H
