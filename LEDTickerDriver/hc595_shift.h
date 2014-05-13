#ifndef _HC595_H_
#define _HC595_H_

void hc595_init();
void hc595_shiftByte(uint8_t data);
void hc595_shiftBit(uint8_t data, uint8_t bit);

void hc595_clk();
void hc595_latchLow();
void hc595_latchHigh();
void hc595_dataLow();
void hc595_dataHigh();
void hc595_dataRedLow();
void hc595_dataRedHigh();

#endif
