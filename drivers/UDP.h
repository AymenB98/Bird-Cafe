#ifndef UDP_H
#define UDP_H

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

#include <thread>
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

class UDP
{
    private:
    std::thread* UDPThread = NULL;
    int running = 0;
    int opCode;
    
    public:
    void start(int message);

    void stop();

    static void sendPacket(UDP* udp);

};

#endif