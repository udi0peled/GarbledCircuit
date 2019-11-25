#include<obliv.h>
#include<stdio.h>
#include<time.h>
#include <common.h>

//#include"../common/util.h"
#include"sha256.h"

void ocTestUtilTcpOrDie(ProtocolDesc* pd,const char* remote_host, const char* port);

double lap;

int main(int argc,char* argv[])
{ 
  ProtocolDesc pd;
  protocolIO io;

  if(argc<4)
  {
    if(argc<2) fprintf(stderr,"Port number missing\n");
    else if(argc<3) fprintf(stderr,"Party missing\n");
    else fprintf(stderr,"message share (in hex) missing\n");
    fprintf(stderr,"Usage: %s <port> <--|remote_host> <hex msg>\n",argv[0]);

    return 1;
  }

  const char* remote_host = strcmp(argv[2],"--")==0 ? NULL : argv[2];
  int party = (!remote_host?1:2);

  ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

  unsigned str_input_len = strlen(argv[3]);
  unsigned max_msg_byte_len = (str_input_len+1)/2;
  
  io.input_share = malloc(max_msg_byte_len * sizeof(byte));
  io.input_len = max_msg_byte_len;

  readHexBytes(io.input_share, &io.input_len, argv[3], str_input_len);
  io.input_share = realloc(io.input_share, io.input_len);
  
  setCurrentParty(&pd,party);

  execDebugProtocol(&pd, compute_process_raw, &io);

  fprintf(stderr,"Result: ");
  printHexBytes(io.msg_digest, SHA256_DIGEST_SIZE);

  return 0;
}

void ocTestUtilTcpOrDie(ProtocolDesc* pd,const char* remote_host, const char* port)
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