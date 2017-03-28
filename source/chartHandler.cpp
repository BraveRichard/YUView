/*  This file is part of YUView - The YUV player with advanced analytics toolset
*   <https://github.com/IENT/YUView>
*   Copyright (C) 2015  Institut für Nachrichtentechnik, RWTH Aachen University, GERMANY
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   (at your option) any later version.
*
*   In addition, as a special exception, the copyright holders give
*   permission to link the code of portions of this program with the
*   OpenSSL library under certain conditions as described in each
*   individual source file, and distribute linked combinations including
*   the two.
*
*   You must obey the GNU General Public License in all respects for all
*   of the code used other than OpenSSL. If you modify file(s) with this
*   exception, you may extend this exception to your version of the
*   file(s), but you are not obligated to do so. If you do not wish to do
*   so, delete this exception statement from your version. If you delete
*   this exception statement from all source files in the program, then
*   also delete it here.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "chartHandler.h"

#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include "playlistItem.h"
#include "statisticsExtensions.h"

// Default-Constructor
ChartHandler::ChartHandler()
{
}

// see docu @ChartHandler.h
QChartView* ChartHandler::createChart(playlistItem *aItem)
{/*
  // getting tha data
  QMap<QString, QList<QList<QVariant>>>* map = aItem->getData(aItem->getFrameIndexRange(), true);

  // creating default chart
  QChart *chart = new QChart();
  chart->setTitle("Simple barchart");
  chart->setAnimationOptions(QChart::SeriesAnimations);

  foreach (QString key, map->keys())
  {
    QList<QList<QVariant>> alldata = map->value(key);

    QBarSeries *series = new QBarSeries();
    foreach (QList<QVariant> list, alldata)
    {
      QBarSet* set = new QBarSet(key);
      foreach (QVariant data, list)
      {
        if(data.canConvert<statisticsItem_Value>())
        {
          statisticsItem_Value item = data.value<statisticsItem_Value>();
          *set << item.value;
        }
      }
      series->append(set);
    }
    chart->addSeries(series);
  }

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  return chartView;
  */

  return this->makeDummyChart();
}

//dummy
QChartView* ChartHandler::makeDummyChart()
{
  QBarSet *set0 = new QBarSet("Jane");
  QBarSet *set1 = new QBarSet("John");
  QBarSet *set2 = new QBarSet("Axel");
  QBarSet *set3 = new QBarSet("Mary");
  QBarSet *set4 = new QBarSet("Samantha");

  *set0 << 1 << 2 << 3 << 4 << 5 << 6;
  *set1 << 5 << 0 << 0 << 4 << 0 << 7;
  *set2 << 3 << 5 << 8 << 13 << 8 << 5;
  *set3 << 5 << 6 << 7 << 3 << 4 << 5;
  *set4 << 9 << 7 << 5 << 3 << 1 << 2;

  QBarSeries *series = new QBarSeries();
  series->append(set0);
  series->append(set1);
  series->append(set2);
  series->append(set3);
  series->append(set4);

  QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Simple barchart example");
  chart->setAnimationOptions(QChart::SeriesAnimations);

  QStringList categories;
  categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
  QBarCategoryAxis *axis = new QBarCategoryAxis();
  axis->append(categories);
  chart->createDefaultAxes();
  chart->setAxisX(axis, series);

  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignBottom);

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  return chartView;
}
