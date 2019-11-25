#include <stdio.h>
#include <stdlib.h>

#include "circuit_parser.h"
#include "gc_data_types.h"

int allocate_circuit_from_file(const char* filename, CircuitInfo* circuit_info) {
  
  FILE *infile; 
      
  // open file for writing 
  infile = fopen (filename, "rb"); 
  if (infile == NULL) 
  { 
      fprintf(stderr, "\nError opening file '%s'", filename); 
      return 1;
  }

  fread(circuit_info, sizeof(CircuitInfo), 1, infile);
  
  circuit_info->circuit = malloc(sizeof(GateInfo) * circuit_info->gate_count);
  fread(circuit_info->circuit, sizeof(GateInfo), circuit_info->gate_count, infile);

  for (int pl = 0; pl < 3; ++pl) {

    circuit_info->inputs[pl] = malloc(sizeof(gate_index) * circuit_info->num_inputs[pl]);
    fread(circuit_info->inputs[pl], sizeof(gate_index), circuit_info->num_inputs[pl], infile);

    circuit_info->outputs[pl] = malloc(sizeof(gate_index) * circuit_info->num_outputs[pl]);
    fread(circuit_info->outputs[pl], sizeof(gate_index), circuit_info->num_outputs[pl], infile);
  }

  fclose (infile); 
  
  return 0;
}

void print_circuit_info(CircuitInfo* circuit_info, int should_print_evaluation) {
  for (gate_index i=0; i < circuit_info->gate_count; ++i) {
    
    GateInfo* gate = &circuit_info->circuit[i];
    fprintf(stderr, "%-10lu%-10lu%-10lu%-4x", i, gate->input1, gate->input2, gate->ttable & 0x0f);
    
    if (should_print_evaluation) {
      fprintf(stderr, "%-4x", (gate->ttable & 0x10) >> 4);
    }

    fprintf(stderr, "\n");
  }

  fprintf(stderr, "public/p1/p2 inputs:\n");
  for (int player = 0; player < 3; ++player) {
    
    for (gate_index i = 0; i < circuit_info->num_inputs[player]; ++i) {
      fprintf(stderr, "%-6lu ", circuit_info->inputs[player][i]);
    }

    fprintf(stderr, "\n");

    if (should_print_evaluation) {

      for (gate_index i = 0; i < circuit_info->num_inputs[player]; ++i) {
        fprintf(stderr, "%-6x ", (circuit_info->circuit[circuit_info->inputs[player][i]].ttable & 0x10) >> 4);
      }

      fprintf(stderr,"\n");
    }
  }

  fprintf(stderr, "public/p1/p2 outputs:\n");
  for (int player = 0; player < 3; ++player) {
    
    for (gate_index i = 0; i < circuit_info->num_outputs[player]; ++i) {
      fprintf(stderr, "%-6lu ", circuit_info->outputs[player][i]);
    }

    fprintf(stderr,"\n");

    if (should_print_evaluation) {

      for (gate_index i = 0; i < circuit_info->num_outputs[player]; ++i) {
        fprintf(stderr, "%-6x ", (circuit_info->circuit[circuit_info->outputs[player][i]].ttable & 0x10) >> 4);
      }

      fprintf(stderr, "\n");
    }

  }
}

void free_circuit(CircuitInfo* circuit_info) {
  for (int pl = 0; pl < 3; ++pl) {

    free(circuit_info->inputs[pl]);
    free(circuit_info->outputs[pl]);
  }
  free(circuit_info->circuit);
}