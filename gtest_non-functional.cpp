#include <string>
#include <unistd.h>

void OpenFile(const std::string& filename){
    sleep(2); // Delayed 2sec
}

//-------
//Ex) 시간이 초과 되었는지
#include <gtest/gtest.h>


// 방법 1. TestSuite - SetUp / TearDown를 이용하는 방법.
#if 0
class SampleTest : public testing::Test {
protected:
	time_t startTime;
	void SetUp() override {
		startTime = time(nullptr);
	}

	void TearDown() override {
		time_t endTime = time(nullptr);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 1) << "시간 초과: " << duration << "초 걸림";
	}
};
#endif

#if 0
TEST_F(SampleTest, OpenFile) {
	OpenFile("");
}
#endif

// OpenFile은 1초 이내에 동작해야 합니다.
#if 0
TEST(SampleTest, OpenFile) {
	OpenFile("");
}
#endif

// 방법 2. 시간을 측정하는 사용자 정의 단언문을 만들어서 사용

#if 0
TEST(SampleTest, OpenFile){
    time_t startTime = time(nullptr);

    OpenFile("");

    time_t endTime = time(nullptr);
    time_t duration = endTime - startTime;
    EXPECT_LE(duration, 1) << "시간 초과: " << duration << "초 걸림";
}
#endif

// 사용자 정의 단언문
#if 0
#define EXPECT_TIMEOUT(fn, sec)                                         \
    do {                                                                \
    time_t startTime = time(nullptr);                                   \
    fn;                                                                 \
    time_t endTime = time(nullptr);                                     \
    time_t duration = endTime - startTime;                              \
    EXPECT_LE(duration, sec) << "시간 초과: " << duration << "초 걸림";  \
    } while (0)                                                          

TEST(SampleTest, OpenFile){
    int startTime;
    EXPECT_TIMEOUT(OpenFile(""), 1);
    EXPECT_TIMEOUT(OpenFile(""), 1);
}
#endif

// 객체의 메모리 누수를 판단하는 목적으로 테스트를 이용
// 1) 제품 코드에 미리 정의되어야 하는 코드가 있음
// -> new / delete 연산자 재정의가 필요

// Image* image = new Image;
// 1) 메모리 할당 operator new (재정의 필요)
// 2) 생성자 함수 호출

// 소멸자도 마찬가지

// AllocCount 같은 정적 변수가 제공 되어야함
// 그리고 new, delete등 중요한 피쳐를 override 하기에 조건부 컴파일 등을 통해
// 테스트에서만 적용하는것이 좋음.

#if 0
class Image {
public:
#ifdef GTEST_LEAK_TEST
	static int allocCount;

	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif

	void Draw() {
		printf("Image draw\n");
	}
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif
#endif

//-------
#ifdef GTEST_LEAK_TEST					
#define DECLARE_LEAK_TEST()					\
public:										\
	static int allocCount;					\
	void* operator new(size_t size) {		\
		++allocCount;						\
		return malloc(size);				\
	}										\
	void operator delete(void* p, size_t) {	\
		--allocCount;						\
		free(p);							\
	}
#define IMPLEMENT_LEAK_TEST(classname)		\
	int classname::allocCount = 0
#else
#define DECLARE_LEAK_TEST()	
#define IMPLEMENT_LEAK_TEST(classname)
#endif

class Image {
	DECLARE_LEAK_TEST()
};

IMPLEMENT_LEAK_TEST(Image);

void DrawImage() {
	Image* p1 = new Image; 
	Image* p2 = new Image;
	Image* p3 = new Image;
	// image->Draw();
	
	delete p2;
	delete p3;
}
//------

//---------
class ImageTest : public testing::Test {
protected:
#ifdef GTEST_LEAK_TEST
	int alloc;
#endif

	ImageTest() {
#ifdef GTEST_LEAK_TEST
		alloc = 0;
#endif
	}

	void SetUp() override {
#ifdef GTEST_LEAK_TEST
		alloc = Image::allocCount;
#endif
	}

	void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(diff, 0) << diff << " Object(s) leaks";
#endif
	}
};

TEST_F(ImageTest, DrawImage) {
	DrawImage();
}








