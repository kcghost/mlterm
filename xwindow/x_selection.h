/*
 *	$Id$
 */

#ifndef  __X_SELECTION_H__
#define  __X_SELECTION_H__


#include  <kiklib/kik_types.h>		/* u_int */
#include  <ml_str.h>


typedef struct  x_sel_event_listener
{
	void *  self ;
	int  (*select_in_window)( void * , ml_char_t ** , u_int *, int , int , int , int) ;
	void  (*reverse_color)( void * , int , int , int , int) ;
	void  (*restore_color)( void * , int , int , int , int) ;

} x_sel_event_listener_t ;

typedef struct  x_selection
{
	x_sel_event_listener_t *  sel_listener ;

	ml_char_t *  sel_str ;
	u_int  sel_len ;

	/*
	 * Be careful that value of col must be munis in rtl line.
	 * +-----------------------------+
	 * |          a  a  a  a  a  a  a|<= RTL line
	 *           -7 -6 -5 -4 -3 -2 -1 <= index
	 */

	int  base_col_l ;
	int  base_row_l ;
	int  base_col_r ;
	int  base_row_r ;
	int  beg_col ;
	int  beg_row ;
	int  end_col ;
	int  end_row ;

	int  prev_col ;
	int  prev_row ;
	
	int8_t  is_selecting ;
	int8_t  is_reversed ;

}  x_selection_t ;


int  x_sel_init( x_selection_t *  sel , x_sel_event_listener_t *  listener) ;

int  x_sel_final( x_selection_t *  sel) ;

int  x_start_selection( x_selection_t *  sel , int  col_l , int  row_l , int  col_r , int  row_r) ;

int  x_selecting( x_selection_t *  sel , int  col , int  row) ;

int  x_stop_selecting( x_selection_t *  sel) ;

int  x_restore_selected_region_color_except_logs( x_selection_t *  sel) ;

int  x_reverse_selected_region_color_except_logs( x_selection_t *  sel) ;

int  x_restore_selected_region_color( x_selection_t *  sel) ;

int  x_reverse_selected_region_color( x_selection_t *  sel) ;

int  x_sel_clear( x_selection_t *  sel) ;

int  x_selected_region_is_changed( x_selection_t *  sel , int  col , int  row , u_int  base) ;

int  x_sel_line_scrolled_out( x_selection_t *  sel , int  min_row) ;

int  x_is_after_sel_right_base_pos( x_selection_t *  sel , int  col , int  row) ;

int  x_is_before_sel_left_base_pos( x_selection_t *  sel , int  col , int  row) ;


#endif
