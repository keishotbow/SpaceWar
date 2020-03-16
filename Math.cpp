#include "Math.h"

bool Math::NearZero(float val, float epsilon) {
	return abs(val) <= epsilon;
}
