// 11_테스트대역.cpp
#if 0
#include <string>

class FileSystem {
public:
	virtual ~FileSystem() {}

	virtual bool IsValid(const std::string& filename) {
		// ....
		return true;
	}
};

class Logger {
public:
	// file.log
	//  => 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		if (name.size() < 5) {
			return false;
		}

		FileSystem fileSystem;
		return fileSystem.IsValid(filename);
	}
};


//------------------
#include <gtest/gtest.h>

TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid_file_name.log";

	bool actual = logger.IsValidLogFilename(validFilename);
	
	EXPECT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string invalidFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}

#endif

// 11_테스트대역2.cpp
#include <string>

// 핵심: 테스트 대역은 반드시 제품 코드의 설계가 미리 준비되어 있어야 합니다.
//
//              강한 결합: 의존하는 객체에 대해서 구체적인 타입에 의존하는 것
// 약한 결합(느슨한 결합): 의존하는 객체에 구체적인 타입에 의존하는 것이 아니라,
//                         인터페이스나 추상 클래스를 이용하는 것
//                => 직접 생성하는 것이 아니라 외부에서 생성해서 전달받아야 합니다.
//                => DI(Dependency Injection)
//                 1) 생성자 주입
//                  : 협력 객체가 필수적인 경우
//                 2) 메소드 주입
//                  : 협력 객체가 필수적이지 않은 경우
//                -----------------
//                의존성 주입 문제점 - 보일러플레이트
//                  => 가난한자의 의존성 주입
//                  => 해결 방법: 의존성 주입 프레임워크
//                    Java: Dagger2
//                    C++: fruit
//                A a;
//                B b;
//                C c;
//                X x(&a, &b, &c);

// 틈새 만들기
struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& filename) = 0;
};

class FileSystem : public IFileSystem {
public:
	virtual ~FileSystem() {}

	bool IsValid(const std::string& filename) override {
		// return true;
		return false;
	}
};

class Logger {
	IFileSystem* fileSystem;
public:
	// SUT를 테스트 대역을 적용할 수 있는 설계로 변경하는 작업 - 틈새 만들기
	//  => 기존의 사용법과 동일하게 만드는 것이 좋습니다.
	Logger(IFileSystem* p = nullptr) : fileSystem(p) { 
		if (fileSystem == nullptr) {
			fileSystem = new FileSystem;
		}
	}

	// file.log
	//  => 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//------ 단위 테스트
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		if (name.size() < 5) {
			return false;
		}
		//-------------------

		// FileSystem fileSystem;
		// IFileSystem* fileSystem = new FileSystem;
		// bool result = fileSystem->IsValid(filename);
		// delete fileSystem;
		return fileSystem->IsValid(filename);
	}
};


//------------------
#include <gtest/gtest.h>

// Test Double(테스트 대역)을 만드는 방법.
//  => 협력 객체의 인터페이스를 구현하는 형태로 만들면됩니다.
class TestDoubleFileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};


TEST(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestDoubleFileSystem fs;
	Logger logger(&fs);
	std::string validFilename = "valid_file_name.log";

	bool actual = logger.IsValidLogFilename(validFilename);
	
	EXPECT_TRUE(actual) << "파일명이 다섯글자 이상일 때";
}

TEST(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestDoubleFileSystem fs;
	Logger logger(&fs);
	std::string invalidFilename = "bad.log";

	EXPECT_FALSE(logger.IsValidLogFilename(invalidFilename)) << "파일명이 다섯글자 미만일 때";
}
