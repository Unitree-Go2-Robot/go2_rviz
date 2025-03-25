#ifndef GO2_RVIZ_GO2MODES_HPP_
#define GO2_RVIZ_GO2MODES_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <rclcpp/rclcpp.hpp>
#include <go2_interfaces/srv/mode.hpp>

namespace go2_rviz
{

class Go2Modes : public QWidget
{
  Q_OBJECT

public:
  explicit Go2Modes(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr);
  ~Go2Modes();

private slots:
  void onModeChanged(std::string mode);

private:
  rclcpp::Node::SharedPtr node_;

  // Service clients
  rclcpp::Client<go2_interfaces::srv::Mode>::SharedPtr mode_client_;
};

}  // namespace go2_rviz

#endif  // GO2_RVIZ_GO2MODES_HPP_
