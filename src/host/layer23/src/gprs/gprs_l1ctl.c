/* L1CTL protocol for GPRS on phone */

/* (C) 2015 by Miroslav Babjak
 *
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <l1ctl_proto.h>

#include <osmocom/core/msgb.h>
#include <osmocom/bb/common/l1l2_interface.h>
#include <osmocom/bb/gprs/gprs_l1ctl.h>
#include <osmocom/bb/common/osmocom_data.h>
#include <osmocom/bb/common/logging.h>

/** handle received GPRS data */
int rx_ph_gprs_data_ind(struct osmocom_ms *ms, struct msgb *msg){

	struct l1ctl_gprs_data_ind *data_ind;
	struct l1ctl_info_dl *dl;

	if (msgb_l3len(msg) < sizeof(*data_ind)) {
		LOGP(DL1C, LOGL_ERROR, "MSG too short GPRS Data Ind: %u\n",
				msgb_l3len(msg));
		msgb_free(msg);
		return -1;
	}

	dl = (struct l1ctl_info_dl *) msg->l1h;
	msg->l2h = dl->payload;
	data_ind = (struct l1ctl_gprs_data_ind *) msg->l2h;

	/* pull the L1 header from the msgb */
	msgb_pull(msg, msg->l2h - (msg->l1h-sizeof(struct l1ctl_hdr)));
	msg->l1h = NULL;

	return 1;
}
