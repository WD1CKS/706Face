# Connections to the Pico
This documents all the connections that are planned for the Pico.

## Power

The 8VDC line almost certainly doesn't provide enough power to run everything
we plan, so we'll want to use the 13.8VDC output on the ACC port.  We'll want
to buck down to 5V, and drive the pico LDO from that.

## Head unit connector on radio

This is intended to be the primary interface and will hopefully be the only one
that is actually required.

| Connector Pin | Pico Pin | Comment      |
|---------------|----------|--------------|
| 1 (LRXD)      | UART0 TX | Rig control  |
| 2 (LTXD)      | UART0 RX | Rig status   |
| 3 (8VDC)      | GPIOx    | Power state  |
| 8 (PWK)       | GPIOx    | Power switch |

## CI-V Connector

The CI-V control allows direct selection of modes and tuning steps, which can
require a long press on the front panel.  We don't really care about stuff the
rig sends though (but we may end up needing UART RX for collision/error
detection).  Depending on how well behaved the rig is, we may be able to detect
CI-V vs. head unit using the head unit handshake sequence.

| Connector Pin | Pico Pin | Comment         |
|---------------|----------|-----------------|
| Tip (Data)    | UART1 TX | Mode selection  |
| Tip (Data)    | UART1 RX | Error detection |

## Radio connector in head unit

If pass-through mode is enabled, we won't be able to use the CI-V connection
above, but can pass everything through to a real head unit and keep them in
sync.  We can also potentially use the LCD for our own nefarious purposes.

| Connector Pin | Pico Pin | Comment        |
|---------------|----------|----------------|
| 1 (LRXD)      | UART1 RX | Pass-through   |
| 2 (LTXD)      | UART1 TX | Pass-through   |

## ACC connection

While we could access the FSK key line via the FSK jack, we're likely to be
taking our power from ACC anyway, so using the FSKK line allows us to save an
extra connection.

| Connector Pin | Pico Pin | Comment           |
|---------------|----------|-------------------|
| 10 (FSKK)     | GPIOx    | FSK Keyer         |

## ELEC-KEY

The only way to send CW through the head unit cable is via the mic up/down
buttons, which uses the keyer and doesn't allow both on at the same time.

This means for CW, we need to connect to the CW jack.  Since we're there, may
as well connect both signals.

| Connector Pin | Pico Pin | Comment           |
|---------------|----------|-------------------|
| TIP           | GPIOx    | dit/straight      |
| RING          | GPIOx    | dah               |

## Custom keypad

For individual keys, we will use a conventional GPIO key matrix.  For the main
tuning knob, we'll need two GPIOs for the argade spinner encoder.  For other
knobs, we can use the ADC lines to read potentiaometers, and one GPIO per pot
to select.
