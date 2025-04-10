#define WPM_SPEED_1 10
#define WPM_SPEED_2 40

#define ANIM_FRAME_DURATION 300
#define ENCODER_STATE_TIMEOUT 2000

uint32_t anim_timer = 0;
uint8_t current_frame = 0;
int current_wpm = 0;

bool is_ctrl_pressed = false;
bool is_pet_jumping  = false;
bool is_pet_jump_done = true;

int8_t left_encoder_state = 0;
int8_t right_encoder_state = 0;
uint32_t last_activity_left_encoder = 0;
uint32_t last_activity_right_encoder = 0;

enum ctrl_direction {
    _CTRL_NORTH,
    _CTRL_EAST,
    _CTRL_SOUTH,
    _CTRL_WEST,
};

enum ctrl_direction last_ctrl_direction = _CTRL_NORTH;

enum scroll_direction {
    _NO_SCROLL,
    _NORTH_SCROLL,
    _NORTH_EAST_SCROLL,
    _EAST_SCROLL,
    _SOUTH_EAST_SCROLL,
    _SOUTH_SCROLL,
    _SOUTH_WEST_SCROLL,
    _WEST_SCROLL,
    _NORTH_WEST_SCROLL,
};

enum scroll_direction encoder_state_to_direction[3][3] = {
    {_NORTH_WEST_SCROLL,  _NORTH_SCROLL,  _NORTH_EAST_SCROLL},
    {_WEST_SCROLL,        _NO_SCROLL,     _EAST_SCROLL},
    {_SOUTH_WEST_SCROLL,  _SOUTH_SCROLL,  _SOUTH_EAST_SCROLL}
};

