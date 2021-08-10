#!/bin/bash


echo Carregando...

export SYSTEMC_HOME=/usr/local/systemc-2.3.3

g++ -I. -std=c++11 -o processador src/main.cpp -I include/  -I $SYSTEMC_HOME/include -L. -L $SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -l systemc -lm


