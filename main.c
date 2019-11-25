#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common_printing.h"
#include "circuit_parser.h"

int main(int argc,char* argv[])
{
  if(argc<3)
  {
    printf("Usage: %s <filename> <test_file>\n",argv[0]);
    return 1;
  }

  CircuitInfo circuit_info;
  
  allocate_circuit_from_file(argv[1], &circuit_info);

  print_circuit_info(&circuit_info, 1);

  free_circuit(&circuit_info);
}