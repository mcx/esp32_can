#include "esp32_can_builtin.h"

// add the following define into your code if you have an MCP2517FD or MCP2515 connected to the SPI bus
// #define USES_MCP2515
// or
// #define USES_MCP2517FD

#if defined(USES_MCP2517FD)
#include "mcp2517fd.h"
#elif defined(USES_MCP2515)
#include "mcp2515.h"
#endif

// only one of these can be defined
#if defined(USES_MCP2517FD) and defined(USES_MCP2515)
#error "Only one of USES_MCP2517FD or USES_MCP2515 can be defined"
#endif

extern ESP32CAN CAN0;
//Select which external chip you've got connected

#if not defined(USES_MCP2517FD) and not defined(USES_MCP2515) and ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5, 2, 0) and not SOC_TWAI_CONTROLLER_NUM == 2
#error "You must define either USES_MCP2517FD or USES_MCP2515"
#define USES_MCP2515
// #define USES_MCP2517FD
#endif

#if SOC_TWAI_CONTROLLER_NUM == 2 and ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0)
extern ESP32CAN CAN1;

#if defined(USES_MCP2517FD)
extern MCP2517FD CAN2;
#elif defined(USES_MCP2515)
extern MCP2515 CAN2;
#endif

#elif defined (USES_MCP2517FD)
extern MCP2517FD CAN1;
#elif defined (USES_MCP2515)
extern MCP2515 CAN1;
#endif

extern volatile uint32_t biIntsCounter;
extern volatile uint32_t biReadFrames;

#define Can0 CAN0

#if (SOC_TWAI_CONTROLLER_NUM == 2 and ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0)) or defined (USES_MCP2517FD) or defined (USES_MCP2515)
#define Can1 CAN1
#endif

#if (SOC_TWAI_CONTROLLER_NUM == 2 and ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 2, 0)) and (defined (USES_MCP2517FD) or defined (USES_MCP2515))
#define Can2 CAN2
#endif