cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pacman-rp2350-touch-lcd-2 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(pacman-rp2350-touch-lcd-2
	pacman-rp2350-touch-lcd-2.c
	rp2350_lcd_2.c
	graphlib.c
	pacman2data.c
	ff.C
	pico-sdmm.c
	usbkeyboard.c
	hid_virtual_keytable.c
	qmi8658.c
)

target_include_directories(pacman-rp2350-touch-lcd-2 PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

# Pull in basic dependencies
target_link_libraries(pacman-rp2350-touch-lcd-2 pico_stdlib hardware_spi hardware_pwm tinyusb_host tinyusb_board pico_multicore hardware_i2c)

pico_add_extra_outputs(pacman-rp2350-touch-lcd-2)
