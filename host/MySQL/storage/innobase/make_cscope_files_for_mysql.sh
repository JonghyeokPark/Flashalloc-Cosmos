#!/bin/bash

echo "Delete cscope and tags file"
rm -rf cscope.files cscope.out
rm -rf tags

echo "Make cscope.files"
find -name *.i >> cscope.files
find -name *.ic >> cscope.files
find -name *.cc | grep -v "yacc" >> cscope.files
find -name *.c >> cscope.files
find -name *.cpp >> cscope.files
find -name *.h >> cscope.files

echo "Make ctags"
ctags --langmap=c++:+.ic.i --languages=c,c++ -R *

echo "Clean-up and make cscope and tags done "
