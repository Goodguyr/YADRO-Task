#include "TapeSorter.h"

#include <queue>

#include "Setup.h"

struct TapeHolder
{
	TapeHolder(int32_t value, uint32_t id) : value(value), tapeId(id) {}
	int32_t value;
	uint32_t tapeId;

	// bool operator>(const TapeHolder& other) const { return value > other.value; }
};

struct compareTape
{
	bool operator()(const TapeHolder& lhs, const TapeHolder& rhs) const { return lhs.value > rhs.value; }
};

TapeSorter::TapeSorter(std::shared_ptr<Tape>& in, std::shared_ptr<Tape>& out) : inTape(in), outTape(out)
{
	try
	{
		uint32_t elemCount{0};

		while (!in->finished())
		{
			if (elemCount != ramLimit)
			{
				ram[elemCount++] = in->read();
				in->shiftForward();
			}
			else
			{
				// Might throw here
				makeTempTape(ramLimit);
				elemCount = 0;
			}
		}
		if (elemCount)
		{
			makeTempTape(elemCount);
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(e.what());
	}
}

void TapeSorter::sortTapes()
{
	std::priority_queue<TapeHolder, std::vector<TapeHolder>, compareTape> minHeap;
	size_t tapeLimit = tempTapes.size() < ramLimit ? tempTapes.size() : ramLimit;

	uint32_t outSize = 0;

	for (size_t i = 0; i < tapeLimit; ++i)
	{
		if (!tempTapes[i]->finished())
		{
			outSize += tempTapes[i]->getSize();
			minHeap.push(TapeHolder(tempTapes[i]->read(), i));
			tempTapes[i]->shiftForward();
		}
	}

	auto mergeTape = std::make_shared<Tape>("TempTape_" + std::to_string(tempCounter++), outSize);

	while (!minHeap.empty())
	{
		TapeHolder smallest = minHeap.top();
		minHeap.pop();

		mergeTape->write(smallest.value);
		mergeTape->shiftForward();

		if (!tempTapes[smallest.tapeId]->finished())
		{
			minHeap.push(TapeHolder(tempTapes[smallest.tapeId]->read(), smallest.tapeId));
			tempTapes[smallest.tapeId]->shiftForward();
		}
	}
}

void TapeSorter::makeTempTape(const uint32_t size)
{
	std::sort(ram.begin(), ram.end());
	auto tempTape = std::make_shared<Tape>("TempTape_" + std::to_string(tempCounter++), size);
	auto it = ram.begin();

	while (!tempTape->finished() && it != ram.end())
	{
		tempTape->write(*it);
		tempTape->shiftForward();
		++it;
	}

	tempTapes.push_back(tempTape);
}
