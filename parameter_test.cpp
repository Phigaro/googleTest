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

// 9_파라미터화테스트2.cpp

bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0) {
			return false;
		}
	}

	// return true;
	return false;
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
};

// 2. DataSet 정의
// INSTANTIATE_TEST_CASE_P(심볼이름, TestSuiteName, DataSet); - 1.10 이전
// INSTANTIATE_TEST_SUITE_P(심볼이름, TestSuiteName, DatSet); - 1.10 이후

INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, 
	testing::Values(2, 3, 5, 7, 11, 13, 17, 19, 23));

// 3. TestCase 생성
//  TEST / TEST_F
//  TEST_P를 통해 테스트 케이스를 작성해야 합니다.
TEST_P(PrimeTest, IsPrime) {
	EXPECT_TRUE(IsPrime(GetParam()));
}
