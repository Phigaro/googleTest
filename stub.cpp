// 12_Stub.cpp
#include <iostream>

class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad Network State...";
	}
};

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
};

class TCPConnection : public IConnection {
public:
	void Move(int x, int y) override {
		// Move 패킷을 만들어서 서버로 전송한다.
	}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		try {
			conn->Move(x, y);
			// ....
		} catch (NetworkException& e) {
			printf("NetworkException 처리 로직\n");
			throw e;
		}
	}
};

//------------
#include <gtest/gtest.h>

// Test Stub Pattern
//  의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//  방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 제어한다.
//  => 특수한 상황을 시뮬레이션 하고 싶다.
//    : 예외, 반환값, 시간 등의 제어가 불가능한 환경을 제어하기 위한 목적으로 사용합니다.

// 테스트 대역
//  : 협력 객체의 인터페이스가 간결할 수록 테스트 대역을 만들기 편리합니다.

// SOLID 원칙 => Testability(테스트 용이성)
//  - SRP(단일 책임 원칙): 단 하나의 책임을 가져야 한다.
//  - OCP(개방 폐쇄 원칙): 수정에는 닫혀 있고, 확장에는 열려 있어야 한다.
//  - LSP(리스코프 대체 원칙): 자식 클래스는 부모 클래스로 대체할 수 있어야 한다.
//                          => 자식의 공통된 기능은 부모로부터 비롯되어야 한다.
//  - ISP(인터페이스 분리 원칙): 범용 인터페이스보다 세분화된 인터페이스가 낫다.
//  - DIP(의존관계 역전 원칙): 구체적인 타입에 의존하는 것이 아니라, 인터페이스나 추상 개념에 의존해야 한다.
class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}
};

// 의존성 주입
//  => 제품 코드를 사용하는 방식 그대로 테스트 코드를 작성할 수 있습니다.

// Player의 Move가 호출되었을 때, NetworkException이 발생한다면,
// NetworkException이 외부로 전파되는지 여부를 검증하고 싶다.
TEST(PlayerTest, Move) {
	StubConnection conn; // !!!
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}

#if 0
TEST(PlayerTest, Move) {
	TCPConnection conn;
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}
#endif

#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class Clock : public Time {
public:
	std::string GetCurrentTime() override {
		// 현재 시간을 문자열로 변경해서 반환한다.
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
// User의 Display를 호출하였을 때,
// 00시 00분에 42를 반환하는지 여부를 검증하고 싶다.
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