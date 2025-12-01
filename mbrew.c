// -*- MonkeyBrew Package Manager -*-
// (database located in /opt/mbrew/package.h)

#include "/opt/mbrew/packages.h"
#include <stdio.h>      // for printf, fprintf, snprintf
#include <stdlib.h>     // for system(), exit()
#include <string.h>     // for strcmp()

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
    if (strcmp(argv[1], "update")) { /* TODO */ }
    
    return 0;
}
