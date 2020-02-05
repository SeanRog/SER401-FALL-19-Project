TARGET_EXEC ?= main.exe

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src/main
JSONS ?= ./*.json
TXT ?= ./*.txt
CSV ?= ./*.csv

CXX := -c++


LDFLAGS := -L/usr/lib `fltk-config --cxxflags` -lstdc++ -lcurl -pthread -lm `fltk-config --libs` -lfltk -lfltk_images -lpng -lftgl -lX11 -ldl -lXrender -lXcursor -lXfixes -lXinerama -lXext -lXft -lfontconfig -lpthread

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS ?= ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

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
