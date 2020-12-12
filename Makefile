# Build settings
OBJNAME :=    snek
DEVKIT_LOC := /opt/devkitpro
EMU_LOC :=    ../vba-migration/visualboyadvance-m/build/
CC :=         $(DEVKIT_LOC)/devkitARM/bin/arm-none-eabi-gcc
CFLAGS :=     -mthumb-interwork -mthumb -O2
LD :=         $(DEVKIT_LOC)/devkitARM/bin/arm-none-eabi-gcc
LDFLAGS :=    -mthumb-interwork -mthumb -specs=gba.specs
OBJCP :=      $(DEVKIT_LOC)/devkitARM/bin/arm-none-eabi-objcopy
OBJCPFLAGS := -v -O binary
FIXER :=      $(DEVKIT_LOC)/tools/bin/gbafix
SRCFLDR :=    src
OBJFLDR :=    obj
INCFLDR :=    include

# Auto-settings
SRC :=        $(wildcard $(SRCFLDR)/*.c)
OBJS :=       $(subst $(SRCFLDR),$(OBJFLDR),$(subst .c,.o,$(SRC)))
HFILES :=     $(wildcard $(INCFLDR)/*.h)
INC :=        -I$(INCFLDR)

# Helper targets
.PHONY : all
all : $(DEVKIT_LOC) $(OBJNAME).gba

.PHONY : clean
clean :
	rm -rf $(OBJNAME).gba
	rm -rf $(OBJFLDR)

.PHONY : emu
emu : $(OBJNAME).gba
	$(EMU_LOC)/visualboyadvance-m snek.gba

# Main targets
$(DEVKIT_LOC):
	sudo apt install -y wget build-essential
	wget https://github.com/devkitPro/pacman/releases/download/v1.0.2/devkitpro-pacman.amd64.deb
	sudo dpkg -i devkitpro-pacman.amd64.deb

$(OBJFLDR)/%.o : $(SRCFLDR)/%.c $(HFILES)
	mkdir -p $(OBJFLDR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJFLDR)/$(OBJNAME).elf : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@

$(OBJNAME).gba : $(OBJFLDR)/$(OBJNAME).elf
	$(OBJCP) $(OBJCPFLAGS) $< $@
	$(FIXER) $@
