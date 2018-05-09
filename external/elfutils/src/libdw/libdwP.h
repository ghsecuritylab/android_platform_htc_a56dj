/* Internal definitions for libdwarf.
   Copyright (C) 2002-2011, 2013, 2014 Red Hat, Inc.
   This file is part of elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2002.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifndef _LIBDWP_H
#define _LIBDWP_H 1

#include <libintl.h>
#include <stdbool.h>

#include <libdw.h>
#include <dwarf.h>


#define _(Str) dgettext ("elfutils", Str)


struct loc_s
{
  void *addr;
  Dwarf_Op *loc;
  size_t nloc;
};

struct loc_block_s
{
  void *addr;
  unsigned char *data;
  size_t length;
};

struct files_lines_s
{
  Dwarf_Off debug_line_offset;
  Dwarf_Files *files;
  Dwarf_Lines *lines;
};

enum
  {
    IDX_debug_info = 0,
    IDX_debug_types,
    IDX_debug_abbrev,
    IDX_debug_aranges,
    IDX_debug_line,
    IDX_debug_frame,
    IDX_debug_loc,
    IDX_debug_pubnames,
    IDX_debug_str,
    IDX_debug_macinfo,
    IDX_debug_macro,
    IDX_debug_ranges,
    IDX_gnu_debugaltlink,
    IDX_last
  };


enum
{
  DWARF_E_NOERROR = 0,
  DWARF_E_UNKNOWN_ERROR,
  DWARF_E_INVALID_ACCESS,
  DWARF_E_NO_REGFILE,
  DWARF_E_IO_ERROR,
  DWARF_E_INVALID_ELF,
  DWARF_E_NO_DWARF,
  DWARF_E_NOELF,
  DWARF_E_GETEHDR_ERROR,
  DWARF_E_NOMEM,
  DWARF_E_UNIMPL,
  DWARF_E_INVALID_CMD,
  DWARF_E_INVALID_VERSION,
  DWARF_E_INVALID_FILE,
  DWARF_E_NO_ENTRY,
  DWARF_E_INVALID_DWARF,
  DWARF_E_NO_STRING,
  DWARF_E_NO_ADDR,
  DWARF_E_NO_CONSTANT,
  DWARF_E_NO_REFERENCE,
  DWARF_E_INVALID_REFERENCE,
  DWARF_E_NO_DEBUG_LINE,
  DWARF_E_INVALID_DEBUG_LINE,
  DWARF_E_TOO_BIG,
  DWARF_E_VERSION,
  DWARF_E_INVALID_DIR_IDX,
  DWARF_E_ADDR_OUTOFRANGE,
  DWARF_E_NO_LOCLIST,
  DWARF_E_NO_BLOCK,
  DWARF_E_INVALID_LINE_IDX,
  DWARF_E_INVALID_ARANGE_IDX,
  DWARF_E_NO_MATCH,
  DWARF_E_NO_FLAG,
  DWARF_E_INVALID_OFFSET,
  DWARF_E_NO_DEBUG_RANGES,
  DWARF_E_INVALID_CFI,
  DWARF_E_NO_ALT_DEBUGLINK,
  DWARF_E_INVALID_OPCODE,
};


#include "dwarf_sig8_hash.h"

struct Dwarf
{
  
  Elf *elf;

  
  Dwarf *alt_dwarf;

  
  Elf_Data *sectiondata[IDX_last];

#if USE_ZLIB
  
  unsigned int sectiondata_gzip_mask:IDX_last;
#endif

  
  bool other_byte_order;

  
  bool free_elf;

  struct pubnames_s
  {
    Dwarf_Off cu_offset;
    Dwarf_Off set_start;
    unsigned int cu_header_size;
    int address_len;
  } *pubnames_sets;
  size_t pubnames_nsets;

  
  void *cu_tree;
  Dwarf_Off next_cu_offset;

  
  void *tu_tree;
  Dwarf_Off next_tu_offset;
  Dwarf_Sig8_Hash sig8_hash;

  
  void *macro_ops;

  
  void *files_lines;

  
  Dwarf_Aranges *aranges;

  
  struct Dwarf_CFI_s *cfi;

  struct Dwarf_CU *fake_loc_cu;

  struct libdw_memblock
  {
    size_t size;
    size_t remaining;
    struct libdw_memblock *prev;
    char mem[0];
  } *mem_tail;

  
  size_t mem_default_size;

  
  Dwarf_OOM oom_handler;
};


struct Dwarf_Abbrev
{
  Dwarf_Off offset;
  unsigned char *attrp;
  unsigned int attrcnt;
  unsigned int code;
  unsigned int tag;
  bool has_children;
};

#include "dwarf_abbrev_hash.h"


struct Dwarf_Files_s
  {
    unsigned int ndirs;
    unsigned int nfiles;
    struct Dwarf_Fileinfo_s
    {
      char *name;
      Dwarf_Word mtime;
      Dwarf_Word length;
    } info[0];
    
  };
typedef struct Dwarf_Fileinfo_s Dwarf_Fileinfo;



struct Dwarf_Line_s
{
  Dwarf_Files *files;

  Dwarf_Addr addr;
  unsigned int file;
  int line;
  unsigned short int column;
  unsigned int is_stmt:1;
  unsigned int basic_block:1;
  unsigned int end_sequence:1;
  unsigned int prologue_end:1;
  unsigned int epilogue_begin:1;
  unsigned int op_index:8;
  unsigned int isa:8;
  unsigned int discriminator:24;
};

struct Dwarf_Lines_s
{
  size_t nlines;
  struct Dwarf_Line_s info[0];
};

struct Dwarf_Aranges_s
{
  Dwarf *dbg;
  size_t naranges;

  struct Dwarf_Arange_s
  {
    Dwarf_Addr addr;
    Dwarf_Word length;
    Dwarf_Off offset;
  } info[0];
};


struct Dwarf_CU
{
  Dwarf *dbg;
  Dwarf_Off start;
  Dwarf_Off end;
  uint8_t address_size;
  uint8_t offset_size;
  uint16_t version;

  
  size_t type_offset;
  uint64_t type_sig8;

  
  Dwarf_Abbrev_Hash abbrev_hash;
  
  size_t orig_abbrev_offset;
  
  size_t last_abbrev_offset;

  
  Dwarf_Lines *lines;

  
  Dwarf_Files *files;

  
  void *locs;

  
  void *startp;
  void *endp;
};

#define DIE_OFFSET_FROM_CU_OFFSET(cu_offset, offset_size, type_unit)	\
  ((type_unit) ? ((cu_offset) + 4 * (offset_size) - 4 + 3 + 8)		\
   : ((cu_offset) + 3 * (offset_size) - 4 + 3))

#define CUDIE(fromcu)							      \
  ((Dwarf_Die)								      \
   {									      \
     .cu = (fromcu),							      \
     .addr = ((char *) fromcu->dbg->sectiondata[cu_sec_idx (fromcu)]->d_buf   \
	      + DIE_OFFSET_FROM_CU_OFFSET ((fromcu)->start,		      \
					   (fromcu)->offset_size,	      \
					   (fromcu)->type_offset != 0))	      \
   })									      \


typedef struct
{
  Dwarf_Word nforms;
  unsigned char const *forms;
} Dwarf_Macro_Op_Proto;

typedef struct
{
  
  Dwarf_Off offset;

  
  Dwarf_Off line_offset;

  
  Dwarf_Files *files;

  const char *comp_dir;

  
  Dwarf_Half header_len;

  uint16_t version;
  bool is_64bit;
  uint8_t sec_index;	

  unsigned char opcodes[255];

  
  Dwarf_Macro_Op_Proto table[];
} Dwarf_Macro_Op_Table;

struct Dwarf_Macro_s
{
  Dwarf_Macro_Op_Table *table;
  Dwarf_Attribute *attributes;
  uint8_t opcode;
};

static inline Dwarf_Word
libdw_macro_nforms (Dwarf_Macro *macro)
{
  return macro->table->table[macro->table->opcodes[macro->opcode - 1]].nforms;
}

#include "memory-access.h"


extern void __libdw_seterrno (int value) internal_function;


#define libdw_alloc(dbg, type, tsize, cnt) \
  ({ struct libdw_memblock *_tail = (dbg)->mem_tail;			      \
     size_t _required = (tsize) * (cnt);				      \
     type *_result = (type *) (_tail->mem + (_tail->size - _tail->remaining));\
     size_t _padding = ((__alignof (type)				      \
			 - ((uintptr_t) _result & (__alignof (type) - 1)))    \
			& (__alignof (type) - 1));			      \
     if (unlikely (_tail->remaining < _required + _padding))		      \
       _result = (type *) __libdw_allocate (dbg, _required, __alignof (type));\
     else								      \
       {								      \
	 _required += _padding;						      \
	 _result = (type *) ((char *) _result + _padding);		      \
	 _tail->remaining -= _required;					      \
       }								      \
     _result; })

#define libdw_typed_alloc(dbg, type) \
  libdw_alloc (dbg, type, sizeof (type), 1)

extern void *__libdw_allocate (Dwarf *dbg, size_t minsize, size_t align)
     __attribute__ ((__malloc__)) __nonnull_attribute__ (1);

extern void __libdw_oom (void) __attribute ((noreturn, visibility ("hidden")));

#if USE_ZLIB
extern void __libdw_free_zdata (Dwarf *dwarf) internal_function;
#else
# define __libdw_free_zdata(dwarf)	((void) (dwarf))
#endif

extern struct Dwarf_CU *__libdw_intern_next_unit (Dwarf *dbg, bool debug_types)
     __nonnull_attribute__ (1) internal_function;

extern struct Dwarf_CU *__libdw_findcu (Dwarf *dbg, Dwarf_Off offset, bool tu)
     __nonnull_attribute__ (1) internal_function;

extern Dwarf_Abbrev *__libdw_findabbrev (struct Dwarf_CU *cu,
					 unsigned int code)
     __nonnull_attribute__ (1) internal_function;

extern Dwarf_Abbrev *__libdw_getabbrev (Dwarf *dbg, struct Dwarf_CU *cu,
					Dwarf_Off offset, size_t *lengthp,
					Dwarf_Abbrev *result)
     __nonnull_attribute__ (1) internal_function;

static inline Dwarf_Abbrev *
__nonnull_attribute__ (1)
__libdw_dieabbrev (Dwarf_Die *die, const unsigned char **readp)
{
  
  if (die->abbrev == NULL || readp != NULL)
    {
      
      unsigned int code;
      const unsigned char *addr = die->addr;
      get_uleb128 (code, addr, die->cu->endp);
      if (readp != NULL)
	*readp = addr;

      
      if (die->abbrev == NULL)
	die->abbrev = __libdw_findabbrev (die->cu, code);
    }
  return die->abbrev;
}

extern size_t __libdw_form_val_compute_len (struct Dwarf_CU *cu,
					    unsigned int form,
					    const unsigned char *valp)
     __nonnull_attribute__ (1, 3) internal_function;

static inline size_t
__nonnull_attribute__ (1, 3)
__libdw_form_val_len (struct Dwarf_CU *cu, unsigned int form,
		      const unsigned char *valp)
{
  static const uint8_t form_lengths[] =
    {
      [DW_FORM_flag_present] = 0x80,
      [DW_FORM_data1] = 1, [DW_FORM_ref1] = 1, [DW_FORM_flag] = 1,
      [DW_FORM_data2] = 2, [DW_FORM_ref2] = 2,
      [DW_FORM_data4] = 4, [DW_FORM_ref4] = 4,
      [DW_FORM_data8] = 8, [DW_FORM_ref8] = 8, [DW_FORM_ref_sig8] = 8,
    };

  
  if (form < sizeof form_lengths / sizeof form_lengths[0])
    {
      uint8_t len = form_lengths[form];
      if (len != 0)
	{
	  const unsigned char *endp = cu->endp;
	  len &= 0x7f; 
	  if (unlikely (len > (size_t) (endp - valp)))
	    {
	      __libdw_seterrno (DWARF_E_INVALID_DWARF);
	      return -1;
	    }
	  return len;
	}
    }

  
  return __libdw_form_val_compute_len (cu, form, valp);
}

extern int __libdw_formref (Dwarf_Attribute *attr, Dwarf_Off *return_offset)
     __nonnull_attribute__ (1, 2) internal_function;


extern unsigned char *__libdw_find_attr (Dwarf_Die *die,
					 unsigned int search_name,
					 unsigned int *codep,
					 unsigned int *formp)
     __nonnull_attribute__ (1) internal_function;

extern int __libdw_attr_intval (Dwarf_Die *die, int *valp, int attval)
     __nonnull_attribute__ (1, 2) internal_function;

struct Dwarf_Die_Chain
{
  Dwarf_Die die;
  struct Dwarf_Die_Chain *parent;
  bool prune;			
};
extern int __libdw_visit_scopes (unsigned int depth,
				 struct Dwarf_Die_Chain *root,
				 int (*previsit) (unsigned int depth,
						  struct Dwarf_Die_Chain *,
						  void *arg),
				 int (*postvisit) (unsigned int depth,
						   struct Dwarf_Die_Chain *,
						   void *arg),
				 void *arg)
  __nonnull_attribute__ (2, 3) internal_function;

extern int __libdw_intern_expression (Dwarf *dbg,
				      bool other_byte_order,
				      unsigned int address_size,
				      unsigned int ref_size,
				      void **cache, const Dwarf_Block *block,
				      bool cfap, bool valuep,
				      Dwarf_Op **llbuf, size_t *listlen,
				      int sec_index)
  __nonnull_attribute__ (5, 6, 9, 10) internal_function;

extern Dwarf_Die *__libdw_offdie (Dwarf *dbg, Dwarf_Off offset,
				  Dwarf_Die *result, bool debug_types)
  internal_function;


extern int __dwarf_errno_internal (void);




static inline int
__libdw_relocate_address (Dwarf *dbg __attribute__ ((unused)),
			  int sec_index __attribute__ ((unused)),
			  const void *addr __attribute__ ((unused)),
			  int width __attribute__ ((unused)),
			  Dwarf_Addr *val __attribute__ ((unused)))
{
  return 0;
}

static inline int
__libdw_relocate_offset (Dwarf *dbg __attribute__ ((unused)),
			 int sec_index __attribute__ ((unused)),
			 const void *addr __attribute__ ((unused)),
			 int width __attribute__ ((unused)),
			 Dwarf_Off *val __attribute__ ((unused)))
{
  return 0;
}

static inline Elf_Data *
__libdw_checked_get_data (Dwarf *dbg, int sec_index)
{
  Elf_Data *data = dbg->sectiondata[sec_index];
  if (unlikely (data == NULL)
      || unlikely (data->d_buf == NULL))
    {
      __libdw_seterrno (DWARF_E_INVALID_DWARF);
      return NULL;
    }
  return data;
}

static inline int
__libdw_offset_in_section (Dwarf *dbg, int sec_index,
			   Dwarf_Off offset, size_t size)
{
  Elf_Data *data = __libdw_checked_get_data (dbg, sec_index);
  if (data == NULL)
    return -1;
  if (unlikely (offset > data->d_size)
      || unlikely (data->d_size - offset < size))
    {
      __libdw_seterrno (DWARF_E_INVALID_OFFSET);
      return -1;
    }

  return 0;
}

static inline bool
__libdw_in_section (Dwarf *dbg, int sec_index,
		    const void *addr, size_t size)
{
  Elf_Data *data = __libdw_checked_get_data (dbg, sec_index);
  if (data == NULL)
    return false;
  if (unlikely (addr < data->d_buf)
      || unlikely (data->d_size - (addr - data->d_buf) < size))
    {
      __libdw_seterrno (DWARF_E_INVALID_OFFSET);
      return false;
    }

  return true;
}

#define READ_AND_RELOCATE(RELOC_HOOK, VAL)				\
  ({									\
    if (!__libdw_in_section (dbg, sec_index, addr, width))		\
      return -1;							\
									\
    const unsigned char *orig_addr = addr;				\
    if (width == 4)							\
      VAL = read_4ubyte_unaligned_inc (dbg, addr);			\
    else								\
      VAL = read_8ubyte_unaligned_inc (dbg, addr);			\
									\
    int status = RELOC_HOOK (dbg, sec_index, orig_addr, width, &VAL);	\
    if (status < 0)							\
      return status;							\
    status > 0;								\
   })

static inline int
__libdw_read_address_inc (Dwarf *dbg,
			  int sec_index, const unsigned char **addrp,
			  int width, Dwarf_Addr *ret)
{
  const unsigned char *addr = *addrp;
  READ_AND_RELOCATE (__libdw_relocate_address, (*ret));
  *addrp = addr;
  return 0;
}

static inline int
__libdw_read_address (Dwarf *dbg,
		      int sec_index, const unsigned char *addr,
		      int width, Dwarf_Addr *ret)
{
  READ_AND_RELOCATE (__libdw_relocate_address, (*ret));
  return 0;
}

static inline int
__libdw_read_offset_inc (Dwarf *dbg,
			 int sec_index, const unsigned char **addrp,
			 int width, Dwarf_Off *ret, int sec_ret,
			 size_t size)
{
  const unsigned char *addr = *addrp;
  READ_AND_RELOCATE (__libdw_relocate_offset, (*ret));
  *addrp = addr;
  return __libdw_offset_in_section (dbg, sec_ret, *ret, size);
}

static inline int
__libdw_read_offset (Dwarf *dbg, Dwarf *dbg_ret,
		     int sec_index, const unsigned char *addr,
		     int width, Dwarf_Off *ret, int sec_ret,
		     size_t size)
{
  READ_AND_RELOCATE (__libdw_relocate_offset, (*ret));
  return __libdw_offset_in_section (dbg_ret, sec_ret, *ret, size);
}

static inline size_t
cu_sec_idx (struct Dwarf_CU *cu)
{
  return cu->type_offset == 0 ? IDX_debug_info : IDX_debug_types;
}

int __libdw_read_begin_end_pair_inc (Dwarf *dbg, int sec_index,
				     unsigned char **addr, int width,
				     Dwarf_Addr *beginp, Dwarf_Addr *endp,
				     Dwarf_Addr *basep)
  internal_function;

unsigned char * __libdw_formptr (Dwarf_Attribute *attr, int sec_index,
				 int err_nodata, unsigned char **endpp,
				 Dwarf_Off *offsetp)
  internal_function;

void __libdw_empty_loc_attr (Dwarf_Attribute *attr)
  internal_function;

int __libdw_getsrclines (Dwarf *dbg, Dwarf_Off debug_line_offset,
			 const char *comp_dir, unsigned address_size,
			 Dwarf_Lines **linesp, Dwarf_Files **filesp)
  internal_function
  __nonnull_attribute__ (1);

const char *__libdw_getcompdir (Dwarf_Die *cudie);


INTDECL (dwarf_aggregate_size)
INTDECL (dwarf_attr)
INTDECL (dwarf_attr_integrate)
INTDECL (dwarf_begin)
INTDECL (dwarf_begin_elf)
INTDECL (dwarf_child)
INTDECL (dwarf_dieoffset)
INTDECL (dwarf_diename)
INTDECL (dwarf_end)
INTDECL (dwarf_entrypc)
INTDECL (dwarf_errmsg)
INTDECL (dwarf_formaddr)
INTDECL (dwarf_formblock)
INTDECL (dwarf_formref_die)
INTDECL (dwarf_formsdata)
INTDECL (dwarf_formstring)
INTDECL (dwarf_formudata)
INTDECL (dwarf_getalt)
INTDECL (dwarf_getarange_addr)
INTDECL (dwarf_getarangeinfo)
INTDECL (dwarf_getaranges)
INTDECL (dwarf_getlocation_die)
INTDECL (dwarf_getsrcfiles)
INTDECL (dwarf_getsrclines)
INTDECL (dwarf_hasattr)
INTDECL (dwarf_haschildren)
INTDECL (dwarf_haspc)
INTDECL (dwarf_highpc)
INTDECL (dwarf_lowpc)
INTDECL (dwarf_nextcu)
INTDECL (dwarf_next_unit)
INTDECL (dwarf_offdie)
INTDECL (dwarf_peel_type)
INTDECL (dwarf_ranges)
INTDECL (dwarf_setalt)
INTDECL (dwarf_siblingof)
INTDECL (dwarf_srclang)
INTDECL (dwarf_tag)

#endif	