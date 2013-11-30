#include "random.h"

namespace random {

static uint32_t state = 0;

const uint32_t a = 1103515245;
const uint32_t c = 12345;


uint32_t init(uint32_t seed) {
	const uint32_t prev = state;

	state = seed;

	return prev;
}

uint32_t next() {
	state = a * state + c;

	return state;
}


}
