/*
 *	$Id$
 */

#include  "kik_file.h"

#include  "kik_config.h"
#include  "kik_mem.h"		/* malloc */


#define  BUF_UNIT_SIZE  512


/* --- global functions --- */

kik_file_t *
kik_file_new(
	FILE *  fp
	)
{
	kik_file_t *  file  ;

	if( ( file = malloc( sizeof( kik_file_t))) == NULL)
	{
		return  NULL ;
	}
	
	file->file = fp ;
	file->buffer = NULL ;
	file->buf_size = 0 ;

	return  file ;
}

int
kik_file_delete(
	kik_file_t *  file
	)
{
	/* not fclose(file->fp) */
	
	free( file->buffer) ;
	free( file) ;

	return  1 ;
}

kik_file_t *
kik_file_open(
	char *  file_path ,
	char *  mode
	)
{
	FILE *  fp ;
	
	if( ( fp = fopen( file_path , mode)) == NULL)
	{
		return  0 ;
	}

	return  kik_file_new( fp) ;
}

int
kik_file_close(
	kik_file_t *  file
	)
{
	int  result ;
	
	if( fclose( file->file) == 0)
	{
		result = 1 ;
	}
	else
	{
		result = 0 ;
	}

	result |= kik_file_delete( file) ;

	return  result ;
}

#ifdef  HAVE_FGETLN

/*
 * this is the wrapper function of fgetln().
 */
char *
kik_file_get_line(
	kik_file_t *  from ,
	size_t *  len
	)
{
	return  fgetln( from->file , len) ;
}

#else

/*
 * this behaves like fgetln().
 *
 * this returns the pointer to the beginning of line , and it becomes invalid
 * after the next kik_file_get_line() (whether successful or not) or as soon as
 * kik_file_close() is executed.
 */
char *
kik_file_get_line(
	kik_file_t *  from ,
	size_t *  len
	)
{
	size_t  filled ;
	int  c ;

	filled = 0 ;
	
	if( ( c = fgetc( from->file)) < 0)
	{
		return  NULL ;
	}

	while( 1)
	{
		if( filled == from->buf_size)
		{
			from->buf_size += BUF_UNIT_SIZE ;
			from->buffer = realloc( from->buffer , from->buf_size) ;
		}
		
		from->buffer[filled++] = c ;

		if( c == '\n')
		{
			break ;
		}

		if( ( c = fgetc( from->file)) < 0)
		{
			break ;
		}
	}

	*len = filled ;

	return  from->buffer ;
}

#endif
