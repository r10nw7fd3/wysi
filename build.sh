#!/bin/sh

set -ex

cc -Wall -Wextra -std=c99 -O2 -s -o wysi main.c
cc -Wall -Wextra -std=c99 -O2 -s -o bf2wysi bf2wysi.c
