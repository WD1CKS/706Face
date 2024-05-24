# Head Unit Cable Connection

## Connectors

The head unit uses a single row of eight pogo pins with approximately 0.95mm plunger diameter, at a 2mm pitch.
Male pins are on the radio, pads are on the head unit.

## Pinout

It appears that pin 1 is on the top of the radio, but this has not been verified yet.

| Pin | Signal | Description                          |
|-----|--------|--------------------------------------|
| 1   | LRXD   | Data from head unit to radio         |
| 2   | LTXD   | Data from radio to head unit         |
| 3   | 8VDC   | Power to head unit                   |
| 4   | AF     | Receive audio to headphone jack      |
| 5   | GND    | Ground for everything except the mic |
| 6   | MIC    | Microphone input                     |
| 7   | MICE   | Microphone ground                    |
| 8   | PWK    | Power button (active low)            |

## Physical layer

LRXD and LRXD are both 19200 8N1 at TTL level.
