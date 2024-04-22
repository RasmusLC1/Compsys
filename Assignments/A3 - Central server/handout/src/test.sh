#!/bin/bash
rm [option] "zsuccess.txt"
rm [option] "zerrors.txt"
make test

for i in {1..1000}
do
    ./networkingtest ../config.yaml
done