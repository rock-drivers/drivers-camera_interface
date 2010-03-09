/* 
 * File:   CamTypes.h
 * Author: developer
 *
 * Created on February 11, 2010, 12:37 AM
 */

#ifndef _CAMTYPES_H
#define _CAMTYPES_H

#include <string>
#include <stdexcept>

namespace camera
{
    // grab modes
    //

    //integer camera attributes
    namespace int_attrib
    {
        enum CamAttrib
        {
            BinningX,
            BinningY,
            RegionX,
            RegionY,
            TotalBytesPerFrame,            //read only
            AcquisitionFrameCount,
            RecorderPreEventCount,      
            FrameStartTriggerDelay,
            ExposureValue,
            ExposureAutoMax,
            ExposureAutoMin,
            ExposureAutoOutliers,
            ExposureAutoRate,
            ExposureAutoTarget,
            ExposureAutoAdjustTol,
            GainValue,
            GainAutoAdjustDelay,
            GainAutoAdjustTol,
            GainAutoMax,
            GainAutoMin,
            GainAutoOutliers,
            GainAutoRate,
            GainAutoTarget,
            WhitebalValueRed,
            WhitebalValueBlue,
            WhitebalAutoAdjustDelay,
            WhitebalAutoAdjustTol,
            WhitebalAutoAlg,
            WhitebalAutoRate,
            OffsetValue,
            DSPSubregionLeft,
            DSPSubregionTop,
            DSPSubregionRight,
            DSPSubregionBottom,
            IrisAutoTarget,
            IrisVideoLevelMin,
            IrisVideoLevelMax,
            IrisVideoLevel,
            SyncInLevels,
            SyncOutGpoLevels,
            Strobe1Delay,
            Strobe1Duration,
            PacketSize,
            StreamBytesPerSecond,
            GvcpRetries,
            HeartbeatTimeout,
            HeartbeatInterval,
            StreamHoldCapacity,
            UniqueId,
            PartNumber,
            PartVersion,
            FirmwareVerMajor,
            FirmwareVerMinor,
            FirmwareVerBuild,
            SensorBits,
            SensorWidth,
            SensorHeight,
            TimeStampFrequency,
            StatFramesCompleted,
            StatFramesDropped,
            StatPacketsErroneous,
            StatPacketsMissed,
            StatPacketsReceived,
            StatPacketsRequested,
            StatPacketsResent
        };
    }

    //double camera attributes
    namespace double_attrib
    {
        enum CamAttrib
        {
            FrameRate,
            StatFrameRate
        };
    }

    //string camera attributes
    namespace str_attrib
    {
        enum CamAttrib
        {
            DeviceEthAddress,
            DeviceIPAddress,
            HostEthAddress,
            HostIPAddress,
            MulticastIPAddress,
            CameraName,
            ModelName,
            SerialNumber,
            PartRevision,
            StatFilterVersion,
        };
    }

     //enum camera attributes
    namespace enum_attrib
    {
        enum CamAttrib
        {
            FrameStartTriggerModeToFreerun,
            FrameStartTriggerModeToSyncIn1,
            FrameStartTriggerModeToSyncIn2,
            FrameStartTriggerModeToSyncIn3,
            FrameStartTriggerModeToSyncIn4,
            FrameStartTriggerModeToFixedRate,
            FrameStartTriggerModeToSoftware,
            ExposureModeToManual,
            ExposureModeToAuto,
            ExposureModeToAutoOnce,
            MirrorXToOn,
            MirrorXToOff,
            FrameStartTriggerEventToEdgeRising,
            FrameStartTriggerEventToEdgeFalling,
            FrameStartTriggerEventToEdgeAny,
            FrameStartTriggerEventToLevelHigh,
            FrameStartTriggerEventToLevelLow,
            AcqEndTriggerEventToEdgeRising,
            AcqEndTriggerEventToEdgeFalling,
            AcqEndTriggerEventToEdgeAny,
            AcqEndTriggerEventToLevelHigh,
            AcqEndTriggerEventToLevelLow,
            AcqEndTriggerModeToSyncIn1,
            AcqEndTriggerModeToSyncIn2,
            AcqEndTriggerModeToSyncIn3,
            AcqEndTriggerModeToSyncIn4,
            AcqEndTriggerModeToDisabled,
            AcqRecTriggerEventToEdgeRising,
            AcqRecTriggerEventToEdgeFalling,
            AcqRecTriggerEventToEdgeAny,
            AcqRecTriggerEventToLevelHigh,
            AcqRecTriggerEventToLevelLow,
            AcqRecTriggerModeToSyncIn1,
            AcqRecTriggerModeToSyncIn2,
            AcqRecTriggerModeToSyncIn3,
            AcqRecTriggerModeToSyncIn4,
            AcqRecTriggerModeToDisabled,
            AcqStartTriggerEventToEdgeRising,
            AcqStartTriggerEventToEdgeFalling,
            AcqStartTriggerEventToEdgeAny,
            AcqStartTriggerEventToLevelHigh,
            AcqStartTriggerEventToLevelLow,
            AcqStartTriggerModeToSyncIn1,
            AcqStartTriggerModeToSyncIn2,
            AcqStartTriggerModeToSyncIn3,
            AcqStartTriggerModeToSyncIn4,
            AcqStartTriggerModeToDisabled,
	    GammaToOn,
	    GammaToOff,
	    GainModeToAuto,
	    GainModeToManual
        };
    }

    //
    // IP configuration mode for ethernet cameras.
    //
    enum IpConfig
    {
        IpConfigUnknown      = 0,
        IpConfigPersistent   = 1,            // Use persistent IP settings
        IpConfigDhcp         = 2,            // Use DHCP, fallback to AutoIP
        IpConfigAutoIp       = 4,            // Use AutoIP only
    };

    struct IPSettings
    {
        // IP configuration mode: persistent, DHCP & AutoIp, or AutoIp only.
        IpConfig           config_mode;
        // IP configuration mode supported by the camera
        unsigned long       config_mode_support;

        // Current IP configuration.  Ignored for PvCameraIpSettingsChange().
        // All values are in network byte order (i.e. big endian).
        unsigned long       current_ip_address;
        unsigned long       current_ip_subnet;
        unsigned long       current_ip_gateway;

        // Persistent IP configuration.  See "ConfigMode" to enable persistent
        // IP settings.  All values are in network byte order.
        unsigned long       persisten_ip_addr;
        unsigned long       persistent_ip_subnet;
        unsigned long       persistent_ip_gateway;

        IPSettings()
        {
            config_mode = IpConfigUnknown;
            config_mode_support = 0;
            current_ip_address = 0;
            current_ip_subnet = 0;
            current_ip_gateway = 0;
            persisten_ip_addr = 0;
            persistent_ip_subnet = 0;
            persistent_ip_gateway = 0;
        };

        bool matches(const IPSettings &other)const
        {
            if (config_mode != 0 && other.config_mode != 0 &&
                    config_mode != other.config_mode)
                    return false;
            if (config_mode_support != 0 && other.config_mode_support != 0 &&
                    config_mode_support != other.config_mode_support)
                    return false;
            if (current_ip_address != 0 && other.current_ip_address != 0 &&
                    current_ip_address != other.current_ip_address)
                    return false;
            if (current_ip_subnet != 0 && other.current_ip_subnet != 0 &&
                    current_ip_subnet != other.current_ip_subnet)
                    return false;
            if (current_ip_gateway != 0 && other.current_ip_gateway != 0 &&
                    current_ip_gateway != other.current_ip_gateway)
                    return false;
            if (persisten_ip_addr != 0 && other.persisten_ip_addr != 0 &&
                    persisten_ip_addr != other.persisten_ip_addr)
                    return false;
            if (persistent_ip_subnet  != 0 && other.persistent_ip_subnet!= 0 &&
                    persistent_ip_subnet != other.persistent_ip_subnet)
                    return false;
            if (persistent_ip_gateway != 0 && other.persistent_ip_gateway != 0 &&
                    persistent_ip_gateway != other.persistent_ip_gateway)
                    return false;
            return true;
        };
    };

    //
    // Camera interface type (i.e. firewire, ethernet):
    //
    enum Interface
    {
        InterfaceUnknown,
        InterfaceFirewire,
        InterfaceEthernet,
        InterfaceUSB       
    };

    static inline std::string enumInterfaceToStr(Interface i)
    {
        switch(i)
        {
            case InterfaceUnknown:
                return "InterfaceUnknown";
            case InterfaceFirewire:
                return "InterfaceFirewire";
            case InterfaceEthernet:
                return "InterfaceEthernet";
             case InterfaceUSB:
                return "InterfaceUSB";
            default:
                throw std::runtime_error("no Interface enum value found");

        }
        return "";
    }

    //
    // Camera information type.
    //
    struct CamInfo
    {
        unsigned long       unique_id ;       // Unique value for each camera
        std::string         serial_string;    // Camera's serial number
        unsigned long       part_number;      // Camera part number
        unsigned long       part_version;     // Camera part version
        unsigned long       permitted_access; // A combination of tPvAccessFlags
        unsigned long       interface_id;     // Unique value for each interface
                                              // or bus
        Interface           interface_type;   // Interface type; see
                                              // tPvInterface
        std::string         display_name;     // People-friendly camera name
        bool                reachable;        // indicates if the camera is
                                              // reachable (same sub net)
        IPSettings         ip_settings;      // ip settings for ethernet
                                              // cameras

        CamInfo()
        {
            unique_id = 0;
            part_number = 0;
            part_version = 0;
            permitted_access = 0;
            interface_id = 0;
            interface_type = InterfaceUnknown;
            reachable = false;
        };

        bool matches(const CamInfo &other)const
        {
            if (unique_id != 0 && other.unique_id != 0 &&
                    unique_id != other.unique_id)
                    return false;
            if (part_number != 0 && other.part_number != 0 &&
                    part_number != other.part_number)
                    return false;
            if (part_version != 0 && other.part_version != 0 &&
                    part_version != other.part_version)
                    return false;
            if (permitted_access != 0 && other.permitted_access != 0 &&
                    permitted_access != other.permitted_access)
                    return false;
            if (interface_id != 0 && other.interface_id != 0 &&
                    interface_id != other.interface_id)
                    return false;
            if (interface_type != 0 && other.interface_type != 0 &&
                    interface_type != other.interface_type)
                    return false;
            if (serial_string.size() != 0 && other.serial_string.size() != 0 &&
                    serial_string != other.serial_string)
                    return false;
            if (display_name.size() != 0 && other.display_name.size() != 0 &&
                    display_name != other.display_name)
                    return false;
          //  if (reachable && !other.reachable)
          //          return false;
            if(!ip_settings.matches(other.ip_settings))
                return false;
            return true;
        };
    };

    //
    // grab modes
    //
    enum GrabMode
    {
        Stop,
        SingleFrame,
        MultiFrame,
        Continuously
    } ;

    //
    // Camera access modes.
    //
    enum AccessMode
    {
       Monitor,         //listen only
       Master,          //full control
       MasterMulticast  //full control + enables multicast for ethernet cameras
    } ;

}

#endif	/* _CAMTYPES_H */

