/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#include "idxmap.h"

GIT__USE_IDXMAP
GIT__USE_IDXMAP_ICASE

int git_idxmap_alloc(git_idxmap **map)
{
	if ((*map = kh_init(idx)) == NULL) {
		giterr_set_oom();
		return -1;
	}

	return 0;
}

int git_idxmap_icase_alloc(git_idxmap_icase **map)
{
	if ((*map = kh_init(idxicase)) == NULL) {
		giterr_set_oom();
		return -1;
	}

	return 0;
}

void git_idxmap_insert(git_idxmap *map, const git_index_entry *key, void *value, int *rval)
{
	khiter_t idx = kh_put(idx, map, key, rval);

	if ((*rval) >= 0) {
		if ((*rval) == 0)
			kh_key(map, idx) = key;
		kh_val(map, idx) = value;
	}
}

void git_idxmap_icase_insert(git_idxmap_icase *map, const git_index_entry *key, void *value, int *rval)
{
	khiter_t idx = kh_put(idxicase, map, key, rval);

	if ((*rval) >= 0) {
		if ((*rval) == 0)
			kh_key(map, idx) = key;
		kh_val(map, idx) = value;
	}
}

size_t git_idxmap_lookup_index(git_idxmap *map, const git_index_entry *key)
{
	return kh_get(idx, map, key);
}

size_t git_idxmap_icase_lookup_index(git_idxmap_icase *map, const git_index_entry *key)
{
	return kh_get(idxicase, map, key);
}

void *git_idxmap_value_at(git_idxmap *map, size_t idx)
{
	return kh_val(map, idx);
}

int git_idxmap_valid_index(git_idxmap *map, size_t idx)
{
	return idx != kh_end(map);
}

int git_idxmap_has_data(git_idxmap *map, size_t idx)
{
	return kh_exist(map, idx);
}

void git_idxmap_resize(git_idxmap *map, size_t size)
{
	kh_resize(idx, map, size);
}

void git_idxmap_icase_resize(git_idxmap_icase *map, size_t size)
{
	kh_resize(idxicase, map, size);
}

void git_idxmap__free(git_idxmap *map)
{
	kh_destroy(idx, map);
}

void git_idxmap_clear(git_idxmap *map)
{
	kh_clear(idx, map);
}

void git_idxmap_delete_at(git_idxmap *map, size_t idx)
{
	kh_del(idx, map, idx);
}

void git_idxmap_icase_delete_at(git_idxmap_icase *map, size_t idx)
{
	kh_del(idxicase, map, idx);
}

void git_idxmap_delete(git_idxmap *map, const git_index_entry *key)
{
	khiter_t idx = git_idxmap_lookup_index(map, key);
	if (git_idxmap_valid_index(map, idx))
		git_idxmap_delete_at(map, idx);
}
void git_idxmap_icase_delete(git_idxmap_icase *map, const git_index_entry *key)
{
	khiter_t idx = git_idxmap_icase_lookup_index(map, key);
	if (git_idxmap_valid_index((git_idxmap *)map, idx))
		git_idxmap_icase_delete_at(map, idx);
}
