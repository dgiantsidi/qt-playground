#pragma once
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <iostream>

class file_parser {
public:
  file_parser() : flag(false), fname(""){};

  explicit file_parser(const std::string &filename) : flag(false), fname("") {
    fname = QString::fromStdString(filename);
  };

  explicit file_parser(std::string &&filename) : flag(false), fname("") {
    fname = QString::fromStdString(filename);
  }

  int parse_file() {
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << file.errorString();
      return -1;
    }

    while (!file.atEnd()) {
      QByteArray line = file.readLine();
      auto l = line.split(';').first();
      if (l == "TIMESTEP") {
        timestep = std::atoi(line.split(';')[1]);
      }
      if (l == "UNITS") {
        units = line.split(';')[1];
      }
      if (l == "DATA") {
        flag = true;
      }
      if (flag) {
        y.append(std::atoi(line.split(';').first()));
      }
    }
#if 0
    qDebug() << "TIMESTEP=" << timestep;
    qDebug() << "UNITS=" << units;
    qDebug() << y;
#endif
    return 1;
  }

  bool ret_flag() { return flag; }
  const QString &ret_units() { return units; }
  const int &ret_timestep() { return timestep; }
  const QVector<int> &ret_y() { return y; }
  QVector<int> y;
  bool flag;
  QString fname, units;
  int timestep;
};
