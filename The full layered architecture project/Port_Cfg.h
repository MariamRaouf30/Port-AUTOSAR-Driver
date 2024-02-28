/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Tarek
 ******************************************************************************/
#ifndef PORT_CFG_H
#define PORT_CFG_H

#define PORT_CFG_AR_RELEASE_MAJOR_VERSION       (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION       (0U)       
#define PORT_CFG_AR_RELEASE_PATCH_VERSION       (3U)        

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION               (1U)
#define PORT_CFG_SW_MINOR_VERSION               (0U)
#define PORT_CFG_SW_PATCH_VERSION               (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION       (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION       (0U)       
#define PORT_CFG_AR_RELEASE_PATCH_VERSION       (3U)   


/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_GetVersionInfo                  (STD_ON)

#define PortSetPinDirectionApi               (STD_ON)

#define PortSetPinModeApi                    (STD_ON)   

/* Pins numbers in TivaC*/
#define PORT_CONFIGURED_CHANNLES              (43U)  
   
/*TivaC Ports*/
typedef enum{
  PORTA_ID,
  PORTB_ID,
  PORTC_ID,
  PORTD_ID,
  PORTE_ID,
  PORTF_ID
}Port_IDType;
   
/*TivaC Pins*/   
#define PIN0_ID                               (0U)
#define PIN1_ID                               (1U)            
#define PIN2_ID                               (2U)
#define PIN3_ID                               (3U)
#define PIN4_ID                               (4U)
#define PIN5_ID                               (5U)
#define PIN6_ID                               (6U)
#define PIN7_ID                               (7U)

/* RCC Registers */
#define SYSCTL_REGCGC2_REG        		(*((volatile uint32 *)0x400FE108))

#endif /* PORT_CFG_H */
