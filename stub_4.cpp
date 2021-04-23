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
#include <gmock/gmock.h>

class StubConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
};

using testing::NiceMock;
using testing::Throw;

TEST(PlayerTest, Move) {
	NiceMock<StubConnection> conn; 
	ON_CALL(conn, Move).WillByDefault(Throw(NetworkException()));
	Player player(&conn);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}