#!/bin/bash

export SPHIA_PATH=test-db

rm -rf ./test-db

for i in {1..5}; do
  sphia set \
    --key "key$i" \
    --value "value$i" > /dev/null
done

last=`./sphia-last`

if [ "$last" != "key$i" ]; then
  exit 1
fi
