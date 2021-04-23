#if 0
// #include <gtest/gtest.h>
#include <gmock/gmock.h>
// : Google Mock은 Google Test에 대한 의존성이 있습니다.

struct Mp3 {
	virtual ~Mp3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;

	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

	virtual std::pair<bool, int> GetPair() const = 0;
	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
};

// Mocking - 테스트 대역
// 1.10
//  - MOCK_METHOD(반환타입, 이름, (인자1, 인자2), (한정자1, 한정자2));

// 한정자
//  - override: virtual 함수(옵션)
//  - const: 필수
//  - noexcept: 필수
//  - stdcall: Windows platform(필수)

// Type aliasing
using BoolIntPair = std::pair<bool, int>;
using IntDoubleMap = std::map<int, double>;

class MockMp3 : public Mp3 {
public:
	MOCK_METHOD(bool, CheckMap, (IntDoubleMap a, bool b), (override));
	MOCK_METHOD(BoolIntPair, GetPair, (), (const, override));
	
	// 템플릿 인자가 두 개 이상인 경우, 괄호가 필요합니다.
	// MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (override));
	// MOCK_METHOD((std::pair<bool, int>), GetPair, (), (const, override));

	// std::string GetName() const override {}
	MOCK_METHOD(std::string, GetName, (), (const, override));

	// void Foo() noexcept override {}
	MOCK_METHOD(void, Foo, (), (noexcept, override));

	// void Play() override {}
	// MOCK_METHOD(void, Play, ());
	MOCK_METHOD(void, Play, (), (override));
	
	// void Stop(int n) override {}
	MOCK_METHOD(void, Stop, (int n), (override));
};

TEST(Mp3Test, Sample) {
	MockMp3 mock;      // !
}
#endif

#include <gmock/gmock.h>

struct Element {};

class Calc {
	int x;
public:
	virtual ~Calc() {}

	// 행위 기반 검증 대상이 아닙니다.
	virtual int Add(Element x) {}

	// 행위 기반 검증 대상
	virtual int Add(int times, Element x) {}
};

class User {
public:
	void Add(Calc* p) {
		p->Add(10, Element{});
	}
};
//------------------
// 의존하는 객체가 상속 가능한 클래스라면, Google Mock을 통해 행위기반 검증을 수행하 수 있습니다.
class MockCalc : public Calc {
public:
	MOCK_METHOD(int, Add, (int times, Element x), (override));
};

// 인자 일치하는지 검증하기 위해서 필요합니다.
bool operator==(const Element& lhs, const Element& rhs) {
	return true;
}

TEST(UserTest, Add) {
	User user;
	MockCalc calc;

	// EXPECT_CALL(calc, Add);
	EXPECT_CALL(calc, Add(10, Element{}));
	
	user.Add(&calc);
}
