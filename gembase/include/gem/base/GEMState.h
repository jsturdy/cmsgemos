#ifndef gem_base_GEMStates_h
#define gem_base_GEMStates_h

//Basic implementation copied from HCAL code

namespace gem {
  namespace base {
    //namespace states {
      static const toolbox::fsm::State STATE_UNINIT      = 'U'; ///< Uninitialized state (power on, reset, and recovery state)
      static const toolbox::fsm::State STATE_COLD        = 'B'; ///< Cold initialization state (firmware reload)
      static const toolbox::fsm::State STATE_INITIAL     = 'I'; ///< Initial state
      static const toolbox::fsm::State STATE_HALTED      = 'H'; ///< Halted state
      static const toolbox::fsm::State STATE_CONFIGURED  = 'C'; ///< Configured state
      static const toolbox::fsm::State STATE_RUNNING     = 'E'; ///< Running (enabled, active) state
      static const toolbox::fsm::State STATE_PAUSED      = 'P'; ///< Paused state
      static const toolbox::fsm::State STATE_FAILED      = 'F'; ///< Failed state
      
      //transitional states, TCDS way seems more elegant than HCAL, but both use a similar idea
      static const toolbox::fsm::State STATE_INITIALIZING = 'i'; ///< Initializing transitional state
      static const toolbox::fsm::State STATE_CONFIGURING  = 'c'; ///< Configuring transitional state
      static const toolbox::fsm::State STATE_HALTING      = 'h'; ///< Halting transitional state
      static const toolbox::fsm::State STATE_PAUSING      = 'p'; ///< Pausing transitional state
      static const toolbox::fsm::State STATE_STOPPING     = 's'; ///< Stopping transitional state
      static const toolbox::fsm::State STATE_STARTING     = 'e'; ///< Starting transitional state
      static const toolbox::fsm::State STATE_RESUMING     = 'r'; ///< Resuming transitional state
      static const toolbox::fsm::State STATE_RESETTING    = 't'; ///< Resetting transitional state
      static const toolbox::fsm::State STATE_FIXING       = 'X'; ///< Fixing transitional state
      
      //HCAL states, are they useful for GEM?
      /*
        static const toolbox::fsm::State STATE_INIT    ='I'; ///< Initialization state
        static const toolbox::fsm::State STATE_PREINIT ='N'; ///< Pre-initialized state used by cards which may require two stages of configuration, where the first is fast
        static const toolbox::fsm::State STATE_WARM    ='W'; ///< WARM Initialization state
      */
      //} // namespace gem::base::states
  } // namespace gem::base
} // namespace gem

#endif
