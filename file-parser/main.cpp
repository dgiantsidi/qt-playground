#include <QFile>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include "file_parser.h"


int main()
{
    file_parser a("file.csv");

    a.parse_file();

    return 0;
}

