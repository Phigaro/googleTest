#include <gtest/gtest.h>
#include <string>

// 1. 단언문
// ASSERT_XX : EQ, TRUE, / FALSE, LT, GT, LE, GE ..
// 	-> 하나의 단언문이 실패하면 이후의 코드는 수행되지 않음
// 	-> "죽은 단언문"
// 		: 하나의 테스트케이스 안에 최소한의 단언문을 사용하는것이 좋다.
// 		-> 여러개의 TC를 만들어야한다.

//  => 구글 테스트는 위의 문제를 해결하기 위해 단언 매크로를 제공함
// EXPECT_XX : EQ, TRUE, / FALSE, LT, GT, LE, GE ..
//  -> 단언문이 실패하더라도 이후의 코드가 실행 됨.
//  -> 하나의 단언문이 실패하면 TC의 result는 실패

int foo() { return 0; }
int goo() { return -1; }

TEST(GoogleTest, Sample1){
	int expected = 42;

	int actual1 = foo();
	int actual2 = goo();

	//ASSERT_EQ(actual1, expected);
	//ASSERT_EQ(actual2, expected);
	
	//EXPECT_EQ(actual1, expected);
	EXPECT_EQ(actual2, expected);
}

// 2. 문자열
// C-Style 문자열 : const char*
// C++ 문자열 : std::string

TEST(GoogleTest, Sample2){
	std::string s1 = "hello";
	std::string s2 = "hello";

	const char* s3 = s2.c_str();
	const char* s4 = "hello";

	EXPECT_EQ(s1, s2); // Success
	EXPECT_EQ(s3, s4); // Fail
	EXPECT_STREQ(s3, s4); // Success
	EXPECT_STRCASEEQ(s3, s4); // Success
}

// 3. 부동 소수점
// EXPECt_DOUBLE_EQ
// EXPECt_FLOAT_EQ
//
// EXPECT_NEAR : 오차 범위를 직접 설정하는 것이 가능

TEST(GoogleTest, Sample3){
	double a = 0.7;
	double b = 0.1 * 7;

	//EXPECT_EQ(a, b); // FAIL
	EXPECT_DOUBLE_EQ(a, b);
	EXPECT_FLOAT_EQ(a, b);

	//EXPECT_NEAR(a, b, 0.0000000);
}

// comverage: 테스트 코드를 통해 수행된 제품 코드의 비율을 측정

void IsValidFilename(const std::string& filename){
	if(filename.empty()){
		throw std::invalid_argument("filename is empty!");
	}

	// ...
}

// Error 가 나는 상황 throw를 상정한 case
TEST(GoogleTest, Sample4){
	std::string emptyFilename = "";
	
	try{
		IsValidFilename(emptyFilename);
		FAIL() << "예외가 발생하지 않았습니다.";
	} catch (std::invalid_argument&) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였습니다.";
	}
}

TEST(GoogleTest, Sample5){
	std::string emptyFilename = "";

	EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument) << "빈 문자열을 전달하였을 때";
	EXPECT_ANY_THROW(IsValidFilename(emptyFilename));
}

// TC 비활성화 특정 TC로 인해 계속해서 전체 테스트가 실패. 
// 1) comment 처리시 "잊혀진 Test"가 된다.
// 2) 비활성화 한 TC가 있다는 사실을 알려준다. 
//
// TEST_F(DISABLED_TestSuiteName, DISABLED_TestCaseName)
// => TestSuite 의 이름이 DISABLED_로 되어있거나
// => TestCast의 이름이 DISABLED_로 되어있으면 비활성화 처리됨

TEST(DISABLED_SampleTest, DISABLED_TestA) {
}

TEST(SampleTest, TestB) {
}

// 7. 필터
//   : 잘 정의된 이름 규칙이 필요합니다.
//   $ ./a.out --gtest_filter=*.TestA
//   $ ./a.out --gtest_filter=-*.TestA
//
//   $ ./a.out --gtest_filter=TestSuiteA.*:-*.TestA
TEST(TestSuiteA, TestA) {}
TEST(TestSuiteB, TestA) {}
TEST(TestSuiteC, TestA) {}
TEST(TestSuiteD, TestA) {}

TEST(TestSuiteA, TestB) {}
TEST(TestSuiteB, TestB) {}
TEST(TestSuiteC, TestB) {}

// 8. Test Result Formatter
//   $ ./a.out --gtest_output=[xml|json]:/path/output.xml
//
//   xml: test_details.xml  -> xUnit Test Framework
//  json: test_details.json -> Google Test


// 9. 추가적인 정보도 기록할 수 있습니다.
TEST(GoogleTest, Sample9) {
	RecordProperty("cpu", "1.5");  // !
	RecordProperty("mem", "512m"); // !
}