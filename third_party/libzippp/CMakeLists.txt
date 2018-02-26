set(zippp_SRCS
        libzippp.cpp
        )

add_library(zippp ${zippp_SRCS})
target_link_libraries(zippp zip z)