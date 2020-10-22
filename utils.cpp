#include "utils.h"

size_t pred(const size_t &k) {
	return k & (k - 1);
}

size_t zeros(size_t k) {
	size_t res = 0;
	while (k > 0) {
		res++;
		k &= (k - 1);
	}
	return res;
}

size_t rpred(const size_t &i, const size_t &j) {
	size_t res = i;
	while (res >= j) {
		res = pred(res);
	}
	return res;
}

size_t bit_lift(const size_t &i, const size_t &u) {
	if (i % (1 << u) != 0)
		return (i >> u) << u;
	if (i % (1 << (u + 1)) != 0)
		return i;
	return ((i >> u) - 1) << u;
}
