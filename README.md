# DHT11 library for ESP-IDF

This library allow work with the DHT11 sensor and read it values.


## How to use

If you are using PlatformIO, you can just clone this project in the **lib** folder. 

```
cd lib/ && git clone https://github.com/AiltonFidelix/DHT11
```

Otherwise, just copy this project and use however you want.

## Example

```
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include <DHT11.h>

static const char *TAG = "Example";

void app_main(void)
{

    ESP_LOGI(TAG, "Starting DHT11 example...");

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    dht11SetPin(DHT11_DEFAULT_PIN);

    while (1)
    {
        if (dht11Read() == DHT11_OK)
        {
            ESP_LOGI(TAG, "Humidity: %d", dht11GetHumidity());
            ESP_LOGI(TAG, "Temperature: %d", dht11GetTemperature());
        }
        else
        {
            ESP_LOGE(TAG, "Error reading DHT11 sensor!");
        }

        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}
```

### Author

Created by Ailton Fidelix

[![Linkedin Badge](https://img.shields.io/badge/-Ailton-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/ailtonfidelix/)](https://www.linkedin.com/in/ailton-fidelix-9603b31b7/) 
