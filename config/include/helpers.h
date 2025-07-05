// Helpers for my Rolio config

/* Dead key macros
 * These create mod morphs that switch on the left or right shift keys to obtain the upper case letter; both send the same dead key first.
 */
#define DEADKEY_MACRO(NAME, DEADKEY, NEXTKEY) ZMK_MACRO(NAME, \
    bindings = <&kp DEADKEY &kp NEXTKEY>; \
)

#define DEADKEY_MODMORPH(NAME, LOWER, UPPER) ZMK_MOD_MORPH(NAME, \
    bindings = <LOWER>, <UPPER>; \
    mods = <(MOD_LSFT | MOD_RSFT)>; \
)

#define DEADKEY(NAME, DEADKEY, LETTER) \
    DEADKEY_MACRO(NAME ## _lower, DEADKEY, LETTER) \
    DEADKEY_MACRO(NAME ## _upper, DEADKEY, LS(LETTER)) \
    DEADKEY_MODMORPH(NAME, &NAME ## _lower, &NAME ## _upper)

/* Hold taps */
// TODO maybe a bit overcomplicated

#define REQUIRE_IDLE_MS 125
#define QUICK_TAP_MS 175
#define HOLD_MS_SHORT 250
#define HOLD_MS_MEDIUM 500
#define HOLD_MS_LONG 1000

// Note: These are all tap-preferred hold-taps, with quick tap and require prior idle times set in addition to the tap time.
#define TAP_OR_HOLD(NAME, DESC, TAP, HOLD, DURATION) ZMK_HOLD_TAP(NAME, \
    display-name = DESC; \
    flavor = "tap-preferred"; \
    tapping-term-ms = <DURATION>; \
    quick-tap-ms = <QUICK_TAP_MS>; \
    require-prior-idle-ms = <REQUIRE_IDLE_MS>; \
    bindings = <&HOLD>, <&TAP>; \
)

// Short, medium and long hold macros, with tap and hold bindings as parameters
#define TAP_OR_SHORT_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_MS_SHORT)
#define TAP_OR_MEDIUM_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_MS_MEDIUM)
#define TAP_OR_LONG_HOLD(NAME, DESC, TAP, HOLD) TAP_OR_HOLD(NAME, DESC, TAP, HOLD, HOLD_MS_LONG)

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

/* Various keycodes */

#define LHYPER LS(LC(LA(LGUI)))
#define LMEH LS(LC(LALT))
//#define COPILOT LS(LG(F23)) // No point, Win+C does the same thing

/* Home row mods */
#define KEYS_L LT0 LT1 LT2 LT3 LT4 LT5 LM0 LM1 LM2 LM3 LM4 LM5 LB0 LB1 LB2 LB3 LB4 LB5 LEC
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RT5 RM0 RM1 RM2 RM3 RM4 RM5 RB0 RB1 RB2 RB3 RB4 RB5 REC
#define THUMBS LH4 LH3 LH2 LH1 LH0 RH0 RH1 RH2 RH3 RH4

#define MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS)                                 \
  ZMK_HOLD_TAP(NAME, bindings = <HOLD>, <TAP>; flavor = "balanced";            \
               tapping-term-ms = <280>; quick-tap-ms = <QUICK_TAP_MS>;         \
               require-prior-idle-ms = <150>; hold-trigger-on-release;         \
               hold-trigger-key-positions = <TRIGGER_POS>;)

#define MAKE_LEFT_HRM(NAME, HOLD, TAP) MAKE_HRM(NAME, HOLD, TAP, KEYS_R THUMBS)
#define MAKE_RIGHT_HRM(NAME, HOLD, TAP) MAKE_HRM(NAME, HOLD, TAP, KEYS_L THUMBS)

// Hack: Make HRM combos tap-only (cf, ZMK issue #544).
#define ZMK_COMBO_8(NAME, TAP, POS, LAYERS, COMBO_MS, IDLE_MS, HOLD, SIDE)     \
  MAKE_HRM(hm_combo_##NAME, &kp, TAP, SIDE THUMBS)                             \
  ZMK_COMBO_6(NAME, &hm_combo_##NAME HOLD 0, POS, LAYERS, COMBO_MS, IDLE_MS)
