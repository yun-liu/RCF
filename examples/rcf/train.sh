#!/bin/bash

set -x

LOG="logs/fcn_`date +%Y-%m-%d_%H-%M-%S`.txt"
exec &> >(tee -a "$LOG")

./solve.py
