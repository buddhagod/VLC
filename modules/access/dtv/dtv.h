/**
 * @file dtv.h
 * @brief Digital TV module common header
 */
/*****************************************************************************
 * Copyright © 2011 Rémi Denis-Courmont
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 ****************************************************************************/

typedef struct delsys delsys_t;

extern const delsys_t dvbc, dvbs, dvbs2, dvbt, atsc;

typedef struct dvb_device dvb_device_t;

dvb_device_t *dvb_open (vlc_object_t *obj, bool tune);
void dvb_close (dvb_device_t *);
ssize_t dvb_read (dvb_device_t *, void *, size_t);

int dvb_add_pid (dvb_device_t *, uint16_t);
void dvb_remove_pid (dvb_device_t *, uint16_t);

const delsys_t *dvb_guess_system (dvb_device_t *);
float dvb_get_signal_strength (dvb_device_t *);
float dvb_get_snr (dvb_device_t *);

int dvb_set_inversion (dvb_device_t *, int);
int dvb_tune (dvb_device_t *);

/* DVB-C */
int dvb_set_dvbc (dvb_device_t *, uint32_t freq, const char *mod,
                  uint32_t srate, const char *fec);

/* DVB-S */
int dvb_set_dvbs (dvb_device_t *, uint32_t freq, uint32_t srate,
                  const char *fec);
int dvb_set_dvbs2 (dvb_device_t *, uint32_t freq, const char *mod,
                   uint32_t srate, const char *fec, int pilot, int rolloff);
int dvb_set_sec (dvb_device_t *, bool tone, int voltage, bool high_voltage);
/* XXX^^ */

/* DVB-T */
int dvb_set_dvbt (dvb_device_t *, uint32_t freq, const char *mod,
                  const char *fec_hp, const char *fec_lp, uint32_t bandwidth,
                  int transmission, const char *guard, int hierarchy);

/* ATSC */
int dvb_set_atsc (dvb_device_t *, uint32_t freq, const char *mod);

/* ISDB-T */
typedef struct isdbt_layer
{
    const char *modulation;
    const char *code_rate;
    uint8_t segment_count;
    uint8_t time_interleaving;
} isdbt_layer_t;

typedef struct isdbt_sound
{
    uint8_t subchannel_id;
    uint8_t segment_index;    uint8_t segment_cound;
} isdbt_sound_t;

int dvb_set_isdbt (dvb_device_t *, uint32_t freq, const isdbt_layer_t *a,
                   const isdbt_layer_t *b, const isdbt_layer_t *c,
                   const isdbt_sound_t *sb);
