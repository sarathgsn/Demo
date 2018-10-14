/*
 * Copyright (c) 2002-2005 Atheros Communications, Inc.
 * All rights reserved.
 *
 * $Id: //depot/sw/releases/9.5.5/linux/drivers/ethernet/tools/ethreg.c#1 $
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <getopt.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>

#define ETHREG_TOOL_BUILD
#include "pkgconf/athrs_ioctl.h"
#include "shell_err.h"
#define CONFIG_ATHRS_QOS
#define CFG_ATHRS27_PHY
#define MAX_PORT 4
#define ARG_CHECK  0x3f
#define READ_MAC  0x01
#define WRITE_MAC 0x02
#define READ_PHY  0x10
#define WRITE_PHY 0x20
#define CMD_FLAG_REPEAT 0

#define READ_MAC  0x01
#define WRITE_MAC 0x02
#define READ_PHY  0x10
#define WRITE_PHY 0x20
#define CMD_FLAG_REPEAT 0

unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);   //base is the input number system

#ifdef CYGPKG_COMPONENT_VLAN

#define ACCESS_MODE 0
#define TRUNK_MODE 1
#define VLAN_TABLE_SIZE 10

struct vlan_table_entry {
    int vlanid;
    int portno;
};

static struct vlan_table_entry table[VLAN_TABLE_SIZE];

#endif /* CYGPKG_COMPONENT_VLAN */

struct ifreq ifr;
struct eth_cfg_params etd;
int s, opt_force = 0, duplex = 1;
const char *progname;

int 
do_ethreg(int argc, char *argv[])
{
    int rcode = 0, rd_value = 0;
    int reg = 0, val = 0, portnum;

    if (argc == 1) {
        reg = simple_strtoul(argv[0], ((void *)0), 10);
        rcode = READ_MAC;
    }
    if (argc == 2) {
        reg = simple_strtoul(argv[0], ((void *)0), 10);
        val = simple_strtoul(argv[1], ((void *)0), 10);
        rcode = WRITE_MAC;
    }
    if (argc == 3) {
        if (*argv[0] == 'p') {
            portnum = simple_strtoul(argv[1], ((void *)0), 10);
            reg = simple_strtoul(argv[2], ((void *)0), 10);
            rcode = READ_PHY;
        } else {
            return -EINVAL;
        }
    }
    if (argc == 4) {
        if (*argv[0] == 'p') {
            portnum = simple_strtoul(argv[1], ((void *)0), 10);
            reg = simple_strtoul(argv[2], ((void *)0), 10);
            val = simple_strtoul(argv[3], ((void *)0), 10);
            rcode = WRITE_PHY;
        } else {
            return -EINVAL;
        }
    }

    if ((argc > 3) || (argc < 1))
        return -EINVAL;

#ifdef CFG_ATHRS27_PHY

    if (rcode == READ_PHY) {
        rd_value = s27_rd_phy(1, portnum, reg);
        SHELL_PRINT("Read Reg: 0x%08x = 0x%08x\n", reg, rd_value);
    } else if (rcode == READ_MAC) {
        rd_value = athrs27_reg_read(reg);
        SHELL_PRINT("Read Reg: 0x%08x = 0x%08x\n", reg, rd_value);
    } else if (rcode == WRITE_PHY) {
        rd_value = s27_rd_phy(1, portnum, reg);
        s27_wr_phy(1, portnum, reg, val);
        SHELL_PRINT("Write Reg: 0x%08x: Oldval = 0x%08x Newval = 0x%08x\n", reg,
                    rd_value, val);
    } else if (rcode == WRITE_MAC) {
        rd_value = athrs27_reg_read(reg);
        athrs27_reg_write(reg, val);
        SHELL_PRINT("Write Reg: 0x%08x: Oldval = 0x%08x Newval = 0x%08x\n", reg,
                    rd_value, val);
    } else {
        return -EINVAL;
    }

#endif /* CFG_ATHRS27_PHY */
     return 0;
}

static void
rx_stats(void)
{
    SHELL_PRINT("\t%d\t port%d :Rx bcast cntr\n", etd.rxcntr.rx_broad,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx pause cntr\n", etd.rxcntr.rx_pause,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx multi frames rcvd\n", etd.rxcntr.rx_multi,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx fcs err cntr\n", etd.rxcntr.rx_fcserr,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx allign err cntr\n", etd.rxcntr.rx_allignerr,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx runt cntr \n", etd.rxcntr.rx_runt,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx fragment cntr\n", etd.rxcntr.rx_frag,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 64b byte cntr\n", etd.rxcntr.rx_64b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 128b byte cntr\n", etd.rxcntr.rx_128b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 256b byte cntr\n", etd.rxcntr.rx_256b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 512b byte cntr\n", etd.rxcntr.rx_512b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 1024b byte cntr\n", etd.rxcntr.rx_1024b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx 1518b byte cntr\n ", etd.rxcntr.rx_1518b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx total pkt rcvd\n",
                (etd.rxcntr.rx_64b + etd.rxcntr.rx_128b + etd.rxcntr.rx_256b +
                 etd.rxcntr.rx_512b + etd.rxcntr.rx_1024b +
                 etd.rxcntr.rx_1518b), etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx maxb cntr\n", etd.rxcntr.rx_maxb,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx too long cntr\n", etd.rxcntr.rx_tool,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx byte_l\n", etd.rxcntr.rx_goodbl,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx byte_h\n", etd.rxcntr.rx_goodbh,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx overflow cntr\n", etd.rxcntr.rx_overflow,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx bad byte_l cntr\n", etd.rxcntr.rx_badbl,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d :Rx bad byte_u cntr\n", etd.rxcntr.rx_badbu,
                etd.portnum);
}

static void
tx_stats(void)
{
    SHELL_PRINT("\t%d\t port%d : Tx bcast cntr \n", etd.txcntr.tx_broad,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx pause cntr\n", etd.txcntr.tx_pause,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx multi cntr\n", etd.txcntr.tx_multi,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx under run cntr\n", etd.txcntr.tx_underrun,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 64b byte cntr\n", etd.txcntr.tx_64b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 128b byte cntr\n", etd.txcntr.tx_128b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 256b byte cntr\n", etd.txcntr.tx_256b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 512b byte cntr\n", etd.txcntr.tx_512b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 1024b byte cntr\n", etd.txcntr.tx_1024b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx 1518b byte cntr\n", etd.txcntr.tx_1518b,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx total pkt txmtd cntr\n",
                (etd.txcntr.tx_64b + etd.txcntr.tx_128b + etd.txcntr.tx_256b +
                 etd.txcntr.tx_512b + etd.txcntr.tx_1024b +
                 etd.txcntr.tx_1518b), etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx max byte cntr\n", etd.txcntr.tx_maxb,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx oversize \n", etd.txcntr.tx_oversiz,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx byte _l \n", etd.txcntr.tx_bytel,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx byte _h \n", etd.txcntr.tx_byteh,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx collision err cntr\n",
                etd.txcntr.tx_collision, etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx abort collision err cntr\n",
                etd.txcntr.tx_abortcol, etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx multi collision err cntr\n",
                etd.txcntr.tx_multicol, etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx single collision err cntr\n",
                etd.txcntr.tx_singalcol, etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx exec deffer err cntr\n",
                etd.txcntr.tx_execdefer, etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx defer err cntr\n", etd.txcntr.tx_defer,
                etd.portnum);
    SHELL_PRINT("\t%d\t port%d : Tx late collision err cntr\n",
                etd.txcntr.tx_latecol, etd.portnum);

}

static void
tx_mac_stats(void)
{
    SHELL_PRINT("\t%d\t : Tx pkt cntr\n", etd.txmac.pkt_cntr);
    SHELL_PRINT("\t%d\t : Tx byte cntr\n", etd.txmac.byte_cntr);
    SHELL_PRINT("\t%d\t : Tx mcast pkt cntr\n", etd.txmac.mcast_cntr);
    SHELL_PRINT("\t%d\t : Tx bcast pkt cntr\n", etd.txmac.bcast_cntr);
    SHELL_PRINT("\t%d\t : Tx pause frame pkt cntr\n",
                etd.txmac.pctrlframe_cntr);
    SHELL_PRINT("\t%d\t : Tx deferal pkt cntr\n", etd.txmac.deferal_cntr);
    SHELL_PRINT("\t%d\t : Tx excessive deferal pkt cntr\n",
                etd.txmac.excess_deferal_cntr);
    SHELL_PRINT("\t%d\t : Tx single collision pkt cntr\n",
                etd.txmac.single_col_cntr);
    SHELL_PRINT("\t%d\t : Tx multiple collision pkt cntr\n",
                etd.txmac.multi_col_cntr);
    SHELL_PRINT("\t%d\t : Tx late collision pkt cntr\n",
                etd.txmac.late_col_cntr);
    SHELL_PRINT("\t%d\t : Tx excessive collison pkt cntr\n",
                etd.txmac.excess_col_cntr);
    SHELL_PRINT("\t%d\t : Tx total collison pkt cntr\n",
                etd.txmac.total_col_cntr);
    SHELL_PRINT("\t%d\t : Tx drop frame cntr\n", etd.txmac.dropframe_cntr);
    SHELL_PRINT("\t%d\t : Tx jabber frame cntr\n", etd.txmac.jabberframe_cntr);
    SHELL_PRINT("\t%d\t : Tx fcs err cntr\n", etd.txmac.fcserr_cntr);
    SHELL_PRINT("\t%d\t : Tx control frame cntr\n", etd.txmac.ctrlframe_cntr);
    SHELL_PRINT("\t%d\t : Tx oversize frame cntr\n", etd.txmac.oz_frame_cntr);
    SHELL_PRINT("\t%d\t : Tx undersize frame cntr\n", etd.txmac.us_frame_cntr);
    SHELL_PRINT("\t%d\t : Tx fragments frame cntr\n",
                etd.txmac.frag_frame_cntr);

}

static void
rx_mac_stats(void)
{
    SHELL_PRINT("\t%d\t: Rx byte cntr\n", etd.rxmac.byte_cntr);
    SHELL_PRINT("\t%d\t: Rx pkt cntr\n", etd.rxmac.pkt_cntr);
    SHELL_PRINT("\t%d\t: Rx fcs err cntr\n", etd.rxmac.fcserr_cntr);
    SHELL_PRINT("\t%d\t: Rx mcast pkt cntr\n", etd.rxmac.mcast_cntr);
    SHELL_PRINT("\t%d\t: Rx bcast pkt cntr\n", etd.rxmac.bcast_cntr);
    SHELL_PRINT("\t%d\t: Rx ctrl frame cntr\n", etd.rxmac.ctrlframe_cntr);
    SHELL_PRINT("\t%d\t: Rx pause frame pkt cntr\n", etd.rxmac.pausefr_cntr);
    SHELL_PRINT("\t%d\t: Rx unknown opcode cntr\n", etd.rxmac.unknownop_cntr);
    SHELL_PRINT("\t%d\t: Rx alignment err cntr\n", etd.rxmac.allignerr_cntr);
    SHELL_PRINT("\t%d\t: Rx frame length err cntr\n", etd.rxmac.framelerr_cntr);
    SHELL_PRINT("\t%d\t: Rx code err cntr\n", etd.rxmac.codeerr_cntr);
    SHELL_PRINT("\t%d\t: Rx carrier sense err cntr\n",
                etd.rxmac.carriersenseerr_cntr);
    SHELL_PRINT("\t%d\t: Rx under sz pkt cntr\n", etd.rxmac.underszpkt_cntr);
    SHELL_PRINT("\t%d\t: Rx over sz pkt cntr\n", etd.rxmac.ozpkt_cntr);
    SHELL_PRINT("\t%d\t: Rx fragment cntr\n", etd.rxmac.fragment_cntr);
    SHELL_PRINT("\t%d\t: Rx jabber cntr\n", etd.rxmac.jabber_cntr);
    SHELL_PRINT("\t%d\t: RX drop cntr\n", etd.rxmac.rcvdrop_cntr);
}

#define INVALID_DATA 0xffffffff

u_int32_t
regread(u_int32_t phy_reg, u_int16_t portno)
{

    etd.phy_reg = phy_reg;
    etd.cmd = ATHR_PHY_RD;
    etd.portnum = portno;

    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0) {
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
        return INVALID_DATA;
    }
    return etd.data;
}

static void
athr_sw_reset()
{

    etd.cmd = ATHR_GMAC_CTRL_SW_RESET;

    if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_CTRL_IOC):");
}

static void
athr_phy_reset(unsigned int portnum)
{

    etd.cmd = ATHR_PHY_CTRL_RESET;
    etd.portnum = portnum;

    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
}

static void
reg_read_all(unsigned int portnum)
{

    etd.cmd = ATHR_PHY_RD;
    etd.portnum = portnum;

    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
}

static void
athr_en_jumboframe(int value)
{
    etd.cmd = ATHR_JUMBO_FRAME;
    etd.data = value;

    if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_CTRL_IOC):");
}

static void
athr_set_framesize(int sz)
{
    etd.cmd = ATHR_FRAME_SIZE_CTL;
    etd.data = sz;

    if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_CTRL_IOC):");
}

#if 0
#ifdef CONFIG_ATHRS_HW_ACL
static void
athr_commit_acl_rules(void)
{
    etd.cmd = ATHR_ACL_COMMIT;

    if (ioctl(s, ATHR_HW_ACL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_HW_ACL_IOC);");
}

static void
athr_flush_acl_rules(void)
{
    etd.cmd = ATHR_ACL_FLUSH;
    if (ioctl(s, ATHR_HW_ACL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_HW_ACL_IOC):");
}
#endif
#endif

static void
athr_flow_link(int portno, int val)
{
    etd.cmd = ATHR_FLOW_LINK_EN;
    etd.data = val;
    etd.portnum = portno;
    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
}

static void
athr_txflctrl(int portno, int val)
{
    if (portno == ARG_CHECK) {
        etd.data = val;
        etd.cmd = ATHR_GMAC_TX_FLOW_CTRL;

        if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_GMAC_CTRL_IOC): ");

    } else {
        etd.cmd = ATHR_PHY_TXFCTL;
        etd.portnum = portno;
        etd.data = val;
        if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_GMAC_CTRL_IOC): ");
    }
}

static void
athr_rxflctrl(int portno, int val)
{
    if (portno == ARG_CHECK) {
        etd.data = val;
        etd.cmd = ATHR_GMAC_RX_FLOW_CTRL;
        if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_GMAC_CTRL_IOC):");

    } else {
        etd.cmd = ATHR_PHY_RXFCTL;
        etd.portnum = portno;
        etd.data = val;
        if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_PHY_CTRL_IOC):");
    }
}

#ifdef CYGPKG_COMPONENT_VLAN

static void
athr_vlan_table(int value, int data)
{
    etd.cmd = ATHR_TABLE_CREATE;
    etd.portnum = value;
    etd.data = data;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static void
athr_vlan_disable(int port)
{
    etd.cmd = ATHR_VLAN_DISABLE;
    etd.portnum = port;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static void
athr_vlan_packet_flag(void)
{
    etd.cmd = ATHR_PACKET_FLAG;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static void
athr_vlan_addports(int portno, int data)
{
    etd.cmd = ATHR_VLAN_ADDPORTS;
    etd.portnum = portno;
    etd.data = data;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static void
athr_vlan_delports(void)
{
    etd.cmd = ATHR_VLAN_DELPORTS;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static int
athr_vlan_settagmode(int portno, int val)
{
    int ret = 0;

    etd.cmd = ATHR_VLAN_SETTAGMODE;
    etd.portnum = portno;
    etd.data = val;
    if ((ret = ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr)) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");

    return ret;
}

static void
athr_vlan_setdefaultid(int portno, int val)
{
    etd.cmd = ATHR_VLAN_SETDEFAULTID;
    etd.portnum = portno;
    etd.data = val;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

#if 0
static void
athr_vlan_igmp_on_off(int portno, int val)
{
    etd.cmd = ATHR_IGMP_ON_OFF;
    etd.portnum = portno;
    etd.data = val;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}

static void
athr_vlan_getstat(void)
{
    etd.cmd = ATHR_LINK_GETSTAT;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}

static void
athr_vlan_arl_del(void)
{
    etd.cmd = ATHR_ARL_DEL;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}

static void
athr_vlan_arl_add(void)
{
    etd.cmd = ATHR_ARL_ADD;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}

static void
athr_vlan_mcast_clr(void)
{
    etd.cmd = ATHR_MCAST_CLR;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}
#endif
static void
athr_vlan_arl_flush(void)
{
    etd.cmd = ATHR_ARL_FLUSH;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

static void
athr_vlan_vhyfi_plc_port(void)
{
    etd.cmd = ATHR_VHYFI_PLC_PORT;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

#if 0
static void
athr_vlan_reset(void)
{
    etd.cmd = ATHR_VLAN_RESET;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
    close(s);
}

#endif

#endif /* CYGPKG_COMPONENT_VLAN */

static void
athr_set_mib(int val)
{
    etd.cmd = ATHR_PHY_MIB;
    etd.portnum = ARG_CHECK;
    etd.data = val;
    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
}

static void
athr_disp_stats(int portno)
{
    if (portno == ARG_CHECK) {
        etd.cmd = ATHR_GMAC_STATS;
        if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0) {
            perror("ioctl(ATHR_GMAC_CTRL_IOC)");
        } else {
            rx_mac_stats();
            tx_mac_stats();
        }

    } else {
        etd.cmd = ATHR_PHY_STATS;
        etd.portnum = portno;
        if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_PHY_CTRL_IOC):");
        else {
            rx_stats();
            tx_stats();
        }
    }
}

static void
athr_dma_check(int val)
{
    etd.cmd = ATHR_GMAC_DMA_CHECK;
    etd.data = val;
    if (ioctl(s, ATHR_GMAC_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_CTRL_IOC):");
}

#ifdef CONFIG_ATHRS_QOS
static void
athr_set_qos(int val)
{
    etd.cmd = ATHR_QOS_ETH_SOFT_CLASS;
    etd.data = val;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}

static void
athr_set_port_pri(int portno, int val)
{
    etd.cmd = ATHR_QOS_ETH_PORT;
    etd.portnum = portno;
    etd.data = val;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}

static void
athr_ip_qos(int tos, int val)
{
    etd.cmd = ATHR_QOS_ETH_IP;
    etd.data = val;
    etd.tos = tos;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}

#ifdef CYGPKG_COMPONENT_VLAN

static void
athr_vlan_qos(int vlan_id, int val)
{
    etd.cmd = ATHR_QOS_ETH_VLAN;
    etd.data = val;
    etd.vlanid = vlan_id;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}

#endif /* CYGPKG_COMPONENT_VLAN */

void
token_convert(char *mac_addr)
{
    char *token = strtok(mac_addr, ":");

    int l = 0;

    while (token) {

        etd.mac_addr[l] = simple_strtoul(token, NULL, 16);

        token = strtok(NULL, ":");

        l++;
    }
}

static void
athr_mac_qos(int portno, int val, char *mac_addr)
{
    etd.cmd = ATHR_QOS_ETH_DA;
    etd.data = val;
    etd.portnum = portno;

    token_convert(mac_addr);

    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}
#endif

#ifdef CYGPKG_COMPONENT_VLAN
static int
athr_vlan_enable(int port)
{
    int ret;
    etd.cmd = ATHR_VLAN_ENABLE;
    etd.portnum = port;

    if ((ret = ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr)) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");

    return ret;
}

static void
athr_vlan_trunkmode(int port)
{
    etd.cmd = ATHR_VLAN_TRUNK_MODE;
    etd.portnum = port;
    if (ioctl(s, ATHR_VLAN_IGMP_IOC, &ifr) < 0)
        perror("ioctl(ATHR_VLAN_IGMP_IOC):");
}

void
athr_vlan_enable_all(void)
{
    athrs27_reg_write(0x104, 0x4204);
    athrs27_reg_write(0x108, 0x00001);
    athrs27_reg_write(0x10c, 0xc07e0000);
    athrs27_reg_write(0x204, 0x4104);
    athrs27_reg_write(0x208, 0x20001);
    athrs27_reg_write(0x20c, 0xc07d0000);
    athrs27_reg_write(0x304, 0x4104);
    athrs27_reg_write(0x308, 0x30001);
    athrs27_reg_write(0x30c, 0xc07b0000);
    athrs27_reg_write(0x404, 0x4104);
    athrs27_reg_write(0x408, 0x30001);  //1st 3 bytes : vlan ID
    athrs27_reg_write(0x40c, 0xc0770000);

    athrs27_reg_write(0x44, 0x80f);
    athrs27_reg_write(0x40, 0x3000a);
    while (athrs27_reg_read(0x40) & (1 << 3)) {
        cyg_thread_delay(5);
    }

    athrs27_reg_write(0x44, 0x80f);
    athrs27_reg_write(0x40, 0x2000a);
    while (athrs27_reg_read(0x40) & (1 << 3)) {
        cyg_thread_delay(5);
    }
}

#endif /* CYGPKG_COMPONENT_VLAN */

static void
athr_port_st(int portno)
{
#define MAX_SIZ 20
    char p_duplex[][MAX_SIZ] = { "Half", "Full" };
    char p_speed[][MAX_SIZ] = { "10Mbps", "100Mbps" };
    char p_link[][MAX_SIZ] = { "Down", "up" };

    etd.cmd = ATHR_PORT_STATS;
    etd.portnum = portno;

    if (etd.portnum > MAX_PORT) {
        SHELL_PRINT("port usage <0-4>");
        return;
    }
    if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0) {
        perror("ioctl(ATHR_PHY_CTRL_IOC):");
    } else {
        SHELL_PRINT("port %d link %s speed %s duplex %s\n", portno,
                    p_link[etd.phy_st.link], p_speed[etd.phy_st.speed],
                    p_duplex[etd.phy_st.duplex]);
    }
}

#ifdef CONFIG_ATHRS_QOS
static void
athr_process_egress(int portno, int val)
{
    etd.cmd = ATHR_QOS_PORT_ELIMIT;
    etd.data = val;
    etd.portnum = portno;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}

static void
athr_process_igress(int portno, int val)
{
    etd.cmd = ATHR_QOS_PORT_ILIMIT;
    etd.data = val;
    etd.portnum = portno;
    if (ioctl(s, ATHR_GMAC_QOS_CTRL_IOC, &ifr) < 0)
        perror("ioctl(ATHR_GMAC_QOS_CTRL_IOC):");
}
#endif

static void
regwrite(u_int32_t phy_reg, u_int32_t val, u_int16_t portno)
{

    etd.data = val;
    etd.phy_reg = phy_reg;
    etd.portnum = portno;

    if (opt_force) {
        etd.duplex = duplex;
        etd.cmd = ATHR_PHY_FORCE;

        if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_PHY_CTRL_IOC):");

        opt_force = 0;          /* Forcefully changing the port Duplex mode by enabling  "-f " */

    } else {

        etd.cmd = ATHR_PHY_WR;
        if (ioctl(s, ATHR_PHY_CTRL_IOC, &ifr) < 0)
            perror("ioctl(ATHR_PHY_CTRL_IOC):");
    }
}

static void
usage(void)
{
    fprintf(stderr, "usage: %s [--reg] [-p portnum] [regaddr] [data]\n",
            progname);
    fprintf(stderr, "usage: %s [-f]  -p portnum =10/100/0 [-d duplex]\n",
            progname);
    fprintf(stderr, "usage: %s [-i ifname][-x]\n", progname);
    fprintf(stderr, "usage: %s [-i ifname][-c]\n", progname);
    fprintf(stderr, "usage: %s [-i ifname][-s value]\n", progname);
    fprintf(stderr, "usage: %s [-i ifname][-j 0|1]\n", progname);
    fprintf(stderr, "usage: %s [--txfctl] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--txfctl] [-i ifname] -v [0|1] -p <portno>\n",
            progname);
    fprintf(stderr, "usage: %s [--rxfctl] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--rxfctl] [-i ifname] -v [0|1] -p <portno>\n",
            progname);
    fprintf(stderr, "usage: %s [--dma] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--f_link] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--mib] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--stats] [-i ifname]\n", progname);
    fprintf(stderr, "usage: %s [--stats] [-i ifname] -p <portno>\n", progname);
    fprintf(stderr, "usage: %s [--qos] [-i ifname] -v [0|1]\n", progname);
    fprintf(stderr, "usage: %s [--ipqos] [-i ifname] -t <tos> -v <val>\n",
            progname);
#ifdef CYGPKG_COMPONENT_VLAN
    fprintf(stderr, "usage: %s [--vqos] [-i ifname] -l <vlanid> -v <val>\n",
            progname);
#endif
    fprintf(stderr,
            "usage: %s [--mqos [-i ifname] -v <val> -p <portnum> -m <macaddr>\n",
            progname);
    fprintf(stderr, "usage: %s [--p_st] [-i ifname] -p <portno>\n", progname);
#ifdef CYGPKG_COMPONENT_VLAN
    fprintf(stderr, "usage: %s [--vlanen] -p <portnum> \n", progname);
    fprintf(stderr, "usage: %s [--vlandis] -p <portnum> \n", progname);
    fprintf(stderr, "usage: %s [--vlansetVID] -p <portnum> -v  <VID> \n",
            progname);
    fprintf(stderr, "usage: %s [--vlantable]   -v <VID> -p <portnumbers> \n",
            progname);
    fprintf(stderr, "usage: %s [--vlansetegmod]   -p <portnum> -m <mode> \n",
            progname);
#endif /* CYGPKG_COMPONENT_VLAN */
    fprintf(stderr, "usage: %s [--igrl] [-i ifname] -p <portno> -v <val>\n",
            progname);
    fprintf(stderr, "usage: %s [--egrl] [-i ifname] -p <portno> -v <val>\n",
            progname);
    fprintf(stderr, "usage: %s [-i ifname][-s value]\n", progname);
    fprintf(stderr, "usage: %s [-i ifname][-j 0|1]\n", progname);
}

int
ethreg_start(int argc, char *argv[])
{
    char *argu[10];
    char **args = argu;
    const char *ifname = "eth0";
    int c, portnum = ARG_CHECK, cmd = 0, value = -1, argc_tmp = argc;
    int optionindex = 0;
    int vlanid = 0;
    char *mac = NULL;
    int tos = -1;
    int var, index, data;
    char *opt = "xfhci:d:s:j:v:t:p:m:l:";

    argu[0] = "ethreg";
    for (var = 0; var < argc; var++) {
        argu[var + 1] = argv[var];
    }
    argc = argc + 1;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        return s;
    }
    opt_force = 0;
    progname = args[0];

    struct option long_options[] = {
        {"f_link", no_argument, 0, ATHR_FLOW_LINK_EN},
        {"txfctl", no_argument, 0, ATHR_PHY_TXFCTL},
        {"rxfctl", no_argument, 0, ATHR_PHY_RXFCTL},
        {"stats", no_argument, 0, ATHR_GMAC_STATS},
        {"mib", no_argument, 0, ATHR_PHY_MIB},
        {"dma", no_argument, 0, ATHR_GMAC_DMA_CHECK},
        {"reg", no_argument, 0, ATHR_REG_RW},

#ifdef CONFIG_ATHRS_QOS
        {"qos", no_argument, 0, ATHR_QOS_ETH_SOFT_CLASS},
        {"ppri", no_argument, 0, ATHR_QOS_ETH_PORT},
        {"ipqos", no_argument, 0, ATHR_QOS_ETH_IP},
        {"vqos", no_argument, 0, ATHR_QOS_ETH_VLAN},
        {"mqos", no_argument, 0, ATHR_QOS_ETH_DA},
        {"igrl", no_argument, 0, ATHR_QOS_PORT_ELIMIT},
        {"egrl", no_argument, 0, ATHR_QOS_PORT_ILIMIT},
#endif
        {"p_st", no_argument, 0, ATHR_PORT_STATS},
#ifdef CYGPKG_COMPONENT_VLAN
        {"vlanen", no_argument, 0, ATHR_VLAN_ENABLE},
        {"vlandis", no_argument, 0, ATHR_VLAN_DISABLE},
        {"vlanaddp", no_argument, 0, ATHR_VLAN_ADDPORTS},
        {"vlandelp", no_argument, 0, ATHR_VLAN_DELPORTS},
        {"vlanpf", no_argument, 0, ATHR_PACKET_FLAG},
        {"vlansetVID", no_argument, 0, ATHR_VLAN_SETDEFAULTID},
        {"vlanigof", no_argument, 0, ATHR_IGMP_ON_OFF},
        {"vlanlgst", no_argument, 0, ATHR_LINK_GETSTAT},
        {"vlanarlad", no_argument, 0, ATHR_ARL_ADD},
        {"vlanarldel", no_argument, 0, ATHR_ARL_DEL},
        {"vlanmcastc", no_argument, 0, ATHR_MCAST_CLR},
        {"vlanvlanres", no_argument, 0, ATHR_VLAN_RESET},
        {"vlanvhfi", no_argument, 0, ATHR_VHYFI_PLC_PORT},
        {"vlanarfl", no_argument, 0, ATHR_ARL_FLUSH},
        {"vlansetegmod", no_argument, 0, ATHR_VLAN_SETTAGMODE},
        {"vlantable", no_argument, 0, ATHR_TABLE_CREATE},
        {"vlanall", no_argument, 0, ATHR_VLAN_ENABLE_ALL},
#endif /* CYGPKG_COMPONENT_VLAN */
        {0, 0, 0, 0}
    };

    init_getopt();
    while ((c = getopt_long(argc, args, opt, long_options, &optionindex)) != -1) {
        switch (c) {
        case ATHR_FLOW_LINK_EN:
            cmd = ATHR_FLOW_LINK_EN;
            break;
        case ATHR_PHY_TXFCTL:
            cmd = ATHR_PHY_TXFCTL;
            break;
        case ATHR_PHY_RXFCTL:
            cmd = ATHR_PHY_RXFCTL;
            break;
        case ATHR_PHY_MIB:
            cmd = ATHR_PHY_MIB;
            break;
        case ATHR_GMAC_STATS:
            cmd = ATHR_GMAC_STATS;
            break;
        case ATHR_GMAC_DMA_CHECK:
            cmd = ATHR_GMAC_DMA_CHECK;
            break;
        case ATHR_GMAC_CTRL_SW_RESET:
            cmd = ATHR_GMAC_CTRL_SW_RESET;
            break;
        case ATHR_PHY_CTRL_RESET:
            cmd = ATHR_PHY_CTRL_RESET;
            break;
        case ATHR_PHY_CTRL_REG_RW:
            cmd = ATHR_PHY_CTRL_REG_RW;
            break;
        case ATHR_REG_RW:
            cmd = ATHR_REG_RW;
            break;
//#ifdef CONFIG_ATHRS_HW_ACL
        case ATHR_QOS_ETH_SOFT_CLASS:
            cmd = ATHR_QOS_ETH_SOFT_CLASS;
            break;
        case ATHR_QOS_ETH_PORT:
            cmd = ATHR_QOS_ETH_PORT;
            break;
#ifdef CYGPKG_COMPONENT_VLAN
        case ATHR_QOS_ETH_VLAN:
            cmd = ATHR_QOS_ETH_VLAN;
            break;
#endif
        case ATHR_QOS_ETH_IP:
            cmd = ATHR_QOS_ETH_IP;
            break;
        case ATHR_QOS_ETH_DA:
            cmd = ATHR_QOS_ETH_DA;
            break;
        case ATHR_PORT_STATS:
            cmd = ATHR_PORT_STATS;
            break;
#ifdef CYGPKG_COMPONENT_VLAN
        case ATHR_VLAN_ENABLE:
            cmd = ATHR_VLAN_ENABLE;
            break;
        case ATHR_VLAN_ENABLE_ALL:
            cmd = ATHR_VLAN_ENABLE_ALL;
            break;
        case ATHR_TABLE_CREATE:
            cmd = ATHR_TABLE_CREATE;
            break;
        case ATHR_PACKET_FLAG:
            cmd = ATHR_PACKET_FLAG;
            break;
        case ATHR_VLAN_ADDPORTS:
            cmd = ATHR_VLAN_ADDPORTS;
            break;
        case ATHR_VLAN_DELPORTS:
            cmd = ATHR_VLAN_DELPORTS;
            break;
        case ATHR_VLAN_SETTAGMODE:
            cmd = ATHR_VLAN_SETTAGMODE;
            break;
        case ATHR_VLAN_SETDEFAULTID:
            cmd = ATHR_VLAN_SETDEFAULTID;
            break;
        case ATHR_VLAN_DISABLE:
            cmd = ATHR_VLAN_DISABLE;
            break;
        case ATHR_IGMP_ON_OFF:
            cmd = ATHR_IGMP_ON_OFF;
            break;
#endif /* CYGPKG_COMPONENT_VLAN */
        case ATHR_LINK_GETSTAT:
            cmd = ATHR_LINK_GETSTAT;
            break;
        case ATHR_ARL_ADD:
            cmd = ATHR_ARL_ADD;
            break;
        case ATHR_ARL_DEL:
            cmd = ATHR_ARL_DEL;
            break;
        case ATHR_MCAST_CLR:
            cmd = ATHR_MCAST_CLR;
            break;
#ifdef CYGPKG_COMPONENT_VLAN
        case ATHR_VLAN_RESET:
            cmd = ATHR_VLAN_RESET;
            break;
#endif
        case ATHR_ARL_FLUSH:
            cmd = ATHR_ARL_FLUSH;
            break;
        case ATHR_VHYFI_PLC_PORT:
            cmd = ATHR_VHYFI_PLC_PORT;
            break;
        case ATHR_QOS_PORT_ELIMIT:
            cmd = ATHR_QOS_PORT_ELIMIT;
            break;
        case ATHR_QOS_PORT_ILIMIT:
            cmd = ATHR_QOS_PORT_ILIMIT;
            break;
//#endif
        case 'm':
            //    mac = optarg;
            value = strtoul(optarg, 0, 0);
            break;
        case 'v':
            value = strtoul(optarg, 0, 0);
            break;
        case 'i':
            ifname = optarg;
            break;
        case 't':
            tos = strtoul(optarg, 0, 0);
            break;
        case 'p':
#ifdef CYGPKG_COMPONENT_VLAN
            if (cmd == ATHR_TABLE_CREATE) {
                data = 1;
                for (index = optind; index <= argc; index++) {
                    portnum = strtoul(optarg, 0, 0);
                    data |= (1 << (portnum + 1));
                    optarg = args[index];
                }
            } else
#endif
                portnum = strtoul(optarg, 0, 0);
            break;
        case 'f':
            opt_force = 1;
            break;
        case 'd':
            duplex = strtoul(optarg, 0, 0);
            break;
#ifdef CONFIG_ATHRS_HW_ACL
        case 'c':
            cmd = ATHR_ACL_COMMIT;
            break;
        case 'x':
            cmd = ATHR_ACL_FLUSH;
            break;
#endif
        case 's':
            cmd = ATHR_FRAME_SIZE_CTL;
            value = strtoul(optarg, 0, 0);
            break;
        case 'j':
            cmd = ATHR_JUMBO_FRAME;
            value = strtoul(optarg, 0, 0);
            break;
        case 'l':
            vlanid = strtoul(optarg, 0, 0);
            break;
        case 'h':

            usage();
            break;
        default:

            usage();
         /*NOTREACHED*/}

    }

    argc -= optind;
    args += optind;

    strncpy(etd.ad_name, ifname, sizeof(etd.ad_name) - 1);
    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);

    ifr.ifr_data = (void *)&etd;

    if (cmd == ATHR_REG_RW) {
        value = do_ethreg(argc, args);
	if ( value < 0 ) {
	SHELL_PRINT("Invalid arguments \n");
	}
        goto success;
    }
#ifdef CONFIG_ATHRS_HW_ACL
    if (cmd == ATHR_ACL_COMMIT) {
        athr_commit_acl_rules();
        goto success;
    } else if (cmd == ATHR_ACL_FLUSH) {
        athr_flush_acl_rules();
        goto success;
    } else
#endif
    if (cmd == ATHR_FRAME_SIZE_CTL) {
        if (value == -1) {
            SHELL_PRINT("usage:ethreg -i <if_name> -s <val>\n");
            goto invalid_arg;
        } else {
            athr_set_framesize(value);
            goto success;
        }
    } else if (cmd == ATHR_JUMBO_FRAME) {
        if (value == -1) {
            SHELL_PRINT("usage: ethreg -i <if_name> -j <0|1>\n");
            goto invalid_arg;
        } else {
            athr_en_jumboframe(value);
            goto success;
        }
    } else if (cmd == ATHR_FLOW_LINK_EN) {
        if (value == -1 || portnum == ARG_CHECK) {
            SHELL_PRINT
                ("usage: ethreg --f_link -i <ifname> -p <portnum> -v 1\n");
            goto invalid_arg;
        } else {
            athr_flow_link(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_PHY_RXFCTL) {
        if (value == -1) {
            SHELL_PRINT
                ("usage: ethreg --rxfctl -i <ifname> -p <portnum> -v [0|1]\n");
            SHELL_PRINT("usage: ethreg --rxfctl -i <ifname> -v [0|1]\n");
            goto invalid_arg;
        } else {
            athr_rxflctrl(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_PHY_TXFCTL) {
        if (value == -1) {
            SHELL_PRINT
                ("usage: ethreg --txfctl -i <ifname> -p <portnum> -v [0|1]\n");
            SHELL_PRINT("usage: ethreg --txfctl -i <ifname> -v [0|1]\n");
            goto invalid_arg;
        } else {

            athr_txflctrl(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_PHY_MIB) {
        if (value == -1) {
            SHELL_PRINT("usage: ethreg --mib -i <ifname> -v 1\n");
            goto invalid_arg;
        } else {
            athr_set_mib(value);
            goto success;
        }
    } else if (cmd == ATHR_GMAC_STATS) {
        athr_disp_stats(portnum);
        goto success;
    } else if (cmd == ATHR_GMAC_DMA_CHECK) {
        if (value == -1) {
            SHELL_PRINT("usage: ethreg --dma -i <ifname> -v [0|1]\n");
            goto invalid_arg;
        } else {
            athr_dma_check(value);
            goto success;
        }
    }
#ifdef CONFIG_ATHRS_QOS
    else if (cmd == ATHR_QOS_ETH_SOFT_CLASS) {
        if (value == -1) {
            SHELL_PRINT("usage: ethreg --qos -i <ifname> -v [0|1]\n");
            goto invalid_arg;
        } else {
            athr_set_qos(value);
            goto success;
        }
    } else if (cmd == ATHR_QOS_ETH_PORT) {
        if (value == -1) {
            SHELL_PRINT
                ("usage: ethreg --ppri -i <ifname> -p <portno> -v <val>\n");
            goto invalid_arg;
        } else {
            athr_set_port_pri(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_QOS_ETH_IP) {
        if (tos == -1 || value == -1) {
            SHELL_PRINT
                ("usage: ethreg --ipqos -i <ifname> -v <val> -t <tos>\n");
            goto invalid_arg;
        } else {
            athr_ip_qos(tos, value);
            goto success;
        }
#ifdef CYGPKG_COMPONENT_VLAN
    } else if (cmd == ATHR_QOS_ETH_VLAN) {
        if (value == -1 || vlanid == -1) {
            SHELL_PRINT
                ("usage: ethreg --vqos -i <ifname> -v <val> -l <vlanid>\n");
            goto invalid_arg;
        } else {
            athr_vlan_qos(vlanid, value);
            goto success;

        }
#endif
    } else if (cmd == ATHR_QOS_ETH_DA) {
        if (portnum == ARG_CHECK || value == -1 || mac == NULL) {
            SHELL_PRINT
                ("usage: ethreg --mqos -i <ifname> -v <val> -p <portnum> -m <macaddr>\n");
            goto invalid_arg;
        } else {
            athr_mac_qos(portnum, value, mac);
            goto success;
        }
#endif
    } else if (cmd == ATHR_PORT_STATS) {
        if (portnum == ARG_CHECK) {
            SHELL_PRINT("usage: ethreg --port_st -i <ifname> -p <portno>\n");
            goto invalid_arg;
        } else {
            athr_port_st(portnum);
            goto success;
        }
#ifdef CYGPKG_COMPONENT_VLAN
    } else if (cmd == ATHR_TABLE_CREATE) {
        if (value == -1 || portnum == ARG_CHECK) {
            SHELL_PRINT
                ("usage: ethreg --vlantable -v <value> -p <portnumbers> \n");
            goto invalid_arg;
        } else {

            athr_vlan_table(value, data);
            goto success;
        }
    } else if (cmd == ATHR_VLAN_ENABLE) {
        if (portnum == ARG_CHECK) {
            SHELL_PRINT("usage: ethreg --vlanen -p <portnumber> \n");
            goto invalid_arg;
        }
        athr_vlan_enable(portnum + 1);
        goto success;
    } else if (cmd == ATHR_VLAN_ENABLE_ALL) {
        athr_vlan_enable_all();
        goto success;
    } else if (cmd == ATHR_VLAN_DISABLE) {
        if (portnum == ARG_CHECK) {
            SHELL_PRINT("usage: ethreg --vlandis -p <portnumber> \n");
            goto invalid_arg;
        }
        athr_vlan_disable(portnum + 1);

        goto success;
    } else if (cmd == ATHR_PACKET_FLAG) {
        athr_vlan_packet_flag();
        goto success;
    } else if (cmd == ATHR_VLAN_ADDPORTS) {
        athr_vlan_addports(portnum, value);
        goto success;
    } else if (cmd == ATHR_VLAN_DELPORTS) {
        athr_vlan_delports();
        goto success;
    } else if (cmd == ATHR_VLAN_SETTAGMODE) {
        if (portnum == ARG_CHECK || value == -1) {
            SHELL_PRINT
                ("usage: ethreg --vlansetegmod -p <portnum> -m <mode>\n");
            goto invalid_arg;
        } else {
            athr_vlan_settagmode(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_VLAN_SETDEFAULTID) {
        if (portnum == ARG_CHECK || value == -1) {
            SHELL_PRINT("usage: ethreg --vlansetVID -p <portnum> -v <id>\n");
            goto invalid_arg;
        } else {
            athr_vlan_setdefaultid(portnum + 1, value);
            goto success;
        }
        athr_vlan_vhyfi_plc_port();
        goto success;
    } else if (cmd == ATHR_ARL_FLUSH) {
        athr_vlan_arl_flush();
        goto success;
#endif

#ifdef CONFIG_ATHRS_QOS
    } else if (cmd == ATHR_QOS_PORT_ELIMIT) {
        if (portnum == ARG_CHECK || value == -1) {
            SHELL_PRINT
                ("usage: ethreg --egrl -i <ifname> -p <portnum> -v <val>\n");
            goto invalid_arg;
        } else {
            athr_process_egress(portnum, value);
            goto success;
        }
    } else if (cmd == ATHR_QOS_PORT_ILIMIT) {
        if (portnum == ARG_CHECK || value == -1) {
            SHELL_PRINT
                ("usage: ethreg --igrl -i <ifname> -p <portnum> -v <val>\n");
            goto invalid_arg;
        } else {
            athr_process_igress(portnum, value);
            goto success;
        }
#endif

    } else if (cmd == ATHR_GMAC_CTRL_SW_RESET) {
        athr_sw_reset();
        goto success;
    }

    else if (cmd == ATHR_PHY_CTRL_RESET) {
        if (portnum != ARG_CHECK)
            athr_phy_reset(portnum);
        goto success;
    }

    else if (cmd == ATHR_PHY_CTRL_REG_RW) {
        u_int32_t off, data;
        if (portnum != ARG_CHECK && portnum <= MAX_PORT && portnum > 0) {
            if (argc_tmp == 3) {
                reg_read_all(portnum);
            } else if (argc_tmp == 4) {
                off = (u_int) simple_strtoul(argu[4], 0, 16);
                data = regread(off, portnum);
                SHELL_PRINT("Read Reg: 0x%08x = 0x%08x\n", off, data);
            } else if (argc_tmp == 5) {
                off = (u_int) simple_strtoul(argu[4], 0, 16);
                data = (u_int) simple_strtoul(argu[5], 0, 16);
                SHELL_PRINT
                    ("Write Reg: 0x%08x: Oldval = 0x%08x Newval = 0x%08x\n",
                     (off), regread(off, portnum), data);
                regwrite(off, data, portnum);
            }
        }

        goto success;
    }

    for (; argc > 0; argc--, args++) {
        u_int32_t off;
        u_int32_t val, oval;
        char *cp;

        cp = strchr(args[0], '=');
        if (cp != NULL)
            *cp = '\0';

        off = (u_int) strtoul(args[0], 0, 0);

        if (off == 0 && errno == EINVAL)
            SHELL_PRINT("error");

        if (cp == NULL) {
            val = regread(off, portnum);
            SHELL_PRINT("Read Reg: 0x%08x = 0x%08x\n", off, val);
        } else {
            val = (u_int32_t) strtoul(cp + 1, 0, 0);
            if (val == 0) {
                SHELL_PRINT("error!! can't set speed to 0\n");
            } else {
                oval = regread(off, portnum);
                if (opt_force == 0) {
                    SHELL_PRINT
                        ("Write Reg: 0x%08x: Oldval = 0x%08x Newval = 0x%08x\n",
                         off, oval, val);
                    regwrite(off, val, portnum);
                }
                if (opt_force == 1 && portnum == ARG_CHECK) {
                    fprintf(stderr,
                            "usage: %s [-f]  -p portnum =10/100/0 [-d duplex]\n",
                            progname);
                    goto invalid_arg;
                } else {

                    regwrite(off, val, portnum);
                }
            }
        }
    }
success:
    close(s);
    return 0;

invalid_arg:
    close(s);
    return -1;
}

#ifdef CYGPKG_COMPONENT_VLAN
int
vlan_setid(int portnum, int mode, int vlan_id)
{
    int data = 1;
    int data1 = 0xb;            /* For deleting an entry in vlan_table */
    int i = 0;
    int ret;

    strncpy(etd.ad_name, "eth1", sizeof(etd.ad_name) - 1);
    strncpy(ifr.ifr_name, "eth1", IFNAMSIZ - 1);

    ifr.ifr_data = (void *)&etd;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket:");
        return s;
    }

    if (portnum < 0 || portnum > 3) {
        close(s);
        return -EINVAL;
    }
    if (mode == ACCESS_MODE) {
        athrs27_reg_write(0x104, 0x4004);
        athrs27_reg_write(0x108, 0x00001);
        athrs27_reg_write(0x10c, 0x407e0000);
        ret = athr_vlan_enable(portnum + 1);
        if (ret != 0) {
            close(s);
            return ret;
        } else {
            athr_vlan_settagmode(portnum + 1, 1);
            athr_vlan_setdefaultid(portnum + 1, vlan_id);
            for (i = 0; i < VLAN_TABLE_SIZE; i++) {
                if ((table[i].vlanid == 0) && (table[i].vlanid != vlan_id)) {
                    table[i].vlanid = vlan_id;
                    table[i].portno = portnum;
                    data |= 1 << (portnum + 1);
                    athr_vlan_table(vlan_id, data);
                    if ((table[i + 1].vlanid) == 0) {
                        break;
                    }
                } else if (table[i].vlanid == vlan_id) {
                    data1 |= (vlan_id << 16);
                    athrs27_reg_write(0x40, data1);
                    data |= (1 << (table[i].portno + 1));
                    data |= (1 << (portnum + 1));
                    athr_vlan_table(vlan_id, data);
                    if ((table[i + 1].vlanid) == 0) {
                        break;
                    }
                }
            }
        }
    } else if (mode == TRUNK_MODE) {

        athrs27_reg_write(0x104, 0x4004);
        athrs27_reg_write(0x108, 0x00001);
        athrs27_reg_write(0x10c, 0x407e0000);
        ret = athr_vlan_settagmode(portnum + 1, 2);
        if (ret != 0) {
            close(s);
            return ret;
        } else {

            athr_vlan_trunkmode(portnum + 1);
            data |= (1 << (portnum + 1));
            athr_vlan_table(vlan_id, data);
        }
    }
    close(s);
    return 0;
}

int
vlan_dis(int portnum)
{

    strncpy(etd.ad_name, "eth1", sizeof(etd.ad_name) - 1);
    strncpy(ifr.ifr_name, "eth1", IFNAMSIZ - 1);

    ifr.ifr_data = (void *)&etd;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket:");
        return s;
    }

    if (portnum < 0 || portnum > 3) {
        close(s);
        return -EINVAL;
    } else {
        athr_vlan_disable(portnum + 1);
        athr_vlan_settagmode(portnum + 1, 0);

    }
    close(s);
    return 0;
}

int
vlanset(int vlanid)
{
    int data = 0;
    athrs27_reg_write(0x104, 0x4004);
    athrs27_reg_write(0x108, 0x00001);
    athrs27_reg_write(0x10c, 0xc07e0000);
    athrs27_reg_write(0x304, 0x4104);
    athrs27_reg_write(0x308, 0x30001);
    athrs27_reg_write(0x30c, 0xc07b0000);
    athrs27_reg_write(0x404, 0x4104);
    athrs27_reg_write(0x408, 0x30001);  //1st 3 bytes : vlan ID
    athrs27_reg_write(0x40c, 0xc0770000);

    athrs27_reg_write(0x44, 0x80d);
    athrs27_reg_write(0x40, 0x3000a);
    while (athrs27_reg_read(0x40) & (1 << 3)) {
        cyg_thread_delay(5);
    }
    data |= (vlanid << 16);
    athrs27_reg_write(0x204, 0x4104);
    athrs27_reg_write(0x208, data);
    athrs27_reg_write(0x20c, 0xc07d0000);
    athrs27_reg_write(0x44, 0x803);
    data |= 0xa;
    athrs27_reg_write(0x40, data);
    while (athrs27_reg_read(0x40) & (1 << 3)) {
        cyg_thread_delay(5);
    }

    return 0;
}
#endif
