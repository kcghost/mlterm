/*
 *	$Id$
 */

#include  "mkf_big5_parser.h"

#include  <kiklib/kik_mem.h>
#include  <kiklib/kik_debug.h>


/* --- static functions --- */

static int
big5_parser_next_char_intern(
	mkf_parser_t *  big5_parser ,
	mkf_char_t *  ch ,
	mkf_charset_t  big5cs
	)
{
	u_char  big5_byte1_start ;
	
	if( big5_parser->is_eos)
	{
		return  0 ;
	}

	mkf_parser_mark( big5_parser) ;

	/*
	 * 0x8140 - 0xa0fe: user defined area.
	 */
	if( big5cs == BIG5HKSCS)
	{
		big5_byte1_start = 0x81 ;
	}
	else /* if( big5cs == BIG5) */
	{
		big5_byte1_start = 0xa1 ;
	}
	
	if( /* 0x0 <= *big5_parser->str && */ *big5_parser->str <= 0x7f)
	{
		ch->ch[0] = *big5_parser->str ;
		ch->size = 1 ;
		ch->cs = US_ASCII ;
	}
	else if( big5_byte1_start <= *big5_parser->str && *big5_parser->str <= 0xfe)
	{
		ch->ch[0] = *big5_parser->str ;

		if( mkf_parser_increment( big5_parser) == 0)
		{
			mkf_parser_reset( big5_parser) ;

			return  0 ;
		}

		if( ( 0x40 <= *big5_parser->str && *big5_parser->str <= 0x7e) ||
			( 0xa1 <= *big5_parser->str && *big5_parser->str <= 0xfe))
		{
			ch->ch[1] = *big5_parser->str ;
		}
		else
		{
		#ifdef  DEBUG
			kik_warn_printf( KIK_DEBUG_TAG
				" the second byte(0x%x) big5 doesn't support is received.(first is 0x%x)\n" ,
				big5_parser->str[-1] , big5_parser->str[0]) ;
		#endif

			/* skipping */
			mkf_parser_increment( big5_parser) ;
		
			return  0 ;
		}
		
		ch->size = 2 ;
		ch->cs = big5cs ;
	}
	else
	{
		/* illegal */

		mkf_parser_increment( big5_parser) ;
		
		return  0 ;
	}

	ch->property = 0 ;

	mkf_parser_increment( big5_parser) ;
	
	return  1 ;
}

static int
big5_parser_next_char(
	mkf_parser_t *  big5_parser ,
	mkf_char_t *  ch
	)
{
	return  big5_parser_next_char_intern( big5_parser , ch , BIG5) ;
}

static int
big5hkscs_parser_next_char(
	mkf_parser_t *  big5_parser ,
	mkf_char_t *  ch
	)
{
	return  big5_parser_next_char_intern( big5_parser , ch , BIG5HKSCS) ;
}

static void
big5_parser_set_str(
	mkf_parser_t *  big5_parser ,
	u_char *  str ,
	size_t  size
	)
{
	big5_parser->str = str ;
	big5_parser->left = size ;
	big5_parser->marked_left = 0 ;
	big5_parser->is_eos = 0 ;
}

static void
big5_parser_delete(
	mkf_parser_t *  s
	)
{
	free( s) ;
}


/* --- global functions --- */

mkf_parser_t *
mkf_big5_parser_new(void)
{
	mkf_parser_t *  big5_parser ;
	
	if( ( big5_parser = malloc( sizeof( mkf_parser_t))) == NULL)
	{
		return  NULL ;
	}

	mkf_parser_init( big5_parser) ;

	big5_parser->init = mkf_parser_init ;
	big5_parser->next_char = big5_parser_next_char ;
	big5_parser->set_str = big5_parser_set_str ;
	big5_parser->delete = big5_parser_delete ;

	return  big5_parser ;
}

mkf_parser_t *
mkf_big5hkscs_parser_new(void)
{
	mkf_parser_t *  big5_parser ;
	
	if( ( big5_parser = malloc( sizeof( mkf_parser_t))) == NULL)
	{
		return  NULL ;
	}

	mkf_parser_init( big5_parser) ;

	big5_parser->init = mkf_parser_init ;
	big5_parser->next_char = big5hkscs_parser_next_char ;
	big5_parser->set_str = big5_parser_set_str ;
	big5_parser->delete = big5_parser_delete ;

	return  big5_parser ;
}
