if(EXISTS "D:/Development/C++/SFML_GUI3/build/MyTests[1]_tests.cmake")
  include("D:/Development/C++/SFML_GUI3/build/MyTests[1]_tests.cmake")
else()
  add_test(MyTests_NOT_BUILT MyTests_NOT_BUILT)
endif()
