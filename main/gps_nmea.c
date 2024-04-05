#include "gps_nmea.h"

// Method to check whether GPS packet is valid or not

bool IsPacketValid(const char * ggaPacket)
{
    if(*ggaPacket == '\0')
    {
        printf("Packet received is empty\n\r");
        return false;
    }
    
    char *packetcopy =(char *) ggaPacket;
    //unsigned char checksumPacket;
    
    uint8_t checksum = 0;
    uint8_t checksumPacket = 0;
    sscanf(packetcopy, "%*[^*]*%hhx", &checksumPacket);
    while(*packetcopy != '*')
    {
        if(*packetcopy != '$')
            checksum = checksum ^ *packetcopy;
        //printf("%c\n\r", *packetcopy);
        packetcopy++;
    }
    packetcopy = ggaPacket;
    
    if(checksum == checksumPacket)
    {
        printf("Packet is valid\n\r");
        return true;
    }
    else
    {
        printf("Packet is invalid. Checksum mismatch\n\r");
        return false;
    }
    
}

// Method to parse GPS packet

void parseGGA(const char* ggaPacket, GPSData* gpsData) {

    if (IsPacketValid(ggaPacket) == false)
        return;

    char *ggaPacketCopy = (char *)ggaPacket;
    char* token = strtok((char*)ggaPacketCopy, ",");
    uint8_t tokenindex = 0;
    while (token != NULL)
    {
        token = strtok(NULL, ",");
        tokenindex++;
        switch (tokenindex)
        {
        case 1:
            strncpy(gpsData->utc_time, token, sizeof(gpsData->utc_time)-1);
            break;
        case 2:
            strncpy(gpsData->latitude, token, sizeof(gpsData->latitude)-1);
            break;
        case 4:
            strncpy(gpsData->longitude, token, sizeof(gpsData->longitude)-1);
            break;
        case 9:
            strncpy(gpsData->altitude, token, sizeof(gpsData->altitude)-1);
            break;
        default:
            break;
        }  
    }
    printf("Time is %s\n\r", gpsData->utc_time);
    printf("Latitude is %s\n\r", gpsData->latitude);
    printf("Longitude is %s\n\r", gpsData->longitude);
    printf("Altitude is %s\n\r", gpsData->altitude);
}

void exampleUsage() {
    const char ggaPacket[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E\r\n";
    GPSData gpsData;
    parseGGA(ggaPacket, &gpsData);
}
