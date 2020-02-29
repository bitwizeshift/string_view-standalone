
#include <bpstd/string_view.hpp>

#include <iostream>

int main()
{
  const auto sv = bpstd::string_view{"hello world"};
  std::cout << sv << std::endl;
  return 0;
}