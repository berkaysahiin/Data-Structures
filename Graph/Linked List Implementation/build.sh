#!/bin/bash

echo "Opening dot file"

gcc -o src/out/graph src/graph.c src/test.c && ./src/out/graph && dot src/dotfiles/vis.dot -Tpdf > src/dotfiles/vis.pdf && xdg-open src/dotfiles/vis.pdf

