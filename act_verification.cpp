#include <gmock/gmock.h>

// 행위 기반 검증
// 1. 함수 호출 여부
// 2. 함수 호출 횟수
// 3. 함수 호출 순서
//  => 인자 검증

struct User {
	virtual ~User() {}

	virtual void Go(int x, int y) = 0;
};

class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (int x, int y), (override));
};

void Sample1(User* p) {
	p->Go(10, 20);
	p->Go(10, 20);
}

// 1. EXPECT_CALL => 호출 여부
TEST(UserTest, Sample1) {
	MockUser mock;

	// EXPECT_CALL(mock, Go);          // 인자 X
	// EXPECT_CALL(mock, Go).Times(2);
	EXPECT_CALL(mock, Go(10, 20)).Times(2);  // 인자 O

	Sample1(&mock);
}

void Sample2(User* p) {
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
	p->Go(10, 20);
}

// 2. 호출 횟수
//  EXPECT_CALL(...).Times(...)
// - AtLeast: 적어도 N번 이상
// - AtMost: 최대 N번 이하
// - AnyNumber
// - Between
using testing::AtLeast;
using testing::AtMost;
using testing::AnyNumber;
using testing::Between;

TEST(UserTest, Sample2) {
	MockUser mock;
	
	// EXPECT_CALL(mock, Go(10, 20)).Times(4);
	// EXPECT_CALL(mock, Go(10, 20)).Times(AtLeast(1));
	// EXPECT_CALL(mock, Go(10, 20)).Times(AtMost(3));
	// EXPECT_CALL(mock, Go(10, 20)).Times(AnyNumber());
	EXPECT_CALL(mock, Go(10, 20)).Times(Between(1, 4));

	Sample2(&mock);
}

using testing::_;   // 모든 것에 매칭됩니다.
using testing::Eq;  // ==
using testing::Lt;  // <
using testing::Gt;  // >
using testing::Le;  // <=
using testing::Ge;  // >=
using testing::AllOf; // &&
using testing::AnyOf; // ||

using testing::Matcher;

// 호출 횟수 / 인자 검증(Matcher - Hamcrest)
void Sample3(User* p) {
	p->Go(11, 21);
	p->Go(12, 22);
	p->Go(13, 23);
	p->Go(14, 24);
}

TEST(UserTest, Sample3) {
	MockUser mock;

	// EXPECT_CALL(mock, Go(10, _)).Times(4);
	// EXPECT_CALL(mock, Go(Gt(10), Le(25))).Times(4);
	
	// first arg:  10 < arg1 && 20 >= arg2
	// second arg: 25 >= arg2 || 100 < arg2
	Matcher<int> firstArg = AllOf(Gt(10), Le(20));
	Matcher<int> secondArg = AnyOf(Le(25), Gt(100));
	EXPECT_CALL(mock, Go(firstArg, secondArg)).Times(4);

	Sample3(&mock);
}

struct Foo {
	virtual ~Foo() {}

	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD
	

};