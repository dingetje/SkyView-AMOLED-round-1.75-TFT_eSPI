/*
 * BatteryHelper.h
 * Copyright (C) 2019-2021 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Arduino_DriveBus_Library.h"
#include <../pins_config.h>

#ifndef BATTERYHELPER_H
#define BATTERYHELPER_H

#define isTimeToBattery()         (millis() - Battery_TimeMarker > 30000)

#define BATTERY_THRESHOLD_NIMHX2  2.3
#define BATTERY_THRESHOLD_LIPO    3.5
#define BATTERY_THRESHOLD_LIFE    3.0
#define BATTERY_THRESHOLD_NIZNX2  3.0

#define BATTERY_CUTOFF_NIMHX2     2.1
#define BATTERY_CUTOFF_LIPO       3.0
#define BATTERY_CUTOFF_NIZNX2     2.9

void  Battery_setup(void);
void  Battery_loop(void);
float Battery_voltage(void);
float Battery_threshold(void);
float Battery_cutoff(void);

#if defined(SY6970)
extern int read_SY6970_voltage(void);
extern int read_SY6970_charge_current(void);
extern int read_SY6970_charging_status(void);
extern void SY6970_setup(void);
#endif

#if defined(XPOWERS_CHIP_AXP2101)
extern void AXP2101_setup(void);
extern float read_AXP2101_voltage(void);
extern int read_AXP2101_charge_current();
extern uint8_t read_AXP2101_charging_status(void);
extern void prepare_AXP2101_deep_sleep(void);
#endif

extern int charging_status();
extern void battery_fini(void);

#endif /* BATTERYHELPER_H */
