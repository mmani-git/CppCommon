//
// Created by Ivan Shynkarenka on 10.02.2016.
//

#include "catch.hpp"

#include "errors/system_error.h"

using namespace CppCommon;

TEST_CASE("System error wrapper", "[CppCommon][Errors]")
{
    SystemError::SetLast(123);
    REQUIRE(SystemError::GetLast() == 123);
    SystemError::ClearLast();

    REQUIRE(SystemError::GetLast() == 0);

    REQUIRE(!SystemError::to_string().empty());
    REQUIRE(!SystemError::to_string(SystemError::GetLast()).empty());
}
