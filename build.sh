#!/bin/sh

set -xe

cc -Wall -Werror -std=c11 -pedantic -ggdb -o main main.c
./main > main.dot
dot -Tsvg main.dot > main.svg

