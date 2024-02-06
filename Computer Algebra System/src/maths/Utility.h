#ifndef UTILITY_H
#define UTILITY_H

float randomFloat() {
	return (float)(rand() / (RAND_MAX + 1.0));
}

float randomFloat(float min, float max) {
	return min + (max - min) * randomFloat();
}
#endif