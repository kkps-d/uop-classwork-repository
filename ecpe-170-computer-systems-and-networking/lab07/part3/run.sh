#!/bin/bash
sizes=(256 512 768 1024 1280 1536 1792 2048)
echo alg,size,flops > log.csv
for i in {1..2}
do
    for j in {0..7}
    do
        echo Running algorithm $i with array size ${sizes[$j]}
        flops=$(./matrix_math $i ${sizes[$j]} | grep "Floating-point ops/sec:" | cut -c25-32)
        echo Flops: $flops
        echo $i,${sizes[$j]},$flops >> log.csv
    done
done
echo log.csv created containing the flops.