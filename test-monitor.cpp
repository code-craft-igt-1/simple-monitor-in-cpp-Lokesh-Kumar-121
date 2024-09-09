#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(103, 70, 95));
  ASSERT_TRUE(vitalsOk(102, 70, 95));
  ASSERT_TRUE(vitalsOk(96, 70, 95));

  ASSERT_FALSE(vitalsOk(99, 110, 95));
  ASSERT_TRUE(vitalsOk(99, 99, 95));
  ASSERT_TRUE(vitalsOk(99, 60.5, 95));

  ASSERT_FALSE(vitalsOk(99, 70, 80));
  ASSERT_TRUE(vitalsOk(99, 70, 91));

  ASSERT_TRUE(vitalsOk(99, 70, 98));
}
