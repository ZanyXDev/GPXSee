#include "tooltip.h"
#include "temperaturegraphitem.h"

TemperatureGraphItem::TemperatureGraphItem(const Graph &graph,
  QGraphicsItem *parent) : GraphItem(graph, parent)
{
	qreal sum = 0;

	for (int j = 1; j < graph.size(); j++)
		sum += graph.at(j).y() * (graph.at(j).s() - graph.at(j-1).s());
	_avg = sum/graph.last().s();

	setToolTip(toolTip(Metric));
}

QString TemperatureGraphItem::toolTip(Units units) const
{
	ToolTip tt;
	qreal scale = (units == Metric) ? 1.0 : C2FS;
	qreal offset = (units == Metric) ? 0 : C2FO;
	QString su = (units == Metric) ?
	  QChar(0x00B0) + tr("C") : QChar(0x00B0) + tr("F");

	tt.insert(tr("Average"), QString::number(avg() * scale + offset, 'f', 1)
	  + UNIT_SPACE + su);
	tt.insert(tr("Maximum"), QString::number(max() * scale + offset, 'f', 1)
	  + UNIT_SPACE + su);
	tt.insert(tr("Minimum"), QString::number(min() * scale + offset, 'f', 1)
	  + UNIT_SPACE + su);

	return tt.toString();
}

void TemperatureGraphItem::setUnits(Units units)
{
	setToolTip(toolTip(units));
}
