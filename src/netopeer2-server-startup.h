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
#include <sysrepo.h>

 /**
 * @brief netopeer2-server startup options
 */
typedef struct {
    /* whether to daemonize */
    int daemonize;
    /* whether to print verbose logging messages */
    int verbose;
    /* the path to the pidfile of the process */
    const char *pidfile;
} np2srv_opts_t;

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
int np2srv_parse_options(int argc, char *argv[], np2srv_opts_t *opts);

/**
 * @brief netopeer2-server work on this thread
 * This function will set the thread as a worker thread and run the worker_starter function.
 * @param [in] index The index of the worker thread, used to identify the thread
 * @param [in] worker_starter The function to start the worker thread, it would be worker_thread() if not set.
 * @note This function is used to occupy this thread as a worker thread
 */
void np2srv_work_on_this_thread(int index, np2srv_worker_starter_func worker_starter);

/**
 * @brief netopeer2-server startup
 * @param [in] opts Parsed options
 * @param [in] set_signal_handler whether to set signal handler
 * @param [in] worker_starter_func function to start worker threads, set it NULL to use the default one
 * @param [in] send_sd_ready whether to send sd_notify READY=1
 * @param [in] occupy_this_thread whether to occupy this thread as a worker thread
 * @param [in] sr_conn Pointer to a sysrepo connection context that will used by the server,
 *  can be NULL and netopeer2-server will create a new one.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int np2srv_startup(np2srv_opts_t *opts, bool set_signal_handler,
                   np2srv_worker_starter_func worker_starter,
                   bool send_sd_ready, bool occupy_this_thread,
                   sr_conn_ctx_t *sr_conn);

/**
 * @brief netopeer2-server teardown
 * @param [in] pidfile Path to the pidfile of the process
 * @param [in] send_sd_stopping whether to send sd_notify STOPPING=1
 * @param [in] cleanup whether to cleanup the server resources
 */
void np2srv_teardown(const char *pidfile, bool send_sd_stopping, bool cleanup);

#endif /* __NETOPEER2_SERVER_STARTUP_H__ */
