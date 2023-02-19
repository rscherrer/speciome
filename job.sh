#!/bin/bash
#SBATCH --time=10:00:00
#SBATCH --mem=32Gb
#SBATCH --partition=gelifes
../speciome parameters.txt
