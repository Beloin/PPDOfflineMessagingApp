#!/bin/bash

cmake -S . -B build;
pushd build;
cp compile_commands.json ../;
popd;
