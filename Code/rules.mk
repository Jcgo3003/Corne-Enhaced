SRC += analog.c

NKRO_ENABLE        = yes
WPM_ENABLE         = yes

TAP_DANCE_ENABLE   = yes
LOCK_KEY_ENABLE    = yes  
MOUSEKEY_ENABLE    = yes
EXTRAKEY_ENABLE	   = yes

RGBLIGHT_ENABLE    = no 
RGB_MATRIX_ENABLE  = no	

OLED_ENABLE        = yes
OLED_DRIVER        = SSD1306

ENCODER_ENABLE     = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

BOOTMAGIC_ENABLE   = yes  # Clean EEprom Feature
LTO_ENABLE         = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

# Dont use
CONSOLE_ENABLE     = no
AUDIO_ENABLE	   = no
MIDI_ENABLE		   = no
BLUETOOTH_ENABLE   = no