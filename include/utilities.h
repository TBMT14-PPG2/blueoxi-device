/**
 * @file	utilities.h
 * @author  Eriks Zaharans
 * @date    16 Nov 2015
 *
 * @section DESCRIPTION
 *
 * Utilities library header file.
 */

#ifndef __UTILITIES_H
#define __UTILITIES_H

/* -- Includes -- */

/* -- Defines -- */
// Declare a circular buffer structure to use for Rx and Tx queues
#define s_UTILITIES__BUFFER_SIZE		512

/* -- Constants -- */

/* -- Constants -- */

/* -- Enumerations -- */

/* -- Types -- */

/**
 * @brief Circular buffer structure
 */
typedef struct s_CIRCULAR_BUFFER_STRUCT
{
    uint8_t 	data[s_UTILITIES__BUFFER_SIZE];  /* data buffer */
    uint32_t	rdI;               /* read index */
    uint32_t	wrI;               /* write index */
    uint32_t	pendingBytes;      /* count of how many bytes are not yet handled */
    uint8_t		overflow;          /* buffer overflow indicator */
    uint8_t		lock;
} CircularBuffer_t;

/* -- Extern -- */

/* -- Function Prototypes -- */




#endif /* __UTILITIES_H */
