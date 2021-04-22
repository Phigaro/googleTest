#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class FileTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("File에 기록 - %d[%s]\n", level, message.c_str());
	}
};

class NetworkTarget : public DLoggerTarget {
public:
	void Write(Level level, const std::string& message) override {
		printf("Network에 기록 - %d[%s]\n", level, message.c_str());
	}
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* e: targets) {
			e->Write(level, message);
		}
	}
};

//----------------
#include <gtest/gtest.h>
#include <algorithm>

// Test Spy Pattern
//  의도: 함수를 호출하였을 때 발생하는 부수효과를 관찰할 수 없어서, 테스트되지 않은 요구사항이 있을 때
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//       "다른 컴포넌트로부터의 간접 출력을 저장해 두었다가 검증한다"
class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) const {
		static std::string levelStr[] = {
			"I", "W", "E"	
		};

		return levelStr[level] + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(concat(level, message));
	}
	
	bool IsReceived(Level level, const std::string& message) const {
		return std::find(history.begin(), history.end(), concat(level, message)) 
				!= history.end();
	}
};

// DLoggerTarget에 2개 이상 타겟이 등록되고,
// Write 수행하였을 때, 각 Target에 Write가 제대로 전달되는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	DLogger logger;
	SpyTarget t1, t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	logger.Write(test_level, test_message);

	EXPECT_TRUE(t1.IsReceived(test_level, test_message));
	EXPECT_TRUE(t2.IsReceived(test_level, test_message));
}

#if 0
int main() {
	DLogger logger;
	FileTarget t1;
	NetworkTarget t2;

	logger.AddTarget(&t1);
	logger.AddTarget(&t2);

	logger.Write(INFO, "hello world");
	logger.Write(WARN, "show me the money");
}
#endif
