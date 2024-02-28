/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H



/* Id for the company in the AUTOSAR*/
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)


   
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

  
/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port_Init */
#define PORT_INIT_SID					(uint8)0x00

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIR_SID				(uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIR_SID			(uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID			(uint8)0x03

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID				(uint8)0x04

   
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/   

/* DET code to report Invalid Port Pin ID */ 
#define PORT_E_PARAM_PIN                 (uint8)0x0A
 
/* DET code to report Invalid Port Pin not configured as changeable */   
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)0x0B 
   
/* Det code to report Port_Init API service called with wrong parameter */
#define PORT_E_PARAM_CONFIG              (uint8)0x0C

/* DET code to report service called when mode is unchangeable.  */    
#define PORT_E_PARAM_INVALID_MODE        (uint8)0x0D 
   
#define PORT_E_MODE_UNCHANGEABLE         (uint8)0x0E

/* Det code to report API service called without module initialization */   
#define PORT_E_UNINIT                    (uint8)0x0F 

/* DET code to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER             (uint8)0x10

  

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Description: Data type for the symbolic name of a port PIN*/ 
typedef uint8 Port_PinType;

/*Description: Different port pin modes.*/
typedef enum{
PORT_PIN_DIO_MODE ,
PORT_PIN_UART_MODE,
PORT_PIN_SSI_MODE,
PORT_PIN_I2C_MODE,
PORT_PIN_PWM0_MODE,
PORT_PIN_PWM1_MODE,
PORT_PIN_ADC_MODE,
PORT_PIN_CAN_MODE = 8
} Port_PinModeType;

/* Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Enum to hold PIN initial level value */
typedef enum
{
    Level_LOW, Level_HIGH
}Port_LevelType;

/* Enum to hold PIN direction changeable status */
typedef enum{
  PinDirectionChangeable_OFF, PinDirectionChangeable_ON
}Port_PinDirectionChangeable;

/* Enum to hold PIN mode changeable status */
typedef enum{
  PinModeChangeable_OFF, PinModeChangeable_ON
}Port_PinModeChangeable;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. The PORT Which the pin belongs to. 
 *	2. The number of the pin in the PORT.
 *      3. The mode of the pin.
 *      4. The direction of pin --> INPUT or OUTPUT 
 *      5. The pin level initial value. 
 *      6. The pin direction changeable (standard_ON/standard_OFF)
 *      7. The pin mode changeable (standard_ON/standard_OFF)
 *      8. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    Port_IDType port_num; 
    Port_PinType pin_num; 
    Port_PinModeType mode;
    Port_PinDirectionType direction;
    Port_LevelType level;
    Port_PinDirectionChangeable directionChangeable;
    Port_PinModeChangeable modeChangeable;
    Port_InternalResistor resistor;
}Port_ChannelConfigType;

/* Array of Configured Port Pins */
typedef struct
{
   Port_ChannelConfigType Channels[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*Function Initializes the Port Driver module*/
void Port_Init(const Port_ConfigType *ConfigPtr);

/*Function Sets the Port pin direction*/
#if (PortSetPinDirectionApi == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/*Function Refreshes Port direction*/ 
void Port_RefreshPortDirection(void);

/*Function Returns the version information of this module*/
#if (Port_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);
#endif

/*Function Sets the Port pin mode.*/
#if (PortSetPinModeApi == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode); 
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType PORT_Configuration;


#endif /* PORT_H */