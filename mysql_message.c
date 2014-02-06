#include "mysql_message.h"


MYSQL *init_mysql() {

  MYSQL *mysql_conn = mysql_init(NULL);

  if (mysql_conn == NULL) {
    printf("Error %u: %s\n", mysql_errno(mysql_conn), mysql_error(mysql_conn));
    exit(1);
  }
    if(mysql_real_connect(mysql_conn, 
     MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB,0, NULL, 0) == NULL) {
      printf("Error %u: %s\n", mysql_errno(mysql_conn), mysql_error(mysql_conn));
      exit(1);
    }
  return(mysql_conn);
  
}


int mysql_insert_reading_db(MYSQL *mysql_conn, struct sensor_reading *reading) {

  char mysql_qry[1024];
  int qry_len, readingID, i, err;
  int *result;

  /* insert reading instance. */
  qry_len = sprintf(mysql_qry,
      "INSERT INTO sensors_reading(deviceID,date) VALUES ('%d','%s')",
      reading->deviceID,reading->date);

  if(mysql_real_query(mysql_conn, mysql_qry,qry_len)) {
    printf("Error %u: %s\n", mysql_errno(mysql_conn), mysql_error(mysql_conn));
    err = mysql_errno(mysql_conn);
  }
  /* get reading ID */
  if ((result = (int *)mysql_store_result(mysql_conn)) == 0 &&
          mysql_field_count(mysql_conn) == 0 &&
              mysql_insert_id(mysql_conn) != 0)
  {
        reading->readingID = mysql_insert_id(mysql_conn);
  }


  for(i=0; i<reading->meas_count; i++) {
    /* insert measurement into reading */
    qry_len = sprintf(mysql_qry,
        "INSERT INTO sensors_measurement(readingID,sensorID,measurement) VALUES ('%d','%d','%s')",
        reading->readingID,
        reading->measurements[i]->sensorID,
        reading->measurements[i]->measurement);

    if(mysql_real_query(mysql_conn, mysql_qry,qry_len)) {
      printf("Error %u: %s\n", mysql_errno(mysql_conn), mysql_error(mysql_conn));
      exit(1);
    }
  }
  return(reading->readingID);

}
