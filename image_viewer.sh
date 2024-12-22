#!/bin/bash

# Get the directory of the script
script_dir="$(cd "$(dirname "$0")" && pwd)"

# Change to the script's directory
cd "$script_dir"

/Library/Frameworks/Python.framework/Versions/3.12/bin/python3 image_viewer.py

