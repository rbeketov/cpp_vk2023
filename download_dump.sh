#!/usr/bin/env bash

set -e

mkdir data
cd data

wget https://datasets.imdbws.com/title.basics.tsv.gz
wget https://datasets.imdbws.com/title.akas.tsv.gz
wget https://datasets.imdbws.com/title.ratings.tsv.gz

gunzip title.basics.tsv.gz
gunzip title.akas.tsv.gz
gunzip title.ratings.tsv.gz