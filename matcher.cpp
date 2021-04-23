struct Printer {
	virtual ~Printer() {}

	virtual void Print(int n) = 0;
	virtual void Print(char c) = 0;
};

void UsePrinter(Printer* p) {
	p->Print(10);  // Print(int)
	p->Print('a'); // Print(char)
}

#include <gmock/gmock.h>

class MockPrinter : public Printer {
public:
	MOCK_METHOD(void, Print, (int n), (override));
	MOCK_METHOD(void, Print, (char c), (override));
};

void foo(int n)  { printf("foo(int)\n"); }
// void foo(char n) { printf("foo(char)\n"); }

// char ->char: 정확한 매칭
// char ->int : Promotion
// int  ->char: Type Conversion
// int  ->... : 가변 인자

using testing::An;
using testing::TypedEq;
using testing::Matcher;

// call of overloaded ‘gmock_Print(int)’ is ambiguous
TEST(PrinterTest, UsePrinter) {
	// foo(10);
	// foo('a');

	MockPrinter mock;
	
	// EXPECT_CALL(mock, Print(An<int>()));
	EXPECT_CALL(mock, Print(TypedEq<int>(10)));
	EXPECT_CALL(mock, Print(Matcher<char>('a')));

	UsePrinter(&mock);
}