/**
 * @file DHT11.c
 * @author Ailton Fidelix
 * @brief DHT11 sensor library for ESP-IDF
 * @version 1.0.0
 * @date 20-04-2023
 * @copyright Copyright (c) 2023
 */

#include "DHT11.h"

#define NUM_OF_BITS 40
#define NUM_OF_BYTES 5

static const char *TAG = "DHT11";

uint8_t humidity = 0;
uint8_t temperature = 0;
uint8_t dht11Pin;

int dht11GetSignalLevel(int usTimeOut, int state)
{
    int uSec = 0;
    while (gpio_get_level(dht11Pin) == state)
    {
        if (uSec > usTimeOut)
        {
            ESP_LOGE(TAG, "Timeout error!");
            return -1;
        }
        uSec++;
        ets_delay_us(1);
    }
    return uSec;
}

esp_err_t dht11SetPin(uint8_t pin)
{
    ESP_LOGI(TAG, "Setting data pin...");

    dht11Pin = pin;

    return ESP_OK;
}

int8_t dht11Read()
{
    ESP_LOGI(TAG, "Reading sensor...");

    uint8_t bytes[NUM_OF_BYTES];
    uint8_t bitIdx = 7;
    uint8_t byteIdx = 0;

    for (int i = 0; i < NUM_OF_BYTES; i++)
        bytes[i] = 0;

    gpio_set_direction(dht11Pin, GPIO_MODE_OUTPUT);
    gpio_set_level(dht11Pin, 0);
    ets_delay_us(25000);
    gpio_set_level(dht11Pin, 1);
    ets_delay_us(25);
    gpio_set_direction(dht11Pin, GPIO_MODE_INPUT);

    int uSec = 0;

    uSec = dht11GetSignalLevel(85, 0);
    if (uSec < 0)
        return DHT11_TIMEOUT;

    uSec = dht11GetSignalLevel(85, 1);
    if (uSec < 0)
        return DHT11_TIMEOUT;

    // READ OUTPUT - 40 BITS
    for (int i = 0; i < NUM_OF_BITS; i++)
    {
        uSec = dht11GetSignalLevel(56, 0);
        if (uSec < 0)
            return DHT11_TIMEOUT;

        uSec = dht11GetSignalLevel(75, 1);
        if (uSec < 0)
            return DHT11_TIMEOUT;

        if (uSec > 40)
            bytes[byteIdx] |= (1 << bitIdx);
        if (bitIdx == 0) // next byte?
        {
            bitIdx = 7; // restart at MSB
            byteIdx++;  // next byte!
        }
        else
            bitIdx--;
    }

    uint8_t sum = 0;

    for (int i = 0; i < (NUM_OF_BYTES - 1); i++)
        sum += bytes[i];

    if (bytes[4] == (sum & 0xFF))
    {
        humidity = bytes[0];
        temperature = bytes[2];
        return DHT11_OK;
    }

    ESP_LOGE(TAG, "Checksum error!");
    return DHT11_ERROR_CHECKSUM;
}

uint8_t dht11GetHumidity()
{
    return humidity;
}

uint8_t dht11GetTemperature()
{
    return temperature;
}