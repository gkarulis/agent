/*
 * Machine.cpp
 *
 *  Created on: 11/lug/2013
 *      Author: stefano
 */

#include "Machine.h"
#include "Support.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>

Machine::Machine()
{
	_GetDMIDecodeData();
}


Machine::~Machine()
{
}


std::string
Machine::BIOSVersion() const
{
	return fBiosVersion;
}


std::string
Machine::BIOSManufacturer() const
{
	return fBiosManufacturer;
}


std::string
Machine::BIOSDate() const
{
	return fBiosDate;
}


std::string
Machine::MachineManufacturer() const
{
	return fMachineManufacturer;
}


void
Machine::_GetDMIDecodeData()
{
	popen_streambuf dmi;
	dmi.open("dmidecode", "r");
	std::istream iStream(&dmi);

	std::string string;
	while (std::getline(iStream, string) > 0) {
		//std::cout << "*** " << string << " ***" << std::endl;
		if (string.find("BIOS Information") != std::string::npos)
			_GetBIOSInfo(iStream);
		else if (string.find("System Information") != std::string::npos) {
			_GetSystemInfo(iStream);
		}
	}
}


void
Machine::_GetBIOSInfo(std::istream& stream)
{
	std::map<std::string, std::string> stringMap;
	std::string string;
	size_t pos = 0;
	std::string vendorString = "Vendor: ";
	std::string versionString = "Version: ";
	std::string dateString = "Release Date: ";
	while (std::getline(stream, string) > 0) {
		std::cout << "**" << string << "**" << std::endl;
		if (string == "")
			break;

		pos = string.find(vendorString);
		if (pos != std::string::npos) {
			fBiosManufacturer = string.substr(pos + vendorString.length(), std::string::npos);
			continue;
		}

		pos = string.find(versionString);
		if (pos != std::string::npos) {
			fBiosVersion = string.substr(pos + versionString.length(), std::string::npos);
			continue;
		}

		pos = string.find(dateString);
		if (pos != std::string::npos) {
			fBiosDate = string.substr(pos + dateString.length(), std::string::npos);
			continue;
		}
	}
}


void
Machine::_GetSystemInfo(std::istream& stream)
{
	std::cout << "GetSystemInfo()" << std::endl;
	std::map<std::string, std::string> stringMap;

	std::string string;
	size_t pos = 0;
	std::string manufacturerString = "Manufacturer: ";
	std::string ssnString = "Serial Number: ";
	std::string productString = "Product Name: ";
	while (std::getline(stream, string) > 0) {
		std::cout << "sys ** " << string << "*** " << std::endl;
		if (string == "")
			break;

		pos = string.find(":");
		if (pos == std::string::npos)
			continue;

		stringMap[string.substr(0, pos)] = string.substr(pos + 2, std::string::npos);
	}

	std::map<std::string, std::string>::const_iterator i;
	for (i = stringMap.begin(); i != stringMap.end(); i++) {
		std::cout << "name: " << (*i).first << " value: " << (*i).second << std::endl;
	}
}