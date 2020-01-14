#  Copyright (c) Microsoft Corporation. All rights reserved.
#  Licensed under the MIT License.

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
PROJECT(Azure_Sphere_RTcore_ArduCAM C)

# include
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/printf ${CMAKE_SOURCE_DIR}/lib ${CMAKE_SOURCE_DIR}/lib/mt3620 ${CMAKE_SOURCE_DIR}/arducam_driver)

# macro
add_compile_definitions(AzureSphere_CM4)

# Create executable
ADD_EXECUTABLE(${PROJECT_NAME} main.c delay.c Log_Debug.c printf/printf.c lib/VectorTable.c lib/SPIMaster.c lib/I2CMaster.c lib/GPIO.c lib/UART.c arducam_driver/ArduCAM.c arducam_driver/ll.c arducam_driver/ov2640_regs.c)
TARGET_LINK_LIBRARIES(${PROJECT_NAME})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_SOURCE_DIR}/linker.ld)

# Add MakeImage post-build command
INCLUDE("${AZURE_SPHERE_MAKE_IMAGE_FILE}")
