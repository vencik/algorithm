#!/bin/sh
# UT for cli/string/levenshtein

set -e

SOURCE_DIR="$1"
BUILD_DIR="$2"

. ${SOURCE_DIR}/unit_test/functions.sh


match "${BUILD_DIR}/cli/string/levenshtein dist" "\
sitting
kitten
Sunday
Saturday" \
"\
3
3"
