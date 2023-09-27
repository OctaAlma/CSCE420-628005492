#!/bin/zsh

echo "I am gonna run the files on all heuristics"

minHeuristic=6
maxHeuristic=6

for H in {$minHeuristic..$maxHeuristic}; 
do
    touch ./Outputs/timingDataH$H.txt
    echo "" > ./Outputs/timingDataH$H.txt
    echo "\n-------------------------- USING PROB A FILES --------------------------n" >> ./Outputs/timingDataH$H.txt    
    for i in {3..9}
    do
        {time ./blocksworld probA0$i.bwp -H$H dp >> ./Outputs/timingDataH$H.txt ; } 2>> ./Outputs/timingDataH$H.txt
        echo "\n\n" >> ./Outputs/timingDataH$H.txt
    done

    for i in {10..11}
    do
        {time ./blocksworld probA$i.bwp -H$H dp >> ./Outputs/timingDataH$H.txt ; } 2>> ./Outputs/timingDataH$H.txt
        echo "\n\n" >> ./Outputs/timingDataH$H.txt
    done

    echo "\n-------------------------- USING PROB B FILES --------------------------n" >> ./Outputs/timingDataH$H.txt
    for i in {3..9}
    do
        {time ./blocksworld probB0$i.bwp -H$H dp >> ./Outputs/timingDataH$H.txt ; } 2>> ./Outputs/timingDataH$H.txt
        echo "\n\n" >> ./Outputs/timingDataH$H.txt
    done

    for i in {10..20}
    do
        {time ./blocksworld probB$i.bwp -H$H dp >> ./Outputs/timingDataH$H.txt ; } 2>> ./Outputs/timingDataH$H.txt
        echo "\n\n" >> ./Outputs/timingDataH$H.txt
    done

done