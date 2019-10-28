#include "modes.h"
#include "gps.h"
#include "common.h"


Thread testmode_thread(osPriorityNormal, 1024); // 1K stack size

void test_mode() {
	while(event_flags.wait_any(TEST_MODE)){
		pc.printf("\n\rSoil Moisture: %.2f%%\
		\n\rLIGHT: %.2f%%\
		\n\rACCELEROMETER: X_axis: %.2f, Y_axis: %.2f, Z_axis: %.2f\
		\n\rTEMP/HUM: Temperature: %.2f C. Relative Humidity: %.4f%\
		\n\r#Sats: %d, Lat(UTC): %.6f, Long(UTC): %.6f, Altitude: %.1f\
		\n\rGPS_time: %02d:%02d:%02d\
		\n\rClear (%d), Red (%d), Green (%d), Blue (%d), Dominant Color: %c\
		\n",\
		valueSM,\
		valueLight,\
		x, y, z,\
		temp, hum,\
		gps_info.nsats, gps_info.lat, gps_info.lon, gps_info.alt,\
		gps_info.hour, gps_info.minute, gps_info.seconds,\
		clear_value, red_value, green_value, blue_value, dominant_colour);
	}
}
