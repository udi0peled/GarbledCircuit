
#ifndef GC_DATA_TYPES_H
#define GC_DATA_TYPES_H

#define YAO_KEY_BITS 80
#define YAO_KEY_BYTES ((YAO_KEY_BITS+7)/8)
#if YAO_KEY_BITS!=(YAO_KEY_BYTES*8)
#error "Yao key size needs to be a multiple of 8 bits"
#endif

typedef char yao_key_t[YAO_KEY_BYTES];

typedef unsigned long gate_index;

typedef struct GateInfo {
  gate_index input1;
  gate_index input2;
  unsigned char ttable;
  //yao_key_t key;
} GateInfo;

typedef struct CircuitInfo {
  
  gate_index gate_count;
  gate_index num_not_gates;
  gate_index num_xor_gates;
  gate_index num_or_gates;
  gate_index num_and_gates;

  GateInfo* circuit;

  // Arrays to sizes and indices for: [0]=public, [1]=p1, [2]=p2
  gate_index num_inputs[3];
  gate_index num_outputs[3];
  
  gate_index* inputs[3];
  gate_index* outputs[3];
  
} CircuitInfo;

#endif