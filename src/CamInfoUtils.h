/* 
 * File:   CamInfoUtils.h
 * Author: cgaudig
 *
 * Created on February 24, 2010, 11:44 AM
 */

#include "CamTypes.h"
#include <iostream>

#ifndef _CAMINFOUTILS_H
#define	_CAMINFOUTILS_H

namespace camera
{
    static void showCamInfo(CamInfo cam_info)
    {
        std::cout << std::endl << "=== begin CamInfo ===" << std::endl
            << "display_name: " << cam_info.display_name << std::endl
            << "interface_id: " << cam_info.interface_id << std::endl
            << "interface_type: " << enumInterfaceToStr(cam_info.interface_type) << std::endl
            << "current_ip_address: " << cam_info.ip_settings.current_ip_address << std::endl
            << "current_ip_subnet: " << cam_info.ip_settings.current_ip_subnet  << std::endl
            << "part_number: " << cam_info.part_number << std::endl
            << "part_version: " << cam_info.part_version << std::endl
            << "permitted_access: " << cam_info.permitted_access << std::endl
            << "reachable: " << cam_info.reachable << std::endl
            << "serial_string: " << cam_info.serial_string << std::endl
            << "unique_id: " << cam_info.unique_id << std::endl
            << "===  end CamInfo  ===" << std::endl << std::endl;
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

