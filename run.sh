#!/bin/bash
mkdir -p results
pushd results
../build/main
open render.ppm
popd
