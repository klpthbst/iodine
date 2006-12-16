/*
 * Copyright (c) 2006 Bjorn Andersson <flex@kryo.se>, Erik Ekman <yarrick@kryo.se>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base32.h"
#include "test.h"

struct touple
{
	char *a;
	char *b;
} testpairs[] = {
	{ "abc123", "mfrggmjsgm" },
	{ NULL, NULL }	
};

START_TEST(test_base32_encode)
{
	size_t len;
	char *buf;
	int i;

	len = 0;
	buf = NULL;

	for (i = 0; testpairs[i].a != NULL; i++) {
		base32_encode(&buf, &len, testpairs[i].a, strlen(testpairs[i].a));

		fail_unless(strcmp(buf, testpairs[i].b) == 0, 
				va_str("'%s' != '%s'", buf, testpairs[i].b));
	}
}
END_TEST

START_TEST(test_base32_decode)
{
	size_t len;
	void *buf;
	int i;

	len = 0;
	buf = NULL;

	for (i = 0; testpairs[i].a != NULL; i++) {
		base32_decode(&buf, &len, testpairs[i].b);

		fail_unless(strcmp(buf, testpairs[i].a) == 0, 
				va_str("'%s' != '%s'", buf, testpairs[i].a));
	}
}
END_TEST

TCase *
test_base32_create_tests()
{
	TCase *tc;

	tc = tcase_create("Base32");
	tcase_add_test(tc, test_base32_encode);
	tcase_add_test(tc, test_base32_decode);

	return tc;
}
