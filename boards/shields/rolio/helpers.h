// Helpers for my Rolio config

/* Dead key macros
 * These create mod morphs that switch on the left or right shift keys to obtain the upper case letter; both send the same dead key first.
 * It's a bit of a hack because these are designed to be used within other mod morphs with AltGr (Right Alt) as the modifier.
 * The hack is to unpress RALT before sending the dead key and next key, then press it again.
 */
#define DEADKEY_MACRO(NAME, DEADKEY, NEXTKEY) ZMK_MACRO(NAME, \
    bindings = <&macro_release &kp RALT>, <&macro_tap &kp DEADKEY &kp NEXTKEY>, <&macro_press &kp RALT>; \
)

#define DEADKEY_MODMORPH(NAME, LOWER, UPPER) ZMK_MOD_MORPH(NAME, \
    bindings = <LOWER>, <UPPER>; \
    mods = <(MOD_LSFT | MOD_RSFT)>; \
)

#define DEADKEY(NAME, DEADKEY, LETTER) \
    DEADKEY_MACRO(NAME ## _lower, DEADKEY, LETTER) \
    DEADKEY_MACRO(NAME ## _upper, DEADKEY, LS(LETTER)) \
    DEADKEY_MODMORPH(NAME, &NAME ## _lower, &NAME ## _upper)

/* Macro for keys with Right Alt modifier
 * This creates a mod morph that gives the given key normally, but switches to somee other behaviour when AltGr is pressed.
 */
#define KP_OR_OTHER_WITH_RA(KEY, OTHER, DESC) ZMK_MOD_MORPH(KEY ## _ ## OTHER, \
    display-name = DESC; \
    bindings = <&kp KEY>, <&OTHER>; \
    mods = <(MOD_RALT)>; \
)

/* Hold taps */
// TODO maybe a bit overcomplicated

#define REQUIRE_IDLE_TIME 125
#define QUICK_TAP_TIME 175
#define HOLD_TIME_SHORT 250
#define HOLD_TIME_MEDIUM 500
#define HOLD_TIME_LONG 1000

// Note: These are all tap-preferred hold-taps, with quick tap and require prior idle times set in addition to the tap time.
#define TAP_OR_HOLD(NAME, DESC, TAP, HOLD, DURATION) ZMK_HOLD_TAP(NAME, \
    display-name = DESC; \
    flavor = "tap-preferred"; \
    tapping-term-ms = <DURATION>; \
    quick-tap-ms = <QUICK_TAP_TIME>; \
    require-prior-idle-ms = <REQUIRE_IDLE_TIME>; \
    bindings = <&HOLD>, <&TAP>; \
)

// Short, medium and long hold macros, with tap and hold bindings as parameters
#define TAP_OR_SHORT_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_TIME_SHORT)
#define TAP_OR_MEDIUM_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_TIME_MEDIUM)
#define TAP_OR_LONG_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_TIME_LONG)

// Short, medium and long hold macros, tap binding is keypress and hold binding is parameter
#define TAP_KP_OR_SHORT_HOLD(NAME, DESC, HOLD) TAP_OR_SHORT_HOLD(NAME, DESC, kp, HOLD)
#define TAP_KP_OR_MEDIUM_HOLD(NAME, DESC, HOLD) TAP_OR_MEDIUM_HOLD(NAME, DESC, kp, HOLD)
#define TAP_KP_OR_LONG_HOLD(NAME, DESC, HOLD) TAP_OR_LONG_HOLD(NAME, DESC, kp, HOLD)

// Short, medium and long hold macros, both tap and hold bindings are keypresses
#define TAP_KP_OR_SHORT_HOLD_KP(NAME, DESC) TAP_KP_OR_SHORT_HOLD(NAME, DESC, kp)
#define TAP_KP_OR_MEDIUM_HOLD_KP(NAME, DESC) TAP_KP_OR_MEDIUM_HOLD(NAME, DESC, kp)
#define TAP_KP_OR_LONG_HOLD_KP(NAME, DESC) TAP_KP_OR_LONG_HOLD(NAME, DESC, kp)

// Short, medium and long hold macros, tap binding is none and hold binding is parameter
#define SHORT_HOLD(NAME, DESC, HOLD) TAP_OR_SHORT_HOLD(NAME, DESC, none, HOLD)
#define MEDIUM_HOLD(NAME, DESC, HOLD) TAP_OR_MEDIUM_HOLD(NAME, DESC, none, HOLD)
#define LONG_HOLD(NAME, DESC, HOLD) TAP_OR_LONG_HOLD(NAME, DESC, none, HOLD)

/* Layers */

// urob has ZMK_LAYER but I wanted to pass DESC as a parameter, not stringified NAME
#define LAYER(NAME, DESC, SENSORS, LAYOUT) \
    / { \
        keymap { \
             compatible = "zmk,keymap"; \
            layer_ ## NAME { \
                display-name = DESC; \
                bindings = <LAYOUT>; \
                sensor-bindings = <SENSORS>; \
            }; \
        }; \
    };

#define ___ &trans
