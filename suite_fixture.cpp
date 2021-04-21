#include <string>
#include <unistd.h> // sleep
#include <gtest/gtest.h>

class Database {
public:
	void Connect() {
		sleep(2);
	}
	void Disconnect() {
		sleep(2);
	}

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//-------------------------
// Inline Fixture

#if 0
TEST(DatabaseTest, Login) {
	Database* database = new Database;
	database-> Connect(0;

	database-> Login("test_id", "test_password");
	
	ASSERT_TRUE(database-> IsLogin()) << "로그인 하였을 때";

	database-> Disconnect();
	delete database;
}

TEST(DatabaseTest, Logout) {
	Database* database = new Database;
	database-> Connect(0;

	database-> Login("test_id", "test_password");
	database-> Logout();
	
	ASSERT_TRUE(database-> IsLogin()) << "로그아웃 하였을 때";

	database-> Disconnect();
	delete database;
}
#endif

//------------------------

// 문제점 : 픽스쳐를 설치하거나 해체하는 과정으로 인해 "느린 테스트" 의 문제가 발생하였다
// 해결방법 : Suite Fixture 를 사용
// 문제는 DatabaseTest* ts = new DatabaseTest를 TC마다 반족해서 생기는 문제
// 그래서 이 ts 생성 단게 전 후에
// <suite Fixture SetUp> - static
// <suite Fixture TearDown> - static 을 사용해 전체를 아우르는 SetUp TearDown을 사용한다.

// 4sec(connect, disconnect) * 25TC = 100sec

class DatabaseTest : public testing::Test {
protected:
	// 1.10 이전
#if 0
	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
	}
	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
	}
#endif
	// 1.10 이후 이게 권장
	static void SetUpTestSuite(){
		printf("SetUpTestSuite()\n");
	}
	static void TearDownTestSuite(){
		printf("tearDownTestSuidte()\n");
	}

	Database* database;
	
	DatabaseTest() : database(nullptr) {}

	void SetUp() override {
		database = new Database;
		database-> Connect();
	}

	void TearDown() override {
		database-> Disconnect();
		delete database;
	}
};


TEST_F(DatabaseTest, Login) {
	database-> Login("test_id", "test_password");

	ASSERT_TRUE(database-> IsLogin()) << "로그인 하였을 때";
};

TEST_F(DatabaseTest, Logout) {
	database-> Login("test_id", "test_password");
	database-> Logout();

	ASSERT_FALSE(database-> IsLogin()) << "로그아웃 하였을 때";
};
