CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lm
PYLON_ROOT ?= /opt/pylon
CPPFLAGS += $(shell $(PYLON_ROOT)/bin/pylon-config --cflags)
CPPFLAGS += -I/usr/local/include/opencv4
LDFLAGS += $(shell $(PYLON_ROOT)/bin/pylon-config --libs-rpath)
LDLIBS += $(shell $(PYLON_ROOT)/bin/pylon-config --libs) -lm -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

program: projectile_guidance.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) -o program projectile_guidance.cpp $(LDFLAGS) $(LDLIBS)

clean:
	rm -f program

