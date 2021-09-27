export CXX=i686-w64-mingw32-g++

TARGET=aimpy-bridge.dll
SRCS=DllMain Thread ServerThread ClientThread Console AimpMessageHook AimpPluginCore

OUT=bin

OBJS := $(patsubst %,$(OUT)/%.o, $(SRCS))
TARGET := $(OUT)/$(TARGET)

INCLUDES := -I$(CURDIR) -Iaimp_sdk
export CXXFLAGS=-MD -Os -s -luuid

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ -shared $^ $(CXXFLAGS) -Wl,--kill-at

$(OUT)/%.o: %.cpp
	$(CXX) -c -o $@ $^ $(CXXFLAGS) $(INCLUDES)

clean:
	rm -f bin/*.o bin/*.d bin/*.exe bin/*.dll

.PHONY: all clean
