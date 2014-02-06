#ifndef READING_H
#define READING_H

#ifndef MAX_MEASURE_PER_READING
#define MAX_MEASURE_PER_READING 24
#endif

struct sensor_measurement {
  int sensorID;
  char measurement[32];
};

struct sensor_reading {
  int readingID;
  int deviceID;
  char date[20];
  int meas_count;
  struct sensor_measurement *measurements[MAX_MEASURE_PER_READING];
};
#endif
