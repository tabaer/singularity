/* 
 * Copyright (c) 2015-2016, Gregory M. Kurtzer. All rights reserved.
 * 
 * “Singularity” Copyright (c) 2016, The Regents of the University of California,
 * through Lawrence Berkeley National Laboratory (subject to receipt of any
 * required approvals from the U.S. Dept. of Energy).  All rights reserved.
 * 
 * This software is licensed under a customized 3-clause BSD license.  Please
 * consult LICENSE file distributed with the sources of this project regarding
 * your rights to use or distribute this software.
 * 
 * NOTICE.  This Software was developed under funding from the U.S. Department of
 * Energy and the U.S. Government consequently retains certain rights. As such,
 * the U.S. Government has been granted for itself and others acting on its
 * behalf a paid-up, nonexclusive, irrevocable, worldwide license in the Software
 * to reproduce, distribute copies to the public, prepare derivative works, and
 * perform publicly and display publicly, and to permit other to do so. 
 * 
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "util/file.h"
#include "util/util.h"
#include "lib/message.h"
#include "lib/privilege.h"
#include "lib/config_parser.h"

#include "../../runtime.h"


int singularity_runtime_rootfs_chroot_precheck(void) {
    return(0);
}


int singularity_runtime_rootfs_chroot_setup(void) {
    return(0);
}


int singularity_runtime_rootfs_chroot_activate(void) {
    return(0);
}


int singularity_runtime_rootfs_chroot_contain(void) {
    char *container_dir = singularity_runtime_containerdir(NULL);

    singularity_priv_escalate();
    singularity_message(VERBOSE, "Entering container file system root: %s\n", container_dir);
    if ( chroot(container_dir) < 0 ) { // Flawfinder: ignore (yep, yep, yep... we know!)
        singularity_message(ERROR, "failed chroot to container at: %s\n", container_dir);
        ABORT(255);
    }
    singularity_priv_drop();

    singularity_message(DEBUG, "Changing dir to '/' within the new root\n");
    if ( chdir("/") < 0 ) {
        singularity_message(ERROR, "Could not chdir after chroot to /: %s\n", strerror(errno));
        ABORT(1);
    }

    return(0);
}

