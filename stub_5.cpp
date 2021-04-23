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
#include <gtest/gtest.h>

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, Display) {
	StubTime c;
	// Clock c;
	User user(&c);

	EXPECT_EQ(user.Display(), 42) << "00:00분에 수행하였을 때";
}