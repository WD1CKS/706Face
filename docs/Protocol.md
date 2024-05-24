# Rig/Head Unit protocol

Aside from the power off handshake, all messages in either direction take the format: `FE cmd data FD`

Three data bytes are escaped:
| Byte | Sent as |
|------|---------|
| `FD` | `FF 0D` |
| `FE` | `FF 0E` |
| `FF` | `FF 0F` |

All others are sent as-is.

## Head Unit to Radio

### `00` PTT

One byte of data.  Bit 0 indicates PTT state, bit 1 indicates if something is plugged into the headphone jack (ie: speaker mute).

### `01` Buttons 0

One byte of data, each bit represents the state of a single button.  Bit 5 is not used.

| Bit | Button     |
|-----|------------|
| 0   | F-1        |
| 1   | Menu       |
| 2   | Tuner/Call |
| 3   | P.Amp/ATT  |
| 4   | RIT/Sub    |
| 6   | Mic Down   |
| 7   | Mic Up     |

### `02` Buttons 1

One byte of data, each bit represents the state of a single button.

| Bit | Button  |
|-----|---------|
| 0   | Down    |
| 1   | Up      |
| 2   | TS      |
| 3   | Mode    |
| 4   | Lock    |
| 5   | Display |
| 6   | F-3     |
| 7   | F-2     |

### `03` Tune

One byte of data `00` to `FF`, indicating main tune knob position.  Increments with clockwise rotation.

### `05` Volume

As above for Volume knob.

### `06` RF/SQL

As above for RF/SQL knob.

### `07` M-CH

As above for M-CH knob.

### `08` Shift

As above for Shift knob.

### `0B` Keepalive

A keepalive packet with a data byte of `00` must be sent periodically.
If one is not sent for 200ms, the radio shuts itself off.

The stock head unit sends the message every 100ms.

## Radio to Head Unit

### `60` Display Data

Data to display.  Format is not yet reverse engineered.

## Handshakes

There are two different handshakes for the radio.

### Power on

On a power on, the radio will repeatedly send `FE F0 FD` until the head unit replies with the same message.  Once it does, the radio will send `FE F1 FD` and the head unit is expected to echo this back as well.

### Power off

The radio sends a single `00` byte, and the head unit does as well.

## References

https://www.oz9aec.net/radios/ic-706/diy-remote-kit-for-the-ic-706-part-2-a-closer-look-at-the-protocol
https://ok1zia.nagano.cz/wiki/Front_panel_IC-706
