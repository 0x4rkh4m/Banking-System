.PHONY: all clean

BUILD_DIR = build

all: $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

$(BUILD_DIR):
	cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_C_COMPILER=gcc

clean:
	rm -rf $(BUILD_DIR)
