#if 0
// SUT
class User {
private:
	int age;
public:
	User() : age(42) {}

	void Do() {
		age += 1;
	}

protected: 
	int GetAge() const {
		return age;
	}
};

//------------
#include <gtest/gtest.h>
// 접근하는 속성이 protected 인 경우
//  => 테스트 전용 하위 클래스

class TestUser : public User {
public:
	using User::GetAge;  // protected ->public
};

TEST(UserTest, Do) {
	// User user;
	TestUser user;

	user.Do();

	EXPECT_EQ(43, user.GetAge());
}
#endif

// SUT
#if 0
class User {
private:
	int age;
public:
	User() : age(42) {}

	void Do() {
		age += 1;
		do1();
		do2();
	}

private:
	void do1() {
	}
	void do2() {
	}

protected: 
	int GetAge() const {
		return age;
	}
};
#endif

//------------
// GetAge() 가 private인 경우
//  : 절대 사용하면 안되는 접근 방식입니다.
//  => pImpl idiom(컴파일러 방화벽)은 위의 접근을 막을 수 있습니다.
// #define class struct
// #define private public
// #include "User.h"
// #undef class
// #undef private

// => Frined Test를 이용해서 해결해야 합니다.
//  : Google Test 의존성이 형성됩니다.

//---------
//  로버트 C 마틴 - Clean Code
//   => private 메소드는 public 메소드의 가독성을 높이기 위해 사용해야 한다.
//   => public 메소드를 통해 호출되지 않는 private 메소드는 잘못된 설계이다.
//
//   "테스트 되지 않은 private 메소드가 테스트 된 public 메소드보다 위험하다."


#include <gtest/gtest.h>

TEST(UserTest, Do) {
	User user;

	user.Do();

	EXPECT_EQ(43, user.GetAge());
}

#include <stdio.h>

class Engine {
public:
	Engine() {}
	virtual ~Engine() {}

	virtual void Start() {
		printf("Engine Start...\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ...
		engine->Start();
		// ...
	}
};

//----------
#include <gtest/gtest.h>

// 테스트 전용 하위 클래스 패턴(Test Specific Subclass Pattern)
//  의도: SUT의 클래스가 테스트를 위한 기능을 제공하지 있지 않다면,
//        테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 됩니다.
//        => 기능을 재사용(virtual 함수)
class TestEngine : public Engine {
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	void Start() override {
		Engine::Start();     // 부모의 기능을 재사용한다.
		isStart = true;
		// printf("TestEngine Start\n");
	}

	bool IsStart() const {
		return isStart;
	}
};

// Car의 Go를 호출하였을 때, Engine의 Start가 제대로 호출되는지 여부를 검증하고 싶다.
TEST(CarTest, Go) {
	// Engine engine;
	TestEngine engine;
	Car car(&engine);

	car.Go();

	// engine 객체에 상태를 검증하기 위한 기능이 제공되지 않는다.
	EXPECT_TRUE(engine.IsStart()) << "Car가 Go 했을 때";
}