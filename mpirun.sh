#!/bin/bash
#SBATCH -A SNIC2023-056
#SBATCH -N 1
#SBATCH -n 2
#SBATCH -c 1
#SBATCH --time=0-00:05:00
#SBATCH -error=job.%J.err
#SBATCH -output=job.%J.out


ml foss
srun ./nqueen