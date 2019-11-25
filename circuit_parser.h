#include "gc_data_types.h"

int allocate_circuit_from_file(const char* filename, CircuitInfo* circuit);

void print_circuit_info(CircuitInfo* circuit_info, int should_print_evaluation);
//unsigned char* evaluate_plain_circuit(GateInfo* circuit, unsigned long gate_count, unsigned char* input_p1, unsigned long p1_bitlen, unsigned char* input_p2, unsigned long p2_bitlen);

void free_circuit(CircuitInfo* circuit_info);