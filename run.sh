#!/bin/bash
mkdir -p results
pushd results
../build/main
open image.ppm
popd
