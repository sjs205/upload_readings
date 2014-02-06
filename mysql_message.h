#ifndef MYSQL_MESSAGE
#define MYSQL_MESSAGE

#include <my_global.h>
#include <mysql.h>

#include "reading.h"

#define MYSQL_DB "drupal_test"
#define MYSQL_HOST "192.168.5.20"
#define MYSQL_USER "swannonl_ccmeter"
#define MYSQL_PASS "JopU1+Vs(E{y"


int mysql_insert_reading_db(MYSQL *mysql_conn, struct sensor_reading *reading);

MYSQL *init_mysql();

#endif
