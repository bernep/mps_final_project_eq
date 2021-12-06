/*
 * usb.h
 *
 *  Created on: Nov 23, 2021
 *      Author: mchonaker
 */

#ifndef USB_H_
#define USB_H_

#include "init.h"


#ifdef USB_DEVICE_ENABLE

#include "usbd_conf.h"
#include "usbd_core.h"

USBD_ClassTypeDef husbd;


void USBD_Setup();



#endif /* USB_HOST_ENABLE */



#ifdef USB_HOST_ENABLE

//include usb dependencies
#include "usbh_conf.h"
#include "usbh_hid.h"
#include "usbh_core.h"

//usb device types
#define USB_DEVICE_DEVICE   	0x00U
#define USB_AUDIO_DEVICE       	0x01U
#define USB_CDC_DEVICE        	0x02U
#define USB_HID_DEVICE        	0x03U
#define USB_PHY_DEVICE        	0x05U
#define USB_IMAGE_DEVICE        0x06U
#define USB_PRINTER_DEVICE    	0x07U
#define USB_MSH_DEVICE        	0x08U
#define USB_HUB_DEVICE        	0x09U
#define USB_CDCDATA_DEVICE    	0x0AU
#define USB_MSC_DEVICE        	0x0BU
#define USB_CONTENT_DEVICE     	0x0DU
#define USB_VIDEO_DEVICE        0x0EU
#define USB_HEALTH_DEVICE     	0x0FU
#define USB_AVDEVICE_DEVICE    	0x10U
#define USB_BILL_DEVICE        	0x11U
#define USB_BRGD_DEVICE        	0x12U
#define USB_DIAG_DEVICE        	0xDCU
#define USB_WIRELESS_DEVICE    	0xE0U
#define USB_MISC_DEVICE       	0xEFU
#define USB_APP_DEVICE        	0xFEU
#define USB_VEND_DEVICE        	0xFFU

//Usb driver enumerations
#define USB_DRIVER_INACTIVE  	0x00U
#define USB_DRIVER_ACTIVE       0x01U

//global stores current usb device type
uint8_t usbh_device_type;
uint8_t usbh_driver_status;


//keep current state
uint8_t usbh_state;

//usbh handle
USBH_HandleTypeDef husbh;


//usb init function
void USBH_Setup();

//usb call back
void USBH_UserProcess(USBH_HandleTypeDef *, uint8_t);

#endif /* USB_HOST_ENABLE */



#endif /* USB_H_ */

