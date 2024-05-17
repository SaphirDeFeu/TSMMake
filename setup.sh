#!/bin/bash

echo "Set up build files"

if [ -d "./target" ]; then
  echo "Build folder already up"
else
  mkdir target
  mkdir target/obj
  mkdir target/obj/build
  mkdir target/obj/parser
fi