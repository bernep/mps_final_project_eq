/*
 * usb.c
 *
 *  Created on: Nov 23, 2021
 *      Author: mchonaker
 */
#include "usb.h"




#ifdef USB_DEVICE_ENABLE


void USBD_Setup(){

	// Application Initializations
	printf("\033[2J\033[HInitialize USBH\r\n");
	fflush(stdout);
	USBD_Init(&husbd, USBD_UserProcess, 0);

	// USBH Driver Initialization
	printf("Registering Class\r\n");
	fflush(stdout);
	USBD_RegisterClass(&husbd, USBD_AUDIO_CLASS);

	// USB Driver Class Registrations: Add device types to handle.
	// Start USBH Driver
	printf("Starting USB Host\r\n");
	fflush(stdout);
	USBD_Start(&husbd);

}

void USBD_UserProcess(USBD_HandleTypeDef *phost, uint8_t id) {
	switch (id)
	{
		case DEVICE_USER_DISCONNECTION:

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
