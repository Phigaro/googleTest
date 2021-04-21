// : TEST(TestSuite Name, TestCase Name)

#if 0
#include <gtest/gtest.h>

TEST(SampleTest, Sample1){
	SUCCEED();
}

TEST(SampleTest, Sample2){
	FAIL();
}
#endif
// -----------------------------
// "단위 테스트를 구성하는 방법" 


// SUT(System Under Test)
#include <gtest/gtest.h>

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}
private:
};

// ----------------------------
// calculator.h / calculator.cpp
// tests/calculator.spec.cpp (example)
//       calculator.test.cpp

// First of all, define TestSuite Name
// : 테스트 대상 클래스의 마지막에 Test / Spec 이름을 Add.
// => CalcluatorTest / CalculatorSpec

TEST(CalculatorTest, Plus){
	// Arrange
	Calculator* calc = new Calculator();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
    if (calc->Display() != 4){
    	FAIL();
	}else{
	    SUCCEED();
	}
}

// 3A : TC를 구성하는 방법
// 1. Arrange : 객체를 생성하고 ,필요한 경우 설정하고 준비한다.
// 2. Act
// 3. Assert
