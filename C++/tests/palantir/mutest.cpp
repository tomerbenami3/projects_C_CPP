#include "mu_test.h"
#include "rot13.hpp"
#include "caeser.hpp"
#include "messenger.hpp"
#include "cin.hpp"
#include "cout.hpp"
#include "message.hpp"
#include "multi_encoder.hpp"
#include "abstract_encode.hpp"
#include "xor.hpp"
#include "udp.hpp"
#include "tcp.hpp"
#include "vigenere.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"
#include <string>
#include <iostream>
#include <vector>


/*
BEGIN_TEST(message_encode_rot13)
    palantir::Message message("asfnasfbnasmnbfmnas!!");
    palantir::Rot13 rot13;
    rot13.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(message_encode_rot13_execute)
    palantir::Message message("asfnasfbnasmnbfmnas!!");
    
    palantir::Cin src;
    palantir::Cout dst;
    palantir::Rot13 rot13;

    palantir::Messenger msg{src, dst, rot13};
    msg.execute();
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(message_encode_caeser_forward)
    palantir::Message message("abcdefg");
    palantir::Caeser caeser{4};
    caeser.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(message_encode_caeser_backward)
    palantir::Message message("ABCddssrrff!!");
    palantir::Caeser caeser{-4};
    caeser.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(message_encode_caeser_bigger_than_26)
    palantir::Message message("aSadfdsdsdDD!!");
    palantir::Caeser caeser{673};
    caeser.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST
*/
BEGIN_TEST(Messenger_test_read_write)
    palantir::Message message("SHWAYE SHAWYE");

    palantir::Cin src;
    palantir::Cout dst;
    palantir::Rot13 rot13;

    palantir::Messenger msg{src, dst, rot13};
    msg.execute();
    ASSERT_THAT(1);
END_TEST
/*
BEGIN_TEST(vector_of_encoders)
    palantir::Cin src;
    palantir::Cout dst;
    palantir::Rot13 rot13;
    palantir::Caeser caeser{4};
    std::vector<palantir::AbstractEncoder*> vector = {&rot13, &caeser};

    palantir::MultiEncoder encoders{vector};
    palantir::Messenger msg{src, dst, encoders};

    // msg.execute();
    // std::cout << message.getmsg() << "\n";

    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(message_encode_xor)
    palantir::Message message("matanasdasdaswerwerwerwerwerwerqqwxwddsa");
    palantir::XorEnc exor("abuhamzi");
    exor.encode(message);
    std::cout << message.getmsg() << "\n";
    exor.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST
*/
// BEGIN_TEST(udp_source_read_test_with_netcat)
//     const std::string testIP = "127.0.0.1";
//     const size_t testPort = 12345;
//     palantir::UDPSource UDPSource(testIP, testPort);

//     std::string receivedMessage = UDPSource.read();
//     std::cout<< "here " <<receivedMessage<<" len = "<<receivedMessage.length()<<'\n';
//     std::string const testMsg = "abcd\n";

//     std::cout<< "here " <<testMsg<<" len = "<<testMsg.length()<<'\n';
//     ASSERT_EQUAL(receivedMessage.compare(testMsg),0);
// END_TEST


// BEGIN_TEST(udp_receiver_write_test_with_netcat)
//     const std::string testMessage = "abcd";
//     const size_t testPort = 12345;

//     palantir::UDPReceiver UDPRec("127.0.0.1",testPort);
//     UDPRec.write(testMessage);

//     ASSERT_THAT(1);
// END_TEST

// BEGIN_TEST(tcp_source_read_test_with_netcat)
//     const std::string testIP = "127.0.0.1";
//     const size_t testPort = 12345;

//     palantir::TCPSource tcpSource(testIP, testPort);

//     std::string receivedMessage = tcpSource.read();

//     std::cout << "Received: " << receivedMessage << '\n';

//     ASSERT_EQUAL(receivedMessage, "abcd\n");
// END_TEST


BEGIN_TEST(tcp_destination_write_test_with_netcat)
    const std::string testIP = "127.0.0.1";
    const size_t testPort = 8080;

    palantir::TCPDestination tcpDest(testIP, testPort);

    const std::string testMsg = "abcd";
    tcpDest.write(testMsg);

    ASSERT_THAT(1); 
END_TEST

// BEGIN_TEST(message_encode_vigenere)
//     palantir::Message message("abcderfs!!");
//     palantir::Vigenere vig("key");
//     vig.encode(message);
//     std::cout << message.getmsg() << "\n";
//     ASSERT_THAT(1);
// END_TEST

BEGIN_TEST(read_from_file_and_encode_vegenere)
    palantir::FileSource file("test.txt");
    std::string line = file.read();
    palantir::Message message(line);
    palantir::Vigenere vig("key");
    // vig.encode(message);
    std::cout << message.getmsg() << "\n";
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(open_file_twice)
    try {
        palantir::FileSource file1("test.txt");
        std::string line = file1.read();
        palantir::Message message(line);
        palantir::Vigenere vig("key");
        // vig.encode(message);
        std::cout << message.getmsg() << "\n";

        palantir::FileSource file2("test.txt");
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
        ASSERT_THAT(std::string(e.what()).find("failed to open file") != std::string::npos);
    }
    ASSERT_THAT(1);
END_TEST




TEST_SUITE(palantir unit tests)
	// TEST(message_encode_rot13)
	// TEST(message_encode_rot13_execute)
	// TEST(message_encode_caeser_forward)
	// TEST(message_encode_caeser_backward)
	// TEST(message_encode_caeser_bigger_than_26)
	TEST(Messenger_test_read_write)
	// TEST(vector_of_encoders)
	// TEST(message_encode_xor)
	// TEST(udp_source_read_test_with_netcat)
	// TEST(udp_receiver_write_test_with_netcat)
	// TEST(tcp_source_read_test_with_netcat)
	TEST(tcp_destination_write_test_with_netcat)
	// TEST(message_encode_vigenere)
	TEST(read_from_file_and_encode_vegenere)
	TEST(open_file_twice)

END_SUITE