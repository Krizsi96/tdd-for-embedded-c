#This makefile makes the examples from the first few chapters with Unity test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = BookCode_Unity
BUILD_DIR = build

#--- Inputs ----#
UNITY_HOME = Unity
CC = gcc
PROJECT_HOME_DIR = .
PROJECT_TEST_DIR = test


UNITY_CFLAGS += -Wno-missing-prototypes
UNITY_WARNINGFLAGS += -Wall
UNITY_WARNINGFLAGS += -Werror
UNITY_WARNINGFLAGS += -Wswitch-default

INCLUDE_DIRS = \
	-I$(PROJECT_HOME_DIR)/include\
	-I$(UNITY_HOME)/src\
	-I$(UNITY_HOME)/extras/fixture/src\
	-I$(UNITY_HOME)/extras/memory/src\
	-I$(PROJECT_TEST_DIR)/mocks

BINARIES = \
	unity\
	unity_fixture\
	unity_memory\
	all_tests\
	led_driver\
	led_driver_test\
	led_driver_test_runner\
	runtime_error_stub\

all: $(BUILD_DIR) $(BUILD_DIR)/$(COMPONENT_NAME)

clean:
	$(SILENCE)rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	$(SILENCE)mkdir $@

$(BUILD_DIR)/$(COMPONENT_NAME): $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(BINARIES)))
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) -o $@ $^

$(BUILD_DIR)/unity.o: $(UNITY_HOME)/src/unity.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/unity_fixture.o: $(UNITY_HOME)/extras/fixture/src/unity_fixture.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/unity_memory.o: $(UNITY_HOME)/extras/memory/src/unity_memory.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/all_tests.o: $(PROJECT_TEST_DIR)/all_tests.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/led_driver.o: $(PROJECT_HOME_DIR)/src/led_driver/led_driver.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/led_driver_test.o: $(PROJECT_TEST_DIR)/led_driver/led_driver_test.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/led_driver_test_runner.o: $(PROJECT_TEST_DIR)/led_driver/led_driver_test_runner.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^

$(BUILD_DIR)/runtime_error_stub.o: $(PROJECT_TEST_DIR)/mocks/runtime_error_stub.c
	$(SILENCE)$(CC) $(UNITY_CFLAGS) $(UNITY_WARNINGFLAGS) $(INCLUDE_DIRS) -c -o $@ $^