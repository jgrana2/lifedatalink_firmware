extern "C"{
  #include "nrf_drv_spi.h"
}

#include <stdint.h> //For uint8_t

class LED {
public:
  char color[6];
  static volatile inline bool spi_xfer_done = false;  /**< Flag used to indicate that SPI instance completed the transfer. */
  LED();
  void led_spi_init();
  void set_color(const char color[6]);
  void led_spi_send(uint8_t *color);
  static void led_spi_event_handler(nrf_drv_spi_evt_t const * p_event, void *p_context);
};

// inline bool LED::spi_xfer_done = false;
