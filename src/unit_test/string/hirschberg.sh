#!/bin/sh
# UT for cli/string/hirschberg

set -e

SOURCE_DIR="$1"
BUILD_DIR="$2"

. ${SOURCE_DIR}/unit_test/functions.sh


match "${BUILD_DIR}/cli/string/hirschberg" "\
AGTACGCA
TATGC" \
"\
AGTACGCA
--TATGC-"
