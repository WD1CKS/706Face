#ifndef HEAD_UNIT_STATE_H
#define HEAD_UNIT_STATE_H

enum modes {
	MODE_USB,
	MODE_LSB,
	MODE_CW,
	MODE_CWR,
	MODE_AM,
	MODE_RTTY,
	MODE_FM,
	MODE_WFM,
};

enum menus {
	MENU_M1,
	MENU_M2,
	MENU_M3,
	MENU_M4,
	MENU_S1,
	MENU_S2,
	MENU_G1,
	MENU_G2,
	MENU_G3,
	MENU_G4,
	MENU_Q1,
	MENU_Q2,
	MENU_Q3,
	MENU_Q4,
	MENU_Q5,
	MENU_Q6,
};

enum buttons {
	BUTTON_F1,
	BUTTON_MENU,
	BUTTON_TUNER,
	BUTTON_PREAMP,
	BUTTON_RIT,
	BUTTON_DN = 6,
	BUTTON_UP,
	BUTTON_BAND_DOWN,
	BUTTON_BAND_UP,
	BUTTON_TS,
	BUTTON_MODE,
	BUTTON_LOCK,
	BUTTON_F3,
	BUTTON_F2,
	BUTTON_PTT,
	BUTTON_HEADPHONES,
};

enum power_state {
	HS_STATE_OFF,	// Wait for FE F0 FD
	HS_STATE_FIRST,	// Wait for FE F1 FD
	HS_STATE_ON,	// Done handshake
};

#endif