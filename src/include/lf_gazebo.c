#include "tag.h"
#include "environment.h"
#include "util.h"

/** Condition variable used to have the runtime wait on time passage from the simulator. */
static lf_cond_t *lf_cond;
/** Whether the runtime is currently waiting for Gazebo to advance time to a certain time point. */
static bool lf_waiting = false;
/** The current wakeup time, if the runtime is waiting */
static instant_t lf_wakeup_time;
/** The current physical time seen by the runtime. */
static instant_t lf_time = 0;

/**
 * @brief Update the physical time seen by the runtime. 
 * 
 * This function is intended to be called by the Gazebo plugin,
 * when it receives a new clock message from the Gazebo simulator.
 * 
 * @param now 
 */
void lf_gazebo_set_time(instant_t now) {
  LF_MUTEX_LOCK(lf_cond->mutex);
  lf_time = now;

  if (lf_waiting && lf_time >= lf_wakeup_time) {
    lf_cond_signal(lf_cond);
  }
  LF_MUTEX_UNLOCK(lf_cond->mutex);
}

/**
 * @brief Gazebo plugin implementation of reading the current physical time. 
 * 
 * This function simply returns the global variable used for tracking the simulate time of the Gazebo simulator.
 * 
 * @param now 
 * @return int 
 */
int lf_clock_gettime(instant_t *now) {
  LF_MUTEX_LOCK(lf_cond->mutex);
  *now = lf_time;
  LF_MUTEX_UNLOCK(lf_cond->mutex);
  return 0;
}

/**
 * @brief Gazebo plugin implementation of waiting until a certain time point.
 * 
 * This function checks whether the simulator has already advanced to the desired time point.
 * If not, it sets the wakeup time and waits on the condition variable. The thread
 * will be woken up by the Gazebo plugin when the simulator advances to the desired time point.
 * 
 */
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