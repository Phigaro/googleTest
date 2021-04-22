// 9_파라미터화테스트.cpp

#if 0

bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) {
			return false;
		}
	}

	return false;
}

#include <gtest/gtest.h>

TEST(PrimeTest, IsPrime2) {
	int data[] = {
		2, 3, 5, 7, 11, 13, 17, 19, 23
	};

	for (int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; ++i) {
		EXPECT_TRUE(IsPrime(data[i]));
	}
}

TEST(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(2));
	EXPECT_TRUE(IsPrime(3));
	EXPECT_TRUE(IsPrime(5));
	EXPECT_TRUE(IsPrime(7));
	EXPECT_TRUE(IsPrime(11));
	EXPECT_TRUE(IsPrime(13));
	EXPECT_TRUE(IsPrime(17));
	EXPECT_TRUE(IsPrime(19));
	EXPECT_TRUE(IsPrime(23));
}

#endif

#if 0
// 9_파라미터화테스트2.cpp

bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) {
			return false;
		}
	}

	return true;
	// return false;
}

#include <gtest/gtest.h>

// Parameterized Test Pattern
//  => xUnit Test Framework이 제공하는 기능입니다.
//  의도: 입력 데이터를 바꿔가며 반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없앨 수 있습니다.


// 1. TestSuite class
//  class PrimeTest : public testing::Test {};
//  testing::TestWithParam<T>
//   T ->Input Type 
class PrimeTest : public testing::TestWithParam<int> {
protected:
	void SetUp() override {
		printf("SetUp()\n");
	}

	void TearDown() override {
		printf("TearDown()\n");
	}

	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
	}

	static void TearDownTestSuite() {
		printf("TearDownTestSuite()\n");
	}
};

// 2. DataSet 정의
// INSTANTIATE_TEST_CASE_P(심볼이름, TestSuiteName, DataSet); - 1.10 이전
// INSTANTIATE_TEST_SUITE_P(심볼이름, TestSuiteName, DatSet); - 1.10 이후

using testing::Values;
using testing::ValuesIn;

int data[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, 
	// Values(2, 3, 5, 7, 11, 13, 17, 19, 23));
	ValuesIn(data));

// 3. TestCase 생성
//    TEST: 암묵적인 TestSuite class
//  TEST_F: 명시적인 TestSuite class - testing::Test
//  TEST_P: 명시적인 TestSuite class - testing::TestWithParam<T> : GetParam()
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}
#endif
// 9_파라미터화테스트3.cpp

#if 0
#include <gtest/gtest.h>

bool Check(int arg1, int arg2) {
	return arg1 > arg2;
}

//-----

struct Input {
	int arg1;
	int arg2;

	bool result;
};

std::ostream& operator<<(std::ostream& os, const Input& input) {
	return os << "Input{arg1=" << input.arg1 << ", arg2=" << input.arg2 << ", result=" << input.result << "}";
}

class SampleTest : public testing::TestWithParam<Input> {
};

using testing::Values;

INSTANTIATE_TEST_SUITE_P(InputValues, SampleTest,
	Values(Input{20, 30, true}, Input{30, 40, true}, Input{40, 50, true}));

TEST_P(SampleTest, Check) {
	Input input = GetParam();
	EXPECT_TRUE(Check(input.arg1, input.arg2));
	EXPECT_EQ(Check(input.arg1, input.arg2), input.result);
}
#endif

// 9_파라미터화테스트4.cpp
#if 0
#include <gtest/gtest.h>

enum Color { BLACK, RED, WHITE };
const char* animals[] = { "Cat", "Dog" };

// "Cat" - BLACK / RED / WHITE
// "Dog" - BLACK / RED / WHITE
class AnimalTest : public testing::TestWithParam<std::tuple<const char*, Color>> {
};

using testing::Values;
using testing::ValuesIn;
using testing::Combine;

INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest, 
	Combine(ValuesIn(animals), Values(BLACK, RED, WHITE)));

TEST_P(AnimalTest, AnimalLooks) {
	std::tuple<const char*, Color> data = GetParam();

	const char* animal = std::get<0>(data);
	Color color = std::get<1>(data);

	printf("%s(%d)\n", animal, color);
}
#endif

// 9_파라미터화테스트5.cpp
#if 0
#include <iostream>
#include <vector>
#include <string>

#include <gtest/gtest.h>

class StringTest : public testing::TestWithParam<std::string> {
};

// Data가 별도의 파일에서 로드가 필요합니다.
//  => ValuesIn

// std::vector<std::string> LoadFromFile() {
// 	std::vector<std::string> result;
// 	result.push_back("hello");
// 	result.push_back("world");
// 	return result;
// }

// $ ./a.out < input.txt
std::vector<std::string> LoadFromFile() {
	std::vector<std::string> v;

	while (!std::cin.eof()) {
		std::string input;
		std::cin >> input;

		v.push_back(input);
	}

	return v;
}

using testing::ValuesIn;
INSTANTIATE_TEST_SUITE_P(StringValues, StringTest, 
	ValuesIn(LoadFromFile()));

TEST_P(StringTest, InputTest) {
	std::string s = GetParam();
	std::cout << s << std::endl;
}
#endif

// 9_파라미터화테스트6.cpp
#include <gtest/gtest.h>

class SampleTest : public testing::TestWithParam<int> {
};

// Values
// ValuesIn
// Combine
// Range
using testing::Range;
// Range(0, 100, step)
//   [0, 100)

INSTANTIATE_TEST_SUITE_P(IntValues, SampleTest, 
	Range(0, 100, 10));

TEST_P(SampleTest, Sample) {
	printf("%d\n", GetParam());
}