#!/bin/bash

sudo apt-get install -y bison flex
cd asn1c-0.9.27
./configure
make
sudo make install


