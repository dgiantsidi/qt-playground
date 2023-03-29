#include "../../file-parser/file_parser.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

#if 0
  file_parser c("file.csv");
  c.parse_file();
#endif
  MainWindow w;
#if 0
  w.set_file_parser(&c);
#endif
  w.show();

  return a.exec();
}
