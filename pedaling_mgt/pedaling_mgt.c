/**
 * Copyright (c) 2019 eBikeLabs. All Rights Reserved.
 */

#include <string.h>
#include <stdbool.h>

#include "pedaling_mgt.h"
#include "time_mgt.h"

/**
 * @def PEDALING_MGT_AVG_COUNT
 * @brief Define the maximum number of magnet used to compute average
 * @def PEDALING_MGT_MAGNET_NUM
 * @brief Define the PEDALING_MGT_MICRO_TO_SEC of magnet
 * @def PEDALING_MGT_AVG_COUNT
 * @brief Define the number of micro-seconds in one second
 * @def PEDALING_MGT_MIN_TO_SEC
 * @brief Define the number of second in one minute
 * @def MAX
 * @brief Define maximum function
 * @def MIN
 * @brief Define the minimum function
 */
#define PEDALING_MGT_AVG_COUNT		10
#define PEDALING_MGT_MAGNET_NUM		12
#define PEDALING_MGT_MICRO_TO_SEC	1000000
#define PEDALING_MGT_MIN_TO_SEC		60
#define MAX(x, y) 			        ((x) > (y) ? (x) : (y))
#define MIN(x, y)	 		        ((x) < (y) ? (x) : (y))

/**
 * @brief Describe the structure pedaling_mgt_sm_t
 * @brief Contain the necessary measure to compute pedaling speed and average speed
 */
typedef struct
{
    uint32_t magnetTime[PEDALING_MGT_AVG_COUNT];		/**< The last magnet time */
    uint8_t  index;						                /**< A counter for the first received values */
} pedaling_mgt_sm_t;

static pedaling_mgt_sm_t pedaling_mgt_sm;

/**
 * @brief Return speed in RPM
 * @param magnetNum		r   : Space in magnet used to compute the speed must be superior or egal to 2 and should not be greater than @see PEDALING_MGT_AVG_COUNT
 * @param fast			r   : Indicate if compute has to be done even when not enough sample are recorded
 */
static float _pedaling_mgt_compute_speed(uint8_t magnetNum, bool fast);

/**** Public API ****/

void pedaling_mgt_init(void)
{
    memset((void *)&pedaling_mgt_sm, 0x00, sizeof(pedaling_mgt_sm_t));
}

float get_pedaling_speed(void)
{
    // WRITE YOUR CODE HERE
    return _pedaling_mgt_compute_speed(2, true);
}

float get_average_pedaling_speed(void)
{
    // WRITE YOUR CODE HERE
    return _pedaling_mgt_compute_speed(PEDALING_MGT_AVG_COUNT, true);
}

void new_magnet_cb(void)
{
    // WRITE YOUR CODE HERE
    uint8_t counter;
    
    if (pedaling_mgt_sm.index < PEDALING_MGT_AVG_COUNT)
    {
        pedaling_mgt_sm.magnetTime[pedaling_mgt_sm.index] = get_timestamp();
        pedaling_mgt_sm.index++;
    }
    else
    {
        for (counter = 0x00; counter < PEDALING_MGT_AVG_COUNT - 1; counter++)
        {
            pedaling_mgt_sm.magnetTime[counter] = pedaling_mgt_sm.magnetTime[counter + 1];
        }
        pedaling_mgt_sm.magnetTime[PEDALING_MGT_AVG_COUNT - 1] = get_timestamp();
    }
    
}

/**** Private API ****/
static float _pedaling_mgt_compute_speed(uint8_t magnetNum, bool fast)
{
    float ret = 0.f;
    
    if (((pedaling_mgt_sm.index >= 2) && (magnetNum > 1)) && ((fast == true) || (magnetNum <= pedaling_mgt_sm.index)))
    {
        // First average is computed at once by may not include the requested "magnet number"
        magnetNum = MIN(magnetNum, pedaling_mgt_sm.index);
        ret       = (float)(pedaling_mgt_sm.magnetTime[pedaling_mgt_sm.index - 1] - pedaling_mgt_sm.magnetTime[pedaling_mgt_sm.index - magnetNum]);
        ret       = ret * PEDALING_MGT_MAGNET_NUM / PEDALING_MGT_MICRO_TO_SEC / (magnetNum - 1);
        ret       = PEDALING_MGT_MIN_TO_SEC / ret;
    }
    
    return ret;
}
