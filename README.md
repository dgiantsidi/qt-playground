# QCustomPlot
QCustomPlot is a Qt C++ widget for plotting and data visualization. It has no further dependencies and is well documented. This plotting library focuses on making good looking, publication quality 2D plots, graphs and charts, as well as offering high performance for realtime visualization applications. Have a look at the Setting Up and the Basic Plotting tutorials to get started.  QCustomPlot can export to various formats such as vectorized PDF files and rasterized images like PNG, JPG and BMP. QCustomPlot is the solution for displaying of realtime data inside the application as well as producing high quality plots for other media.

Author: Emanuel Eichhammer

QCustomPLot is under default license GPL, feel free to use QCP in free software! Visit https://www.qcustomplot.com for commertial license and more information!



# Docker
## To build the container:
`docker build . -t example-docker`
## To run the application:
`QT_GRAPHICSSYSTEM="native" docker run -it --rm --env DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix example-docker bash -c "cd /home/myuser/app/examples/my_app && qmake && make -j && ./my_app"`
## To run the tests:
`QT_GRAPHICSSYSTEM="native" docker run -it --rm --env DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix example-docker bash -c "cd /home/myuser/app/gtest && bash ./build_static_libs.sh && cd /home/myuser/app/gtest && qmake && make -j && ./example`
