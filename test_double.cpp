// 11_테스트대역.cpp
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
