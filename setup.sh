#!/bin/bash

IP='192.168.56.101'
PORT='4242'
SSHPASS="/sgoinfre/goinfre/Perso/kibotrel/sshpass/sshpass"
LEVELS=9

mkdir -p binaries

if (( $# == 0))
then
  for (( i=0; i<=$LEVELS; i++ ))
  do
    if (( $i == 0 ))
    then
      PASSWORD='level0'
    else
      PASSWORD=$(cat level$(($i - 1))/flag)
    fi
    if (( $i == 9 ))
    then
      FILE='source.cpp'
      COMPILATION=$(cat level$i/Ressources/README.md | grep 'g++' | cut -c5-)
    else
      FILE='source.c'
      COMPILATION=$(cat level$i/Ressources/README.md | grep 'gcc' | cut -c5-)
    fi
    $SSHPASS -p $PASSWORD scp -P$PORT level$i@$IP:level$i binaries/.
    $SSHPASS -p $PASSWORD ssh -p $PORT level$i@$IP 'chmod 777 .'
    $SSHPASS -p $PASSWORD scp -P$PORT level$i/$FILE level$i@$IP:/tmp/.
    $SSHPASS -p $PASSWORD ssh -p $PORT level$i@$IP "cd /tmp ; $COMPILATION ; rm -f $FILE"
  done
else
  if (( $1 == 0 ))
  then
    PASSWORD='level0'
  else
    PASSWORD=$(cat level$(($1 - 1))/flag)
  fi
  if (( $1 == 9 ))
  then
    FILE='source.cpp'
    COMPILATION=$(cat level$1/Ressources/README.md | grep 'g++' | cut -c5-)
  else
    FILE='source.c'
    COMPILATION=$(cat level$1/Ressources/README.md | grep 'gcc' | cut -c5-)
  fi
  $SSHPASS -p $PASSWORD scp -P$PORT level$1@$IP:level$1 binaries/.
  $SSHPASS -p $PASSWORD ssh -p $PORT level$1@$IP 'chmod 777 .'
  $SSHPASS -p $PASSWORD scp -P$PORT level$1/$FILE level$1@$IP:/tmp/.
  $SSHPASS -p $PASSWORD ssh -p $PORT level$1@$IP "cd /tmp ; $COMPILATION ; rm -f $FILE"
fi
