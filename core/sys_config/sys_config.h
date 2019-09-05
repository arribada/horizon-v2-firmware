/* sys_config.h - Configuration data and tag definitions
 *
 * Copyright (C) 2018 Arribada
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>

// Constants
#define SYS_CONFIG_NO_ERROR               ( 0)
#define SYS_CONFIG_ERROR_INVALID_TAG      (-1)
#define SYS_CONFIG_ERROR_WRONG_SIZE       (-2)
#define SYS_CONFIG_ERROR_NO_MORE_TAGS     (-3)
#define SYS_CONFIG_ERROR_TAG_NOT_SET      (-4)

#define SYS_CONFIG_FORMAT_VERSION (4) // This should be incremented when/if the sys_config layout is modified

#define SYS_CONFIG_MAX_DATA_SIZE (60) // Max size the configuration tag's data can be in bytes

#define SYS_CONFIG_TAG_ID_SIZE (sizeof(uint16_t))
#define SYS_CONFIG_TAG_DATA_SIZE(tag_type) (sizeof(((tag_type *)0)->contents)) // Size of data in tag. We exclude the set member
#define SYS_CONFIG_TAG_MAX_SIZE (SYS_CONFIG_MAX_DATA_SIZE + SYS_CONFIG_TAG_ID_SIZE) // Max size the configuration tag can be

#define SYS_CONFIG_TAG_TOTAL_NUMBER (51) // Number of configuration tags - WARN: This has to be manually updated

#define SYS_CONFIG_GPS_TRIGGER_MODE_SWITCH_TRIGGERED (0)
#define SYS_CONFIG_GPS_TRIGGER_MODE_SCHEDULED        (1)
#define SYS_CONFIG_GPS_TRIGGER_MODE_HYBRID           (2)

#define SYS_CONFIG_AXL_MODE_PERIODIC      (0)
#define SYS_CONFIG_AXL_MODE_TRIGGER_ABOVE (3)

#define SYS_CONFIG_PRESSURE_MODE_PERIODIC        (0)
#define SYS_CONFIG_PRESSURE_MODE_TRIGGER_BELOW   (1)
#define SYS_CONFIG_PRESSURE_MODE_TRIGGER_BETWEEN (2)
#define SYS_CONFIG_PRESSURE_MODE_TRIGGER_ABOVE   (3)

#define SYS_CONFIG_TEMP_MODE_PERIODIC        (0)
#define SYS_CONFIG_TEMP_MODE_TRIGGER_BELOW   (1)
#define SYS_CONFIG_TEMP_MODE_TRIGGER_BETWEEN (2)
#define SYS_CONFIG_TEMP_MODE_TRIGGER_ABOVE   (3)

#define SYS_CONFIG_TAG_BLUETOOTH_TRIGGER_CONTROL_REED_SWITCH  (1 << 0)
#define SYS_CONFIG_TAG_BLUETOOTH_TRIGGER_CONTROL_SCHEDULED    (1 << 1)
#define SYS_CONFIG_TAG_BLUETOOTH_TRIGGER_CONTROL_GEOFENCE     (1 << 2)

#define SYS_CONFIG_TAG_BLUETOOTH_PHY_MODE_1_MBPS  (0)
#define SYS_CONFIG_TAG_BLUETOOTH_PHY_MODE_2_MBPS  (1)

enum
{
    // GPS
    SYS_CONFIG_TAG_GPS_LOG_POSITION_ENABLE = 0x0000,         // Enable logging of position information.
    SYS_CONFIG_TAG_GPS_LOG_TTFF_ENABLE,                      // Enable logging of time to first fix (TTFF)
    SYS_CONFIG_TAG_GPS_TRIGGER_MODE,                         // Mode shall allow for continuous operation or external switch triggered operation.
    SYS_CONFIG_TAG_GPS_SCHEDULED_ACQUISITION_INTERVAL,       // Interval in seconds between GPS acquisition attempts. Setting to zero means always on
    SYS_CONFIG_TAG_GPS_MAXIMUM_ACQUISITION_TIME,             // Maximum time period, in seconds, to allow for GPS fixes. Setting to zero means no upper limit
    SYS_CONFIG_TAG_GPS_SCHEDULED_ACQUISITION_NO_FIX_TIMEOUT, // When triggered by a scheduled acquisition, this is the timeout period in seconds during acquisition after which to shutdown the GPS if no fix is found
    SYS_CONFIG_TAG_GPS_LAST_KNOWN_POSITION,                  // Shall contain the last fix position before provisioning mode was entered. If no fix was found since powered on, then the field shall be set to all 0x00 bytes
    SYS_CONFIG_TAG_GPS_VERY_FIRST_FIX_HOLD_TIME,             // The time period to continue logging after the very first GPS fix has been achieved. This is used to ensure an up to date ephemeris is aquired
    SYS_CONFIG_TAG_GPS_DEBUG_LOGGING_ENABLE,                 // Enable logging of the GPS being switched on and off

    // Saltwater Switch
    SYS_CONFIG_SALTWATER_SWITCH_LOG_ENABLE = 0x0800, // Controls whether switch change states should be logged
    SYS_CONFIG_SALTWATER_SWITCH_HYSTERESIS_PERIOD,   // Switch de-bouncing period in milliseconds i.e., the switch should remain in a stable closed state for this period before considering the unit as sub-merged and powering down GPS acquisition. Set to zero for no debouncing

    // Real time crystal
    SYS_CONFIG_TAG_RTC_SYNC_TO_GPS_ENABLE = 0x0600, // If set, the RTC will sync to GPS time
    SYS_CONFIG_TAG_RTC_CURRENT_DATE_AND_TIME,       // Current date and time

    // Logging
    SYS_CONFIG_TAG_LOGGING_ENABLE = 0x0100,              // Controls whether the global logging function is enabled or disabled.
    SYS_CONFIG_TAG_LOGGING_FILE_SIZE,                    // Maximum file size allowed for logging. This is set when the logging file is created.
    SYS_CONFIG_TAG_LOGGING_FILE_TYPE,                    // Indicates fill or circular mode. This is set when the logging file is created.
    SYS_CONFIG_TAG_LOGGING_GROUP_SENSOR_READINGS_ENABLE, // If set, the logging engine should attempt to group multiple sensor readings together into a single log entry.
    SYS_CONFIG_TAG_LOGGING_START_END_SYNC_ENABLE,        // If set, each log entry shall be framed with a start and end sync. This is set when the logging file is created.
    SYS_CONFIG_TAG_LOGGING_DATE_TIME_STAMP_ENABLE,       // If set, the RTC date & time shall be logged with each long entry.
    SYS_CONFIG_TAG_LOGGING_HIGH_RESOLUTION_TIMER_ENABLE, // If set, the HRT shall be logged with each long entry.

    // Accelerometer
    SYS_CONFIG_TAG_AXL_LOG_ENABLE = 0x0200,             // The AXL shall be enabled for logging.
    SYS_CONFIG_TAG_AXL_CONFIG,                          // G-force setting, sensitivity mode, etc.
    SYS_CONFIG_TAG_AXL_G_FORCE_HIGH_THRESHOLD,          // The X2+Y2+Z2 vector magnitude threshold.
    SYS_CONFIG_TAG_AXL_SAMPLE_RATE,                     // Number of times per second to perform a reading of the AXL.
    SYS_CONFIG_TAG_AXL_MODE,                            // 0=>PERIODIC, 3=>TRIGGER_ABOVE
    SYS_CONFIG_TAG_AXL_SCHEDULED_ACQUISITION_INTERVAL,  // Interval in seconds between AXL readings. Setting to zero means always on
    SYS_CONFIG_TAG_AXL_MAXIMUM_ACQUISITION_TIME,        // How long to capture readings for per scheduled acquisition period, in seconds

    // Pressure sensor
    SYS_CONFIG_TAG_PRESSURE_SENSOR_LOG_ENABLE = 0x0300,      // The pressure sensor shall be enabled for logging.
    SYS_CONFIG_TAG_PRESSURE_SAMPLE_RATE,                     // Number of times per second to perform a reading of the pressure sensor.
    SYS_CONFIG_TAG_PRESSURE_LOW_THRESHOLD,                   // Low threshold setting.
    SYS_CONFIG_TAG_PRESSURE_HIGH_THRESHOLD,                  // High threshold setting.
    SYS_CONFIG_TAG_PRESSURE_MODE,                            // 0=>PERIODIC, 1=>TRIGGER_BELOW, 2=>TRIGGER_BETWEEN, 3=>TRIGGER_ABOVE
    SYS_CONFIG_TAG_PRESSURE_SCHEDULED_ACQUISITION_INTERVAL,  // Interval in seconds between pressure sensor readings. Setting to zero means always on
    SYS_CONFIG_TAG_PRESSURE_MAXIMUM_ACQUISITION_TIME,        // How long to capture readings for per scheduled acquisition period, in seconds

    // Temperature sensor
    SYS_CONFIG_TAG_TEMP_SENSOR_LOG_ENABLE = 0x0700,  // The sensor shall be enabled for logging.
    SYS_CONFIG_TAG_TEMP_SENSOR_SAMPLE_RATE,          // Number of times per second to perform a reading of the sensor.
    SYS_CONFIG_TAG_TEMP_SENSOR_LOW_THRESHOLD,        // Low threshold setting.
    SYS_CONFIG_TAG_TEMP_SENSOR_HIGH_THRESHOLD,       // High threshold setting.
    SYS_CONFIG_TAG_TEMP_SENSOR_MODE,                 // 0=>PERIODIC, 1=>TRIGGER_BELOW, 2=>TRIGGER_BETWEEN, 3=>TRIGGER_ABOVE

    // System
    SYS_CONFIG_TAG_SYSTEM_DEVICE_IDENTIFIER = 0x0400, // Unique device identifier.

    // Bluetooth
    SYS_CONFIG_TAG_BLUETOOTH_DEVICE_ADDRESS = 0x0500,        // The device address is a 6 byte address that uniquely identifies a bluetooth device
    SYS_CONFIG_TAG_BLUETOOTH_TRIGGER_CONTROL,                // Control what triggers the bluetooth de/activation
    SYS_CONFIG_TAG_BLUETOOTH_SCHEDULED_INTERVAL,             // Bluetooth shall be enabled periodically every N seconds as specified
    SYS_CONFIG_TAG_BLUETOOTH_SCHEDULED_DURATION,             // Bluetooth shall remain on for the specified number of seconds when waiting for a connection to be made. If no connection is made during the scheduled duration then bluetooth shall be switched off
    SYS_CONFIG_TAG_BLUETOOTH_ADVERTISING_INTERVAL,           // The bluetooth advertising interval expressed in units of 0.625 ms
    SYS_CONFIG_TAG_BLUETOOTH_CONNECTION_INTERVAL,            // The bluetooth connection interval expressed in units of 1.25 ms
    SYS_CONFIG_TAG_BLUETOOTH_CONNECTION_INACTIVITY_TIMEOUT,  // When a bluetooth connection is established if no activity occurs on the connection then the connection shall be forcibly terminated after the specified of inactivity period in seconds
    SYS_CONFIG_TAG_BLUETOOTH_PHY_MODE,                       // The PHY mode to use for GATT connections
    SYS_CONFIG_TAG_BLUETOOTH_LOG_ENABLE,                     // Log all bluetooth events if enabled

    // Battery
    SYS_CONFIG_TAG_BATTERY_LOG_ENABLE = 0x0900, // The battery charge state shall be enabled for logging.
    SYS_CONFIG_TAG_BATTERY_LOW_THRESHOLD        // If set, the device will enter the low battery state and preserve any data when the battery charge goes below this threshold
};

typedef struct __attribute__((__packed__))
{
    bool set; // Whether or not this command tag has been set
} sys_config_hdr_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_gps_log_position_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_gps_log_ttff_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t mode;
    } contents;
} sys_config_gps_trigger_mode_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_gps_scheduled_acquisition_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_gps_maximum_acquisition_time_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_gps_scheduled_acquisition_no_fix_timeout_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint32_t iTOW;   // Time since navigation epoch in ms
        int32_t lon;     // Longitude (10^-7)
        int32_t lat;     // Latitude (10^-7)
        int32_t height;  // Height in mm
        uint32_t hAcc;   // Horizontal accuracy estimate
        uint32_t vAcc;   // Vertical accuracy estimate

        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
    } contents;
} sys_config_gps_last_known_position_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_gps_very_first_fix_hold_time_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_gps_debug_logging_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_saltwater_switch_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_saltwater_switch_hysteresis_period_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_rtc_sync_to_gps_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t day;
        uint8_t month;
        uint16_t year;
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
    } contents;
} sys_config_rtc_current_date_and_time_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_logging_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint32_t file_size;
    } contents;
} sys_config_logging_file_size_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t file_type;
    } contents;
} sys_config_logging_file_type_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_logging_group_sensor_readings_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_logging_start_end_sync_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_logging_date_time_stamp_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_logging_high_resolution_timer_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_axl_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t config;
    } contents;
} sys_config_axl_config_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t threshold;
    } contents;
} sys_config_axl_g_force_high_threshold_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t sample_rate;
    } contents;
} sys_config_axl_sample_rate_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t mode;
    } contents;
} sys_config_axl_mode_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_axl_scheduled_acquisition_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_axl_maximum_acquisition_time_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_pressure_sensor_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t sample_rate;
    } contents;
} sys_config_pressure_sample_rate_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t threshold;
    } contents;
} sys_config_pressure_low_threshold_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t threshold;
    } contents;
} sys_config_pressure_high_threshold_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t mode;
    } contents;
} sys_config_pressure_mode_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_pressure_scheduled_acquisition_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_pressure_maximum_acquisition_time_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_temp_sensor_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t sample_rate;
    } contents;
} sys_config_temp_sensor_sample_rate_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t threshold;
    } contents;
} sys_config_temp_sensor_low_threshold_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t threshold;
    } contents;
} sys_config_temp_sensor_high_threshold_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t mode;
    } contents;
} sys_config_temp_sensor_mode_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t id[8];
    } contents;
} sys_config_system_device_identifier_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t address[6];
    } contents;
} sys_config_tag_bluetooth_device_address_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t flags;
    } contents;
} sys_config_tag_bluetooth_trigger_control_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_tag_bluetooth_scheduled_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_tag_bluetooth_scheduled_duration_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t interval;
    } contents;
} sys_config_tag_bluetooth_advertising_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t interval;
    } contents;
} sys_config_tag_bluetooth_connection_interval_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint16_t seconds;
    } contents;
} sys_config_tag_bluetooth_connection_inactivity_timeout_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t mode;
    } contents;
} sys_config_tag_bluetooth_phy_mode_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_tag_bluetooth_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t enable;
    } contents;
} sys_config_battery_log_enable_t;

typedef struct __attribute__((__packed__))
{
    sys_config_hdr_t hdr;
    struct __attribute__((__packed__))
    {
        uint8_t threshold;
    } contents;
} sys_config_battery_low_threshold_t;

typedef struct __attribute__((__packed__))
{
    uint8_t                                                     format_version; // A version number to keep track of the format/contents of this struct
    sys_config_system_device_identifier_t                       sys_config_system_device_identifier;
    sys_config_gps_log_position_enable_t                        sys_config_gps_log_position_enable;
    sys_config_gps_log_ttff_enable_t                            sys_config_gps_log_ttff_enable;
    sys_config_gps_trigger_mode_t                               sys_config_gps_trigger_mode;
    sys_config_gps_scheduled_acquisition_interval_t             sys_config_gps_scheduled_acquisition_interval;
    sys_config_gps_maximum_acquisition_time_t                   sys_config_gps_maximum_acquisition_time;
    sys_config_gps_scheduled_acquisition_no_fix_timeout_t       sys_config_gps_scheduled_acquisition_no_fix_timeout;
    sys_config_gps_last_known_position_t                        sys_config_gps_last_known_position;
    sys_config_gps_very_first_fix_hold_time_t                   sys_config_gps_very_first_fix_hold_time;
    sys_config_gps_debug_logging_enable_t                       sys_config_gps_debug_logging_enable;
    sys_config_saltwater_switch_log_enable_t                    sys_config_saltwater_switch_log_enable;
    sys_config_saltwater_switch_hysteresis_period_t             sys_config_saltwater_switch_hysteresis_period;
    sys_config_rtc_sync_to_gps_enable_t                         sys_config_rtc_sync_to_gps_enable;
    sys_config_rtc_current_date_and_time_t                      sys_config_rtc_current_date_and_time;
    sys_config_logging_enable_t                                 sys_config_logging_enable;
    sys_config_logging_file_size_t                              sys_config_logging_file_size;
    sys_config_logging_file_type_t                              sys_config_logging_file_type;
    sys_config_logging_group_sensor_readings_enable_t           sys_config_logging_group_sensor_readings_enable;
    sys_config_logging_start_end_sync_enable_t                  sys_config_logging_start_end_sync_enable;
    sys_config_logging_date_time_stamp_enable_t                 sys_config_logging_date_time_stamp_enable;
    sys_config_logging_high_resolution_timer_enable_t           sys_config_logging_high_resolution_timer_enable;
    sys_config_axl_log_enable_t                                 sys_config_axl_log_enable;
    sys_config_axl_config_t                                     sys_config_axl_config;
    sys_config_axl_g_force_high_threshold_t                     sys_config_axl_g_force_high_threshold;
    sys_config_axl_sample_rate_t                                sys_config_axl_sample_rate;
    sys_config_axl_mode_t                                       sys_config_axl_mode;
    sys_config_axl_scheduled_acquisition_interval_t             sys_config_axl_scheduled_acquisition_interval;
    sys_config_axl_maximum_acquisition_time_t                   sys_config_axl_maximum_acquisition_time;
    sys_config_pressure_sensor_log_enable_t                     sys_config_pressure_sensor_log_enable;
    sys_config_pressure_sample_rate_t                           sys_config_pressure_sample_rate;
    sys_config_pressure_low_threshold_t                         sys_config_pressure_low_threshold;
    sys_config_pressure_high_threshold_t                        sys_config_pressure_high_threshold;
    sys_config_pressure_mode_t                                  sys_config_pressure_mode;
    sys_config_pressure_scheduled_acquisition_interval_t        sys_config_pressure_scheduled_acquisition_interval;
    sys_config_pressure_maximum_acquisition_time_t              sys_config_pressure_maximum_acquisition_time;
    sys_config_temp_sensor_log_enable_t                         sys_config_temp_sensor_log_enable;
    sys_config_temp_sensor_sample_rate_t                        sys_config_temp_sensor_sample_rate;
    sys_config_temp_sensor_low_threshold_t                      sys_config_temp_sensor_low_threshold;
    sys_config_temp_sensor_high_threshold_t                     sys_config_temp_sensor_high_threshold;
    sys_config_temp_sensor_mode_t                               sys_config_temp_sensor_mode;
    sys_config_tag_bluetooth_device_address_t                   sys_config_tag_bluetooth_device_address;
    sys_config_tag_bluetooth_trigger_control_t                  sys_config_tag_bluetooth_trigger_control;
    sys_config_tag_bluetooth_scheduled_interval_t               sys_config_tag_bluetooth_scheduled_interval;
    sys_config_tag_bluetooth_scheduled_duration_t               sys_config_tag_bluetooth_scheduled_duration;
    sys_config_tag_bluetooth_advertising_interval_t             sys_config_tag_bluetooth_advertising_interval;
    sys_config_tag_bluetooth_connection_interval_t              sys_config_tag_bluetooth_connection_interval;
    sys_config_tag_bluetooth_connection_inactivity_timeout_t    sys_config_tag_bluetooth_connection_inactivity_timeout;
    sys_config_tag_bluetooth_phy_mode_t                         sys_config_tag_bluetooth_phy_mode;
    sys_config_tag_bluetooth_log_enable_t                       sys_config_tag_bluetooth_log_enable;
    sys_config_battery_log_enable_t                             sys_config_battery_log_enable;
    sys_config_battery_low_threshold_t                          sys_config_battery_low_threshold;
} sys_config_t;

// Exposed variables
extern sys_config_t sys_config;

// Functions
int sys_config_set(uint16_t tag, void * value, uint32_t length);
int sys_config_unset(uint16_t tag);
int sys_config_get(uint16_t tag, void ** value);
int sys_config_size(uint16_t tag);
bool sys_config_is_valid(uint16_t tag);
int sys_config_iterate(uint16_t * tag, uint16_t * last_index);