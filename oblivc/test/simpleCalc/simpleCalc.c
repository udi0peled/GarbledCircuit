#include<stdio.h>
#include<obliv.h>
#include<stdlib.h>
#include<time.h>
#include <common.h>

#include "simpleCalc.h"

void ocTestUtilTcpOrDie(struct ProtocolDesc* pd,const char* remote_host,
                        const char* port);
double wallClock();

int main(int argc,char *argv[])
{
  ProtocolDesc pd;
  protocolIO io;
 
  if(argc<4)
  {
    if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Party missing\n");
    else fprintf(stderr,"message share (in hex) missing\n");
    fprintf(stderr,"Usage: %s <port> <--|localhost> <int value>\n",argv[0]);

    return 1;
  }

  const char* remote_host = strcmp(argv[2],"--")==0 ? NULL : argv[2];
  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

  int party = (!remote_host?1:2);
  setCurrentParty(&pd,party);
  
  //byte value;
  unsigned int temp = 4*N;
  readHexBytes(io.value, &temp, argv[3] , strlen(argv[3]));

  print_array("value = ", io.value, N, " ", "\n");

  // execYaoProtocol_noHalf(&pd, calc_and ,&io);
  // cleanupProtocol(&pd);

  execDebugProtocol(&pd, calc_add_int ,&io);
  
  print_array("result = ", io.result, N, " ", "\n");
  
  return 0;
}

void ocTestUtilTcpOrDie(ProtocolDesc* pd,const char* remote_host,
                        const char* port)
{
  if(!remote_host)
  { if(protocolAcceptTcp2P(pd,port)!=0)
    { fprintf(stderr,"TCP accept failed\n");
      exit(1);
    }
  }
  else 
    if(protocolConnectTcp2P(pd,remote_host,port)!=0) 
    { fprintf(stderr,"TCP connect failed\n");
      exit(1);
    }
}
