
// Author: Aymen Benylles
// This code was adapted from the files "udp_transmit.cpp" and "AD7705Comm.h"
// from the following GitHub repo: 
// https://github.com/berndporr/rpi_AD7705_daq
// https://github.com/berndporr/rpi_AD7705_daq/blob/28ecfe9245ccc5fec673dee7df1c9dd178e8c3d1/udp_transmit.cpp
// https://github.com/berndporr/rpi_AD7705_daq/blob/28ecfe9245ccc5fec673dee7df1c9dd178e8c3d1/AD7705Comm.h

/*
 * AD7705 test/demo program for the Raspberry PI
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 * Copyright (c) 2013-2020  Bernd Porr <mail@berndporr.me.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include "UDP.h"
#include "latencyTimers.h"

#define LATENCY_DEBUG

#ifdef LATENCY_DEBUG
float udpDuration;
std::chrono::high_resolution_clock::time_point udpTimerStart;
FILE* udpLog = fopen("udpLog.dat", "at");
#endif

/** @brief Constructor which creates a socket and sets up the address
 *        parameters
 * 
 *  @return none
 */
UDPTransmit::UDPTransmit(int visitCount)
{

#ifdef LATENCY_DEBUG
    udpTimerStart = std::chrono::high_resolution_clock::now();
#endif

    newSocket = socket(PF_INET, SOCK_DGRAM, 0);
    portNumber = 5000;
    // Make sure socket has been created successfully
    if(newSocket == -1)
    {   
    // Throw error if socket creation failed
        const char socketError[] = "Failed to create socket\n";
        fprintf(stderr, socketError);
        throw socketError;
    }

    // Assign values for serverAddress struct
    serverAddress.sin_family = AF_INET;
    // Port number (5000)
    serverAddress.sin_port = htons(portNumber);
    // Send to any address that is listening to this port
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    sendPacket(visitCount);
}


/** @brief Create socket and send bird count to web page
 *   
 *     
 *  @return none
 */
void UDPTransmit::sendPacket(int packet)
{  
    // Copy bird count into char so it can be sent to webpage 
    char message[1];
    sprintf(message, "%d", packet);
    // Transmit UDP packet
    sendto(newSocket, message, (strlen(message) + 1), 0,
    (const struct sockaddr *) &serverAddress, sizeof(serverAddress));
}

/** @brief Clear port so that it can be used again after run
 *
 *  @return none
 */
void UDPTransmit::killProcess()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    
    if(sigaction (SIGHUP, &act, NULL) < 0) 
    {
        printf("Closing process\n");
        exit(-1);
    }
}

/** @brief Destructor which cleans up processes, allows 
 *        port to be used again after this code is run
 * 
 *  @return none
 */
UDPTransmit::~UDPTransmit()
{
    // Close the socket
    close(newSocket);

    // Allow the port to be used after this code has been run
    killProcess();
#ifdef LATENCY_DEBUG
    std::chrono::high_resolution_clock::time_point udpTimerEnd = std::chrono::high_resolution_clock::now();
    udpDuration = std::chrono::duration <float> (udpTimerEnd - udpTimerStart).count();
    fprintf(udpLog, "%f\n", 1000*udpDuration);  
#endif

}