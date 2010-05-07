/*
   derived from code by: Josh Faust 
   under license below.
*/


/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "ros/poll_set.h"
#include "ros/transport/transport_tcp.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using namespace ros;

class ROSPair
{
private:
  TransportTCPPtr transports_[3];

public:

  void init() {
    transports_[0] = TransportTCPPtr(new TransportTCP(NULL, TransportTCP::SYNCHRONOUS));
    transports_[1] = TransportTCPPtr(new TransportTCP(NULL, TransportTCP::SYNCHRONOUS));

    if (!transports_[0]->listen(0, 100, TransportTCP::AcceptCallback())) {
      fprintf(stderr, "death by not listening\n");
      exit(1);
    }

    if (!transports_[1]->connect("localhost", transports_[0]->getServerPort())) {
      fprintf(stderr, "death by not connecting\n");
      exit(1);
    }

    transports_[2] = transports_[0]->accept();
    if (!transports_[2])
    {
      fprintf(stderr, "death by not accepting\n");
      exit(1);
    }
  }

  void fini() {
    for (int i=0; i<3; i++) {
      if (transports_[i]) {
        transports_[i]->close();
      }
    }
  }

  int writeAndReadTest() {
    std::string msg = "test";
    int32_t written = transports_[1]->write((uint8_t*)msg.c_str(), 
					    msg.length());
    if (written!=(int32_t)msg.length()) {
      fprintf(stderr, "death by failing to write the right amount\n");
      return 1;
    }

    uint8_t buf[5];
    memset(buf, 0, sizeof(buf));
    int32_t read = transports_[2]->read(buf, msg.length());
    if (read!=(int32_t)msg.length()) {
      fprintf(stderr, "death by failing to read the right amount\n");
      return 1;
    }
    if (msg!=((const char*)buf)) {
      fprintf(stderr, "death by failing to read what was written\n");
      return 1;
    }

    printf("Read and write via TCP went ok\n");
    return 0;
  }
};


int main(int argc, char** argv) {
  signal(SIGPIPE, SIG_IGN);
  ROSPair pair;

  pair.init();
  int result = pair.writeAndReadTest();
  pair.fini();

  return result;
}
