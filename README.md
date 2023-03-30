# Qt-example
The code extends the QCustomPlot examples (https://www.qcustomplot.com/index.php/introduction)

# System requirements
The code is developped and tested (natively) in an Ubuntu 18.04 LTS machine (x86). We also provide a Dockerfile which builds and runs the application and some basic testing.

## Libraries
You should install the following dependencies through your package manager `qt5-default qt5-doc qt5-doc-html qtbase5-doc-html libgtest-dev cmake`. You may ignore `libgtest-dev` and `cmake` if you do not want to run the tests. 

## Build and run

To run the application:
- `cd <src-dir>/examples/my_app`
- `qmake`
- `make -j4`
- `./myapp`

To run the test:
- `cd <src-dir>/gtest`
- `sh ./build_static_libs.sh` (which installs the static libraries for gtest in your system)
- `qmake && make`
- `./example`

# Docker

We provide a Dockerfile and instructions on how to build and run the application (so we won't mess up with your system-wide packages installations :).
We used the following docker version `Docker version 20.10.21, build 20.10.21-0ubuntu1~18.04.2`.

## To build the container:
`docker build . -t example-docker`
## To run the application:
`QT_GRAPHICSSYSTEM="native" docker run -it --rm --env DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix example-docker bash -c "cd /home/myuser/app/examples/my_app && qmake && make -j && ./my_app"`
## To run the tests:
`QT_GRAPHICSSYSTEM="native" docker run -it --rm --env DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix example-docker bash -c "cd /home/myuser/app/gtest && bash ./build_static_libs.sh && cd /home/myuser/app/gtest && qmake && make -j && ./example`
