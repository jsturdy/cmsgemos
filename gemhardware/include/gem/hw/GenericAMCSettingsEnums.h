/** @file GenericAMCSettingsEnums.h */

#ifndef GEM_HW_AMCSETTINGSENUMS_H
#define GEM_HW_AMCSETTINGSENUMS_H

namespace gem {
  namespace hw {

    // TODO: FIXME: replace these constructs with enum class/struct objects (only possible with c++11 or greater)
    class AMCLinkSettings
    {
    public:
      struct LinkBitMasks {
        enum ELinkBitMasks {
          ERROR  = 0x01,
          RECI2C = 0x02,
          SNTI2C = 0x04,
          RECREG = 0x08,
          SNTREG = 0x10,
        } LinkBitMasks;
      };

      struct LinkBitShifts {
        enum ELinkBitShifts {
          ERROR  = 0,
          RECI2C = 1,
          SNTI2C = 2,
          RECREG = 3,
          SNTREG = 4,
        } LinkBitShifts;
      };
    };

    class AMCSettings {
    public:

      struct TTCEncoding { //TTCEncoding settings
        enum ETTCEncoding { //TTCEncoding settings
          AMC13  = 0x0, //Use the AMC13 style TTC encoding
          GEMCSC = 0x1, //Use the CSC/GEM style TTC encoding
        } TTCEncoding;
      };

      struct TTCCommand {  ///< TTCCommand settings
        enum ETTCCommand {  ///< TTCCommand settings
          TTC_L1A,
          TTC_BC0,
          TTC_EC0,
          TTC_RESYNC,
          TTC_OC0,
          TTC_HARD_RESET,
          TTC_CALPULSE,
          TTC_START,
          TTC_STOP,
          TTC_TEST_SYNC,
        } TTCCommand;
      };

      struct OHLinkCount {  ///< OHLinkCount settings
        enum EOHLinkCount {  ///< OHLinkCount settings
          LINK_NOT_VALID,
          LINK_MISSED_COMMA,
          LINK_OVERFLOW,
          LINK_UNDERFLOW,
          LINK_SYNC_WORD
        } OHLinkCount;
      };
    };  // class AMCSettings

    /// This class holds constants and enums related to the SCA chip
    class SCASettings {
    public:

      /**
       * \brief SCA Resets
       * Types of resets able to be sent via the SCA
       */
      struct SCAResetType {  //SCAResetType settings
        enum ESCAResetType { //SCAResetType settings
          SCAReset  = 0x0, ///< Reset the SCA
          HardReset = 0x1, ///< Use the SCA to send a TTC-style HardReset command
        } SCAResetType;
      };  // struct SCAResetTypes

      /**
       * \brief SCA Channels
       * List of channels with which the SCA can be controlled
       */
      struct SCAChannel {
        enum ESCAChannel {
          CTRL  = 0x00, ///< SCA configuration registers
          SPI   = 0x01, ///< Serial peripheral master interface
          GPIO  = 0x02, ///< General purpose parallel I/O interface
          I2C00 = 0x03, ///< I2C serial interface - master 0
          I2C01 = 0x04, ///< I2C serial interface - master 1
          I2C02 = 0x05, ///< I2C serial interface - master 2
          I2C03 = 0x06, ///< I2C serial interface - master 3
          I2C04 = 0x07, ///< I2C serial interface - master 4
          I2C05 = 0x08, ///< I2C serial interface - master 5
          I2C06 = 0x09, ///< I2C serial interface - master 6
          I2C07 = 0x0a, ///< I2C serial interface - master 7
          I2C08 = 0x0b, ///< I2C serial interface - master 8
          I2C09 = 0x0c, ///< I2C serial interface - master 9
          I2C10 = 0x0d, ///< I2C serial interface - master 10
          I2C11 = 0x0e, ///< I2C serial interface - master 11
          I2C12 = 0x0f, ///< I2C serial interface - master 12
          I2C13 = 0x10, ///< I2C serial interface - master 13
          I2C14 = 0x11, ///< I2C serial interface - master 14
          I2C15 = 0x12, ///< I2C serial interface - master 15
          JTAG  = 0x13, ///< JTAG serial master interface
          ADC   = 0x14, ///< Analog-to-digital converter
          DAC   = 0x15, ///< Digital-to-analog converter
        } SCAChannel;
      };  // struct SCAChannel

      /**
       * \brief SCA Error Flags
       * List of error flags that can be set in the reply
       */
      struct SCAErrorFlags {  //SCAErrorFlags settings
        enum ESCAErrorFlags { //SCAErrorFlags settings
          Generic     = 0x01, ///< Generic error flag
          InvChReq    = 0x02, ///< Invalid channel requested
          InvCmdReq   = 0x04, ///< Invalid command requested
          InvTranReqN = 0x08, ///< Invalid transaction request number
          InvLen      = 0x10, ///< Invalid length
          ChNotEn     = 0x20, ///< Channel not enabled
          ChBusy      = 0x40, ///< Channel busy
          CmdInTreat  = 0x80, ///< Command in treatment
        } SCAErrorFlags;
      };  // struct SCAErrorFlags

    };  // class SCASettings

    /// This class holds constants and enums related to the GBT chip
    class GBTSettings {
    public:

      struct GBTResetType { //GBTResetType settings
        enum EGBTResetType { //GBTResetType settings
          GBTReset  = 0x0, ///< Use the AMC13 style TTC encoding
          HardReset = 0x1, ///< Use the CSC/GEM style TTC encoding
        } GBTResetType;
      };
    };  // class GBTSettings
  }  // namespace gem::hw

  // <name>  is the enum scoped namespace for scope::VALUE access
  // <name>T is the enum type
  // typedef the struct for access to the members via struct::VALUE
  typedef gem::hw::AMCLinkSettings::LinkBitMasks  AMCLinkBitMasks;
  typedef gem::hw::AMCLinkSettings::LinkBitShifts AMCLinkBitShifts;

  typedef gem::hw::AMCSettings::TTCEncoding AMCTTCEncoding;
  typedef gem::hw::AMCSettings::TTCCommand  AMCTTCCommand;
  typedef gem::hw::AMCSettings::OHLinkCount AMCOHLinkCount;

  typedef gem::hw::SCASettings::SCAResetType   AMCSCAResetType;

  // typedef the enum for casting and access
  typedef gem::hw::AMCLinkSettings::LinkBitMasks::ELinkBitMasks   AMCLinkBitMasksT;
  typedef gem::hw::AMCLinkSettings::LinkBitShifts::ELinkBitShifts AMCLinkBitShiftsT;

  typedef gem::hw::AMCSettings::TTCEncoding::ETTCEncoding AMCTTCEncodingT;
  typedef gem::hw::AMCSettings::TTCCommand::ETTCCommand   AMCTTCCommandT;
  typedef gem::hw::AMCSettings::OHLinkCount::EOHLinkCount AMCOHLinkCountT;

  typedef gem::hw::SCASettings::SCAResetType::ESCAResetType   AMCSCAResetTypeT;

}  // namespace gem

#endif  // GEM_HW_AMCSETTINGSENUMS_H
