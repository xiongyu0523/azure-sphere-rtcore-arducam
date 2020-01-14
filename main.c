/* Copyright (c) Microsoft Corporation. All rights reserved.
   Licensed under the MIT License. */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "ArduCAM.h"
#include "Log_Debug.h"
#include "delay.h"
#include "VectorTable.h"

uint8_t ImageBuffer[64 * 1024];

_Noreturn void RTCoreMain(void)
{
	VectorTableInit();
	CPUFreq_Set(197600000);
	
	DebugUARTInit();

	Log_Debug("Exmaple to capture a JPEG image from ArduCAM mini 2MP Plus\r\n");

	// init hardware and probe camera
	arducam_ll_init();
	arducam_reset();
	if (arducam_test() == 0) {
		Log_Debug("ArduCAM mini 2MP Plus is found\r\n");
	}
	else {
		Log_Debug("ArduCAM mini 2MP Plus is not found\r\n");
		while (1);
		goto END;
	}

	// config Camera
	arducam_set_format(JPEG);
	arducam_InitCAM();
	arducam_OV2640_set_JPEG_size(OV2640_160x120);
	delay_ms(1000);
	arducam_clear_fifo_flag();
	arducam_flush_fifo();

	// Trigger a capture and wait for data ready in DRAM
	arducam_start_capture();
	while (!arducam_check_fifo_done());

	uint32_t img_len = arducam_read_fifo_length();
	if (img_len > MAX_FIFO_SIZE) {
		Log_Debug("ERROR: FIFO overflow\r\n");
		goto END;
	}

	uint8_t* p_imgBuffer = &ImageBuffer[0];

	arducam_CS_LOW();
	arducam_set_fifo_burst();
	arducam_read_fifo_burst(p_imgBuffer, img_len);
	arducam_CS_HIGH();

	arducam_clear_fifo_flag();

	// OV2640 pad 0x00 bytes at the end of JPG image
	while (p_imgBuffer[img_len - 1] != 0xD9) {
		--img_len;
	}

END:
	while (1);
}
