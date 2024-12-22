#!/bin/bash

PROJECT_ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd ) # want to call the script from anywhere

doxygen "$PROJECT_ROOT_DIR/docs/.doxyfile"
