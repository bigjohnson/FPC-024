#!/bin/bash
for PROGRAM in 8255/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_1A/*.c
do
	echo ${PROGRAM/.c/}
	gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_1B/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_1C/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_2A/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_2B/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
for PROGRAM in 8255_2C/*.c
do
        echo ${PROGRAM/.c/}
        gcc ${PROGRAM} -o ${PROGRAM/.c/}
done
cd devport
./devport.sh
cd ..
