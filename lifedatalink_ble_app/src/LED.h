extern "C"{
  #include "nrf_drv_spi.h"
}

#include <stdint.h> /**< For uint8_t */

class LED {
public:
  char color[6];
  static volatile inline bool spi_xfer_done = false;  /**< Flag used to indicate that SPI instance completed the transfer. */
  static const inline nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(0);  /**< SPI instance. */
  static inline uint16_t m_tx_buf[300] = { 0 };;

  LED();
  void spi_init();
  void set_color(uint32_t color);
  void spi_send(uint8_t *color);
  static void spi_event_handler(nrf_drv_spi_evt_t const * p_event, void *p_context);
};
