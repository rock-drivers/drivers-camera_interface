/* 
 * File:   CamInterface.cpp
 * Author: developer
 * 
 * Created on February 9, 2010, 8:27 AM
 */

#include "CamInterface.h"
#include "CamInfoUtils.h"
#include <iostream>

//default settings for all cameras
//use settings which most cameras supports !!!
const int kDefaultImageWidth = 640;
const int kDefaultImageHeight = 480;
const base::samples::frame::frame_mode_t kDefaultImageMode = base::samples::frame::MODE_RGB;
const int kDefaultColorDepth = 3;                       // in bytes per pixel

using namespace base::samples::frame;
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

    bool CamInterface::setFrameSettings(  const base::samples::frame::frame_size_t size,
                                          const base::samples::frame::frame_mode_t mode,
                                          const uint8_t color_depth,
                                          const bool resize_frames)
    {
        image_size_ = size;
        image_mode_ = mode;
        image_color_depth_ = color_depth;
        return true;
    }


    bool CamInterface::setFrameSettings(const base::samples::frame::Frame &frame,
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
             throw std::runtime_error("Can not find camera: \n" + getCamInfo(pattern));
        return false;
     }

    bool CamInterface::open2(const std::string &display_name,
                             const AccessMode mode)
    {
        CamInfo info;
        info.display_name = display_name;
        return open2(info,mode);
    }
    
    bool CamInterface::open2(unsigned long &unique_camera_id,
					  const AccessMode mode)
    {
        CamInfo info;
        info.unique_id = unique_camera_id;
        return open2(info,mode);
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
        frame.init(size.width,size.height,depth*8,mode);
        return true;
    }
    
    std::string CamInterface::doDiagnose()
    {
      std::stringstream strstr;
      //list all cameras
      strstr << "Available cameras:\n";
      std::vector<CamInfo> cam_infos;
      listCameras(cam_infos);
      std::vector<CamInfo>::iterator iter = cam_infos.begin();
      for(;iter != cam_infos.end();++iter)
      {
	strstr << "Unique Id: " << iter->unique_id << "\n";
	strstr << "Display Name: " << iter->display_name << "\n";
	strstr << "Interface ID: " << iter->interface_id << "\n";
	strstr << "Interface Type: " << iter->interface_type << "\n";
	strstr << "Part Number: " << iter->part_number << "\n";
	strstr << "Part Version: " << iter->part_version << "\n";
	strstr << "Permitted Access: " << iter->permitted_access << "\n";
	strstr << "Reachable: " << iter->reachable << "\n";
	strstr << "Serial String: " << iter->serial_string << "\n\n";
      }
      
      strstr << "\n";
      if(!isOpen())
      {
	strstr << "No camera is open! Cannot do a full diagnose\n";
	return strstr.str();
      }
      
      //show CamInfo of the open camera 
      const CamInfo *pcam_info;
      try
      {
	pcam_info = getCameraInfo();
	strstr << "Opened Camera:\n"; 
	strstr << "Unique Id: " << pcam_info->unique_id << "\n";
      }
      catch(std::runtime_error e)
      {
	strstr << e.what() << "\n Cannot display CamInfo of the opened camera. \n";
      }
      
      //test sync ports
      strstr << "Testing syncin ports (time interval = 10 ms):\n"; 
      if(isAttribAvail(int_attrib::SyncInLevels))
      {
	std::stringstream strstr_in1;
	std::stringstream strstr_in2;
	std::stringstream strstr_in3;
	std::stringstream strstr_in4;
	for(int i=0;i<100;i++)
	{
	  uint32_t value = getAttrib(int_attrib::SyncInLevels);
	  strstr_in1 << (value & 1);
	  strstr_in2 << (value & 2);
	  strstr_in3 << (value & 4);
	  strstr_in4 << (value & 4);
	  usleep(10000);
	}
	strstr << "SyncIn1: " << strstr_in1.str() << "\n"; 
	strstr << "SyncIn2: " << strstr_in2.str() << "\n"; 
	strstr << "SyncIn3: " << strstr_in3.str() << "\n"; 
	strstr << "SyncIn4: " << strstr_in4.str() << "\n\n"; 
      }
      else
      {
	 strstr << "test syncin ports is not supported by the camera.\n\n"; 
      }
      
      //do some other stuff
      return strstr.str();
    }
    
    bool Helper::convertColor(const Frame &src,Frame &dst,frame_mode_t mode)
    {
      if (mode == MODE_UNDEFINED)
      {
	mode = dst.frame_mode;
	if(src.getWidth() != dst.getWidth() || src.getWidth() != dst.getWidth())
	   throw std::runtime_error("Helper::convertColor: Size does not match!");

	if(src.getDataDepth() != 8|| dst.getDataDepth() != 8)
	   throw std::runtime_error("Helper::convertColor: Color depth is not valid!" 
				    "Both frames must have a color depth of 8 bits.");
      }
      else
      {
	if(src.getWidth() != dst.getWidth() || src.getWidth() != dst.getWidth()||dst.getDataDepth() != 3||dst.frame_mode!= MODE_RGB)
	  dst.init(dst.getWidth(),dst.getHeight(),8,MODE_RGB);
      }
      
      //set frame attributes
      dst.copyImageIndependantAttributes(src);
      
      switch(mode)
      {
	case MODE_RGB:
	    return convertBayerToRGB24(src.getImageConstPtr(),dst.getImagePtr(),src.getWidth(),src.getHeight(),src.frame_mode);	
	  break;
	default: 
	    throw std::runtime_error("Helper::convertColor: Color conversion is not supported!");
      }
      return false;
    }
    
    
    
  bool Helper::convertBayerToRGB24(const uint8_t *src, uint8_t *dst, int width, int height, frame_mode_t mode)
  {
      const int srcStep = width;
      const int dstStep = 3 * width;
      int blue = mode == MODE_BAYER_RGGB
		|| mode == MODE_BAYER_GRBG ? -1 : 1;
      int start_with_green = mode == MODE_BAYER_GBRG
			    || mode == MODE_BAYER_GRBG ;
      int i, imax, iinc;

      if (!(mode==MODE_BAYER_RGGB||mode==MODE_BAYER_GBRG||mode==MODE_BAYER_GRBG||mode==MODE_BAYER_BGGR))
	  throw std::runtime_error("Helper::convertBayerToRGB24: Unknown Bayer pattern");
      
      // add a black border around the image
      imax = width * height * 3;
      // black border at bottom
      for (i = width * (height - 1) * 3; i < imax; i++) 
      	  dst[i] = 0;
      
      iinc = (width - 1) * 3;
      // black border at right side
      for (i = iinc; i < imax; i += iinc) {
	  dst[i++] = 0;
	  dst[i++] = 0;
	  dst[i++] = 0;
      }

      dst ++;
      width --;
      height --;

      for (; height--; src += srcStep, dst += dstStep) {
	  const uint8_t *srcEnd = src + width;

	  if (start_with_green) {
	      dst[-blue] = src[1];
	      dst[0] = (src[0] + src[srcStep + 1] + 1) >> 1;
	      dst[blue] = src[srcStep];
	      src++;
	      dst += 3;
	  }

	  if (blue > 0) {
	      for (; src <= srcEnd - 2; src += 2, dst += 6) {
		  dst[-1] = src[0];
		  dst[0] = (src[1] + src[srcStep] + 1) >> 1;
		  dst[1] = src[srcStep + 1];

		  dst[2] = src[2];
		  dst[3] = (src[1] + src[srcStep + 2] + 1) >> 1;
		  dst[4] = src[srcStep + 1];
	      }
	  } else {
	      for (; src <= srcEnd - 2; src += 2, dst += 6) {
		  dst[1] = src[0];
		  dst[0] = (src[1] + src[srcStep] + 1) >> 1;
		  dst[-1] = src[srcStep + 1];

		  dst[4] = src[2];
		  dst[3] = (src[1] + src[srcStep + 2] + 1) >> 1;
		  dst[2] = src[srcStep + 1];
	      }
	  }

	  if (src < srcEnd) {
	      dst[-blue] = src[0];
	      dst[0] = (src[1] + src[srcStep] + 1) >> 1;
	      dst[blue] = src[srcStep + 1];
	      src++;
	      dst += 3;
	  }

	  src -= width;
	  dst -= width * 3;

	  blue = -blue;
	  start_with_green = !start_with_green;
      }
      return true;
  }
}
    
