
struct User {
	virtual ~User() {}

	virtual void Go() = 0;
	virtual void Say() = 0;
};

void UseUser(User* p) {
	// p->Go();
	p->Say();
}
//---------
#include <gmock/gmock.h>

class MockUser : public User {
public:
	MOCK_METHOD(void, Go, (), (override));
	MOCK_METHOD(void, Say, (), (override));
};

// MOCK_METHOD를 한 메소드에 대해서 호출 여부를 검증(EXPECT_CALL)하고 있지 않다면
// 1. Default Mock - Naggy Mock
//  => 관심없는 호출에 대한 경고를 발생시킵니다.
//  => 테스트의 결과에는 영향이 없습니다.

// 2. NiceMock
//  => 경고를 발생시키지 않습니다.
//
// 3. StrictMock
//  => 테스트가 실패합니다.

#if 0
GMOCK WARNING:
Uninteresting mock function call - returning directly.
    Function call: Say()
#endif
// UseUser에서 User에 대하여 Go가 제대로 호출되는지 여부를 검증하고 싶다.
using testing::NiceMock;
using testing::StrictMock;

TEST(UserTest, UseUser) {
	// MockUser mock;
	// NiceMock<MockUser> mock;
	StrictMock<MockUser> mock;

	EXPECT_CALL(mock, Go);

	UseUser(&mock);
}