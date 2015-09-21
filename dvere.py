"""
Turris
"""
from __future__ import print_function
import sys
import datetime

from device import Device

if __name__ == "__main__":
    device_name = "/dev/ttyUSB0"
    device = Device(device="/dev/ttyUSB0")
    reader = device.gen_lines()

    dvere_open="[01664712] JA-81M SENSOR LB:0 ACT:1"
    dvere_closed="[01664712] JA-81M SENSOR LB:0 ACT:0"

    device = Device(device=device_name)
    reader = device.gen_lines()
    while True:
        line = reader.next()
        
	if line == dvere_open:
		device.send_command("TX ENROLL:0 PGX:0 PGY:1 ALARM:0 BEEP:NONE")
        elif line == dvere_closed:
		device.send_command("TX ENROLL:0 PGX:0 PGY:0 ALARM:0 BEEP:NONE")