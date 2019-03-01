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
       * \brief SCA Commands
       * List of commands that can be used when controlling the SCA
       */
      struct SCACommands {  //SCACommands settings
        enum ESCACommands { //SCACommands settings
          CTRL_R_ID_V1 = 0x91, ///< Read the SCA ChipID (channel 0x14)
          CTRL_R_ID_V2 = 0xD1, ///< Read the SCA ChipID (channel 0x14)
          CTRL_W_CRB   = 0x02, ///< Write to CTRL register B
          CTRL_W_CRC   = 0x04, ///< Write to CTRL register C
          CTRL_W_CRD   = 0x06, ///< Write to CTRL register D
          CTRL_R_CRB   = 0x03, ///< Read from CTRL register B
          CTRL_R_CRC   = 0x05, ///< Read from CTRL register C
          CTRL_R_CRD   = 0x07, ///< Read from CTRL register D
          CTRL_R_SEU   = 0xF1, ///< Read from the SEU monitor (channel 0x13)
          CTRL_C_SEU   = 0xF0, ///< Reset the SEU monitor (channel 0x13)

          // I2C commands
          I2C_W_CTRL   = 0x30, ///< Write I2C control register
          I2C_R_CTRL   = 0x31, ///< Read I2C control register
          I2C_R_STR    = 0x11, ///< Read I2C status register
          I2C_W_MSK    = 0x20, ///< Write I2C mask register
          I2C_R_MSK    = 0x21, ///< Read I2C mask register
          I2C_W_DATA0  = 0x40, ///< Write I2C data register bytes [3:0]
          I2C_R_DATA0  = 0x41, ///< Read I2C data register bytes [3:0]
          I2C_W_DATA1  = 0x50, ///< Write I2C data register bytes [7:4]
          I2C_R_DATA1  = 0x51, ///< Read I2C data register bytes [7:4]
          I2C_W_DATA2  = 0x60, ///< Write I2C data register bytes [11:8]
          I2C_R_DATA2  = 0x61, ///< Read I2C data register bytes [11:8]
          I2C_W_DATA3  = 0x70, ///< Write I2C data register bytes [15:12]
          I2C_R_DATA3  = 0x71, ///< Read I2C data register bytes [15:12]
          I2C_S_7B_W   = 0x82, ///< Start I2C single-byte write with 7-bit address
          I2C_S_7B_R   = 0x86, ///< Start I2C single-byte read with 7-bit address
          I2C_S_10B_W  = 0x8A, ///< Start I2C single-byte write with 10-bit address
          I2C_S_10B_R  = 0x8E, ///< Start I2C single-byte read with 10-bit address
          I2C_M_7B_W   = 0xDA, ///< Start I2C multi-byte write with 7-bit address
          I2C_M_7B_R   = 0xDE, ///< Start I2C multi-byte read with 7-bit address
          I2C_M_10B_W  = 0xE2, ///< Start I2C multi-byte write with 10-bit address
          I2C_M_10B_R  = 0xE6, ///< Start I2C multi-byte read with 10-bit address
          I2C_RMW_AND  = 0xXX, ///< Start RMW transaction with AND
          I2C_RMW_OR   = 0xC6, ///< Start RMW transaction with OR
          I2C_RMW_XOR  = 0xCA, ///< Start RMW transaction with XOR

          // SPI commands

          // JTAG commands

          // GPIO commands

          // DAC commands
          DAC_W_A   = 0x10, ///< Write DAC value on output A
          DAC_R_A   = 0x11, ///< Read DAC value on output A
          DAC_W_B   = 0x20, ///< Write DAC value on output B
          DAC_R_B   = 0x21, ///< Read DAC value on output B
          DAC_W_C   = 0x30, ///< Write DAC value on output C
          DAC_R_C   = 0x31, ///< Read DAC value on output C
          DAC_W_D   = 0x40, ///< Write DAC value on output D
          DAC_R_D   = 0x41, ///< Read DAC value on output D

          // ADC commands V2
          ADC_GO     = 0x02, ///< Start of ADC conversion
          ADC_W_MUX  = 0x50, ///< Write ADC register INSEL
          ADC_R_MUX  = 0x51, ///< Read ADC register INSEL
          ADC_W_CURR = 0x60, ///< Write ADC register
          ADC_R_CURR = 0x61, ///< Read ADC register
          ADC_W_GAIN = 0x10, ///< Write ADC register output A
          ADC_R_GAIN = 0x11, ///< Read ADC register output A
          ADC_R_DATA = 0x21, ///< Read ADC converted value
          ADC_R_RAW  = 0x31, ///< Read ADC raw value
          ADC_R_OFS  = 0x41, ///< Read ADC offset
          // ADC commands V1??
          ADC_GO       = 0xB2, ///< Start of ADC conversion
          ADC_W_INSEL  = 0x30, ///< Write ADC register INSEL
          ADC_R_INSEL  = 0x31, ///< Read ADC register INSEL
          ADC_W_CURREN = 0x40, ///< Write ADC register
          ADC_R_CURREN = 0x41, ///< Read ADC register
        } SCACommands;
      };  // struct SCACommands

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

      /**
       * \brief SCA ADC Channels
       * List of ADC Channels on the SCA
       */
      struct SCAADCChannels {  //SCAADCChannels settings
        enum ESCAADCChannels { //SCAADCChannels settings
          AVCCN_V1P0     = 27, ///< FPGA MGT 1.0V
          AVTTN_V1P2     = 30, ///< FPGA MGT 1.2V
          INT_V1P0       = 17, ///< 1.0V FPGA core voltage
          ADC_V1P8       = 14, ///< 1.8V used by the PROM
          ADC_V1P5       = 24, ///< 1.5V used by the GBTXs and SCA
          ADC_2V5        = 15, ///< 2.5V used by FPGA I/O and VTRXs/VTTXs
          // Aliases
          FPGA_MGT_V1P0  = 27, ///< FPGA MGT 1.0V
          FPGA_MGT_V1P2  = 30, ///< FPGA MGT 1.2V
          FPGA_CORE      = 17, ///< 1.0V FPGA core voltage
          PROM_V1P8      = 14, ///< 1.8V used by the PROM
          GBTX_V1P5      = 24, ///< 1.5V used by the GBTXs and SCA
          SCA_V1P5       = 24, ///< 1.5V used by the GBTXs and SCA
          FPGA_IO_V2P5   = 15, ///< 2.5V used by FPGA I/O and VTRXs/VTTXs
          VTTX_VTRX_V2P5 = 15, ///< 2.5V used by FPGA I/O and VTRXs/VTTXs

          ADC_CH00 = 0x00, ///< ADC channel 00, Temp sensor
          ADC_CH01 = 0x01, ///< ADC channel 01, NOT CONNECTED
          ADC_CH02 = 0x02, ///< ADC channel 02, NOT CONNECTED
          ADC_CH03 = 0x03, ///< ADC channel 03, NOT CONNECTED
          ADC_CH04 = 0x04, ///< ADC channel 04, Temp sensor
          ADC_CH05 = 0x05, ///< ADC channel 05, NOT CONNECTED
          ADC_CH06 = 0x06, ///< ADC channel 06
          ADC_CH07 = 0x07, ///< ADC channel 07, Temp sensor
          ADC_CH08 = 0x08, ///< ADC channel 08, Temp sensor
          ADC_CH09 = 0x09, ///< ADC channel 09
          ADC_CH10 = 0x0A, ///< ADC channel 10
          ADC_CH11 = 0x0B, ///< ADC channel 11
          ADC_CH12 = 0x0C, ///< ADC channel 12, NOT CONNECTED
          ADC_CH13 = 0x0D, ///< ADC channel 13
          ADC_CH14 = 0x0E, ///< ADC channel 14, 1.8V
          ADC_CH15 = 0x0F, ///< ADC channel 15, 2.5V I/O
          ADC_CH16 = 0x10, ///< ADC channel 16
          ADC_CH17 = 0x11, ///< ADC channel 17, internal 1.0V
          ADC_CH18 = 0x12, ///< ADC channel 18, VTRx rssi3
          ADC_CH19 = 0x13, ///< ADC channel 19, VTRx rssi2
          ADC_CH20 = 0x14, ///< ADC channel 20
          ADC_CH21 = 0x15, ///< ADC channel 21, VTRx rssi1
          ADC_CH22 = 0x16, ///< ADC channel 22
          ADC_CH23 = 0x17, ///< ADC channel 23
          ADC_CH24 = 0x18, ///< ADC channel 24, 1.5V
          ADC_CH25 = 0x19, ///< ADC channel 25
          ADC_CH26 = 0x1A, ///< ADC channel 26
          ADC_CH27 = 0x1B, ///< ADC channel 27, AVCCN
          ADC_CH28 = 0x1C, ///< ADC channel 28
          ADC_CH29 = 0x1D, ///< ADC channel 29
          ADC_CH30 = 0x1E, ///< ADC channel 30, AVTTN
          ADC_CH31 = 0x1F, ///< ADC channel 31
        } SCAADCChannels;
      };  // struct SCAADCChannels

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
