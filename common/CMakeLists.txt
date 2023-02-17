project(appvm-manager-common)

find_package(Boost COMPONENTS REQUIRED)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER include/appvm-manager/common/protocol/Protocol.proto)

set(PROTOBUF_INCLUDE_DIRS ${PROTOBUF_INCLUDE_DIRS} PARENT_SCOPE)
set(PROTOBUF_LIBRARIES ${PROTOBUF_LIBRARIES} PARENT_SCOPE)
set(PROTO_SRC ${PROTO_SRC} PARENT_SCOPE)
set(PROTO_HEADER ${PROTO_HEADER} PARENT_SCOPE)

set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)

add_library(common SHARED
	src/helpers/CommonTypes.cpp
	src/transport/TcpClientTransport.cpp
	src/protocol/ProtobufClientProtocol.cpp
	${PROTO_SRC}
	${PROTO_HEADER}
)

file(COPY ${PROTO_HEADER}
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/appvm-manager/common/protocol)
message(${PROTO_HEADER})

target_include_directories(common
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
