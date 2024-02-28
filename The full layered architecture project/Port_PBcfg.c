#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType PORT_Configuration = {
                                             /*PORT A CONFIGURATIONS*/
  PORTA_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN5_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN6_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTA_ID, PIN7_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
                                             /*PORT B CONFIGURATIONS*/
  PORTB_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN5_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN6_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTB_ID, PIN7_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
                                             /*PORT C CONFIGURATIONS*/
  PORTC_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN5_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN6_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTC_ID, PIN7_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
                                             /*PORT D CONFIGURATIONS*/
  PORTD_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN5_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN6_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTD_ID, PIN7_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
                                             /*PORT E CONFIGURATIONS*/ 
  PORTE_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTE_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTE_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTE_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTE_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTE_ID, PIN5_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
                                             /*PORT F CONFIGURATIONS*/
  PORTF_ID, PIN0_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTF_ID, PIN1_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTF_ID, PIN2_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTF_ID, PIN3_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,
  PORTF_ID, PIN4_ID, PORT_PIN_DIO_MODE, PORT_PIN_IN, Level_LOW, PinDirectionChangeable_ON, PinModeChangeable_ON,OFF,                   
};