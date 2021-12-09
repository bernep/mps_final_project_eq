/*
 * usb.h
 *
 *  Created on: Nov 23, 2021
 *      Author: mchonaker
 */

#ifndef USB_H_
#define USB_H_


#ifdef USB_DEVICE_ENABLE

#include "usb_audio.h"
#include "usbd_desc.h"
#include "usbd_audio.h"



void USBD_Setup(void);
void USBD_Start_Device(void);
void USBD_Stop_Device();


USBD_HandleTypeDef USBD_Device;

extern USBD_AUDIO_InterfaceCallbacksfTypeDef audio_class_interface;

#endif

#ifdef USB_HOST_ENABLE

//include usb dependencies
#include "usbh_conf.h"
#include "usbh_hid.h"
#include "usbh_core.h"
#include "ff_gen_drv.h"
#include "usbh_diskio.h"

//usb device types
#define USB_HID_DEVICE          0x01U
#define USB_MSC_DEVICE          0x02U
#define USB_SND_DEVICE          0x03U

//global stores current usb device type
uint8_t usbh_device_type;

//keep current state
uint8_t usbh_state;

//usbh handle
USBH_HandleTypeDef husbh;


//usb init function
void USBH_Setup();

//usb call back
void USBH_UserProcess(USBH_HandleTypeDef *, uint8_t);

#endif

#endif /* USB_H_ */
