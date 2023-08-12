#!/bin/sh

set -xe

cc -Wall -Werror -std=c11 -pedantic -ggdb -o main main.c
./main > output/main.dot
dot -Tsvg output/main.dot > output/main.svg

