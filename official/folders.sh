#!/bin/bash

counter=0
while [[ counter -lt 52 ]]; do
counter=$(($counter + 1))
  mkdir -p ex$counter
  touch ex$counter/.keep
done
