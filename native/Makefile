export CXX=i686-w64-mingw32-g++
export PROTOC=protoc

# target dependencies
TARGET=aimpy-bridge.dll
SRCS=DllMain Thread ServerThread ClientThread Console AimpMessageHook AimpPluginCore PacketConsumer PacketProducer
PROTOS=addressbook

OUT=bin
PROTO_DIR=../proto

OBJS := $(patsubst %,$(OUT)/%.o, $(SRCS))
PROTO_OBJS := $(patsubst %,$(OUT)/proto/%.o, $(PROTOS))
TARGET := $(OUT)/$(TARGET)

INCLUDES := -I$(CURDIR) -Iaimp_sdk -I$(OUT)/proto
export CXXFLAGS=-MD -Os -s -luuid -lprotobuf

all: $(TARGET)

# target rules

$(TARGET): $(OBJS) $(PROTO_OBJS)
	$(CXX) -o $@ -shared $^ $(CXXFLAGS) -Wl,--kill-at

# object compilation rules

$(OUT)/%.o: %.cpp | $(PROTO_OBJS)
	$(CXX) -c -o $@ $^ $(CXXFLAGS) $(INCLUDES)

$(OUT)/proto/%.pb.cc: $(PROTO_DIR)/%.proto
	$(PROTOC) -I$(PROTO_DIR) --cpp_out=$(OUT)/proto/ $^

$(OUT)/proto/%.o: $(OUT)/proto/%.pb.cc
	$(CXX) -c -o $@ $^ $(CXXFLAGS) $(INCLUDES)

# cleaning

clean:
	rm -f bin/*.o bin/*.d bin/*.exe bin/*.dll bin/proto/*.o bin/proto/*.d bin/proto/*.cc bin/proto/*.h

.PHONY: all clean
