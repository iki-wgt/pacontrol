/*
 * Copyright (C) 2015 Benjamin Reiner <reiner@hs-weingarten.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PACONTROL_H_
#define PACONTROL_H_

#include "ros/ros.h"
#include "dynamic_reconfigure/server.h"

#include "pacontrol/pulseaudio.hh"
#include "pacontrol/device.hh"
#include "pacontrol/GetMute.h"
#include "pacontrol/SetMute.h"
#include "pacontrol/pacontrolConfig.h"

class PaControl
{
public:
  PaControl();
  virtual ~PaControl();

  void printSources();

private:
  bool getMuteCb(pacontrol::GetMute::Request& req, pacontrol::GetMute::Response& res);
  bool setMuteCb(pacontrol::SetMute::Request& req, pacontrol::SetMute::Response& res);
  void dynReconfCallback(pacontrol::pacontrolConfig &config, uint32_t level);

  ros::NodeHandle node_handle_;
  Pulseaudio pulse_;
  ros::ServiceServer get_mute_service_;
  ros::ServiceServer set_mute_service_;
  dynamic_reconfigure::Server<pacontrol::pacontrolConfig> dyn_reconf_server_;
  dynamic_reconfigure::Server<pacontrol::pacontrolConfig>::CallbackType dyn_reconf_callback_;
  std::string device_;
  bool muted_at_start_;
};

#endif /* PACONTROL_H_ */
