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

#ifndef QCP_H
#define QCP_H

#include <qcp/axis/axis.h>
#include <qcp/axis/axisticker.h>
#include <qcp/axis/axistickerdatetime.h>
#include <qcp/axis/axistickerfixed.h>
#include <qcp/axis/axistickerlog.h>
#include <qcp/axis/axistickerpi.h>
#include <qcp/axis/axistickertext.h>
#include <qcp/axis/axistickertime.h>
#include <qcp/axis/range.h>
#include <qcp/colorgradient.h>
#include <qcp/core.h>
#include <qcp/datacontainer.h>
#include <qcp/global.h>
#include <qcp/item.h>
#include <qcp/items/item-bracket.h>
#include <qcp/items/item-curve.h>
#include <qcp/items/item-ellipse.h>
#include <qcp/items/item-line.h>
#include <qcp/items/item-pixmap.h>
#include <qcp/items/item-rect.h>
#include <qcp/items/item-triangle.h>
#include <qcp/items/item-angle.h>
#include <qcp/items/item-parallel.h>
#include <qcp/items/item-straightline.h>
#include <qcp/items/item-text.h>
#include <qcp/items/item-tracer.h>
#include <qcp/layer.h>
#include <qcp/layout.h>
#include <qcp/layoutelements/layoutelement-axisrect.h>
#include <qcp/layoutelements/layoutelement-colorscale.h>
#include <qcp/layoutelements/layoutelement-legend.h>
#include <qcp/layoutelements/layoutelement-textelement.h>
#include <qcp/lineending.h>
#include <qcp/paintbuffer.h>
#include <qcp/painter.h>
#include <qcp/plottable.h>
#include <qcp/plottable1d.h>
#include <qcp/plottables/plottable-bars.h>
#include <qcp/plottables/plottable-colormap.h>
#include <qcp/plottables/plottable-curve.h>
#include <qcp/plottables/plottable-errorbar.h>
#include <qcp/plottables/plottable-financial.h>
#include <qcp/plottables/plottable-graph.h>
#include <qcp/plottables/plottable-statisticalbox.h>
#include <qcp/polar/layoutelement-angularaxis.h>
#include <qcp/polar/polargraph.h>
#include <qcp/polar/polargrid.h>
#include <qcp/polar/radialaxis.h>
#include <qcp/scatterstyle.h>
#include <qcp/selection.h>
#include <qcp/selectiondecorator-bracket.h>
#include <qcp/selectionrect.h>
#include <qcp/vector2d.h>

#endif  // QCP_H
