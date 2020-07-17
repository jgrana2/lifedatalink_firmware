extern "C"{
  #include "nrf_drv_spi.h"
  #include "nrf_log.h"
}

#include "LED.h"

LED::LED(){
  this->spi_init();
}

void LED::spi_init() {
  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
  spi_config.mosi_pin = 36;
  spi_config.frequency = NRF_DRV_SPI_FREQ_1M;
  APP_ERROR_CHECK(nrf_drv_spi_init(&LED::spi, &spi_config, LED::spi_event_handler, NULL));
  NRF_LOG_INFO("LED SPI initialized");
}

void LED::set_color(uint32_t color) {
  size_t i = 0;
  for (uint32_t mask = 0x800000; mask != 0; mask >>= 1) {
    if (color & mask) {
      LED::m_tx_buf[i] = (uint16_t) 0b1110000000; //Bit is 1
      // NRF_LOG_INFO("1");
    }
    else {
      LED::m_tx_buf[i] = (uint16_t) 0b0000000111; //Bit is 0
      // NRF_LOG_INFO("0");
    }
    i++;
    // NRF_LOG_INFO("Up");
  }
  NRF_LOG_INFO("Done");
  this->spi_send(((uint8_t *)m_tx_buf));
}

void LED::spi_send(uint8_t *m_tx_buf) {
  LED::spi_xfer_done = false;
  APP_ERROR_CHECK(nrf_drv_spi_transfer(&LED::spi, m_tx_buf, 100, NULL, 0));
  NRF_LOG_INFO("Atempt send...");
}

void LED::spi_event_handler(nrf_drv_spi_evt_t const * p_event, void *p_context) {
  LED::spi_xfer_done = true;
  NRF_LOG_INFO("Color msg sent");
}
