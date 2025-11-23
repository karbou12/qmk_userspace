VIA_ENABLE = yes
VIAL_ENABLE = yes

CAPS_WORD_ENABLE = yes
OS_DETECTION_ENABLE = yes
CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY = yes
CONSOLE_ENABLE = yes

SRC += $(USER_PATH)/karbou12.c \
       $(USER_PATH)/us_utils.c \
       $(USER_PATH)/us_status.c \
       $(USER_PATH)/us_eeconfig.c

ifeq ($(strip $(CUSTOM_RGBLIGHT)), yes)
	SRC += $(USER_PATH)/us_rgb.c
endif

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
	SRC += $(USER_PATH)/us_os.c
endif

ifeq ($(strip $(CUSTOM_KEY_OVERRIDE)), yes)
	SRC += $(USER_PATH)/us_key_override.c
endif

ifeq ($(strip $(CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY)), yes)
	SRC += $(USER_PATH)/us_tap_hold.c
endif
