# TinyUF2 for Skydeck A01

TinyUF2 bootloader for the Skydeck A01 board based on phyCORE-i.MX RT1176 SoM.

## Board Configuration

- **MCU**: MIMXRT1176 (Cortex-M7 core)
- **Flash**: 16MB QSPI (W25Q128JV or compatible)
- **Flash Base**: 0x30000000
- **Bootloader Address**: 0x30000400 (FCFB at 0x400 offset)
- **Application Address**: 0x3000C000
- **USB**: OTG1 with power enable on GPIO9_IO06
- **LED**: Green LED on GPIO_LPSR_08 (active low)
- **UF2 Volume**: SKYDECKBOOT

## Building TinyUF2

### Prerequisites

1. Install ARM GCC toolchain (arm-none-eabi-gcc)
2. Clone TinyUF2 and initialize submodules:
   ```bash
   git clone https://github.com/adafruit/tinyuf2.git
   cd tinyuf2
   git submodule update --init
   ```
3. Get dependencies for the mimxrt10xx port:
   ```bash
   python tools/get_deps.py mimxrt10xx
   ```

### Build Commands

Build the flash-resident version (recommended for Skydeck):

```bash
cd ports/mimxrt10xx
make BOARD=skydeck_a01 FLASH_BUILD=1 all
```

Output files will be in `_build/skydeck_a01/`:
- `tinyuf2-skydeck_a01.bin` - Binary for direct flash programming
- `tinyuf2-skydeck_a01.elf` - ELF file for debugging
- `tinyuf2-skydeck_a01.hex` - Intel HEX file

### Flashing

#### Using External Debugger (LinkServer/pyOCD)

Flash the binary to 0x30000400:

```bash
make BOARD=skydeck_a01 FLASH_BUILD=1 flash-pyocd-bin
```

Or manually with LinkServer:
```bash
LinkServer flash MIMXRT1176xxxxx:MIMXRT1170-EVK load _build/skydeck_a01/tinyuf2-skydeck_a01.bin --addr 0x30000400
```

#### Using Serial Download Mode (SDP)

1. Set boot mode pins to enter Serial Download mode (BOOT_MODE[1:0]=01)
2. Connect USB to the board
3. Run:
   ```bash
   make BOARD=skydeck_a01 flash-sdp
   ```

Note: SDP mode loads to RAM, but the RAM-linked version will self-program to flash.

## Skydeck Firmware Requirements

For firmware to work correctly with TinyUF2, it must:

### Memory Layout

1. **Start at 0x3000C000**: Application must be linked to start at this address
2. **Include valid vector table**: First word must be valid stack pointer, second word must be reset handler address
3. **Reserve first 48KB**: Addresses 0x30000000-0x3000BFFF are used by TinyUF2

Example linker script fragment:
```
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x3000C000, LENGTH = 16M - 48K
    DTCM (rwx)  : ORIGIN = 0x20000000, LENGTH = 256K
    OCRAM (rwx) : ORIGIN = 0x20240000, LENGTH = 1024K
}
```

### UF2 Family ID

Use the iMXRT family ID when creating UF2 files:

```bash
uf2conv.py -f 0x4FB2D5BD -b 0x3000C000 -c -o firmware.uf2 firmware.bin
```

Family ID `0x4FB2D5BD` is the standard iMXRT UF2 family.

### Re-entering Bootloader

Firmware can re-enter TinyUF2 bootloader by:

1. **Double-tap reset**: Press reset button twice quickly (within ~500ms)
2. **Software reset to bootloader**: Write magic value `0xf01669ef` to SNVS->LPGPR[3] (address 0x40C8_400C) then trigger system reset

Example code to enter bootloader from firmware:
```c
// Write magic value to SNVS LPGPR3
SNVS->LPGPR[3] = 0xf01669ef;
// Trigger system reset
NVIC_SystemReset();
```

### FCFB Configuration

If your firmware needs its own FlexSPI configuration (FCFB), it should be placed at offset 0x400 from the flash base. However, for Skydeck firmware starting at 0x3000C000, the TinyUF2 bootloader's FCFB at 0x30000400 will be used by the ROM bootloader.

## USB Identification

When in bootloader mode:
- **VID**: 0xF055 (Skydeck)
- **PID**: 0x9802
- **Manufacturer**: PHYTEC
- **Product**: Skydeck A01
- **Volume Label**: SKYDECKBOOT

## Troubleshooting

### USB not appearing after power on
- Ensure the board is not stuck in firmware - double-tap reset to force bootloader mode
- Check that USB power enable is working (GPIO9_IO06 active high)

### UF2 copy fails
- Ensure firmware is built for correct address (0x3000C000)
- Verify UF2 family ID is correct (0x4FB2D5BD)
- Check that firmware binary is not larger than available flash space

### LED not blinking
- Green LED on GPIO_LPSR_08 should pulse when in bootloader mode
- If LED is always on or off, there may be a boot issue - use debugger to investigate

### Board hangs after firmware update
- Verify firmware vector table is correct (valid SP and reset handler)
- Check firmware is linked for 0x3000C000 base address
- Use debugger to examine PC/SP after reset
