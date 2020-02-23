TARGET_EXEC ?= main.exe

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src/main
JSONS ?= ./*.json
TXT ?= ./*.txt
CSV ?= ./*.csv

CXX := -c++

LDFLAGS := -L/usr/lib -lstdc++ -lcurl -lm -lfltk -lfltk_images -lpng -lX11 -ldl -lXrender -lXcursor -lXfixes -lXinerama -lXext -lXft -lfontconfig -lpthread


SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

GTKINC := `pkg-config --cflags gtk+-3.0 gtkmm-3.0 webkitgtk-3.0`
GTKLIB := `pkg-config --libs gtk+-3.0 gtkmm-3.0 webkitgtk-3.0`

WEBVIEW_CFLAGS := -DWEBVIEW_GTK=1 $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.0)
WEBVIEW_LDFLAGS := $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.0)

INC_DIRS ?= ./include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(WEBVIEW_CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(WEBVIEW_LDFLAGS)

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
