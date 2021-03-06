/*
 * usb.c
 *
 *  Created on: Nov 23, 2021
 *      Author: mchonaker
 */
#include "usb.h"


#ifdef USB_DEVICE_ENABLE

#include "usb_audio.h"
#include "usbd_desc.h"
#include "usbd_audio.h"
#include "usbd_audio_if.h"


void USBD_Setup(){

	// Application Initializations
	  /* Init Device Library */
	  USBD_Init(&USBD_Device, &AUDIO_Desc, 0);

	  /* Add Supported Class */
	  USBD_RegisterClass(&USBD_Device, USBD_AUDIO_CLASS);

	  /* Add Interface callbacks for AUDIO Class */
	  USBD_AUDIO_RegisterInterface(&USBD_Device, &audio_class_interface);



}


void USBD_Start_Device(){
	  /* Start Device Process */
	  USBD_Start(&USBD_Device);
}

void USBD_Stop_Device(){
	  /* Start Device Process */
	  USBD_Stop(&USBD_Device);
}

#endif



#ifdef USB_HOST_ENABLE

void USBH_Setup(){

	// Application Initializations
	printf("\033[2J\033[HInitialize USBH\r\n");
	fflush(stdout);
	USBH_Init(&husbh, USBH_UserProcess, 0);




	// USBH Driver Initialization
	printf("Registering Class\r\n");
	fflush(stdout);
	USBH_RegisterClass(&husbh, USBH_HID_CLASS);

	// USB Driver Class Registrations: Add device types to handle.
	// Start USBH Driver
	printf("Starting USB Host\r\n");
	fflush(stdout);
	USBH_Start(&husbh);
}


void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id) {
	switch (id)
	{
		case HOST_USER_DISCONNECTION:

			usbh_state = HOST_USER_DISCONNECTION;
			break;

			/* when HOST_USER_CLASS_ACTIVE event is received, application can start
  	  communication with device*/
		case HOST_USER_CLASS_ACTIVE:
			if(phost->pActiveClass->ClassCode == USB_HID_DEVICE){
				usbh_device_type = USB_HID_DEVICE;
			} else if (phost->pActiveClass->ClassCode == USB_MSC_DEVICE) {
				usbh_device_type = USB_MSC_DEVICE;
			}
			usbh_state = HOST_USER_CLASS_ACTIVE;
			usbh_driver_status = USB_DRIVER_INACTIVE;
			break;


		case HOST_USER_CONNECTION:
			usbh_state = HOST_USER_CONNECTION;
			break;
		default:
			break;
	}
}



#endif
