#include "tag.h"
#include "environment.h"

int lf_clock_gettime(instant_t *now) {
  lf_print("lf_clock_gettime");
  *now = 0;
  return 0;
}

int wait_until(environment_t *env, instant_t wakeup_time) {
  if (wakeup_time < FOREVER) {
    lf_print("wait_until less than forever");
    return 0;
  } else {
    lf_print("wait_until FOREVER");
    while (true) {}
  }
}