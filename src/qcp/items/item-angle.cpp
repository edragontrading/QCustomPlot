/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2022 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: https://www.qcustomplot.com/                         **
**             Date: 06.11.22                                             **
**          Version: 2.1.1                                                **
****************************************************************************/

#include <qcp/core.h>
#include <qcp/items/item-angle.h>
#include <qcp/painter.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPItemAngle
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPItemAngle
  \brief A straight line that spans infinitely in both directions

  \image html QCPItemAngle.png "Straight line example. Blue dotted
  circles are anchors, solid blue discs are positions."

  It has two positions, \a point1 and \a point2, which define the straight line.
*/

/*!
  Creates a straight line item and sets default values.

  The created item is automatically registered with \a parentPlot. This
  QCustomPlot instance takes ownership of the item, so do not delete it manually
  but use QCustomPlot::removeItem() instead.
*/
QCPItemAngle::QCPItemAngle(QCustomPlot *parentPlot)
    : QCPAbstractItem(parentPlot), mAngleWidth(60),
      point1(createPosition(QLatin1String("point1"))),
      point2(createPosition(QLatin1String("point2"))) {
    point1->setCoords(0, 0);
    point2->setCoords(1, 1);

    setPen(QPen(Qt::black));
    setSelectedPen(QPen(Qt::blue, 2));
}

QCPItemAngle::~QCPItemAngle() {
}

/*!
  Sets the pen that will be used to draw the line

  \see setSelectedPen
*/
void QCPItemAngle::setPen(const QPen &pen) {
    mPen = pen;
}

/*!
  Sets the pen that will be used to draw the line when selected

  \see setPen, setSelected
*/
void QCPItemAngle::setSelectedPen(const QPen &pen) {
    mSelectedPen = pen;
}

/*!
  Sets the brush that will be used to fill the rectangle. To disable filling,
  set \a brush to Qt::NoBrush.

  \see setSelectedBrush, setPen
*/
void QCPItemAngle::setBrush(const QBrush &brush) {
    mBrush = brush;
}

/*!
  Sets the brush that will be used to fill the rectangle when selected. To
  disable filling, set \a brush to Qt::NoBrush.

  \see setBrush
*/
void QCPItemAngle::setSelectedBrush(const QBrush &brush) {
    mSelectedBrush = brush;
}

void QCPItemAngle::setAngleWidth(const double &width) {
    mAngleWidth = width;
}

/* inherits documentation from base class */
double QCPItemAngle::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const {
    Q_UNUSED(details)
    if (onlySelectable && !mSelectable) return -1;

    double result = QCPVector2D(pos).distanceSquaredToLine(point1->pixelPosition(), point2->pixelPosition());

    return result;
}

/* inherits documentation from base class */
void QCPItemAngle::draw(QCPPainter *painter) {
    QPolygonF triangle;
    QPointF origin(point1->pixelPosition());
    QPointF p1(point2->pixelPosition());
    QPointF p2(origin.x() + mAngleWidth, origin.y());

    if (origin.toPoint() == p1.toPoint()) return;

    QPointF rp1 = QPointF(std::min({origin.x(), p1.x(), p2.x()}), std::min({origin.y(), p1.y(), p2.y()}));
    QPointF rp2 = QPointF(std::max({origin.x(), p1.x(), p2.x()}), std::max({origin.y(), p1.y(), p2.y()}));

    QRectF rect = QRectF(rp1, rp2).normalized();
    double clipPad = mainPen().widthF();
    QRectF boundingRect = rect.adjusted(-clipPad, -clipPad, clipPad, clipPad);

    if (boundingRect.intersects(clipRect()))  // only draw if bounding rect of rect
    {                                         // item is visible in cliprect
        // Compute vectors
        QVector2D v1(p1 - origin);
        QVector2D v2(p2 - origin);

        // Arc bounding rectangle (for angle arc drawing)
        QRectF arcRect(origin.x() - mAngleWidth, origin.y() - mAngleWidth, mAngleWidth * 2, mAngleWidth * 2);

        // Calculate angle directions
        double startAngle = std::atan2(-v1.y(), v1.x()) * 180.0 / M_PI;  // note: -y due to Qt's inverted Y-axis
        double endAngle = std::atan2(-v2.y(), v2.x()) * 180.0 / M_PI;

        // Ensure angles are in correct range
        double spanAngle = endAngle - startAngle;

        // Draw the arc

        QPen pen = mainPen();
        pen.setStyle(Qt::DotLine);
        pen.setWidth(1);
        painter->setPen(pen);
        painter->setBrush(mainBrush());
        painter->drawPie(arcRect, static_cast<int>(startAngle * 16), static_cast<int>(spanAngle * 16));

        // Draw angle text and line
        painter->setPen(mainPen());
        painter->drawText(origin + QPointF(mAngleWidth + 5, 0), QString("%1°").arg(-std::round(spanAngle), 0, 'f', 0));
        painter->drawLine(origin, p1);
    }
}

/*! \internal

  Returns the pen that should be used for drawing lines. Returns mPen when the
  item is not selected and mSelectedPen when it is.
*/
QPen QCPItemAngle::mainPen() const {
    return mSelected ? mSelectedPen : mPen;
}

/*! \internal

  Returns the brush that should be used for drawing fills of the item. Returns
  mBrush when the item is not selected and mSelectedBrush when it is.
*/
QBrush QCPItemAngle::mainBrush() const {
    return mSelected ? mSelectedBrush : mBrush;
}
