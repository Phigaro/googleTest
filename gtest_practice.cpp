// : TEST(TestSuite Name, TestCase Name)
#define SPEC printf

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
	//Calculator() {}

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

// TDD vs BDD

// 테스트 코드 품질
// 1. 가독성
//   : 테스트 이름 / 테스트 실패 메세지
// 2. 유지보수성
//   : 테스트 케이스 안에서 제어 구문 ( 조건문, 반복문, 예외 처리 등)의 발생을 최소화 해야한다.
// 3. 신뢰성

// 테스트의 이름이 어떤 테스트를 수행하는지 드러날 수 있도록 (가독)
// convention ) TestTargetMethod_Scenraio_ExpectValue

// Test Fixture
// 정의 : xUnit Test Pattern에서는 SUT를 실행하기 위해 준비해야 하는 모든 작업을
//        Test Fixture라고 함
//        Fixture를 구성하는 모든 logic 부분을 "픽스쳐를 설치한다" 라고함

// Intall Fixture
// 1. Inline Fixture Setup
// : 모든 픽스쳐 설치를 테스트 케이스 안에서 수행한다.
// 장점 : 인과관계를 구분하기 쉽다.
// 단점 : 모든 테스트 코드 안에서 "테스트 코드 중복"이 발생함

// 2. Delegate Setup (위임 설치)
// : 테스트 케이스안에서 발생하는 픽스쳐 설치에 대한 코드를 별도의 테스트 유티리티 함수를 통해 모듈화 한다.

// 3. Implicit Setup (암묵적 설치)
// : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp() 함수에서 생성한다
// => xUnit Test Framework 기능


// TestCase를 만드는 매크로
// 1) TEST : 암묵적인 테스트 스위트를 사용합니다.

// 적용 방법.
// 1. 테스트 스위트 클래스를 만듭니다.
class CalculatorTest : public testing::Test {
protected:
	Calculator* calc;
	CalculatorTest() : calc(nullptr) {}

    // virtaul void SetUp() {
	void SetUp() override{
		printf("SetUp()\n");
		calc = new Calculator();
	}
	void TearDown() override{
		printf("Teardown\n");
		delete calc;
		calc = nullptr;
	}
public:
	//Calculator* Create() { return new Calculator(); }
	//Calculator* Create() { return new Calculator(0); }
};

// xUnit Test Pattern 에서 테스트 케이스를 구성하는 방법
// => Four Phase Test Pattern
// 1) Test Fixture를 설치하거나 실제 결과를 위해서 필요한 것을 집어넣는 작업 -SetUp()
// 2) SUT와 상호작용을 한다. - TestBody()
// 3) 기대 결과를 단언한다 - TestBody()
// 4) 테스트 픽스쳐를 해체해서 테스트 시작 이전의 상태로 돌려놓는다. => TearDown()

// xUnit Test Framework 테스트 실행 흐름
// Test Runner
// : RUN_ALL_TESTS();
// 

// 2. TEST_F: TSET_F 매크코를 이용해서 테스트 케이스를 만듭니다. (Fixture)
TEST_F(CalculatorTest, PressPlus_2Plus2_Display4) {
    // OR
    SPEC("2 더하기 2는 4가 나오는지 검증한다.\n");
	// Arrange
	//Calculator* calc = new Calculator();
	//Calculator* calc = Create();
	//SetUp();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을때";

	// Assertion이 실패하면 
	printf("Delete Calc\n");
	
#if 0
    if (calc->Display() != 4){
    	FAIL() << "result: " << calc->Display() << " - 2 + 2 하였을 때";
	}else{
	    SUCCEED();
	}
#endif
}

// Test Smells

#if 0
TEST(CalculatorTest, PressPlus_2Plus2_Display4){
    // OR
    SPEC("2 더하기 2는 4가 나오는지 검증한다.\n");
	// Arrange
	Calculator* calc = new Calculator();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEquals();

	// Assert
	ASSERT_EQ(calc->Display(), 4) << "2 + 2 하였을때";
#if 0
    if (calc->Display() != 4){
    	FAIL() << "result: " << calc->Display() << " - 2 + 2 하였을 때";
	}else{
	    SUCCEED();
	}
#endif
}
#endif

// 3A : TC를 구성하는 방법
// 1. Arrange(Given) : 객체를 생성하고 ,필요한 경우 설정하고 준비한다.
// 2. Act(When) : 객체의 작용을 가한다.
// 3. Assert(then) : 기대하는 바를 단언한다.
