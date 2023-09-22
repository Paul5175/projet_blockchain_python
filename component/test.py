#include <gtest/gtest.h>
#include "bip39.cpp"

TEST(Bip39Test, CreateAndValidateRecoveryPhrase) {
    // Test creating and validating a recovery phrase
    std::string recovery_phrase = create_recovery_phrase(24, "en");
    EXPECT_TRUE(validate_recovery_phrase(recovery_phrase, "en"));
}

// Add more test cases as needed

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

