#include "file_parser.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <iostream>

int main() {
  file_parser a("file.csv");

  a.parse_file();

  return 0;
}
