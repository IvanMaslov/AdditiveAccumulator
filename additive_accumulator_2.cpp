#include "additive_accumulator_2.h"

statement_2::statement_2() = default;

statement_2::statement_2(const std::string &x, const std::string &rh)
	: x(x), rh(rh)
{}

additive_accumulator_2::additive_accumulator_2() {
	size = 0;
	x = { "" };
	r = { "" };
	s = merkle_tree();
}

bool additive_accumulator_2::wit_verify(const std::string &z, const size_t &j, const size_t &i, witness &w) {
	statement_2 p = w.back();
	w.pop_back();
	if (sha256(p.x + p.rh) != r[i])
		return false;
	if (i == j)
		return z == p.x;

	size_t i_ = rpred(i - 1, j);
	size_t leaf_index = zeros(i_);

	std::vector<std::string> items;
	for (size_t u = 0; (1 << u) <= i; u++) {
		items.push_back(r[bit_lift(i - 1, u)]);
	}

	merkle_tree tree = merkle_tree(items);
	return tree.verify_witness(p.w, leaf_index, items[leaf_index]) && wit_verify(z, j, i_, w);
}

void additive_accumulator_2::add(const std::string &z) {
	x.push_back(z);
	const std::string m = s.get_root();
	size++;
	r.push_back(sha256(z + m));
	s.set(zeros(size), r.back());
}

additive_accumulator_2::witness additive_accumulator_2::create_witness(const size_t &j, const size_t &i) {
	std::vector<std::string> items;
	for (size_t u = 0; (1 << u) <= i; u++) {
		items.push_back(r[bit_lift(i - 1, u)]);
	}
	merkle_tree tree = merkle_tree(items);
	statement_2 p(x[i], tree.get_root());
	if (i > j) {
		size_t i_ = rpred(i - 1, j);
		merkle_tree::witness w = tree.create_witness(zeros(i_));
		p.w = w;
		witness res = create_witness(j, i_);
		res.push_back(p);
		return res;
	}
	else {
		return{ p };
	}
}

bool additive_accumulator_2::verify_witness(const std::string &z, const size_t &j, const size_t &i, additive_accumulator_2::witness w) {
	return wit_verify(z, j, i, w);
}