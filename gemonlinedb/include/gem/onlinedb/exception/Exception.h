/** @file gem/onlinedb/exception/Exception.h */

#ifndef GEM_ONLINEDB_EXCEPTION_EXCEPTION_H
#define GEM_ONLINEDB_EXCEPTION_EXCEPTION_H

#include "gem/utils/exception/Exception.h"

// The gem::onlinedb exceptions.
#define GEM_ONLINEDB_DEFINE_EXCEPTION(EXCEPTION_NAME) GEM_DEFINE_EXCEPTION(EXCEPTION_NAME, onlinedb)
GEM_ONLINEDB_DEFINE_EXCEPTION(SoftwareProblem)
GEM_ONLINEDB_DEFINE_EXCEPTION(DBConnectionError)
GEM_ONLINEDB_DEFINE_EXCEPTION(ParseError)
GEM_ONLINEDB_DEFINE_EXCEPTION(ReferenceError)

// The gem::onlinedb alarms.
#define GEM_ONLINEDB_DEFINE_ALARM(ALARM_NAME) GEM_ONLINEDB_DEFINE_EXCEPTION(ALARM_NAME)
GEM_ONLINEDB_DEFINE_ALARM(MonitoringFailureAlarm)

#endif  // GEM_ONLINEDB_EXCEPTION_EXCEPTION_H
