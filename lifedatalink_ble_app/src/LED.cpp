extern "C"{
  #include "nrf_drv_spi.h"
}

#include "LED.h"

LED::LED(){
  this->led_spi_init();
}

void LED::led_spi_init() {
  static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(0);  /**< SPI instance. */
  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
  spi_config.mosi_pin = 36;
  spi_config.frequency = NRF_DRV_SPI_FREQ_1M;
  APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, LED::led_spi_event_handler, NULL));
}

void LED::set_color(const char color[6]) {
  this->led_spi_send(((uint8_t *)color));
}

void LED::led_spi_send(uint8_t *color) {
  /* code */
}

void LED::led_spi_event_handler(nrf_drv_spi_evt_t const * p_event, void *p_context) {
  LED::spi_xfer_done = true;
}
