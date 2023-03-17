#pragma once
#include "activitate.h"
#include "repo.h"
#include "service.h"
#include "validare.h"
#include "wishlistexceptii.h"
#include <algorithm>
#include <cassert>
class teste {
private:
	void tests_domain();
	void tests_repo();
	void test_find_srv();
	void test_service_add_delete_modify();
	void test_filter_by_description();
	void test_filter_by_type();
	void test_sort_by_title();
	void test_sort_by_description();
	void test_wishlist_add_generate_delete();
	void test_raport();
	void test_undo();
	void test_file();
public:
	void run_tests();
};