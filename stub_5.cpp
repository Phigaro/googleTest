#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
	std::string GetCurrentTime() override {
		return "15:07";
	}
};

class User {
	Time* time;
public:
	User(Time* p) : time(p) {}

	int Display() {
		std::string t = time->GetCurrentTime();
		if (t == "00:00") {
			return 42;
		}

		return 0;
	}
};

//----------
#include <gmock/gmock.h>

class StubTime : public Time {
public:
	MOCK_METHOD(std::string, GetCurrentTime, (), (override));
};

using testing::NiceMock;
using testing::Return;

TEST(UserTest, Display) {
	NiceMock<StubTime> c;
	ON_CALL(c, GetCurrentTime).WillByDefault(Return("00:00"));
	User user(&c);

	EXPECT_EQ(user.Display(), 42) << "00:00분에 수행하였을 때";
}