#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "Tape.h"

void createTapeFile(const std::string& fileName, const std::vector<int32_t>& values)
{
	std::ofstream ofs(fileName, std::ios::binary);
	for (int32_t value : values)
	{
		ofs.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
}

TEST(TapeTest, ReadWriteRewind)
{
	const std::string fileName = "testTape.txt";
	createTapeFile(fileName, {1, 2, 3, 4});

	Tape tape(fileName);
	EXPECT_EQ(tape.read(), 1);
	tape.shiftForward();
	EXPECT_EQ(tape.read(), 2);
	tape.shiftForward();
	EXPECT_EQ(tape.read(), 3);
	tape.shiftForward();
	EXPECT_EQ(tape.read(), 4);
	tape.shiftForward();
	EXPECT_TRUE(tape.finished());

	tape.rewind();
	EXPECT_EQ(tape.read(), 1);

	tape.write(5);
	tape.rewind();
	EXPECT_EQ(tape.read(), 5);

	std::remove(fileName.c_str());
}

TEST(TapeTest, ShiftForwardBackward)
{
	const std::string fileName = "testTape2.txt";
	createTapeFile(fileName, {1, 2, 3, 4});

	Tape tape(fileName);
	tape.shiftForward();
	EXPECT_EQ(tape.read(), 2);
	tape.shiftBackward();
	EXPECT_EQ(tape.read(), 1);

	std::remove(fileName.c_str());
}

TEST(TapeTest, GetSize)
{
	const std::string fileName = "testTape3.txt";
	createTapeFile(fileName, {1, 2, 3, 4});

	Tape tape(fileName);
	EXPECT_EQ(tape.getSize(), 4);

	std::remove(fileName.c_str());
}
