include(FetchContent)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.48.0  # e.g v1.28.0
        USES_TERMINAL_DOWNLOAD ON
)
set(FETCHCONTENT_QUIET OFF)

if(NOT gRPC_POPULATED)
    FetchContent_Populate(gRPC)
    add_subdirectory(
            ${grpc_SOURCE_DIR}
            ${grpc_BINARY_DIR}
            EXCLUDE_FROM_ALL)
endif()


# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()