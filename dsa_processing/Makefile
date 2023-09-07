CXX = /opt/homebrew/bin/g++-13
CXXFLAGS = -std=c++20

TARGET = main

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
