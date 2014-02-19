
add_library(aws aws4c.c)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(aws ${CURL_LIBRARIES})

find_package(Crypto REQUIRED)
include_directories(${CRYPTO_INCLUDE_DIR})
target_link_libraries(aws ${CRYPTO_LIBRARIES})

