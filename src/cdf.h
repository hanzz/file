/*-
 * Copyright (c) 2008 Christos Zoulas
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Info from: http://sc.openoffice.org/compdocfileformat.pdf 
 */

#ifndef _H_CDF_
#define _H_CDF_

typedef int32_t cdf_secid_t;

#define CDF_SECID_NULL					0
#define CDF_SECID_FREE					-1
#define	CDF_SECID_END_OF_CHAIN				-2
#define	CDF_SECID_SECTOR_ALLOCATION_TABLE		-3
#define CDF_SECID_MASTER_SECTOR_ALLOCATION_TABLE	-4

typedef struct {
	uint64_t	h_magic;
#define CDF_MAGIC	0xE11AB1A1E011CFD0LL
	uint64_t	h_uuid[2];
	uint16_t	h_revision;
	uint16_t	h_version;
	uint16_t	h_byte_order;
	uint16_t	h_sec_size_p2;
	uint16_t	h_short_sec_size_p2;
	uint8_t		h_unused0[10];
	uint32_t	h_num_sectors_in_sat;
	uint32_t	h_secid_first_directory;
	uint8_t		h_unused1[4];
	uint32_t	h_min_size_standard_stream;
	cdf_secid_t	h_secid_first_sector_in_short_sat;
	uint32_t	h_num_sectors_in_short_sat;
	cdf_secid_t	h_secid_first_sector_in_master_sat;
	uint32_t	h_num_sectors_in_master_sat;
	cdf_secid_t	h_master_sat[436/4];
} cdf_header_t;

#define CDF_SEC_SIZE(h)	(1 << (h)->h_sec_size_p2)
#define CDF_SEC_POS(h, secid) (512 + (secid) * CDF_SEC_SIZE(h))
#define CDF_SHORT_SEC_SIZE(h)	(1 << (h)->h_short_sec_size_p2)
#define CDF_SHORT_SEC_POS(h, secid) ((secid) * CDF_SHORT_SEC_SIZE(h))

typedef int32_t	cdf_dirid_t;
#define CDF_DIRID_NULL	-1

typedef int64_t	cdf_timestamp_t;
#define CDF_BASE_YEAR	1601
#define CDF_TIME_PREC	10000000

typedef struct {
	uint16_t	d_name[32];
	uint16_t	d_namelen;
	uint8_t		d_type;
#define CDF_DIR_TYPE_EMPTY		0
#define	CDF_DIR_TYPE_USER_STORAGE	1
#define	CDF_DIR_TYPE_USER_STREAM	2
#define	CDF_DIR_TYPE_LOCKBYTES		3
#define	CDF_DIR_TYPE_PROPERTY		4
#define	CDF_DIR_TYPE_ROOT_STORAGE	5
	uint8_t		d_color;
#define CDF_DIR_COLOR_READ	0
#define CDF_DIR_COLOR_BLACK	1
	cdf_dirid_t	d_left_child;
	cdf_dirid_t	d_right_child;
	cdf_dirid_t	d_storage;
	uint64_t	d_storage_uuid[2];
	uint32_t	d_flags;
	cdf_timestamp_t	d_created;
	cdf_timestamp_t	d_modified;
	cdf_secid_t	d_stream_first_sector;
	uint32_t	d_size;
	uint32_t	d_unused0;
} cdf_directory_t;

typedef struct {
	cdf_secid_t *sat_tab;
	size_t sat_len;
} cdf_sat_t;

typedef struct {
	cdf_directory_t *dir_tab;
	size_t dir_len;
} cdf_dir_t;

typedef struct {
	void *sst_tab;
	size_t sst_len;
	size_t sst_dirlen;
} cdf_stream_t;

typedef struct {
	uint32_t	cl_dword;
	uint16_t	cl_word[2];
	uint8_t		cl_two[2];
	uint8_t		cl_six[6];
} cdf_classid_t;

typedef struct {
	uint16_t	si_byte_order;
	uint16_t	si_zero;
	uint16_t	si_os_version;
	uint16_t	si_os;
	cdf_classid_t	si_class;
	uint32_t	si_count;
} cdf_summary_info_header_t;

#define CDF_SECTION_DECLARATION_OFFSET 0x1c

typedef struct {
	cdf_classid_t	sd_class;
	uint32_t	sd_offset;
} cdf_section_declaration_t;

typedef struct {
	uint32_t	sh_len;
	uint32_t	sh_properties;
} cdf_section_header_t;

#define CDF_ROUND(val, by)     (((val) + (by) - 1) & ~((by) - 1))

#define CDF_SIGNED16		0x00000002
#define CDF_SIGNED32		0x00000003
#define	CDF_UNSIGNED32		0x00000013
#define CDF_LENGTH32_STRING	0x0000001e
#define CDF_FILETIME		0x00000040
#define CDF_CLIPBOARD		0x00000047

#define CDF_PROPERTY_CODE_PAGE			0x00000001
#define CDF_PROPERTY_TITLE			0x00000002
#define CDF_PROPERTY_SUBJECT			0x00000003
#define CDF_PROPERTY_AUTHOR			0x00000004
#define CDF_PROPERTY_KEYWORDS			0x00000005
#define CDF_PROPERTY_COMMENTS 			0x00000006
#define CDF_PROPERTY_TEMPLATE			0x00000007
#define CDF_PROPERTY_LAST_SAVED_BY		0x00000008
#define CDF_PROPERTY_REVISION_NUMBER		0x00000009
#define CDF_PROPERTY_TOTAL_EDITING_TIME		0x0000000a
#define CDF_PROPERTY_LAST_PRINTED		0X0000000b
#define CDF_PROPERTY_CREATE_TIME		0x0000000c
#define CDF_PROPERTY_LAST_SAVED_TIME		0x0000000d
#define CDF_PROPERTY_NUMBER_OF_PAGES		0x0000000e
#define CDF_PROPERTY_NUMBER_OF_WORDS		0x0000000f
#define CDF_PROPERTY_NUMBER_OF_CHARACTERS	0x00000010
#define CDF_PROPERTY_THUMBNAIL			0x00000011
#define CDF_PROPERTY_NAME_OF_APPLICATION	0x00000012
#define CDF_PROPERTY_SECURITY			0x00000013
#define CDF_PROPERTY_LOCALE_ID			0x80000000

#define CDF_NEED_SWAP	cdf_need_swap()

#define CDF_TOLE8(x)	(CDF_NEED_SWAP ? cdf_tole8(x) : (uint64_t)(x))
#define CDF_TOLE4(x)	(CDF_NEED_SWAP ? cdf_tole4(x) : (uint32_t)(x))
#define CDF_TOLE2(x)	(CDF_NEED_SWAP ? cdf_tole2(x) : (uint16_t)(x))

struct timespec;
int cdf_timestamp_to_timespec(struct timespec *, cdf_timestamp_t);
int cdf_timespec_to_timestamp(cdf_timestamp_t *, const struct timespec *);
int cdf_need_swap(void);
int cdf_read_header(int, cdf_header_t *);
void cdf_swap_header(cdf_header_t *);
void cdf_swap_dir(cdf_directory_t *);
ssize_t cdf_read_sector(int, void *, size_t, size_t, const cdf_header_t *,
    cdf_secid_t);
int cdf_read_sat(int, cdf_header_t *, cdf_sat_t *);
size_t cdf_count_chain(const cdf_header_t *, const cdf_sat_t *, cdf_secid_t);
int cdf_read_stream(int, const cdf_header_t *, const cdf_sat_t *, cdf_secid_t,
    size_t, cdf_stream_t *);
int cdf_read_dir(int, const cdf_header_t *, const cdf_sat_t *, cdf_dir_t *);
int cdf_read_ssat(int, const cdf_header_t *, const cdf_sat_t *, cdf_sat_t *);
int cdf_read_short_stream(int, const cdf_header_t *, const cdf_sat_t *,
    const cdf_dir_t *, cdf_stream_t *);
int cdf_read_summary_info(int, const cdf_header_t *, const cdf_sat_t *,
    const cdf_dir_t *, cdf_stream_t *);
int cdf_print_classid(char *, size_t, const cdf_classid_t *);
int cdf_print_property_name(char *, size_t, uint32_t);
int cdf_print_elapsed_time(char *, size_t, cdf_timestamp_t);
uint16_t cdf_tole2(uint16_t);
uint32_t cdf_tole4(uint32_t);
uint64_t cdf_tole8(uint64_t);

#ifdef CDF_DEBUG
void cdf_dump_header(const cdf_header_t *);
void cdf_dump_sat(const char *, const cdf_header_t *, const cdf_sat_t *);
void cdf_dump(void *, size_t);
void cdf_dump_stream(const cdf_header_t *, const cdf_stream_t *);
void cdf_dump_dir(int, const cdf_header_t *, const cdf_sat_t *, const cdf_dir_t *);
void cdf_dump_section_info(const cdf_stream_t *, uint32_t);
void cdf_dump_summary_info(const cdf_header_t *, const cdf_stream_t *);
#endif


#endif /* _H_CDF_ */