#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql_message.h"
#include "reading.h"

void main(int argc, char *argv[]) {
  if(argc < 5) {
    printf( "usage: %s filename [deviceID] '[mysql-date]' [sensorID] [measurement1] <sensorID> <measurement2> \n\n\n", argv[0] );
  } else {

    struct sensor_reading reading;
    strcpy(reading.date,argv[2]);
    reading.deviceID = atoi(argv[1]);
    
    printf("\nReading:\n");
    printf("DeviceID: %d\n", reading.deviceID);
    printf("Date: %s\n", reading.date);
    
    /* process measurements */

   reading.meas_count = (argc - 2)/2;
   printf("No of Measurements: %d\n", reading.meas_count);

    
      
    int i, count;
    for(count=0, i=3; count < reading.meas_count; count++) {
      reading.measurements[count] = (struct sensor_measurement *) 
        malloc(sizeof(struct sensor_measurement));
      if(reading.measurements == NULL)
      {
        printf("ERROR: Out of memory\n");
        exit(1);
      }
      reading.measurements[count]->sensorID = atoi(argv[i++]);
      strcpy(reading.measurements[count]->measurement, argv[i++]);
      printf("%d\tMeasurement SensorID: %d\t\t Measurement: %s\n", 
          count+1, reading.measurements[count]->sensorID, reading.measurements[count]->measurement);
    }

    for(count=0; count < reading.meas_count; count++) {
    }

    /* insert readig into database */
    /* init mysql connection */
    MYSQL *mysql_conn = init_mysql();


    printf("Inserting reading into database\n");
    reading.readingID = mysql_insert_reading_db(mysql_conn, &reading);
    printf("\nCOMPLETE.\nReadingID: %d\n\n", reading.readingID);

    mysql_close(mysql_conn);

    for(count=0; count < reading.meas_count; count++) {
      free(reading.measurements[count]);
    }

  }
}

