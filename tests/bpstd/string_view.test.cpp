/**
 * \file string_view.test.cpp
 *
 * \brief Unit tests for #bpstd::basic_string_view
 *
 * \author Matthew Rodusek (matthew.rodusek@gmail.com)
 */

#include "../catch.hpp"

#include <bpstd/string_view.hpp>
#include <string>
#include <cstring>

//----------------------------------------------------------------------------
// Constructors
//----------------------------------------------------------------------------

TEST_CASE("string_view::string_view()","[ctor]")
{
  bpstd::string_view view;
  SECTION("Constructs an empty string")
  {
    REQUIRE( view.empty() );
  }
  SECTION("Is 0 bytes in size")
  {
    REQUIRE( view.size() == 0 );
  }

  SECTION("Points to null")
  {
    REQUIRE( view.data() == nullptr );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::string_view( const std::string& )","[ctor]")
{
  std::string      str  = "Hello world";
  bpstd::string_view view = str;

  SECTION("Constructs a non-empty string")
  {
    REQUIRE_FALSE( view.empty() );
  }

  SECTION("Has non-zero size")
  {
    REQUIRE( view.size() != 0 );
  }

  SECTION("Points to original string")
  {
    REQUIRE( view.data() == str.data() );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::string_view( const char* )","[ctor]")
{
  const char* empty_str = "";
  const char* non_empty_str = "Hello World";

  SECTION("Is empty with empty string")
  {
    bpstd::string_view view = empty_str;

    REQUIRE( view.empty() );
  }

  SECTION("Is non-empty with non-empty string")
  {
    const char* str = "Hello world";
    bpstd::string_view view = non_empty_str;

    REQUIRE_FALSE( view.empty() );
  }

  SECTION("Is size 0 with empty string")
  {
    bpstd::string_view view = empty_str;

    REQUIRE( view.size() == 0 );
  }

  SECTION("Is not size 0 with non-empty string")
  {
    bpstd::string_view view = non_empty_str;

    REQUIRE( view.size() != 0 );
  }

  SECTION("Points to original string")
  {
    bpstd::string_view view = non_empty_str;

    REQUIRE( view.data() == non_empty_str );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::string_view( const char (&)[N] )", "[ctor]")
{
  bpstd::string_view empty = "";
  bpstd::string_view view  = "Hello world";

  SECTION("Is empty with empty string")
  {
    REQUIRE( empty.empty() );
  }

  SECTION("Is non-empty with non-empty string")
  {
    REQUIRE_FALSE( view.empty() );
  }

  SECTION("Is size 0 with empty string")
  {
    REQUIRE( empty.size() == 0 );
  }

  SECTION("Is not size 0 with non-empty string")
  {
    REQUIRE( view.size() != 0 );
  }
}

//----------------------------------------------------------------------------
// Capacity
//----------------------------------------------------------------------------

TEST_CASE("string_view::size", "[capacity]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Returns non-zero for non-empty string")
  {
    REQUIRE( view.size() == std::char_traits<char>::length(str) );
  }

  SECTION("Returns 0 for empty string")
  {
    view = "";

    REQUIRE( view.size() == 0 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::length", "[capacity]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Returns non-zero for non-empty string")
  {
    REQUIRE( view.length() == std::char_traits<char>::length(str) );
  }

  SECTION("Returns 0 for empty string")
  {
    view = "";

    REQUIRE( view.length() == 0 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::empty","[capacity]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Returns false on non-empty string")
  {
    REQUIRE_FALSE( view.empty() );
  }

  SECTION("Returns true on empty string")
  {
    view = "";

    REQUIRE( view.empty() );
  }
}

//----------------------------------------------------------------------------
// Element Access
//----------------------------------------------------------------------------

TEST_CASE("string_view::c_str()","[accessor]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Points to original data source")
  {
    REQUIRE( view.c_str() == str );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::data()","[accessor]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Points to original data source")
  {
    REQUIRE( view.data() == str );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::operator[](size_t n)","[accessor]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Returns reference to entry at position")
  {
    REQUIRE( &view[0] == str );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::at(size_t n)","[accessor]")
{
  const char* str = "Hello World";
  bpstd::string_view view = str;

  SECTION("Returns reference to entry at position")
  {
    REQUIRE( &view.at(0) == str );
  }

  SECTION("Throws when out of range")
  {
    REQUIRE_THROWS_AS( view.at(11), std::out_of_range );
  }

}

//----------------------------------------------------------------------------

TEST_CASE("string_view::front()","[accessor]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Returns reference to first character")
  {
    REQUIRE( view.front() == 'H' );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::back()","[accessor]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Returns reference to last character")
  {
    REQUIRE( view.back() == 'd' );
  }
}

//----------------------------------------------------------------------------
// Modifiers
//----------------------------------------------------------------------------

TEST_CASE("string_view::remove_prefix( size_type )","[modifier]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Removes first n characters")
  {
    view.remove_prefix(6);

    REQUIRE(view == "World");
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::remove_suffix( size_type )","[modifier]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Removes last n characters")
  {
    view.remove_suffix(6);

    REQUIRE(view == "Hello");
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::swap( string_view& )","[modifier]")
{
  const char* str1 = "Hello World";
  const char* str2 = "Goodbye World";
  bpstd::string_view view1 = str1;
  bpstd::string_view view2 = str2;

  SECTION("Swaps entries")
  {
    view1.swap(view2);

    REQUIRE( ((view1.data()==str2) && (view2.data()==str1)) );
  }
}

//----------------------------------------------------------------------------
// String Operations
//----------------------------------------------------------------------------

TEST_CASE("string_view::to_string()","[conversion]")
{
  bpstd::string_view view = "Hello World";

  std::string string = view.to_string();

  SECTION("Copies view to new location in std::string")
  {
    REQUIRE(view.data()!=string.data());
  }

  SECTION("Copied string contains same contents as view")
  {
    REQUIRE(string == "Hello World");
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::operator std::string()","[conversion]")
{
  bpstd::string_view view = "Hello World";

  std::string string = static_cast<std::string>(view);

  SECTION("Copies view to new location in std::string")
  {
    REQUIRE(view.data()!=string.data());
  }

  SECTION("Copied string contains same contents as view")
  {
    REQUIRE(string == "Hello World");
  }
}

//----------------------------------------------------------------------------
// Operations
//----------------------------------------------------------------------------

TEST_CASE("string_view::copy( char_type*, size_type, size_type )","[operation]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Throws std::out_of_range if pos >= view.size()")
  {
    char result[11];

    REQUIRE_THROWS_AS( view.copy(result,11,11), std::out_of_range );
  }

  SECTION("Copies entire string")
  {
    char result[11];
    view.copy(result,11);

    REQUIRE( std::strncmp(result,"Hello World",11)==0 );
  }

  SECTION("Copies remaining characters if count > size")
  {
    char result[11];
    view.copy(result,20);

    REQUIRE( std::strncmp(result,"Hello World",11)==0 );
  }

  SECTION("Copies part of the string")
  {
    char result[11];
    view.copy(result,5);

    REQUIRE( std::strncmp(result,"Hello",5)==0 );
  }

  SECTION("Copies part of the string, offset from the beginning")
  {
    char result[11];
    view.copy(result,10,6);

    REQUIRE( std::strncmp(result,"World",5)==0 );
  }

  SECTION("Returns number of characters copied")
  {
    char result[11];

    REQUIRE( view.copy(result,20)==11 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::substr( size_t, size_t )","[operation]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Returns the full string when given no args")
  {
    auto substr = view.substr();
    REQUIRE( substr=="Hello World" );
  }

  SECTION("Returns last part of string")
  {
    auto substr = view.substr(6);
    REQUIRE( substr=="World" );
  }

  SECTION("Substring returns at most count characters")
  {
    auto substr = view.substr(6,1);
    REQUIRE( substr=="W" );
  }

  SECTION("Returns up to end of string if length > size")
  {
    auto substr = view.substr(6,10);
    REQUIRE( substr=="World" );
  }

  SECTION("Throws std::out_of_range if pos > size")
  {
    REQUIRE_THROWS_AS( view.substr(15), std::out_of_range );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::compare( string_view )","[comparison]")
{
  SECTION("Returns 0 for identical views")
  {
    bpstd::string_view view = "Hello World";

    REQUIRE( view.compare("Hello World") == 0 );
  }

  SECTION("Returns nonzero for different views")
  {
    bpstd::string_view view = "Hello World";

    REQUIRE( view.compare("Goodbye World") != 0 );
  }

  SECTION("Returns > 0 for substring beginning with same string")
  {
    bpstd::string_view view = "Hello World";

    REQUIRE( view.compare("Hello") > 0 );
  }

  SECTION("Returns < 0 for superstring beginning with self")
  {
    bpstd::string_view view = "Hello";

    REQUIRE( view.compare("Hello World") < 0 );
  }

  SECTION("Returns < 0 for same-sized string compared to character greater than char")
  {
    bpstd::string_view view = "1234567";

    REQUIRE( view.compare("1234667") < 0 );
  }

  SECTION("Returns > 0 for same-sized string compared to character less than char")
  {
    bpstd::string_view view = "1234567";

    REQUIRE( view.compare("1234467") > 0 );
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::operator==(...)","[comparison]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Is equal")
  {
    SECTION("Returns true for equal string views")
    {
      bpstd::string_view view2 = "Hello World";

      REQUIRE( view == view2 );
    }

    SECTION("Returns true for equal strings with left char array")
    {
      REQUIRE( "Hello World" == view );
    }

    SECTION("Returns true for equal strings with right char array")
    {
      REQUIRE( view == "Hello World" );
    }

    SECTION("Returns true for equal strings with left char ptr")
    {
      const char* str = "Hello World";
      REQUIRE( str == view );
    }

    SECTION("Returns true for equal strings with right char ptr")
    {
      const char* str = "Hello World";
      REQUIRE( view == str );
    }

    SECTION("Returns true for equal strings with left std::string")
    {
      std::string str = "Hello World";
      REQUIRE( str == view );
    }

    SECTION("Returns true for equal strings with right std::string")
    {
      std::string str = "Hello World";
      REQUIRE( view == str );
    }

  }

  SECTION("Is not equal")
  {
    SECTION("Returns false for non-equal string views")
    {
      bpstd::string_view view2 = "Goodbye World";

      REQUIRE_FALSE( view == view2 );
    }

    SECTION("Returns false for non-equal strings with left char array")
    {
      REQUIRE_FALSE( "Goodbye World" == view );
    }

    SECTION("Returns false for non-equal strings with right char array")
    {
      REQUIRE_FALSE( view == "Goodbye World" );
    }

    SECTION("Returns false for non-equal strings with left char ptr")
    {
      const char* str = "Goodbye World";
      REQUIRE_FALSE( str == view );
    }

    SECTION("Returns false for non-equal strings with right char ptr")
    {
      const char* str = "Goodbye World";
      REQUIRE_FALSE( view == str );
    }

    SECTION("Returns false for non-equal strings with left std::string")
    {
      std::string str = "Goodbye World";
      REQUIRE_FALSE( str == view );
    }

    SECTION("Returns false for non-equal strings with right std::string")
    {
      std::string str = "Goodbye World";
      REQUIRE_FALSE( view == str );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::operator!=(...)","[compariso]")
{
  bpstd::string_view view = "Hello World";

  SECTION("Is equal")
  {
    SECTION("Returns false for equal string views")
    {
      bpstd::string_view view2 = "Hello World";

      REQUIRE_FALSE( view != view2 );
    }

    SECTION("Returns false for equal strings with left char array")
    {
      REQUIRE_FALSE( "Hello World" != view );
    }

    SECTION("Returns false for equal strings with right char array")
    {
      REQUIRE_FALSE( view != "Hello World" );
    }

    SECTION("Returns false for equal strings with left char ptr")
    {
      const char* str = "Hello World";
      REQUIRE_FALSE( str != view );
    }

    SECTION("Returns false for equal strings with right char ptr")
    {
      const char* str = "Hello World";
      REQUIRE_FALSE( view != str );
    }

    SECTION("Returns false for equal strings with left std::string")
    {
      std::string str = "Hello World";
      REQUIRE_FALSE( str != view );
    }

    SECTION("Returns false for equal strings with right std::string")
    {
      std::string str = "Hello World";
      REQUIRE_FALSE( view != str );
    }
  }

  SECTION("Is not equal")
  {
    SECTION("Returns true for non-equal string views")
    {
      bpstd::string_view view2 = "Goodbye World";

      REQUIRE( view != view2 );
    }

    SECTION("Returns true for non-equal strings with left char array")
    {
      REQUIRE( "Goodbye World" != view );
    }

    SECTION("Returns true for non-equal strings with right char array")
    {
      REQUIRE( view != "Goodbye World" );
    }

    SECTION("Returns true for non-equal strings with left char ptr")
    {
      const char* str = "Goodbye World";
      REQUIRE( str != view );
    }

    SECTION("Returns true for non-equal strings with right char ptr")
    {
      const char* str = "Goodbye World";
      REQUIRE( view != str );
    }

    SECTION("Returns true for non-equal strings with left std::string")
    {
      std::string str = "Goodbye World";
      REQUIRE( str != view );
    }

    SECTION("Returns true for non-equal strings with right std::string")
    {
      std::string str = "Goodbye World";
      REQUIRE( view != str );
    }
  }
}

//----------------------------------------------------------------------------

TEST_CASE("string_view::operator<(...)","[comparison]")
{

}

TEST_CASE("string_view::operator>(...)","[comparison]")
{

}
TEST_CASE("string_view::operator<=(...)","[comparison]")
{

}
TEST_CASE("string_view::operator>=(...)","[comparison]")
{

}

