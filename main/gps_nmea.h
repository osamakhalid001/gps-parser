#include "stddef.h"
#include "string.h"
#include <stdio.h>
#include <inttypes.h>
#include "stdbool.h"

typedef struct {
    //char *time;
    char utc_time[10];
    char latitude[15];
    char longitude[15];
    char altitude[10];
    // Add more fields as needed
} GPSData;

void exampleUsage();
