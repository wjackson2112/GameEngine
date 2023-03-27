#ifndef INPUTS_H
#define INPUTS_H

#include <GLFW\glfw3.h>
#include <vector>

enum Key
{
	KEY_UNKNOWN=GLFW_KEY_UNKNOWN,
	KEY_SPACE=GLFW_KEY_SPACE,
	KEY_APOSTROPHE=GLFW_KEY_APOSTROPHE,
	KEY_COMMA=GLFW_KEY_COMMA,
	KEY_MINUS=GLFW_KEY_MINUS,
	KEY_PERIOD=GLFW_KEY_PERIOD,
	KEY_SLASH=GLFW_KEY_SLASH,
	KEY_0=GLFW_KEY_0,
	KEY_1=GLFW_KEY_1,
	KEY_2=GLFW_KEY_2,
	KEY_3=GLFW_KEY_3,
	KEY_4=GLFW_KEY_4,
	KEY_5=GLFW_KEY_5,
	KEY_6=GLFW_KEY_6,
	KEY_7=GLFW_KEY_7,
	KEY_8=GLFW_KEY_8,
	KEY_9=GLFW_KEY_9,
	KEY_SEMICOLON=GLFW_KEY_SEMICOLON,
	KEY_EQUAL=GLFW_KEY_EQUAL,
	KEY_A=GLFW_KEY_A,
	KEY_B=GLFW_KEY_B,
	KEY_C=GLFW_KEY_C,
	KEY_D=GLFW_KEY_D,
	KEY_E=GLFW_KEY_E,
	KEY_F=GLFW_KEY_F,
	KEY_G=GLFW_KEY_G,
	KEY_H=GLFW_KEY_H,
	KEY_I=GLFW_KEY_I,
	KEY_J=GLFW_KEY_J,
	KEY_K=GLFW_KEY_K,
	KEY_L=GLFW_KEY_L,
	KEY_M=GLFW_KEY_M,
	KEY_N=GLFW_KEY_N,
	KEY_O=GLFW_KEY_O,
	KEY_P=GLFW_KEY_P,
	KEY_Q=GLFW_KEY_Q,
	KEY_R=GLFW_KEY_R,
	KEY_S=GLFW_KEY_S,
	KEY_T=GLFW_KEY_T,
	KEY_U=GLFW_KEY_U,
	KEY_V=GLFW_KEY_V,
	KEY_W=GLFW_KEY_W,
	KEY_X=GLFW_KEY_X,
	KEY_Y=GLFW_KEY_Y,
	KEY_Z=GLFW_KEY_Z,
	KEY_LEFT_BRACKET=GLFW_KEY_LEFT_BRACKET,
	KEY_BACKSLASH=GLFW_KEY_BACKSLASH,
	KEY_RIGHT_BRACKET=GLFW_KEY_RIGHT_BRACKET,
	KEY_GRAVE_ACCENT=GLFW_KEY_GRAVE_ACCENT,
	KEY_WORLD_1=GLFW_KEY_WORLD_1,
	KEY_WORLD_2=GLFW_KEY_WORLD_2,
	KEY_ESCAPE=GLFW_KEY_ESCAPE,
	KEY_ENTER=GLFW_KEY_ENTER,
	KEY_TAB=GLFW_KEY_TAB,
	KEY_BACKSPACE=GLFW_KEY_BACKSPACE,
	KEY_INSERT=GLFW_KEY_INSERT,
	KEY_DELETE=GLFW_KEY_DELETE,
	KEY_RIGHT=GLFW_KEY_RIGHT,
	KEY_LEFT=GLFW_KEY_LEFT,
	KEY_DOWN=GLFW_KEY_DOWN,
	KEY_UP=GLFW_KEY_UP,
	KEY_PAGE_UP=GLFW_KEY_PAGE_UP,
	KEY_PAGE_DOWN=GLFW_KEY_PAGE_DOWN,
	KEY_HOME=GLFW_KEY_HOME,
	KEY_END=GLFW_KEY_END,
	KEY_CAPS_LOCK=GLFW_KEY_CAPS_LOCK,
	KEY_SCROLL_LOCK=GLFW_KEY_SCROLL_LOCK,
	KEY_NUM_LOCK=GLFW_KEY_NUM_LOCK,
	KEY_PRINT_SCREEN=GLFW_KEY_PRINT_SCREEN,
	KEY_PAUSE=GLFW_KEY_PAUSE,
	KEY_F1=GLFW_KEY_F1,
	KEY_F2=GLFW_KEY_F2,
	KEY_F3=GLFW_KEY_F3,
	KEY_F4=GLFW_KEY_F4,
	KEY_F5=GLFW_KEY_F5,
	KEY_F6=GLFW_KEY_F6,
	KEY_F7=GLFW_KEY_F7,
	KEY_F8=GLFW_KEY_F8,
	KEY_F9=GLFW_KEY_F9,
	KEY_F10=GLFW_KEY_F10,
	KEY_F11=GLFW_KEY_F11,
	KEY_F12=GLFW_KEY_F12,
	KEY_F13=GLFW_KEY_F13,
	KEY_F14=GLFW_KEY_F14,
	KEY_F15=GLFW_KEY_F15,
	KEY_F16=GLFW_KEY_F16,
	KEY_F17=GLFW_KEY_F17,
	KEY_F18=GLFW_KEY_F18,
	KEY_F19=GLFW_KEY_F19,
	KEY_F20=GLFW_KEY_F20,
	KEY_F21=GLFW_KEY_F21,
	KEY_F22=GLFW_KEY_F22,
	KEY_F23=GLFW_KEY_F23,
	KEY_F24=GLFW_KEY_F24,
	KEY_F25=GLFW_KEY_F25,
	KEY_KP_0=GLFW_KEY_KP_0,
	KEY_KP_1=GLFW_KEY_KP_1,
	KEY_KP_2=GLFW_KEY_KP_2,
	KEY_KP_3=GLFW_KEY_KP_3,
	KEY_KP_4=GLFW_KEY_KP_4,
	KEY_KP_5=GLFW_KEY_KP_5,
	KEY_KP_6=GLFW_KEY_KP_6,
	KEY_KP_7=GLFW_KEY_KP_7,
	KEY_KP_8=GLFW_KEY_KP_8,
	KEY_KP_9=GLFW_KEY_KP_9,
	KEY_KP_DECIMAL=GLFW_KEY_KP_DECIMAL,
	KEY_KP_DIVIDE=GLFW_KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY=GLFW_KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT=GLFW_KEY_KP_SUBTRACT,
	KEY_KP_ADD=GLFW_KEY_KP_ADD,
	KEY_KP_ENTER=GLFW_KEY_KP_ENTER,
	KEY_KP_EQUAL=GLFW_KEY_KP_EQUAL,
	KEY_LEFT_SHIFT=GLFW_KEY_LEFT_SHIFT,
	KEY_LEFT_CONTROL=GLFW_KEY_LEFT_CONTROL,
	KEY_LEFT_ALT=GLFW_KEY_LEFT_ALT,
	KEY_LEFT_SUPER=GLFW_KEY_LEFT_SUPER,
	KEY_RIGHT_SHIFT=GLFW_KEY_RIGHT_SHIFT,
	KEY_RIGHT_CONTROL=GLFW_KEY_RIGHT_CONTROL,
	KEY_RIGHT_ALT=GLFW_KEY_RIGHT_ALT,
	KEY_RIGHT_SUPER=GLFW_KEY_RIGHT_SUPER,
	KEY_MENU=GLFW_KEY_MENU,
	KEY_KP_MAX=KEY_MENU+1
};

class KeyFlags
{
	bool flags[KEY_KP_MAX];

public:
	//TODO: Add variadic constructor or something to set initial flag state
	KeyFlags(std::vector<Key> keys)
	{
		this->clear();
		for(int i = 0; i < KEY_KP_MAX; i++)
		{
			this->setKey(intToKey(i), keys[i]);
		}
	}

	bool getKey(Key key)
	{
		return flags[key];
	}

	void setKey(Key key)
	{
		flags[key] = true;
	}

	void setKey(Key key, bool value)
	{
		flags[key] = value;
	}

	void clearKey(Key key)
	{
		flags[key] = false;
	}

	void clear()
	{
		flags[KEY_KP_MAX] = { 0 };
	}

	static Key intToKey(int intKey)
	{
		return static_cast<Key>(intKey);
	}
};

enum MouseButton
{

    MOUSE_BUTTON_NONE=-1,
    MOUSE_BUTTON_1=GLFW_MOUSE_BUTTON_1,
    MOUSE_BUTTON_2=GLFW_MOUSE_BUTTON_2,
    MOUSE_BUTTON_3=GLFW_MOUSE_BUTTON_3,
    MOUSE_BUTTON_4=GLFW_MOUSE_BUTTON_4,
    MOUSE_BUTTON_5=GLFW_MOUSE_BUTTON_5,
    MOUSE_BUTTON_6=GLFW_MOUSE_BUTTON_6,
    MOUSE_BUTTON_7=GLFW_MOUSE_BUTTON_7,
    MOUSE_BUTTON_8=GLFW_MOUSE_BUTTON_8,
    MOUSE_BUTTON_LAST=GLFW_MOUSE_BUTTON_LAST,
    MOUSE_BUTTON_LEFT=GLFW_MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT=GLFW_MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE=GLFW_MOUSE_BUTTON_MIDDLE
};

enum Action
{
    ACTION_NONE=-1,
    ACTION_PRESS=GLFW_PRESS,
    ACTION_RELEASE=GLFW_RELEASE,
    ACTION_REPEAT=GLFW_REPEAT
};

enum Modifier
{
    MOD_NONE=-1,
    MOD_SHIFT=GLFW_MOD_SHIFT,
    MOD_CONTROL=GLFW_MOD_CONTROL,
    MOD_ALT=GLFW_MOD_ALT,
    MOD_SUPER=GLFW_MOD_SUPER,
    MOD_CAPS_LOCK=GLFW_MOD_CAPS_LOCK,
    MOD_NUM_LOCK=GLFW_MOD_NUM_LOCK
};

enum GamepadHandle
{
    GAMEPAD_HANDLE_NONE=-1,
    GAMEPAD_HANDLE_1=GLFW_JOYSTICK_1,
    GAMEPAD_HANDLE_2=GLFW_JOYSTICK_2,
    GAMEPAD_HANDLE_3=GLFW_JOYSTICK_3,
    GAMEPAD_HANDLE_4=GLFW_JOYSTICK_4,
    GAMEPAD_HANDLE_5=GLFW_JOYSTICK_5,
    GAMEPAD_HANDLE_6=GLFW_JOYSTICK_6,
    GAMEPAD_HANDLE_7=GLFW_JOYSTICK_7,
    GAMEPAD_HANDLE_8=GLFW_JOYSTICK_8,
    GAMEPAD_HANDLE_9=GLFW_JOYSTICK_9,
    GAMEPAD_HANDLE_10=GLFW_JOYSTICK_10,
    GAMEPAD_HANDLE_11=GLFW_JOYSTICK_11,
    GAMEPAD_HANDLE_12=GLFW_JOYSTICK_12,
    GAMEPAD_HANDLE_13=GLFW_JOYSTICK_13,
    GAMEPAD_HANDLE_14=GLFW_JOYSTICK_14,
    GAMEPAD_HANDLE_15=GLFW_JOYSTICK_15,
    GAMEPAD_HANDLE_16=GLFW_JOYSTICK_16,
    GAMEPAD_HANDLE_MAX
};

enum GamepadButton
{
    GAMEPAD_BUTTON_NONE=-1,
    GAMEPAD_BUTTON_A=GLFW_GAMEPAD_BUTTON_A,
    GAMEPAD_BUTTON_B=GLFW_GAMEPAD_BUTTON_B,
    GAMEPAD_BUTTON_X=GLFW_GAMEPAD_BUTTON_X,
    GAMEPAD_BUTTON_Y=GLFW_GAMEPAD_BUTTON_Y,
    GAMEPAD_BUTTON_LEFT_BUMPER=GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    GAMEPAD_BUTTON_RIGHT_BUMPER=GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    GAMEPAD_BUTTON_BACK=GLFW_GAMEPAD_BUTTON_BACK,
    GAMEPAD_BUTTON_START=GLFW_GAMEPAD_BUTTON_START,
    GAMEPAD_BUTTON_GUIDE=GLFW_GAMEPAD_BUTTON_GUIDE,
    GAMEPAD_BUTTON_LEFT_THUMB=GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    GAMEPAD_BUTTON_RIGHT_THUMB=GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    GAMEPAD_BUTTON_DPAD_UP=GLFW_GAMEPAD_BUTTON_DPAD_UP,
    GAMEPAD_BUTTON_DPAD_RIGHT=GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    GAMEPAD_BUTTON_DPAD_DOWN=GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    GAMEPAD_BUTTON_DPAD_LEFT=GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    GAMEPAD_BUTTON_MAX
};

enum GamepadAxis
{
    GAMEPAD_AXIS_NONE=-1,
    GAMEPAD_AXIS_LEFT_X=GLFW_GAMEPAD_AXIS_LEFT_X,
    GAMEPAD_AXIS_LEFT_Y=GLFW_GAMEPAD_AXIS_LEFT_Y,
    GAMEPAD_AXIS_RIGHT_X=GLFW_GAMEPAD_AXIS_RIGHT_X,
    GAMEPAD_AXIS_RIGHT_Y=GLFW_GAMEPAD_AXIS_RIGHT_Y,
    GAMEPAD_AXIS_LEFT_TRIGGER=GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    GAMEPAD_AXIS_RIGHT_TRIGGER=GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
    GAMEPAD_AXIS_MAX
};

// struct key_flags
// {
// 	unsigned int key_flag_unknown : 1;
// 	unsigned int key_flag_space : 1;
// 	unsigned int key_flag_apostrophe : 1;
// 	unsigned int key_flag_comma : 1;
// 	unsigned int key_flag_minus : 1;
// 	unsigned int key_flag_period : 1;
// 	unsigned int key_flag_slash : 1;
// 	unsigned int key_flag_0 : 1;
// 	unsigned int key_flag_1 : 1;
// 	unsigned int key_flag_2 : 1;
// 	unsigned int key_flag_3 : 1;
// 	unsigned int key_flag_4 : 1;
// 	unsigned int key_flag_5 : 1;
// 	unsigned int key_flag_6 : 1;
// 	unsigned int key_flag_7 : 1;
// 	unsigned int key_flag_8 : 1;
// 	unsigned int key_flag_9 : 1;
// 	unsigned int key_flag_semicolon : 1;
// 	unsigned int key_flag_equal : 1;
// 	unsigned int key_flag_a : 1;
// 	unsigned int key_flag_b : 1;
// 	unsigned int key_flag_c : 1;
// 	unsigned int key_flag_d : 1;
// 	unsigned int key_flag_e : 1;
// 	unsigned int key_flag_f : 1;
// 	unsigned int key_flag_g : 1;
// 	unsigned int key_flag_h : 1;
// 	unsigned int key_flag_i : 1;
// 	unsigned int key_flag_j : 1;
// 	unsigned int key_flag_k : 1;
// 	unsigned int key_flag_l : 1;
// 	unsigned int key_flag_m : 1;
// 	unsigned int key_flag_n : 1;
// 	unsigned int key_flag_o : 1;
// 	unsigned int key_flag_p : 1;
// 	unsigned int key_flag_q : 1;
// 	unsigned int key_flag_r : 1;
// 	unsigned int key_flag_s : 1;
// 	unsigned int key_flag_t : 1;
// 	unsigned int key_flag_u : 1;
// 	unsigned int key_flag_v : 1;
// 	unsigned int key_flag_w : 1;
// 	unsigned int key_flag_x : 1;
// 	unsigned int key_flag_y : 1;
// 	unsigned int key_flag_z : 1;
// 	unsigned int key_flag_left_bracket : 1;
// 	unsigned int key_flag_backslash : 1;
// 	unsigned int key_flag_right_bracket : 1;
// 	unsigned int key_flag_grave_accent : 1;
// 	unsigned int key_flag_world_1 : 1;
// 	unsigned int key_flag_world_2 : 1;
// 	unsigned int key_flag_escape : 1;
// 	unsigned int key_flag_enter : 1;
// 	unsigned int key_flag_tab : 1;
// 	unsigned int key_flag_backspace : 1;
// 	unsigned int key_flag_insert : 1;
// 	unsigned int key_flag_delete : 1;
// 	unsigned int key_flag_right : 1;
// 	unsigned int key_flag_left : 1;
// 	unsigned int key_flag_down : 1;
// 	unsigned int key_flag_up : 1;
// 	unsigned int key_flag_page_up : 1;
// 	unsigned int key_flag_page_down : 1;
// 	unsigned int key_flag_home : 1;
// 	unsigned int key_flag_end : 1;
// 	unsigned int key_flag_caps_lock : 1;
// 	unsigned int key_flag_scroll_lock : 1;
// 	unsigned int key_flag_num_lock : 1;
// 	unsigned int key_flag_print_screen : 1;
// 	unsigned int key_flag_pause : 1;
// 	unsigned int key_flag_f1 : 1;
// 	unsigned int key_flag_f2 : 1;
// 	unsigned int key_flag_f3 : 1;
// 	unsigned int key_flag_f4 : 1;
// 	unsigned int key_flag_f5 : 1;
// 	unsigned int key_flag_f6 : 1;
// 	unsigned int key_flag_f7 : 1;
// 	unsigned int key_flag_f8 : 1;
// 	unsigned int key_flag_f9 : 1;
// 	unsigned int key_flag_f10 : 1;
// 	unsigned int key_flag_f11 : 1;
// 	unsigned int key_flag_f12 : 1;
// 	unsigned int key_flag_f13 : 1;
// 	unsigned int key_flag_f14 : 1;
// 	unsigned int key_flag_f15 : 1;
// 	unsigned int key_flag_f16 : 1;
// 	unsigned int key_flag_f17 : 1;
// 	unsigned int key_flag_f18 : 1;
// 	unsigned int key_flag_f19 : 1;
// 	unsigned int key_flag_f20 : 1;
// 	unsigned int key_flag_f21 : 1;
// 	unsigned int key_flag_f22 : 1;
// 	unsigned int key_flag_f23 : 1;
// 	unsigned int key_flag_f24 : 1;
// 	unsigned int key_flag_f25 : 1;
// 	unsigned int key_flag_kp_0 : 1;
// 	unsigned int key_flag_kp_1 : 1;
// 	unsigned int key_flag_kp_2 : 1;
// 	unsigned int key_flag_kp_3 : 1;
// 	unsigned int key_flag_kp_4 : 1;
// 	unsigned int key_flag_kp_5 : 1;
// 	unsigned int key_flag_kp_6 : 1;
// 	unsigned int key_flag_kp_7 : 1;
// 	unsigned int key_flag_kp_8 : 1;
// 	unsigned int key_flag_kp_9 : 1;
// 	unsigned int key_flag_kp_decimal : 1;
// 	unsigned int key_flag_kp_divide : 1;
// 	unsigned int key_flag_kp_multiply : 1;
// 	unsigned int key_flag_kp_subtract : 1;
// 	unsigned int key_flag_kp_add : 1;
// 	unsigned int key_flag_kp_enter : 1;
// 	unsigned int key_flag_kp_equal : 1;
// 	unsigned int key_flag_left_shift : 1;
// 	unsigned int key_flag_left_control : 1;
// 	unsigned int key_flag_left_alt : 1;
// 	unsigned int key_flag_left_super : 1;
// 	unsigned int key_flag_right_shift : 1;
// 	unsigned int key_flag_right_control : 1;
// 	unsigned int key_flag_right_alt : 1;
// 	unsigned int key_flag_right_super : 1;
// 	unsigned int key_flag_menu : 1;
// };

enum KeyState
{
	KEY_STATE_RELEASE = GLFW_RELEASE,
	KEY_STATE_PRESS = GLFW_PRESS,
	KEY_STATE_REPEAT = GLFW_REPEAT,
	KEY_STATE_MAX
};

#endif
