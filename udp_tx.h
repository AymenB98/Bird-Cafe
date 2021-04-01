#ifndef __UDP_TX_H_
#define __UDP_TX_H_

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

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/types.h>

/** @brief Transmit a UDP packet to a client (web page) that
 *         contains the number of birds that have visited the
 *         feeder in a day.
 */
class UDPTransmit
{
    struct sockaddr_in serverAddress;
    int newSocket, portNumber;
    public:

        /** @brief Constructor which creates a socket and sets up the address
         *        parameters
         * 
         *  @return none
         */
        UDPTransmit()
        {
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
        }

        /** @brief Create socket and send bird count to web page
         *   
         *  @param birdCount     How many birds have visited today
         *     
         *  @return none
         */
        void sendPacket(uint8_t birdCount)
        {  
            // Copy bird count into char so it can be sent to webpage 
            char message[1];
            sprintf(message, "%d", birdCount);
            // Transmit UDP packet
            sendto(newSocket, message, (strlen(message) + 1), 0,
            (const struct sockaddr *) &serverAddress, sizeof(serverAddress));

        }

        /** @brief Clear port so that it can be used again after run
         *
         *  @return none
         */
        void killProcess()
        {
            struct sigaction act;
            memset(&act, 0, sizeof(act));
            
            if(sigaction (SIGHUP, &act, NULL) < 0) 
            {
                exit(-1);
            }
        }

        /** @brief Destructor which cleans up processes, allows 
         *        port to be used again after this code is run
         * 
         *  @return none
         */
        ~UDPTransmit()
        {
            // Close the socket
            close(newSocket);
            // Allow the port to be used after this code has been run
            killProcess();
        }
};

#endif