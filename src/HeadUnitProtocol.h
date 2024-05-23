#ifndef HEAD_UNIT_PROTOCOL_H
#define HEAD_UNIT_PROTOCOL_H

#define KEEPALIVE_TIMEOUT_MS 100

// TODO: Magic 0x00 message means power off
#define PANEL_PTT       UINT8_C(0x00)
#define PANEL_BUTTONS0  UINT8_C(0x01)
#define PANEL_BUTTONS1  UINT8_C(0x02)
#define PANEL_TUNE      UINT8_C(0x03)
#define PANEL_VOLUME    UINT8_C(0x05)
#define PANEL_RFSQL     UINT8_C(0x06)
#define PANEL_MCH       UINT8_C(0x07)
#define PANEL_SHIFT     UINT8_C(0x08)
#define PANEL_KEEPALIVE UINT8_C(0x0B)
#define PANEL_HS0       UINT8_C(0xF0)
#define PANEL_HS1       UINT8_C(0xF1)
#define PANEL_DISPLAY   UINT8_C(0x60)

#endif
