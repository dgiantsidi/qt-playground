#!/usr/bin/env bash

cd /usr/src/gtest
sudo cmake .
sudo make
sudo mv libg* /usr/lib/
