// Copyright 2025 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "go2_rviz/Go2Panel.hpp"
#include "go2_rviz/Go2Services.hpp"
#include "go2_rviz/Go2Modes.hpp"
#include "go2_rviz/Go2ObstaclesAvoidance.hpp"
#include "go2_rviz/Go2VUI.hpp"
#include "go2_rviz/Go2TTS.hpp"

#include <QtConcurrent/QtConcurrent>
#include <QVBoxLayout>
#include <memory>
#include <vector>
#include <utility>
#include <chrono>
#include <string>

#include "rviz_common/display_context.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"

using namespace std::chrono_literals;

namespace go2_rviz
{

Go2Panel::Go2Panel(QWidget * parent)
: Panel(parent)
{
  node_ = rclcpp::Node::make_shared("go2_panel");

  tab_widget_ = new QTabWidget();
  layout_ = new QVBoxLayout();

  // Crear las pestañas
  Go2Services * services_tab = new Go2Services(node_);
  Go2Modes * modes_tab = new Go2Modes(node_);
  Go2ObstaclesAvoidance * obstacles_tab = new Go2ObstaclesAvoidance(node_);
  Go2VUI * vui_tab = new Go2VUI(node_);
  Go2TTS * tts_tab = new Go2TTS(node_);

  // Agregar pestañas al QTabWidget
  tab_widget_->addTab(services_tab, "Services");
  tab_widget_->addTab(modes_tab, "Modes");  
  tab_widget_->addTab(obstacles_tab, "Obstacles Avoidance");
  tab_widget_->addTab(tts_tab, "TTS");
  tab_widget_->addTab(vui_tab, "VUI");

  layout_->addWidget(tab_widget_);
  setLayout(layout_);

  spin_thread_ = std::thread(
    [this]() {
      rclcpp::spin(node_);
    });
}

Go2Panel::~Go2Panel()
{
  spin_thread_.join();
}

void
Go2Panel::onInitialize()
{
}

}  // namespace go2_rviz

#include <pluginlib/class_list_macros.hpp>  // NOLINT
PLUGINLIB_EXPORT_CLASS(go2_rviz::Go2Panel, rviz_common::Panel)
