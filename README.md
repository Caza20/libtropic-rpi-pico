# libtropic-rpi-pico v0.1

## About

This repository contains examples of libtropic's usage on Raspberry Pi Pico development boards.

Currently supported boards are:
* Raspberry Pi Pico (RP2040) https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#pico-1-family

Debug messages are transmitted over devboard's USB ACM serial port, they can be received by opening a serial port on PC.

More info about wiring is in each project's own README.md file.

## Dependencies

* cmake
* arm-none-eabi-gcc
* pico-sdk ( https://github.com/raspberrypi/pico-sdk )

## Cloning

This repository must be cloned recursively, because it contains submodules - libtropic and target drivers:

```bash
git clone https://github.com/Caza20/libtropic-rpi-pico.git
cd libtropic-rpi-pico
git submodule update --init --recursive
```

## Building and Running Examples
All available examples can be found [here](https://github.com/Caza20/libtropic/tree/master/examples).

To build examples, switch to one of the platform directories (in this case, the `RPI-PICO`), and do the following:
```bash
cd RPI-PICO/
mkdir build
cd build
cmake -DLT_BUILD_EXAMPLES=1 .. -G "Ninja"
ninja
```

For each example, an ELF binary and an UF2 file will be created in the build directory.

> [!IMPORTANT]
> When `LT_BUILD_EXAMPLES` are set, there has to be a way to define the SH0 private key for the TROPIC01's pairing key slot 0, because both the examples and the tests depend on it. For this purpose, the CMake variable `LT_SH0_PRIV_PATH` is used, which should hold the path to the file with the SH0 private key in PEM or DER format. By default, the path is set to the currently used lab batch package, found in `libtropic/provisioning_data/<lab_batch_package_directory>/sh0_key_pair/`. But it can be overriden by the user either from the command line when executing CMake (switch `-DLT_SH0_PRIV_PATH=<path>`), or from a child CMakeLists.txt.

### Flashing

The RPi Pico board must be started in Boot mode, and the corresponding UF2 file for the example you want to run must be copied to the board.

After copying the UF2 file, the RPi Pico board will restart, and the example will start running.

After this, output should be seen in the opened serial port.

For example, when flashing the lt_ex_hello_world example by copying the lt_ex_hello_world.uf2 file to the RPi Pico board.

Then, You should see some output similar to this:
```
INFO    [  21] ======================================
INFO    [  22] ==== TROPIC01 Hello World Example ====
INFO    [  23] ======================================
INFO    [  27] Initializing handle
INFO    [  35] Starting Secure Session with key 0
INFO    [  43] 	-------------------------------------------------
INFO    [  46] Sending Ping command with message:
INFO    [  47] 	"This is Hello World message from TROPIC01!!"
INFO    [  55] 	-------------------------------------------------
INFO    [  57] Message received from TROPIC01:
INFO    [  58] 	"This is Hello World message from TROPIC01!!"
INFO    [  59] 	-------------------------------------------------
INFO    [  61] Aborting Secure Session
INFO    [  69] Deinitializing handle
```

> [!IMPORTANT]
> In version `v0.1`, only `L2 layer` examples (non-secure communication) work. `L3 layer` functionality (secure communication) has not been implemented yet.

## Building Functional Tests

> Work in progress

## Debugging in VS Code

For compiling in debug mode, pass `-DCMAKE_BUILD_TYPE=Debug` during cmake call.

Install dependencies:

* cortex-debug extension
* arm-none-eabi-gdb

Then place this launch.json file into .vscode folder:

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "cortex-debug",
            "request": "attach",
            "name": "Debug (OpenOCD)",
            "servertype": "openocd",
            "cwd": "${workspaceRoot}",
            //"preLaunchTask": "cargo build",
            //"runToEntryPoint": "true",
            "executable": "./build/stm32_example.elf",
            "device": "STM32F429ZI",
            "configFiles": [
                "/usr/share/openocd/scripts/board/stm32f429discovery.cfg"
            ],
        }
    ]
}

```

Debugging should be enabled after restarting your VS Code.

## Wuard - v0.1 - 08-2025

