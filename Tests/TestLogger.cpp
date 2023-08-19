//
// Created by Alex on 8/19/2023.
//
#include "gtest/gtest.h"

#include "../Engine/include/Logger.h"

class TestLogger : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    Logger *loggerObj;
    std::string strOut;
    std::stringstream streamOut;

    TestLogger() {
        loggerObj = new Logger();
        loggerObj->setStream(&streamOut);
        loggerObj->setLogLevel(LogLevel::Verbose);
    }

    ~TestLogger() override {
        delete loggerObj;
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        strOut = "";
        streamOut.clear();
        loggerObj->setLogLevel(LogLevel::Verbose);
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

};

TEST_F(TestLogger, TestGetLogLevelMethod) {
    ASSERT_EQ(LogLevel::Verbose, loggerObj->getLogLevel())
                                << "Expected default log level of test: VERBOSE" << std::endl;
}

TEST_F(TestLogger, TestSetLogLevelMethod) {
    loggerObj->setLogLevel(LogLevel::Warning);
    ASSERT_EQ(LogLevel::Warning, loggerObj->getLogLevel())
                                << "Expected change to Warning" << std::endl;
}

TEST_F(TestLogger, TestLogInfoMethod) {
    loggerObj->logInfo("test", "message");
    strOut = streamOut.str();
    ASSERT_EQ(strOut, "\033[0m[INFO]-[test]: message\033[0m\n")
                                << "Message should" << std::endl
                                << "- start with [INFO]" << std::endl
                                << "- no color on text" << std::endl;
}

TEST_F(TestLogger, TestLogWarnMethod) {
    loggerObj->logWarning("test", "message");
    strOut = streamOut.str();
    ASSERT_EQ(strOut, "\033[33m[WARNING]-[test]: message\033[0m\n")
                                << "Message should" << std::endl
                                << "- start with [WARNING]" << std::endl
                                << "- yellow color on text" << std::endl;
}

TEST_F(TestLogger, TestLogErrorMethod) {
    loggerObj->logError("test", "message");
    strOut = streamOut.str();
    ASSERT_EQ(strOut, "\033[31m[ERROR]-[test]: message\033[0m\n")
                                << "Message should" << std::endl
                                << "- start with [ERROR]" << std::endl
                                << "- red color on text" << std::endl;
}

TEST_F(TestLogger, TestLogLevelFilter) {
    loggerObj->setLogLevel(LogLevel::Error);
    loggerObj->log(LogLevel::Warning, "test", "message");
    strOut = streamOut.str();
    ASSERT_EQ(strOut, "")
                                << "Expected no input" << std::endl;
}

TEST_F(TestLogger, TestLogLevelOrder) {
    ASSERT_EQ(LogLevel::None, static_cast< LogLevel >( 0 )) << "Level 0 should be 'None'" << std::endl;
    ASSERT_EQ(LogLevel::Error, static_cast< LogLevel >( 1 )) << "Level 0 should be 'Error'" << std::endl;
    ASSERT_EQ(LogLevel::Warning, static_cast< LogLevel >( 2 )) << "Level 0 should be 'Warning'" << std::endl;
    ASSERT_EQ(LogLevel::Info, static_cast< LogLevel >( 3 )) << "Level 0 should be 'Info'" << std::endl;
    ASSERT_EQ(LogLevel::Debug, static_cast< LogLevel >( 4 )) << "Level 0 should be 'Debug'" << std::endl;
    ASSERT_EQ(LogLevel::Verbose, static_cast< LogLevel >( 5 )) << "Level 0 should be 'Verbose'" << std::endl;
}