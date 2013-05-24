/* 
 * File:   CamInfoUtils.h
 * Author: cgaudig
 *
 * Created on February 24, 2010, 11:44 AM
 */

#include "CamTypes.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <arpa/inet.h>

#ifndef _CAMINFOUTILS_H
#define	_CAMINFOUTILS_H

namespace camera
{
    static std::string getCamInfo(const CamInfo &cam_info)
    {
       std::stringstream str; 
       struct in_addr ip_address, ip_subnet, ip_gateway;
       ip_address.s_addr = cam_info.ip_settings.current_ip_address;
       ip_subnet.s_addr = cam_info.ip_settings.current_ip_subnet;
       ip_gateway.s_addr = cam_info.ip_settings.current_ip_gateway;

       std::string ip = inet_ntoa(ip_address);
       std::string subnet = inet_ntoa(ip_subnet);
       std::string gateway = inet_ntoa(ip_gateway);

       str  << std::endl << "=== begin CamInfo ===" << std::endl
            << "display_name: " << cam_info.display_name << std::endl
            << "interface_id: " << cam_info.interface_id << std::endl
            << "interface_type: " << enumInterfaceToStr(cam_info.interface_type) << std::endl
            << "current_ip_address: " << ip << std::endl
            << "current_ip_subnet: " << subnet << std::endl
            << "current_ip_gateway: " << gateway << std::endl
            << "part_number: " << cam_info.part_number << std::endl
            << "part_version: " << cam_info.part_version << std::endl
            << "permitted_access: " << cam_info.permitted_access << std::endl
            << "reachable: " << cam_info.reachable << std::endl
            << "serial_string: " << cam_info.serial_string << std::endl
            << "unique_id: " << cam_info.unique_id << std::endl
            << "===  end CamInfo  ===" << std::endl << std::endl;
       return str.str();
    }
    
    static void showCamInfo(const CamInfo &cam_info)
    {
       std::cout << getCamInfo(cam_info);
        //cam_info.
    }

    static void showCamInfos(std::vector<CamInfo> &cam_infos)
    {
        int inum = cam_infos.size();
        std::cout << "Found " << inum<< " cameras:\n";
        for(int i=0;i<inum;i++)
            showCamInfo(cam_infos[i]);
    }
}
#endif	/* _CAMINFOUTILS_H */

