/**
 * @file netopeer2-server-startup.h
 * @author focksor <focksor@outlook.com>
 * @brief netopeer2-server startup header, separated from main.c to make it easier to integrate with other projects.
 *
 * @copyright
 * This source code is not a file of the netopeer2 project.
 */
#ifndef __NETOPEER2_SERVER_STARTUP_H__
#define __NETOPEER2_SERVER_STARTUP_H__ 

#include <stdbool.h>

 /**
 * @brief netopeer2-server startup options
 */
typedef struct {
    /* whether to daemonize */
    int daemonize;
    /* whether to print verbose logging messages */
    int verbose;
    /* the path to the pidfile of the process */
    char *pidfile;
} np2srv_opts;

/**
 * @brief netopeer2-server worker starter function prototype
 */
typedef void *(*np2srv_worker_starter_func) (void *);

/**
 * @brief netopeer2-server signal handler to control the process
 */
void np2srv_signal_handler(int sig);

/**
 * @brief netopeer2-server named worker thread
 * the thread will set name to <"np2-worker-%d", idx>
 *  and then run worker_thread(arg)
 */
void *np2srv_named_worker_thread(void *arg);

/**
 * @brief Set signal handler for netopeer2-server
 * it will handle multiple signals and mainly set loop_continue to false
 *  so that the worker threads will stop.
 */
void np2srv_set_signal_handler(void);

/**
 * @brief Parse the startup options
 * @param [in] argc Number of arguments
 * @param [in] argv Array of arguments
 * @param [out] opts Parsed options
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int np2srv_parse_options(int argc, char *argv[], np2srv_opts *opts);

/**
 * @brief netopeer2-server startup
 * @param [in] opts Parsed options
 * @param [in] set_signal_handler whether to set signal handler
 * @param [in] worker_starter_func function to start worker threads, set it NULL to use the default one
 * @param [in] send_sd_ready whether to send sd_notify READY=1
 * @param [in] occupy_this_thread whether to occupy this thread as a worker thread
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int np2srv_startup(np2srv_opts *opts, bool set_signal_handler,
                   np2srv_worker_starter_func worker_starter,
                   bool send_sd_ready, bool occupy_this_thread);


#endif /* __NETOPEER2_SERVER_STARTUP_H__ */
