#/bin/bash -e
valgrind --leak-check=full -v ./lisp
