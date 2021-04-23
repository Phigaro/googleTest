#include <string>
#include <vector>

#include "DLoggerTarget.h"
#if 0
enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};
#endif

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

// Mock Object Pattern
//  의도: 함수를 호출하였을 때 발생하는 부수효과를 관찰할 수 없어서, 테스트되지 않은 요구사항이 있을 때
//  방법: 모의 객체를 이용해서 "행위 기반 검증"을 수행한다. 
//       "행위 기반 검증(동작 검증)"
//        - 객체에 작용을 가한 후, 내부적으로 발생한 함수의 호출 여부 / 횟수 / 순서 등의 정보 등을 통해 검증을 수행합니다.
//       "상태 기반 검증(상태 검증)"
//        - 객체에 작용을 가한 후, 내부적으로 발생한 부수효과(값 변경, 반환 값)를 이용해 검증을 수행합니다.
//
//  모의 객체(Mock Object)
//    - 내부적으로 발생한 함수의 호출 여부 / 호출 횟수 / 호출 순서 등의 정보를 기록합니다.
//    => Mock Framework 
//      Java: jMock, EasyMock, Mockito, Spock
//       C++: Google Mock

// 1. include
#include <gmock/gmock.h>

// 2. Mocking
	

#if 0
// 아래의 방법은 더 이상 권장되지 않습니다. - 1.10 이전
// - MOCK_METHOD{ArgN}(함수 이름, 함수 시그니처)
$ ./googletest/googlemock/scripts/generator/gmock_gen.py DLoggerTarget.h

class MockDLoggerTarget : public DLoggerTarget {
 public:
  MOCK_METHOD2(Write,
      void(Level level, const std::string& message));
};
#endif

// 1.10
//  - Mocking을 위한 매크로가 변경되었습니다.
//   => MOCK_METHOD(반환타입, 함수이름, 인자정보, 한정자정보);

class MockDLoggerTarget : public DLoggerTarget {
public:
	// void Write(Level level, const std::string& message) override {}
	MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
};

// DLoggerTarget에 2개 이상 타겟이 등록되고,
// Write 수행하였을 때, 각 Target에 Write가 제대로 전달되는지 여부를 검증하고 싶다.
TEST(DLoggerTest, Write) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget t1, t2;
	logger.AddTarget(&t1);
	logger.AddTarget(&t2);
	Level test_level = INFO;
	std::string test_message = "test_log_message";

	// Assert
	EXPECT_CALL(t1, Write(test_level, test_message));
	EXPECT_CALL(t2, Write(test_level, test_message));

	// Act
	logger.Write(test_level, test_message);
}