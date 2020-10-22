#ifndef ADDITIVE_ACCUMULATOR_2
#define ADDITIVE_ACCUMULATOR_2

#include "sha256.h"
#include "utils.h"
#include "merkle_tree.h"

struct statement_2 {
	std::string x;
	std::string rh;
	merkle_tree::witness w;

	statement_2();

	statement_2(const std::string &x, const std::string &rh);
};

class additive_accumulator_2 {
public:
	using witness = std::vector<statement_2>;

private:

	size_t size;
	std::vector<std::string> x;
	std::vector<std::string> r;
	merkle_tree s;

	bool wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w);

public:

	additive_accumulator_2();
	
	void add(const std::string &z);

	witness create_witness(const size_t &j, const size_t &i);

	bool verify_witness(const std::string &z, const size_t &j, const size_t &i, witness w);
};

#endif