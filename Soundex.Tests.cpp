#include <gtest/gtest.h>
#include "Soundex.h"

TEST(SoudexTestsuite, ReplacesConsonantsWithAppropriateDigits) {
 //AAA
  char soundex[5];
  generateSoundex("AX", soundex);
  //ASSERT_EQ(soundex,"A200");
}

// TEST(SoudexTestsuite, DropsAllVowels) {
//   char soundex[5];
//   generateSoundex("Honeyman", soundex);
//   ASSERT_EQ(soundex,"H555");
}
