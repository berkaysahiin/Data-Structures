#include <stdint.h>

typedef struct {
  uint32_t state;
}random_number_generator;

/* --------------PUBLIC-------------------*/
uint32_t get_next(random_number_generator* rng);
uint32_t get_next_range(random_number_generator* rng, int upper_bound);
uint32_t get_prev(random_number_generator* rng);
uint32_t get_prev_range(random_number_generator* rng, int upper_bound);
uint32_t xor_shift(uint32_t value);
uint32_t revert(uint32_t value);

/* --------------PRIVATE-------------------*/
uint32_t revert_4_bits_left_shift(uint32_t xorshiftedValue);
uint32_t revert_17_bits_right_shift(uint32_t xorshiftedValue);
uint32_t revert_13_bits_left_shift(uint32_t xorshiftedValue);
void set_bit(uint32_t* target, int val, int index);
int get_bit(uint32_t target, int index) ;
int xor(int b1, int b2);

/*------------------------------------------------------------------------------------*/

random_number_generator rng_init(uint32_t seed)
{
  random_number_generator rng = {
    .state = seed
  };

  return rng;
}

uint32_t get_next(random_number_generator* rng)
{
  rng->state = xor_shift(rng->state);
  return rng->state;
}

uint32_t get_next_range(random_number_generator* rng, int upper_bound)
{
  return get_next(rng) % upper_bound;
}

uint32_t get_prev(random_number_generator* rng)
{
  rng->state = revert(rng->state);
  return rng->state;
}

uint32_t get_prev_range(random_number_generator* rng, int upper_bound)
{
  return get_prev(rng) % upper_bound;
}

uint32_t xor_shift(uint32_t value) 
{
  value ^= value << 13;
  value ^= value >> 17;
  value ^= value << 4;

  return value;
}

uint32_t revert(uint32_t value)
{
  return revert_13_bits_left_shift(revert_17_bits_right_shift(revert_4_bits_left_shift(value))); 
}

//----------------------------------BITWISE.OPERATIONS-------------------------------------------------------------------------------

void set_bit(uint32_t* target, int val, int index)
{
  if(val == 1) {
    *target |= 1U << index;
  }
  else {
    *target &= ~(1U << index);
  }
}

int get_bit(uint32_t target, int index) 
{
  return (target & (1 << index)) != 0;
}

int xor(int b1, int b2) {
    return !(b1 == b2);
}

uint32_t revert_4_bits_left_shift(uint32_t xorshiftedValue) 
{
  uint32_t revertedValue = 0;
  for(int i=0; i<4; i++) {
    set_bit(&revertedValue,get_bit(xorshiftedValue,i),i);
  }
  
  for(int i=4; i<32; i++) {
    set_bit(&revertedValue, xor(get_bit(revertedValue, i-4), get_bit(xorshiftedValue, i)), i);
  }
    
  return revertedValue;
}

uint32_t revert_17_bits_right_shift(uint32_t xorshiftedValue) 
{
  uint32_t revertedValue = 0;

  for(int i=15; i<32; i++) {
    set_bit(&revertedValue,get_bit(xorshiftedValue,i), i);
  }

  for(int i=0; i<15; i++) {
    set_bit(&revertedValue, xor(get_bit(revertedValue, i+17), get_bit(xorshiftedValue, i)), i);
  }
  
  return revertedValue;
}

uint32_t revert_13_bits_left_shift(uint32_t xorshiftedValue) 
{
  uint32_t revertedValue = 0;

  for(int i=0; i<13; i++) {
    set_bit(&revertedValue, get_bit(xorshiftedValue,i), i);
  }

  for(int i=13; i<32; i++) {
    set_bit(&revertedValue, xor(get_bit(revertedValue, i - 13), get_bit(xorshiftedValue, i)), i);
  }
  
  return revertedValue;
}

