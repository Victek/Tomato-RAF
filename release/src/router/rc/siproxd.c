/*

	Copyright (C) 2011 Ofer Chen - oferchen AT gmail DOT com
	No Part of this file may be used without permissions.

*/


#include "rc.h"

static const char siproxdpid[] = "/tmp/var/run/siproxd.pid";
static const char siproxdregistrationfile[] =  "/tmp/var/run/siproxd_registration";
static const char siproxdconf[] = "/tmp/etc/siproxd.conf";
static const char siproxdplugindir[] = "/usr/lib/siproxd/";
static const char siproxd_process[] = "siproxd";
unsigned int fastpath=0;

int build_siproxd_conf (void)
{
	char *dp; //default param buffer
	FILE *f;
	unsigned int i; //integer cast


	syslog(LOG_INFO,"siproxd - config file generating started\n");
	if (!(f=fopen(siproxdconf,"w")))
	{
	perror(siproxdconf);
	return errno;
	}

	fprintf(f, "# Siproxd daemon generated config\n");

	if ((dp=nvram_safe_get("siproxd_if_inbound")) == NULL) dp = nvram_safe_get("lan_ifname");
	fprintf(f, "if_inbound=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_if_outbound")) == NULL) dp = nvram_safe_get("wan_ifname");
	fprintf(f, "if_outbound=%s\n", dp);

	i=nvram_get_int("siproxd_listen_port");
	if ((i <= 0) || (i >= 0xFFFF)) i = 5060; // 0xFFFF 65535
	fprintf(f, "sip_listen_port=%d\n", i);

	if ((dp=nvram_safe_get("siproxd_daemonize")) == NULL) dp = "1";
	fprintf(f, "daemonize=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_silence_log")) == NULL) dp = "1";
	fprintf(f, "silence_log=%s\n", dp);

	fprintf(f, "registration_file=%s\n", siproxdregistrationfile); //registration file location is static

	if ((dp=nvram_safe_get("siproxd_autosave_registrations")) == NULL) dp = "90";
	fprintf(f, "autosave_registrations=%s\n", dp);

	fprintf(f,"pid_file=%s\n",siproxdpid); //pid file is static

	if ((dp=nvram_safe_get("siproxd_rtp_proxy")) == NULL) dp = "1";
	fprintf(f, "rtp_proxy_enable=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_rtp_port_low")) == NULL) dp = "10000";
	fprintf(f, "rtp_port_low=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_rtp_port_high")) == NULL) dp = "10010";
	fprintf(f, "rtp_port_high=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_rtp_timeout")) == NULL) dp = "300";
	fprintf(f, "rtp_timeout=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_rtp_dscp")) == NULL) dp = "46";
	fprintf(f, "rtp_dscp=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_sip_dscp")) == NULL) dp = "0";
	fprintf(f, "sip_dscp=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_default_expires")) == NULL) dp = "600";
	fprintf(f, "default_expires=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_debug_level") == NULL )) dp = "0x00000000";
	else
	i=nvram_get_int("siproxd_debug_level");
		switch (i) {
		case 0: dp = "0x00000000"; break;  /* 0x00000000 debug disabled */
		case 1: dp = "0x00000001"; break;  /* 0x00000001 babble (like entering/leaving func) */
		case 2: dp = "0x00000002"; break;  /* 0x00000002 network */
		case 3: dp = "0x00000004"; break;  /* 0x00000004 SIP manipulations */
		case 4: dp = "0x00000008"; break;  /* 0x00000008 Client registration */
		case 5: dp = "0x00000010"; break;  /* 0x00000010 non specified class */
		case 6: dp = "0x00000020"; break;  /* 0x00000020 proxy */
		case 7: dp = "0x00000040"; break;  /* 0x00000040 DNS stuff */
		case 8: dp = "0x00000080"; break;  /* 0x00000080 network traffic */
		case 9: dp = "0x00000100"; break;  /* 0x00000100 configuration */
		case 10: dp = "0x00000200"; break; /* 0x00000200 RTP proxy */
		case 11: dp = "0x00000400"; break; /* 0x00000400 Access list evaluation */
		case 12: dp = "0x00000800"; break; /* 0x00000800 Authentication */
		default: dp = "0x00000000"; break;  /* default is 0x00000000 debug disabled */
		}
	fprintf(f, "debug_level=%s\n", dp);

	if ((dp=nvram_safe_get("siproxd_debug_port")) == NULL) dp = "0";
	fprintf(f, "debug_port=%s\n", dp);

	fprintf(f, "plugindir=%s\n", siproxdplugindir); //plugin dir location is static

	if ((dp=nvram_safe_get("siproxd_logcall")) == NULL) dp = "1";
	if (strcmp(dp, "1") == 0) {
		fprintf(f,
		"load_plugin=plugin_logcall.la\n"
		"plugin_log_calls=1\n"
		);
	}

	if ((dp=nvram_safe_get("siproxd_shortdial")) == NULL) dp = "1";
	if (strcmp(dp, "1") == 0) {
		fprintf(f,
		"load_plugin=plugin_shortdial.la\n"
		);
	}
	if ((dp=nvram_safe_get("siproxd_pi_shortdial_akey")) == NULL) dp = "1";
	if (strcmp(dp, "1") == 0) {
		if ((dp=nvram_get("siproxd_pi_shortdial_akey")) == NULL) dp = "*00";
			fprintf(f, "plugin_shortdial_akey=%s\n", dp);
		if ((dp = nvram_get("siproxd_pi_shortdial1")) != NULL) fprintf(f, "plugin_shortdial_entry=%s\n", dp);
		if ((dp = nvram_get("siproxd_pi_shortdial2")) != NULL) fprintf(f, "plugin_shortdial_entry=%s\n", dp);
		if ((dp = nvram_get("siproxd_pi_shortdial3")) != NULL) fprintf(f, "plugin_shortdial_entry=%s\n", dp);
		if ((dp = nvram_get("siproxd_pi_shortdial4")) != NULL) fprintf(f, "plugin_shortdial_entry=%s\n", dp);
		if ((dp = nvram_get("siproxd_pi_shortdial5")) != NULL) fprintf(f, "plugin_shortdial_entry=%s\n", dp);
	}

	fclose(f);
	syslog(LOG_INFO,"siproxd - config file generating ended\n");
	return(0);
}


void start_siproxd(void)
{
	if (fastpath != 1) {
		if (!nvram_match("Siproxd_enable", "1")){ /* if siproxd not enabled dont run */
		syslog(LOG_INFO,"Siproxd not enabled - config file generation skipped!\n");
		return;
		}
	} else {
		syslog(LOG_INFO,"Siproxd - fastpath forced generation of config file\n");
	}
		
/* kill and clean all PIDs before running */
        if (fastpath != 1) {
                stop_siproxd();
        }else{
                stop_siproxdfp();
        }
        
	build_siproxd_conf();
	syslog(LOG_INFO,"Siproxd - running daemon\n");
	xstart(siproxd_process, "-c", siproxdconf ,"-p", siproxdpid);
}

void start_siproxdfp(void)
{
fastpath = 1;
start_siproxd();
fastpath = 0;
}

void stop_siproxd(void)
{
	unsigned int i;

	i = 0;
	syslog(LOG_INFO,"Siproxd - killing daemon\n");
	if ((i = pidof (siproxd_process)) > 3) {
		killall_tk(siproxd_process);
			if (f_exists(siproxdpid)) {
			unlink(siproxdpid);
			}
	}
}

void stop_siproxdfp(void)
{
fastpath = 1;
stop_nginx();
fastpath = 0;
}
