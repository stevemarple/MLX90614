#include <AsyncDelay.h>
#include <SoftWire.h>
#include <MLX90614.h>

#ifdef JTD
#include <DisableJTAG.h>
#endif

MLX90614 mlx90614;
AsyncDelay powerUp;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("MLX90614_read_config");
#ifdef JTD
  disableJTAG();
#endif
  mlx90614.initialise();
  mlx90614.getSoftWire().setDelay_us(2);
  mlx90614.start();
  powerUp.start(1000, AsyncDelay::MILLIS);
  while (!powerUp.isExpired())
    mlx90614.process();
}

void loop(void)
{
  for (uint8_t addr = 0; addr < 0x20; ++addr) {
    Serial.print("RAM ");
    Serial.print(addr, HEX);
    Serial.print(": ");
    Serial.println(mlx90614.read(addr), HEX);
  }

  for (uint8_t addr = 0; addr < 0x20; ++addr) {
    Serial.print("EEPROM ");
    Serial.print(addr, HEX);
    Serial.print(": ");
    Serial.println(mlx90614.read(0x20 | addr), HEX);
  }

  Serial.print("FLAGS: ");
  Serial.println(mlx90614.read(0xF0), HEX);
  delay(10000);
}
