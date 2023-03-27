#!/usr/bin/env bash

set -e

cd build/project

./pars --basicsDump=../../data/title.basics.tsv --ratingsDump=../../data/title.ratings.tsv --akasDump=../../data/title.akas.tsv --numMin=60