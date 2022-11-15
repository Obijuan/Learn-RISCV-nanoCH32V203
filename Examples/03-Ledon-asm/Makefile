TARGET_NAME ?= app
TARGET_ELF  ?= $(TARGET_NAME).elf
TARGET_BIN  ?= $(TARGET_NAME).bin

AS := riscv-none-embed-gcc
CC := riscv-none-embed-gcc
OBJCOPY := riscv-none-embed-objcopy

BUILD_DIR ?= ./build

SRCS := startup_ch32v20x_D6.S 
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

FLAGS ?= -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore
ASFLAGS ?= $(FLAGS) -x assembler -MMD -MP
LDFLAGS ?= $(FLAGS) -T ./Link.ld -nostartfiles -Xlinker --gc-sections


$(BUILD_DIR)/$(TARGET_ELF): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(OBJCOPY) -Obinary $@ $(BUILD_DIR)/$(TARGET_BIN)

# assembly
$(BUILD_DIR)/%.S.o: %.S
	$(MKDIR_P) $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
