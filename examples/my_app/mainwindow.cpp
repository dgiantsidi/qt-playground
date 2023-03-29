/***************************************************************************
 **                                                                        **
 **  QCustomPlot, an easy to use, modern plotting widget for Qt            **
 **  Copyright (C) 2011-2018 Emanuel Eichhammer                            **
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
 **  Website/Contact: http://www.qcustomplot.com/                          **
 **             Date: 25.06.18                                             **
 **          Version: 2.0.1                                                **
 ****************************************************************************/

#include "mainwindow.h"
#include "../../file-parser/file_parser.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  p = new file_parser("file.csv");
  p->parse_file();
  ui->setupUi(this);
  setupPlot();

  // configure scroll bars:
  // Since scroll bars only support integer values, we'll set a high default
  // range of -500..500 and divide scroll bar position values by 100 to provide
  // a scroll range -5..5 in floating point axis coordinates. if you want to
  // dynamically grow the range accessible with the scroll bar, just increase
  // the the minimum/maximum values of the scroll bars as needed.
  ui->horizontalScrollBar->setRange(0, (p->y.count() + 1) * p->timestep);
  //   ui->verticalScrollBar->setRange(0, 3);

  // create connection between axes and scroll bars:
  connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this,
          SLOT(horzScrollBarChanged(int)));
  // connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this,
  // SLOT(vertScrollBarChanged(int)));
  //  connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this,
  //  SLOT(xAxisChanged(QCPRange))); connect(ui->plot->yAxis,
  //  SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

  // initialize axis range (and scroll bar positions via signals we just
  // connected):
  ui->plot->xAxis->setRange(0, 20000);
  // ui->plot->yAxis->setRange(0, 3, Qt::AlignCenter);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupPlot() {

  const int nums = p->y.count(); // 300000;
  // qDebug() << "nums=" << nums << "\n";
  QVector<double> x(nums), y(nums); // initialize with entries 0..100
  for (int i = 0; i < nums; ++i) {
    x[i] = 100 * i; // x goes from -1 to 1
    y[i] = p->y[i]; // i % 2;   // let's plot a quadratic function
    // qDebug() << y[i] << " " << p->y[i] << "\n";
  }
  // The following plot setup is mostly taken from the plot demos:
  ui->plot->addGraph();
  ui->plot->graph()->setPen(QPen(Qt::blue));
  ui->plot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
  ui->plot->graph()->setPen(QPen(Qt::red));
  ui->plot->axisRect()->setBackground(QBrush(Qt::black));
  constexpr int left = 15, top = 15, right = 15;
  constexpr int bottom = 400;
  ui->plot->axisRect()->setMinimumMargins(QMargins(
      left, top, right, bottom)); // add some more minimum space at bottom left
                                  // of rect for subfigure label (15 is default)

  // customPlot->axisRect()->setBackground(QPixmap("./black_image.jpg"));
  ui->plot->graph()->setData(x, y);
  ui->plot->graph()->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsStepLeft);
  // ui->plot->axisRect()->setupFullAxesBox(true);
  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  QSharedPointer<QCPAxisTickerFixed> fixedLongitudeTicker(
      new QCPAxisTickerFixed);
  auto tick_step = 10000; //(nums <= 20) ? 100 : nums*100/20;
  fixedLongitudeTicker->setTickStep(tick_step);
  fixedLongitudeTicker->setScaleStrategy(
      QCPAxisTickerFixed::ssNone); // and no scaling of the tickstep (like
                                   // multiples or powers) is allowed
  ui->plot->xAxis->setTicker(fixedLongitudeTicker);
  ui->plot->xAxis->setTickLabels(true);
  ui->plot->xAxis->setTickPen(QPen(Qt::black));
  auto &customPlot = ui->plot;
  customPlot->xAxis->grid()->setVisible(false);
  //    customPlot->xAxis->setRange(0, (nums+1)*100);
  customPlot->yAxis->setRange(0, 2);
  customPlot->yAxis->grid()->setVisible(false);

  customPlot->xAxis->setTickLabelColor(Qt::black);
  customPlot->xAxis->setBasePen(QPen(Qt::black));
  customPlot->xAxis->setLabelColor(Qt::black);
  customPlot->xAxis->setTickPen(QPen(Qt::black));
  customPlot->xAxis->setSubTickPen(QPen(Qt::black));
}

void MainWindow::horzScrollBarChanged(int value) {

  // std::cout << value << " " << ui->plot->xAxis->range().size() << "\n";

  if (qAbs(ui->plot->xAxis->range().center() - value / 100.0) > 0.01) // if user
  // is dragging plot, we don't want to replot twice
  /*
  if (qAbs(ui->plot->xAxis->range().center() >
           value)) // if user is dragging plot, we don't want to replot twice
  */
  {
    /*
  std::cout << "setRange() " << value << "  "
            << ui->plot->xAxis->range().size() << "\n";
            */
    // ui->plot->xAxis->setRange(value, value +
    // ui->plot->xAxis->range().size());
    ui->plot->xAxis->setRange(value, value + ui->plot->xAxis->range().size());
    // ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(),
    // Qt::AlignCenter);
    ui->plot->replot();
  }
}

#if 0
void MainWindow::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        // ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
        // ui->plot->replot();
    }
}
#endif

void MainWindow::xAxisChanged(QCPRange range) {
  // std::cout << "setValue()" << qRound(range.center() * 100.0) << "\n";
  ui->horizontalScrollBar->setValue(
      qRound(range.center() * 100.0)); // adjust position of scroll bar slider
  ui->horizontalScrollBar->setPageStep(
      qRound(range.size() * 100.0)); // adjust size of scroll bar slider
}

#if 0
void MainWindow::yAxisChanged(QCPRange range)
{
    //ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
    //ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}
#endif
