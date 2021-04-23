#include <stdio.h>

// 의존성 주입 - C++
//  2. 템플릿 기반 - 단위 전략(Policy Based Design)
struct Packet {};

class ConcreatePacketStream {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream::GetPacket\n");
		return nullptr;
	}
};

// Class Template: 타입 추론이 불가능
// template <typename PacketStream>
class PacketReader {
public:
	// Function Template: 타입 추론이 가능합니다.
	template <typename PacketStream>
	void ReadPacket(PacketStream* stream, size_t packet_number) {
		stream->AppendPacket(nullptr);
		stream->GetPacket(packet_number);
	}
};

class ConcreatePacketStream2 {
public:
	void AppendPacket(Packet* new_packet) {
		printf("ConcreatePacketStream2::AppendPacket\n");
	}

	const Packet* GetPacket(size_t packet_number) const {
		printf("ConcreatePacketStream2::GetPacket\n");
		return nullptr;
	}
};

#if 0
int main() {
	PacketReader reader;
	ConcreatePacketStream stream;
	
	reader.ReadPacket(&stream, 42);
}
#endif
//---------
#include <gmock/gmock.h>
#if 0
class MockPacketStream : public PacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet), (override));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const, override));
};
#endif

class MockPacketStream {
public:
	MOCK_METHOD(void, AppendPacket, (Packet* new_packet));
	MOCK_METHOD(const Packet*, GetPacket, (size_t packet_number), (const));
};

TEST(PacketReaderTest, ReadPacket) {
	PacketReader reader;
	MockPacketStream stream;

	EXPECT_CALL(stream, AppendPacket);
	EXPECT_CALL(stream, GetPacket);

	reader.ReadPacket(&stream, 42);
}