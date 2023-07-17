#!/bin/bash

for i in $(eval echo "{1..$1}")
do
	./main $2
done
