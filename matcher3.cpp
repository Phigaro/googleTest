#include <gmock/gmock.h>

// Matcher를 상태 기반 검증에서 사용할 수 있습니다.
// => Hamcrest Matcher
//  : 단언문을 사용할 때, 문장에 가까운 표현을 사용할 수 있습니다.
//   "비교 표현의 확장 라이브러리"
//   "가독성"
int GetAge() { return 420; }
const char* GetName() { return "Tommy"; }

using testing::Eq;
using testing::StartsWith;
using testing::MatchesRegex;

TEST(HamcrestTest, Sample) {
	// Google Test - EXPECT_EQ
	EXPECT_EQ(GetAge(), 42);
	
	// Google Mock(Hamcrest Matcher) - EXPECT_THAT => Matcher
	EXPECT_THAT(GetAge(), Eq(42));
	EXPECT_THAT(GetName(), StartsWith("Tom"));
	EXPECT_THAT(GetName(), MatchesRegex(".+"));
}