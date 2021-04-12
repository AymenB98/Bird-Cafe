#include "UDP.h"
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

void UDP::start(int message)
{
    opCode = message;
    UDPThread = new std::thread(sendPacket, this);
}

void UDP::stop()
{
    running = 0;
        
    if (UDPThread)
    {
        UDPThread->join();
        delete UDPThread;
        UDPThread = NULL;
    }
}

void UDP::sendPacket(UDP* udp)
{
    udp->running = 1;

    while(udp->running)
    {
        struct sockaddr_in serverAddress;
        int newSocket, portNumber;
    
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

        // Copy bird count into char so it can be sent to webpage 
        char message[1];
        sprintf(message, "%d", udp->opCode);
        // Transmit UDP packet
        sendto(newSocket, message, (strlen(message) + 1), 0,
        (const struct sockaddr *) &serverAddress, sizeof(serverAddress));
        close(newSocket);

        struct sigaction act;
        memset(&act, 0, sizeof(act));
        
        if(sigaction (SIGHUP, &act, NULL) < 0) 
        {
            exit(-1);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}