#include "./monitor.h"

#include "gtest/gtest.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 95));
  ASSERT_FALSE(vitalsOk(103, 70, 95));
  ASSERT_FALSE(vitalsOk(99, 70, 70));
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));
}
