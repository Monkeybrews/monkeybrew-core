// -*- MonkeyBrew Package Manager -*-
// (database located in /opt/mbrew/package.h)

#include "/opt/mbrew/packages.h"
#include <stdio.h>      // for printf, fprintf, snprintf
#include <stdlib.h>     // for system(), exit()
#include <string.h>     // for strcmp()
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Fetch and install a package using curl + tar
void install_package(const char *name) {
    const PackageInfo *pkg = find_package(name);
    if (!pkg) {
        fprintf(stderr, "Error: No formulae or casks found for '%s'.\n", name);
        return;
    }

    printf("\033[1;34m=>\033[0m mbrew: Fetching \033[1;32m%s\033[0m (%s)\n", pkg->name, pkg->url);

    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
        "curl -L -o %s.tar.gz %s && "
        "tar -xf %s.tar.gz && "
        "cd %s-* && %s > configure.log 2>&1 && %s >> configure.log 2>&1",
        pkg->name, pkg->url, pkg->name, pkg->name,
        pkg->configure, pkg->build);
    printf("\033[1;34m=>\033[0m Brewing package... check configure.log for details...\n");

    int ret = system(cmd);
    if (ret == 0)
        printf("\033[1;32m%s\033[0m was brewed successfully!\n", pkg->name);
    else
        fprintf(stderr, "Error: failed to brew \033[1;32m%s\033[0m.\n", pkg->name);
}

void silent_update() {
    printf("\033[1;34m=>\033[0m Updating MonkeyBrew..\n");
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        return;
    } else if (pid == 0) {
        // Child process

        // Redirect stdin, stdout, stderr to /dev/null
        int devnull = open("/dev/null", O_RDWR);
        if (devnull < 0) _exit(1);

        dup2(devnull, STDIN_FILENO);
        dup2(devnull, STDOUT_FILENO);
        dup2(devnull, STDERR_FILENO);
        close(devnull);

        // Prepare command
        char *argv[] = {
            "bash",
            "-c",
            "curl -fsSL https://raw.githubusercontent.com/Monkeybrews/install/HEAD/install.sh | sudo /bin/bash -- update",
            NULL
        };

        execvp("/bin/bash", argv);
        printf("\033[1;34m=>\033[0m Updating formulaes..\n");

        // If execvp fails
        _exit(1);
    } else {
        // Parent process: wait for child
        int status;
        waitpid(pid, &status, 0);
    }
}

// Simple CLI
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Example usage:\n  %s install FORMULAE|CASK...\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "install") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: no package name provided.\n");
            return 1;
        }
        install_package(argv[2]);  // argv[2] is the package name
    }
    if (strcmp(argv[1], "update") == 0) {
        silent_update();
    }
    
    return 0;
}
