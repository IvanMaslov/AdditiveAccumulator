#include "utils.h"

size_t pred(const size_t &k) {
	return k & (k - 1);
}

size_t zeros(size_t k) {
	if (k == 0)
		return 0;
	size_t res = 0;
	while (k % 2 == 0) {
		res++;
		k /= 2;
	}
	return res;
}

size_t rpred(const size_t &i, const size_t &j) {
	size_t res = i;
	while (true) {
		size_t prev = res;
		res = pred(res);
		if (res < j)
			return prev;
	}
	return 0;
}

size_t bit_lift(const size_t &i, const size_t &u) {
	if (i == 0)
		return 0;
	if (i % (1 << u) != 0)
		return bit_lift((i >> u) << u, u);
	if (i % (1 << (u + 1)) != 0)
		return i;
	return ((i >> u) - 1) << u;
}
