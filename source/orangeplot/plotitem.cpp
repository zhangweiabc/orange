#include "plotitem.h"
#include "plot.h"

#include <QtCore/QPropertyAnimation>

// Copied from OrangeWidgets/plot/owconstants.py
const int xBottom = 2;
const int yLeft = 0;

PlotItem::PlotItem(QGraphicsItem* parent, QGraphicsScene* scene): QGraphicsItem(parent, scene), 
    m_plot(0)
{
    set_axes(xBottom, yLeft);
    set_auto_scale(true);
    set_in_background(false);
}

PlotItem::~PlotItem()
{
    detach();
}

void PlotItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}

QRectF PlotItem::boundingRect() const
{
    return QRectF();
}

void PlotItem::attach(Plot* plot)
{
    plot->add_item(this);
}

void PlotItem::detach()
{
    if (m_plot)
    {
        m_plot->remove_item(this);
    }
}

QPair< int, int > PlotItem::axes() const
{
    return m_axes;
}

void PlotItem::set_axes(int x_axis, int y_axis)
{
    m_axes.first = x_axis;
    m_axes.second = y_axis;
}

bool PlotItem::is_auto_scale() const
{
    return m_autoScale;
}

void PlotItem::set_auto_scale(bool auto_scale)
{
    m_autoScale = auto_scale;
}

QRectF PlotItem::data_rect() const
{
    return m_dataRect;
}

void PlotItem::set_graph_transform(const QTransform& transform)
{
    m_graphTransform = transform;
}

QTransform PlotItem::graph_transform() const
{
    return m_graphTransform;
}

void PlotItem::set_zoom_transform(const QTransform& zoom)
{
    m_zoom_transform = zoom;
}

QTransform PlotItem::zoom_transform() const
{
    return m_zoom_transform;
}

void PlotItem::update_properties()
{

}

QRectF PlotItem::rect_from_data(const QList< double >& x_data, const QList< double >& y_data)
{
    int n = qMin(x_data.size(), y_data.size());
    if (n == 0)
        return QRectF();
    double x_min, x_max, y_min, y_max;
    x_min = x_max = x_data[0];
    y_min = y_max = y_data[0];
    for (int i = 1; i < n; ++i)
    {
        x_min = qMin(x_min, x_data[i]);
        x_max = qMax(x_max, x_data[i]);
        y_min = qMin(y_min, y_data[i]);
        y_max = qMax(y_max, y_data[i]);
    }
    return QRectF(x_min, y_min, x_max-x_min, y_max-y_min);
}

void PlotItem::move_item(QGraphicsObject* item, const QPointF& pos, int duration)
{
    QPropertyAnimation* a = new QPropertyAnimation();
    a->setTargetObject(item);
    a->setPropertyName("pos");
    a->setStartValue(item->pos());
    a->setEndValue(pos);
    a->setDuration(duration);
    a->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlotItem::set_data_rect(const QRectF& dataRect) {
    m_dataRect = dataRect;
    if (m_plot)
    {
        m_plot->set_dirty();
    }
}

void PlotItem::set_in_background(bool bg)
{
    m_background = bg;
    if (m_plot)
    {
        m_plot->set_item_in_background(this, bg);
    }
}

bool PlotItem::is_in_background() const
{
    return m_background;
}

Plot* PlotItem::plot() 
{
    return m_plot;
}

void PlotItem::register_points()
{

}

