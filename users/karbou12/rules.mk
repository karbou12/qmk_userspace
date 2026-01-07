VIA_ENABLE = yes
VIAL_ENABLE = yes

ifeq ($(strip $(CAPS_WORD_ENABLE)),)
CAPS_WORD_ENABLE = yes
endif

ifeq ($(strip $(OS_DETECTION_ENABLE)),)
OS_DETECTION_ENABLE = yes
endif

ifeq ($(strip $CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY)),)
CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY = yes
endif

# CONSOLE_ENABLE = yes

SRC += $(USER_PATH)/karbou12.c \
       $(USER_PATH)/us_utils.c \
       $(USER_PATH)/us_status.c \
       $(USER_PATH)/us_eeconfig.c

ifeq ($(strip $(CUSTOM_RGBLIGHT)), yes)
	OPT_DEFS += -DRGBLIGHT_ENABLE -DRGBLIGHT_LAYERS -DRGBLIGHT_LAYER_BLINK
	SRC += $(USER_PATH)/us_rgb.c
endif

ifeq ($(strip $(CUSTOM_RGBMATRIX)), yes)
	OPT_DEFS += -DRGB_MATRIX_ENABLE -DCUSTOM_RGBMATRIX
	SRC += $(USER_PATH)/us_rgb.c
endif

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
	SRC += $(USER_PATH)/us_os.c
endif

ifeq ($(strip $(CUSTOM_TAP_DANCE)), yes)
	OPT_DEFS += -DCUSTOM_TAP_DANCE_ENABLE
	SRC += $(USER_PATH)/us_tap_dance.c
endif

ifeq ($(strip $(CUSTOM_COMBO)), yes)
	OPT_DEFS += -DCUSTOM_COMBO_ENABLE
	SRC += $(USER_PATH)/us_combo.c
endif

ifeq ($(strip $(CUSTOM_KEY_OVERRIDE)), yes)
	OPT_DEFS += -DCUSTOM_KEY_OVERRIDE_ENABLE
	SRC += $(USER_PATH)/us_key_override.c
endif

ifeq ($(strip $(CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY)), yes)
	OPT_DEFS += -DCUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY_ENABLE
	SRC += $(USER_PATH)/us_tap_hold.c
endif

ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
	SRC += $(USER_PATH)/us_pointing_device.c
endif
