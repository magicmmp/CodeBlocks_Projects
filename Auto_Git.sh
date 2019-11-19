#!/bin/sh

git add *

date_time=$(date)

git commit -m "auto git push  CodeBlocks Project: ${date_time}"

git push origin master

