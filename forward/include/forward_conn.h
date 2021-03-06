#ifndef FORWARD_INCLUDE_FORWARD_CONN_H_
#define FORWARD_INCLUDE_FORWARD_CONN_H_

#include <string>

#include "forward/include/work_thread.h"
#include "forward/include/forward_define.h"

namespace forward {

class WorkThread;

class ForwardConn {
 public:
  explicit ForwardConn(int fd_, const std::string &remote_ip_, int16_t remote_port_, WorkThread *thread_);
  virtual ~ForwardConn();

  virtual ReadStatus GetRequest() = 0;

  virtual WriteStatus SendReply() = 0;

  virtual int ClearUp(const std::string msg) {
    return 0;
  }

  int getFd_() const {
    return fd_;
  }
  WorkThread *getThread_() const {
    return thread_;
  }
  void setHeart_beat_(const int heart_beat) {
    heart_beat_ = heart_beat;
  }
  int32_t getHeart_beat_() const {
    return heart_beat_;
  }
  void setLast_time_wheel_scale_(const int32_t last_time_wheel_scale) {
    last_time_wheel_scale_ = last_time_wheel_scale;
  }
  int32_t getLast_time_wheel_scale_() {
    return last_time_wheel_scale_;
  }
  void setLast_active_time_(const int64_t last_active_time) {
    last_active_time_ = last_active_time;
  }
  uint64_t getLast_active_time_() {
    return last_active_time_;
  }
  bool isIs_reply_() const {
    return is_reply_;
  }
  void setIs_reply_(bool is_reply_) {
    ForwardConn::is_reply_ = is_reply_;
  }

  bool SetNoBlock();

 private:
  int fd_;
  std::string remote_ip_;
  int16_t remote_port_;
  int32_t heart_beat_;
  int32_t last_time_wheel_scale_;
  uint64_t last_active_time_;
  bool is_reply_;
  /*
   * Which thread this connection belongs to
   */
  WorkThread *thread_;

  /*
   * No allowed copy and copy assign operator
   */
  ForwardConn(const ForwardConn &);
  void operator=(const ForwardConn &);
};

class ConnFactory {
 public:
  virtual ~ConnFactory() {
  }
  virtual ForwardConn *NewConn(const int fd_, const std::string &remote_ip_, int16_t remote_port_,
                               forward::WorkThread *thread_) const = 0;
};
}

#endif  // FORWARD_INCLUDE_FORWARD_CONN_H_
