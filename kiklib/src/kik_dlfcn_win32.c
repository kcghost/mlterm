/*
 *	$Id$
 */

#include  "kik_dlfcn.h"

#include  <stdio.h>		/* NULL */
#include  <string.h>		/* strlen */
#include  <limits.h>		/* MAX_PATH */
#include  "kik_mem.h"		/* alloca() */

#include  <windows.h>
#include  <winbase.h>

/* --- global functions --- */

kik_dl_handle_t
kik_dl_open(
	const char *  dirpath ,
	const char *  name
	)
{
	HMODULE  module ;
	char *  path ;
#if defined(__CYGWIN__) || defined(__MSYS__)
	char  winpath[MAX_PATH];
#endif

	if( ( path = alloca( strlen( dirpath) + strlen( name) + 8)) == NULL)
	{
		return  NULL ;
	}

#if defined(__CYGWIN__)
	sprintf( path , "%scyg%s.dll" , dirpath , name) ;
	cygwin_conv_to_win32_path( path , winpath);
	path = winpath ;
#elif  defined(__MSYS__)
	sprintf( path , "%slib%s.dll" , dirpath , name) ;
	cygwin_conv_to_win32_path( path , winpath) ;
	path = winpath ;
#else
	sprintf( path , "%slib%s.dll" , dirpath , name) ;
#endif

	if( ( module = LoadLibrary( path)))
	{
		return  ( kik_dl_handle_t)module ;
	}

#if defined(__CYGWIN__) || defined(__MSYS__)
	sprintf( path , "%s%s.dll" , dirpath , name) ;
	cygwin_conv_to_win32_path( path , winpath) ;
	path = winpath ;
#else
	sprintf( path , "%s%s.dll" , dirpath , name) ;
#endif

	if( ( module = LoadLibrary( path)))
	{
		return  ( kik_dl_handle_t)module ;
	}

	return  NULL ;
}

int
kik_dl_close(
	kik_dl_handle_t  handle
	)
{
	return  FreeLibrary( (HMODULE)handle) ;
}

void *
kik_dl_func_symbol(
	kik_dl_handle_t  handle ,
	const char *  symbol
	)
{
	return  GetProcAddress( (HMODULE)handle , symbol) ;
}

int
kik_dl_is_module(
	const char *  name
	)
{
	size_t  len ;

	if ( ! name)
	{
		return  0 ;
	}

	if( ( len = strlen( name)) < 4)
	{
		return  0 ;
	}

	if( strcmp( &name[len - 4] , ".dll") == 0)
	{
		return  1 ;
	}

	return  0 ;
}

