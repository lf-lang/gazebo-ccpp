#include "tag.h"
#include "environment.h"
#include "util.h"

static lf_cond_t *lf_cond;
static instant_t lf_wakeup_time;
static bool lf_waiting = false;
static instant_t lf_time = 0;

void lf_gazebo_set_time(instant_t now) {
  // lf_print("Setting time to %ld", now);
  LF_MUTEX_LOCK(lf_cond->mutex);
  lf_time = now;

  if (lf_waiting && lf_time >= lf_wakeup_time) {
    lf_cond_signal(lf_cond);
  }
  LF_MUTEX_UNLOCK(lf_cond->mutex);
}

int lf_clock_gettime(instant_t *now) {
  *now = lf_time;
  return 0;
}

bool wait_until(instant_t wakeup_time, lf_cond_t *condition) {
  lf_cond = condition;
  if (wakeup_time <= lf_time) {
    return true;
  } else {
    lf_wakeup_time = wakeup_time;
    lf_waiting = true;
    LF_COND_WAIT(condition);
    lf_waiting = false;
    if (wakeup_time <= lf_time) {
      return true;
    } else {
      return false;
    }
  }
}