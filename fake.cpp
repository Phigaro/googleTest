#include <string>

// DAO(Database Access Object)
class User {
	std::string name;
	int age;
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};
struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
	// ....
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* p) {
		database->SaveUser(p->GetName(), p);
	}

	User* Load(const std::string& name) {
		return database->LoadUser(name);
	}

	bool IsExist(const std::string& name) {
		return Load(name) != nullptr;
	}
};
//---------
#include <gtest/gtest.h>
#include <map>

// 문제: IDatabase의 구현체가 아직 준비되지 않았다.

// Fake Object Pattern
//  의도: 아직 준비되지 않은 의존 객체로 인해서, 테스트되지 않은 요구사항이 있을 때
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서 테스트를 수행한다.
//   1) 의존 객체가 준비되지 않았을 때
//   2) 의존 객체가 너무 느려서 느린 테스트의 문제가 발생하였을 때
//   3) 의존 객체가 사용하기 어려울 때
class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
};

TEST(UserManagerTest, IsExist) {
	FakeDatabase db;
	UserManager manager(&db);
	std::string name = "test_name";
	int age = 100;
	User expected(name, age);
	
	manager.Save(&expected);

	EXPECT_TRUE(manager.IsExist(name)) << "Save 하였을 때";
}
