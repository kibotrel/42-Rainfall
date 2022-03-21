#!/bin/bash

IP='192.168.56.101'
PORT='4242'
SSHPASS="/sgoinfre/goinfre/Perso/kibotrel/sshpass/sshpass"
LEVELS=7

mkdir -p binaries

for (( i=0; i<=$LEVELS; i++ ))
  do
    if (( $i == 0 ))
    then
      PASSWORD='level0'
    else
      PASSWORD=$(cat level$(($i - 1))/flag)
    fi
    COMPILATION=$(cat level$i/Ressources/README.md | grep 'gcc' | cut -c5-)

    $SSHPASS -p $PASSWORD scp -P$PORT level$i@$IP:level$i binaries/.
    $SSHPASS -p $PASSWORD ssh -p $PORT level$i@$IP 'chmod 777 .'
    $SSHPASS -p $PASSWORD scp -P$PORT level$i/source.c level$i@$IP:/tmp/.
    $SSHPASS -p $PASSWORD ssh -p $PORT level$i@$IP "cd /tmp ; $COMPILATION ; rm -f source.c"
  done