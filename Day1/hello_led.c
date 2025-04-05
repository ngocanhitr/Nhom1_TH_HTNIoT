#include <stdint.h>
#include <system_stm32f4xx.h>
#include <stdint.h>
#include <timer.h>
#include <Ucglib.h>

static ucg_t ucg;

int main(void)
{
	SystemCoreClockUpdate();	// cap clock
	TimerInit();				// de khoi tao chuc nang timer

	// Khoi tao LCD
	Ucglib4WireSWSPI_begin(&ucg, UCG_FONT_MODE_SOLID);
	ucg_ClearScreen(&ucg);

	ucg_SetFont(&ucg, ucg_font_helvR08_tf);	// lua chon font chu va co chu
	ucg_SetColor(&ucg, 0, 255, 255, 255);	// chon mau chu la mau trang
	ucg_SetColor(&ucg, 1, 0, 0, 0);			// mau background la mau den
	ucg_SetRotate180(&ucg);					// quay man hinh lai 180 do
	ucg_DrawString(&ucg, 0, 12, 0, "Nhom 1"); // in dong chu ra LCD
	ucg_DrawString(&ucg, 0, 26, 0, "Love Embedded");
	ucg_DrawString(&ucg, 0, 40, 0, "Programming");

	/* Loop forever */
	while(1)
	{
		processTimerScheduler();
	}
}
