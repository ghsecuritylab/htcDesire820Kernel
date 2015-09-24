// Copyright 2005, Google Inc.
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_H_


#include <gtest/internal/gtest-internal.h>
#include <gtest/internal/gtest-string.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest-message.h>
#include <gtest/gtest_prod.h>


namespace testing {

const int kMaxStackTraceDepth = 100;

GTEST_DECLARE_int32(stack_trace_depth);

GTEST_DECLARE_bool(show_internal_stack_frames);

enum TestPartResultType {
  TPRT_SUCCESS,           
  TPRT_NONFATAL_FAILURE,  
  TPRT_FATAL_FAILURE      
};

namespace internal {

class GTestFlagSaver;

template <typename T>
String StreamableToString(const T& streamable) {
  return (Message() << streamable).GetString();
}

}  

class AssertionResult {
 public:
  
  
  friend AssertionResult AssertionSuccess();
  friend AssertionResult AssertionFailure(const Message&);

  
  operator bool() const { return failure_message_.c_str() == NULL; }  

  
  const char* failure_message() const { return failure_message_.c_str(); }

 private:
  
  AssertionResult() {}

  
  explicit AssertionResult(const internal::String& failure_message);

  
  internal::String failure_message_;
};

AssertionResult AssertionSuccess();

AssertionResult AssertionFailure(const Message& msg);

class Test {
 public:
  friend class internal::TestInfoImpl;

  
  
  typedef void (*SetUpTestCaseFunc)();
  typedef void (*TearDownTestCaseFunc)();

  
  virtual ~Test();

  
  static bool HasFatalFailure();

  
  
  
  
  
  
  
  
  
  
  
  
  static void RecordProperty(const char* key, const char* value);
  static void RecordProperty(const char* key, int value);

 protected:
  
  Test();

  
  
  
  
  
  
  static void SetUpTestCase() {}

  
  
  
  
  
  
  static void TearDownTestCase() {}

  
  virtual void SetUp();

  
  virtual void TearDown();

 private:
  
  
  static bool HasSameFixtureClass();

  
  
  
  
  
  
  virtual void TestBody() = 0;

  
  void Run();

  
  const internal::GTestFlagSaver* const gtest_flag_saver_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  struct Setup_should_be_spelled_SetUp {};
  virtual Setup_should_be_spelled_SetUp* Setup() { return NULL; }

  
  GTEST_DISALLOW_COPY_AND_ASSIGN(Test);
};


typedef Test* (*TestMaker)();


class TestInfo {
 public:
  
  
  ~TestInfo();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  static TestInfo* MakeAndRegisterInstance(
      const char* test_case_name,
      const char* name,
      internal::TypeId fixture_class_id,
      Test::SetUpTestCaseFunc set_up_tc,
      Test::TearDownTestCaseFunc tear_down_tc,
      TestMaker maker);

  
  const char* test_case_name() const;

  
  const char* name() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool should_run() const;

  
  const internal::TestResult* result() const;
 private:
#ifdef GTEST_HAS_DEATH_TEST
  friend class internal::DefaultDeathTestFactory;
#endif  
  friend class internal::TestInfoImpl;
  friend class internal::UnitTestImpl;
  friend class Test;
  friend class TestCase;

  
  
  int increment_death_test_count();

  
  internal::TestInfoImpl* impl() { return impl_; }
  const internal::TestInfoImpl* impl() const { return impl_; }

  
  TestInfo(const char* test_case_name, const char* name,
           internal::TypeId fixture_class_id, TestMaker maker);

  
  internal::TestInfoImpl* impl_;

  GTEST_DISALLOW_COPY_AND_ASSIGN(TestInfo);
};

class Environment {
 public:
  
  virtual ~Environment() {}

  
  virtual void SetUp() {}

  
  virtual void TearDown() {}
 private:
  
  
  struct Setup_should_be_spelled_SetUp {};
  virtual Setup_should_be_spelled_SetUp* Setup() { return NULL; }
};

class UnitTest {
 public:
  
  
  
  static UnitTest* GetInstance();

  
  
  
  
  
  
  
  
  
  Environment* AddEnvironment(Environment* env);

  
  
  
  
  
  
  void AddTestPartResult(TestPartResultType result_type,
                         const char* file_name,
                         int line_number,
                         const internal::String& message,
                         const internal::String& os_stack_trace);

  
  
  void RecordPropertyForCurrentTest(const char* key, const char* value);

  
  
  
  
  
  
  int Run() GTEST_MUST_USE_RESULT;

  
  
  const TestCase* current_test_case() const;

  
  
  const TestInfo* current_test_info() const;

  
  internal::UnitTestImpl* impl() { return impl_; }
  const internal::UnitTestImpl* impl() const { return impl_; }
 private:
  
  
  friend class internal::ScopedTrace;

  
  UnitTest();

  
  virtual ~UnitTest();

  
  
  void PushGTestTrace(const internal::TraceInfo& trace);

  
  void PopGTestTrace();

  
  
  mutable internal::Mutex mutex_;

  
  
  
  
  internal::UnitTestImpl* impl_;

  
  GTEST_DISALLOW_COPY_AND_ASSIGN(UnitTest);
};

inline Environment* AddGlobalTestEnvironment(Environment* env) {
  return UnitTest::GetInstance()->AddEnvironment(env);
}

void InitGoogleTest(int* argc, char** argv);

#ifdef GTEST_OS_WINDOWS
void InitGoogleTest(int* argc, wchar_t** argv);
#endif  

namespace internal {

#if GTEST_HAS_STD_STRING
inline String FormatForFailureMessage(const ::std::string& str) {
  return (Message() << '"' << str << '"').GetString();
}
#endif  

#if GTEST_HAS_STD_WSTRING
inline String FormatForFailureMessage(const ::std::wstring& wstr) {
  return (Message() << "L\"" << wstr << '"').GetString();
}
#endif  

#if GTEST_HAS_GLOBAL_STRING
inline String FormatForFailureMessage(const ::string& str) {
  return (Message() << '"' << str << '"').GetString();
}
#endif  

#if GTEST_HAS_GLOBAL_WSTRING
inline String FormatForFailureMessage(const ::wstring& wstr) {
  return (Message() << "L\"" << wstr << '"').GetString();
}
#endif  

template <typename T1, typename T2>
String FormatForComparisonFailureMessage(const T1& value,
                                         const T2& ) {
  return FormatForFailureMessage(value);
}

template <typename T1, typename T2>
AssertionResult CmpHelperEQ(const char* expected_expression,
                            const char* actual_expression,
                            const T1& expected,
                            const T2& actual) {
  if (expected == actual) {
    return AssertionSuccess();
  }

  return EqFailure(expected_expression,
                   actual_expression,
                   FormatForComparisonFailureMessage(expected, actual),
                   FormatForComparisonFailureMessage(actual, expected),
                   false);
}

AssertionResult CmpHelperEQ(const char* expected_expression,
                            const char* actual_expression,
                            BiggestInt expected,
                            BiggestInt actual);

template <bool lhs_is_null_literal>
class EqHelper {
 public:
  
  template <typename T1, typename T2>
  static AssertionResult Compare(const char* expected_expression,
                                 const char* actual_expression,
                                 const T1& expected,
                                 const T2& actual) {
    return CmpHelperEQ(expected_expression, actual_expression, expected,
                       actual);
  }

  
  
  
  
  
  
  static AssertionResult Compare(const char* expected_expression,
                                 const char* actual_expression,
                                 BiggestInt expected,
                                 BiggestInt actual) {
    return CmpHelperEQ(expected_expression, actual_expression, expected,
                       actual);
  }
};

template <>
class EqHelper<true> {
 public:
  
  
  
  
  template <typename T1, typename T2>
  static AssertionResult Compare(const char* expected_expression,
                                 const char* actual_expression,
                                 const T1& expected,
                                 const T2& actual) {
    return CmpHelperEQ(expected_expression, actual_expression, expected,
                       actual);
  }

  
  
  template <typename T1, typename T2>
  static AssertionResult Compare(const char* expected_expression,
                                 const char* actual_expression,
                                 const T1& expected,
                                 T2* actual) {
    
    return CmpHelperEQ(expected_expression, actual_expression,
                       static_cast<T2*>(NULL), actual);
  }
};

#define GTEST_IMPL_CMP_HELPER(op_name, op)\
template <typename T1, typename T2>\
AssertionResult CmpHelper##op_name(const char* expr1, const char* expr2, \
                                   const T1& val1, const T2& val2) {\
  if (val1 op val2) {\
    return AssertionSuccess();\
  } else {\
    Message msg;\
    msg << "Expected: (" << expr1 << ") " #op " (" << expr2\
        << "), actual: " << FormatForComparisonFailureMessage(val1, val2)\
        << " vs " << FormatForComparisonFailureMessage(val2, val1);\
    return AssertionFailure(msg);\
  }\
}\
AssertionResult CmpHelper##op_name(const char* expr1, const char* expr2, \
                                   BiggestInt val1, BiggestInt val2);


GTEST_IMPL_CMP_HELPER(NE, !=)
GTEST_IMPL_CMP_HELPER(LE, <=)
GTEST_IMPL_CMP_HELPER(LT, < )
GTEST_IMPL_CMP_HELPER(GE, >=)
GTEST_IMPL_CMP_HELPER(GT, > )

#undef GTEST_IMPL_CMP_HELPER

AssertionResult CmpHelperSTREQ(const char* expected_expression,
                               const char* actual_expression,
                               const char* expected,
                               const char* actual);

AssertionResult CmpHelperSTRCASEEQ(const char* expected_expression,
                                   const char* actual_expression,
                                   const char* expected,
                                   const char* actual);

AssertionResult CmpHelperSTRNE(const char* s1_expression,
                               const char* s2_expression,
                               const char* s1,
                               const char* s2);

AssertionResult CmpHelperSTRCASENE(const char* s1_expression,
                                   const char* s2_expression,
                                   const char* s1,
                                   const char* s2);


AssertionResult CmpHelperSTREQ(const char* expected_expression,
                               const char* actual_expression,
                               const wchar_t* expected,
                               const wchar_t* actual);

AssertionResult CmpHelperSTRNE(const char* s1_expression,
                               const char* s2_expression,
                               const wchar_t* s1,
                               const wchar_t* s2);

}  

AssertionResult IsSubstring(
    const char* needle_expr, const char* haystack_expr,
    const char* needle, const char* haystack);
AssertionResult IsSubstring(
    const char* needle_expr, const char* haystack_expr,
    const wchar_t* needle, const wchar_t* haystack);
AssertionResult IsNotSubstring(
    const char* needle_expr, const char* haystack_expr,
    const char* needle, const char* haystack);
AssertionResult IsNotSubstring(
    const char* needle_expr, const char* haystack_expr,
    const wchar_t* needle, const wchar_t* haystack);
#if GTEST_HAS_STD_STRING
AssertionResult IsSubstring(
    const char* needle_expr, const char* haystack_expr,
    const ::std::string& needle, const ::std::string& haystack);
AssertionResult IsNotSubstring(
    const char* needle_expr, const char* haystack_expr,
    const ::std::string& needle, const ::std::string& haystack);
#endif  

#if GTEST_HAS_STD_WSTRING
AssertionResult IsSubstring(
    const char* needle_expr, const char* haystack_expr,
    const ::std::wstring& needle, const ::std::wstring& haystack);
AssertionResult IsNotSubstring(
    const char* needle_expr, const char* haystack_expr,
    const ::std::wstring& needle, const ::std::wstring& haystack);
#endif  

namespace internal {

template <typename RawType>
AssertionResult CmpHelperFloatingPointEQ(const char* expected_expression,
                                         const char* actual_expression,
                                         RawType expected,
                                         RawType actual) {
  const FloatingPoint<RawType> lhs(expected), rhs(actual);

  if (lhs.AlmostEquals(rhs)) {
    return AssertionSuccess();
  }

  StrStream expected_ss;
  expected_ss << std::setprecision(std::numeric_limits<RawType>::digits10 + 2)
              << expected;

  StrStream actual_ss;
  actual_ss << std::setprecision(std::numeric_limits<RawType>::digits10 + 2)
            << actual;

  return EqFailure(expected_expression,
                   actual_expression,
                   StrStreamToString(&expected_ss),
                   StrStreamToString(&actual_ss),
                   false);
}

AssertionResult DoubleNearPredFormat(const char* expr1,
                                     const char* expr2,
                                     const char* abs_error_expr,
                                     double val1,
                                     double val2,
                                     double abs_error);

class AssertHelper {
 public:
  
  AssertHelper(TestPartResultType type, const char* file, int line,
               const char* message);
  
  
  void operator=(const Message& message) const;
 private:
  TestPartResultType const type_;
  const char*        const file_;
  int                const line_;
  String             const message_;

  GTEST_DISALLOW_COPY_AND_ASSIGN(AssertHelper);
};

}  



#define ADD_FAILURE() GTEST_NONFATAL_FAILURE("Failed")

#define FAIL() GTEST_FATAL_FAILURE("Failed")

#define SUCCEED() GTEST_SUCCESS("Succeeded")

#define EXPECT_TRUE(condition) \
  GTEST_TEST_BOOLEAN(condition, #condition, false, true, \
                     GTEST_NONFATAL_FAILURE)
#define EXPECT_FALSE(condition) \
  GTEST_TEST_BOOLEAN(!(condition), #condition, true, false, \
                     GTEST_NONFATAL_FAILURE)
#define ASSERT_TRUE(condition) \
  GTEST_TEST_BOOLEAN(condition, #condition, false, true, \
                     GTEST_FATAL_FAILURE)
#define ASSERT_FALSE(condition) \
  GTEST_TEST_BOOLEAN(!(condition), #condition, true, false, \
                     GTEST_FATAL_FAILURE)

#include <gtest/gtest_pred_impl.h>


#define EXPECT_EQ(expected, actual) \
  EXPECT_PRED_FORMAT2(::testing::internal:: \
                      EqHelper<GTEST_IS_NULL_LITERAL(expected)>::Compare, \
                      expected, actual)
#define EXPECT_NE(expected, actual) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperNE, expected, actual)
#define EXPECT_LE(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperLE, val1, val2)
#define EXPECT_LT(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperLT, val1, val2)
#define EXPECT_GE(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperGE, val1, val2)
#define EXPECT_GT(val1, val2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperGT, val1, val2)

#define ASSERT_EQ(expected, actual) \
  ASSERT_PRED_FORMAT2(::testing::internal:: \
                      EqHelper<GTEST_IS_NULL_LITERAL(expected)>::Compare, \
                      expected, actual)
#define ASSERT_NE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperNE, val1, val2)
#define ASSERT_LE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperLE, val1, val2)
#define ASSERT_LT(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperLT, val1, val2)
#define ASSERT_GE(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperGE, val1, val2)
#define ASSERT_GT(val1, val2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperGT, val1, val2)


#define EXPECT_STREQ(expected, actual) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTREQ, expected, actual)
#define EXPECT_STRNE(s1, s2) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRNE, s1, s2)
#define EXPECT_STRCASEEQ(expected, actual) \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASEEQ, expected, actual)
#define EXPECT_STRCASENE(s1, s2)\
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASENE, s1, s2)

#define ASSERT_STREQ(expected, actual) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTREQ, expected, actual)
#define ASSERT_STRNE(s1, s2) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRNE, s1, s2)
#define ASSERT_STRCASEEQ(expected, actual) \
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASEEQ, expected, actual)
#define ASSERT_STRCASENE(s1, s2)\
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperSTRCASENE, s1, s2)


#define EXPECT_FLOAT_EQ(expected, actual)\
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<float>, \
                      expected, actual)

#define EXPECT_DOUBLE_EQ(expected, actual)\
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, \
                      expected, actual)

#define ASSERT_FLOAT_EQ(expected, actual)\
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<float>, \
                      expected, actual)

#define ASSERT_DOUBLE_EQ(expected, actual)\
  ASSERT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<double>, \
                      expected, actual)

#define EXPECT_NEAR(val1, val2, abs_error)\
  EXPECT_PRED_FORMAT3(::testing::internal::DoubleNearPredFormat, \
                      val1, val2, abs_error)

#define ASSERT_NEAR(val1, val2, abs_error)\
  ASSERT_PRED_FORMAT3(::testing::internal::DoubleNearPredFormat, \
                      val1, val2, abs_error)


AssertionResult FloatLE(const char* expr1, const char* expr2,
                        float val1, float val2);
AssertionResult DoubleLE(const char* expr1, const char* expr2,
                         double val1, double val2);


#ifdef GTEST_OS_WINDOWS

#define EXPECT_HRESULT_SUCCEEDED(expr) \
    EXPECT_PRED_FORMAT1(::testing::internal::IsHRESULTSuccess, (expr))

#define ASSERT_HRESULT_SUCCEEDED(expr) \
    ASSERT_PRED_FORMAT1(::testing::internal::IsHRESULTSuccess, (expr))

#define EXPECT_HRESULT_FAILED(expr) \
    EXPECT_PRED_FORMAT1(::testing::internal::IsHRESULTFailure, (expr))

#define ASSERT_HRESULT_FAILED(expr) \
    ASSERT_PRED_FORMAT1(::testing::internal::IsHRESULTFailure, (expr))

#endif  


#define SCOPED_TRACE(message) \
  ::testing::internal::ScopedTrace GTEST_CONCAT_TOKEN(gtest_trace_, __LINE__)(\
    __FILE__, __LINE__, ::testing::Message() << (message))



#define TEST(test_case_name, test_name)\
  GTEST_TEST(test_case_name, test_name, ::testing::Test)



#define TEST_F(test_fixture, test_name)\
  GTEST_TEST(test_fixture, test_name, test_fixture)


#define RUN_ALL_TESTS()\
  (::testing::UnitTest::GetInstance()->Run())

}  

#endif  