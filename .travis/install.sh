#!/usr/bin/env bash
################################################################################
# Travis-CI : install
# -------------------
#
# Installs the required tools for the CI build
################################################################################

set -e

# Nothing to install when we do a doxygen build
if ! test -z "${DOXYGEN_AGENT}"; then
  exit 0
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  python3 -m pip install --user conan
  python3 -m pip install --user --upgrade "urllib3==1.22"
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew install python3 ninja cmake
  # Apparently some Travis nodes don't link python3 for some brilliant reason.
  brew link --overwrite python3
  python3 -m pip install conan
  python3 -m pip install --upgrade "urllib3==1.22"
else
  echo >&2 "Unknown TRAVIS_OS_NAME: '${TRAVIS_OS_NAME}'"
  exit 1
fi