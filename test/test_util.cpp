#include "test_util.h"

namespace TestUtil {
	extern std::random_device rnd_dev = std::random_device();
	extern std::mt19937 rnd(rnd_dev());
}
