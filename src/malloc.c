
#define EXTUNIX_WANT_MALLOC_INFO
#define EXTUNIX_WANT_MALLOC_STATS
#include "config.h"

#if defined(EXTUNIX_HAVE_MALLOC_STATS)

CAMLprim value caml_extunix_malloc_stats(value v_unit)
{
  malloc_stats();
  return Val_unit;
}

#endif

#if defined(EXTUNIX_HAVE_MALLOC_INFO)

#include <stdio.h>
#include <memory.h>

CAMLprim value caml_extunix_malloc_info(value v_unit)
{
  CAMLparam0();
  CAMLlocal1(v_s);
  char* buf = NULL;
  size_t size;
  int r;
  FILE* f = open_memstream(&buf,&size);
  if (NULL == f)
    uerror("malloc_info", Nothing);
  r = malloc_info(0,f);
  fclose(f);
  if (0 != r)
  {
    free(buf);
    uerror("malloc_info", Nothing);
  }
  v_s = caml_alloc_string(size);
  memcpy(Bp_val(v_s), buf, size);
  free(buf);
  CAMLreturn(v_s);
}

#endif

