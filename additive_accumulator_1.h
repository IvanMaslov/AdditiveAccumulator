#ifndef ADDITIVE_ACCUMULATOR_1
#define ADDITIVE_ACCUMULATOR_1

#include "sha256.h"
#include <vector>

struct statement {
	std::string x;
	std::string prev;
	std::string parent;

	statement();

	statement(const std::string &x, const std::string &prev, const std::string &parent);
};

using witness = std::vector<statement>;

class additive_accumulator {
	size_t size;
	std::vector<std::string> x;
	std::vector<std::string> r;
	std::vector<std::string> s;

	size_t pred(const size_t &k);

	size_t zeros(size_t k);

	witness wit_create(const size_t &j, const size_t &i);

	bool wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w);

public:

	additive_accumulator();

	void add(const std::string &z);

	witness create_witness(const size_t &num, const size_t &i);

	witness create_witness(const size_t &num);

	bool verify_witness(const std::string &z, const size_t &num, const size_t &i, witness w);
};

#endif