size_t rng() {
	static size_t seed = 0;
	if (!seed) {
		seed += (size_t) empty_rel();
		seed = seed * (size_t) empty_set();
	}
	size_t res = 0;
	for (int i = 0; i < 124; ++i) {
		seed = seed * 3;
		seed += 1;
		res ^= seed;
		res >>= 1;
	}
	return res;
}
