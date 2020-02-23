TARGET_EXEC ?= main.exe

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src/main
JSONS ?= ./*.json
TXT ?= ./*.txt
CSV ?= ./*.csv

CXX := -c++
CC := gcc

# Added webkit2gtk-4.0 for building with webkit2gtk
GTKLIB :=`pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`


LD :=gcc
LDFLAGS := -L/usr/lib -lstdc++ -lcurl -lgtk-3 -lgdk-3 -pthread -lm -lfltk -lfltk_images -lpng -lX11 -ldl -lXrender -lXcursor -lXfixes -lXinerama -lXext -lXft -lfontconfig -lpthread -export-dynamic


SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS ?= ./usr/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))



CPPFLAGS ?= $(INC_FLAGS) $(GTKLIB) -MMD -MP



$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(JSONS)
	$(RM) -r $(TXT)
	$(RM) -r $(CSV)

run:
	./build/main.exe $(ARGS)


-include $(DEPS)

MKDIR_P ?= mkdir -p
