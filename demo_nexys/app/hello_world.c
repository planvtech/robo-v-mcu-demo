#include <app/include/hello_world.h>
#include "hal/include/hal_udma_i2cm_reg_defs.h"
#include "drivers/include/udma_uart_driver.h"
#include "hal/include/hal_apb_soc_ctrl_regs.h"
#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include "libs/cli/include/cli.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/unistd.h>

void rx_byte( int c )
{
    static const char _backspace[] = "\b \b";
    int x;
    static int last_was_cr;

    /* handle CR/LF
    * and CR
    * and LF
    * As a terminator
    */
    if( last_was_cr && (c =='\n') ){
        /* make CR/LF look like a single \n */
        last_was_cr = 0;
        return;
    }

    if( c == '\r' ){
        /* map to newline */
        c = '\n';
        last_was_cr = 1;
    } else {
        last_was_cr = 0;
    }

    /* we commonly need the len so get it always */
    /* todo: Future, would be nice to have up/dn arrow support cmd history */
    /* Todo: Would be nice if we had fancy editing of the command line */

    x = strlen( CLI_common.cmdline );
    switch( c ){
    case 0x03: /* Control-C */
        /* Acknowedge the key, also see the Simualted ^C in command dispatch  */
        CLI_printf(" **^C**\n");
        memset( (void *)(&(CLI_common.cmdline[0])), 0, sizeof(CLI_common.cmdline) );
        CLI_cmd_stack_clear();
        break;
    case 0x1b: /* ESCAPE key erases all bytes */
      /* note: this is different then ESC as a prefix to a CSI sequence (arrow key)
       * See arrow key decoding in CLI_getkey() code
       */
        if( x == 0 ){
            /* beep */
            CLI_beep();
            break;
        }
        /* back over */
        while( x ){
            CLI_puts_no_nl(_backspace);
            x--;
        }
        memset( CLI_common.cmdline, 0, sizeof(CLI_common.cmdline) );
        break;
    case '\b': /* backspace */
    case 0x7F: /* delete */
        if( x == 0 ){
            CLI_beep();
            break;
        }
        CLI_puts_no_nl(_backspace);
        x--;
        CLI_common.cmdline[x] = 0;
        break;
    case '\n':
        CLI_putc('\n');
        break;
    case '\t':
        /* future: add command completion */
        /* treat as space */
        c = ' ';
        /* fallthrough */
    default:
        /* if NOT in ASCII range (function keys, arrow keys, etc)*/
        if( (c < 0x20) || (c >= 0x7f) ){
            CLI_beep();
            break;
        }
        if( x >= (sizeof(CLI_common.cmdline)-1) ){
	    /* too much */
	    CLI_beep();
        } else {
   	    /* Append */
            CLI_common.cmdline[x+0] = c;
            CLI_common.cmdline[x+1] = 0;
            /* echo */
            CLI_putc(c);
        }
        break;
    }
}

void get_string()
{
    int k;

    memset( (void *)(&CLI_common.cmdline[0]), 0, sizeof(CLI_common.cmdline) );

	while(1) {
		k = CLI_getkey( 10*1000 );
		if( k == EOF ){
			continue;
		}
		rx_byte( k );

		if (strlen( CLI_common.cmdline ) == 0)
			break;

		if(k == '\r' || k == '\n')
			break;
	}
}

void hello_world( void *pParameter )
{
	(void)pParameter;

    vTaskDelay(100);
    CLI_common.timestamps = 0;

	//udma_uart_open(1, 115200);
	//udma_uart_open(0, 115200);

	while (1) {
		CLI_printf("Hello World!\r\n");
		CLI_printf("I am the demo program for the robo-v-mcu project\r\n");
		CLI_printf("What's your name?\r\n");
		get_string();
		while (strlen( CLI_common.cmdline ) == 0) {
			CLI_printf("Sorry, I didn't understand - could you please repeat?\r\n");
			get_string();
		}
		CLI_printf("Nice to meet you, %s!\r\n", CLI_common.cmdline);
	}
}
