#include "clike/integer.h"
#include <gtest/gtest.h>

std::vector<uint8_t> int_to_vec(const uint32_t value) {
  std::vector<uint8_t> r(4);
  r[0] = value & 0xff;
  r[1] = (value >> 8) & 0xff;
  r[2] = (value >> 16) & 0xff;
  r[3] = (value >> 24) & 0xff;
  while (!r.empty() && (r.back() == 0)) {
    r.pop_back();
  }
  return r;
}

clike::digit_vector int_to_vec_64(const uint64_t x) {
  clike::digit_vector r({x});
  r.remove_leading_zeros();
  return r;
}

TEST(integer, add_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x01;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a + in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a + b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, add_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a + in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a + b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, add_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffff;
  uint32_t in_b = 0xffff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a + in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a + b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, add_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a + in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a + b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, add_8bit_5) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffffff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a + in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a + b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, add_64bit_carry) {
  std::vector<uint64_t> m = {0x00, 0x00, 0x01};
  clike::integer_radix<uint64_t> a({0xffffffffffffffff}, m);
  clike::integer_radix<uint64_t> b({0x01}, m);

  clike::integer_radix<uint64_t> sum = a + b;
  ASSERT_EQ(2, sum.digits_.size());

  EXPECT_EQ(0, sum.digits_.at(0));
  EXPECT_EQ(1, sum.digits_.at(1));
}

TEST(integer, mul_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x03;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a * in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a * b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mul_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a * in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a * b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mul_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a * in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a * b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mul_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a * in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a * b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, less_than_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x01}, m);
  clike::integer_radix<uint8_t> b({0x02}, m);

  bool result = a < b;
  bool ref_result = 0x01 < 0x02;
  EXPECT_EQ(result, ref_result);

  bool result2 = b < a;
  bool ref_result2 = 0x02 < 0x01;
  EXPECT_EQ(result2, ref_result2);
}

TEST(integer, less_than_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x02}, m);
  clike::integer_radix<uint8_t> b({0x01}, m);

  bool result = a < b;
  bool ref_result = 0x02 < 0x01;
  EXPECT_EQ(result, ref_result);

  bool result2 = b < a;
  bool ref_result2 = 0x01 < 0x02;
  EXPECT_EQ(result2, ref_result2);
}

TEST(integer, less_than_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x01, 0x01}, m);
  clike::integer_radix<uint8_t> b({0x02}, m);

  bool result = a < b;
  bool ref_result = 0x0101 < 0x02;
  EXPECT_EQ(result, ref_result);

  bool result2 = b < a;
  bool ref_result2 = 0x02 < 0x0101;
  EXPECT_EQ(result2, ref_result2);
}

TEST(integer, less_than_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x01}, m);
  clike::integer_radix<uint8_t> b({0x02, 0x01}, m);

  bool result = a < b;
  bool ref_result = 0x01 < 0x0201;
  EXPECT_EQ(result, ref_result);

  bool result2 = b < a;
  bool ref_result2 = 0x0201 < 0x01;
  EXPECT_EQ(result2, ref_result2);
}

TEST(integer, less_than_8bit_5) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x01}, m);
  clike::integer_radix<uint8_t> b({0x01}, m);

  bool result = a < b;
  bool ref_result = 0x01 < 0x01;
  EXPECT_EQ(result, ref_result);
}

TEST(integer, less_than_8bit_6) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x04, 0x00, 0xad, 0x01}, m);
  clike::integer_radix<uint8_t> b({0x11}, m);

  bool result = a < b;
  bool ref_result = 0x0400ad01 < 0x11;
  EXPECT_EQ(result, ref_result);
}

TEST(integer, less_than_8bit_7) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};
  clike::integer_radix<uint8_t> a({0x11}, m);
  clike::integer_radix<uint8_t> b({0x04, 0x00, 0xad, 0x01}, m);

  bool result = a < b;
  bool ref_result = 0x11 < 0x0400ad01;
  EXPECT_EQ(result, ref_result);
}

TEST(integer, sub_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x01;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffff;
  uint32_t in_b = 0xffff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_5) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xffffff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_6) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x01ad0004;
  uint32_t in_b = 0x11;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_7) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x020000;
  uint32_t in_b = 0x03fffe;
  std::vector<uint8_t> out_ref = int_to_vec(in_a - in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, sub_8bit_8) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x03fffe;
  uint32_t in_b = 0x020000;

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a - b;

  clike::integer_radix<uint8_t> out_ref = c + b;

  ASSERT_EQ(out_ref.size(), a.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), a.digits_.at(i));
  }
}

TEST(integer, sub_64bit_carry) {
  std::vector<uint64_t> m = {0x00, 0x00, 0x01};
  clike::integer_radix<uint64_t> a({0xffffffffffffffff}, m);
  clike::integer_radix<uint64_t> b({0x01}, m);

  clike::integer_radix<uint64_t> diff = a - b;
  ASSERT_EQ(1, diff.digits_.size());
  EXPECT_EQ(0xfffffffffffffffe, diff.digits_.at(0));
}

TEST(integer, sub_64bit_carry_2) {
  std::vector<uint64_t> m = {0x00, 0x00, 0x01};
  clike::integer_radix<uint64_t> a({0x00, 0x01}, m);
  clike::integer_radix<uint64_t> b({0x01}, m);

  clike::integer_radix<uint64_t> diff = a - b;
  ASSERT_EQ(1, diff.digits_.size());
  EXPECT_EQ(0xffffffffffffffff, diff.digits_.at(0));
}

TEST(integer, inv_64bit) {
  std::vector<uint64_t> m = {0x00, 0x00, 0x01};
  clike::integer_radix<uint64_t> b({0x00, 0x01}, m);

  clike::integer_radix<uint64_t> inv_b = -b;
  clike::integer_radix<uint64_t> z = b + inv_b;

  EXPECT_TRUE(z.is_zero());
}

TEST(integer, div_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x03;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_5) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xdeadbeef;
  uint32_t in_b = 0x1111;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_6) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x1111;
  uint32_t in_b = 0xdeadbeef;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_7) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xdeadbeef;
  uint32_t in_b = 0x11;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_8bit_8) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x8000;
  uint32_t in_b = 0x04;
  std::vector<uint8_t> out_ref = int_to_vec(in_a / in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a / b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, div_64bit) {
  std::vector<uint64_t> m = {0x00, 0x01};
  clike::integer_radix<uint64_t> a({0x88888888}, m);
  clike::integer_radix<uint64_t> b({0x88}, m);

  clike::integer_radix<uint64_t> r = a / b;
  ASSERT_EQ(1, r.digits_.size());

  uint64_t ref_value = 0x88888888 / 0x88;
  EXPECT_EQ(ref_value, r.digits_.at(0));
}

TEST(integer, mod_8bit) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x03;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_2) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x01;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_3) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0x02;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_4) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xff;
  uint32_t in_b = 0xff;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_5) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xdeadbeef;
  uint32_t in_b = 0x1111;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_6) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x1111;
  uint32_t in_b = 0xdeadbeef;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_7) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0xdeadbeef;
  uint32_t in_b = 0x11;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_8bit_8) {
  std::vector<uint8_t> m = {0x00, 0x00, 0x00, 0x00, 0x01};

  uint32_t in_a = 0x8000;
  uint32_t in_b = 0x04;
  std::vector<uint8_t> out_ref = int_to_vec(in_a % in_b);

  clike::integer_radix<uint8_t> a(int_to_vec(in_a), m);
  clike::integer_radix<uint8_t> b(int_to_vec(in_b), m);
  clike::integer_radix<uint8_t> c = a % b;

  ASSERT_EQ(out_ref.size(), c.digits_.size());
  for (size_t i = 0; i < out_ref.size(); ++i) {
    EXPECT_EQ(out_ref.at(i), c.digits_.at(i));
  }
}

TEST(integer, mod_64bit) {
  std::vector<uint64_t> m = {0x00, 0x01};
  clike::integer_radix<uint64_t> a({0x88888888}, m);
  clike::integer_radix<uint64_t> b({0x88}, m);

  clike::integer_radix<uint64_t> r = a % b;
  ASSERT_EQ(0, r.digits_.size());
}

TEST(integer, pow_8bit) {
  size_t e = 17;
  std::vector<uint8_t> m = {uint8_t(e)};
  std::vector<uint8_t> n = {uint8_t(e - 1)};

  for (size_t i = 1; i < e; ++i) {
    clike::integer_radix<uint8_t> g({uint8_t(i)}, m);
    clike::integer_radix<uint8_t> r = g.pow(n);

    ASSERT_EQ(1, r.digits_.size());
    EXPECT_EQ(1, r.digits_.at(0));
  }
}

TEST(integer, pow_8bit_2) {
  std::vector<uint8_t> p = {
    0xe6, 0xc4, 0x3a, 0x69, 0x93, 0x13, 0x00, 0x57
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint8_t> n = p;
  n[0] -= 1;

  std::vector<uint8_t> i_vec(1);
  i_vec[0] = 123;

  clike::integer_radix<uint8_t> g(i_vec, p);
  clike::integer_radix<uint8_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_16bit) {
  std::vector<uint16_t> p = {
    0x9150, 0x4893, 0x3c50, 0xabf6, 0x18a9, 0x6fb4, 0x5a48, 0x3b2f
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint16_t> n = p;
  n[0] -= 1;

  std::vector<uint16_t> i_vec(1);
  i_vec[0] = 123;

  clike::integer_radix<uint16_t> g(i_vec, p);
  clike::integer_radix<uint16_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_32bit) {
  std::vector<uint32_t> p = {
    0x98399524, 0x3bcf8e38, 0x3425173b, 0xc687ec15
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint32_t> n = p;
  n[0] -= 1;

  std::vector<uint32_t> i_vec(1);
  i_vec[0] = 123;

  clike::integer_radix<uint32_t> g(i_vec, p);
  clike::integer_radix<uint32_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit) {
  std::vector<uint64_t> p = {
    0xb707ea8278da5ff7, 0xa2f30dfd93b2cc0d
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 1;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 123;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit_2) {
  std::vector<uint64_t> p = {
    0x9632790564697fd5, 0x629e64d1e683807a, 0x63427fc38174cfab
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 1;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 123;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit_3) {
  std::vector<uint64_t> p = {
    0xb707ea8278da5ff7, 0xa2f30dfd93b2cc0d
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 1;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 3;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit_4) {
  std::vector<uint64_t> p = {
    0x46a0ba3a952a283f, 0x1bdb3e66f75a3aff
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 1;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 3;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit_5) {
  std::vector<uint64_t> p = {
    0x2bbfc65dc798accf, 0xb1920f5f2c19815d
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 1;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 3;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> r = g.pow(n);

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, pow_64bit_6) {
  std::vector<uint64_t> p = {
    0xe8790a90e, 0x71ebe589baaad50f
  };

  std::reverse(std::begin(p), std::end(p));

  std::vector<uint64_t> n = p;
  n[0] -= 2;

  std::vector<uint64_t> i_vec(1);
  i_vec[0] = 2;

  clike::integer_radix<uint64_t> g(i_vec, p);
  clike::integer_radix<uint64_t> inv_g = g.pow(n);

  clike::integer_radix<uint64_t> r = g * inv_g;

  ASSERT_EQ(1, r.digits_.size());
  EXPECT_EQ(1, r.digits_.at(0));
}

TEST(integer, mod2_add) {
  for (uint64_t i = 0; i < 2; ++i) {
    for (uint64_t j = 0; j < 2; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {2});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {2});
      clike::integer_radix<uint64_t> r = a + b;
      uint64_t ref_result = (i + j) % 2;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, mod2_sub) {
  for (uint64_t i = 0; i < 2; ++i) {
    for (uint64_t j = 0; j < 2; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {2});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {2});
      clike::integer_radix<uint64_t> r = a - b;
      uint64_t ref_result = (2 + i - j) % 2;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, mod2_mul) {
  for (uint64_t i = 0; i < 2; ++i) {
    for (uint64_t j = 0; j < 2; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {2});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {2});
      clike::integer_radix<uint64_t> r = a * b;
      uint64_t ref_result = (i * j) % 2;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, mod3_add) {
  for (uint64_t i = 0; i < 3; ++i) {
    for (uint64_t j = 0; j < 3; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {3});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {3});
      clike::integer_radix<uint64_t> r = a + b;
      uint64_t ref_result = (i + j) % 3;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, mod3_sub) {
  for (uint64_t i = 0; i < 3; ++i) {
    for (uint64_t j = 0; j < 3; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {3});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {3});
      clike::integer_radix<uint64_t> r = a - b;
      uint64_t ref_result = (3 + i - j) % 3;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, mod3_mul) {
  for (uint64_t i = 0; i < 3; ++i) {
    for (uint64_t j = 0; j < 3; ++j) {
      clike::integer_radix<uint64_t> a(int_to_vec_64(i), {3});
      clike::integer_radix<uint64_t> b(int_to_vec_64(j), {3});
      clike::integer_radix<uint64_t> r = a * b;
      uint64_t ref_result = (i * j) % 3;
      if (ref_result == 0) {
        ASSERT_EQ(0, r.digits_.size());
      } else {
        ASSERT_EQ(1, r.digits_.size());
        EXPECT_EQ(ref_result, r.digits_.at(0));
      }
    }
  }
}

TEST(integer, bitwise_or) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x1020305;
  uint64_t c2 = 0x0006075;
  uint64_t c3 = (c1 | c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_or(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
  EXPECT_EQ(0, c3_3); /* high word zero due to modulus */
}

TEST(integer, bitwise_or_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x0006075;
  uint64_t c2 = 0x1020305;
  uint64_t c3 = (c1 | c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_or(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
  EXPECT_EQ(0, c3_3); /* high word zero due to modulus */
}

TEST(integer, bitwise_or_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 3;
  uint64_t c2 = 1;
  uint64_t c3 = (c1 | c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() == a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_or(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
}

TEST(integer, bitwise_xor) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x1020305;
  uint64_t c2 = 0x0006075;
  uint64_t c3 = (c1 ^ c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_xor(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
  EXPECT_EQ(0, c3_3); /* high word zero due to modulus */
}

TEST(integer, bitwise_xor_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x0006075;
  uint64_t c2 = 0x1020305;
  uint64_t c3 = (c1 ^ c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_xor(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
  EXPECT_EQ(0, c3_3); /* high word zero due to modulus */
}

TEST(integer, bitwise_xor_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 3;
  uint64_t c2 = 1;
  uint64_t c3 = (c1 ^ c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() == a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_xor(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
}

TEST(integer, bitwise_and) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x1020305;
  uint64_t c2 = 0x0006075;
  uint64_t c3 = (c1 & c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_and(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(0, c3_1);
  EXPECT_EQ(0, c3_2);
  EXPECT_EQ(0, c3_3);
}

TEST(integer, bitwise_and_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x0006075;
  uint64_t c2 = 0x1020305;
  uint64_t c3 = (c1 & c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;
  uint64_t c3_3 = (c3 >> 24) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() != a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_and(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(0, c3_1);
  EXPECT_EQ(0, c3_2);
  EXPECT_EQ(0, c3_3);
}

TEST(integer, bitwise_and_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 3;
  uint64_t c2 = 1;
  uint64_t c3 = (c1 & c2) % (uint64_t(1) << 24);
  uint64_t c3_0 = c3 & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);
  EXPECT_TRUE(a1.size() == a2.size());

  clike::integer_radix<uint8_t> a3 = a1.bitwise_and(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
}

TEST(integer, equal) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 3;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 == a2);
}

TEST(integer, equal_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 == a2);
}

TEST(integer, equal_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xaa;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 == a2);
}

TEST(integer, equal_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 == a2);
}

TEST(integer, not_equal) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 3;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 != a2);
}

TEST(integer, not_equal_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 != a2);
}

TEST(integer, not_equal_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xaa;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 != a2);
}

TEST(integer, not_equal_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 != a2);
}

TEST(integer, operator_lt) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 < a2);
}

TEST(integer, operator_lt_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 < a2);
}

TEST(integer, operator_lt_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 < a2);
}

TEST(integer, operator_lt_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 < a2);
}

TEST(integer, operator_lt_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 < a2);
}

TEST(integer, operator_lt_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 < a2);
}

TEST(integer, operator_gt) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 > a2);
}

TEST(integer, operator_gt_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 > a2);
}

TEST(integer, operator_gt_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 > a2);
}

TEST(integer, operator_gt_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 > a2);
}

TEST(integer, operator_gt_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 > a2);
}

TEST(integer, operator_gt_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 > a2);
}

TEST(integer, operator_lte) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 <= a2);
}

TEST(integer, operator_lte_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 <= a2);
}

TEST(integer, operator_lte_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 <= a2);
}

TEST(integer, operator_lte_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 <= a2);
}

TEST(integer, operator_lte_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 <= a2);
}

TEST(integer, operator_lte_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 <= a2);
}

TEST(integer, operator_gte) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 >= a2);
}

TEST(integer, operator_gte_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 >= a2);
}

TEST(integer, operator_gte_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 >= a2);
}

TEST(integer, operator_gte_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0xdeadbeef;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_FALSE(a1 >= a2);
}

TEST(integer, operator_gte_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0xdeadbeef;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 >= a2);
}

TEST(integer, operator_gte_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  EXPECT_TRUE(a1 >= a2);
}

TEST(integer, operator_shl) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shl_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(0x11, a3.digits_.at(0));
  EXPECT_EQ(0xFF, a3.digits_.at(1));
  EXPECT_EQ(0x88, a3.digits_.at(2));
}

TEST(integer, operator_shl_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 3;
  uint64_t c3 = (c1 << c2);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
}

TEST(integer, operator_shl_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 23;
  uint64_t c3 = (c1 << c2);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
}

TEST(integer, operator_shl_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 24;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shl_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 25;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shl_7) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 999;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shl(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shr) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shr_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(0x11, a3.digits_.at(0));
  EXPECT_EQ(0xFF, a3.digits_.at(1));
  EXPECT_EQ(0x88, a3.digits_.at(2));
}

TEST(integer, operator_shr_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 3;
  uint64_t c3 = (c1 >> c2);
  uint64_t c3_0 = c3 & 0xff;
  uint64_t c3_1 = (c3 >> 8) & 0xff;
  uint64_t c3_2 = (c3 >> 16) & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
  EXPECT_EQ(c3_1, a3.digits_.at(1));
  EXPECT_EQ(c3_2, a3.digits_.at(2));
}

TEST(integer, operator_shr_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 23;
  uint64_t c3 = (c1 >> c2);
  uint64_t c3_0 = c3 & 0xff;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(c3_0, a3.digits_.at(0));
}

TEST(integer, operator_shr_5) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 24;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shr_6) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 25;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_shr_7) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0x88FF11;
  uint64_t c2 = 999;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1.bitwise_shr(a2);
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_add) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 + a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_add_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 + a2;
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(1, a3.digits_.at(0));
}

TEST(integer, operator_add_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 + a2;
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(1, a3.digits_.at(0));
}

TEST(integer, operator_add_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 + a2;
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(2, a3.digits_.at(0));
}

TEST(integer, operator_sub) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 - a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_sub_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 - a2;
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(1, a3.digits_.at(0));
}

TEST(integer, operator_sub_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 - a2;
  ASSERT_EQ(3, a3.digits_.size());
  EXPECT_EQ(0xff, a3.digits_.at(0));
  EXPECT_EQ(0xff, a3.digits_.at(1));
  EXPECT_EQ(0xff, a3.digits_.at(2));
}

TEST(integer, operator_sub_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 - a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_mul) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 * a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_mul_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 0;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 * a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_mul_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 * a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_mul_4) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 1;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 * a2;
  ASSERT_EQ(1, a3.digits_.size());
  EXPECT_EQ(1, a3.digits_.at(0));
}

TEST(integer, operator_div_zero) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 / a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, operator_mod_zero) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c1 = 0;
  uint64_t c2 = 1;

  clike::integer_radix<uint8_t> a1(int_to_vec(c1), m);
  clike::integer_radix<uint8_t> a2(int_to_vec(c2), m);

  clike::integer_radix<uint8_t> a3 = a1 % a2;
  ASSERT_EQ(0, a3.digits_.size());
}

TEST(integer, unary_minus) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 0;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = -a;
  ASSERT_EQ(0, b.digits_.size());
}

TEST(integer, unary_minus_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 1;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = -a;
  ASSERT_EQ(3, b.digits_.size());
  EXPECT_EQ(0xFF, b.digits_.at(0));
  EXPECT_EQ(0xFF, b.digits_.at(1));
  EXPECT_EQ(0xFF, b.digits_.at(2));
}

TEST(integer, unary_minus_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 0xFFFFFF;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = -a;
  ASSERT_EQ(1, b.digits_.size());
  EXPECT_EQ(1, b.digits_.at(0));
}

TEST(integer, unary_bitwise_negate) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 0;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = a.unary_bitwise_negate();
  ASSERT_EQ(3, b.digits_.size());
  EXPECT_EQ(0xFF, b.digits_.at(0));
  EXPECT_EQ(0xFF, b.digits_.at(1));
  EXPECT_EQ(0xFF, b.digits_.at(2));
}

TEST(integer, unary_bitwise_negate_2) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 0xFFFFFF;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = a.unary_bitwise_negate();
  ASSERT_EQ(0, b.digits_.size());
}

TEST(integer, unary_bitwise_negate_3) {
  std::vector<uint8_t> m = {
    0, 0, 0, 1
  };

  uint64_t c = 0xA5A5A5;

  clike::integer_radix<uint8_t> a(int_to_vec(c), m);

  clike::integer_radix<uint8_t> b = a.unary_bitwise_negate();
  ASSERT_EQ(3, b.digits_.size());
  EXPECT_EQ(0x5A, b.digits_.at(0));
  EXPECT_EQ(0x5A, b.digits_.at(1));
  EXPECT_EQ(0x5A, b.digits_.at(2));
}

TEST(integer, unary_bitwise_negate_4) {
  std::vector<uint8_t> m = {
    2
  };

  clike::integer_radix<uint8_t> a(int_to_vec(0), m);

  clike::integer_radix<uint8_t> b = a.unary_bitwise_negate();
  ASSERT_EQ(1, b.digits_.size());
  EXPECT_EQ(1, b.digits_.at(0));
}

TEST(integer, unary_bitwise_negate_5) {
  std::vector<uint8_t> m = {
    2
  };

  clike::integer_radix<uint8_t> a(int_to_vec(1), m);

  clike::integer_radix<uint8_t> b = a.unary_bitwise_negate();
  ASSERT_EQ(0, b.digits_.size());
}
