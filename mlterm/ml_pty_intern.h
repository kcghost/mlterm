/*
 *	$Id$
 */

#ifndef  __ML_PTY_INTERN_H__
#define  __ML_PTY_INTERN_H__

#include  "ml_pty.h"
#include  "ml_config_menu.h"


typedef struct  ml_pty
{
	int  master ;		/* master pty fd */
	int  slave ;		/* slave pty fd */
	pid_t  child_pid ;

	/* Used in ml_write_to_pty */
	u_char *  buf ;
	size_t  left ;
	size_t  size ;

	int (*final)( ml_pty_ptr_t) ;
	int (*set_winsize)( ml_pty_ptr_t , u_int , u_int , u_int , u_int) ;
	ssize_t (*write)( ml_pty_ptr_t , u_char * , size_t) ;
	ssize_t (*read)( ml_pty_ptr_t , u_char * , size_t) ;

	ml_pty_event_listener_t *  pty_listener ;

	ml_config_menu_t  config_menu ;

	struct
	{
		int  master ;
		int  slave ;
		ssize_t (*write)( ml_pty_ptr_t , u_char * , size_t) ;
		ssize_t (*read)( ml_pty_ptr_t , u_char * , size_t) ;

		u_int  ref_count ;

	} *  stored ;

	char *  cmd_line ;

} ml_pty_t ;


ml_pty_t *  ml_pty_unix_new( const char *  cmd_path , char **  cmd_argv , char **  env ,
	const char *  host , const char *  work_dir , u_int  cols , u_int  rows ,
	u_int  width_pix , u_int  height_pix) ;

ml_pty_t *  ml_pty_unix_new_with( int  master , int  slave , pid_t  child_pid ,
	const char *  host , u_int  cols , u_int  rows ,
	u_int  width_pix , u_int  height_pix) ;

ml_pty_t *  ml_pty_ssh_new( const char *  cmd_path , char **  cmd_argv , char **  env ,
	const char *  host , const char *  pass ,
	const char *  pubkey , const char *  privkey , u_int  cols , u_int  rows ,
	u_int  width_pix , u_int  height_pix) ;

ml_pty_t *  ml_pty_pipe_new( const char *  cmd_path , char **  cmd_argv , char **  env ,
	const char *  host , const char *  pass , u_int  cols , u_int  rows) ;


#endif
