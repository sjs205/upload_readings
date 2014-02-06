#!/bin/bash
SENSORS='3 ' #DEVICEID
COUNT=0;
fowsr  -c > /tmp/fowsr.log 
cat /tmp/fowsr.log 

exec 0</tmp/fowsr.log;
while read LINE 
do 
#DTime 06-02-2014 02:20:00
#RHi 29.0
#Ti 21.7
#RHo 60.0
#To 8.3
#RP 1010.4
#WS 3.1
#WG 5.8
#DIR 225.0
#Rtot 389.2
#state 00

TITLE=`echo $LINE | awk '{print $1}'`
VALUE=`echo $LINE | awk '{print $2" "$3}'`
if [ "$TITLE" = "DTime" ]
then
  DATE=`echo $VALUE | awk 'BEGIN {OFS="-"} {print substr($1,7,4), substr($1,4,2), substr($1,1,2)}'`
  DATE="$DATE `echo $LINE | awk '{print $3}'`"
  echo  "DATE = " $DATE;
elif [ "$TITLE" = "RHi" ]
then
  RHI=$VALUE;
  echo  "RHi = " $RHI;
  ARGS="$ARGS '12' '$RHI'";
elif [ "$TITLE" = "RHi" ]
then
  TI=$VALUE;
  echo  "Ti = " $TI;
  ARGS="$ARGS '11' '$TI'";
elif [ "$TITLE" = "Ti" ]
then
  RHO=$VALUE;
  echo  "RHo = " $RHO;
  ARGS="$ARGS '17' '$RHO'";
elif [ "$TITLE" = "To" ]
then
  TO=$VALUE;
  echo  "To = " $TO;
  ARGS="$ARGS '10' '$TO'";
elif [ "$TITLE" = "RP" ]
then
  RP=$VALUE;
  echo  "RP = " $RP
  ARGS="$ARGS '13' '$RP'";
elif [ "$TITLE" = "WS" ]
then
  WS=$VALUE;
  echo  "WS = " $WS
  ARGS="$ARGS '14' '$WS'";
elif [ "$TITLE" = "WG" ]
then
  WG=$VALUE;
  echo  "WG = " $WG
  ARGS="$ARGS '19' '$WG'";
elif [ "$TITLE" = "DIR" ]
then
  DIR=$VALUE;
  echo  "DIR = " $DIR
  ARGS="$ARGS '15' '$DIR'";
elif [ "$TITLE" = "Rtot" ]
then
  RTOT=$VALUE;
  ARGS="$ARGS '16' '$RTOT'";
elif [ "$TITLE" = "state" ]
then
  STATE=$VALUE;
  ARGS="$ARGS '18' '$STATE'";
fi

COUNT=$[COUNT+1];
done

CMD="/media/devel/sensor_upload/upload_reading 3  \"$DATE\" $ARGS";
echo $CMD
eval $CMD

exit
