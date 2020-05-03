# Default keymap does not have any overridden options from the rev1 / rev2 rules.mk files.
# Example:
#     if you wanted to disable EXTRAKEY_ENABLE, you would copy the line from the rev1/rules.mk file
#     and paste it in to this file, changing the yes to no. Like so:
# EXTRAKEY_ENABLE         = no       # Audio control and System control
#
# To keep things clean and tidy, as well as make upgrades easier, only place overrides from the defaults in this file.

# Keycode Options
MOUSEKEY_ENABLE         = yes        # Mouse keys

# RGB Options
RGBLIGHT_FULL_POWER     = yes        # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
FULLHAND_ENABLE         = yes        # Enables the additional 24 Full Hand LEDs

# Do not edit past here
include keyboards/$(KEYBOARD)/post_rules.mk
