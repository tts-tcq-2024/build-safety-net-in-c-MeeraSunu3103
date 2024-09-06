#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoudexTestSuite, ReplacesConsonantsWithAppropriateDigits) {
  char soundex[5], soundex1[5], soundex2[5];
  
  generateSoundex("Robert", soundex);
  ASSERT_EQ(soundex,"R163");
  generateSoundex("Ruperd", soundex1);
  ASSERT_EQ(soundex1,"R163");
  ASSERT_EQ(soundex,soundex1);

  generateSoundex("Honeyman", soundex2);
  ASSERT_EQ(soundex2,"H555");
}

TEST(SoudexTestSuite, RetainsFirstCharacter) {
  char soundex[5];
  
  generateSoundex("Meera", soundex);
  ASSERT_EQ(soundex,"M600");
  generateSoundex("aeiou", soundex);
  ASSERT_EQ(soundex,"A000");
}

TEST(SoudexTestSuite, DropsAllVowels) {
  char soundex[5], soundex1[5];
  
  generateSoundex("Cameroon", soundex);
  ASSERT_EQ(soundex,"C565");
  generateSoundex("Cmrn", soundex1);
  ASSERT_EQ(soundex1,"C565");
  ASSERT_EQ(soundex,soundex1);
}

TEST(SoudexTestSuite, DropsRepeatedAdjacentEncodings) {
  char soundex[5], soundex1[5], soundex2[5];
  
  generateSoundex("Mississippi", soundex);
  ASSERT_EQ(soundex,"M221");
  generateSoundex("Misisipi", soundex1);
  ASSERT_EQ(soundex1,"M221");
  ASSERT_EQ(soundex,soundex1);

  generateSoundex("Pfister", soundex2);
  ASSERT_EQ(soundex2,"P236");
}

TEST(SoudexTestSuite, DropsRepeatedAdjacentEncodingsSeparatedByHOrW) {
  char soundex[5];
  
  generateSoundex("Vanyn", soundex);
  ASSERT_EQ(soundex,"V550");
  generateSoundex("Vamyn", soundex);
  ASSERT_EQ(soundex,"V550");
}

TEST(SoudexTestSuite, RetainsRepeatedAdjacentEncodingsSeparatedByVowels) {
  char soundex[5];
  
  generateSoundex("Halal", soundex);
  ASSERT_EQ(soundex,"H440");
}

TEST(SoudexTestSuite, ProcessesEmptyString) {
  char soundex[5];
  
  generateSoundex("", soundex);
  ASSERT_EQ(soundex,"");
}

TEST(SoudexTestSuite, ProcessesLowercaseAndUppercaseAlphabets) {
  char soundex[5];
  
  generateSoundex("McCormick", soundex);
  ASSERT_EQ(soundex,"M265");
}

TEST(SoudexTestSuite, IgnoresNonAlphabeticCharacters) {
  char soundex[5];
  
  generateSoundex("MeeraSunu3103!", soundex);
  ASSERT_EQ(soundex,"M625");
  generateSoundex("Van Dyke", soundex);
  ASSERT_EQ(soundex,"V532");
}
