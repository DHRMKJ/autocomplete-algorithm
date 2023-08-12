#!/bin/sh

set -xe

cc -Wall -Werror -std=c11 -pedantic -ggdb -o output/main main.c
./output/main > output/main.dot
dot -Tsvg output/main.dot > output/main.svg

