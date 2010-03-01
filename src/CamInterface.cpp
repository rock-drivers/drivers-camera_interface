/* 
 * File:   CamInterface.cpp
 * Author: developer
 * 
 * Created on February 9, 2010, 8:27 AM
 */

#include "CamInterface.h"
#include <iostream>

//default settings for all cameras
//use settings which most cameras supports !!!
const int kDefaultImageWidth = 640;
const int kDefaultImageHeight = 480;
const camera::frame_mode_t kDefaultImageMode = camera::MODE_RGB;
const int kDefaultColorDepth = 3;                       // in bytes per pixel

namespace camera
{
    CamInterface::CamInterface()
    {
        image_size_ = frame_size_t(kDefaultImageWidth,kDefaultImageHeight);
        image_mode_ = kDefaultImageMode;
        image_color_depth_ = kDefaultColorDepth;
        act_grab_mode_ = Stop;
    }

    CamInterface::~CamInterface()
    {
         
    }

    bool CamInterface::setFrameSettings(  const frame_size_t size,
                                          const frame_mode_t mode,
                                          const uint8_t color_depth,
                                          const bool resize_frames)
    {
        image_size_ = size;
        image_mode_ = mode;
        image_color_depth_ = color_depth;
        return true;
    }


    bool CamInterface::setFrameSettings(const Frame &frame,
                                        const bool resize_frames)
    {
        return setFrameSettings(frame.size,frame.frame_mode,
                                frame.getPixelSize(),resize_frames);
    }

    bool CamInterface::findCamera
                        (const CamInfo &pattern,CamInfo &cam )const
     {
        std::vector<CamInfo> list;
        listCameras(list);

        for(int i=0; i< list.size();++i)
        {
            if (list[i].matches(pattern))
            {
                cam = list[i];
                return true;
            }
        }
        return false;
    }

     bool CamInterface::open2(const CamInfo &pattern,const AccessMode mode)
     {
        CamInfo info;
        if(findCamera(pattern,info))
            return open(info,mode);
        else
             throw std::runtime_error("Can not find camera!");
        return false;
     }

    bool CamInterface::open2(const std::string &display_name,
                             const AccessMode mode)
    {
        CamInfo info;
        info.display_name = display_name;
        if(findCamera(info,info))
            return open(info,mode);
        else
             throw std::runtime_error("Can not find camera!");
        return false;
    }

    int CamInterface::countCameras()const
    {
        std::vector<CamInfo> cam_infos;
        return listCameras(cam_infos);
    }

    CamInterface& CamInterface::operator>>(Frame &frame)
    {
        if(act_grab_mode_ == Stop)
            grab(SingleFrame,1);
        retrieveFrame(frame);
    }

    bool CamInterface::setFrameToCameraFrameSettings(Frame &frame)
    {
        if(!isOpen())
          throw std::runtime_error("No Camer is open!");
        frame_size_t size;
        frame_mode_t mode;
        uint8_t depth;
        getFrameSettings(size,mode,depth);
        frame.init(size.width,size.height,depth,mode);
        return true;
    }
}
