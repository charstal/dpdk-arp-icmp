GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

all: 
	protoc -I./ --cpp_out ./ ns.proto --grpc_out ./ --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH)
