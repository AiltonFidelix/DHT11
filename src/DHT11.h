/**
 * @file DHT11.h
 * @author Ailton Fidelix
 * @brief DHT11 sensor library for ESP-IDF
 * @version 1.0.0
 * @date 20-04-2023
 * @copyright Copyright (c) 2023
 */

#ifndef DHT11_H
#define DHT11_H

#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include <rom/ets_sys.h>

#define DHT11_OK			   0
#define DHT11_TIMEOUT	      -1
#define DHT11_ERROR_CHECKSUM  -2

#define DHT11_DEFAULT_PIN 22

esp_err_t dht11SetPin(uint8_t pin);
int8_t dht11Read();
uint8_t dht11GetHumidity();
uint8_t dht11GetTemperature();

#endif