cmake_minimum_required(VERSION 3.20)
project(crypto_exchange_api_wrapper)

set(CMAKE_CXX_STANDARD 14)
find_package( Boost 1.71 REQUIRED system )
find_package( cpprestsdk REQUIRED )
find_package( Poco REQUIRED COMPONENTS Crypto )
add_executable(crypto_exchange_api_wrapper main.cpp)
target_link_libraries(crypto_exchange_api_wrapper PRIVATE cpprestsdk::cpprest Boost::system Poco::Crypto)