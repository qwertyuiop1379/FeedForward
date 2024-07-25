CXX = clang++

TARGET = feedforward
RUN_COMMAND = ./build/$(TARGET)

FRAMEWORKS = Foundation

CPPFLAGS = -g -Ofast -Wall -std=c++20 -I.
LDFLAGS = $(addprefix -framework ,$(FRAMEWORKS))

IGNORE_DIRECTORIES = .vscode build
ALL_DIERCTORIES = $(wildcard */)

MODULES = $(filter-out $(IGNORE_DIRECTORIES),$(ALL_DIERCTORIES))
CPPFILES = $(foreach MODULE,$(MODULES),$(wildcard $(MODULE)*.cpp))
OBJECTS = $(CPPFILES:.cpp=.o)

clean:
	@rm -rf build/obj
	@rm build/$(TARGET)

stage:
	@$(foreach MODULE,$(MODULES),mkdir -p build/obj/$(MODULE);)

%.o: %.cpp
	@echo =\> Compiling $<...
	@$(CXX) -c $< -o build/obj/$@ $(CPPFLAGS)

target: stage $(OBJECTS)
	@echo =\> Linking $(TARGET)...
	@$(CXX) $(addprefix build/obj/,$(OBJECTS)) -o build/$(TARGET) $(CPPFLAGS) $(LDFLAGS)

run:
	@echo =\> Running $(TARGET)...
	@./build/$(TARGET) $(RUN_COMMAND)

do: target run