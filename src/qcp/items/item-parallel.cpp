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
#include <qcp/items/item-parallel.h>
#include <qcp/painter.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPItemParallel
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPItemParallel
  \brief A straight line that spans infinitely in both directions

  \image html QCPItemParallel.png "Straight line example. Blue dotted
  circles are anchors, solid blue discs are positions."

  It has two positions, \a point1 and \a point2, which define the straight line.
*/

/*!
  Creates a straight line item and sets default values.

  The created item is automatically registered with \a parentPlot. This
  QCustomPlot instance takes ownership of the item, so do not delete it manually
  but use QCustomPlot::removeItem() instead.
*/
QCPItemParallel::QCPItemParallel(QCustomPlot *parentPlot)
    : QCPAbstractItem(parentPlot),
      point1(createPosition(QLatin1String("point1"))),
      point2(createPosition(QLatin1String("point2"))),
      point3(createPosition(QLatin1String("point3"))) {
    point1->setCoords(0, 0);
    point2->setCoords(1, 1);
    point3->setCoords(0, 1);

    setPen(QPen(Qt::black));
    setSelectedPen(QPen(Qt::blue, 2));
}

QCPItemParallel::~QCPItemParallel() {
}

/*!
  Sets the pen that will be used to draw the line

  \see setSelectedPen
*/
void QCPItemParallel::setPen(const QPen &pen) {
    mPen = pen;
}

/*!
  Sets the pen that will be used to draw the line when selected

  \see setPen, setSelected
*/
void QCPItemParallel::setSelectedPen(const QPen &pen) {
    mSelectedPen = pen;
}

/*!
  Sets the brush that will be used to fill the rectangle. To disable filling,
  set \a brush to Qt::NoBrush.

  \see setSelectedBrush, setPen
*/
void QCPItemParallel::setBrush(const QBrush &brush) {
    mBrush = brush;
}

/*!
  Sets the brush that will be used to fill the rectangle when selected. To
  disable filling, set \a brush to Qt::NoBrush.

  \see setBrush
*/
void QCPItemParallel::setSelectedBrush(const QBrush &brush) {
    mSelectedBrush = brush;
}

/* inherits documentation from base class */
double QCPItemParallel::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const {
    Q_UNUSED(details)
    if (onlySelectable && !mSelectable) return -1;

    // If B, C, A are known and D is opposite of B
    // D = A + (C - B)
    QPointF point4 = point1->pixelPosition() + (point3->pixelPosition() - point2->pixelPosition());

    double r1 = QCPVector2D(pos).distanceSquaredToLine(point1->pixelPosition(), point2->pixelPosition());
    double r2 = QCPVector2D(pos).distanceSquaredToLine(point4, point3->pixelPosition());

    return std::min({r1, r2});
}

/* inherits documentation from base class */
void QCPItemParallel::draw(QCPPainter *painter) {
    QPolygonF parallelogram;
    QPointF p1(point1->pixelPosition());
    QPointF p2(point2->pixelPosition());
    QPointF p3(point3->pixelPosition());

    // If B, C, A are known and D is opposite of B
    // D = A + (C - B)
    QPointF p4 = point1->pixelPosition() + (point3->pixelPosition() - point2->pixelPosition());

    if (p1.toPoint() == p2.toPoint() && p1.toPoint() == p3.toPoint()) return;

    QPointF rp1 = QPointF(std::min({p1.x(), p2.x(), p3.x(), p3.x()}), std::min({p1.y(), p2.y(), p3.y(), p4.y()}));
    QPointF rp2 = QPointF(std::max({p1.x(), p2.x(), p3.x(), p4.x()}), std::max({p1.y(), p2.y(), p3.y(), p4.y()}));

    QRectF rect = QRectF(rp1, rp2).normalized();
    double clipPad = mainPen().widthF();
    QRectF boundingRect = rect.adjusted(-clipPad, -clipPad, clipPad, clipPad);

    if (boundingRect.intersects(clipRect()))  // only draw if bounding rect of rect
    {                                         // item is visible in cliprect
        parallelogram << p1 << p2 << p3 << p4;
        painter->setPen(Qt::NoPen);
        painter->setBrush(mainBrush());
        painter->drawPolygon(parallelogram);

        painter->setPen(mainPen());
        painter->drawLine(p1, p2);
        painter->drawLine(p4, p3);
    }
}

/*! \internal

  Returns the pen that should be used for drawing lines. Returns mPen when the
  item is not selected and mSelectedPen when it is.
*/
QPen QCPItemParallel::mainPen() const {
    return mSelected ? mSelectedPen : mPen;
}

/*! \internal

  Returns the brush that should be used for drawing fills of the item. Returns
  mBrush when the item is not selected and mSelectedBrush when it is.
*/
QBrush QCPItemParallel::mainBrush() const {
    return mSelected ? mSelectedBrush : mBrush;
}
