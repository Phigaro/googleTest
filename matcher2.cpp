#include <gmock/gmock.h>

class Foo {
public:
	virtual ~Foo() {}

	virtual void Do(const std::vector<int>& numbers) = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Do, (const std::vector<int>& numbers), (override));
};

// Container Matcher
void UseFoo(Foo* p) {
	p->Do({1, 2, 3, 4, 5});
}

using testing::Matcher;
using testing::Le;
using testing::Ge;
using testing::Eq;
using testing::Gt;

using testing::ElementsAre;
using testing::ElementsAreArray;
using testing::UnorderedElementsAre;
using testing::UnorderedElementsAreArray;

TEST(MockTest, Foo) {
	MockFoo mock;
	Matcher<int> args[] = {
		// Le(1), Gt(1), Ge(3), Eq(4), Ge(5),
		Ge(3), Eq(4), Ge(6), Le(1), Gt(1), 
	};

	// EXPECT_CALL(mock, Do(ElementsAreArray(args)));
	// EXPECT_CALL(mock, Do(ElementsAre(Le(1), Gt(1), Ge(3), Eq(4), Ge(5))));
	EXPECT_CALL(mock, Do(UnorderedElementsAreArray(args)));
	UseFoo(&mock);
}