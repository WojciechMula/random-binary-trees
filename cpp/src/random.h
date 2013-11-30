#ifndef random_h_included__
#define random_h_included__

#include "types.h"

// simple LCG
namespace random {

uint32_t init(uint32_t seed);
uint32_t next();

}

#endif
