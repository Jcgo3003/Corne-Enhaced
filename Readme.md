# Corne Keyboard Enhaced

I've made a subtle yet significant modification to the classic Corne keyboard. I've incorporated additional features to take the Corne keyboard beyond, adding 2 encoders, a joystick, and bringing back 6 buttons.

This is a keyboard designed for a macOS environment with a Dvorak layout, so most of the mappings are only for macOS and use Dvorak bindings.

## Table of Contents

- [Features](#Features)
- [Other Features](#Other_Features)
- [Usage](#Usage)
- [Diagrams](#Diagrams)
- [Layout](#Layout)
- [Compiled Size](#Compiled_Size)
- [Possible Updates](#Possible_Updates)
- [FAQ](#FAQ)
- [Credits](#Credits)

## Features

* Left Encoder 
	- Mouse scroll Horizontal base layer | base layer + Ctrl Slower scroll
	- Vertical scroll layer 2            
	- Zoom in/out Layer 3
	- Brightness -/+ Layer 4

* Right Encoder 
	- Volume control base layer 				
	- Word Scrolling Vertical Layer 2 
	- History scrolling layer 3     	  
	- Word Scrolling Horizontal Layer 4

* 4 Speed Mouse Speed cursor | Joystick
	- Min | Base Layer + Shift
	- Norm | Base Layer 
	- Fast | Layer 3 
	- Max | Layer 3 + Shift

* Extra keys 
	
	Thumbwheel Toggle Switch 
	- Mission Control  						 | Base Layer  
	- Browser Tab Navigation				 | Layer 2 
	- Mission Control 						 | Layer 3 
	- History Browser Back/Forward | Layer 4

	Encoder switch 
	- Mute Layer 
	- Power Button Layer 2

	Keymaps
	- Base
	- Layer 2
	- Layer 3
	- Numpad Mode/Full Number Keypad on the right side
	- Adjust

	- Magic Swap Ctrl/GUI
	- Magic Unswap Ctrl/GUI

* OLED animations
	- Layer indicator
	- Modifier indicators ⌘ ⇧ ⌥  ⌃.
	- Fully animated Luna on the left side.

* LED lights:
	- No RGB lights or animations due to lack of memory space

## Other Features

### Tap Dance 
* alt/cmd 
* cmd+space/keycaps  | Search/keycaps
* cmd+shift+s/cmd+ - | Save/Save as
* cmd+c/8 					 | Copy/8

# Key Combinations

This keyboard is focused on macOS with Dvorak Bindings. Saying this for some reason, on a Dvorak layout, the keys get physically mapped. For example, the copy shortcut uses cmd + c on a QWERTY layout. There's no problem; you just map it normally as LGUI(KC_C). On the other hand, on a Dvorak layout, you should map the physical place of C on the layout, which is I. So that's why I mapped LGUI(KC_I).

Most of the universal ones should also work fine on Linux and Windows using the Swap Control and GUI magic code feature available on the 5th layer as CG_SWAP key. However, for macOS, that won't be useful at all on other OS.

| Shortcut     | macOS           | QWERTY  		  | Dvorak          | Compatibility |
|:-				   | :-              | :-              | :-              | :-            |	
|Select 		  | cmd + shift     | LGUI(KC_LSFT)   | Same            | All           |
|Select All   | cmd + a         | LGUI(KC_A)      | Same            | All           |
|Cut          | cmd + x         | LGUI(KC_X)      | LGUI(KC_B)      | All-check     |
|Copy         | cmd + c         | LGUI(KC_C)      | LGUI(KC_I)      | All-check     |
|Paste        | cmd + v         | LGUI(KC_V)      | LGUI(KC_DOT)    | All-check     |
|Undo         | cmd + z         | LGUI(KC_Z)      | LGUI(KC_SLSH)   | All-check     |
|Redo         | cmd + shift + z | SGUI(KC_Z)      | SGUI(KC_SLSH)   | All-check     |
|Comment Line | cmd + /         | LGUI(KC_SLSH)   | LGUI(KC_LBRC)   | All           |
|Save As      | cmd + shift + s | SGUI(KC_S)      | SGUI(KC_SCLN)   | All           |
|Save         | cmd + s         | LGUI(KC_S)      | LGUI(KC_SCLN)   | All           |
|Tab Left     | cmd + alt + Left| LAG(KC_LEFT)    | Same            | All           |
|Tab Right    | cmd + alt + right| LAG(KC_RGHT)   | Same            | All           |
|Back         | cmd + left      | LGUI(KC_LEFT)  | Same            | All           |
|Forward      | cmd + right     | LGUI(KC_RGHT)  | Same            |	All           |
|Zoom in      | cmd + -         | LGUI(KC_MINS)  | LGUI(X_QUOT)    | All-check     |
|Zoom out     | cmd + +         | LGUI(KC_PLUS)  | LGUI(X_RBRC)    | All-check     |
|Close Tab    | cmd + w         | LGUI(KC_W)      | LGUI(KC_COMM)   | All-check     |
|Tab Nav      | cmd + Tab       | SGUI(KC_TAB)    | Same            | All-check     |

# macOS Only

| Shortcut        | macOS           | QWERTY  		  | Dvorak        | 
|:-				        |:-				        |:-					|:-				      | 
|Print Screen     | cmd + shift + 3 | SGUI(KC_3)  	  | Same	          |
|Custom Print Screen | cmd + shift + 4 | SGUI(KC_4)	  | Same 	          |
|Mission Control Up | ctl + up 		    | LCTL(KC_UP)  	| Same 	          |
|Mission Control Down| ctl + down 	  | LCTL(KC_DOWN) | Same	          |
|Mission Control Left| ctl + left 	  | LCTL(KC_LEFT) | Same	          |
|Mission Control Right| ctl + right | LCTL(KC_RGHT) | Same	          |
|Switch App Window | cmd + ` 	      | SGUI(KC_NUBS) | Same            |
|Up a Folder 		  | cmd + up 		    | SGUI(KC_UP)   | Same	          |
|Open Folder/Files| cmd + down      | LGUI(KC_DOWN) | Same	          |
|Search 		        | cmd + space     | LGUI(KC_SPACE)| Same	          |
|Delete 		        | cmd + Backspace| LGUI(KC_BSPC) | Same	          |

Also, check the mapping you get with these keys; I think they change across the OS. On macOS, you get this:

KC_NUBS = `
KC_GRV  = §

## Usage

To compile and flash from the `qmk setup` folder, copy the 'Code' folder to your
local qmk folder and place it into keyboards/crkbd/keymaps then run:

	$ qmk flash -c -kb crkbd/rev1 -km Code

* Alternatively, you can also just flash the firmware ![file](Firmware/crkbd_rev1_Jcgo.hex)

## Compiled Size

* The firmware size is approaching the maximum - 28470/28672 (99%, 202 bytes free)

## ![Diagrams](Diagrams/Diagrams.md)

# Electronic Components 

This is the list of the electronic components required:

| Component           | Quantity  		  | 
|:-				          | :-				      |	
| Nintendo Switch Joystick (Or a PSP or PSVita Joystick) | 1x |
| Tripod Thumbwheel Toggle Switch                    | 2x |
| Kailh 7mm Rotary Mouse Scroll Wheel Encoder       | 1x |
| Rotary Encoder Module for Arduino                 | 1x |

## ![Layout](QMK_Configurator/layout.md)
### ![QMK Configurator Files](QMK_Configurator)

Check the layout photos and the layout ![file](QMK_Configurator/jcgo.json) for the QMK configurator. I was not able to add the extra keys but still, I think it would give you a good idea of how the layout is mapped.

## FAQ
### How to Get Back the RGB Lights

If you want to get back the RGB feature, you can disable one or more features:

Joystick:
Delete these lines in 'rules.mk':
- SRC += analog.c 
- MOUSEKEY_ENABLE    = yes
- POINTING_DEVICE_ENABLE = yes
- POINTING_DEVICE_DRIVER = custom

Encoder:
Delete this line in 'rules.mk':
ENCODER_ENABLE     = yes

Lag algorithm:
Delete this line in 'rules.mk':
DEBOUNCE_TYPE = asym_eager_defer_pk

And modify these lines:
- RGBLIGHT_ENABLE    = yes
- RGB_MATRIX_ENABLE  = yes

### Why Are Bindings Weird?
For some reason, when I use the keyboard on macOS with a Dvorak layout, I must change the mapping to match the keys' physical positions instead of the literal bindings.

Example:

Copy binding on a QWERTY macOS layout should be: cmd + c, but because of this strange behavior, I wrote cmd + i where 'i' is the place on the physical keyboard for c. So, in the end, it's written LGUI(KC_C) instead of LGUI(KC_I).

## Possible Updates
- Detect the host OS and automatically use swap Ctrl/GUI
- Use smart zoom on macOS (I think it's not possible because it's reserved only for the trackpad)

## Credits

* @soundmonster[(GitHub)](https://github.com/soundmonster) - OLED code
* @hellsingcoder[(GitHub)](https://github.com/HellSingCoder) - Luna animation
* @yhren[(GitHub)](https://github.com/YHRen) - Pointing device code
* @Bermeo[(GitHub)](https://git.bermeo.dev) - Multiple OS support and ideas
