/** @file mainpage.h
* @brief Definition of class Template
*
* $Header: /nfs/slac/g/glast/ground/cvs/workbook/pages/advanced_doxygen/usingDoxygen.htm,v 1.1.1.1 2007/06/29 15:03:16 chuckp Exp $
*/
/** @mainpage CIoT - Programming Guide
*
* @authors Wesley José Santos
*
* @section intro Introduction
* This is the documentation for Connected IoT (CIOT). CIoT is a library created to facilitate the implementation of IoT devices.
* This document describes how to use CIoT APIs. The CIoT source code is based on interfaces implementations. Each interface have it own types.
* CIoT implementations are divided in some <a href="topics.html">topics</a> to better organize the code.
*<p> Each interface implementation follow an general common abstraction defined by the CIoT Core. An interface header file must implement the following methods:
* - ciot_iface_new(handle): Create a new interface instance
* - ciot_iface_start(self, cfg): Start the interface using the specified configuration
* - ciot_iface_stop(self): Stop the interface
* - ciot_iface_process_req(self, req): Use the interface to process an external request
* - ciot_iface_send_data(self, data, size): User the interface to send data
* <hr>
* @section notes Release notes
* This software is under development. Release notes will be provided on first official release.
* <hr>
* @section requirements Requirements
* @verbatim 
 - Mingw32 for Windows
 - ESP IDF for Espressif devices
 - nRF5 SDK 17 for Nordic devices 
 @endverbatim
* <hr>
* @todo Create readme.md
* @todo Create an common decoding/encoding abstraction
* @todo Implement ciot_s and slip encoding/decoding modules using the ciot_decoding abstraction
* @todo Integrate the modular decoding/encoding tool to serial interfaces like UART/USB/Bluetooth
* @todo Add support to STM32 devices
* @todo Implement ciot_mbus interface
* @todo Implement ciot_opcuas interface
* @todo Implement ciot_opcuac interface
* @todo Implement unit tests
* @todo Create GHA to generate TAGs and Releases
* @todo Create a more detailed version of this documentation
*
*/