#ifndef ADDITIVE_ACCUMULATOR_1
#define ADDITIVE_ACCUMULATOR_1

#include "sha256.h"
#include "utils.h"
#include <vector>

struct statement_1 {
	std::string x;
	std::string prev;
	std::string parent;

	statement_1();

	statement_1(const std::string &x, const std::string &prev, const std::string &parent);
};

class additive_accumulator_1 {
public:
	using witness = std::vector<statement_1>;

private:
	size_t size;
	std::vector<std::string> x;
	std::vector<std::string> r;
	std::vector<std::string> s;

	witness wit_create(const size_t &j, const size_t &i);

	bool wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w);

public:

	additive_accumulator_1();

	void add(const std::string &z);

	witness create_witness(const size_t &num, const size_t &i);

	witness create_witness(const size_t &num);

	bool verify_witness(const std::string &z, const size_t &num, const size_t &i, witness w);
};

#endif