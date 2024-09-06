#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoudexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
  char soundex[5], soundex1[5], soundex2[5];
  
  generateSoundex("Robert", soundex);
  ASSERT_EQ(soundex,"R163");
  generateSoundex("Ruperd", soundex1);
  ASSERT_EQ(soundex1,"R163");
  ASSERT_EQ(soundex,soundex1);

  generateSoundex("Honeyman", soundex2);
  ASSERT_EQ(soundex2,"H555");
}

TEST(SoudexTestsuite, DropsAllVowels) {
  char soundex[5], char soundex1[5];
  
  generateSoundex("Cameroon", soundex);
  ASSERT_EQ(soundex,"C565");
  generateSoundex("Cmrn", soundex1);
  ASSERT_EQ(soundex1,"C565");
  ASSERT_EQ(soundex,soundex1);
}

TEST(SoudexTestsuite, DropsRepeatedAdjacentEncodings) {
  char soundex[5], soundex1[5], soundex2[5];
  
  generateSoundex("Mississippi", soundex);
  ASSERT_EQ(soundex,"M221");
  generateSoundex("Misisipi", soundex1);
  ASSERT_EQ(soundex1,"M221");
  ASSERT_EQ(soundex,soundex1);

  generateSoundex("Pfister", soundex2);
  ASSERT_EQ(soundex2,"P236");
}

TEST(SoudexTestsuite, DropsRepeatedAdjacentEncodingsSeparatedByHOrW) {
  char soundex[5], soundex1[5];
  
  generateSoundex("Vanyn", soundex);
  ASSERT_EQ(soundex,"V550");
  generateSoundex("Vamyn", soundex);
  ASSERT_EQ(soundex,"V550");
}
