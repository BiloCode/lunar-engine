#!/bin/bash
set -e
xdg-open http://localhost:3000
python3 -m http.server 3000 -d .docs
