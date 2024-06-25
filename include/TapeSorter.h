#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Setup.h"
#include "Tape.h"

class TapeSorter
{
public:
	TapeSorter(std::shared_ptr<Tape>& in, std::shared_ptr<Tape>& out);
	~TapeSorter();
	void sortTapes();

private:
	uint32_t tempCounter{0};

	std::array<int32_t, ramLimit> ram;
	std::vector<std::shared_ptr<Tape>> tempTapes;
	std::shared_ptr<Tape> inTape;
	std::shared_ptr<Tape> outTape;

	void makeTempTape(const uint32_t size);
};