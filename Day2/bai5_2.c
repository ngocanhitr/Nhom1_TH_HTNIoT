#include <stdint.h>
#include <stm32f401re_gpio.h>
#include <stm32f401re_rcc.h>
#include <typedefs.h>

#define BTN_PRESS							0
// Define Logic GPIO_PIN

#define GPIO_PIN_SET						1
#define GPIO_PIN_RESET						0

// Define GPIO PIN

#define BUZZER_GPIO_PORT					GPIOC
#define BUZZER_GPIO_PIN						GPIO_Pin_9
#define BUZZERControl_SetClock				RCC_AHB1Periph_GPIOC

#define BUTTON_GPIO_PORT					GPIOB
#define BUTTON_GPIO_PIN						GPIO_Pin_4
#define BUTTONControl_SetClock				RCC_AHB1Periph_GPIOB

static void_t buzzer_Init(void_t);
static void_t button_Init(void_t);
static void_t buzzerControlSetStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin, u8_t byStatus);
static u8_t buttonReadStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin);

void_t delay();

int main(void_t) {
	u8_t byStatus = 1;
	buzzer_Init();
	button_Init();
	while (1) {

		if (buttonReadStatus(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN) == BTN_PRESS) {
			delay();
			byStatus++;
		}
		if (byStatus % 2 == 0) {
			delay();
			buzzerControlSetStatus(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_SET);
		} else {
			delay();
			buzzerControlSetStatus(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN, GPIO_PIN_RESET);
		}
	}
	return 0;
}

void_t delay() {
	for (u32_t i = 0; i < 200000; i++);
}

static void_t buzzer_Init(void_t) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(BUZZERControl_SetClock, ENABLE);


	GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;


	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;


	GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);

}

static void_t button_Init(void_t) {

	GPIO_InitTypeDef GPIO_InitStructure;



	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);


	GPIO_InitStructure.GPIO_Pin = BUTTON_GPIO_PIN;


	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;


	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;


	GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStructure);
}

static void_t buzzerControlSetStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin,
		u8_t byStatus) {
	// SET bit in BSRR Registers

	if (byStatus == GPIO_PIN_SET) {
		pGPIOx->BSRRL = wGPIO_Pin;
	}
	if (byStatus == GPIO_PIN_RESET) {
		pGPIOx->BSRRH = wGPIO_Pin;
	}
}

static u8_t buttonReadStatus(GPIO_TypeDef *pGPIOx, u16_t wGPIO_Pin) {
	u8_t Read_Pin = Bit_RESET;

	if ((pGPIOx->IDR & wGPIO_Pin) != (u32_t) Bit_RESET) {
		Read_Pin = (u8_t) Bit_SET;
	} else {
		Read_Pin = (u8_t) Bit_RESET;
	}
	return Read_Pin;
}