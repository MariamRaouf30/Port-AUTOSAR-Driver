/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)
   #include "Det.h"
      /* AUTOSAR Version checking between Det and Dio Modules */
      #if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
         || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
         || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
         #error "The AR version of Det.h does not match the expected version"
      #endif

#endif


STATIC uint8 g_PORT_Status = PORT_NOT_INITIALIZED;
STATIC const  Port_ConfigType* g_PORT_CONFIG = NULL_PTR;

/************************************************************************************
*Service name: Port_Init
*Syntax: void Port_Init(const Port_ConfigType* ConfigPtr) 
*Service ID[hex]: 0x00 
*Sync/Async: Synchronous 
*Reentrancy: Non Reentrant 
*Parameters (in): ConfigPtr Pointer to configuration set. 
*Parameters (inout): None 
*Parameters (out): None 
*Return value: None 
*Description: Initializes the Port Driver module. 
************************************************************************************/

void Port_Init(const Port_ConfigType *ConfigPtr)
{
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
	}
	else 
        {
          /*Do Nothing*/
        }
    #endif
	{
          /*
          * Set the module state to initialized and point to the PB configuration structure using a global pointer.
          * This global pointer is global to be used by other functions to read the PB configuration structures
          */
	  g_PORT_Status = PORT_INITIALIZED;
          uint8 index;
          g_PORT_CONFIG = ConfigPtr;
          for(index=0;index <= PORT_CONFIGURED_CHANNLES;index++){
             volatile uint32* PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
             volatile uint32 delay = 0;
             switch(ConfigPtr->Channels[index].port_num)
                {
                  case  0: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		  break;
                  case  1: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		  break;
                  case  2: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		  break;
                  case  3: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		  break;
                  case  4: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		  break;
                  case  5: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		  break;
                }
            /* Enable clock for PORT and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= (1<<ConfigPtr->Channels[index].port_num);
            delay = SYSCTL_REGCGC2_REG;
            if( ((ConfigPtr->Channels[index].port_num == 3) && (ConfigPtr->Channels[index].pin_num == 7)) || ((ConfigPtr->Channels[index].port_num == 5) && (ConfigPtr->Channels[index].pin_num == 0)) ) /* PD7 or PF0 */
            {
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (ConfigPtr->Channels[index].port_num == 2) && (ConfigPtr->Channels[index].pin_num <= 3) ) /* PC0 to PC3 */
            {
              /* Do Nothing ...  this is the JTAG pins */
            }
             else
            {
              /* Do Nothing ... No need to unlock the commit register for this pin */
            }
            if(ConfigPtr->Channels[index].mode == PORT_PIN_ADC_MODE){
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);      /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            }
            else{
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
           // CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
           // *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4));     /* Clear the PMCx bits for this pin */
            switch(ConfigPtr->Channels[index].mode)
            {
              case PORT_PIN_DIO_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_UART_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_UART_MODE << (ConfigPtr->Channels[index].pin_num * 4));
                break;  
              case PORT_PIN_SSI_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_SSI_MODE << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_I2C_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_I2C_MODE  << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_PWM0_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_PWM0_MODE  << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_PWM1_MODE : 
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_PWM1_MODE  << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_ADC_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_ADC_MODE  << (ConfigPtr->Channels[index].pin_num * 4));
                break;
              case PORT_PIN_CAN_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (ConfigPtr->Channels[index].pin_num * 4))) | (PORT_PIN_CAN_MODE  << (ConfigPtr->Channels[index].pin_num * 4));
                break;
            }
          if(ConfigPtr->Channels[index].direction == PORT_PIN_OUT)
          {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            if(ConfigPtr->Channels[index].level == Level_HIGH)
            {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
            }
            else
            {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
            }
          }
          else if(ConfigPtr->Channels[index].direction == PORT_PIN_IN)
          {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            if(ConfigPtr->Channels[index].resistor == PULL_UP)
            {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
            }
            else if(ConfigPtr->Channels[index].resistor == PULL_DOWN)
            {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
            }
            else
            {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Channels[index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
            }
          }
          else
          {
           /* Do Nothing */
          }

        }
    }      
}




/************************************************************************************
*Service name: Port_SetPinDirection 
*Syntax: void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)  
*Service ID[hex]: 0x01 
*Sync/Async: Synchronous 
*Reentrancy: Reentrant 
*Pin Port Pin ID number Parameters (in): Direction Port Pin Direction 
*Parameters(inout): None  
*Parameters (out): None 
*Return value: None 
*Description: Sets the port pin direction 
************************************************************************************/
#if (PortSetPinDirectionApi == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction){
	boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
     if (PORT_NOT_INITIALIZED == g_PORT_Status)
      {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_UNINIT);
         error = TRUE;
         return;
      }
      else
	{
		/* No Action Required */
	}
     if(Pin >= PORT_CONFIGURED_CHANNLES){
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_PARAM_PIN);
       error = TRUE;
     }
     else
     {
              /* No Action Required */
     }
     if(g_PORT_CONFIG->Channels[Pin].directionChangeable == PinDirectionChangeable_OFF){
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIR_SID, PORT_E_DIRECTION_UNCHANGEABLE);
       error = TRUE;
     }
     else
     {
              /* No Action Required */
     }
#endif
     if(FALSE == error)
	{
          
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
          volatile uint32* PortGpio_Ptr = NULL_PTR;
          switch(g_PORT_CONFIG->Channels[Pin].port_num)
        {
            case  0: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
            case  1: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
            case  2: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
            case  3: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
            case  4: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
            case  5: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
        }
         if( (g_PORT_CONFIG->Channels[Pin].port_num == 2) && (g_PORT_CONFIG->Channels[Pin].pin_num <= 3) ) /* PC0 to PC3 */
        { 
          /* JTAG pins */
        }
        else
        {
          /* Do Nothing ... No need to unlock the commit register for this pin */
        }
      
		if(Direction == PORT_PIN_OUT)
                {
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);
	        }
                else if(Direction == PORT_PIN_IN)
                {
		 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,g_PORT_CONFIG->Channels[Pin].pin_num);
                }
                else{
                  /* Do Nothing */
                }
}
}
#endif

/************************************************************************************
*Service name: Port_RefreshPortDirection 
*Syntax: void Port_RefreshPortDirection(void)  
*Service ID[hex]: 0x02 
*Sync/Async: Synchronous 
*Reentrancy: Non Reentrant 
*Parameters (in): None 
*Parameters(inout): None 
*Parameters (out): None 
*Return value: None 
*Description: Refreshes port direction. 
************************************************************************************/
void Port_RefreshPortDirection(void){
  boolean error = FALSE;
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
     if (PORT_NOT_INITIALIZED == g_PORT_Status)
      {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIR_SID, PORT_E_UNINIT);
         error = TRUE;
      }
     else{
     /*Do Nothing*/
     }
     
#endif
     if(FALSE == error){
     uint8 index;
     volatile uint32* PortGpio_Ptr = NULL_PTR;
     for(index = 0; index < PORT_CONFIGURED_CHANNLES  ;index++){
       if( (g_PORT_CONFIG->Channels[index].port_num == 2) && (g_PORT_CONFIG->Channels[index].pin_num <= 3) ) /* PC0 to PC3 */
        {
          /* JTAG pins */
          continue;
        }
        else
        {
          /* Do Nothing ... No need to unlock the commit register for this pin */
        }
       if(g_PORT_CONFIG->Channels[index].directionChangeable == PinDirectionChangeable_ON){
          continue;
       }
       else if(g_PORT_CONFIG->Channels[index].direction == PORT_PIN_OUT){
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  g_PORT_CONFIG->Channels[index].pin_num);
	        }
        else if(g_PORT_CONFIG->Channels[index].direction == PORT_PIN_IN)
                {
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  g_PORT_CONFIG->Channels[index].pin_num);
                }
        else{
            /* Do Nothing */
         }
     }
     }
}

/************************************************************************************
*Service name: Port_GetVersionInfo 
*Syntax: void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)  
*Service ID[hex]: 0x03 
*Sync/Async: Synchronous 
*Reentrancy: Non Reentrant 
*Parameters (in): None 
*Parameters (inout):None  
*Parameters (out): versioninfo Pointer to where to store the version information of this module. 
*Return value: None 
*Description: Returns the version information of this module. 
************************************************************************************/
#if (Port_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif 
          /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
*Service name: Port_SetPinMode 
*Syntax: void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode) 
*Service ID[hex]: 0x04 
*Sync/Async: Synchronous 
*Reentrancy: Reentrant 
*Pin Port Pin ID number Parameters (in): Mode New Port Pin mode to be set on port pin. 
*Parameters(inout):  None 
*Parameters (out): None 
*Return value: None 
*Description: Sets the port pin mode. 
************************************************************************************/
#if (PortSetPinModeApi == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode){
    boolean error = FALSE;
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
     if (PORT_NOT_INITIALIZED == g_PORT_Status)
      {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
         error = TRUE;
      }
     else{
     /*Do Nothing*/
     }
     if(g_PORT_CONFIG->Channels[Pin].modeChangeable == PinModeChangeable_OFF){
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
                error = TRUE;
     }
     else{
     /*Do Nothing*/
     }
      if(Pin >= PORT_CONFIGURED_CHANNLES){
       Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
       error = TRUE;
     }
     else
     {
              /* No Action Required */
     }
     if(Mode != PORT_PIN_DIO_MODE && Mode != PORT_PIN_UART_MODE && Mode != PORT_PIN_SSI_MODE && Mode != PORT_PIN_I2C_MODE && Mode != PORT_PIN_PWM0_MODE && Mode !=PORT_PIN_PWM1_MODE && PORT_PIN_ADC_MODE && Mode != PORT_PIN_CAN_MODE){
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
      error = TRUE;
     }
     else
     {
              /* No Action Required */
     }
    #endif
     if(FALSE == error){
  	/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
          volatile uint32* PortGpio_Ptr = NULL_PTR;
          switch(g_PORT_CONFIG->Channels[Pin].port_num)
        {
            case  0: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
            case  1: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
            case  2: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
            case  3: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
            case  4: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
            case  5: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
        }
         if(g_PORT_CONFIG->Channels[Pin].mode == PORT_PIN_ADC_MODE){
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);        /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);      /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            }
            else{
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            }
                /* Enable the Alternate Function option only if the pin isn't GPIO */
      if (Mode == PORT_PIN_DIO_MODE)
      {
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
      }
      else
      {
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , g_PORT_CONFIG->Channels[Pin].pin_num);             /* Set Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */
      }
           switch(Mode)
            {
              case PORT_PIN_DIO_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_UART_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_UART_MODE << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;  
              case PORT_PIN_SSI_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_SSI_MODE << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_I2C_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_I2C_MODE  << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_PWM0_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_PWM0_MODE  << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_PWM1_MODE : 
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_PWM1_MODE  << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_ADC_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_ADC_MODE  << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
              case PORT_PIN_CAN_MODE :
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) = (*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) & ~(0x0000000F << (g_PORT_CONFIG->Channels[Pin].pin_num * 4))) | (PORT_PIN_CAN_MODE  << (g_PORT_CONFIG->Channels[Pin].pin_num * 4));
                break;
            }
     }
}
#endif