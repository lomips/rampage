/*
    Copyright (C) 2010  Jens Neuhalfen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>       /* printk() */

#include <linux/mm.h>
#include <linux/pfn.h>
#include <linux/memory_hotplug.h>

void my_dump_page(struct page *page, char *msg)
{
#if 0
	if (!msg)
		msg="";

	if (page)
		pr_debug("%s page #%lu: flags: %lx Count: %i, Mapcount: %i, Mapping/private/first_page/... %p. Index: %lu. lru.next: %p / prev: %p\n",
			 msg, page_to_pfn(page), page->flags, page_count(page),
			 page_mapcount(page), page->mapping, page->index,
			 page->lru.next, page->lru.prev);
	else
		pr_debug("%s page NULL\n", msg);
#endif
}

int rampage_remove_memory(u64 start, u64 size)
{
	unsigned long start_pfn, nr_pages;
	int ret;

	mem_hotplug_begin();

	start_pfn = PFN_DOWN(start);
	nr_pages = PFN_DOWN(size);
	ret = offline_pages(start_pfn, nr_pages);

	mem_hotplug_done();
	return ret;
}

int rampage_online_pages(unsigned long pfn, unsigned long nr_pages)
{
	int ret;

	mem_hotplug_begin();

	ret = online_pages(pfn, nr_pages, MMOP_ONLINE_KEEP);

	mem_hotplug_done();
	return ret;
}

int rampage_add_memory(u64 start, u64 size)
{
	unsigned long start_pfn, nr_pages;
	int ret;

	mem_hotplug_begin();

	start_pfn = PFN_DOWN(start);
	nr_pages = PFN_DOWN(size);
	ret = online_pages(start_pfn, nr_pages, MMOP_ONLINE_KEEP);

	mem_hotplug_done();
	return ret;
}
