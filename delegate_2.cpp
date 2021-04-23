#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}
	
	virtual void Pure(int n) = 0;
	virtual int Concreate(const char* str) {
		printf("Foo - Concreate\n");
		return 0;
	}
};


class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Pure, (int n), (override));
	MOCK_METHOD(int, Concreate, (const char* str), (override));

	// 부모의 기능을 이용하기 위해서는 별도의 함수를 제공해야 합니다.
	int FooConcreate(const char* str) {
		return Foo::Concreate(str);
	}
};

using testing::NiceMock;
TEST(MockFooTest, Sample) {
	NiceMock<MockFoo> mock;
	
	// ON_CALL을 통해 Concreate가 수행되면, Foo::Concreate가 호출되도록 하고 싶다.
	ON_CALL(mock, Concreate).WillByDefault([&mock](const char* str) {
		// return mock.Concreate(str); // 재귀!
		return mock.FooConcreate(str);      // !!
	});
	
	mock.Concreate("hello");
}