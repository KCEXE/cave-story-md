#define SRAM_UNCHECKED		0x00
#define SRAM_VALID_EMPTY	0x01
#define SRAM_VALID_SAVE		0x02
#define SRAM_INVALID		0xFF

// 8KB save file map, like this:
// 0000 - Counter
// 0020 - Config (global, maybe should have per file?)
// 0100 - First save file
// 0400 - backup of first save
// 0700 - Second save
// ...
// 1900 - End of saves (room for 4)
// 1FFC - Last 4 bytes, used to test if SRAM is working
// There are extra bytes of padding between, so more things can be added if necessary
#define SRAM_TEST_POS		0x1FFC
#define SRAM_COUNTER_POS	0x0000
#define SRAM_CONFIG_POS		0x0020
#define SRAM_CHECKSUM_POS	0x00C0

#define SRAM_FILE_START		0x0100

#define SRAM_BACKUP_OFFSET	0x0300
#define SRAM_FILE_LEN		0x0600

#define SRAM_FILE_MAX		4
#define SRAM_FILE_CHEAT		90

#define FLAG_EVENTONDROWN		4000
#define FLAG_DISABLESAVE		4095

typedef struct {
	uint8_t used; // Whether save contains any data
	uint8_t hour, minute, second;
	uint8_t stage_id, max_health, health;
	uint8_t weapon[5];
} SaveEntry;

extern uint8_t cfg_btn_jump;
extern uint8_t cfg_btn_shoot;
extern uint8_t cfg_btn_ffwd;
extern uint8_t cfg_btn_rswap;
extern uint8_t cfg_btn_lswap;
extern uint8_t cfg_btn_map;
extern uint8_t cfg_btn_pause;

extern uint8_t cfg_language;
extern uint8_t cfg_ffwd;
extern uint8_t cfg_updoor;
extern uint8_t cfg_hellquake;
extern uint8_t cfg_iframebug;

extern uint8_t sram_file;

// Global flags are persisted to save data
void system_set_flag(uint16_t flag, uint8_t value);
uint8_t system_get_flag(uint16_t flag);
// Skip flags remain in memory until power off, or new game
// Used to skip boss cutscenes when retrying
void system_set_skip_flag(uint16_t flag, uint8_t value);
uint8_t system_get_skip_flag(uint16_t flag);

// Increments play time
void system_update();

// Initializes variables with defaults when starting a new game
void system_new();
// Fills a structure with some info about a save file
void system_peekdata(uint8_t index, SaveEntry *file);
// Initializes variables from SRAM when loading a game save
void system_load(uint8_t index);
// Stores variables and game state into SRAM
void system_save();

void system_copy(uint8_t from, uint8_t to);
void system_delete(uint8_t index);

void system_load_config();
void system_save_config();
// Validates whether any save data exists in SRAM
uint8_t system_checkdata();
// Load to a stock save file from the level select list
void system_load_levelselect(uint8_t file);

// Counter stuff
void system_start_counter();
uint32_t system_counter_ticks();
void system_counter_draw();
uint32_t system_load_counter();
void system_save_counter(uint32_t ticks);

// SGDK sys.h stuff
void SYS_assertReset();
void SYS_hardReset();
void SYS_die(char *err);
