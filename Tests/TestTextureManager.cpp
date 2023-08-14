//
// Created by Alex on 8/14/2023.
//
#include "gtest/gtest.h"

#include "../Engine/include/TextureManager.h"


TEST(TestTextureManager, TestLoadFromFileWithZeroValue) {
    int error = 0;
    error = TextureManager::LoadTextureFromFile(0, "Resources/test.png");
    ASSERT_EQ(error, 0);
}

TEST(TestTextureManager, TestLoadFromFileWithPositiveValue) {
    int error = 0;
    error = TextureManager::LoadTextureFromFile(1, "Resources/test.png");
    ASSERT_EQ(error, 0);
}

TEST(TestTextureManager, TestLoadFromFilehandleDuplicateKey) {
    int error = 0;
    error = TextureManager::LoadTextureFromFile(123, "Resources/test.png");
    ASSERT_EQ(error, 0);
    error = TextureManager::LoadTextureFromFile(123, "Resources/test.png");
    ASSERT_EQ(error, ERROR_TEXTURE_ALREADY_DECLARED) << " function must return ERROR_TEXTURE_ALREADY_DECLARED";
}
